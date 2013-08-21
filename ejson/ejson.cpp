/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <ejson/ejson.h>
#include <ejson/debug.h>
#include <etk/os/FSNode.h>

#include <ejson/Object.h>
#include <ejson/Array.h>
#include <ejson/String.h>

#undef __class__
#define __class__	"Document"

ejson::Document::Document(void) : 
	m_subElement(NULL),
	m_writeErrorWhenDetexted(true),
	m_comment(""),
	m_Line(""),
	m_filePos(0,0)
{
	
}

ejson::Document::~Document(void)
{
	if (NULL!=m_subElement) {
		delete m_subElement;
		m_subElement=NULL;
	}
}

bool ejson::Document::IGenerate(etk::UString& _data, int32_t _indent) const
{
	if (NULL!=m_subElement) {
		m_subElement->IGenerate(_data, _indent+1);
	}
	_data += "\n";
	return true;
}

bool ejson::Document::Parse(const etk::UString& _data)
{
	JSON_VERBOSE("Start parsing document (type: string) size=" << _data.Size());
	Clear();
	ejson::filePos filePos(1,0);
	int32_t parsePos = 0;
	return IParse(_data, parsePos, filePos, *this);
}

bool ejson::Document::Generate(etk::UString& _data)
{
	_data = "";
	return IGenerate(_data,0);
}

bool ejson::Document::Load(const etk::UString& _file)
{
	// Start loading the XML : 
	JSON_VERBOSE("open file (xml) \"" << _file << "\"");
	Clear();
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.Exist()) {
		JSON_ERROR("File Does not exist : " << _file);
		return false;
	}
	int64_t fileSize = tmpFile.FileSize();
	if (0==fileSize) {
		JSON_ERROR("This file is empty : " << _file);
		return false;
	}
	if (false == tmpFile.FileOpenRead()) {
		JSON_ERROR("Can not open (r) the file : " << _file);
		return false;
	}
	// allocate data
	char * fileBuffer = new char[fileSize+5];
	if (NULL == fileBuffer) {
		JSON_ERROR("Error Memory allocation size=" << fileSize);
		return false;
	}
	// TODO :  change this ... get the charset from the Declaration element ...
	memset(fileBuffer, 0, (fileSize+5)*sizeof(char));
	// load data from the file :
	tmpFile.FileRead(fileBuffer, 1, fileSize);
	// close the file:
	tmpFile.FileClose();
	
	// convert in UTF8 :
	etk::UString tmpDataUnicode(fileBuffer, unicode::EDN_CHARSET_UTF8);
	// remove temporary buffer:
	delete(fileBuffer);
	// parse the data :
	bool ret = Parse(tmpDataUnicode);
	//Display();
	return ret;
}

bool ejson::Document::Store(const etk::UString& _file)
{
	etk::UString createData;
	if (false == Generate(createData)) {
		JSON_ERROR("Error while creating the XML : " << _file);
		return false;
	}
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.FileOpenWrite()) {
		JSON_ERROR("Can not open (w) the file : " << _file);
		return false;
	}
	etk::Char endTable = createData.c_str();
	if (tmpFile.FileWrite(endTable, sizeof(char), endTable.Size()) != endTable.Size()) {
		JSON_ERROR("Error while writing output XML file : " << _file);
		tmpFile.FileClose();
		return false;
	}
	tmpFile.FileClose();
	return true;
}

void ejson::Document::Display(void)
{
	etk::UString tmpp;
	IGenerate(tmpp, 0);
	JSON_INFO("Generated JSON : \n" << tmpp);
}

static etk::UString CreatePosPointer(const etk::UString& _line, int32_t _pos)
{
	etk::UString out;
	int32_t iii;
	for (iii=0; iii<_pos && iii<_line.Size(); iii++) {
		if (_line[iii] == '\t') {
			out += "\t";
		} else {
			out += " ";
		}
	}
	for (; iii<_pos; iii++) {
		out += " ";
	}
	out += "^";
	return out;
}

