#pragma once

#include "Krux/Core/Ref.h"

#include <filesystem>

namespace Krux {

	class Asset : public RefCounted {
	public:
		virtual ~Asset() = default;
		virtual bool Load(const std::filesystem::path& path) = 0;

		const std::filesystem::path& GetPath() const { return m_Path; }
	protected:
		std::filesystem::path m_Path;
	};

}