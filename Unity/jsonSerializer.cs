using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Numerics;
using UnityEditor;
using Quaternion = UnityEngine.Quaternion;
using Vector3 = UnityEngine.Vector3;
using System.Data;

[ExecuteInEditMode]
public class jsonSerializer : MonoBehaviour
{
	public TextAsset textJSON;
	
	public GameObject cube;
	public GameObject plane;
	public GameObject physicsCube;
	
	public bool isSave;
    public bool isLoad;
	
	public List<GameObject> toSave;
	
	[System.Serializable]
	public class Thing // multiple things in screen
	{
		public int type;
		public string name;
        public float mass;
        public float[] position;
		public float[] scale;
		public float[] rotation;
        public float[] euler;
    }
	
	[System.Serializable]
	public class ThingList
	{
		public Thing[] thing;
	}
	
	public ThingList myThingList = new ThingList();

#if UNITY_EDITOR
    void Awake()
    {
        EditorApplication.update += EditorUpdate;
    }

    void EditorUpdate()
    {
        if ((!EditorApplication.isPlaying) || EditorApplication.isPaused)
        {
            if (isSave)
            {
                SaveJsonScene();
                isSave = false;
            }
            if (isLoad)
            {
                LoadJsonScene();
                isLoad = false;
            }
        }
    }
    
    void OnDestroy()
    {
        EditorApplication.update -= EditorUpdate;
    }
#endif

    // Start is called before the first frame update
    void Start()
    {
        
    }
	
    // Update is called once per frame
    void Update()
    {	

    }
	
	public void AddObjectToList(GameObject gameObject)
	{
		toSave.Add(gameObject);
	}
	
	void SaveJsonScene()
	{
		myThingList = new ThingList();
		myThingList.thing = new Thing[toSave.Count];
		// emit game object to thing data
		for(int i = 0; i < toSave.Count; i++)
		{
			Thing thing = new Thing();
			thing.type = toSave[i].GetComponent<objectLister>().type;
			thing.name = toSave[i].name;

            Vector3 position;
            Quaternion rotation;
            Vector3 scale = toSave[i].transform.localScale;// because of plane sizing

            toSave[i].transform.GetPositionAndRotation(out position, out rotation);
            Vector3 eulerRotation = rotation.eulerAngles;

            thing.position = new [] { position.x, position.y, position.z };
            thing.scale = new[] {scale.x, scale.y, scale.z};
            thing.rotation = new [] { rotation.w, rotation.x, rotation.y, rotation.z };
            thing.euler = new[] { eulerRotation.x, eulerRotation.y, eulerRotation.z};

            if (thing.type == 2)
            {
                Rigidbody rigidbody = toSave[i].GetComponent<Rigidbody>();
                if (rigidbody != null)
                {
                    thing.mass = rigidbody.mass;
                }
            }

            myThingList.thing[i] = thing;
        }
		
		string output = JsonUtility.ToJson(myThingList);
		File.WriteAllText(Application.dataPath + "/unity_test.json", output);
	}
	
	void LoadJsonScene()
	{
		myThingList = JsonUtility.FromJson<ThingList>(textJSON.text);
		
		// parse thing data to game object
		foreach(Thing thing in myThingList.thing) // not confusing at all
        {
            Vector3 position = new Vector3(thing.position[0], thing.position[1], thing.position[2]);
            Vector3 scale = new Vector3(thing.scale[0], thing.scale[1], thing.scale[2]);
            Quaternion rotation = new Quaternion(thing.rotation[0], thing.rotation[1], thing.rotation[2], thing.rotation[3]);
            Vector3 euler = new Vector3(thing.euler[0], thing.euler[1], thing.euler[2]);

            GameObject gameObject;
            switch (thing.type)
			{
				case 0:
                    gameObject = Instantiate(cube, position, rotation);
					gameObject.name = thing.name;
                    gameObject.transform.localScale = scale;
					break;
				case 1:
                    gameObject = Instantiate(plane, position, rotation);
                    gameObject.name = thing.name;
                    gameObject.transform.localScale = scale;// because of plane sizing
                    break;
				case 2:
                    gameObject = Instantiate(physicsCube, position, rotation);
                    gameObject.name = thing.name;
                    gameObject.transform.localScale = scale;
                    Rigidbody rigidbody = gameObject.GetComponent<Rigidbody>();
                    if (rigidbody != null)
                    {
                        rigidbody.mass = thing.mass;
                    }
                    break;
			}
		}
	}
}
