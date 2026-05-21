#pragma once

#include "Krux/Core/Ref.h"
#include "Asset.h"

#include <filesystem>
#include <glm/glm.hpp>

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

		REGISTER_ASSET_TYPE_FUNCTIONS(Shader);

		virtual uint32_t GetRendererID() const = 0;

		static Ref<Shader> Create(const std::filesystem::path& path);

		// Uniform binds
		virtual void SetInt1(const char* location, int value) = 0;
		virtual void SetIntV(const char* location, int count, const int32_t* data) = 0;
		
		virtual void SetFloat(const char* location, float value) = 0;
		virtual void SetFloat4(const char* location, float v0, float v1, float v2, float v3) = 0;
		
		virtual void SetMat4(const char* location, const glm::mat4& matrix) = 0;

	protected:
		virtual bool Compile(const char* vertex_shader_source, const char* fragment_shader_source) = 0;
		virtual std::unordered_map<ShaderType, std::stringstream> ParseShader(const std::filesystem::path& path) = 0;
	};

}