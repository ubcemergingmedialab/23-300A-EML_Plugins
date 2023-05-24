using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEditor;
using UnityEditor.SceneManagement;
using System.Security.Policy;
using System.Reflection;
using UnityEditor.Callbacks;


public class EML_Core_Unity : Editor
{

    [MenuItem("EML/Generate EML Project Structure")]
    public static void EMLMenuItem()
    {
        // Generating Project Structure Here

        List<string> projectFolders = new List<string>()
        {
            "EML",
            "EML/AI",
            "EML/Art",
            "EML/Art/Materials",
            "EML/Art/Meshes",
            "EML/Art/Models",
            "EML/Art/Textures",
            "EML/Art/Sprites",
            "EML/Animations",
            "EML/Audio",
            "EML/Audio/Music",
            "EML/Audio/Sound",
            "EML/Cinematics",
            "EML/Databases",
            "EML/Editor",
            "EML/Effects",
            "EML/Fonts",
            "EML/Maps",
            "EML/Misc",
            "EML/Media",
            "EML/OOP",
            "EML/OOP/Actors",
            "EML/OOP/Actors/NPCs",
            "EML/OOP/Actors/Pawns",
            "EML/OOP/Actors/Objects",
            "EML/OOP/Code",
            "EML/OOP/Controllers",
            "EML/OOP/Data",
            "EML/OOP/Environment",
            "EML/OOP/Network",
            "EML/OOP/UI",
            "EML/Shaders",
            "ThirdParty",
            "Developers"
        };

        for (int i = 0; i < projectFolders.Count; i++)
        {
            if (!Directory.Exists("Assets/" + projectFolders[i]))
            {
                Directory.CreateDirectory("Assets/" + projectFolders[i]);
            }
        }

        AssetDatabase.Refresh();
    }


    [MenuItem("EML/EML Coding Styleguide")]
    public static void EML_CodingStyleguide()
    {
        Application.OpenURL(@"https://eml.ubc.ca");
    }

    [MenuItem("EML/Contact Information")]
    public static void EML_ContactInformation()
    {
        Application.OpenURL(@"https://eml.ubc.ca");
    }

}

