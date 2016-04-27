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
	class Boolean : public ejson::Value {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalValue Internal Value to set data
			 */
			Boolean(ememory::SharedPtr<ejson::internal::Value> _internalValue);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Boolean(const ejson::Boolean& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _value bool value to store
			 */
			Boolean(bool _value=false);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			ejson::Boolean& operator= (const ejson::Boolean& _obj);
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void set(bool _value);
			/**
			 * @brief get the current element Value.
			 * @param[in] _errorValue Value return if no value Exist
			 * @return the reference of the string value.
			 */
			bool get(bool _errorValue=false) const;
	};
}

