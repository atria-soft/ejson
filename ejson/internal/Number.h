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
				Number(uint64_t _value=0);
				Number(int64_t _value);
				Number(double _value);
			public:
				/**
				 * @brief Create factory on the ejson::internal::Number
				 * @param[in] _value Value to set on the ejson::Value
				 * @return A SharedPtr on the Number value
				 */
				static ememory::SharedPtr<Number> create(uint64_t _value=0);
				static ememory::SharedPtr<Number> create(int64_t _value);
				static ememory::SharedPtr<Number> create(double _value);
			protected:
				enum class type {
					tDouble,
					tInt,
					tUint,
				};
				type m_typeNumber;
				union {
					double m_value; //!< value of the node
					uint64_t m_valueU64; //!< value of the node
					int64_t m_valueI64; //!< value of the node
				};
			public:
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(double _value);
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(int64_t _value);
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(uint64_t _value);
				/**
				 * @brief Get the current element Value.
				 * @return The double number registered
				 */
				double get() const;
				/**
				 * @brief Get the current element Value.
				 * @return The unsigned integer  number registered
				 */
				uint64_t getU64() const;
				/**
				 * @brief Get the current element Value.
				 * @return The unsigned integer  number registered
				 */
				int64_t getI64() const;
			public:
				bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				bool iGenerate(std::string& _data, size_t _indent) const override;
				void iMachineGenerate(std::string& _data) const override;
				bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}


