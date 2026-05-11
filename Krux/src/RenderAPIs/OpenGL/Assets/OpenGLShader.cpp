#include "krxpch.h"
#include "OpenGLShader.h"

#include "Krux/Core/Core.h"

#include <glad/glad.h>

#include <ios>

namespace Krux {

	OpenGLShader::OpenGLShader(const std::filesystem::path& path)
	{
		if (!Load(path)) {
			KRX_CORE_ERROR("Failed to load Shader Asset in \'{}\'", path.string());
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	bool OpenGLShader::Load(const std::filesystem::path& path)
	{
		m_Path = path;
		auto& shaderSources = ParseShader(path);
		std::string vertex_shader_source_str = shaderSources[ShaderType::Vertex].str();
		std::string fragment_shader_source_str = shaderSources[ShaderType::Fragment].str();

		return Compile(vertex_shader_source_str.c_str(), fragment_shader_source_str.c_str());
	}

	void OpenGLShader::Bind() const
	{
		// TODO: maybe change to glActivateShaderProgram
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		// TODO: maybe change to glActivateShaderProgram
		glUseProgram(0);
	}

	void OpenGLShader::SetInt1(const char* location, int value)
	{
		glUniform1i(GetUniformLocation(location), value);
	}

	void OpenGLShader::SetIntV(const char* location, int count, const int32_t* data)
	{
		glUniform1iv(GetUniformLocation(location), count, data);
	}

	void OpenGLShader::SetFloat(const char* location, float value)
	{
		glUniform1f(GetUniformLocation(location), value);
	}

	void OpenGLShader::SetFloat4(const char* location, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(location), v0, v1, v2, v3);
	}

	void OpenGLShader::SetMat4(const char* location, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(location), 1, GL_FALSE, &matrix[0][0]);
	}

	bool OpenGLShader::Compile(const char* vertex_shader_source, const char* fragment_shader_source)
	{
		GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshader, 1, &vertex_shader_source, NULL); // vertex_shader_source is a GLchar* containing glsl shader source code
		glCompileShader(vshader);

		GLint vertex_compiled;
		glGetShaderiv(vshader, GL_COMPILE_STATUS, &vertex_compiled);
		if (vertex_compiled != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(vshader, 1024, &log_length, message);

			KRX_CORE_ERROR("Failed to compile vertex shader with message: {}", (char*)message);
			return false;
		}

		GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshader, 1, &fragment_shader_source, NULL); // fragment_shader_source is a GLchar* containing glsl shader source code
		glCompileShader(fshader);

		GLint fragment_compiled;
		glGetShaderiv(fshader, GL_COMPILE_STATUS, &fragment_compiled);
		if (fragment_compiled != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(fshader, 1024, &log_length, message);

			KRX_CORE_ERROR("Failed to compile fragment shader with message: {}", (char*)message);
			return false;
		}

		GLuint program = glCreateProgram();

		glAttachShader(program, vshader);
		glAttachShader(program, fshader);
		glLinkProgram(program);

		GLint program_linked;
		glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
		if (program_linked != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetProgramInfoLog(program, 1024, &log_length, message);

			KRX_CORE_ERROR("Failed to link shader program: {}", (char*)message);
			return false;
		}

		m_RendererID = program;
		return true;
	}

	std::unordered_map<ShaderType, std::stringstream> OpenGLShader::ParseShader(const std::filesystem::path& path)
	{
		std::ifstream in;
		in.open(path.string(), std::ios::binary);

		KRX_CORE_ASSERT(in.is_open(), "Could not open shader path!");

		std::string line;
		ShaderType currentType = ShaderType::None;

		std::unordered_map<ShaderType, std::stringstream> shaderSources;

		while (std::getline(in, line)) {
			if (line.find("#type") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					currentType = ShaderType::Vertex;
				}
				else if (line.find("fragment") != std::string::npos) {
					currentType = ShaderType::Fragment;
				}
				else {
					currentType = ShaderType::None;
				}
				continue;
			}

			if (currentType == ShaderType::None)
				continue;

			shaderSources[currentType] << line;

		}

		in.close();
		return shaderSources;
	}

	GLint OpenGLShader::GetUniformLocation(const std::string& location)
	{
		if (m_UniformLocationCache.find(location) != m_UniformLocationCache.end())
			return m_UniformLocationCache[location];

		GLint locationIndex = glGetUniformLocation(m_RendererID, location.c_str());
		if (locationIndex == -1) {
			KRX_CORE_WARN("Couldn't find uniform location ({})", location);
		}

		m_UniformLocationCache[location] = locationIndex;
		return locationIndex;
	}

}