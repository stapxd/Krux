#pragma once

#include "Panel.h"

#include "Krux/Render/Assets/Texture2D.h"
#include "Krux/Render/Assets/AssetManager.h"

#include <filesystem>

namespace Krux {

	class ContentBrowserPanel : public Panel {
	public:
		ContentBrowserPanel();
		virtual void RenderContent(PanelData panelData = std::monostate{}) override;

	private:
		std::filesystem::path m_CurrentDirectory{ "assets" };

		AssetHandle m_FolderTextureHandle;
		AssetHandle m_FileTextureHandle;
	};

}