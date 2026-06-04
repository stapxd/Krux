#pragma once

#include "Krux/Scene/Components.h"

namespace Krux {

	class CameraSystem {
	public:
		static void RecalculateProjection(CameraComponent& camera);
	};

}