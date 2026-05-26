#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Krux {

	class Input {
	public:
		static bool IsKeyPressed(Key key);
		static bool IsMouseButtonPressed(Mouse mouseButton);
		
		static void GetMousePosition(double& xpos, double& ypos);
		static void SetCursorInputMode(CursorInputMode mode);
	};

}