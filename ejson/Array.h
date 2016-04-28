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
	/**
	 * @brief ejson Array interface [ ... ].
	 */
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
			 * @return Local reference on this object
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
			/**
			 * @brief get the pointer on an element reference with his ID.
			 * @param[in] _id Id of the element.
			 * @return nullptr if the element does not exist.
			 */
			const ejson::Value operator[] (size_t _id) const;
			/**
			 * @brief add an element on the array.
			 * @param[in] _element element to add.
			 * @return false if an error occured.
			 */
			bool add(const ejson::Value& _element);
			/**
			 * @brief Remove Value with his Id
			 * @param[in] _id Id of the element.
			 */
			void remove(size_t _id);
		public:
			using iterator = ejson::iterator<ejson::Array>; //!< Specify iterator of the Array methode
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

