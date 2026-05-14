#pragma once

#include <iostream>

namespace Krux {

	class RefCounted;

	template<typename T>
	class Ref {
	public:
		Ref(T* instance = nullptr)
			: m_Ptr(instance)
		{
			static_assert(std::is_base_of<RefCounted, T>::value, "Class must be derived from RefCounted!");

			if (m_Ptr)
				m_Ptr->IncrementRefCount();
		}

		template<typename U>
		Ref(const Ref<U>& other)
			: m_Ptr(other.Get())
		{
			static_assert(std::is_base_of<T, U>::value, "Incompatible types!");

			if (m_Ptr)
				m_Ptr->IncrementRefCount();
		}

		Ref(const Ref& other)
			: m_Ptr(other.m_Ptr)
		{
			m_Ptr->IncrementRefCount();
		}

		template<typename U>
		Ref& operator=(const Ref<U>& other) {
			static_assert(std::is_base_of<T, U>::value, "Incompatible types!");

			if ((void*)this != (void*)&other) {
				if (other.Get()) other.Get()->IncrementRefCount();
				if (m_Ptr) m_Ptr->DecrementRefCount();
				m_Ptr = other.Get();
			}
			return *this;
		}

		Ref& operator=(const Ref& other) {
			if (this != &other) {
				if (other.m_Ptr) other.m_Ptr->IncrementRefCount();
				if (m_Ptr) m_Ptr->DecrementRefCount();
				m_Ptr = other.m_Ptr;
			}
			return *this;
		}

		Ref(Ref<T>&& other)
			: m_Ptr(other.m_Ptr)
		{
			other.m_Ptr = nullptr;
		}

		~Ref() {
			if (m_Ptr)
				m_Ptr->DecrementRefCount();
		}

		T* operator->() const { return m_Ptr; }
		T& operator*() const { return *m_Ptr; }
		T* Get() const { return m_Ptr; }

		explicit operator bool() const { return m_Ptr != nullptr; }

		bool operator==(const Ref& other) {
			return this == &other;
		}

		template<typename T>
		Ref<T> As() {
			return Ref<T>((T*)m_Ptr);
		}

		template<typename... Args>
		static Ref<T> Create(Args&&... args) {
			return Ref<T>(new T(std::forward<Args>(args)...));
		}

	private:
		T* m_Ptr;
	};

	class RefCounted {
	public:
		virtual ~RefCounted() = default;

		uint32_t GetRefCount() const { return m_RefCount; }

	private:
		void IncrementRefCount() { m_RefCount++; }
		void DecrementRefCount() { if (--m_RefCount == 0) delete this; }

	private:
		uint32_t m_RefCount = 0;

		template<typename T>
		friend class Ref;
	};
}
