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
		class Number : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Number(double _value=0.0) :
				  m_value(_value) {
					m_type = ejson::valueType::number;
				};
			public:
				static ememory::SharedPtr<Number> create(double _value=0.0);
				/**
				 * @brief destructor
				 */
				virtual ~Number() { };
			protected:
				double m_value; //!< value of the node
			public:
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(double _value) {
					m_value = _value;
				};
				/**
				 * @brief Get the current element Value.
				 * @return The double number registered
				 */
				double get() const {
					return m_value;
				};
				/**
				 * @brief Get the current element Value.
				 * @return The 32 bit integer number registered
				 */
				int32_t getInt32() const {
					return (int32_t)m_value;
				};
				/**
				 * @brief Get the current element Value.
				 * @return The 64 bit integer number registered
				 */
				int64_t getInt64() const {
					return (int64_t)m_value;
				};
			public: // herited function :
				virtual bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc);
				virtual bool iGenerate(std::string& _data, size_t _indent) const;
				virtual bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj);
				virtual ememory::SharedPtr<ejson::internal::Value> clone() const;
		};
	}
}


