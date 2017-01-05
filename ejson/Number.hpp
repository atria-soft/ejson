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
	 * @brief ejson Number interface.
	 */
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
			 * @return Local reference on this object
			 */
			ejson::Number& operator= (const ejson::Number& _obj);
			
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void set(double _value);
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node (integer mode).
			 */
			void set(uint64_t _value);
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node (integer mode).
			 */
			void set(int64_t _value);
			/**
			 * @brief Get the current element Value.
			 * @param[in] _errorValue Value return if no value Exist
			 * @return The double number registered
			 */
			double get(double _errorValue=0.0) const;
			/**
			 * @brief Get the current element Value.
			 * @param[in] _errorValue Value return if no value Exist
			 * @return The unsigned integer number registered
			 */
			uint64_t getU64(uint64_t _errorValue=0) const;
			/**
			 * @brief Get the current element Value.
			 * @param[in] _errorValue Value return if no value Exist
			 * @return The integer number registered
			 */
			int64_t getI64(int64_t _errorValue=0) const;
			
			ejson::internal::Number::type getType() const;
	};
}


