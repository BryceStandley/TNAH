#include "tnahpch.h"
#include "Serializer.h"

#include "GameObject.h"
#include "Components/AI/AIComponent.h"
#include "Components/AI/CharacterComponent.h"
#include "TNAH/Core/Application.h"

#define ALPHA_SEARCH_STRING "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm"

namespace tnah {
    
    
    Resource Serializer::s_SceneResource = Resource();

#pragma region Serialize
    bool Serializer::SaveScene(Ref<Scene> scene, const std::string& saveFilePath)
    {
        if(saveFilePath != "" && scene != nullptr)
        {
            return SerializeScene(scene, saveFilePath);
        }

        return false;
    }



    bool Serializer::SerializeScene(Ref<Scene> scene, const std::string& filePath)
    {
        std::fstream sceneFile;
        sceneFile.exceptions(std::fstream::failbit | std::fstream::badbit);
        try
        {
            sceneFile.open(filePath.c_str(), std::fstream::out);
            std::stringstream ss;
            ss << GenerateTagOpen("scene", 0);
            ss << GenerateGlobalSettings(scene);

            ss << GenerateSceneSettings(scene);
            
            ss << GenerateTagClose("scene");

            std::string s = ss.str();
            //sceneFile.write(s.c_str(), s.size());
            sceneFile << s << std::endl;
            sceneFile.close();
        }
        catch(std::fstream::failure& e)
        {
            TNAH_CORE_ERROR("{0}", e.what());
            TNAH_CORE_ASSERT(false, "Scene file failed to open");
        }
        return false;
    }

    std::string Serializer::GenerateGlobalSettings(Ref<Scene> scene)
    {
        
        auto sceneCam = scene->GetSceneCamera();
        auto sceneLight = scene->GetSceneLight();
        std::stringstream ss;

        ss << GenerateTagOpen("global", 1);
        if(scene->m_IsEditorScene)
        {
            auto editorCam = scene->GetEditorCamera();
            ss << GenerateTagOpen("editor", 2);
            ss << GenerateTagEntry(editorCam.GetComponent<TagComponent>(), 3);
            ss << GenerateTransform(editorCam.GetComponent<TransformComponent>(), 3);
            ss << GenerateCamera(editorCam.GetComponent<EditorCameraComponent>(), 3);
            ss << GenerateTagClose("editor", 2);
        }

        ss << GenerateTagOpen("sceneCamera", 2);
        ss << GenerateTagEntry(sceneCam.GetComponent<TagComponent>(), 3);
        ss << GenerateTransform(sceneCam.GetComponent<TransformComponent>(),3 );
        ss << GenerateCamera(sceneCam.GetComponent<CameraComponent>(), 3);
        ss << GenerateTagClose("sceneCamera", 2);

        ss << GenerateTagOpen("sceneLight", 2);
        if(sceneLight.HasComponent<TagComponent>(), 3)
            ss << GenerateTagEntry(sceneLight.GetComponent<TagComponent>(), 3);
        ss << GenerateTransform(sceneLight.GetComponent<TransformComponent>(), 3);
        ss << GenerateLight(sceneLight.GetComponent<LightComponent>(), 3);
        ss << GenerateTagClose("sceneLight", 2);
        
        ss << GenerateTagClose("global", 1);

        return ss.str();
    }

    std::string Serializer::GenerateSceneSettings(Ref<Scene> scene)
    {
        auto& objects = scene->GetGameObjectsInScene();
        std::stringstream ss;
        ss << GenerateTagOpen("hierarchy", 1);
        for(auto& go : objects)
        {
            //Skip if the game object is a global game object
            if(go.first == scene->GetSceneCamera().GetUUID()) continue;
            if(go.first == scene->GetSceneLight().GetUUID()) continue;
            if(go.first == scene->GetEditorCamera().GetUUID()) continue;
            
            ss << GenerateTagOpen("gameObject", 2);
            auto& g = go.second;
            if(g.HasComponent<TagComponent>())
                ss << GenerateTagEntry(g.GetComponent<TagComponent>(), 3);
            if(g.HasComponent<TransformComponent>())
                ss << GenerateTransform(g.GetComponent<TransformComponent>(), 3);
            if(g.HasComponent<CameraComponent>())
                ss << GenerateCamera(g.GetComponent<CameraComponent>(), 3);
            if(g.HasComponent<TerrainComponent>())
                ss << GenerateTerrain(g.GetComponent<TerrainComponent>(), 3);
            if(g.HasComponent<MeshComponent>())
                ss << GenerateMesh(g.GetComponent<MeshComponent>(), 3);
            if(g.HasComponent<LightComponent>())
                ss << GenerateLight(g.GetComponent<LightComponent>(), 3);
            if(g.HasComponent<SkyboxComponent>())
                ss << GenerateSkybox(g.GetComponent<SkyboxComponent>(), 3);
            if(g.HasComponent<AudioListenerComponent>())
                ss << GenerateAudioListener(g.GetComponent<AudioListenerComponent>(), 3);
            if(g.HasComponent<AudioSourceComponent>())
                ss << GenerateAudioSource(g.GetComponent<AudioSourceComponent>(), 3);
            if(g.HasComponent<RigidBodyComponent>())
                ss << GenerateRigidBody(g.GetComponent<RigidBodyComponent>(), 3);
            if (g.HasComponent<AIComponent>() && g.HasComponent<CharacterComponent>())
                ss << GenerateAi(g.GetComponent<AIComponent>(), g.GetComponent<CharacterComponent>(), 3);
            if (g.HasComponent<AStarComponent>())
                ss << GenerateAStar(g.GetComponent<AStarComponent>(), 3);
            if (g.HasComponent<AStarObstacleComponent>())
                ss << GenerateAStarObstacle(g.GetComponent<AStarObstacleComponent>());
            if (g.HasComponent<Affordance>())
                ss << GenerateAffordance(g.GetComponent<Affordance>());
            
            ss << GenerateTagClose("gameObject", 2);
        }
        ss << GenerateTagClose("hierarchy", 1);
        
        return ss.str();
    }

