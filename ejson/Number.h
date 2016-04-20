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
	class Number : public ejson::Value {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalValue Internal Value to set data
			 */
			Number(ememory::SharedPtr<ejson::internal::Value> _internalValue);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Number(const ejson::Number& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _value number value
			 */
			Number(double _value=0.0);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			ejson::Number& operator= (const ejson::Number& _obj);
			
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void set(double _value);
			/**
			 * @brief Get the current element Value.
			 * @return The double number registered
			 */
			double get() const;
			/**
			 * @brief Get the current element Value.
			 * @param[in] _errorValue Value return if no value Exist
			 * @return The double number registered
			 */
			double get(double _errorValue) const;
			/**
			 * @brief Get the current element Value.
			 * @return The 32 bit integer number registered
			 */
			int32_t getInt32() const;
			/**
			 * @brief Get the current element Value.
			 * @return The 64 bit integer number registered
			 */
			int64_t getInt64() const;
	};
}


