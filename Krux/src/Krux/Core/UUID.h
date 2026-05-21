#pragma once

#include <stdint.h>

namespace Krux {

	class UUID {
	public:
		UUID();
		UUID(const UUID& uuid);
		UUID(uint64_t uuid);

		operator uint64_t() const { return m_UUID; }

	private:
		uint64_t m_UUID;
	};

}

namespace std {
	template<>
	struct hash<Krux::UUID> {
		std::size_t operator()(const Krux::UUID& uuid) const {
			return std::hash<uint64_t>()((uint64_t)uuid);
		}
	};
}