/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/Stream.hpp>

namespace ejson {
	/**
	 * @brief Type of the JSON elements.
	 */
	enum class valueType {
		Unknow, //!< might be an error ...
		Value, //!< might be an error ...
		Document, //!< all the file main access
		Array, //!< te element [ ... ]
		Object, //!< the element { ... }
		String,  //!< the element "..."
		Number, //!< The element 1111.2222
		Null, //!< the element null
		Boolean, //!< the element true or false
	};
	//! @not_in_doc
	etk::Stream& operator <<(etk::Stream& _os, enum valueType _obj);
}

