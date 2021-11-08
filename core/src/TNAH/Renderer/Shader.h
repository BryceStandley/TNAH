#pragma once

#include <string>
#include <glm/glm.hpp>

#include "TNAH/Core/Ref.h"


namespace tnah {

	/**
	 * @enum	ShaderUniformType
	 *
	 * @brief	Values that represent shader uniform types
	 */

	enum class ShaderUniformType
	{
		None = 0, Bool, Int, UInt, Float, Vec2, Vec3, Vec4, Mat3, Mat4,
		IVec2, IVec3, IVec4
	};

	/**
	 * @class	ShaderUniform
	 *
	 * @brief	Form for viewing the shader uniform.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class ShaderUniform
	{
	public:

		/**
		 * @fn	ShaderUniform::ShaderUniform() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		ShaderUniform() = default;

		/**
		 * @fn	ShaderUniform::ShaderUniform(std::string name, ShaderUniformType type, uint32_t size, uint32_t offset);
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name  	The name.
		 * @param 	type  	The type.
		 * @param 	size  	The size.
		 * @param 	offset	The offset.
		 */

		ShaderUniform(std::string name, ShaderUniformType type, uint32_t size, uint32_t offset);

		/**
		 * @fn	const std::string& ShaderUniform::GetName() const
		 *
		 * @brief	Gets the name
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The name.
		 */

		const std::string& GetName() const { return m_Name; }

		/**
		 * @fn	ShaderUniformType ShaderUniform::GetType() const
		 *
		 * @brief	Gets the type
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The type.
		 */

		ShaderUniformType GetType() const { return m_Type; }

		/**
		 * @fn	uint32_t ShaderUniform::GetSize() const
		 *
		 * @brief	Gets the size
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The size.
		 */

		uint32_t GetSize() const { return m_Size; }

		/**
		 * @fn	uint32_t ShaderUniform::GetOffset() const
		 *
		 * @brief	Gets the offset
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The offset.
		 */

		uint32_t GetOffset() const { return m_Offset; }

		/**
		 * @fn	static const std::string& ShaderUniform::UniformTypeToString(ShaderUniformType type);
		 *
		 * @brief	Uniform type to string
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	type	The type.
		 *
		 * @returns	A reference to a const std::string.
		 */

		static const std::string& UniformTypeToString(ShaderUniformType type);
	private:

		/** @brief	The name */
		std::string m_Name;

		/** @brief	The type */
		ShaderUniformType m_Type = ShaderUniformType::None;

		/** @brief	The size */
		uint32_t m_Size = 0;

