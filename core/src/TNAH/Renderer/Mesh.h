#pragma once
#define MAX_BONE_INFLUENCE 4

#include "TNAH/Core/Core.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Renderer/VertexArray.h"
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Material.h"
#include "Animation.h"
#include "BoneInfo.h"

#pragma warning(push, 0)
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>


#pragma warning(pop)


namespace tnah {

/**
 * @struct	Vertex
 *
 * @brief	A vertex.
 *
 * @author	Bryce Standley
 * @date	12/09/2021
 */

struct Vertex
{

    /** @brief	The position */
    glm::vec3 Position;

    /** @brief	The normal */
    glm::vec3 Normal;

    /** @brief	The tangent */
    glm::vec3 Tangent;

    /** @brief	The bitangents */
    glm::vec3 Bitangents;

    /** @brief	The texcoord */
    glm::vec2 Texcoord;
    

    /** @brief	bone IDs */
    uint32_t IDs[MAX_BONE_INFLUENCE];

    /** @brief	The weights of bones */
    float Weights[MAX_BONE_INFLUENCE];

    /**
     * @fn	void AddBoneData(uint32_t BoneID, float Weight)
     *
     * @brief	Adds bone data
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     *
     * @param 	BoneID	Identifier for the bone.
     * @param 	Weight	The weight.
     */

    void AddBoneData(uint32_t BoneID, float Weight)
    {
        for (size_t i = 0; i < 4; i++)
        {
            if (Weights[i] == 0.0)
            {
                IDs[i] = BoneID;
                Weights[i] = Weight;
                return;
            }
        }

        // TODO: Keep top weights
        TNAH_CORE_WARN("Vertex has more than four bones/weights affecting it, extra data will be discarded (BoneID={0}, Weight={1})", BoneID, Weight);
    }
};

    /**
     * @struct	MeshTexture
     *
     * @brief	A mesh texture
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     */

    struct MeshTexture
    {

        /** @brief	The texture */
        Ref<Texture2D> Texture;

        /** @brief	Full pathname of the texture file */
        std::string TexturePath;

        /**
         * @fn	MeshTexture(Ref<Texture2D> texture, const std::string& path)
         *
         * @brief	Constructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	texture	The texture.
         * @param 	path   	Full pathname of the file.
         */

        MeshTexture(Ref<Texture2D> texture, const std::string& path)
            :Texture(texture), TexturePath(path)
        {}
    };

    /**
     * @struct	MeshShader
     *
     * @brief	A mesh shader.
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     */

    struct MeshShader
    {

        /** @brief	The shader */
        Ref<Shader> Shader;

        /** @brief	Full pathname of the vertex shader file */
        std::string VertexShaderPath;

        /** @brief	Full pathname of the fragment shader file */
        std::string FragmentShaderPath;

        /**
         * @fn	MeshShader(Ref<tnah::Shader> shader, const std::string& vertex, const std::string& fragment)
         *
         * @brief	Constructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	shader  	The shader.
         * @param 	vertex  	The vertex.
         * @param 	fragment	The fragment.
         */

        MeshShader(Ref<tnah::Shader> shader, const std::string& vertex, const std::string& fragment)
            :Shader(shader), VertexShaderPath(vertex), FragmentShaderPath(fragment)
        {}
    };

    /**
     * @class	Mesh
     *
     * @brief	A mesh class responsible for handling the meshes of models 
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     */

    class Mesh  {
    public:

        /**
         * @fn	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture2D>> textures, bool animated);
         *
         * @brief	Constructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	vertices	The vertices.
         * @param 	indices 	The indices.
         * @param 	textures	The textures.
         * @param 	animated	True if animated.
         */

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture2D>> textures, bool animated);

        /**
         * @fn	Ref<VertexArray> Mesh::GetMeshVertexArray() const
         *
         * @brief	Gets mesh vertex array
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The mesh vertex array.
         */

        Ref<VertexArray> GetMeshVertexArray() const {return m_Vao;}

        /**
         * @fn	Ref<VertexBuffer> Mesh::GetMeshVertexBuffer() const
         *
         * @brief	Gets mesh vertex buffer
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The mesh vertex buffer.
         */

        Ref<VertexBuffer> GetMeshVertexBuffer() const {return m_Vbo;}

        /**
         * @fn	Ref<IndexBuffer> Mesh::GetMeshIndexBuffer() const
         *
         * @brief	Gets mesh index buffer
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The mesh index buffer.
         */

        Ref<IndexBuffer> GetMeshIndexBuffer() const {return m_Ibo;}

        /**
         * @fn	Ref<Material> Mesh::GetMeshMaterial() const
         *
         * @brief	Gets mesh material
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The mesh material.
         */

        Ref<Material> GetMeshMaterial() const {return m_Material;}

        /**
         * @fn	std::vector<glm::vec3> Mesh::GetVertexPositions() const;
         *
         * @brief	Gets vertex positions
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The vertex positions.
         */

        std::vector<glm::vec3> GetVertexPositions() const;

        /**
         * @fn	std::vector<uint32_t> Mesh::GetIndices() const
         *
         * @brief	Gets the indices
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The indices.
         */

        std::vector<uint32_t> GetIndices() const { return m_Indices; }
    private:
        
        /** @brief	The vertices */
        std::vector<Vertex> m_Vertices;

        /** @brief	The indices */
        std::vector<uint32_t> m_Indices;

        /** @brief	True if animated */
        bool m_Animated;
     
        /** @brief	The vao */
        Ref<VertexArray> m_Vao;

        /** @brief	The vbo */
        Ref<VertexBuffer> m_Vbo;

        /** @brief	The ibo */
        Ref<IndexBuffer> m_Ibo;

