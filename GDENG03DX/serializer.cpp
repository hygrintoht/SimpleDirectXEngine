#include "serializer.h"

#include "cubeObject.h"
#include "iostream"
#include "fstream"

#include "json/json.h"

#include "gameObject.h"
#include "gameObjectManager.h"
#include "graphicsEngine.h"
#include "meshObject.h"
#include "uiManager.h"

void serializer::saveScene()
{
    std::string filepath;

    OPENFILENAME ofn;
    TCHAR szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = uiManager::get()->getWindowHandle();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(*szFile);
    ofn.lpstrFilter = L"JSON Scene File (*.json) \0 *.json\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn)) 
    {
        std::wstring filepathW = szFile;
        filepath = std::string(filepathW.begin(), filepathW.end());
    }

    save(filepath);
}

void serializer::openScene()
{
    std::string filepath;

    OPENFILENAME ofn;
    TCHAR szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = uiManager::get()->getWindowHandle();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(*szFile);
    ofn.lpstrFilter = L"JSON Scene File (*.json) \0 *.json\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) 
    {
        std::wstring filepathW = szFile;
        filepath = std::string(filepathW.begin(), filepathW.end());
    }

    open(filepath);
}

void serializer::saveScene(std::string filepath)
{
    save(filepath);
}

void serializer::openScene(std::string filepath)
{
    open(filepath);
}

void serializer::save(std::string filepath)
{
    std::vector<gameObject*> game_objects = gameObjectManager::get()->getAllObjects(); // get list of objects in scene

    Json::Value json_scene; // holds all the scene data

    for (auto& game_object : game_objects)
    {
        Json::Value json_game_object; // hold a data of the current game object
        // game object attributes
        json_game_object["name"] = game_object->getName();
        json_game_object["type"] = game_object->getType();
        Json::Value json_transform;
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                json_transform.append(game_object->m_transform.m_mat[i][j]);
                //std::printf("%+04f ", game_object->m_transform.m_mat[i][j]);
            }
            //std::cout << std::endl;
        }
        json_game_object["transform"] = json_transform;
        // additional attributes for game object extensions
        if (game_object->getType() == gameObject::gameObjectType::mesh)
        {
            auto* mesh_object = dynamic_cast<meshObject*>(game_object);
            json_game_object["filename"] = mesh_object->getFilePath();
        }
        json_scene["scene"].append(json_game_object);
        //std::cout << std::endl;
    }

    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, json_scene);

    // Print the serialized JSON object
    //std::cout << jsonString << std::endl;

    // save to file stream
    std::ofstream file(filepath);
    //std::ofstream file("sample.json");


    if (!file.is_open()) {
        std::cout << "Error opening file for writing!" << std::endl;
        return;
    }

    file << jsonString;
    file.close();
}

void serializer::open(std::string filepath)
{
    std::ifstream file(filepath);
    //std::ifstream file("sample.json");

    if (!file.is_open())
    {
        std::cout << "failed to open file" << std::endl;
        return;
    }

    Json::Value root;
    file >> root;
    file.close();
    /*
    if (!Json::parseFromStream(reader, file, &root, nullptr)) {
        std::cerr << "failed to parse json" << std::endl;
        return;
    }
    */

    const Json::Value jsonScene = root["scene"];
    // for each object in scene
    for (const Json::Value& jsonObject : jsonScene)
    {
        auto objectType = static_cast<gameObject::gameObjectType>(jsonObject["type"].asInt());
        std::string objectName = jsonObject["name"].asString();
        matrix4x4 objectTransform;
        objectTransform.setZero();

        const Json::Value jsonTransformArray = jsonObject["transform"];
        int row = 0;
        int column = 0;
        for (const Json::Value& jsonTransformValue : jsonTransformArray)
        {

            objectTransform.m_mat[row][column] = jsonTransformValue.asFloat();
            //std::printf("%+04f ", objectTransform.m_mat[row][column]);
            row++;
            if (row == 4)
            {
                //std::cout << std::endl;
                column++;
                row = 0;
            }
        }
        //std::cout << std::endl;

        // start object type checks



        void* shader_byte_code = nullptr;
        size_t size_shader = 0;

        switch (objectType)
        {
        case gameObject::gameObjectType::none:
        {
            /*
            auto* game_object = new gameObject(objectName);
            game_object->m_transform = objectTransform;

            gameObjectManager::get()->addObject(game_object);

            void* shader_byte_code = nullptr;
            size_t size_shader = 0;

            graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

            game_object->loadVertexBuffer(shader_byte_code, size_shader);
            */
            break;
        }

        case gameObject::gameObjectType::mesh:
        {
            std::string filename = jsonObject["filename"].asString();
            //std::cout << filepath << std::endl;

            auto* mesh_object = new meshObject(objectName);
            mesh_object->loadObjFileData(filename);
            mesh_object->m_transform = objectTransform;

            mesh_object->changeAnimationType(-1);

            gameObjectManager::get()->addObject(mesh_object);

            graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

            mesh_object->loadVertexBuffer(shader_byte_code, size_shader);
            break;
        }

        case gameObject::gameObjectType::cube:
        {
            auto* cube_object = new cubeObject(objectName);

            cube_object->m_transform = objectTransform;
            cube_object->changeSpeed(randomFloat(0.5f, 0.5f));

            gameObjectManager::get()->addObject(cube_object);

            graphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);

            cube_object->loadVertexBuffer(shader_byte_code, size_shader);
            break;
        }
        }
        // end object type checks

        // add components to game object
    }

}
