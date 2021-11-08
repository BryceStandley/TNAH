#pragma once
#include "Scene.h"
#include "Components/AI/Affordance.h"
#include "Components/AI/AIComponent.h"
#include "Components/AI/CharacterComponent.h"
#include "TNAH/Physics/Collider.h"

namespace tnah
{
    class Serializer
    {
    public:

        /**
         * @brief Public serializer save scene function
         * @author Bryce Standley
         * @date 06-11-2021
         * @return true 
         * @return false 
         */
        static bool SaveScene(Ref<Scene> scene, const std::string& saveFilePath);

        /**
         * @brief Public serializer load scene function
         * @author Bryce Standley
         * @date 06-11-2021
         * @return Ref<Scene> 
         */
        static Ref<Scene> LoadScene(const std::string& saveFilePath);
    
    private: 
        /**
         * 
         * \fn Ref<Scene> DeserializeScene
         * 
         * \brief Deserializes a scene from a file into memory
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param filePath
         * 
         * \return 
         * 
         */
        static Ref<Scene> DeserializeScene(const std::string& filePath);
     
    
      /**
        * 
        * \fn bool SerializeScene
        * 
        * \brief Serializes the scene to the given file path
        * 
        * \author Bryce Standley
        * \date 13/9/2021
        * 
        * \param scene
        * \param filePath
        * 
        * \return 
        * 
        */
        static bool SerializeScene(Ref<Scene> scene, const std::string& filePath);
    
        /**
         * 
         * \fn std::string GenerateGlobalSettings
         * 
         * \brief Generates global settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param scene
         * 
         * \return 
         * 
         */
        static std::string GenerateGlobalSettings(Ref<Scene> scene);

        /**
         * 
         * \fn std::string GenerateSceneSettings
         * 
         * \brief Generates scene settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param scene
         * 
         * \return 
         * 
         */
        static std::string GenerateSceneSettings(Ref<Scene> scene);
        
        //Components
        /**
         * 
         * \fn std::string GenerateTransform
         * 
         * \brief Generates transform settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param transform
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateTransform(const TransformComponent& transform, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateCamera
         * 
         * \brief Generates Camera settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param camera
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateCamera(const SceneCamera& camera, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateSkybox
         * 
         * \brief Generates skybox settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param skybox
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateSkybox(const SkyboxComponent& skybox, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateTerrain
         * 
         * \brief Generates transform terrain to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param terrain
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateTerrain(const TerrainComponent& terrain, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateMesh
         * 
         * \brief Generates mesh settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param mesh
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateMesh(const MeshComponent& mesh, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateLight
         * 
         * \brief Generates light settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param light
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateLight(const LightComponent& light, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateAudioListener
         * 
         * \brief Generates audio listener settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param sound
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateAudioListener(const AudioListenerComponent& sound, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateAudioSource
         * 
         * \brief Generates audio source settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param sound
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateAudioSource(const AudioSourceComponent& sound, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateRigidBody
         * 
         * \brief Generates rigidbody settings to serialize
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param rb
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateRigidBody(const RigidBodyComponent& rb, const uint32_t& totalTabs = 0);

        /**
        * 
        * \fn std::string GenerateCollider(const Ref<Physics::Collider>& col, const uint32_t& totalTabs = 0);
        * 
        * \brief Generates collider settings to serialize
        * 
        * \author Bryce Standley
        * \date 13/9/2021
        * 
        * \param col
        * \param totalTabs
        * 
        * \return string
        * 
        */
        static std::string GenerateCollider(const Ref<Physics::Collider>& col, const uint32_t& totalTabs = 0);

        /**
         * @brief Generates a AI conponent to serialize
         * @author Christopher Logan
         * @date 06-11-2021
         * @return std::string 
         */
        static std::string GenerateAi(const AIComponent& ai, const CharacterComponent &c,const uint32_t& totalTabs = 0);

        /**
         * @brief Generates a Astar component to serialize
         * @author Christopher Logan
         * @date 06-11-2021
         * @return std::string 
         */
        static std::string GenerateAStar(const AStarComponent& astar, const uint32_t& totalTabs = 0);

        /**
         * @brief Generates a Astar obstacle component to serialize
         * @author Christopher Logan
         * @date 06-11-2021
         * @return std::string 
         */
        static std::string GenerateAStarObstacle(const AStarObstacleComponent& astar, const uint32_t& totalTabs = 0);

