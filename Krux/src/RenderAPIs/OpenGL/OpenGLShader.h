#pragma once

#include "Krux/Render/Shader.h"

#include <filesystem>

namespace Krux {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::filesystem::path& path);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetRendererID() const override { return m_RendererID; }

	protected:
		virtual void Compile(const char* vertex_shader_source, const char* fragment_shader_source) override;
		virtual std::unordered_map<ShaderType, std::stringstream> ParseShader(const std::filesystem::path& path) override;

	private:
		uint32_t m_RendererID;
	};

}

