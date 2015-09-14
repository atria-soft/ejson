/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_JSON_VALUE_H__
#define __ETK_JSON_VALUE_H__

#include <etk/types.h>
#include <memory>


namespace ejson {
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
	//! @not-in-doc
	class filePos {
		private:
			size_t m_col;
			size_t m_line;
		public:
			filePos() :
			  m_col(0),
			  m_line(0) {
				
			};
			filePos(size_t _line, size_t _col) :
			  m_col(_col),
			  m_line(_line) {
				
			};
			~filePos() { };
			filePos& operator ++() {
				m_col++;
				return *this;
			};
			filePos& operator --() {
				if(m_col>0) {
					m_col--;
				}
				return *this;
			};
			const filePos& operator +=(const filePos& _obj) {
				if (_obj.m_line == 0) {
					m_col += _obj.m_col;
				} else {
					m_col = _obj.m_col;
					m_line += _obj.m_line;
				}
				return *this;
			};
			const filePos& operator +=(size_t _col) {
				m_col += _col;
				return *this;
			};
			const filePos& operator= (const filePos& _obj ) {
				m_col = _obj.m_col;
				m_line = _obj.m_line;
				return *this;
			}
			void newLine() {
				m_col=0;
				m_line++;
			};
			bool check(char32_t _val) {
				m_col++;
				if (_val == '\n') {
					newLine();
					return true;
				}
				return false;
			}
			void set(size_t _line, size_t _col) {
				m_col = _col;
				m_line = _line;
			}
			void clear() {
				m_col = 0;
				m_line = 0;
			}
			int32_t getCol() const {
				return m_col;
			};
			int32_t getLine() const {
				return m_line;
			};
	};
	std::ostream& operator <<(std::ostream& _os, const filePos& _obj);
	
	class Value : public std11::enable_shared_from_this<Value> {
		protected:
			/**
			 * @brief basic element of a xml structure
			 */
			Value() { };
			/**
			 * @brief destructor
			 */
			virtual ~Value();
		public:
			/**
			 * @brief parse the Current node [pure VIRUAL]
			 * @param[in] _data data string to parse.
			 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
			 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool iParse(const std::string& _data, size_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc) = 0;
			/**
			 * @brief generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool iGenerate(std::string& _data, size_t _indent) const = 0;
			/**
			 * @brief Display the Document on console
			 */
			void display() const;
		protected:
			/**
			 * @brief add indentation of the string input.
			 * @param[in,out] _data String where the indentation is done.
			 * @param[in] _indent Number of tab to add at the string.
			 */
			void addIndent(std::string& _data, size_t _indent) const;
			/**
			 * @brief Display the cuurent element that is curently parse.
			 * @param[in] _val Char that is parsed.
			 * @param[in] _filePos Position of the char in the file.
			 */
			void drawElementParsed(char32_t _val, const ejson::filePos& _filePos) const;
			/**
			 * @brief check if an name (for object named) (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \n\t\r).
			 * @param[in] _val Value to check the conformity.
			 */
			bool checkString(char32_t _val) const;
			/**
			 * @brief check if an number -+.0123456789e).
			 * @param[in] _val Value to check the conformity.
			 */
			bool checkNumber(char32_t _val) const;
			/**
			 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
			 * @param[in] _data Data to parse.
			 * @param[in] _pos Start position in the string.
			 * @param[out] _filePos new poistion of te file to add.
			 * @return number of white element.
			 */
			int32_t countWhiteChar(const std::string& _data, size_t _pos, ejson::filePos& _filePos) const;
		public:
			/**
			 * @brief Cast the element in a Value if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::Value> toValue();
			//! @previous
			const std11::shared_ptr<const ejson::Value> toValue() const;
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::Document> toDocument();
			//! @previous
			const std11::shared_ptr<const ejson::Document> toDocument() const;
			/**
			 * @brief Cast the element in a Array if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::Array> toArray();
			//! @previous
			const std11::shared_ptr<const ejson::Array> toArray() const;
			/**
			 * @brief Cast the element in a Object if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::Object> toObject();
			//! @previous
			const std11::shared_ptr<const ejson::Object> toObject() const;
			/**
			 * @brief Cast the element in a String if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::String> toString();
			//! @previous
			const std11::shared_ptr<const ejson::String> toString() const;
			/**
			 * @brief Cast the element in a Number if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::Number> toNumber();
			//! @previous
			const std11::shared_ptr<const ejson::Number> toNumber() const;
			/**
			 * @brief Cast the element in a Boolean if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::Boolean> toBoolean();
			//! @previous
			const std11::shared_ptr<const ejson::Boolean> toBoolean() const;
			/**
			 * @brief Cast the element in a Null if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			std11::shared_ptr<ejson::Null> toNull();
			//! @previous
			const std11::shared_ptr<const ejson::Null> toNull() const;
			
			/**
			 * @brief check if the node is a ejson::Document
			 * @return true if the node is a ejson::Document
			 */
			bool isDocument() const {
				return toDocument() != nullptr;
			};
			/**
			 * @brief check if the node is a ejson::Array
			 * @return true if the node is a ejson::Array
			 */
			bool isArray() const {
				return toArray() != nullptr;
			};
			/**
			 * @brief check if the node is a ejson::Object
			 * @return true if the node is a ejson::Object
			 */
			bool isObject() const {
				return toObject() != nullptr;
			};
			/**
			 * @brief check if the node is a ejson::String
			 * @return true if the node is a ejson::String
			 */
			bool isString() const {
				return toString() != nullptr;
			};
			/**
			 * @brief check if the node is a ejson::Number
			 * @return true if the node is a ejson::Number
			 */
			bool isNumber() const {
				return toNumber() != nullptr;
			};
			/**
			 * @brief check if the node is a ejson::Boolean
			 * @return true if the node is a ejson::Boolean
			 */
			bool isBoolean() const {
				return toBoolean() != nullptr;
			};
			/**
			 * @brief check if the node is a ejson::Null
			 * @return true if the node is a ejson::Null
			 */
			bool isNull() const {
				return toNull() != nullptr;
			};
			
			/**
			 * @brief clear the Node
			 */
			virtual void clear() {};
			/**
			 * @brief Tranfert all element in the element set in parameter
			 * @param[in,out] _obj move all parameter in the selected element
			 * @return true if transfer is done corectly
			 * @note all element is remove from the curent element.
			 */
			virtual bool transfertIn(std11::shared_ptr<ejson::Value> _obj) {
				return false;
			};
			/**
			 * @brief Copy the curent node and all the child in the curent one.
			 * @return nullptr in an error occured, the pointer on the element otherwise
			 */
			virtual std11::shared_ptr<ejson::Value> clone() const {
				return std11::shared_ptr<ejson::Value>();
			};
		protected:
			/**
			 * @brief check if the current element is white or not : '\t' '\n' '\r' ' '
			 * @return tue if it is white char
			 */
			static bool isWhiteChar(char32_t _val);
	};
};

#include <ejson/Array.h>
#include <ejson/Boolean.h>
#include <ejson/Null.h>
#include <ejson/Number.h>
#include <ejson/Object.h>
#include <ejson/String.h>

#endif

