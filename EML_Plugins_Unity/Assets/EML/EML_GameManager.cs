using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EML_GameManager : MonoBehaviour
{
    private static EML_GameManager instance;
    public EML_GameManager Instance
    {
        get
        {
            if (instance == null)
                instance = new EML_GameManager();

            return instance;
        }
        private set
        {
            instance = value;
        }
    }

    public EML_GameManager()
    {

    }

    private void Awake()
    {
        // If there is an instance, and it's not me, delete myself.
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }

        // Make sure this object is not destroyed when loading, changing maps etc.
        DontDestroyOnLoad(this);

    }
}
