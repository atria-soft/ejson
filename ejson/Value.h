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
	class String;
	
	typedef enum {
		typeUnknow, //!< might be an error ...
		typeValue, //!< XXXXXX:*
		typeDocument, //!< all the file main access
		typeArray, //!< [...]
		typeString, //!< the "" or %d numbers null ... 
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
			const filePos& operator +=(const filePos& _obj)
			{
				if (_obj.m_line==0) {
					m_col += _obj.m_col;
				} else {
					m_col = _obj.m_col;
					m_line += _obj.m_line;
				}
				return *this;
			};
			const filePos& operator +=(int32_t _col)
			{
				m_col += _col;
				return *this;
			};
			const filePos& operator= (const filePos& _obj )
			{
				m_col = _obj.m_col;
				m_line = _obj.m_line;
				return *this;
			}
			void NewLine(void) { m_col=0; m_line++; };
			bool Check(const etk::UniChar& _val)
			{
				m_col++;
				if (_val=='\n') {
					NewLine();
					return true;
				}
				return false;
			}
			void Set(int32_t _line, int32_t _col)
			{
				m_col = _col;
				m_line = _line;
			}
			void Clear(void)
			{
				m_col = 0;
				m_line = 0;
			}
			int32_t GetCol(void) const { return m_col; };
			int32_t GetLine(void) const { return m_line; };
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
			virtual ~Value(void) { };
		public:
			/**
			 * @brief Parse the Current node [pure VIRUAL]
			 * @param[in] _data data string to parse.
			 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
			 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc);
			/**
			 * @brief Generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool IGenerate(etk::UString& _data, int32_t _indent) const { return true; };
		public:
			/**
			 * @brief Get the node type.
			 * @return the type of the Node.
			 */
			virtual nodeType_te GetType(void) const { return typeValue; };
		protected:
			/**
			 * @brief Add indentation of the string input.
			 * @param[in,out] _data String where the indentation is done.
			 * @param[in] _indent Number of tab to add at the string.
			 */
			void AddIndent(etk::UString& _data, int32_t _indent) const;
			/**
			 * @brief Display the cuurent element that is curently parse.
			 * @param[in] _val Char that is parsed.
			 * @param[in] _filePos Position of the char in the file.
			 */
			void DrawElementParsed(const etk::UniChar& _val, const ejson::filePos& _filePos) const;
			/**
			 * @brief check if an element or attribute is availlable (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \n\t\r and for first char : not -.0123456789).
			 * @param[in] _val Value to check the conformity.
			 * @param[in] _firstChar True if the element check is the first char.
			 */
			bool CheckAvaillable(const etk::UniChar& _val, bool _firstChar=true) const;
			/**
			 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
			 * @param[in] _data Data to parse.
			 * @param[in] _pos Start position in the string.
			 * @param[out] _filePos new poistion of te file to add.
			 * @return number of white element.
			 */
			int32_t CountWhiteChar(const etk::UString& _data, int32_t _pos, ejson::filePos& _filePos) const;
		public:
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Document* ToDocument(void) { return NULL; };
			virtual const ejson::Document* ToDocument(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Array if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Array* ToArray(void) { return NULL; };
			virtual const ejson::Array* ToArray(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a Object if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::Object* ToObject(void) { return NULL; };
			virtual const ejson::Object* ToObject(void) const{ return NULL; };
			/**
			 * @brief Cast the element in a String if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual ejson::String* ToString(void) { return NULL; };
			virtual const ejson::String* ToString(void) const{ return NULL; };
			
			/**
			 * @brief Check if the node is a ejson::Document
			 * @return true if the node is a ejson::Document
			 */
			bool IsDocument(void) const { return GetType()==ejson::typeDocument; };
			/**
			 * @brief Check if the node is a ejson::Array
			 * @return true if the node is a ejson::Array
			 */
			bool IsArray(void) const { return GetType()==ejson::typeArray; };
			/**
			 * @brief Check if the node is a ejson::Object
			 * @return true if the node is a ejson::Object
			 */
			bool IsObject(void) const { return GetType()==ejson::typeObject; };
			/**
			 * @brief Check if the node is a ejson::String
			 * @return true if the node is a ejson::String
			 */
			bool IsString(void) const { return GetType()==ejson::typeString; };
			
			/**
			 * @brief Clear the Node
			 */
			virtual void Clear(void) {};
	};
};

#endif

