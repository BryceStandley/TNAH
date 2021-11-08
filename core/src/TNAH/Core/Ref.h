#pragma once

#include <stdint.h>
#include <atomic>

namespace tnah {

	/**
	 * @class	RefCounted
	 *
	 * @brief	A wrapper for shared pointers
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class RefCounted
	{
	public:
		/**
		 * 
		 * \fn void IncRefCount
		 * 
		 * \brief Increase the ref count
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * 
		 */
		void IncRefCount() const
		{
			m_RefCount++;
		}

		/**
		 * 
		 * \fn void DecRefCount
		 * 
		 * \brief Decrease the ref count
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * 
		 */
		void DecRefCount() const
		{
			m_RefCount--;
		}

		/**
		 * 
		 * \fn uint32_t GetRefCount
		 * 
		 * \brief Get the ref count
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return 
		 * 
		 */
		uint32_t GetRefCount() const { return m_RefCount.load(); }
	private:
		/** @brief The Ref count */
		mutable std::atomic<uint32_t> m_RefCount = 0;
	};

	/**
	 * 
	 * 
	 * \brief Utility Functions
	 * 
	 * \author Bryce Standley
	 * \date 13/9/2021
	 */
	namespace RefUtils {
		/**
		 * 
		 * 
		 * \brief Adds to the references list
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 */
		void AddToLiveReferences(void* instance);

		/**
		 * 
		 * 
		 * \brief Removes from the references list
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 */
		void RemoveFromLiveReferences(void* instance);

		/**
		 * 
		 * 
		 * \brief Is the reference live
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 */
		bool IsLive(void* instance);
	}

	template<typename T>
	class Ref
	{
	public:
		/**
		 * 
		 * \fn void Ref
		 * 
		 * \brief Constructor
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * 
		 */
		Ref()
			: m_Instance(nullptr)
		{
		}
		
		/**
		 *
		 * \fn void Ref
		 *
		 * \brief Constructor
		 *
		 * \author Bryce Standley
		 * \date 13/9/2021
		 *
		 *
		 *
		 */
		Ref(std::nullptr_t n)
			: m_Instance(nullptr)
		{
		}

		/**
		 *
		 * \fn void Ref
		 *
		 * \brief Constructor
		 *
		 * \author Bryce Standley
		 * \date 13/9/2021
		 *
		 *@params instance The instance to reference
		 *
		*/
		Ref(T* instance)
			: m_Instance(instance)
		{
			static_assert(std::is_base_of<RefCounted, T>::value, "Class is not RefCounted!");

			IncRef();
		}

		/**
		 * 
		 * \fn void Ref
		 * 
		 * \brief Copy constructor of different type
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * 
		 */
		template<typename T2>
		Ref(const Ref<T2>& other)
		{
			m_Instance = (T*)other.m_Instance;
			IncRef();
		}

		/**
		 * 
		 * \fn void Ref
		 * 
		 * \brief Copy constructor of a different type
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * 
		 */
		template<typename T2>
		Ref(Ref<T2>&& other)
		{
			m_Instance = (T*)other.m_Instance;
			other.m_Instance = nullptr;
		}

		/**
		 * 
		 * \fn Ref<T> CopyWithoutIncrement
		 * 
		 * \brief Copy reference without increasing the reference count
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * \return Ref<T> Reference of type T
		 * 
		 */
		static Ref<T> CopyWithoutIncrement(const Ref<T>& other)
		{
			Ref<T> result = nullptr;
			result->m_Instance = other.m_Instance;
			return result;
		}

		/**
		 * 
		 * \fn void ~Ref
		 * 
		 * \brief Deconstructor
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * 
		 */
		~Ref()
		{
			DecRef();
		}

		/**
		 * 
		 * \fn void Ref
		 * 
		 * \brief Copy Constructor
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * 
		 */
		Ref(const Ref<T>& other)
			: m_Instance(other.m_Instance)
		{
			IncRef();
		}

		/**
		 * 
		 * \fn Ref & operator=
		 * 
		 * \brief Nullptr_t Operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param 
		 * 
		 * \return 
		 * 
		 */
		Ref& operator=(std::nullptr_t)
		{
			DecRef();
			m_Instance = nullptr;
			return *this;
		}

		/**
		 * 
		 * \fn Ref & operator=
		 * 
		 * \brief Copy operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * \return Ref copy
		 * 
		 */
		Ref& operator=(const Ref<T>& other)
		{
			other.IncRef();
			DecRef();

			m_Instance = other.m_Instance;
			return *this;
		}

		/**
		 * 
		 * \fn Ref & operator=
		 * 
		 * \brief Copy operator of different type
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * \return 
		 * 
		 */
		template<typename T2>
		Ref& operator=(const Ref<T2>& other)
		{
			other.IncRef();
			DecRef();

			m_Instance = other.m_Instance;
			return *this;
		}

		/**
		 * 
		 * \fn Ref & operator=
		 * 
		 * \brief Copy operator of different type
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * \return 
		 * 
		 */
		template<typename T2>
		Ref& operator=(Ref<T2>&& other)
		{
			DecRef();

			m_Instance = other.m_Instance;
			other.m_Instance = nullptr;
			return *this;
		}

		/**
		 * 
		 * \fn int operator bool
		 * 
		 * \brief Active operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return bool If the reference instance is not null
		 * 
		 */
		operator bool() { return m_Instance != nullptr; }

		/**
		 * 
		 * \fn int operator bool
		 * 
		 * \brief Active operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return bool If the reference instance is not null
		 * 
		 */
		operator bool() const { return m_Instance != nullptr; }

		/**
		 * 
		 * \fn T * operator->
		 * 
		 * \brief Pointer operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return m_Instance Reference instance
		 * 
		 */
		T* operator->() { return m_Instance; }

		/**
		 * 
		 * \fn const T * operator->
		 * 
		 * \brief Pointer operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return m_Instance Reference instance
		 * 
		 */
		const T* operator->() const { return m_Instance; }

		/**
		 * 
		 * \fn T & operator*
		 * 
		 * \brief Reference operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return m_Instance Reference to ref instace
		 * 
		 */
		T& operator*() { return *m_Instance; }

		/**
		 * 
		 * \fn const T & operator*
		 * 
		 * \brief Reference operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return m_Instance Reference to ref instace
		 * 
		 */
		const T& operator*() const { return *m_Instance; }

		/**
		 * 
		 * \fn T * Raw
		 * 
		 * \brief Raw instance
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return m_Instance Raw pointer to instance
		 * 
		 */
		T* Raw() { return  m_Instance; }

		/**
		 * 
		 * \fn const T * Raw
		 * 
		 * \brief Raw instance
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return m_Instance Raw pointer to instance
		 * 
		 */
		const T* Raw() const { return  m_Instance; }

		/**
		 * 
		 * \fn void Reset
		 * 
		 * \brief Resets the current instance
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param instance
		 * 
		 * 
		 */
		void Reset(T* instance = nullptr)
		{
			DecRef();
			m_Instance = instance;
		}

		/**
		 * 
		 * \fn Ref<T2> As
		 * 
		 * \brief Reinterprate instance as T2
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return this as a reference of type T2
		 * 
		 */
		template<typename T2>
		Ref<T2> As() const
		{
			return Ref<T2>(*this);
		}

		/**
		 * 
		 * \fn Ref<T> Create
		 * 
		 * \brief Create template. Calls the constructor on a object of type T
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param ...args
		 * 
		 * \return this A new Ref<T> object
		 * 
		 */
		template<typename... Args>
		static Ref<T> Create(Args&&... args)
		{
			return Ref<T>(new T(std::forward<Args>(args)...));
		}

		/**
		 * 
		 * \fn bool operator==
		 * 
		 * \brief Compare operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * \return bool true if equal, false if not
		 * 
		 */
		bool operator==(const Ref<T>& other) const
		{
			return m_Instance == other.m_Instance;
		}

		/**
		 * 
		 * \fn bool operator!=
		 * 
		 * \brief Compare operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * \return bool true if not equal, false if equal
		 * 
		 */
		bool operator!=(const Ref<T>& other) const
		{
			return !(*this == other);
		}

		/**
		 * 
		 * \fn bool EqualsObject
		 * 
		 * \brief Compares this with another object
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param other
		 * 
		 * \return bool true if equal, false if not
		 * 
		 */
		bool EqualsObject(const Ref<T>& other)
		{
			if (!m_Instance || !other.m_Instance)
				return false;
			
			return *m_Instance == *other.m_Instance;
		}
	private:
		/**
		 * 
		 * \fn void IncRef
		 * 
		 * \brief Increase the reference count
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * 
		 */
		void IncRef() const
		{
			if (m_Instance)
			{
				m_Instance->IncRefCount();
				RefUtils::AddToLiveReferences((void*)m_Instance);
			}
		}

		/**
		 * 
		 * \fn void DecRef
		 * 
		 * \brief Decrease the reference count
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * 
		 */
		void DecRef() const
		{
			if (m_Instance)
			{
				m_Instance->DecRefCount();
				if (m_Instance->GetRefCount() == 0)
				{
					delete m_Instance;
					RefUtils::RemoveFromLiveReferences((void*)m_Instance);
					m_Instance = nullptr;
				}
			}
		}

		template<class T2>
		friend class Ref;
		/**  @brief Instance the reference holds */
		mutable T* m_Instance;
	};
	
	/**
	 * 
	 * 
	 * \brief Weak reference. Wrapper for weak_ptr
	 * 
	 * \author Bryce Standley
	 * \date 13/9/2021
	 */
	template<typename T>
	class WeakRef
	{
	public:
		/**
		 * 
		 * \fn void WeakRef
		 * 
		 * \brief Default constructor
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * 
		 */
		WeakRef() = default;

		/**
		 * 
		 * \fn void WeakRef
		 * 
		 * \brief Constructor
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param ref
		 * 
		 * 
		 */
		WeakRef(Ref<T> ref)
		{
			m_Instance = ref.Raw();
		}

		/**
		 * 
		 * \fn void WeakRef
		 * 
		 * \brief Constructor
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * \param instance
		 * 
		 * 
		 */
		WeakRef(T* instance)
		{
			m_Instance = instance;
		}

		/**
		 * 
		 * \fn bool IsValid
		 * 
		 * \brief Checks if the reference is valid
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return bool true if valid, false if not
		 * 
		 */
		bool IsValid() const { return m_Instance ? RefUtils::IsLive(m_Instance) : false; }

		/**
		 * 
		 * \fn int operator bool
		 * 
		 * \brief Is Valid operator
		 * 
		 * \author Bryce Standley
		 * \date 13/9/2021
		 * 
		 * 
		 * \return bool true if valid, false if not
		 * 
		 */
		operator bool() const { return IsValid(); }
	private:
		/**  @brief Instance of the weak ref */
		T* m_Instance = nullptr;
	};

}
