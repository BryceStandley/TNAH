#pragma once
#include "TNAH/Core/Core.h"
#include <glm/glm.hpp>

#include "ComponentIdentification.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "TNAH/Renderer/Material.h"

namespace tnah {
	class Terrain
	{
	public:

		/**********************************************************************************************//**
		 * @fn	Terrain::Terrain() = default;
		 *
		 * @brief	Defaulted constructor, will construct a 100 square terrain with a min of 40 and a max of
		 * 			100 units.
		 *
		 * @author	Bryce Standley
		 * @date	23/07/2021
		 **************************************************************************************************/

		Terrain();

		/**********************************************************************************************//**
		 * @fn	Terrain::Terrain(const int width, const int maxHeight, const int minHeight);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	width	 	The width.
		 * @param 	maxHeight	The maximum height.
		 * @param 	minHeight	The minimum height.
		 **************************************************************************************************/

		Terrain(const int width, const int maxHeight, const int minHeight);

		/**********************************************************************************************//**
		 * @fn	Terrain::Terrain(const std::string& heightmapFilePath);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	heightmapFilePath	Full pathname of the heightmap file.
		 **************************************************************************************************/

		Terrain(const std::string& heightmapFilePath);

		/**********************************************************************************************//**
		 * @fn	Terrain::~Terrain();
		 *
		 * @brief	Destructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 **************************************************************************************************/

		~Terrain();

		/**********************************************************************************************//**
		 * @fn	inline const glm::vec3 Terrain::GetMaxHeight()
		 *
		 * @brief	Gets maximum height
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The maximum height.
		 **************************************************************************************************/

		inline const glm::vec3 GetMaxHeight() { return m_HighestPoint; }

		/**********************************************************************************************//**
		 * @fn	inline const glm::vec3 Terrain::GetMinHeight()
		 *
		 * @brief	Gets minimum height
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The minimum height.
		 **************************************************************************************************/

		inline const glm::vec3 GetMinHeight() { return m_LowestPoint; }

		/**********************************************************************************************//**
		 * @fn	inline const std::vector<glm::vec3> Terrain::GetVertexPositions()
		 *
		 * @brief	Gets vertex positions
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The vertex positions.
		 **************************************************************************************************/

		inline const std::vector<glm::vec3> GetVertexPositions() { return m_TerrainInfo.position; }

		/**********************************************************************************************//**
		 * @fn	inline float* Terrain::GetTotalData()
		 *
		 * @brief	Gets total data
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else the total data.
		 **************************************************************************************************/

		inline float* GetTotalData() { return &m_VBOData[0].x; }

		/**********************************************************************************************//**
		 * @fn	inline uint32_t* Terrain::GetIndicesData()
		 *
		 * @brief	Gets indices data
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else the indices data.
		 **************************************************************************************************/

		inline uint32_t* GetIndicesData() { return &m_IndicesData[0]; }

		/**********************************************************************************************//**
		 * @fn	inline const glm::vec2 Terrain::GetSize()
		 *
		 * @brief	Gets the size
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The size.
		 **************************************************************************************************/

		inline const glm::vec2 GetSize() { return m_Size; }

		/**********************************************************************************************//**
		 * @fn	inline const float Terrain::GetHeight(int x, int z);
		 *
		 * @brief	Gets a height
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	x	The x coordinate.
		 * @param 	z	The z coordinate.
		 *
		 * @returns	The height.
		 **************************************************************************************************/

		inline const float GetHeight(int x, int z);

		/**********************************************************************************************//**
		 * @fn	inline const float Terrain::GetHeightColor(int x, int z);
		 *
		 * @brief	Gets height color
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	x	The x coordinate.
		 * @param 	z	The z coordinate.
		 *
		 * @returns	The height color.
		 **************************************************************************************************/

		inline const float GetHeightColor(int x, int z);

		/**********************************************************************************************//**
		 * @fn	inline const float Terrain::GetVertexHeight(int x, int z);
		 *
		 * @brief	Gets vertex height
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	x	The x coordinate.
		 * @param 	z	The z coordinate.
		 *
		 * @returns	The vertex height.
		 **************************************************************************************************/

		inline const float GetVertexHeight(int x, int z);

		/**********************************************************************************************//**
		 * @fn	inline const uint32_t Terrain::GetTotalDataSize()
		 *
		 * @brief	Gets total data size
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The total data size.
		 **************************************************************************************************/

		inline const uint32_t GetTotalDataSize() { return m_VBOSize; }

		/**********************************************************************************************//**
		 * @fn	inline const uint32_t Terrain::GetIndicesSize()
		 *
		 * @brief	Gets indices size
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The indices size.
		 **************************************************************************************************/