        /**
         * @brief Generates a Affordance component to serialize
         * @author Christopher Logan
         * @date 06-11-2021
         * @return std::string 
         */
        static std::string GenerateAffordance(Affordance& astar, const uint32_t& totalTabs = 0);

        //Tag creators
        /**
         * 
         * \fn std::string GenerateTagOpen(const std::string& tagType, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates open tags with a custom type
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateTagOpen(const std::string& tagType, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateTagClose(const std::string& tagType, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates close tags with a custom type
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateTagClose(const std::string& tagType, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateTagOpen(const char* tagType, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates open tags with a custom type
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateTagOpen(const char* tagType, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateTagClose(const char* tagType, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates close tags with a custom type
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateTagClose(const char* tagType, const uint32_t& totalTabs = 0);
        
        //Helpers for different data types
        /**
         * 
         * \fn std::string GenerateVec3(const glm::vec3& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates vec3 output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateVec3(const glm::vec3& value, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateVec4(const glm::vec4& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates vec4 output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateVec4(const glm::vec4& value, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateValueEntry(const std::string& tagType, const glm::vec3& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates vec3 entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const glm::vec3& value, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateValueEntry(const std::string& tagType, const glm::vec4& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates vec4 entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const glm::vec4& value, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateDirectoryEntry(const std::string& tagType, const std::string& path, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates directory entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param path
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateDirectoryEntry(const std::string& tagType, const std::string& path, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateValueEntry(const std::string& tagType, const float& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates value entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const float& value, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateValueEntry(const std::string& tagType, const int& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates value entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const int& value, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateValueEntry(const std::string& tagType, const bool& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates value entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const bool& value, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateTagEntry(const TagComponent& tag, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates value entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tag
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateTagEntry(const TagComponent& tag, const uint32_t& totalTabs = 0);

        /**
         * 
         * \fn std::string GenerateValueEntry(const std::string& tagType, const std::string& value, const uint32_t& totalTabs = 0);
         * 
         * \brief Generates value entry with custom type output for serialization
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagType
         * \param value
         * \param totalTabs
         * 
         * \return 
         * 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const std::string& value, const uint32_t& totalTabs = 0);
     
        /**
         * @brief Generates a Mat3 value entry to serialize
         * @author Bryce Standley
         * @date 06-11-2021
         * @return std::string 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const glm::mat3& value, const uint32_t& totalTabs = 0);

        /**
         * @brief Generates a quaternion value entry to serialize
         * @author Bryce Standley
         * @date 06-11-2021
         * @return std::string 
         */
        static std::string GenerateValueEntry(const std::string& tagType, const glm::quat& value, const uint32_t& totalTabs = 0);

    private:
     
        /**
         * 
         * \fn Ref<Scene> GetGlobalSettingsFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos);
         * 
         * \brief Gets global settings from a serialized file
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param scene
         * \param fileContents
         * \param currentPos
         * 
         * \return 
         * 
         */
        static Ref<Scene> GetGlobalSettingsFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos);

        /**
         * 
         * \fn std::pair<size_t, size_t> FindTags(const std::string& tagToFind, const std::string& fileContents, size_t from = 0, size_t to = 0);
         * 
         * \brief Finds tags within the open file
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagToFind
         * \param fileContents
         * \param from
         * \param to
         * 
         * \return 
         * 
         */
        static std::pair<size_t, size_t> FindTags(const std::string& tagToFind, const std::string& fileContents, size_t from = 0, size_t to = 0);

        /**
         * 
         * \fn bool CheckTags(std::pair<size_t, size_t> tags);
         * 
         * \brief Checks if the given tags are valid
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tags
         * 
         * \return 
         * 
         */
        static bool CheckTags(std::pair<size_t, size_t> tags);
        
