#include "ContentBrowserPanel.h"

#include "Krux/Core/Log.h"

#include <iostream>

#include <imgui.h>

namespace Krux {

	ContentBrowserPanel::ContentBrowserPanel()
		: Panel("Content Browser")
	{
		TextureSpecification spec;
		spec.WrapR = TextureWrap::Repeat;
		spec.WrapS = TextureWrap::Repeat;
		spec.WrapT = TextureWrap::Repeat;

		m_FolderTextureHandle = AssetManager::Load<Texture2D>("assets/builtin/textures/folder.png", spec);
		m_FileTextureHandle = AssetManager::Load<Texture2D>("assets/builtin/textures/file.png", spec);
	}
	
	void ContentBrowserPanel::RenderContent(PanelData panelData) {

		Ref<Texture2D> folderTexture = AssetManager::GetAsset<Texture2D>(m_FolderTextureHandle);
		Ref<Texture2D> fileTexture   = AssetManager::GetAsset<Texture2D>(m_FileTextureHandle);

		if (m_CurrentDirectory.string() != "assets") {
			if (ImGui::Button("<-"))
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			ImGui::SameLine();
		}

		ImGui::Text(m_CurrentDirectory.string().c_str());

		float availWidth = ImGui::GetContentRegionAvail().x;
		float sizeOfElement = 100.0f;
		float padding = 8.0f;
		float imageSize = sizeOfElement - padding * 2;
		int columnCount = (int)(availWidth / sizeOfElement);

		int itemsInRow = 0;
		if (ImGui::BeginTable("ContentBrowserTable", columnCount, ImGuiTableFlags_PadOuterX)) {
			for (auto const& dir_entry : std::filesystem::directory_iterator{ m_CurrentDirectory })
			{
				const auto& path = dir_entry.path();
				std::string dirToRender = path.filename().string();
				std::string uniqueID = dirToRender + "##" + path.string();

				if (dirToRender == "builtin")
					continue;

				if(itemsInRow % columnCount == 0)
					ImGui::TableNextRow();

				ImGui::TableSetColumnIndex(itemsInRow % columnCount);

				ImTextureID textureID = dir_entry.is_directory() ? (ImTextureID)folderTexture->GetRendererID() : (ImTextureID)fileTexture->GetRendererID();

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 8.0f));
				if (ImGui::ImageButton(uniqueID.c_str(), textureID, ImVec2(imageSize, imageSize), ImVec2(0, 1), ImVec2(1, 0))) {
					if (dir_entry.is_directory()) {
						m_CurrentDirectory /= dirToRender;
					}
				}
				ImGui::PopStyleVar();

				if (!dir_entry.is_directory() && ImGui::BeginDragDropSource()) {
					std::string pathStr = path.string();
					ImGui::SetDragDropPayload("DND_FILE_PATH", pathStr.c_str(), pathStr.size() + 1);
					ImGui::EndDragDropSource();
				}

				ImGui::Text(dirToRender.c_str());
				itemsInRow++;
			}
			ImGui::EndTable();
		}
	}

}