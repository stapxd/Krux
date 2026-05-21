#pragma once

#include <stdint.h>

namespace Krux {

	class UUID64 {
	public:
		UUID64();
		UUID64(const UUID64& uuid);
		UUID64(uint64_t uuid);

		operator uint64_t() const { return m_UUID; }

	private:
		uint64_t m_UUID;
	};

}

namespace std {
	template<>
	struct hash<Krux::UUID64> {
		std::size_t operator()(const Krux::UUID64& uuid) const {
			return std::hash<uint64_t>()((uint64_t)uuid);
		}
	};
}