#include "tnahpch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <unordered_map>
#include <fstream>
#include <glad/glad.h>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

#include "TNAH/Core/Timer.h"

namespace tnah {

	namespace Utils {

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			if (type == "fragment" || type == "pixel")
				return GL_FRAGMENT_SHADER;

			TNAH_CORE_ASSERT(false, "Unknown shader type!");
			return 0;
		}

	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrcPath, const std::string& fragmentSrcPath)
	{
		m_FilePaths.first = vertexSrcPath;
		m_FilePaths.second = fragmentSrcPath;
		std::unordered_map<GLenum, std::pair<std::string, std::string>> src;
		src[GL_VERTEX_SHADER] = std::pair(Utility::FindFileNameFromPath(vertexSrcPath), PreProcessPaths(vertexSrcPath));
		src[GL_FRAGMENT_SHADER] = std::pair(Utility::FindFileNameFromPath(fragmentSrcPath), PreProcessPaths(fragmentSrcPath));
		Compile(src);
	}

	
	OpenGLShader::OpenGLShader(const std::string& shaderFilePath)
	{
		m_FilePaths.first = shaderFilePath;
		m_FilePaths.second = "SINGLE SHADER FILE";
		
		std::string source = ReadFile(shaderFilePath);
		auto shaderSources = PreProcess(source, shaderFilePath);
		

		m_ShaderName = Utility::FindFileNameFromPath((shaderFilePath));

		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{

		glDeleteProgram(m_ShaderID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
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
				TNAH_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			TNAH_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::string OpenGLShader::PreProcessPaths(const std::string& shaderSorceFilePath)
	{
		/// retrieve the vertex/fragment source code from filePath
		std::string code;
		std::ifstream file;

		/// ensure ifstream objects can throw exceptions:
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			/// open files
			file.open(shaderSorceFilePath);
			std::stringstream ss;
			/// read file's buffer contents into streams
			ss << file.rdbuf();
			/// close file handlers
			file.close();
			/// convert stream into string
			code = ss.str();
		}
		catch (std::ifstream::failure& e)
		{
			TNAH_CORE_ERROR("{0}", e.what());
			TNAH_CORE_ASSERT(false, "Shader failed to open/parse");

		}
		return code;
	}


	std::unordered_map<GLenum, std::pair<std::string, std::string>> OpenGLShader::PreProcess(const std::string& source, const std::string& shaderFilePath)
	{

		std::unordered_map<GLenum, std::pair<std::string, std::string>> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			TNAH_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			TNAH_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			TNAH_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[Utils::ShaderTypeFromString(type)] = std::pair(Utility::FindFileNameFromPath(shaderFilePath), (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos));
		}

		return shaderSources;
	}


	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::pair<std::string, std::string>>& shaderSrc)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSrc.size());

		for (auto& kv : shaderSrc)
		{
			GLenum type = kv.first;
			const std::string& src = kv.second.second;


			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = src.c_str();
			glShaderSource(shader, 1, &sourceCStr, nullptr);


			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);
				TNAH_CORE_ERROR("Error in file: {0} \n Error: {1}", kv.second.first, infoLog.data());
				TNAH_CORE_ASSERT(false, "Shader compilation failure!");
				break;
				
			}
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);

		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			TNAH_CORE_ERROR("{0}", infoLog.data());
			TNAH_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		m_ShaderID = program;

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}

	}


	void OpenGLShader::Bind()
	{
		glUseProgram(m_ShaderID);
		m_Bound = true;
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
		m_Bound = false;
	}

	void OpenGLShader::SetBool(const std::string& name, bool value)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1i(location, (int)value);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetVec2(const std::string& name, const glm::vec2& value)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		if(!IsBound()) Bind();
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
