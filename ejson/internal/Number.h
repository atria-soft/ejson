/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <ejson/internal/Value.h>

namespace ejson {
	namespace internal {
		/**
		 * @brief ejson Number internal data implementation.
		 */
		class Number : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 * @param[in] _value Value to set on the ejson::Value
				 */
				Number(double _value=0.0);
			public:
				/**
				 * @brief Create factory on the ejson::internal::Number
				 * @param[in] _value Value to set on the ejson::Value
				 * @return A SharedPtr on the Number value
				 */
				static ememory::SharedPtr<Number> create(double _value=0.0);
			protected:
				double m_value; //!< value of the node
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
			public:
				bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				bool iGenerate(std::string& _data, size_t _indent) const override;
				bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}


