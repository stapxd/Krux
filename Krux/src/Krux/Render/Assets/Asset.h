#pragma once

#include "Krux/Core/Ref.h"

#include <filesystem>

namespace Krux {

	enum class AssetType {
		None = 0,
		Shader,
		Texture
	};

	#define REGISTER_ASSET_TYPE_FUNCTIONS(type) \
		static AssetType GetStaticAssetType() { return AssetType::##type; } \
		virtual AssetType GetType() const override { return GetStaticAssetType(); }

	class Asset : public RefCounted {
	public:
		virtual ~Asset() = default;
		virtual bool Load(const std::filesystem::path& path) = 0;
		virtual AssetType GetType() const = 0;

		const std::filesystem::path& GetPath() const { return m_Path; }
	protected:
		std::filesystem::path m_Path;
	};

}