		/** @brief	The offset */
		uint32_t m_Offset = 0;
	};

	/**
	 * @enum	ShaderDomain
	 *
	 * @brief	Values that represent shader domains
	 */

	enum class ShaderDomain
	{
		None = 0, Vertex = 0, Pixel = 1 // unused
	};

	/**
	 * @class	ShaderResourceDeclaration
	 *
	 * @brief	A shader resource declaration class.
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class ShaderResourceDeclaration
	{
	public:

		/**
		 * @fn	ShaderResourceDeclaration::ShaderResourceDeclaration() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		ShaderResourceDeclaration() = default;

		/**
		 * @fn	ShaderResourceDeclaration::ShaderResourceDeclaration(const std::string& name, uint32_t resourceRegister, uint32_t count)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name				The name.
		 * @param 	resourceRegister	The resource register.
		 * @param 	count				Number of.
		 */

		ShaderResourceDeclaration(const std::string& name, uint32_t resourceRegister, uint32_t count)
			: m_Name(name), m_Register(resourceRegister), m_Count(count) {}

		/**
		 * @fn	virtual ShaderResourceDeclaration::~ShaderResourceDeclaration();
		 *
		 * @brief	Destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~ShaderResourceDeclaration();

		/**
		 * @fn	virtual const std::string& ShaderResourceDeclaration::GetName() const
		 *
		 * @brief	Gets the name
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The name.
		 */

		virtual const std::string& GetName() const { return m_Name; }

		/**
		 * @fn	virtual uint32_t ShaderResourceDeclaration::GetRegister() const
		 *
		 * @brief	Gets the register
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The register.
		 */

		virtual uint32_t GetRegister() const { return m_Register; }

		/**
		 * @fn	virtual uint32_t ShaderResourceDeclaration::GetCount() const
		 *
		 * @brief	Gets the count
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The count.
		 */

		virtual uint32_t GetCount() const { return m_Count; }
	private:

		/** @brief	The name */
		std::string m_Name;

		/** @brief	The register */
		uint32_t m_Register = 0;

		/** @brief	The count */
		uint32_t m_Count = 0;
	};

	/**
	 * @typedef	std::vector<ShaderResourceDeclaration*> ShaderResourceList
	 *
	 * @brief	Defines a vector of shader resources
	 */

	typedef std::vector<ShaderResourceDeclaration*> ShaderResourceList;

	/**
	 * @class	Shader
	 *
	 * @brief	A shader class which is used to access shaders
	 *
	 * @author	Bryce Standley
	 * @date	12/09/2021
	 */

	class Shader : public RefCounted
	{
	public:

		/**
		 * @fn	virtual Shader::~Shader() = default;
		 *
		 * @brief	Defaulted destructor
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual ~Shader() = default;

		/**
		 * @fn	virtual void Shader::Bind() = 0;
		 *
		 * @brief	Binds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Bind() = 0;

		/**
		 * @fn	virtual void Shader::Unbind() = 0;
		 *
		 * @brief	Unbinds this object
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 */

		virtual void Unbind() = 0;

		/**
		 * @fn	virtual bool Shader::IsBound() const = 0;
		 *
		 * @brief	Query if this object is bound
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	True if bound, false if not.
		 */

		virtual bool IsBound() const = 0;

		/**
		 * @fn	virtual void Shader::SetBool(const std::string& name, bool value) = 0;
		 *
		 * @brief	Sets a bool
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	True to value.
		 */

		virtual void SetBool(const std::string& name, bool value) = 0;

		/**
		 * @fn	virtual void Shader::SetInt(const std::string& name, int value) = 0;
		 *
		 * @brief	Sets an int
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	The value.
		 */

		virtual void SetInt(const std::string& name, int value) = 0;	

		/**
		 * @fn	virtual void Shader::SetFloat(const std::string& name, float value) = 0;
		 *
		 * @brief	Sets a float
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	The value.
		 */

		virtual void SetFloat(const std::string& name, float value) = 0;

		/**
		 * @fn	virtual void Shader::SetVec2(const std::string& name, const glm::vec2& value) = 0;
		 *
		 * @brief	Sets vector 2
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	The value.
		 */

		virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;

		/**
		 * @fn	virtual void Shader::SetVec3(const std::string& name, const glm::vec3& value) = 0;
		 *
		 * @brief	Sets vector 3
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	The value.
		 */

		virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;

		/**
		 * @fn	virtual void Shader::SetVec4(const std::string& name, const glm::vec4& value) = 0;
		 *
		 * @brief	Sets vector 4
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	The value.
		 */

		virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;

		/**
		 * @fn	virtual void Shader::SetMat3(const std::string& name, const glm::mat3& value) = 0;
		 *
		 * @brief	Sets matrix 3
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	The value.
		 */

		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;

		/**
		 * @fn	virtual void Shader::SetMat4(const std::string& name, const glm::mat4& value) = 0;
		 *
		 * @brief	Sets matrix 4
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	name 	The name.
		 * @param 	value	The value.
		 */

		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		/**
		 * @fn	virtual const std::string& Shader::GetName() const = 0;
		 *
		 * @brief	Gets the name
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @returns	The name.
		 */

		virtual const std::string& GetName() const = 0;

		/**
		 * @fn	static Ref<Shader> Shader::Create(const std::string& filePath);
		 *
		 * @brief	Creates a new Shader
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	filePath	Full pathname of the file.
		 *
		 * @returns	A pointer to a shader
		 */

		static Ref<Shader> Create(const std::string& filePath);

		/**
		 * @fn	static Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		 *
		 * @brief	Creates a new Shader
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexSrc  	The vertex source.
		 * @param 	fragmentSrc	The fragment source.
		 *
		 * @returns	A pointer to a shader
		 */

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		/**
		 * @fn	static Ref<Shader> Shader::CheckShaderExists(const std::string& filePath);
		 *
		 * @brief	Queries if a given shader exists
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	filePath	Full pathname of the file.
		 *
		 * @returns	A Ref&lt;Shader&gt;
		 */

		static Ref<Shader> CheckShaderExists(const std::string& filePath);

		/**
		 * @fn	static Ref<Shader> Shader::CheckShaderExists(const std::string& vertexSrc, const std::string& fragmentSrc);
		 *
		 * @brief	Queries if a given shaders exist
		 *
		 * @author	Bryce Standley
		 * @date	12/09/2021
		 *
		 * @param 	vertexSrc  	The vertex source.
		 * @param 	fragmentSrc	The fragment source.
		 *
		 * @returns	A Ref&lt;Shader&gt;
		 */

		static Ref<Shader> CheckShaderExists(const std::string& vertexSrc, const std::string& fragmentSrc);

		/** @brief	The file paths */
		std::pair<std::string, std::string> m_FilePaths;

		/** @brief	Name of the shader */
		std::string m_ShaderName;
		friend class EditorUI;
	};



}

