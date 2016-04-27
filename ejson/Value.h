/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <ememory/memory.h>
#include <ejson/FilePos.h>
#include <ejson/valueType.h>
#include <ejson/internal/Value.h>

/**
 * @brief ejson namespace containing all function for JSON interpretor
 */
namespace ejson {
	class Document;
	class Array;
	class Object;
	class Boolean;
	class Null;
	class Number;
	class String;
	namespace internal {
		class Value;
	}
	/**
	 * @brief Basic main object of all json elements.
	 */
	class Value {
		friend ejson::Array;
		friend ejson::Object;
		protected:
			ememory::SharedPtr<ejson::internal::Value> m_data; //!< internal reference on a Value
		public:
			/**
			 * @brief Get Value type
			 * @return Type of the object
			 */
			enum ejson::valueType getType() const;
		public:
			/**
			 * @brief basic element of a xml structure
			 * @param[in] _internalValue Internal reference of the Value.
			 */
			Value(const ememory::SharedPtr<ejson::internal::Value>& _internalValue);
			/**
			 * @brief basic element of a xml structure
			 */
			Value();
		public:
			/**
			 * @brief Virtualize destructor
			 */
			virtual ~Value() = default;
		public:
			/**
			 * @brief Display the Document on console
			 */
			void display() const;
			/**
			 * @brief Check if the element exit
			 * @return true The element exist
			 * @return False The element does NOT exist
			 */
			bool exist() const;
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			ejson::Document toDocument();
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const ejson::Document toDocument() const;
			/**
			 * @brief Cast the element in a Array if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			ejson::Array toArray();
			/**
			 * @brief Cast the element in a Array if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const ejson::Array toArray() const;
			/**
			 * @brief Cast the element in a Object if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			ejson::Object toObject();
			/**
			 * @brief Cast the element in a Object if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const ejson::Object toObject() const;
			/**
			 * @brief Cast the element in a String if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			ejson::String toString();
			/**
			 * @brief Cast the element in a String if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const ejson::String toString() const;
			/**
			 * @brief Cast the element in a Number if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			ejson::Number toNumber();
			/**
			 * @brief Cast the element in a Number if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const ejson::Number toNumber() const;
			/**
			 * @brief Cast the element in a Boolean if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			ejson::Boolean toBoolean();
			/**
			 * @brief Cast the element in a Boolean if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const ejson::Boolean toBoolean() const;
			/**
			 * @brief Cast the element in a Null if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			ejson::Null toNull();
			/**
			 * @brief Cast the element in a Null if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const ejson::Null toNull() const;
			
			/**
			 * @brief check if the node is a ejson::Document
			 * @return true if the node is a ejson::Document
			 */
			bool isDocument() const;
			/**
			 * @brief check if the node is a ejson::Array
			 * @return true if the node is a ejson::Array
			 */
			bool isArray() const;
			/**
			 * @brief check if the node is a ejson::Object
			 * @return true if the node is a ejson::Object
			 */
			bool isObject() const;
			/**
			 * @brief check if the node is a ejson::String
			 * @return true if the node is a ejson::String
			 */
			bool isString() const;
			/**
			 * @brief check if the node is a ejson::Number
			 * @return true if the node is a ejson::Number
			 */
			bool isNumber() const;
			/**
			 * @brief check if the node is a ejson::Boolean
			 * @return true if the node is a ejson::Boolean
			 */
			bool isBoolean() const;
			/**
			 * @brief check if the node is a ejson::Null
			 * @return true if the node is a ejson::Null
			 */
			bool isNull() const;
			/**
			 * @brief clear the Node
			 */
			void clear();
			/**
			 * @brief Tranfert all element in the element set in parameter
			 * @param[in,out] _obj move all parameter in the selected element
			 * @return true if transfer is done corectly
			 * @note all element is remove from the curent element.
			 */
			bool transfertIn(ejson::Value& _obj);
			/**
			 * @brief Copy the curent node and all the child in the curent one.
			 * @return nullptr in an error occured, the pointer on the element otherwise
			 */
			ejson::Value clone() const;
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const ejson::Value& _obj);
	/**
	 * @brief create an empty Value (that does not exist ...
	 * @return empty value (not usable)
	 */
	ejson::Value empty();
}

#include <ejson/Array.h>
#include <ejson/Boolean.h>
#include <ejson/Null.h>
#include <ejson/Number.h>
#include <ejson/Object.h>
#include <ejson/String.h>