        /**
         * 
         * \fn Ref<Scene> GetSceneStructureFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos);
         * 
         * \brief Gets the scene structure form the file contents
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param scene
         * \param fileContents
         * \param currentPos
         * 
         * \return 
         * 
         */
        static Ref<Scene> GetSceneStructureFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos);
        
        /**
         * 
         * \fn Ref<Scene> GetGameObjectFromFile(Ref<Scene> scene, const std::string& fileContents, std::pair<size_t, size_t> gameObjectTagPositions);
         * 
         * \brief Gets a game object from the file contents
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param scene
         * \param fileContents
         * \param gameObjectTagPositions
         * 
         * \return 
         * 
         */
        static Ref<Scene> GetGameObjectFromFile(Ref<Scene> scene, const std::string& fileContents, std::pair<size_t, size_t> gameObjectTagPositions);

        /**
         * 
         * \fn int FindAndAddComponentsFromFile(GameObject& gameObject, const std::string& fileContents, std::pair<size_t, size_t> gameObjectTagPositions);
         * 
         * \brief Finds and adds a component to a game object from the file contents
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param gameObject
         * \param fileContents
         * \param gameObjectTagPositions
         * 
         * \return 
         * 
         */
        static int FindAndAddComponentsFromFile(GameObject& gameObject, const std::string& fileContents, std::pair<size_t, size_t> gameObjectTagPositions);

        /**
         * 
         * \fn TagComponent GetTagFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Gets a custom tag from the file contents
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static TagComponent GetTagFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
        
        /**
         * 
         * \fn TransformComponent GetTransformFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<transform> </transform>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static TransformComponent GetTransformFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn SceneCamera GetCameraFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<camera> </camera>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static SceneCamera GetCameraFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn SkyboxComponent GetSkyboxFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<skybox> </skybox>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static SkyboxComponent GetSkyboxFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn TerrainComponent GetTerrainFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<terrain> </terrain>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static TerrainComponent GetTerrainFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn MeshComponent GetMeshFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<mesh> </mesh>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static MeshComponent GetMeshFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn void GetRigidBodyFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions, GameObject& gameObject);
         * 
         * \brief Finds the all data for the scene within '<rigidbody> </rigidbody>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * \param gameObject
         * 
         * \return 
         * 
         */
        static void GetRigidBodyFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions, GameObject& gameObject);

        /**
         * 
         * \fn bool GetColliderFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions, RigidBodyComponent& rb);
         * 
         * \brief Finds the all data for the scene within '<boxCollider> </boxCollider>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * \param rb
         * 
         * \return 
         * 
         */
        static bool GetColliderFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions, RigidBodyComponent& rb);
        
        /**
         * 
         * \fn PlayerControllerComponent GetPlayerControllerFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<playerControl> </playerControl>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static PlayerControllerComponent GetPlayerControllerFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn NativeScriptComponent GetNativeScriptFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<native> </native>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static NativeScriptComponent GetNativeScriptFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
        
        /**
         * 
         * \fn LightComponent GetLightFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds the all data for the scene within '<light> </light>' tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static LightComponent GetLightFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
     
        /**
         * @brief Get the Ai From File
         * @author Christopher Logan
         * @date 06-11-2021
         * @return CharacterNames 
         */
        static CharacterNames GetAiFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * @brief Get the Astar From File
         * @author Christopher Logan
         * @date 06-11-2021
         * @return AStarComponent 
         */
        static AStarComponent GetAstarFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * @brief Get the Astar Obstacle From File
         * @author Christopher Logan
         * @date 06-11-2021
         * @return true 
         * @return false 
         */
        static bool GetAstarObstacleFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * @brief Get the Affordances From File
         * @author Christopher Logan
         * @date 06-11-2021
         * @return Affordance 
         */
        static Affordance GetAffordancesFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
     
        /**
         * 
         * \fn glm::vec3 GetVec3FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds values of a vec3 for a component with a given search tag
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static glm::vec3 GetVec3FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn glm::vec4 GetVec4FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds values of a vec4 for a component with a given search tag
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static glm::vec4 GetVec4FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn std::string GetDirectoryFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds a path from a directory entry between <directory> </directory> tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static std::string GetDirectoryFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn int GetIntValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds a int value between <value> </value> tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static int GetIntValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn float GetFloatValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds a float value between <value> </value> tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static float GetFloatValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn bool GetBoolValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds a bool value between <value> </value> tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static bool GetBoolValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
         * 
         * \fn std::string GetStringValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
         * 
         * \brief Finds a string value between <value> </value> tags
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * \param fileContents
         * \param componentTagPositions
         * 
         * \return 
         * 
         */
        static std::string GetStringValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
        
        /**
         * 
         * \fn void GenerateValuesLoadError(const std::string& tagName);
         * 
         * \brief Generates a error if a vaule failed to load
         * 
         * \author Bryce Standley
         * \date 13/9/2021
         * 
         * \param tagName
         * 
         * 
         */
        static void GenerateValuesLoadError(const std::string& tagName);

        /** @brief Resource of the current scene */
        static Resource s_SceneResource;
        
        friend class EditorLayer;
        friend class Editor;
    };

    


}