		inline const uint32_t GetIndicesSize() { return m_IBOSize; }


		/**********************************************************************************************//**
		 * @fn	inline const BufferLayout Terrain::GetBufferLayout()
		 *
		 * @brief	Gets buffer layout
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The buffer layout.
		 **************************************************************************************************/

		inline const VertexBufferLayout GetBufferLayout() { return m_BufferLayout; }


		/**********************************************************************************************//**
		 * @fn	inline Ref<VertexArray> Terrain::GetVertexArray()
		 *
		 * @brief	Gets vertex array
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The vertex array.
		 **************************************************************************************************/

		inline Ref<VertexArray> GetVertexArray() { return m_VAO; }

		/**********************************************************************************************//**
		 * @fn	inline Ref<VertexBuffer> Terrain::GetVertexBuffer()
		 *
		 * @brief	Gets vertex buffer
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The vertex buffer.
		 **************************************************************************************************/

		inline Ref<VertexBuffer> GetVertexBuffer() { return m_VBO; }

		/**********************************************************************************************//**
		 * @fn	inline Ref<IndexBuffer> Terrain::GetIndexBuffer()
		 *
		 * @brief	Gets index buffer
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The index buffer.
		 **************************************************************************************************/

		inline Ref<IndexBuffer> GetIndexBuffer() { return m_IBO; }

		/**********************************************************************************************//**
		 * @fn	inline Ref<Material> Terrain::GetMaterial()
		 *
		 * @brief	Gets the material
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @returns	The material.
		 **************************************************************************************************/

		inline Ref<Material> GetMaterial() { return m_Material; }
		

		

	private:
		/**********************************************************************************************//**
		 * @struct	TerrainInformation
		 *
		 * @brief	Information used to construct the terrain with textures and colours
		 *
		 * @author	Bryce Standley
		 * @date	23/07/2021
		 **************************************************************************************************/

		struct TerrainInformation
		{
			/** @brief	The position */
			std::vector<glm::vec3> position;
			/** @brief	The color */
			std::vector<glm::vec3> color;
			/** @brief	The texture */
			std::vector<glm::vec3> texture;
			/** @brief	The normal */
			std::vector<glm::vec3> normal;
		};

		/**********************************************************************************************//**
		 * @fn	void Terrain::Create();
		 *
		 * @brief	Creates this object
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 **************************************************************************************************/

		void Create();

		/**********************************************************************************************//**
		 * @fn	void Terrain::GenerateHeightmap(const int width, const int maxHeight, const int minHeight);
		 *
		 * @brief	Generates a heightmap
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	width	 	The width.
		 * @param 	maxHeight	The maximum height.
		 * @param 	minHeight	The minimum height.
		 **************************************************************************************************/

		void GenerateHeightmap(const int width, const int maxHeight, const int minHeight);

		/**********************************************************************************************//**
		 * @fn	bool Terrain::LoadHeightField(const std::string& fileName);
		 *
		 * @brief	Loads height field
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	fileName	Filename of the file.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadHeightField(const std::string& fileName);

		/**********************************************************************************************//**
		 * @fn	bool Terrain::InBounds(int x, int z);
		 *
		 * @brief	In bounds
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	x	The x coordinate.
		 * @param 	z	The z coordinate.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool InBounds(int x, int z);

		/**********************************************************************************************//**
		 * @fn	void Terrain::SetVertexHeight(int x, int z, const float newHeight);
		 *
		 * @brief	Sets vertex height
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	x		 	The x coordinate.
		 * @param 	z		 	The z coordinate.
		 * @param 	newHeight	Height of the new.
		 **************************************************************************************************/

		void SetVertexHeight(int x, int z, const float newHeight);

		/**********************************************************************************************//**
		 * @fn	void Terrain::GenerateVertexPositions(TerrainInformation& terrainInformation);
		 *
		 * @brief	Generates a vertex positions
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	terrainInformation	Information describing the terrain.
		 **************************************************************************************************/

		void GenerateVertexPositions(TerrainInformation& terrainInformation);

		/**********************************************************************************************//**
		 * @fn	void Terrain::GenerateVertexIndices();
		 *
		 * @brief	Generates a vertex indices
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 **************************************************************************************************/

		void GenerateVertexIndices();

		/**********************************************************************************************//**
		 * @fn	void Terrain::GenerateVertexColors(TerrainInformation& terrainInformaion);
		 *
		 * @brief	Generates a vertex colors
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	terrainInformaion	The terrain informaion.
		 **************************************************************************************************/

		void GenerateVertexColors(TerrainInformation& terrainInformaion);

