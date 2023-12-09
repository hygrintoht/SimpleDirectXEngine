using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class objectLister : MonoBehaviour
{
    public int type;

    private jsonSerializer serializer;
    // Start is called before the first frame update
    void Awake()
    {
        serializer = FindObjectOfType<jsonSerializer>();

        serializer.AddObjectToList(gameObject);
    }
}
