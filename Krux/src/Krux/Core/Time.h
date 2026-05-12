#pragma once

namespace Krux {

	class Time {
	public:
		Time()
		{}

		void  SetDeltaTime(float value) { m_DeltaTime = value; }
		float DeltaTime() { return m_DeltaTime; }

	private:
		float m_DeltaTime = 0.0f;
	};

}