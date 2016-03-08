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

namespace ejson {
	class String : public ejson::Value {
		protected:
			/**
			 * @brief basic element of a xml structure
			 */
			String(const std::string& _value="") :
			  m_value(_value) {
				
			};
		public:
			static std::shared_ptr<String> create(const std::string& _value="");
			/**
			 * @brief destructor
			 */
			virtual ~String() { };
		protected:
			std::string m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void set(const std::string& _value) {
				m_value = _value;
			};
			/**
			 * @brief get the current element Value.
			 * @return the reference of the string value.
			 */
			const std::string& get() const {
				return m_value;
			};
		public: // herited function :
			virtual bool iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool iGenerate(std::string& _data, size_t _indent) const;
			virtual bool transfertIn(std::shared_ptr<ejson::Value> _obj);
			virtual std::shared_ptr<ejson::Value> clone() const;
	};
}

