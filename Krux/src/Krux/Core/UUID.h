#pragma once

#include <stdint.h>
#include <functional>

namespace Krux {

	class UUID64 {
	public:
		inline static uint64_t INVALID = 0;

	public:
		UUID64();
		UUID64(const UUID64& uuid);
		UUID64(uint64_t uuid);

		operator uint64_t() const { return m_UUID; }

		bool operator==(const UUID64& other) const { return m_UUID == other.m_UUID; }
		bool operator!=(const UUID64& other) const { return m_UUID != other.m_UUID; }

		bool operator==(const uint64_t& uuid) const { return m_UUID != uuid; }
		bool operator!=(const uint64_t& uuid) const { return m_UUID != uuid; }

		bool IsValid() { return m_UUID != INVALID; }

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