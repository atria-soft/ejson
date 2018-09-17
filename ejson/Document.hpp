/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <ejson/Value.hpp>
#include <etk/Vector.hpp>
#include <etk/types.hpp>
#include <ejson/String.hpp>
#include <ejson/Array.hpp>
#include <ejson/Object.hpp>
#include <etk/uri/Uri.hpp>

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
			 * @brief parse a string that contain an Json
			 * @param[in] _data Data to parse
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool parse(const etk::String& _data);
			/**
			 * @brief generate a string that contain the created Json
			 * @param[out] _data Data where the Json is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool generate(etk::String& _data);
			/**
			 * @brief Load the file that might contain the Json
			 * @param[in] _path/_uri Path/URI of the json
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool load(const etk::Path& _path);
			/// @previous
			bool load(const etk::Uri& _uri);
			/**
			 * @brief Store the Json in the file
			 * @param[in] _path/_uri Path/URI of the json
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool store(const etk::Path& _path);
			/// @previous
			bool store(const etk::Uri& _uri);
			/**
			 * @brief Store the Json in the file (safe mode mean that the file is store in a second file xxx.tmp and moved in the file xxx (only one mode to be really safe with filesystem ...)
			 * @param[in] _path/_uri Path/URI of the json
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool storeSafe(const etk::Path& _path);
			/// @previous
			bool storeSafe(const etk::Uri& _uri);
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