    std::string Serializer::GenerateTagOpen(const std::string& tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        return tabs +"<" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagClose(const std::string& tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        return tabs + "</" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagOpen(const char* tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        std::string s = tabs + "<";
        s += tagType;
        s += ">\n";
        return  s;
    }

    std::string Serializer::GenerateTagClose(const char* tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        
        std::string s = tabs +"</";
        s += tagType;
        s += ">\n";
        return  s;
    }

    std::string Serializer::GenerateTransform(const TransformComponent& transform, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("transform", totalTabs);

        ss << GenerateValueEntry("position", transform.Position, totalTabs+1);
        ss << GenerateValueEntry("rotation", transform.Rotation, totalTabs+1);
        ss << GenerateValueEntry("scale", transform.Scale, totalTabs+1);
        
        ss << GenerateTagClose("transform", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateCamera(const SceneCamera& camera, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("camera", totalTabs);
        if(camera.m_ProjectionType == SceneCamera::ProjectionType::Orthographic)
        {
            ss << GenerateValueEntry("orthographic", true, totalTabs + 1);
            ss << GenerateValueEntry("size", camera.m_OrthographicSize, totalTabs + 1);
            ss << GenerateValueEntry("near", camera.m_OrthographicNear, totalTabs + 1);
            ss << GenerateValueEntry("far", camera.m_OrthographicFar, totalTabs + 1);
        }
        else
        {
            ss << GenerateValueEntry("perspective", true, totalTabs + 1);
            ss << GenerateValueEntry("fov", camera.GetPerspectiveVerticalFOV(), totalTabs + 1);
            ss << GenerateValueEntry("near", camera.m_PerspectiveNear, totalTabs + 1);
            ss << GenerateValueEntry("far", camera.m_PerspectiveFar, totalTabs + 1);
        }
        ss << GenerateTagClose("camera", totalTabs);
        return ss.str();
        
    }

    std::string Serializer::GenerateTerrain(const TerrainComponent& terrain, const uint32_t& totalTabs)
    {
        std::stringstream ss;

        ss << GenerateTagOpen("terrain", totalTabs);
        ss << GenerateDirectoryEntry("heightmap", terrain.SceneTerrain->m_HeightmapPath, totalTabs + 1);
        ss << GenerateTagClose("terrain", totalTabs);

        return ss.str();
    }

    std::string Serializer::GenerateSkybox(const SkyboxComponent& skybox, const uint32_t& totalTabs)
    {
        std::stringstream ss;

        ss << GenerateTagOpen("skybox", totalTabs);
        const auto textures = skybox.SceneSkybox->GetMaterial()->GetCubemapProperties();
        
        ss << GenerateDirectoryEntry("front", textures.Front.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry("back", textures.Back.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry("top", textures.Top.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry("bottom", textures.Bottom.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry("left", textures.Left.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry("right", textures.Right.RelativeDirectory, totalTabs + 1);
        
        ss << GenerateTagClose("skybox", totalTabs);

        return ss.str();
    }
    
    std::string Serializer::GenerateMesh(const MeshComponent& mesh, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("mesh", totalTabs);
        ss << GenerateDirectoryEntry("model", mesh.Model->GetResource().RelativeDirectory, totalTabs + 1);
        ss << GenerateTagClose("mesh", totalTabs);

        return ss.str();
        
    }

    std::string Serializer::GenerateLight(const LightComponent& light, const uint32_t& totalTabs)
    {
        auto l = light.Light;
        std::stringstream ss;

        ss << GenerateTagOpen("light", totalTabs);
        ss << GenerateValueEntry("sceneLight", l->m_IsSceneLight, totalTabs + 1);
        ss << GenerateValueEntry("direction", l->m_Direction, totalTabs + 1);
        ss << GenerateValueEntry("color", l->m_Color, totalTabs + 1);
        ss << GenerateValueEntry("intensity", l->m_Intensity, totalTabs + 1);

        ss << GenerateTagClose("light", totalTabs);

        return ss.str();
    }

    std::string Serializer::GenerateAudioListener(const AudioListenerComponent& sound, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("audiolistener", totalTabs);
        ss << GenerateValueEntry("active", sound.m_ActiveListing,totalTabs +1);
        ss << GenerateTagClose("audiolistener", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateAudioSource(const AudioSourceComponent& sound, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("audiosource", totalTabs);
        ss << GenerateDirectoryEntry("sound", sound.m_File.RelativeDirectory.c_str(), totalTabs+1);
        ss << GenerateValueEntry("minimum", sound.m_MinDistance, totalTabs+1);
        ss << GenerateValueEntry("volume", sound.m_Volume, totalTabs+1);
        ss << GenerateValueEntry("shoot", sound.m_Shoot, totalTabs+1);
        ss << GenerateValueEntry("loop", sound.m_Loop, totalTabs+1);
        ss << GenerateTagClose("audiosource", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateAffordance(Affordance& astar, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("affordance", totalTabs + 1);
        ss << GenerateValueEntry("tag", astar.GetTag());
        for(int i = 1; i < 10; i++)
        {
            std::cout << i << std::endl;
            ss << GenerateValueEntry(Affordance::GetActionString((Actions)i), astar.GetActionValue((Actions)i), totalTabs+1);
        }
        ss << GenerateTagClose("affordance", totalTabs + 1);
        return ss.str();
    }

    std::string Serializer::GenerateAStarObstacle(const AStarObstacleComponent& astar, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("astarobstacle", totalTabs + 1);
        ss << GenerateValueEntry("dynamic", astar.dynamic,  totalTabs+1);
        ss << GenerateTagClose("astarobstacle", totalTabs + 1);
        return ss.str();
    }

    std::string Serializer::GenerateRigidBody(const RigidBodyComponent& rb, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("rigidbody", totalTabs);
        
        if(rb.Body->GetType() == tnah::Physics::BodyType::Dynamic)
            ss << GenerateValueEntry("type", "dynamic", totalTabs+1);
        else if(rb.Body->GetType() == Physics::BodyType::Static)   
            ss << GenerateValueEntry("type", "static", totalTabs+1);
        else
            ss << GenerateValueEntry("type", "kinematic", totalTabs+1);

        ss << GenerateValueEntry("linearLock", rb.Body->m_LinearRotationLock, totalTabs+1);
        ss << GenerateValueEntry("angularLock", rb.Body->m_AngularRotationLock, totalTabs+1);
        ss << GenerateValueEntry("linearDamp", rb.Body->m_LinearDampening, totalTabs+1);
        ss << GenerateValueEntry("angularDamp", rb.Body->m_AngularDampening, totalTabs+1);

        //No need to save the inverse mass, when loading, it can be found from the mass.
        ss << GenerateValueEntry("mass", rb.Body->m_BodyMass.Mass, totalTabs + 1);
        ss << GenerateValueEntry("localCOM", rb.Body->m_BodyMass.LocalCentreOfMass, totalTabs + 1);
        
        ss << GenerateValueEntry("ignoreGravity", rb.Body->m_IgnoreGravity, totalTabs + 1);
        ss << GenerateValueEntry("sleepVelocity", rb.Body->m_SleepVelocityThreshold, totalTabs + 1);
        ss << GenerateValueEntry("sleepTime", rb.Body->m_SleepTimeThreshold, totalTabs + 1);

        if(rb.Body->HasColliders())
        {
            ss << GenerateTagOpen("colliders", totalTabs + 1);
            for(auto col : rb.Body->m_Colliders)
            {
                ss << GenerateCollider(col.second, totalTabs + 2);
            }
            ss << GenerateTagClose("colliders", totalTabs + 1);
        }
        ss << GenerateTagClose("rigidbody", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateCollider(const Ref<Physics::Collider>& col, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        auto t = col->GetType();
        switch(t)
        {
        case Physics::Collider::Type::Box:
            {
                ss << GenerateTagOpen("boxCollider", totalTabs);
                
                auto s = static_cast<rp3d::BoxShape*>(col->m_Collider);
                glm::vec3 ext = Math::FromRp3dVec3(s->getHalfExtents()) * 2.0f;
                ss << GenerateValueEntry("extents", ext, totalTabs + 1);
                ss << GenerateValueEntry("localPosition", col->m_LocalPosition, totalTabs + 1);
                ss << GenerateValueEntry("localOrientation", col->m_LocalOrientation, totalTabs + 1);
                ss << GenerateValueEntry("density", col->m_Density, totalTabs + 1);
                ss << GenerateValueEntry("volume", col->m_Volume, totalTabs + 1);
                
                ss << GenerateTagClose("boxCollider", totalTabs);
                break;
            }
        case Physics::Collider::Type::Sphere:
            {
                ss << GenerateTagOpen("sphereCollider", totalTabs);
                auto s = static_cast<rp3d::SphereShape*>(col->m_Collider);
                ss << GenerateValueEntry("radius", s->getRadius(), totalTabs + 1);
                ss << GenerateValueEntry("localPosition", col->m_LocalPosition, totalTabs + 1);
                ss << GenerateValueEntry("localOrientation", col->m_LocalOrientation, totalTabs + 1);
                ss << GenerateValueEntry("density", col->m_Density, totalTabs + 1);
                ss << GenerateValueEntry("volume", col->m_Volume, totalTabs + 1);
                ss << GenerateTagClose("sphereCollider", totalTabs);
                break;
            }
        case Physics::Collider::Type::Capsule:
            {
                ss << GenerateTagOpen("capsuleCollider", totalTabs);
                auto s = static_cast<rp3d::CapsuleShape*>(col->m_Collider);
                ss << GenerateValueEntry("radius", s->getRadius(), totalTabs + 1);
                ss << GenerateValueEntry("Height", s->getHeight(), totalTabs + 1);
                ss << GenerateValueEntry("localPosition", col->m_LocalPosition, totalTabs + 1);
                ss << GenerateValueEntry("localOrientation", col->m_LocalOrientation, totalTabs + 1);
                ss << GenerateValueEntry("density", col->m_Density, totalTabs + 1);
                ss << GenerateValueEntry("volume", col->m_Volume, totalTabs + 1);
                ss << GenerateTagClose("capsuleCollider", totalTabs);
                break;
            }
        default: break;
        }

        return ss.str();
        
    }
    
    std::string Serializer::GenerateAStar(const AStarComponent& astar, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("astar", totalTabs);
        ss << GenerateValueEntry("position", glm::vec3(astar.StartingPos.x, 0, astar.StartingPos.y), totalTabs+1);
        ss << GenerateValueEntry("size", glm::vec3(astar.Size.x, 0, astar.Size.y), totalTabs+1);
        ss << GenerateTagClose("astar", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateAi(const AIComponent& ai, const CharacterComponent& c, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("ai", totalTabs);
        ss << GenerateValueEntry("type", (int)c.currentCharacter, totalTabs + 1);
        ss << GenerateTagClose("ai", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateVec3(const glm::vec3& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        const char* comp[] = {"x", "y", "z"};
        for(uint32_t i = 0; i < 3; i++)
        {
            ss << GenerateValueEntry(comp[i], value[i],totalTabs);
            
        }
        return ss.str();
        
    }

    std::string Serializer::GenerateVec4(const glm::vec4& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        const char* comp[] = {"x", "y", "z", "w"};
        for(uint32_t i = 0; i < 4; i++)
        {
            ss << GenerateValueEntry(comp[i], value[i],totalTabs);
            
        }
        return ss.str();
        
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const glm::vec4& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateVec4(value, totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const glm::vec3& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateVec3(value, totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateDirectoryEntry(const std::string& tagType, const std::string& path, const uint32_t& totalTabs)
    {
        std::stringstream ss;

        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("directory", totalTabs+1);
        ss << GenerateValueEntry("path", path, totalTabs+2);
        ss << GenerateTagClose("directory", totalTabs+1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateTagEntry(const TagComponent& tag, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("tag", totalTabs);
        ss << GenerateValueEntry("name", tag.Tag, totalTabs + 1);
        ss << GenerateTagClose("tag", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const float& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        
        std::stringstream ss;

        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        ss << tabs + std::to_string(value) + "\n";
        ss << GenerateTagClose("value", totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }
    
    std::string Serializer::GenerateValueEntry(const std::string& tagType, const int& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        std::stringstream ss;

        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs+ 1);
        ss << tabs + std::to_string(value) + "\n";
        ss << GenerateTagClose("value", totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }
    
    std::string Serializer::GenerateValueEntry(const std::string& tagType, const bool& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        std::stringstream ss;

        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        if(value)
            ss << tabs + "true\n";
        else
            ss << tabs + "false\n";
        ss << GenerateTagClose("value", totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const std::string& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        ss << tabs +value + "\n";
        ss << GenerateTagClose("value", totalTabs+ 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }
    
    std::string Serializer::GenerateValueEntry(const std::string& tagType, const glm::mat3& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs +3; i++)
            tabs += "\t";
        
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        
        ss << GenerateTagOpen("mat3", totalTabs + 2);
        ss << tabs + Utility::MatToString(value) + "\n";
        ss << GenerateTagClose("mat3", totalTabs + 2);
        
        ss << GenerateTagClose("value", totalTabs+ 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const glm::quat& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(uint32_t i = 0; i < totalTabs +3; i++)
            tabs += "\t";
        
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        
        ss << GenerateTagOpen("quaternion", totalTabs + 2);
        ss << tabs + Utility::QuatToString(value) + "\n";
        ss << GenerateTagClose("quaternion", totalTabs + 2);
        
        ss << GenerateTagClose("value", totalTabs+ 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }
#pragma endregion Serialize

#pragma region Deserialize

    Ref<Scene> Serializer::LoadScene(const std::string& saveFilePath)
    {
        if(saveFilePath != "")
        {
            return DeserializeScene(saveFilePath);
        }

        return nullptr;
    }

    Ref<Scene> Serializer::DeserializeScene(const std::string& filePath)
    {
        std::string result;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
                in.close();
            }
            else
            {
                TNAH_CORE_ERROR("Could not read from file '{0}'", filePath);
                return nullptr;
            }
        }
        else
        {
            TNAH_CORE_ERROR("Could not open file '{0}'", filePath);
            return nullptr;
        }

        // the file has been opened and read in to a string, now parse the string like normal finding the required tags
        int currentPos = 0;
        Ref<Scene> scene = nullptr;
        s_SceneResource = Resource(filePath);
        scene = GetGlobalSettingsFromFile(scene, result, currentPos);
        if(scene != nullptr)
        {
            scene = GetSceneStructureFromFile(scene, result, currentPos);
           if(scene != nullptr)
           {
               return scene;
           }
            return scene;
        }

        return nullptr;
    }

    Ref<Scene> Serializer::GetGlobalSettingsFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos)
    {
        //check each level of the global settings to make sure nothing is missing
        // if anything is missing, the file is corrupt, return false
        const auto sceneTags = FindTags("scene", fileContents);
        if(CheckTags(sceneTags))
        {
            const auto global = FindTags("global", fileContents);
            if(CheckTags(global))
            {
                currentPos = (int)global.second; // the current position in the string is the end of the global section
                if(Application::Get().CheckEditor()) // Only create and check editor scene related objects if the application is in editor mode
                {
                    const auto editor = FindTags("editor", fileContents);
                    if(CheckTags(editor))
                    {
                    
                        scene = Scene::CreateNewEditorScene();
                        auto tag = FindTags("tag", fileContents);
                        if(CheckTags(tag))
                        {
                            auto& editorCam = scene->GetEditorCamera();
                            //auto tagPos = FindTags("tag", fileContents, editor.first, editor.second);
                            auto transformPos = FindTags("transform", fileContents, editor.first, editor.second);
                            auto cameraPos = FindTags("camera", fileContents, editor.first, editor.second);
                        
                            auto& t = editorCam.GetComponent<TagComponent>();
                            t = GetTagFromFile(fileContents, tag);

                            auto& transform = editorCam.Transform();
                            transform = GetTransformFromFile(fileContents, transformPos);

                            auto& camera = editorCam.GetComponent<EditorCameraComponent>();
                            camera.EditorCamera = GetCameraFromFile(fileContents, cameraPos);
                        }
                    }
                }
                else { scene = Scene::CreateEmptyScene(); }
                auto sceneCam = FindTags("sceneCamera", fileContents);
                if(CheckTags(sceneCam))
                {
                    auto cam = scene->GetSceneCamera();
                    auto tagPos = FindTags("tag", fileContents, sceneCam.first, sceneCam.second);
                    auto transformPos = FindTags("transform", fileContents, sceneCam.first, sceneCam.second);
                    auto cameraPos  = FindTags("camera", fileContents, sceneCam.first, sceneCam.second);

                    auto& tag = cam.GetComponent<TagComponent>();
                    auto& camera = cam.GetComponent<CameraComponent>();
                    auto& transform = cam.Transform();

                    tag = GetTagFromFile(fileContents, tagPos);
                    camera.Camera = GetCameraFromFile(fileContents, cameraPos);
                    transform = GetTransformFromFile(fileContents, transformPos);
                }
                else GenerateValuesLoadError("Scene Camera");

                auto sceneLight = FindTags("sceneLight", fileContents);
                if(CheckTags(sceneLight))
                {
                    auto light = scene->GetSceneLight();
                    auto tagPos = FindTags("tag", fileContents, sceneLight.first, sceneLight.second);
                    auto transformPos = FindTags("transform", fileContents, sceneLight.first, sceneLight.second);
                    auto lightPos = FindTags("light", fileContents, sceneLight.first, sceneLight.second);

                    auto& tag = light.GetComponent<TagComponent>();
                    auto& transform = light.Transform();
                    auto& sLight = light.GetComponent<LightComponent>();

                    tag = GetTagFromFile(fileContents, tagPos);
                    transform = GetTransformFromFile(fileContents, transformPos);
                    //sLight.Light = GetLightFromFile(fileContents, lightPos).Light;
                }
                else GenerateValuesLoadError("Scene Light");
                return scene;
            }
            return nullptr; 
        }
        return nullptr;
    }

    Ref<Scene> Serializer::GetSceneStructureFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos)
    {
        
        auto hierarchy = FindTags("hierarchy", fileContents, currentPos);
        int nextGameobjectPos = (int)hierarchy.first;
        if(CheckTags(hierarchy))
        {
            auto go = FindTags("gameObject", fileContents, nextGameobjectPos);
            while(CheckTags(go))
            {
                if(!GetGameObjectFromFile(scene, fileContents, go))
                {
                    GenerateValuesLoadError("GameObject");
                }
                nextGameobjectPos = (int)go.second + (int)strlen("</gameObject>");
                go = FindTags("gameObject", fileContents, nextGameobjectPos);
            }
            return scene;
        }
        return nullptr;
    }

    Ref<Scene> Serializer::GetGameObjectFromFile(Ref<Scene> scene, const std::string& fileContents,
        std::pair<size_t, size_t> gameObjectTagPositions)
    {
        
        
        auto tagPos = FindTags("tag", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        auto transformPos = FindTags("transform", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);

        if(!CheckTags(tagPos) || !CheckTags(transformPos)) return nullptr;
        
        auto tag = GetTagFromFile(fileContents, tagPos);
        auto object = scene->CreateGameObject(tag.Tag);
        auto& transform = object.Transform();
        transform = GetTransformFromFile(fileContents, transformPos);
        
        FindAndAddComponentsFromFile(object, fileContents, gameObjectTagPositions);

        return scene;
    }

    int Serializer::FindAndAddComponentsFromFile(GameObject& gameObject, const std::string& fileContents,
        std::pair<size_t, size_t> gameObjectTagPositions)
    {
        //Here we just try and find each component in the file and add it to the component if we find a entry for ii
        int added = 0;
        auto cameraPos = FindTags("camera", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(cameraPos))
        {
            gameObject.AddComponent<CameraComponent>(GetCameraFromFile(fileContents, cameraPos));
            added++;
        }

        auto meshPos = FindTags("mesh", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(meshPos))
        {
            TNAH_CORE_INFO("Mesh: {0} {1}", meshPos.first, meshPos.second);
            gameObject.AddComponent<MeshComponent>(GetMeshFromFile(fileContents, meshPos));
            added++;
        }

        auto playerControllerPos = FindTags("playerController", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(playerControllerPos))
        {
            gameObject.AddComponent<PlayerControllerComponent>(GetPlayerControllerFromFile(fileContents, playerControllerPos));
            added++;
        }

        auto nativePos = FindTags("nativeScript", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(nativePos))
        {
            gameObject.AddComponent<NativeScriptComponent>(GetNativeScriptFromFile(fileContents, nativePos));
            added++;
        }

        auto terrainPos = FindTags("terrain", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(terrainPos))
        {
            gameObject.AddComponent<TerrainComponent>(GetTerrainFromFile(fileContents, terrainPos));
            added++;
        }

        auto lightPos = FindTags("light", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(lightPos))
        {
            gameObject.AddComponent<LightComponent>(GetLightFromFile(fileContents, lightPos));
            added++;
        }

        auto skyboxPos = FindTags("skybox", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(skyboxPos))
        {
            gameObject.AddComponent<SkyboxComponent>(GetSkyboxFromFile(fileContents, skyboxPos));
            added++;
        }

        auto rigidPos = FindTags("rigidbody", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(rigidPos))
        {
            GetRigidBodyFromFile(fileContents, rigidPos, gameObject);
            added++;
        }

        auto ai = FindTags("ai", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(ai))
        {
            //gameObject.AddComponent<CharacterComponent>(GetAiFromFile(fileContents, ai));
            gameObject.AddComponent<AIComponent>();
            added++;
        }

        auto astar = FindTags("astar", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(astar))
        {
            gameObject.AddComponent<AStarComponent>(GetAstarFromFile(fileContents, astar));
            added++;
        }

        auto aff = FindTags("affordance", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(aff))
        {
            gameObject.AddComponent<Affordance>(GetAffordancesFromFile(fileContents, aff));
            added++;
        }

        auto obstacle = FindTags("astarobstacle", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(obstacle))
        {
            gameObject.AddComponent<AStarObstacleComponent>(GetAstarObstacleFromFile(fileContents, obstacle));
            added++;
        }
        
        return added;
    }

    Affordance Serializer::GetAffordancesFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        std::string t = GetStringValueFromFile("tag", fileContents, componentTagPositions);
        Affordance temp(t);
        for(int i = 1; i < 10; i++)
        {
            float value = GetFloatValueFromFile(Affordance::GetActionString((Actions)i), fileContents, componentTagPositions);
            temp.SetActionValues((Actions)i, value);
        }

        return temp;
    }

    bool Serializer::GetAstarObstacleFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        return GetBoolValueFromFile("dynamic", fileContents, componentTagPositions); 
    }

    CharacterNames Serializer::GetAiFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        return (CharacterNames)GetIntValueFromFile("type", fileContents, componentTagPositions);
        
    }

    AStarComponent Serializer::GetAstarFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        glm::vec3 pos = GetVec3FromFile("position", fileContents, componentTagPositions);
        glm::vec3 size = GetVec3FromFile("size", fileContents, componentTagPositions);
        AStarComponent temp(Int2((int)pos.x, (int)pos.z), Int2((int)size.x, (int)size.z));
        return temp;
    }


    TagComponent Serializer::GetTagFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto tag = GetStringValueFromFile("name", fileContents, componentTagPositions);
        return TagComponent(tag);
    }

    TransformComponent Serializer::GetTransformFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto position = GetVec3FromFile("position", fileContents, componentTagPositions);
        auto rotation = GetVec3FromFile("rotation", fileContents, componentTagPositions);
        auto scale = GetVec3FromFile("scale", fileContents, componentTagPositions);
        return TransformComponent(position, rotation, scale);
    }

    SceneCamera Serializer::GetCameraFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        SceneCamera camera;
        bool perspective = GetBoolValueFromFile("perspective", fileContents, componentTagPositions);
        
        if(perspective)
        {
            float fov = GetFloatValueFromFile("fov", fileContents, componentTagPositions);
            float nearVal = GetFloatValueFromFile("near", fileContents, componentTagPositions);
            float farVal = GetFloatValueFromFile("far", fileContents, componentTagPositions);
            camera.SetPerspective(fov, nearVal, farVal);
        }
        else
        {
            float size = GetFloatValueFromFile("size", fileContents, componentTagPositions);
            float nearClip = GetFloatValueFromFile("near", fileContents, componentTagPositions);
            float farClip = GetFloatValueFromFile("far", fileContents, componentTagPositions);
            camera.SetOrthographic(size, nearClip, farClip);
        }
        
        return camera;
    }

    SkyboxComponent Serializer::GetSkyboxFromFile(const std::string& fileContents,
                                                  std::pair<size_t, size_t> componentTagPositions)
    {
        //TODO: finish skybox

        Texture3DProperties skybox = {
            GetDirectoryFromFile("front", fileContents, componentTagPositions),
            GetDirectoryFromFile("back", fileContents, componentTagPositions),
            GetDirectoryFromFile("left", fileContents, componentTagPositions),
            GetDirectoryFromFile("right", fileContents, componentTagPositions),
            GetDirectoryFromFile("top", fileContents, componentTagPositions),
            GetDirectoryFromFile("bottom", fileContents, componentTagPositions)
        };

        
        return SkyboxComponent(skybox);
    }

    TerrainComponent Serializer::GetTerrainFromFile(const std::string& fileContents,
                                                    std::pair<size_t, size_t> componentTagPositions)
    {
        auto heightmap = GetDirectoryFromFile("heightmap", fileContents, componentTagPositions);
        return TerrainComponent(heightmap);
    }

    MeshComponent Serializer::GetMeshFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto mesh = GetDirectoryFromFile("model", fileContents, componentTagPositions);
        return MeshComponent(mesh);
    }


    void Serializer::GetRigidBodyFromFile(const std::string& fileContents,
                                          std::pair<size_t, size_t> componentTagPositions, GameObject& gameObject)
    {
        auto type = GetStringValueFromFile("type", fileContents, componentTagPositions);
        auto rb = gameObject.AddComponent<RigidBodyComponent>(gameObject);
        if(type == "static")
        {
            rb.Body->SetType(Physics::BodyType::Static);
        }
        else if(type == "kinematic")
        {
            rb.Body->SetType(Physics::BodyType::Kinematic);
        }
        rb.Body->m_LinearRotationLock = GetVec3FromFile("linearLock", fileContents, componentTagPositions);
        rb.Body->m_AngularRotationLock = GetVec3FromFile("angularLock", fileContents, componentTagPositions);
        rb.Body->m_LinearDampening = GetFloatValueFromFile("linearDamp", fileContents, componentTagPositions);
        rb.Body->m_AngularDampening = GetFloatValueFromFile("angularDamp", fileContents, componentTagPositions);
        
        rb.Body->m_BodyMass.SetMass(GetFloatValueFromFile("mass", fileContents, componentTagPositions));
        rb.Body->m_BodyMass.LocalCentreOfMass = GetVec3FromFile("localCOM", fileContents, componentTagPositions);
        
        rb.Body->m_IgnoreGravity = GetBoolValueFromFile("ignoreGravity", fileContents, componentTagPositions);
        rb.Body->m_SleepVelocityThreshold = GetFloatValueFromFile("sleepVelocity", fileContents, componentTagPositions);
        rb.Body->m_SleepTimeThreshold = GetFloatValueFromFile("sleepTime", fileContents, componentTagPositions);

        auto t = FindTags("colliders", fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            //This rb has colliders
           GetColliderFromFile(fileContents, t, rb);
        }
    }

    bool Serializer::GetColliderFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions, RigidBodyComponent& rb)
    {
        auto t = FindTags("boxCollider", fileContents, componentTagPositions.first, componentTagPositions.second);
        while(CheckTags(t))
        {
            auto ext = GetVec3FromFile("extents", fileContents, t);
            auto pos  = GetVec3FromFile("localPosition", fileContents, t);
            auto ori  = GetVec3FromFile("localOrientation", fileContents, t);
            auto dense = GetFloatValueFromFile("density", fileContents, t);
            auto vol = GetFloatValueFromFile("volume", fileContents, t);
            rb.AddCollider(ext, pos, ori, dense, vol);
            t = FindTags("boxCollider", fileContents, componentTagPositions.first, componentTagPositions.second);
        }

        t = FindTags("sphereCollider", fileContents, componentTagPositions.first, componentTagPositions.second);
        while(CheckTags(t))
        {
            auto rad = GetFloatValueFromFile("radius", fileContents, t);
            auto pos  = GetVec3FromFile("localPosition", fileContents, t);
            auto ori  = GetVec3FromFile("localOrientation", fileContents, t);
            auto dense = GetFloatValueFromFile("density", fileContents, t);
            auto vol = GetFloatValueFromFile("volume", fileContents, t);
            rb.AddCollider(rad, pos, ori, dense, vol);
            t = FindTags("sphereCollider", fileContents, componentTagPositions.first, componentTagPositions.second);
        }

        t = FindTags("capsuleCollider", fileContents, componentTagPositions.first, componentTagPositions.second);
        while(CheckTags(t))
        {
            auto rad = GetFloatValueFromFile("radius", fileContents, t);
            auto hei = GetFloatValueFromFile("height", fileContents, t);
            auto pos  = GetVec3FromFile("localPosition", fileContents, t);
            auto ori  = GetVec3FromFile("localOrientation", fileContents, t);
            auto dense = GetFloatValueFromFile("density", fileContents, t);
            auto vol = GetFloatValueFromFile("volume", fileContents, t);
            rb.AddCollider(rad, hei, pos, ori, dense, vol);
            t = FindTags("capsuleCollider", fileContents, componentTagPositions.first, componentTagPositions.second);
        }

        if(rb.Body->HasColliders())
            return true;
        
            return false;
    }
    
    
    PlayerControllerComponent Serializer::GetPlayerControllerFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        uint16_t forward = (uint16_t)GetIntValueFromFile("keyForward", fileContents, componentTagPositions);
        uint16_t backward = (uint16_t)GetIntValueFromFile("keyBackward", fileContents, componentTagPositions);
        uint16_t left = (uint16_t)GetIntValueFromFile("keyLeft", fileContents, componentTagPositions);
        uint16_t right = (uint16_t)GetIntValueFromFile("keyRight", fileContents, componentTagPositions);

        std::pair<uint16_t, uint16_t> sprint = {
            (uint16_t)GetIntValueFromFile("keySprint1", fileContents, componentTagPositions),
            (uint16_t)GetIntValueFromFile("keySprint2", fileContents, componentTagPositions)
        };
        
        uint16_t jump = (uint16_t)GetIntValueFromFile("keyJump", fileContents, componentTagPositions);
        uint16_t crouch = (uint16_t)GetIntValueFromFile("keyCrouch", fileContents, componentTagPositions);

        auto playerHeight = GetFloatValueFromFile("playerHeight", fileContents, componentTagPositions);
        auto movementSpeed = GetFloatValueFromFile("movementSpeed", fileContents, componentTagPositions);
        auto rotationSensitivity = GetFloatValueFromFile("rotationSensitivity", fileContents, componentTagPositions);
        auto sprintSpeed = GetFloatValueFromFile("sprintSpeed", fileContents, componentTagPositions);
        auto crouchSpeed = GetFloatValueFromFile("crouchSpeed", fileContents, componentTagPositions);
        auto crouchHeightMultiplier = GetFloatValueFromFile("crouchHeightMultiplier", fileContents, componentTagPositions);

        auto pc = PlayerControllerComponent();
        pc.Forward = forward;
        pc.Backward = backward;
        pc.Left = left;
        pc.Right = right;
        pc.Sprint = sprint;
        pc.Jump = jump;
        pc.Crouch = crouch;
        pc.PlayerHeight = playerHeight;
        pc.MovementSpeed = movementSpeed;
        pc.RotationSensitivity = rotationSensitivity;
        pc.SprintSpeed = sprintSpeed;
        pc.CrouchSpeed = crouchSpeed;
        pc.CrouchHeightMultiplier = crouchHeightMultiplier;

        return pc;
    }

    NativeScriptComponent Serializer::GetNativeScriptFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        return NativeScriptComponent();
    }

    LightComponent Serializer::GetLightFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto sceneLight = GetBoolValueFromFile("sceneLight", fileContents, componentTagPositions);
        auto direction = GetVec3FromFile("direction", fileContents, componentTagPositions);
        auto ambient = GetVec3FromFile("ambient", fileContents, componentTagPositions);
        auto diffuse = GetVec3FromFile("diffuse", fileContents, componentTagPositions);
        auto specular = GetVec3FromFile("specular", fileContents, componentTagPositions);
        auto position = GetVec3FromFile("position", fileContents, componentTagPositions);
        auto color = GetVec4FromFile("color", fileContents, componentTagPositions);
        auto distance = GetIntValueFromFile("distance", fileContents, componentTagPositions);
        auto constant = GetFloatValueFromFile("constant", fileContents, componentTagPositions);
        auto linear = GetFloatValueFromFile("linear", fileContents, componentTagPositions);
        auto quadratic = GetFloatValueFromFile("quadratic", fileContents, componentTagPositions);
        auto cutoff = GetFloatValueFromFile("cutoff", fileContents, componentTagPositions);
        auto intensity = GetFloatValueFromFile("intensity", fileContents, componentTagPositions);
        auto type = GetIntValueFromFile("type", fileContents, componentTagPositions);

        LightComponent light;
        switch (type)
        {
            case 0: light = LightComponent(Light::LightType::Directional); break;
            case 1: light = LightComponent(Light::LightType::Point); break;
            case 2: light = LightComponent(Light::LightType::Spot); break;
            default: break;
        }
        light.Light->SetDirection(direction);
        light.Light->SetAmbient(ambient);
        light.Light->SetDiffuse(diffuse);
        light.Light->SetSpecular(specular);
        light.Light->SetPosition(position);
        light.Light->SetColor(color);
        light.Light->SetDistance(distance);
        light.Light->SetConstant(constant);
        light.Light->SetLinear(linear);
        light.Light->SetQuadratic(quadratic);
        light.Light->SetCutOff(cutoff);
        light.Light->SetIntensity(intensity);
        
        return light;
    }

    std::pair<size_t, size_t> Serializer::FindTags(const std::string& tagToFind, const std::string& fileContents, size_t from, size_t to)
    {
        std::string o = "<"; o += tagToFind + ">";
        std::string c = "</"; c += tagToFind + ">";
        if(from == 0 && to == 0)
        {
            size_t openTag = fileContents.find(o, from);
            size_t closeTag = fileContents.find(c, from);
            return {openTag, closeTag};
        }

        const auto count = to - from;
        auto open = fileContents.find(o, from);
        auto close = fileContents.find(c, from);
        
        if(CheckTags({open, close}))
            return {open, close};
        return {-1,-1};

        
    }

    bool Serializer::CheckTags(std::pair<size_t, size_t> tags)
    {
        if(tags.first != std::string::npos && tags.second != std::string::npos)
            return true;
        
        return false;
    }
    
    glm::vec3 Serializer::GetVec3FromFile(const std::string& tagName, const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            glm::vec3 out = glm::vec3(GetVec4FromFile(tagName, fileContents, componentTagPositions));
            return out;
        }

        return glm::vec3(0.0f);
    }

    glm::vec4 Serializer::GetVec4FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            glm::vec4 out;
            out.x = GetFloatValueFromFile("x", fileContents, t);
            out.y = GetFloatValueFromFile("y", fileContents, t);
            out.z = GetFloatValueFromFile("z", fileContents, t);
            out.w = GetFloatValueFromFile("w", fileContents, t);

            return out;
        }
        return glm::vec4(0.0f);
    }

    std::string Serializer::GetDirectoryFromFile(const std::string& tagName, const std::string& fileContents,
                                                 std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first);
        if(CheckTags(t))
        {
            return GetStringValueFromFile("path", fileContents, t);
        }
        return "";
    }

    int Serializer::GetIntValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\n");
                size_t numberStart = fileContents.find_first_of("-0123456789", from);
                size_t numberEnd = fileContents.find_first_of("\r\n", numberStart);
                std::string out =  fileContents.substr(numberStart, (numberEnd - numberStart));
                return std::stoi(out);
            }
        }
        return 0;
    }

    float Serializer::GetFloatValueFromFile(const std::string& tagName, const std::string& fileContents,
                                            std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\n");
                size_t numberStart = fileContents.find_first_of("-0123456789", from);
                size_t numberEnd = fileContents.find_first_of("\n", numberStart);
                std::string out =  fileContents.substr(numberStart, (numberEnd - numberStart));
                return std::stof(out);
            }
        }
        return 0;
    }

    bool Serializer::GetBoolValueFromFile(const std::string& tagName, const std::string& fileContents,
                                          std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\n");
                size_t boolStart = fileContents.find_first_of("tf", from);
                size_t boolEnd = fileContents.find_first_of("\r\n", boolStart);
                std::string out =  fileContents.substr(boolStart, (boolEnd - boolStart));
                if(out.compare("true") == 0)
                    return true;
            }
        }
        return false;
    }

    std::string Serializer::GetStringValueFromFile(const std::string& tagName, const std::string& fileContents,
                                                   std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\r\n");
                // Use a capital search string to find the start of the drive letter
                size_t stringStart = fileContents.find_first_of(ALPHA_SEARCH_STRING, from);
                size_t stringEnd = fileContents.find_first_of("\r\n", stringStart);
                std::string out =  fileContents.substr(stringStart, (stringEnd - stringStart));
                return out;
            }
        }
        return "";
    }

    void Serializer::GenerateValuesLoadError(const std::string& tagName)
    {
        std::string error = "Failed to load values for ";
        error += tagName;
        error += " from scene '{0}' at path '{1}'";
        TNAH_WARN(error, s_SceneResource.CustomName, s_SceneResource.AbsoluteDirectory);
        TNAH_WARN("Object defaults loaded");
    }

#pragma endregion Deserialize
    
}
