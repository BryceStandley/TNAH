#pragma once

#include "TNAH/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace tnah {

	class  OpenGLShader : public Shader
	{
	public:

		/**
		* @fn	OpenGLShader::OpenGLShader(const std::string& shaderFilePath);
		*
		* @brief	A constructor that takes in a path to the shader and generates it
		*
		* @author	Dylan Blereau
		* @date	7/09/2021
		*
		* @param 	shaderFilePath	- represents the path to the vertex shader.
		* 
		* case)
		*/

		OpenGLShader(const std::string& shaderFilePath);

		/**
		 * @fn	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		 *
		 * @brief	Constructor that takes in the paths for both the fragment and vertex shaders
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	vertexSrc  	The vertex source.
		 * @param 	fragmentSrc	The fragment source.
		 */

		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

		/**
		 * @fn	OpenGLShader::~OpenGLShader();
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		~OpenGLShader();

		/**
		 * @fn	void OpenGLShader::Bind() override;
		 *
		 * @brief	Allows you to activate and use the shader
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void Bind() override;

		/**
		 * @fn	void OpenGLShader::Unbind() override;
		 *
		 * @brief	Unbind the shader from the program.
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */
		
		void Unbind() override;

		/**
		 * @fn	bool OpenGLShader::IsBound() const override
		 *
		 * @brief	Queries if this object is bound
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if bound, false if not.
		 */

		bool IsBound() const override { return m_Bound; }

		/**
		 * @fn	virtual void OpenGLShader::SetBool(const std::string& name, bool value) override;
		 *
		 * @brief	Sets a boolean for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name 	- represents the name of the variable.
		 * @param 	value	- represents the variable value.
		 */

		virtual void SetBool(const std::string& name, bool value) override;

		/**
		 * @fn	virtual void OpenGLShader::SetInt(const std::string& name, int value) override;
		 *
		 * @brief	Sets an integer for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name 	- represents the name of the variable.
		 * @param 	value	- represents the variable value.
		 */

		virtual void SetInt(const std::string& name, int value) override;

		/**
		 * @fn	virtual void OpenGLShader::SetFloat(const std::string& name, float value) override;
		 *
		 * @brief	Sets a float for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name 	- represents the name of the variable.
		 * @param 	value	- represents the variable value.
		 */

		virtual void SetFloat(const std::string& name, float value) override;

		/**
		 * @fn	virtual void OpenGLShader::SetVec2(const std::string& name, const glm::vec2& value) override;
		 *
		 * @brief	Sets a vec2 for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name 	- represents the name of the variable.
		 * @param 	value	- represents the variable value.
		 */

		virtual void SetVec2(const std::string& name, const glm::vec2& value) override;

		/**
		 * @fn	virtual void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value) override;
		 *
		 * @brief	Sets a vec3 for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name 	- represents the name of the variable.
		 * @param 	value	- represents the variable value.
		 */

		virtual void SetVec3(const std::string& name, const glm::vec3& value) override;

		/**
		 * @fn	virtual void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value) override;
		 *
		 * @brief	Sets a vec4 for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name 	- represents the name of the variable.
		 * @param 	value	- represents the variable value.
		 */

		virtual void SetVec4(const std::string& name, const glm::vec4& value) override;

		/**
		 * @fn	virtual void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& mat) override;
		 *
		 * @brief	Sets a mat3 for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name	- represents the name of the variable.
		 * @param 	mat 	- represents the variable value.
		 */

		virtual void SetMat3(const std::string& name, const glm::mat3& mat) override;

		/**
		 * @fn	virtual void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& mat) override;
		 *
		 * @brief	Sets a mat4 for use in the shader program
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	name	- represents the name of the variable.
		 * @param 	mat 	- represents the variable value.
		 */

		virtual void SetMat4(const std::string& name, const glm::mat4& mat) override;

		/**
		 * @fn	inline virtual const std::string& OpenGLShader::GetName() const override
		 *
		 * @brief	Gets the name of the shader
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	The name of the shader.
		 */

		inline virtual const std::string& GetName() const override { return m_ShaderName; }
	private:

		/**
		 *
		 * @brief	Allows for the processing of vertex and fragment shaders within a singular file
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	source		  	Source code of the shader.
		 * @param 	shaderFilePath	Full pathname of the shader file.
		 *
		 * @returns	std::unordered_map<GLenum, std::pair<std::string, std::string>>
		 * 
		 */
		static std::unordered_map<GLenum, std::pair<std::string, std::string>> PreProcess(const std::string& source, const std::string& shaderFilePath);

		/**
		 * @fn	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::pair<std::string, std::string>>& shaderSources);
		 *
		 * @brief	Compiles the given shader sources
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	shaderSources	The shader sources.
		 */

		void Compile(const std::unordered_map<GLenum, std::pair<std::string, std::string>>& shaderSources);

		/**
		 * @fn	std::string OpenGLShader::ReadFile(const std::string& filepath);
		 *
		 * @brief	Reads a file from a given filepath
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	filepath	The filepath.
		 *
		 * @returns	The file.
		 */

		std::string ReadFile(const std::string& filepath);

		/**
		 * @fn	std::string OpenGLShader::PreProcessPaths(const std::string& shaderSorceFilePath);
		 *
		 * @brief	Applies pre-processing to the paths
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	shaderSorceFilePath	Full pathname of the shader source file.
		 *
		 * @returns	A std::string.
		 */

		std::string PreProcessPaths(const std::string& shaderSorceFilePath);


			/** @brief	Identifier for the shader */
		uint32_t m_ShaderID;
		
		
			/** @brief	True to bound */
		bool m_Bound = false;
	};

	

}
