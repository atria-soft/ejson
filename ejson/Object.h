/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <etk/Hash.h>
#include <algorithm>
#include <ejson/Value.h>
#include <ejson/iterator.h>

namespace ejson {
	/**
	 * @brief ejson Object interface { ... }.
	 */
	class Object : public ejson::Value {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalValue Internal Value to set data
			 */
			Object(ememory::SharedPtr<ejson::internal::Value> _internalValue);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Object(const ejson::Object& _obj);
			/**
			 * @brief Constructor
			 */
			Object();
			/**
			 * @brief Constructor
			 * @param[in] _data string data to parse
			 */
			Object(const std::string& _data);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return Local reference on this object
			 */
			ejson::Object& operator= (const ejson::Object& _obj);
			
		public:
			/**
			 * @brief check if an element exist.
			 * @param[in] _name Name of the object.
			 * @return The existance of the element.
			 */
			bool valueExist(const std::string& _name) const;
			/**
			 * @brief Cet the sub element with his name (no cast check)
			 * @param[in] _name Name of the object
			 * @return Value on the element requested or a value that does not exist @ref ejson::Value::exist.
			 */
			ejson::Value operator[] (const std::string& _name);
			/**
			 * @brief Get the const sub element with his name (no cast check)
			 * @param[in] _name Name of the object
			 * @return const Value on the element requested or a value that does not exist @ref ejson::Value::exist.
			 */
			const ejson::Value operator[] (const std::string& _name) const;
		public:
			/**
			 * @brief Get all the element name (keys).
			 * @return a vector of all name (key).
			 */
			std::vector<std::string> getKeys() const;
			/**
			 * @brief get the number of sub element in the current one
			 * @return the Number of stored element
			 */
			size_t size() const;
			/**
			 * @brief Get the value on an element reference with his ID.
			 * @param[in] _id Id of the element.
			 * @return Value on the element requested or a value that does not exist @ref ejson::Value::exist.
			 */
			ejson::Value operator[] (size_t _id);
			/**
			 * @brief Get the const value on an element reference with his ID.
			 * @param[in] _id Id of the element.
			 * @return const Value on the element requested or a value that does not exist @ref ejson::Value::exist.
			 */
			const ejson::Value operator[] (size_t _id) const;
			/**
			 * @brief Get the element name (key).
			 * @param[in] _id Id of the element.
			 * @return The name (key).
			 */
			std::string getKey(size_t _id) const;
		public:
			/**
			 * @brief add an element in the Object
			 * @param[in] _name name of the object
			 * @param[in] _value Element to add
			 * @return false if an error occured
			 */
			bool add(const std::string& _name, const ejson::Value& _value);
			/**
			 * @brief Remove Value with his name
			 * @param[in] _name Name of the object
			 */
			void remove(const std::string& _name);
			/**
			 * @brief Remove Value with his id
			 * @param[in] _id Id of the element.
			 */
			void remove(size_t _id);
		public:
			using iterator = ejson::iterator<ejson::Object>; //!< Specify iterator of the Object methode
			/**
			 * @brief Get iterator of the first Value
			 * @return iterator on the begin position of the Value
			 */
			iterator begin();
			/**
			 * @brief Get iterator of the next of the last Value
			 * @return iterator on the next of the last position of the Value
			 */
			iterator end();
			/**
			 * @brief Get const iterator of the first Value
			 * @return const iterator on the begin position of the Value
			 */
			const iterator begin() const;
			/**
			 * @brief Get const iterator of the next of the last Value
			 * @return const iterator on the next of the last position of the Value
			 */
			const iterator end() const;
			/**
			 * @brief Remove Value with his iterator
			 * @param[in] _it Iterator on the Value.
			 * @return New valid iterator on the next element or this.end()
			 */
			iterator remove(const iterator& _it);
	};
}

