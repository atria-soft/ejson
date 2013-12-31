/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_NULL_H__
#define __ETK_JSON_NULL_H__

#include <etk/types.h>
#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <ejson/Value.h>

namespace ejson {
	class Null : public ejson::Value {
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Null(void) { };
			/**
			 * @brief destructor
			 */
			virtual ~Null(void) { };
		public: // herited function :
			virtual bool iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool iGenerate(std::string& _data, size_t _indent) const;
			virtual enum nodeType getType(void) const {
				return typeString;
			};
			virtual ejson::Null* toNull(void) {
				return this;
			};
			//! @previous
			virtual const ejson::Null* toNull(void) const{
				return this;
			};
			virtual bool transfertIn(ejson::Value* _obj);
			virtual ejson::Value* duplicate(void) const;
	};
};

#endif

