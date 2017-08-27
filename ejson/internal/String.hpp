/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <ejson/internal/Value.hpp>

namespace ejson {
	namespace internal {
		/**
		 * @brief ejson String internal data implementation.
		 */
		class String : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 * @param[in] _value Value to set on the ejson::Value
				 */
				String(const etk::String& _value="");
			public:
				/**
				 * @brief Create factory on the ejson::internal::String
				 * @param[in] _value Value to set on the ejson::Value
				 * @return A SharedPtr on the String value
				 */
				static ememory::SharedPtr<String> create(const etk::String& _value="");
			protected:
				etk::String m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
			public:
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(const etk::String& _value);
				/**
				 * @brief get the current element Value.
				 * @return the reference of the string value.
				 */
				const etk::String& get() const;
			public:
				bool iParse(const etk::String& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				bool iGenerate(etk::String& _data, size_t _indent) const override;
				void iMachineGenerate(etk::String& _data) const override;
				bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}

