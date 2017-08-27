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
		 * @brief ejson Boolean internal data implementation.
		 */
		class Boolean : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 * @param[in] _value Value to set on the Element
				 */
				Boolean(bool _value=false);
			public:
				/**
				 * @brief Create factory on the ejson::internal::Boolean
				 * @param[in] _value Value to set on the ejson::Value
				 * @return A SharedPtr on the Boolean value
				 */
				static ememory::SharedPtr<Boolean> create(bool _value=false);
			protected:
				bool m_value; //!< value of the node
			public:
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(bool _value);
				/**
				 * @brief get the current element Value.
				 * @return the reference of the string value.
				 */
				bool get() const;
			public:
				bool iParse(const etk::String& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				bool iGenerate(etk::String& _data, size_t _indent) const override;
				void iMachineGenerate(etk::String& _data) const override;
				bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}

