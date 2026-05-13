#include "krxpch.h"
#include "ShaderLibrary.h"

namespace Krux {

    AssetHandle ShaderLibrary::Load(const std::filesystem::path& path)
    {
        std::string fileStem = path.stem().string();
        auto it = s_Shaders.find(fileStem);
        if (it != s_Shaders.end()) {
            return s_Shaders[fileStem];
        }

        AssetHandle handle = AssetManager::Load<Shader>(path);
        s_Shaders[fileStem] = handle;
        return handle;
    }

    AssetHandle ShaderLibrary::Load(const std::string& name, const std::filesystem::path& path)
    {
        auto it = s_Shaders.find(name);
        if (it != s_Shaders.end()) {
            return s_Shaders[name];
        }

        std::string fileStem = path.stem().string();
        it = s_Shaders.find(fileStem);
        if (it != s_Shaders.end()) {
            return s_Shaders[fileStem];
        }

        AssetHandle handle = AssetManager::Load<Shader>(path);
        s_Shaders[name] = handle;
        return handle;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        if (Exists(name)) {
            AssetHandle handle = s_Shaders[name];
            return AssetManager::GetAsset<Shader>(handle);
        }

        return nullptr;
    }

    Ref<Shader> ShaderLibrary::Get(const AssetHandle& handle)
    {
        return AssetManager::GetAsset<Shader>(handle);
    }

    bool ShaderLibrary::Exists(const std::string& name)
    {
        return s_Shaders.find(name) != s_Shaders.end();
    }

}