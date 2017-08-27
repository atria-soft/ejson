/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <ejson/Value.hpp>

namespace ejson {
	/**
	 * @brief ejson String interface.
	 */
	class String : public ejson::Value {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalValue Internal Value to set data
			 */
			String(ememory::SharedPtr<ejson::internal::Value> _internalValue);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			String(const ejson::String& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _value String value to set
			 */
			String(const etk::String& _value="");
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return Local reference on this object
			 */
			ejson::String& operator= (const ejson::String& _obj);
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void set(const etk::String& _value);
			/**
			 * @brief get the current element Value.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return the reference of the string value.
			 */
			etk::String get(const etk::String& _errorValue="") const;
	};
}

