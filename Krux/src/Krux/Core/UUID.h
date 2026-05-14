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