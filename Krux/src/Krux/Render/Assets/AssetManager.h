#pragma once

#include "Krux/Core/Core.h"
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

		bool operator != (const AssetHandle& other) const { return Index != other.Index; }
		bool operator == (const AssetHandle& other) const { return Index == other.Index; }

		bool IsValid() const {
			return *this != AssetHandle();
		}
	};

	class AssetManager {
	public:
		template<typename T, typename... Args>
		static AssetHandle Load(const std::filesystem::path& path, Args&&... args) {
			uint32_t currentID = s_ID;
			uint16_t currentMagic = s_MagicCount;

			std::string pathStr = path.string();
			if (s_PathCache.count(pathStr)) {
				uint32_t id = s_PathCache[pathStr];
				uint16_t magic = s_Assets[id].Magic;
				return AssetHandle(id, magic);
			}

			s_Assets[currentID] = { T::Create(path, std::forward<Args>(args)...), currentMagic };
			s_PathCache[pathStr] = currentID;

			s_ID++;
			s_MagicCount++;

			return AssetHandle(currentID, currentMagic);
		}

		template<typename T, typename... Args>
		static AssetHandle CreateFromArgs(Args&&... args) {
			uint32_t currentID = s_ID;
			uint16_t currentMagic = s_MagicCount;

			s_Assets[currentID] = { T::Create(std::forward<Args>(args)...), currentMagic };
			s_PathCache[pathStr] = currentID;

			s_ID++;
			s_MagicCount++;

			return AssetHandle(currentID, currentMagic);
		}

		template<typename T>
		static AssetHandle CreateMemoryOnlyAsset() {
			uint32_t currentID = s_ID;
			uint16_t currentMagic = s_MagicCount;

			s_Assets[currentID] = { T::Create(), currentMagic };

			s_ID++;
			s_MagicCount++;

			return AssetHandle(currentID, currentMagic);
		}

		template<typename T>
		static Ref<T> GetAsset(AssetHandle handle) {
			if (!handle.IsValid()) return nullptr;

			auto it = s_Assets.find(handle.Index);
			if (it != s_Assets.end() && it->second.Magic == handle.Magic) {
				
				if (it->second.Asset->GetType() != T::GetStaticAssetType()) {
					KRX_CORE_ASSERT(false, "This asset handle does not correspond to type you are trying to cast to!");
					return nullptr;
				}

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