void ejson::Document::DisplayError(void)
{
	if (m_comment.Size()==0) {
		JSON_ERROR("No error detected ???");
		return;
	}
	JSON_ERROR(m_filePos << " " << m_comment << "\n"
	           << m_Line << "\n"
	           << CreatePosPointer(m_Line, m_filePos.GetCol()) );
	#ifdef ENABLE_CRITICAL_WHEN_ERROR
		JSON_CRITICAL("detect error");
	#endif
}

void ejson::Document::CreateError(const etk::UString& _data, int32_t _pos, const ejson::filePos& _filePos, const etk::UString& _comment)
{
	m_comment = _comment;
	m_Line = _data.ExtractLine(_pos);
	m_filePos = _filePos;
	if (true==m_writeErrorWhenDetexted) {
		DisplayError();
	}
}

bool ejson::Document::IParse(const etk::UString& _data, int32_t& _pos, ejson::filePos& _filePos, ejson::Document& _doc)
{
	JSON_PARSE_ELEMENT("start parse : 'Value' ");
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		ejson::filePos tmpPos;
		if(    _data[iii]==' '
		    || _data[iii]=='\t'
		    || _data[iii]=='\n'
		    || _data[iii]=='\r') {
			// white space ==> nothing to do ...
		} else if (_data[iii]=='{') {
			// find an object:
			JSON_PARSE_ELEMENT("find Object");
			ejson::Object * tmpElement = new ejson::Object();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in object");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_subElement = tmpElement;
		} else if (_data[iii]=='"') {
			// find a string:
			JSON_PARSE_ELEMENT("find String quoted");
			ejson::String * tmpElement = new ejson::String(true);
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_subElement = tmpElement;
		} else if (_data[iii]=='[') {
			// find a list:
			JSON_PARSE_ELEMENT("find List");
			ejson::Array * tmpElement = new ejson::Array();
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in Array");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_subElement = tmpElement;
		} else if( CheckAvaillable(_data[iii]) ) {
			// find a string without "" ==> special hook for the etk-json parser
			JSON_PARSE_ELEMENT("find String");
			ejson::String * tmpElement = new ejson::String(false);
			if (NULL==tmpElement) {
				EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, "Allocation error in String");
				_pos=iii;
				return false;
			}
			tmpElement->IParse(_data, iii, _filePos, _doc);
			m_subElement = tmpElement;
		} else if(_data[iii]=='}') {
			// find end of value:
			_pos=iii; // ==> return the end element type ==> usefull to check end and check if adding element is needed
			return true;
		} else {
			// find an error ....
			EJSON_CREATE_ERROR(_doc, _data, iii, _filePos, etk::UString("Find '") + _data[iii] + "' with no element in the element...");
			// move the curent index
			_pos = iii+1;
			return false;
		}
	}
	return true;
}


ejson::Value* ejson::Document::GetSub(const etk::UString& _named) const
{
	if (m_subElement == NULL) {
		return NULL;
	}
	ejson::Object* tmp = m_subElement->ToObject();
	if (NULL==tmp) {
		return NULL;
	}
	return tmp->GetSub(_named);
}

ejson::Object* ejson::Document::GetSubObject(const etk::UString& _named) const
{
	ejson::Value* tmp = GetSub(_named);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->ToObject();
}

ejson::String* ejson::Document::GetSubString(const etk::UString& _named) const
{
	ejson::Value* tmp = GetSub(_named);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->ToString();
}

ejson::Array* ejson::Document::GetSubArray(const etk::UString& _named) const
{
	ejson::Value* tmp = GetSub(_named);
	if (NULL == tmp) {
		return NULL;
	}
	return tmp->ToArray();
}


bool ejson::Document::SetSub(ejson::Value* _value)
{
	if (NULL == _value) {
		return false;
	}
	if (NULL!=m_subElement) {
		delete(m_subElement);
	}
	m_subElement = _value;
	return true;
}

void ejson::Document::Clear(void)
{
	if (NULL!=m_subElement) {
		delete(m_subElement);
		m_subElement=NULL;
	}
}
