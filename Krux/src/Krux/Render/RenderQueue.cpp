#include "krxpch.h"
#include "RenderQueue.h"

namespace Krux {
	
	void RenderQueue::Shutdowm()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Shutdown = true;
		m_CV.notify_all();
	}

	void RenderQueue::Submit(Command command)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_CommandQueue.push(std::move(command));
		m_CV.notify_one();
	}

	bool RenderQueue::Execute()
	{
		std::queue<Command> commandsToExecute;
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_CV.wait(lock, [this]() { return !m_CommandQueue.empty() || m_Shutdown; });

			if (m_Shutdown && m_CommandQueue.empty())
				return false;

			std::swap(commandsToExecute, m_CommandQueue);
		}

		while (!commandsToExecute.empty()) {
			commandsToExecute.front()();
			commandsToExecute.pop();
		}

		return true;
	}

}