#pragma once

#include "Assets/AssetManager.h"
#include "Assets/Shader.h"

#include <unordered_map>

namespace Krux {

	class ShaderLibrary {
	public:
		static AssetHandle Load(const std::filesystem::path& path);

		static AssetHandle Load(const std::string& name, const std::filesystem::path& path);

		static Ref<Shader> Get(const std::string& name);
		static Ref<Shader> Get(const AssetHandle& handle);

		static bool Exists(const std::string& name);

	private:
		inline static std::unordered_map<std::string, AssetHandle> s_Shaders;

	};

}