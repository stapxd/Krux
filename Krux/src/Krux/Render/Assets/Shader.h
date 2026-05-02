#pragma once

#include "Krux/Core/Ref.h"
#include "Asset.h"

#include <filesystem>

namespace Krux {

	enum class ShaderType {
		None = 0,
		Vertex,
		Fragment
	};

	class Shader : public Asset {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetRendererID() const = 0;

		static Ref<Shader> Create(const std::filesystem::path& path);

	protected:
		virtual bool Compile(const char* vertex_shader_source, const char* fragment_shader_source) = 0;
		virtual std::unordered_map<ShaderType, std::stringstream> ParseShader(const std::filesystem::path& path) = 0;
	};

}