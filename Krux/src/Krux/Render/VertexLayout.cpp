#include "krxpch.h"
#include "VertexLayout.h"

#include "Krux/Utils/Utils.h"

namespace Krux {

	VertexLayout::VertexLayout(std::initializer_list<VertexLayoutElement> elements)
		: m_Elements(elements)
	{
		for (auto& el : m_Elements) {
			m_Stride += el.Count * Utils::GetSizeOfVertexLayoutType(el.Type);
		}
	}

}
