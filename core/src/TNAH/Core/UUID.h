#pragma once
#include "Core.h"
#include <xhash>

namespace tnah {

		/**
		 * @class	UUID
		 *
		 * @brief	An unique identifer class used for gameobjects
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		class UUID
		{
		public:

			/**
			 * @fn	UUID::UUID();
			 *
			 * @brief	Default constructor
			 *
			 * @author	Bryce Standley
			 * @date	7/09/2021
			 */

			UUID();

			/**
			 * @fn	UUID::UUID(uint64_t uuid);
			 *
			 * @brief	Constructor
			 *
			 * @author	Bryce Standley
			 * @date	7/09/2021
			 *
			 * @param 	uuid	The uuid.
			 */

			UUID(uint64_t uuid);

			/**
			 * @fn	UUID::UUID(const UUID& other);
			 *
			 * @brief	Copy constructor
			 *
			 * @author	Bryce Standley
			 * @date	7/09/2021
			 *
			 * @param 	other	The other.
			 */

			UUID(const UUID& other);

			/**
			 * @fn	operator UUID::uint64_t ()
			 *
			 * @brief	Cast that converts the given to a uint64_t
			 *
			 * @author	Bryce Standley
			 * @date	7/09/2021
			 *
			 * @returns	The result of the operation.
			 */

			operator uint64_t () { return m_UUID; }

			/**
			 * @fn	operator const UUID::uint64_t() const
			 *
			 * @brief	Cast that converts the given to a const uint64_t
			 *
			 * @author	Bryce Standley
			 * @date	7/09/2021
			 *
			 * @returns	A const.
			 */

			operator const uint64_t() const { return m_UUID; }
		private:

			/** @brief	The uuid */
			uint64_t m_UUID;
		};
}

namespace std {

	template <>

	/**
	 * @struct	hash<tnah::UUID>
	 *
	 * @brief	A templated hash that used the uuid
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	struct hash<tnah::UUID>
	{
		/**
		 * @fn	std::size_t operator()(const tnah::UUID& uuid) const
		 *
		 * @brief	Function call operator
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	uuid	The uuid.
		 *
		 * @returns	The result of the operation.
		 */

		std::size_t operator()(const tnah::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}
