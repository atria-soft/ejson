/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */


#include <ejson/Object.h>
#include <ejson/Array.h>
#include <ejson/String.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"Array"


void ejson::Array::Clear(void)
{
	
}

bool ejson::Array::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	return false;
}


bool ejson::Array::IGenerate(etk::UString& _data, int32_t _indent) const
{
	return false;
}




