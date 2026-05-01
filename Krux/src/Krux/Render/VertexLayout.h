#pragma once

#include <vector>

namespace Krux {

	enum class VertexLayoutType {
		Float,
		Int,
		UnsignedInt
	};

	struct VertexLayoutElement {
		uint32_t Count;
		VertexLayoutType Type;
		bool Normalized;
	};

	class VertexLayout {
	public:
		VertexLayout(std::initializer_list<VertexLayoutElement> elements);

		const std::vector<VertexLayoutElement>& GetElements() const& { return m_Elements; }
		uint32_t GetStride() const { return m_Stride; }
	private:
		std::vector<VertexLayoutElement> m_Elements;
		uint32_t m_Stride = 0;
	};

}