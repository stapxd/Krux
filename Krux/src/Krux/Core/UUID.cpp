#include "krxpch.h"
#include "UUID.h"

#include <random>

namespace Krux {

	static std::random_device s_RandomDevise;
	static std::mt19937_64 s_Engine(s_RandomDevise());
	std::uniform_int_distribution<uint64_t> s_Distribution;

	UUID::UUID()
		: m_UUID(s_Distribution(s_RandomDevise))
	{}

	UUID::UUID(const UUID & uuid)
		: m_UUID(uuid.m_UUID)
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}

}