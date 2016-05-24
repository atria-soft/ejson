/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>
#include <ejson/internal/Value.h>

namespace ejson {
	namespace internal {
		/**
		 * @brief ejson Null internal data implementation.
		 */
		class Null : public ejson::internal::Value {
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Null();
			public:
				/**
				 * @brief Create factory on the ejson::internal::Null
				 * @return A SharedPtr on the Null value
				 */
				static ememory::SharedPtr<Null> create();
			public:
				bool iParse(const std::string& _data, size_t& _pos, ejson::FilePos& _filePos, ejson::internal::Document& _doc) override;
				bool iGenerate(std::string& _data, size_t _indent) const override;
				void iMachineGenerate(std::string& _data) const override;
				bool transfertIn(ememory::SharedPtr<ejson::internal::Value> _obj) override;
				ememory::SharedPtr<ejson::internal::Value> clone() const override;
		};
	}
}



