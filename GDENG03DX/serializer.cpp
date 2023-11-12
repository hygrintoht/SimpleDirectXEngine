#include "serializer.h"

#include <iostream>

#include <json/json.h>

#include "gameObject.h"
#include "gameObjectManager.h"
#include "meshObject.h"

void serializer::saveScene()
{
    /*
    Json::Value jsonObject;
    Json::Value jsonArray;

    jsonArray.append("apple");
    jsonArray.append("banana");
    jsonArray.append("orange");

    jsonObject["fruits"] = jsonArray;

    // Serialize the JSON object to a string
    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, jsonObject);

    // Print the serialized JSON object
    std::cout << jsonString << std::endl;
    */

    /*
    format
    
    Scene:
		GameObject:
			name
			type
			transform
			MeshObject:
				filename
	*/

    std::vector<gameObject*> game_objects = gameObjectManager::get()->getAllObjects(); // get list of objects in scene

	Json::Value json_scene; // holds all the scene data

    for (auto& game_object : game_objects)
    {
        Json::Value json_game_object; // hold a data of the current game object
        json_game_object["name"] = game_object->getName();
        std::cout << game_object->getType() << std::endl;
        json_game_object["type"] = game_object->getType();
        Json::Value json_transform;
        for (int j = 0; j < 4; j++)
        {
            //Json::Value json_transform_line;
            for (int i = 0; i < 4; i++)
            {
                //json_transform_line.append(game_object->m_transform.m_mat[i][j]);
                json_transform.append(game_object->m_transform.m_mat[i][j]);
            }
            //json_transform.append(json_transform_line);
        }
        json_game_object["transform"] = json_transform;
        if(game_object->getType() == gameObject::mesh)
        {
            auto* mesh_object = dynamic_cast<meshObject*>(game_object);
            json_game_object["filename"] = mesh_object->getFilePath();
        }
        json_scene["scene"].append(json_game_object);
    }

    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, json_scene);

    // Print the serialized JSON object
    std::cout << jsonString << std::endl;

    // save to file stream
}

void serializer::loadScene()
{
	
}
