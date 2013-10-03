/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_STRING_H__
#define __ETK_JSON_STRING_H__

#include <etk/types.h>
#include <etk/UString.h>
#include <etk/math/Vector2D.h>
#include <ejson/Value.h>

namespace ejson
{
	class String : public ejson::Value
	{
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			String(const etk::UString& _value="") : m_value(_value) { };
			/**
			 * @brief destructor
			 */
			virtual ~String(void) { };
		protected:
			etk::UString m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void set(const etk::UString& _value) { m_value = _value; };
			/**
			 * @brief get the current element Value.
			 * @return the reference of the string value.
			 */
			const etk::UString& get(void) const { return m_value; };
		public: // herited function :
			virtual bool iParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool iGenerate(etk::UString& _data, int32_t _indent) const;
			virtual nodeType_te getType(void) const { return typeString; };
			virtual ejson::String* toString(void) { return this; };
			virtual const ejson::String* toString(void) const{ return this; };
			virtual bool transfertIn(ejson::Value* _obj);
			virtual ejson::Value* duplicate(void) const;
	};
};

#endif

