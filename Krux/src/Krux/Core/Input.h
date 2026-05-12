#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Krux {

	class Input {
	public:
		static bool IsKeyPressed(Key key);
		static bool IsMouseButtonPressed(Mouse mouseButton);
	};

}