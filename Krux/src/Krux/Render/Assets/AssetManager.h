#pragma once

#include "Asset.h"

#include <stdint.h>
#include <unordered_map>

namespace Krux {

	struct AssetHandle {
		AssetHandle() 
		{}

		AssetHandle(int32_t i, uint16_t m) 
			: Index(i), Magic(m) 
		{}
		
		int32_t Index = -1;
		int16_t Magic = -1;

		bool operator != (const AssetHandle& other) { return Index != other.Index; }

		bool IsValid() {
			return *this != AssetHandle();
		}
	};

	class AssetManager {
	public:
		template<typename T>
		static AssetHandle Load(const std::filesystem::path& path) {
			uint32_t currentID = s_ID++;
			uint16_t currentMagic = s_MagicCount++;

			std::string pathStr = path.string();
			if (s_PathCache.count(pathStr)) {
				uint32_t id = s_PathCache[pathStr];
				uint16_t magic = s_Assets[id].Magic;
				return AssetHandle(id, magic);
			}

			s_Assets[currentID] = { T::Create(path), currentMagic };
			s_PathCache[pathStr] = currentID;

			return AssetHandle(currentID, currentMagic);
		}

		template<typename T>
		static Ref<T> GetAsset(AssetHandle& handle) {
			if (!handle.IsValid()) return nullptr;

			auto it = s_Assets.find(handle.Index);
			if (it != s_Assets.end() && it->second.Magic == handle.Magic) {
				return it->second.Asset.As<T>();
			}

			return nullptr;
		}

		static bool DeleteAsset(AssetHandle& handle) {
			if (!handle.IsValid())
				return false;

			if (s_Assets[handle.Index].Magic == handle.Magic) {
				s_Assets.erase(handle.Index);
				handle.Index = -1;
			}

			return true;
		}

	private:
		struct AssetElement {
			Ref<Asset> Asset;
			uint16_t Magic = 0;
		};

		inline static std::unordered_map<uint32_t, AssetElement> s_Assets;
		inline static std::unordered_map<std::string, uint32_t> s_PathCache;

		inline static uint32_t s_ID = 0;
		inline static uint16_t s_MagicCount = 0;
	};

}

/*

AssetHandle handle = AssetManager::Load<Shader>("assets/shaders/color.glsl");
Shader = AssetManager::GetAsset<Shader>(handle);

*/