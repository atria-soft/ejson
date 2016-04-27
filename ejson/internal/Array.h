/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <ejson/internal/Value.h>

namespace ejson {
	namespace internal {
		class Array : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Array() {
					m_type = ejson::valueType::array;
				}
			public:
				static ememory::SharedPtr<Array> create();
			private:
				std::vector<ememory::SharedPtr<ejson::internal::Value> > m_value; //!< vector of sub elements
			public:
				/**
				 * @brief get the number of sub element in the current one
				 * @return the Number of stored element
				 */
				size_t size() const {
					return m_value.size();
				}
				/**
				 * @brief get the pointer on an element reference with his ID.
				 * @param[in] _id Id of the element.
				 * @return nullptr if the element does not exist.
				 */
				ememory::SharedPtr<ejson::internal::Value> get(size_t _id) {
					return m_value[_id];
				}
				//! @previous
				const ememory::SharedPtr<const ejson::internal::Value> get(size_t _id) const{
					return m_value[_id];
				}
				/**
				 * @brief add an element on the array.
				 * @param[in] _element element to add.
				 * @return false if an error occured.
				 */
				bool add(ememory::SharedPtr<ejson::internal::Value> _element);
				/**
				 * @brief Remove Value with his Id
				 * @param[in] _id Id of the element.
				 */
				void remove(size_t _id);
			public:
				bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				bool iGenerate(std::string& _data, size_t _indent) const override;
				void clear() override;
				bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}

