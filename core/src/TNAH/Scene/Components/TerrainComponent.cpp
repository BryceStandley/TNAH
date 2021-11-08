#include "tnahpch.h"
#include "TerrainComponent.h"

#include <glm/gtc/type_ptr.hpp>

#include "TNAH/Renderer/Renderer.h"

namespace tnah {

	Terrain::Terrain()
	{
		GenerateHeightmap(100, 100, 40);
		Create();
		m_BufferLayout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Color"},
			{ShaderDataType::Float3, "a_TexCoord"},
			{ShaderDataType::Float3, "a_Normal"}
		};
		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(GetTotalData(), GetTotalDataSize());
		m_VBO->SetLayout(m_BufferLayout);
		m_VAO->AddVertexBuffer(m_VBO);

		m_IBO= IndexBuffer::Create(GetIndicesData(), GetIndicesSize());
		m_VAO->SetIndexBuffer(m_IBO);

		m_Material = Material::Create("Resources/shaders/default/terrain/terrain_vertex.glsl", "Resources/shaders/default/terrain/terrain_fragment.glsl");
	}

	Terrain::Terrain(const std::string& heightmapFilePath)
	{
		if (LoadHeightField(heightmapFilePath))
		{
			Create();
			m_BufferLayout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float3, "a_Color"},
				{ShaderDataType::Float3, "a_TexCoord"},
				{ShaderDataType::Float3, "a_Normal"}
			};
			m_VAO = VertexArray::Create();
			m_VBO = VertexBuffer::Create(GetTotalData(), GetTotalDataSize());
			m_VBO->SetLayout(m_BufferLayout);
			m_VAO->AddVertexBuffer(m_VBO);

			m_IBO= IndexBuffer::Create(GetIndicesData(), GetIndicesSize());
			m_VAO->SetIndexBuffer(m_IBO);

			m_Material = Material::Create("Resources/shaders/default/terrain/terrain_vertex.glsl", "Resources/shaders/default/terrain/terrain_fragment.glsl");

			m_TextureFileNames.emplace_back("dirt");
			m_TextureFileNames.emplace_back("grass");
			m_TextureFileNames.emplace_back("rock");
			m_TextureFileNames.emplace_back("snow");

			std::vector<Ref<Texture2D>> textures;
			m_Material->BindShader();
			for(int i = 0; i < (int)m_TextureFileNames.size(); i++)
			{
				Ref<Texture2D> texture = Texture2D::Create("assets/textures/terrain/" + m_TextureFileNames[i] + ".jpg");
				textures.emplace_back(texture);
				m_Material->GetShader()->SetInt("u_" + m_TextureFileNames[i] + "Texture", texture->m_Slot);
			}
			m_Material->SetTextures(textures);
			m_Material->GetShader()->SetInt("u_Material.texture_specular1", Renderer::GetBlackTexture()->m_Slot);
			m_Material->UnBindShader();
		}
	}

	Terrain::Terrain(const int width, const int maxHeight, const int minHeight)
	{
		GenerateHeightmap(width, maxHeight, minHeight);
		Create();
		m_BufferLayout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Color"},
			{ShaderDataType::Float3, "a_TexCoord"},
			{ShaderDataType::Float3, "a_Normal"}
		};
		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(GetTotalData(), GetTotalDataSize());
		m_VBO->SetLayout(m_BufferLayout);
		m_VAO->AddVertexBuffer(m_VBO);

		m_IBO= IndexBuffer::Create(GetIndicesData(), GetIndicesSize());
		m_VAO->SetIndexBuffer(m_IBO);

		m_Material = Material::Create("Resources/shaders/default/terrain/terrain_vertex.glsl", "Resources/shaders/default/terrain/terrain_fragment.glsl");
	}

	Terrain::~Terrain()
	{
		TNAH_CORE_ERROR("Terrain deconstructor called");
	}

	void Terrain::Create()
	{
		GenerateVertexPositions(m_TerrainInfo);
		SmoothTerrain(m_TerrainInfo);
		GenerateVertexColors(m_TerrainInfo);
		GenerateVertexTextureCoords(m_TerrainInfo);
		GenerateVertexNormals(m_TerrainInfo);
		GenerateVertexIndices();

		int size = (int)m_TerrainInfo.position.size();
		for (int i = 0; i < (int)m_TerrainInfo.position.size(); i++)
		{
			m_VBOData.emplace_back(m_TerrainInfo.position[i]);

			m_VBOData.emplace_back(m_TerrainInfo.color[i]);

			m_VBOData.emplace_back(m_TerrainInfo.texture[i]);

			m_VBOData.emplace_back(-m_TerrainInfo.normal[i]);
		}

		//m_VBOSize = sizeof(glm::vec3) * (m_Size.x * m_Size.y);
		m_VBOSize = (uint32_t)(sizeof(glm::vec3) * m_VBOData.size());
	}

	void Terrain::GenerateHeightmap(const int width, const int maxHeight, const int minHeight)
	{
		//TODO: Add some math here to generate a height map using noise
		// use nested for loop of x and z using m_Size.x as a limit
		// push the height value into m_TerrainHeights[z * m_Size.x + x]
	}

	bool Terrain::LoadHeightField(const std::string& fileName)
	{
		auto texture = Texture2D::LoadImageToMemory(fileName);
		if(!texture)
		{
			TNAH_CORE_ERROR("Terrain Component couldn't load heightmap at path: {0}", fileName.c_str());
			return false;
		}
		
		std::vector<float> result;
		auto pixelPtr = texture->GetImageData();
		for (uint32_t z = 0; z < texture->m_Height; ++z)
		{
			for (uint32_t x = 0; x < texture->m_Width; ++x)
			{
				result.emplace_back((float(*pixelPtr) / 255.0f) * m_MaxHeightmapHeight);
				pixelPtr += texture->m_Channels;
			}
		}

		m_TerrainHeights = result;
		m_Size.x = (float)texture->m_Width;
		m_Size.y = (float)texture->m_Height;
		texture->Free();
		return true;
		
	}

	const float Terrain::GetHeight(int x, int z)
	{
		if (x < 0) { x = 0; }
		if (z < 0) { z = 0; }
		if (x > m_Size.x) { x = (int)m_Size.x; }
		if (z > m_Size.x) { z = (int)m_Size.x; }
		if (InBounds(x, z))
		{
			int val = z * (int)m_Size.x + x;
			return m_TerrainHeights[val];
		}
		else
		{
			int val = ((z - 1) * (int)m_Size.x) + x;
			return m_TerrainHeights[val];
		}
	}

	const float Terrain::GetHeightColor(int x, int z)
	{
		if (InBounds(x, z)) {
			int val = (z * (int)m_Size.x) + x;
			return m_TerrainHeights[val];
		}
		return 1;
	}

	const float Terrain::GetVertexHeight(int x, int z)
	{
		if (x < 0) { x = 0; }
		if (z < 0) { z = 0; }
		if (x >= m_Size.x) { x = (int)m_Size.x - 1; }
		if (z >= m_Size.x) { z = (int)m_Size.x - 1; }
		if (InBounds(x, z))
		{
			int val = z * (int)m_Size.x + x;
			return m_TerrainInfo.position[val].y;
		}
		else
		{
			int val = ((z - 1) * (int)m_Size.x) + x;
			return m_TerrainInfo.position[val].y;
		}
	}

	bool Terrain::InBounds(int x, int z)
	{
		if ((x >= 0 && (float)x < m_Size.x) && (z >= 0 && (float)z < m_Size.x))
			return true;
		else
			return false;
	}

	void Terrain::SetVertexHeight(int x, int z, const float newHeight)
	{
		if (InBounds(x, z))
		{
			int val = (z * (int)m_Size.x) + x;
			m_TerrainInfo.position[val].y = newHeight;
		}
		else
		{
			int val = (z - 1 * (int)m_Size.x) + x;
			m_TerrainInfo.position[val].y = newHeight;
		}
	}

	void Terrain::GenerateVertexPositions(TerrainInformation& terrainInformation)
	{
		for (int z = 0; z < m_Size.x; ++z)
		{
			for (int x = 0; x < m_Size.x; ++x)
			{
				glm::vec3 positions((float)x, GetHeight(x, z), (float)z);
				m_TerrainInfo.position.push_back(positions);
				if (positions.y > m_HighestPoint.y) { m_HighestPoint = glm::vec3(x, positions.y, z); }
				if (positions.y < m_LowestPoint.y) { m_LowestPoint = glm::vec3(x, positions.y, z); }
			}
		}
	}

	void Terrain::GenerateVertexIndices()
	{
		uint32_t size = (uint32_t)m_Size.x;

		for (unsigned int z = 0; z < size - 1; ++z)
		{
			for (unsigned int x = 0; x < size - 1; ++x)
			{
				m_IndicesData.push_back((x * size + z));             // 0
				m_IndicesData.push_back(((x * size + 1) + z));       // 1
				m_IndicesData.push_back((((x + 1) * size) + z));     // 3

				m_IndicesData.push_back(((x * size + 1) + z));       // 1
				m_IndicesData.push_back(((x + 1) * size) + (z + 1)); // 2
				m_IndicesData.push_back((((x + 1) * size) + z));     // 3
			}
		}

		m_IBOSize = (uint32_t)m_IndicesData.size();

	}

	void Terrain::GenerateVertexColors(TerrainInformation& terrainInformaion)
	{
		float colorVal = 0.0f;

		for (int z = 0; z < m_Size.x; ++z)
		{
			for (int x = 0; x < m_Size.x; ++x)
			{
				colorVal = GetVertexHeight(x, z) / 255.0f;
				glm::vec3 color(0.0f, colorVal, 0.0f);
				m_TerrainInfo.color.emplace_back(color);
			}
		}
	}

	void Terrain::GenerateVertexTextureCoords(TerrainInformation& terrainInformation)
	{
		unsigned int tracker = 0;
		float prevx = m_TerrainInfo.position[0].x;
		int s = 1;
		int x = 0;
		int z = 0;
		glm::vec3 texCoords = glm::vec3(0.0f);
		for (auto& vert : m_TerrainInfo.position)
		{
			if (static_cast<int>(prevx) != static_cast<int>(vert.x))
			{
				x++;
				z = 0;
				prevx = vert.x;
			}
			if (tracker == 0)
			{
				texCoords.x = static_cast<float>(x) / static_cast<float>(s);
				texCoords.y = static_cast<float>(z) / static_cast<float>(s);
				tracker++;
			}
			else
			{
				texCoords.x = static_cast<float>(x) / static_cast<float>(s);
				texCoords.y = static_cast<float>(z) / static_cast<float>(s);
				tracker = 0;
			}
			z++;
			m_TerrainInfo.texture.emplace_back(texCoords);
		}
	}

	void Terrain::GenerateVertexNormals(TerrainInformation& terrainInformation)
	{
		for (uint32_t z = 0; z < m_Size.x; ++z)
		{
			for (uint32_t x = 0; x < m_Size.x; ++x)
			{
				const glm::vec3& west = m_TerrainInfo.position[(x > 0 ? x - 1 : 0) + z * (uint32_t)m_Size.x];
				const glm::vec3& east = m_TerrainInfo.position[(x < (uint32_t)m_Size.x - 1 ? x + 1 : x) + z * (uint32_t)m_Size.x];

				glm::vec3 slope_x = east - west;

				const glm::vec3& south = m_TerrainInfo.position[x + (z > 0 ? z - 1 : 0) * (uint32_t)m_Size.x];
				const glm::vec3& north = m_TerrainInfo.position[x + (z < (uint32_t)m_Size.x - 1 ? z + 1 : z) * (uint32_t)m_Size.x];

				glm::vec3 slope_y = north - south;


				glm::vec3 normal = cross(slope_x, slope_y);
				glm::vec3 normalized = glm::normalize(normal);
				m_TerrainInfo.normal.push_back(normalized);
			}
		}
	}

	void Terrain::SmoothTerrain(TerrainInformation& terrainInformation)
	{
		for (int z = 0; z < m_Size.x; ++z)
		{
			for (int x = 0; x < m_Size.x; ++x)
			{
				float corners = (GetVertexHeight(x - 1, z - 1) +
					GetVertexHeight(x + 1, z - 1) +
					GetVertexHeight(x - 1, z + 1) +
					GetVertexHeight(x + 1, z + 1)) / 16.0f;

				float sides = (GetVertexHeight(x - 1, z) +
					GetVertexHeight(x + 1, z) +
					GetVertexHeight(x, z - 1) +
					GetVertexHeight(x, z + 1)) / 8.0f;

				float center = GetVertexHeight(x, z) / 4.0f;

				float newHeight = (corners + sides + center);

				if (newHeight > m_HighestPoint.y) { m_HighestPoint = glm::vec3(x, newHeight, z); }
				if (newHeight < m_LowestPoint.y) { m_LowestPoint = glm::vec3(x, newHeight, z); }

				SetVertexHeight(x, z, newHeight);
			}
		}
	}

}
