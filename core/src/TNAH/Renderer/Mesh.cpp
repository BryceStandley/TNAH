#include <tnahpch.h>
#include "Mesh.h"
#include "AssimpGLMHelpers.h"


#include "Renderer.h"

namespace tnah {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture2D>> textures, bool animated)
    {
         m_Vertices = vertices;
        m_Indices = indices;
        m_Animated = animated;

        m_BufferLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            {ShaderDataType::Float3, "a_Tangent"},
            {ShaderDataType::Float3, "a_Bitangent"},
            {ShaderDataType::Float2, "a_TexCoord"},
            {ShaderDataType::Int4, "a_BoneIds"},
            {ShaderDataType::Float4, "a_Weights"}
        };
        
        m_Vao = VertexArray::Create();
        
        m_Vbo = VertexBuffer::Create(&vertices[0], (uint32_t)(sizeof(Vertex) * vertices.size()));

        m_Vbo->SetLayout(m_BufferLayout);
        m_Vao->AddVertexBuffer(m_Vbo);

        m_Ibo = IndexBuffer::Create(&indices[0], (uint32_t)indices.size());
        m_Vao->SetIndexBuffer(m_Ibo);

        
        std::string defaultVertexShader = "Resources/shaders/default/mesh/mesh_vertex.glsl";
        std::string defaultFragmentShader = "Resources/shaders/default/mesh/mesh_fragment.glsl";
        
        bool skip = false;
        for(auto& shader : Renderer::GetLoadedShaders())
        {
            if(std::strcmp(shader->m_FilePaths.first.data(), defaultVertexShader.c_str()) == 0 && std::strcmp(shader->m_FilePaths.second.data(), defaultFragmentShader.c_str()) == 0)
            {
                //The shaders already been loaded, dont load it again
                m_Material = Material::Create(shader);
                skip = true;
                break;
            }
        }
        if(!skip)
        {
            m_Material = Material::Create(defaultVertexShader, defaultFragmentShader);
            auto s = m_Material->GetShader();
            Renderer::RegisterShader(s);
        }
        
        //bind and set the textures inside the shader uniforms
        uint32_t diffuse = 1;
        uint32_t specular = 1;
        m_Material->BindShader();
        if(textures.empty())
        {
            textures.push_back(Renderer::GetMissingTexture());
            textures.push_back(Renderer::GetBlackTexture());
            m_Material->GetShader()->SetInt("u_Material.texture_diffuse1", Renderer::GetMissingTexture()->GetRendererID());
            m_Material->GetShader()->SetInt("u_Material.texture_specular1", Renderer::GetBlackTexture()->GetRendererID());
            m_Material->SetTextures(textures);
        }
        else
        {
            m_Material->SetTextures(textures);
            bool dif = false;
            bool spec = false;
            for(auto t : textures)
            {
                std::string number;
                std::string name = t->m_TextureResource.CustomName;
                if(name == "texture_diffuse")
                {
                    number = std::to_string(diffuse++);
                    dif = true;
                    //m_Material->GetShader()->SetBool("u_Material.diffuse_bound", true);
                }
                else if(name == "texture_specular")
                {
                    number = std::to_string(specular++);
                    spec = true;
                    //m_Material->GetShader()->SetBool("u_Material.specular_bound", true);
                }
                else
                {
                    m_Material->GetShader()->SetInt("u_Material.texture_diffuse1", Renderer::GetMissingTexture()->GetRendererID());
                    m_Material->GetShader()->SetInt("u_Material.texture_specular1", Renderer::GetBlackTexture()->GetRendererID());
                }

                if(dif && !spec)
                {
                    m_Material->GetShader()->SetInt("u_Material.texture_specular1", Renderer::GetBlackTexture()->GetRendererID());
                }
                
                m_Material->GetShader()->SetInt(("u_Material." + name + number ).c_str(), t->GetRendererID());
            }
        }
        m_Material->UnBindShader();
    }

    std::vector<glm::vec3> Mesh::GetVertexPositions() const
    {
        std::vector<glm::vec3> positions;
        
        for(auto& p : m_Vertices)
        {
            positions.push_back(p.Position);
        }

        return positions;
    }


    static const uint32_t s_MeshImportFlags =
            aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
            aiProcess_Triangulate |             // Make sure we're triangles
            aiProcess_SortByPType |             // Split meshes by primitive type
            aiProcess_GenNormals |              // Make sure we have legit normals
            aiProcess_GenUVCoords |             // Convert UVs if required 
            aiProcess_OptimizeMeshes |          // Batch draws where possible
            aiProcess_JoinIdenticalVertices |          
            aiProcess_ValidateDataStructure;  // Validation

    glm::mat4 Model::AiToGLM(aiMatrix4x4t<float> m)
    {
        return glm::mat4{ m.a1, m.b1, m.c1, m.d1,
                m.a2, m.b2, m.c2, m.d2,
                m.a3, m.b3, m.c3, m.d3,
                m.a4, m.b4, m.c4, m.d4 };
    }
    

    glm::vec3 Model::AiToGLM(aiVector3t<float> v)
    {
        return glm::vec3{ v.x, v.y, v.z };
    }

    glm::quat Model::AiToGLM(aiQuaterniont<float> q)
    {
        return glm::quat{ q.w, q.x, q.y, q.z };
    }


    Ref<Model> Model::Create(const std::string& filePath)
    {
        auto model = Ref<Model>::Create();
        bool duplicate = false;
        for(auto& m : Renderer::GetLoadedModels())
        {
            if(std::strcmp(m->m_Resource.RelativeDirectory.c_str(), filePath.c_str()) == 0)
            {
                // this model has already been loaded, no need to process it again
                model = m;
                duplicate = true;
            }
        }

        if(duplicate) return model;

        //if theres no duplicate model, read in the file as normal and return the new model
        model = Ref<Model>::Create(filePath);
        Renderer::RegisterModel(model);
        return model;
    }

    Model::Model()
        :m_Animation(Animation())
    {}

    Model::Model(const std::string& filePath)
    {
        m_Resource = Resource(filePath);
        LoadModel(filePath);
    }

    void Model::SetVertexBoneDataToDefault(Vertex& vertex) 
    {
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++) 
        {
            vertex.IDs[i] = 0;
            vertex.Weights[i] = 0.0f;
        }
    }


    void Model::SetVertexBoneData(Vertex& vertex, int boneID, float weight) 
    {
        for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) 
        {
            vertex.Weights[i] = weight;
            vertex.IDs[i] = boneID;
            
        }
    }

    void Model::ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene) 
    {
        for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) 
        {
            int boneID = -1;
            std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

            if (m_BoneInfoMap.find(boneName) == m_BoneInfoMap.end()) 
            {
                BoneInfo newBoneInfo;
                newBoneInfo.id = m_BoneCounter;
                newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
                m_BoneInfoMap[boneName] = newBoneInfo;
                boneID = m_BoneCounter;
                m_BoneCounter++;
            }
            else 
            {
                boneID = m_BoneInfoMap[boneName].id;
            }
            assert(boneID != -1);
            auto weights = mesh->mBones[boneIndex]->mWeights;
            int numWeights = mesh->mBones[boneIndex]->mNumWeights;

            for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) 
            {
                int vertexId = weights[weightIndex].mVertexId;
                float weight = weights[weightIndex].mWeight;
                assert(vertexId <= vertices.size());
                SetVertexBoneData(vertices[vertexId], boneID, weight);

            }
        }

    }

    void Model::LoadModel(const std::string& filePath)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filePath, s_MeshImportFlags);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            TNAH_CORE_ERROR("Error Importing file: {0}    error: {1}", filePath, importer.GetErrorString());
            return;
        }
        ProcessNode(scene->mRootNode, scene);
    }

    std::vector<Ref<Texture2D>> Model::LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName)
    {
        std::vector<Ref<Texture2D>> textures;
        for(uint32_t i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->Get(AI_MATKEY_TEXTURE(type, 0), str);
            bool skip = false;

            for(uint32_t j = 0; j < Renderer::GetLoadedTextures().size(); j++)
            {
                if(std::strcmp(Renderer::GetLoadedTextures()[j]->m_TextureResource.RelativeDirectory.data(), str.C_Str()) == 0)
                {
                    textures.push_back(Renderer::GetLoadedTextures()[j]);
                    skip = true;
                    break;
                }
            }
            if(!skip)
            {
                Ref<Texture2D> tex;
                
                if(auto t = scene->GetEmbeddedTexture(str.C_Str()))
                {
                    aiTexture* aiTex = const_cast<aiTexture*>(t);
                    //read file from memory
                    tex = (Texture2D::Create(str.C_Str(), typeName + std::to_string(i+1),true, aiTex));
                    textures.push_back(tex);
                    //m_LoadedTextures.push_back(MeshTexture(tex, str.data));
                    Renderer::RegisterTexture(tex);
                }
                else
                {
                    tex = (Texture2D::Create(str.data, typeName + std::to_string(i+1)));
                    textures.push_back(tex);
                    //m_LoadedTextures.push_back(MeshTexture(tex, str.data));
                    Renderer::RegisterTexture(tex);
                }
            }
            
           
        }
        return textures;
    }

    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, bool animated)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture2D>> textures;

        for(uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex v;

            if(animated)
            {
                SetVertexBoneDataToDefault(v);
            }
            else
            {
                // if the mesh isnt animated, set the id's and weights to 0
                for(uint32_t j = 0; j < 4; j++)
                {
                    v.IDs[j] = 0;
                    v.Weights[j] = 0;
                }
            }

            v.Position = AssimpGLMHelpers::GetGLMVec(mesh->mVertices[i]);
            v.Normal = AssimpGLMHelpers::GetGLMVec(mesh->mNormals[i]);


            glm::vec3 vec;
            if(mesh->HasPositions())
            {
                vec.x = mesh->mVertices[i].x;
                vec.y = mesh->mVertices[i].y;
                vec.z = mesh->mVertices[i].z;
                v.Position = vec;
            }

            if(mesh->HasNormals())
            {
                vec.x = mesh->mNormals[i].x;
                vec.y = mesh->mNormals[i].y;
                vec.z = mesh->mNormals[i].z;
                v.Normal = vec;
            }

            if(mesh->HasTangentsAndBitangents())
            {
                vec.x = mesh->mTangents[i].x;
                vec.y = mesh->mTangents[i].y;
                vec.z = mesh->mTangents[i].z;
                v.Tangent = vec;
                vec.x = mesh->mBitangents[i].x;
                vec.y = mesh->mBitangents[i].y;
                vec.z = mesh->mBitangents[i].z;
                v.Bitangents = vec;
            }
            
            
            if(mesh->mTextureCoords[0])
            {
                glm::vec2 tex;
                tex.x = mesh->mTextureCoords[0][i].x;
                tex.y = mesh->mTextureCoords[0][i].y;
                v.Texcoord = tex;
            }
            else
            {
                v.Texcoord = glm::vec2(0.0f);
            }
            vertices.push_back(v);
        }

        for(uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(uint32_t j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }


        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // 1. diffuse maps
        std::vector<Ref<Texture2D>> diffuseMaps = LoadMaterialTextures(scene, material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        /// 2. specular maps
            std::vector<Ref<Texture2D>> specularMaps = LoadMaterialTextures(scene, material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        /// 3. normal maps
        std::vector<Ref<Texture2D>> normalMaps = LoadMaterialTextures(scene, material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        /// 4. height maps
        std::vector<Ref<Texture2D>> heightMaps = LoadMaterialTextures(scene, material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        

        if(animated) ExtractBoneWeightForVertices(vertices, mesh, scene);

        return Mesh(vertices, indices, textures, animated);
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene)
    {
        if(scene->mNumAnimations > 0)
        {
            m_IsAnimated = true;
            m_Animation = Animation(scene);
        }
        
        for(uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            if(m_IsAnimated)
                m_Meshes.push_back(ProcessMesh(mesh, scene, true));
            else
                m_Meshes.push_back(ProcessMesh(mesh, scene, false));
        }

        for(uint32_t i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }

        if(m_IsAnimated) m_Animation.ReadMissingBones(m_BoneInfoMap, m_BoneCounter);
    }
}
