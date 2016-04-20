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
#include <ejson/iterator.h>

namespace ejson {
	class Array : public ejson::Value {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalValue Internal Value to set data
			 */
			Array(ememory::SharedPtr<ejson::internal::Value> _internalValue);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Array(const ejson::Array& _obj);
			/**
			 * @brief Constructor
			 */
			Array();
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			ejson::Array& operator= (const ejson::Array& _obj);
		public:
			/**
			 * @brief get the number of sub element in the current one
			 * @return the Number of stored element
			 */
			size_t size() const;
			/**
			 * @brief get the pointer on an element reference with his ID.
			 * @param[in] _id Id of the element.
			 * @return nullptr if the element does not exist.
			 */
			ejson::Value operator[] (size_t _id);
			const ejson::Value operator[] (size_t _id) const;
			/**
			 * @brief get the value of the string element (if not a string return "")
			 * @param[in] _id Id of the element.
			 * @return value of the element.
			 */
			std::string getStringValue(size_t _id);
			//! @previous
			const std::string& getStringValue(size_t _id) const;
			/**
			 * @brief get the value of the string element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			std::string getStringValue(size_t _id, const std::string& _errorValue) const;
			/**
			 * @brief get the value of the Number element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			double getNumberValue(size_t _id, double _errorValue) const;
			/**
			 * @brief get the value of the Boolean element
			 * @param[in] _id Id of the element.
			 * @param[in] _errorValue The return value if an error occured.
			 * @return value of the element, or the _errorValue.
			 */
			bool getBooleanValue(size_t _id, bool _errorValue) const;
			/**
			 * @brief add an element on the array.
			 * @param[in] _element element to add.
			 * @return false if an error occured.
			 */
			bool add(const ejson::Value& _element);
			/**
			 * @brief add a string element in the Object (automatic creation)
			 * @param[in] _value string value to add
			 * @return false if an error occured
			 */
			bool addString(const std::string& _value);
			/**
			 * @brief add a "null" element in the Object (automatic creation)
			 * @return false if an error occured
			 */
			bool addNull();
			/**
			 * @brief add a boolean element in the Object (automatic creation)
			 * @param[in] _value boolean value to add
			 * @return false if an error occured
			 */
			bool addBoolean(bool _value);
			/**
			 * @brief add a double element in the Object (automatic creation)
			 * @param[in] _value double value to add
			 * @return false if an error occured
			 */
			bool addNumber(double _value);
		public:
			using iterator = ejson::iterator<ejson::Array>;
			iterator begin();
			iterator end();
			const iterator begin() const;
			const iterator end() const;
	};
}

