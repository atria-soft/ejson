/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <ejson/Value.h>

namespace ejson {
	/**
	 * @brief ejson Null interface: 'null'.
	 */
	class Null : public ejson::Value {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalValue Internal Value to set data
			 */
			Null(ememory::SharedPtr<ejson::internal::Value> _internalValue);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Null(const ejson::Null& _obj);
			/**
			 * @brief Constructor
			 */
			Null();
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return Local reference on this object
			 */
			ejson::Null& operator= (const ejson::Null& _obj);
	};
}



