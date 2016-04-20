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
		class Boolean : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Boolean(bool _value=false) :
				  m_value(_value) {
					m_type = ejson::valueType::boolean;
				};
			public:
				static ememory::SharedPtr<Boolean> create(bool _value=false);
				/**
				 * @brief destructor
				 */
				virtual ~Boolean() {
					
				};
			protected:
				bool m_value; //!< value of the node
			public:
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(bool _value) {
					m_value = _value;
				};
				/**
				 * @brief get the current element Value.
				 * @return the reference of the string value.
				 */
				bool get() const {
					return m_value;
				};
			public: // herited function :
				virtual bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc);
				virtual bool iGenerate(std::string& _data, size_t _indent) const;
				virtual bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj);
				virtual ememory::SharedPtr<ejson::internal::Value> clone() const;
		};
	}
}

