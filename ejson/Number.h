/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_NUMBER_H__
#define __ETK_JSON_NUMBER_H__

#include <etk/types.h>
#include <etk/UString.h>
#include <etk/math/Vector2D.h>
#include <ejson/Value.h>

namespace ejson
{
	class Number : public ejson::Value
	{
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Number(double _value=0.0) : m_value(_value) { };
			/**
			 * @brief destructor
			 */
			virtual ~Number(void) { };
		protected:
			double m_value; //!< value of the node
		public:
			/**
			 * @brief Set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			void SetValue(double _value) { m_value = _value; };
			/**
			 * @brief Get the current element Value.
			 * @return the reference of the string value.
			 */
			double GetValue(void) const { return m_value; };
		public: // herited function :
			virtual bool IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			virtual bool IGenerate(etk::UString& _data, int32_t _indent) const;
			virtual nodeType_te GetType(void) const { return typeString; };
			virtual ejson::Number* ToNumber(void) { return this; };
			virtual const ejson::Number* ToNumber(void) const{ return this; };
			virtual bool TransfertIn(ejson::Value* _obj);
			virtual ejson::Value* Duplicate(void) const;
	};
};

#endif

