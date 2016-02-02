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
	class Null : public ejson::Value {
		protected:
			/**
			 * @brief basic element of a xml structure
			 */
			Null() { };
		public:
			static std11::shared_ptr<Null> create();
			/**
			 * @brief destructor
			 */
			virtual ~Null() { };
		public: // herited function :
			virtual bool iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool iGenerate(std::string& _data, size_t _indent) const;
			virtual bool transfertIn(std11::shared_ptr<ejson::Value> _obj);
			virtual std11::shared_ptr<ejson::Value> clone() const;
	};
}