        /** @brief	The VertexBufferLayout */
        VertexBufferLayout m_BufferLayout;

        /** @brief	The material */
        Ref<Material> m_Material;
     

     
        friend class EditorUI;
    };

    /**
     * @class	Model
     *
     * @brief	A model class that inherits from the refCounted class, which allows model to use the Ref *. Responsible for the loading and handling of models
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     */

    class Model : public RefCounted
    {
    public:

        /**
         * @fn	static Ref<Model> Model::Create(const std::string& filePath);
         *
         * @brief	Creates a new model
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	filePath	Full pathname of the file.
         *
         * @returns	A model
         */

        static Ref<Model> Create(const std::string& filePath);

        /**
         * @fn	Model::Model();
         *
         * @brief	Default constructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        Model();

        /**
         * @fn	Model::Model(const std::string& filePath);
         *
         * @brief	Constructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	filePath	Full pathname of the file.
         */

        Model(const std::string& filePath);

        /**
         * @fn	auto& Model::GetAnimation()
         *
         * @brief	Gets the animation
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The animation.
         */

        auto& GetAnimation() { return m_Animation; }

        /**
         * @fn	std::vector<Mesh> Model::GetMeshes() const
         *
         * @brief	Gets the meshes
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The meshes.
         */

        std::vector<Mesh> GetMeshes() const { return m_Meshes; }

        /**
         * @fn	uint32_t Model::GetNumberOfMeshes() const
         *
         * @brief	Gets number of meshes
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The number of meshes.
         */

        uint32_t GetNumberOfMeshes() const { return static_cast<uint32_t>(m_Meshes.size()); }

        /**
         * @fn	auto& Model::GetBoneInfoMap()
         *
         * @brief	Gets bone information map
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The bone information map.
         */

        auto& GetBoneInfoMap() { return m_BoneInfoMap; }

        /**
         * @fn	int& Model::GetBoneCount()
         *
         * @brief	Gets bone count
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	The bone count.
         */

        int& GetBoneCount() { return m_BoneCounter; }
        const Resource& GetResource() const { return m_Resource; }
    private:


        /** @brief	The meshes */
        std::vector<Mesh> m_Meshes;

        Resource m_Resource;

        /** @brief	The animation */
        Animation m_Animation;

        /** @brief	The bone information map */
        std::map<std::string, BoneInfo> m_BoneInfoMap;

        /** @brief	The bone counter */
        int m_BoneCounter = 0;

        /** @brief	True if is animated, false if not */
        bool m_IsAnimated = false;

        /**
         * @fn	glm::mat4 Model::AiToGLM(aiMatrix4x4t<float> m);
         *
         * @brief	Converts aiMatrix to glm::mat4
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	m	An aiMatrix4x4t to process.
         *
         * @returns	A glm::mat4.
         */

        glm::mat4 AiToGLM(aiMatrix4x4t<float> m);

        /**
         * @fn	glm::vec3 Model::AiToGLM(aiVector3t<float> v);
         *
         * @brief	Converts aiVector to glm::vec3
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	v	An aiVector3t to process.
         *
         * @returns	A glm::vec3.
         */

        glm::vec3 AiToGLM(aiVector3t<float> v);

        /**
         * @fn	glm::quat Model::AiToGLM(aiQuaterniont<float> q);
         *
         * @brief	Converts aiQuaterniont to glm::quat 
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	q	An aiQuaterniont to process.
         *
         * @returns	A glm::quat.
         */

        glm::quat AiToGLM(aiQuaterniont<float> q);

        /**
         * @fn	void Model::SetVertexBoneDataToDefault(Vertex& vertex);
         *
         * @brief	Sets vertex bone data to default
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	vertex	The vertex.
         */

        void SetVertexBoneDataToDefault(Vertex& vertex);

        /**
         * @fn	void Model::SetVertexBoneData(Vertex& vertex, int boneID, float weight);
         *
         * @brief	Sets vertex bone data
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	vertex	The vertex.
         * @param 		  	boneID	Identifier for the bone.
         * @param 		  	weight	The weight.
         */

        void SetVertexBoneData(Vertex& vertex, int boneID, float weight);

        /**
         * @fn	void Model::ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
         *
         * @brief	Extracts the bone weight for vertices
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	vertices	The vertices.
         * @param [in,out]	mesh		If non-null, the mesh.
         * @param 		  	scene   	The scene.
         */

        void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

        /**
         * @fn	void Model::LoadModel(const std::string& filePath);
         *
         * @brief	Loads a model
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	filePath	Full pathname of the file.
         */

        void LoadModel(const std::string& filePath);

        /**
         * @fn	void Model::ProcessNode(aiNode* node, const aiScene* scene);
         *
         * @brief	Process the node
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	node 	If non-null, the node.
         * @param 		  	scene	The scene.
         */

        void ProcessNode(aiNode* node, const aiScene* scene);

        /**
         * @fn	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, bool animated);
         *
         * @brief	Process the mesh
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	mesh		If non-null, the mesh.
         * @param 		  	scene   	The scene.
         * @param 		  	animated	True if animated.
         *
         * @returns	A Mesh.
         */

        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, bool animated);

        /**
         * @fn	std::vector<Ref<Texture2D>> Model::LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName);
         *
         * @brief	Loads material textures
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 		  	scene   	The scene.
         * @param [in,out]	material	If non-null, the material.
         * @param 		  	type		The type.
         * @param 		  	typeName	Name of the type.
         *
         * @returns	The material textures.
         */

        std::vector<Ref<Texture2D>> LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName);
        friend class EditorUI;
        friend class Serializer;
    };

}

