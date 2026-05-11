#pragma once

#include "Krux/Render/Assets/Shader.h"

#include <filesystem>
#include <glm/glm.hpp>

#include <glad/glad.h>

namespace Krux {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::filesystem::path& path);
		virtual ~OpenGLShader();

		virtual bool Load(const std::filesystem::path& path) override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		// Uniform Binds
		virtual void SetInt1(const char* location, int value) override;

		virtual void SetFloat4(const char* location, float v0, float v1, float v2, float v3) override;

		virtual void SetMat4(const char* location, const glm::mat4& matrix) override;

	protected:
		virtual bool Compile(const char* vertex_shader_source, const char* fragment_shader_source) override;
		virtual std::unordered_map<ShaderType, std::stringstream> ParseShader(const std::filesystem::path& path) override;

		GLint GetUniformLocation(const std::string& location);

	private:
		uint32_t m_RendererID;

		std::unordered_map<std::string, GLint> m_UniformLocationCache;
	};

}

