/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Map.hpp>
#include <ejson/internal/Value.hpp>

namespace ejson {
	namespace internal {
		/**
		 * @brief ejson Object internal data implementation.
		 */
		class Object : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Object() :
				  m_value(0, false) { // Force unorder map
					m_type = ejson::valueType::object;
				};
			public:
				/**
				 * @brief Create factory on the ejson::internal::Object
				 * @return A SharedPtr on the Object value
				 */
				static ememory::SharedPtr<Object> create();
				/**
				 * @brief Create factory on the ejson::internal::Object
				 * @param[in] _data Json stream to parse and interprete
				 * @return A SharedPtr on the Object value
				 */
				static ememory::SharedPtr<Object> create(const etk::String& _data);
			protected:
				etk::Map<etk::String, ememory::SharedPtr<ejson::internal::Value>> m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
			public:
				/**
				 * @brief check if an element exist.
				 * @param[in] _name name of the object.
				 * @return The existance of the element.
				 */
				bool exist(const etk::String& _name) const;
				/**
				 * @brief get the sub element with his name (no cast check)
				 * @param[in] _name name of the object
				 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
				 */
				ememory::SharedPtr<ejson::internal::Value> get(const etk::String& _name);
				/**
				 * @brief get the sub element with his name (no cast check)
				 * @param[in] _name name of the object
				 * @return pointer on the element requested or nullptr if it not the corect type or does not existed
				 */
				const ememory::SharedPtr<ejson::internal::Value> get(const etk::String& _name) const;
			public:
				/**
				 * @brief Get all the element name (keys).
				 * @return a vector of all name (key).
				 */
				etk::Vector<etk::String> getKeys() const;
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
				ememory::SharedPtr<ejson::internal::Value> get(size_t _id);
				/**
				 * @brief get the pointer on an element reference with his ID.
				 * @param[in] _id Id of the element.
				 * @return nullptr if the element does not exist.
				 */
				const ememory::SharedPtr<ejson::internal::Value> get(size_t _id) const;
				/**
				 * @brief Get the element name (key).
				 * @param[in] _id Id of the element.
				 * @return The name (key).
				 */
				etk::String getKey(size_t _id) const;
			public:
				/**
				 * @brief add an element in the Object
				 * @param[in] _name name of the object
				 * @param[in] _value Element to add
				 * @return false if an error occured
				 */
				bool add(const etk::String& _name, ememory::SharedPtr<ejson::internal::Value> _value);
				/**
				 * @brief Remove Value with his name
				 * @param[in] _name Name of the object
				 */
				void remove(const etk::String& _name);
				/**
				 * @brief Remove Value with his id
				 * @param[in] _id Id of the element.
				 */
				void remove(size_t _id);
				/**
				 * @brief Clone the current object in an other Object
				 * @param[in] _obj Other object ot overwride
				 * @return true The clone has been corectly done, false otherwise
				 */
				bool cloneIn(ememory::SharedPtr<ejson::internal::Object>& _obj) const;
				/**
				 * @brief Clone the current object
				 * @return A new object that has been clone
				 */
				ememory::SharedPtr<ejson::internal::Object> cloneObj() const;
			public:
				bool iParse(const etk::String& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				bool iGenerate(etk::String& _data, size_t _indent) const override;
				void iMachineGenerate(etk::String& _data) const override;
				void clear() override;
				bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}