		/**********************************************************************************************//**
		 * @fn	void Terrain::GenerateVertexTextureCoords(TerrainInformation& terrainInformation);
		 *
		 * @brief	Generates a vertex texture coordinates
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	terrainInformation	Information describing the terrain.
		 **************************************************************************************************/

		void GenerateVertexTextureCoords(TerrainInformation& terrainInformation);

		/**********************************************************************************************//**
		 * @fn	void Terrain::GenerateVertexNormals(TerrainInformation& terrainInformation);
		 *
		 * @brief	Generates a vertex normals
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	terrainInformation	Information describing the terrain.
		 **************************************************************************************************/

		void GenerateVertexNormals(TerrainInformation& terrainInformation);

		/**********************************************************************************************//**
		 * @fn	void Terrain::SmoothTerrain(TerrainInformation& terrainInformation);
		 *
		 * @brief	Smooth terrain
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param [in,out]	terrainInformation	Information describing the terrain.
		 **************************************************************************************************/

		void SmoothTerrain(TerrainInformation& terrainInformation);


	private:
		/** @brief	Full pathname of the heightmap file */
		std::string m_HeightmapPath = "";
		
		/** @brief	The minimum heightmap height */
		float m_MinHeightmapHeight = 40.0f;
		/** @brief	The maximum heightmap height */
		float m_MaxHeightmapHeight = 100.0f;

		/** @brief	The size */
		glm::vec2 m_Size = glm::vec2(0.0f);
		/** @brief	List of heights of the terrains */
		std::vector<float> m_TerrainHeights;
		/** @brief	The minimum height */
		float m_MinHeight = 0.0f;
		/** @brief	The maximum height */
		float m_MaxHeight = 0.0f;
		/** @brief	Information describing the terrain */
		TerrainInformation m_TerrainInfo;

		/** @brief	Terrain information combined into a single vector for use in the vertex buffer*/
		std::vector<glm::vec3> m_VBOData;
		/** @brief	Information describing the indices */
		std::vector<uint32_t> m_IndicesData;
		/** @brief	Size of the vbo */
		uint32_t m_VBOSize;
		/** @brief	Size of the ibo */
		uint32_t m_IBOSize;
		/** @brief	The buffer layout */
		VertexBufferLayout m_BufferLayout;
		/** @brief	The vao */
		

		Ref<VertexArray> m_VAO;
		/** @brief	The vbo */
		Ref<VertexBuffer> m_VBO;
		/** @brief	The ibo */
		Ref<IndexBuffer> m_IBO;
		/** @brief	The material */
		Ref<Material> m_Material;
		/** @brief	List of names of the texture files */
		std::vector<std::string> m_TextureFileNames;


		/** @brief	The highest point */
		glm::vec3 m_HighestPoint = glm::vec3(0.0f);
		/** @brief	The lowest point */
		glm::vec3 m_LowestPoint = glm::vec3(0.0f);

		/**********************************************************************************************//**
		 * @class	EditorUI
		 *
		 * @brief	An editor user interface.
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 **************************************************************************************************/

		friend class EditorUI;
		friend class Serializer;
	};

	/**********************************************************************************************//**
	 * @class	TerrainComponent
	 *
	 * @brief	A terrain component.
	 *
	 * @author	Bryce Standley
	 * @date	10/09/2021
	 **************************************************************************************************/

	class TerrainComponent
	{
	public:
		/** @brief	The scene terrain */
		Terrain* SceneTerrain;

		

		/**********************************************************************************************//**
		 * @fn	TerrainComponent::TerrainComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 **************************************************************************************************/

		TerrainComponent() = default;

		/**********************************************************************************************//**
		 * @fn	TerrainComponent::TerrainComponent(const TerrainComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		TerrainComponent(const TerrainComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	TerrainComponent::TerrainComponent(const std::string& heightMapFilePath)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	heightMapFilePath	Full pathname of the height map file.
		 **************************************************************************************************/

		TerrainComponent(const std::string& heightMapFilePath)
		{
			SceneTerrain = new Terrain(heightMapFilePath);
		}

		/**********************************************************************************************//**
		 * @fn	TerrainComponent::TerrainComponent(const int width, const int maxHeight, const int minHeight)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	width	 	The width.
		 * @param 	maxHeight	The maximum height.
		 * @param 	minHeight	The minimum height.
		 **************************************************************************************************/

		TerrainComponent(const int width, const int maxHeight, const int minHeight)
		{
			SceneTerrain = new Terrain(width, maxHeight, minHeight);
		}

	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "terrain component";
		inline static ComponentTypes s_Types = {
			{ComponentVariations::Terrain},
{{ComponentCategory::Objects, ComponentCategory::Environment, ComponentCategory::Objects}}
		};
	};

}