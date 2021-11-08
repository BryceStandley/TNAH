#pragma once
#include "TNAH/Core/Core.h"

namespace tnah {

	/**
	 * @struct	Buffer
	 *
	 * @brief	A buffer struct
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	struct Buffer
	{

		/** @brief	A pointer to the data */
		void* Data;

		/** @brief	The size */
		uint32_t Size;

		/**
		 * @fn	Buffer()
		 *
		 * @brief	Default constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		Buffer()
			: Data(nullptr), Size(0)
		{
		}

		/**
		 * @fn	Buffer(void* data, uint32_t size)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param [in,out]	data	If non-null, the data.
		 * @param 		  	size	The size.
		 */

		Buffer(void* data, uint32_t size)
			: Data(data), Size(size)
		{
		}

		/**
		 * @fn	static Buffer Copy(const void* data, uint32_t size)
		 *
		 * @brief	Copies this object
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	data	The data.
		 * @param 	size	The size.
		 *
		 * @returns	A Buffer.
		 */

		static Buffer Copy(const void* data, uint32_t size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.Data, data, size);
			return buffer;
		}

		/**
		 * @fn	void Allocate(uint32_t size)
		 *
		 * @brief	Allocates the given size
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	size	The size.
		 */

		void Allocate(uint32_t size)
		{
			delete[] Data;
			Data = nullptr;

			if (size == 0)
				return;

			Data = new byte[size];
			Size = size;
		}

		/**
		 * @fn	void Release()
		 *
		 * @brief	Releases this object
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		void Release()
		{
			delete[] Data;
			Data = nullptr;
			Size = 0;
		}

		/**
		 * @fn	void ZeroInitialize()
		 *
		 * @brief	Zero initialize
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		void ZeroInitialize()
		{
			if (Data)
				memset(Data, 0, Size);
		}

		/**
		 * @fn	template<typename T> T& Read(uint32_t offset = 0)
		 *
		 * @brief	Reads the given offset
		 *
		 * @tparam	T	Generic type parameter.
		 * @param 	offset	(Optional) The offset.
		 *
		 * @returns	A reference to a T.
		 */

		template<typename T>
		T& Read(uint32_t offset = 0)
		{
			return *(T*)((byte*)Data + offset);
		}

		/**
		 * @fn	byte* ReadBytes(uint32_t size, uint32_t offset)
		 *
		 * @brief	Reads the bytes
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	size  	The size.
		 * @param 	offset	The offset.
		 *
		 * @returns	Null if it fails, else the bytes.
		 */

		byte* ReadBytes(uint32_t size, uint32_t offset)
		{
			TNAH_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			byte* buffer = new byte[size];
			memcpy(buffer, (byte*)Data + offset, size);
			return buffer;
		}

		/**
		 * @fn	void Write(void* data, uint32_t size, uint32_t offset = 0)
		 *
		 * @brief	Writes
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param [in,out]	data  	If non-null, the data.
		 * @param 		  	size  	The size.
		 * @param 		  	offset	(Optional) The offset.
		 */

		void Write(void* data, uint32_t size, uint32_t offset = 0)
		{
			TNAH_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			memcpy((byte*)Data + offset, data, size);
		}

		/**
		 * @fn	operator bool() const
		 *
		 * @brief	Cast that converts the given  to a bool
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator bool() const
		{
			return Data;
		}

		/**
		 * @fn	byte& operator[](int index)
		 *
		 * @brief	Array indexer operator
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The indexed value.
		 */

		byte& operator[](int index)
		{
			return ((byte*)Data)[index];
		}

		/**
		 * @fn	byte operator[](int index) const
		 *
		 * @brief	Array indexer operator
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The indexed value.
		 */

		byte operator[](int index) const
		{
			return ((byte*)Data)[index];
		}

		/**
		 * @fn	template<typename T> T* As()
		 *
		 * @brief	Gets data
		 *
		 * @tparam	T	Generic type parameter.
		 *
		 * @returns	Null if it fails, else a pointer to a T.
		 */

		template<typename T>
		T* As()
		{
			return (T*)Data;
		}

		/**
		 * @fn	inline uint32_t GetSize() const
		 *
		 * @brief	Gets the size
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The size.
		 */

		inline uint32_t GetSize() const { return Size; }
	};


}