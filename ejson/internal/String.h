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
		class String : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				String(const std::string& _value="");
			public:
				static ememory::SharedPtr<String> create(const std::string& _value="");
			protected:
				std::string m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
			public:
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				void set(const std::string& _value);
				/**
				 * @brief get the current element Value.
				 * @return the reference of the string value.
				 */
				const std::string& get() const;
			public:
				virtual bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				virtual bool iGenerate(std::string& _data, size_t _indent) const override;
				virtual bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				virtual ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}

