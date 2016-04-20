/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <ejson/internal/Value.h>

namespace ejson {
	namespace internal {
		class Null : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Null() {
					m_type = ejson::valueType::null;
				};
			public:
				static ememory::SharedPtr<Null> create();
				/**
				 * @brief destructor
				 */
				virtual ~Null() { };
			public: // herited function :
				virtual bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc);
				virtual bool iGenerate(std::string& _data, size_t _indent) const;
				virtual bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj);
				virtual ememory::SharedPtr<ejson::internal::Value> clone() const;
		};
	}
}



