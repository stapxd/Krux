#pragma once

#include <functional>
#include <queue>

#include <thread>
#include <mutex>
#include <condition_variable>

namespace Krux {

	class FrameSync {
	public:
		FrameSync(int maxFramesInFlight)
			: m_FramesInFlight(0), m_Max(maxFramesInFlight) {}

		void AcquireFrame() {
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_CV.wait(lock, [this]() { return m_FramesInFlight < m_Max; });
			m_FramesInFlight++;
		}

		void ReleaseFrame() {
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_FramesInFlight--;
			m_CV.notify_one();
		}

	private:
		std::mutex m_Mutex;
		std::condition_variable m_CV;
		int m_FramesInFlight;
		int m_Max;
	};

	class RenderQueue {
	public:
		RenderQueue()
			: m_FrameSync(1)
		{}

		using Command = std::function<void()>;

		void Shutdowm();
		void Submit(Command command);
		bool Execute();

		void AcquireFrame() { m_FrameSync.AcquireFrame(); }
		void ReleaseFrame() { m_FrameSync.ReleaseFrame(); }

	private:
		bool m_Shutdown = false;

		std::queue<Command> m_CommandQueue;
		std::mutex m_Mutex;
		std::condition_variable m_CV;
		FrameSync m_FrameSync;
	};

}