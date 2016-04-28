/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <ejson/Value.h>
#include <vector>
#include <etk/types.h>
#include <ejson/String.h>
#include <ejson/Array.h>
#include <ejson/Object.h>

namespace ejson {
	/**
	 * @brief ejson Document interface (acces with the file and stream).
	 */
	class Document : public ejson::Object {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalValue Internal Value to set data
			 */
			Document(ememory::SharedPtr<ejson::internal::Value> _internalValue);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Document(const ejson::Document& _obj);
			/**
			 * @brief Constructor
			 */
			Document();
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return Local reference on this object
			 */
			ejson::Document& operator= (const ejson::Document& _obj);
			/**
			 * @brief parse a string that contain an XML
			 * @param[in] _data Data to parse
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool parse(const std::string& _data);
			/**
			 * @brief generate a string that contain the created XML
			 * @param[out] _data Data where the xml is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool generate(std::string& _data);
			/**
			 * @brief Load the file that might contain the xml
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool load(const std::string& _file);
			/**
			 * @brief Store the Xml in the file
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool store(const std::string& _file);
			/**
			 * @brief Set the display of the error when detected.
			 * @param[in] _value true: display error, false not display error (get it at end)
			 */
			void setDisplayError(bool _value);
			/**
			 * @brief Get the display of the error status.
			 * @return true Display error
			 * @return false Does not display error (get it at end)
			 */
			bool getDisplayError();
			/**
			 * @brief Display error detected.
			 */
			void displayError();
	};
}

