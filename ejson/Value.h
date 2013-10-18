/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_JSON_VALUE_H__
#define __ETK_JSON_VALUE_H__

#include <etk/types.h>
#include <etk/UString.h>
#include <etk/math/Vector2D.h>

namespace ejson
{
	//#define ENABLE_DISPLAY_PARSED_ELEMENT
	#if 1
		#define JSON_PARSE_ELEMENT JSON_VERBOSE
	#else
		#define JSON_PARSE_ELEMENT JSON_DEBUG
	#endif
	#if 1
		#define JSON_PARSE_ATTRIBUTE JSON_VERBOSE
	#else
		#define JSON_PARSE_ATTRIBUTE JSON_DEBUG
	#endif
	class Document;
	class Array;
	class Object;
	class Boolean;
	class Null;
	class Number;
	class String;
	
	typedef enum {
		typeUnknow, //!< might be an error ...
		typeValue, //!< XXXXXX:*
		typeDocument, //!< all the file main access
		typeArray, //!< [...]
		typeString, //!< the "" 
		typeNumber, //!< the -1565.21515
		typeBoolean, //!< the true and false
		typeNull, //!< the null element
		typeObject, //!< the { ... }
	} nodeType_te;
	
	class filePos
	{
		private:
			int32_t m_col;
			int32_t m_line;
		public:
			filePos(void) : m_col(0),m_line(0) { };
			filePos(int32_t _line, int32_t _col) : m_col(_col),m_line(_line) { };
			~filePos(void) { };
			filePos& operator ++(void) { m_col++; return *this; };
			filePos& operator --(void) { m_col--; if(m_col<0) { m_col=0;} return *this; };
			const filePos& operator +=(const filePos& _obj) {
				if (_obj.m_line == 0) {
					m_col += _obj.m_col;
				} else {
					m_col = _obj.m_col;
					m_line += _obj.m_line;
				}
				return *this;
			};
			const filePos& operator +=(int32_t _col) {
				m_col += _col;
				return *this;
			};
			const filePos& operator= (const filePos& _obj ) {
				m_col = _obj.m_col;
				m_line = _obj.m_line;
				return *this;
			}
			void newLine(void) { m_col=0; m_line++; };
			bool check(const etk::UChar& _val) {
				m_col++;
				if (_val == '\n') {
					newLine();
					return true;
				}
				return false;
			}
			void set(int32_t _line, int32_t _col) {
				m_col = _col;
				m_line = _line;
			}
			void clear(void) {
				m_col = 0;
				m_line = 0;
			}
			int32_t getCol(void) const { return m_col; };
			int32_t getLine(void) const { return m_line; };
	};
	etk::CCout& operator <<(etk::CCout& _os, const filePos& _obj);
	
	class Value
	{
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Value(void) { };
			/**
			 * @brief destructor
			 */
			virtual ~Value(void);
		public:
			/**
			 * @brief parse the Current node [pure VIRUAL]
			 * @param[in] _data data string to parse.
			 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
			 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool iParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) = 0;
			/**
			 * @brief generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool iGenerate(etk::UString& _data, int32_t _indent) const = 0;
		public:
			/**
			 * @brief get the node type.
			 * @return the type of the Node.
			 */
			virtual nodeType_te getType(void) const { return typeValue; };
		protected:
			/**
			 * @brief add indentation of the string input.
			 * @param[in,out] _data String where the indentation is done.
			 * @param[in] _indent Number of tab to add at the string.
			 */
			void addIndent(etk::UString& _data, int32_t _indent) const;
			/**
			 * @brief Display the cuurent element that is curently parse.
			 * @param[in] _val Char that is parsed.
			 * @param[in] _filePos Position of the char in the file.
			 */
			void drawElementParsed(const etk::UChar& _val, const ejson::filePos& _filePos) const;
			/**
			 * @brief check if an name (for object named) (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \n\t\r).
			 * @param[in] _val Value to check the conformity.
			 */
			bool checkString(const etk::UChar& _val) const;
			/**
			 * @brief check if an number -+.0123456789e).
			 * @param[in] _val Value to check the conformity.
			 */
			bool checkNumber(const etk::UChar& _val) const;
			/**
			 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
			 * @param[in] _data Data to parse.
			 * @param[in] _pos Start position in the string.
			 * @param[out] _filePos new poistion of te file to add.
			 * @return number of white element.
			 */
			int32_t countWhiteChar(const etk::UString& _data, int32_t _pos, ejson::filePos& _filePos) const;
		public:
			/**
			 * @brief Cast the element in a Value if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Value* toValue(void) { return this; };
			virtual const ejson::Value* toValue(void) const { return this; };
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Document* toDocument(void) { return NULL; };
			virtual const ejson::Document* toDocument(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Array if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Array* toArray(void) { return NULL; };
			virtual const ejson::Array* toArray(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Object if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Object* toObject(void) { return NULL; };
			virtual const ejson::Object* toObject(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a String if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::String* toString(void) { return NULL; };
			virtual const ejson::String* toString(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Number if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Number* toNumber(void) { return NULL; };
			virtual const ejson::Number* toNumber(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Boolean if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Boolean* toBoolean(void) { return NULL; };
			virtual const ejson::Boolean* toBoolean(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Null if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Null* toNull(void) { return NULL; };
			virtual const ejson::Null* toNull(void) const{ return NULL; };
			
			/**
			 * @brief check if the node is a ejson::Document
			 * @return true if the node is a ejson::Document
			 */
			bool isDocument(void) const { return getType() == ejson::typeDocument; };
			/**
			 * @brief check if the node is a ejson::Array
			 * @return true if the node is a ejson::Array
			 */
			bool isArray(void) const { return getType() == ejson::typeArray; };
			/**
			 * @brief check if the node is a ejson::Object
			 * @return true if the node is a ejson::Object
			 */
			bool isObject(void) const { return getType() == ejson::typeObject; };
			/**
			 * @brief check if the node is a ejson::String
			 * @return true if the node is a ejson::String
			 */
			bool isString(void) const { return getType() == ejson::typeString; };
			/**
			 * @brief check if the node is a ejson::Number
			 * @return true if the node is a ejson::Number
			 */
			bool isNumber(void) const { return getType() == ejson::typeNumber; };
			/**
			 * @brief check if the node is a ejson::Boolean
			 * @return true if the node is a ejson::Boolean
			 */
			bool isBoolean(void) const { return getType() == ejson::typeBoolean; };
			/**
			 * @brief check if the node is a ejson::Null
			 * @return true if the node is a ejson::Null
			 */
			bool isNull(void) const { return getType() == ejson::typeNull; };
			
			/**
			 * @brief clear the Node
			 */
			virtual void clear(void) {};
			/**
			 * @brief Tranfert all element in the element set in parameter
			 * @param[in,out] _obj move all parameter in the selected element
			 * @return true if transfer is done corectly
			 * @note all element is remove from the curent element.
			 */
			virtual bool transfertIn(ejson::Value* _obj) { return false; };
			/**
			 * @brief Copy the curent node and all the child in the curent one.
			 * @return NULL in an error occured, the pointer on the element otherwise
			 */
			virtual ejson::Value* duplicate(void) const { return NULL; };
	};
};

#endif

