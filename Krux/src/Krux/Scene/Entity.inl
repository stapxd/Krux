#pragma once
#include "Scene.h"

namespace Krux {
    template<typename C, typename... Args>
    C* Entity::AddComponent(Args&&... args) {
        return m_Scene->AddComponent<C>(*this, std::forward<Args>(args)...);
    }

    template<typename C>
    C* Entity::GetComponent() {
        return m_Scene->GetComponent<C>(*this);
    }
}