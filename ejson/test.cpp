/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/Debug.h>
#include <etk/Vector.h>
#include <etk/UString.h>
#include <ejson/debug.h>
#include <ejson/ejson.h>

#undef __class__
#define __class__	"ejson::test"

class testCheck
{
	public:
		etk::UString m_ref;
		etk::UString m_input;
		int32_t m_errorPos; // -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
		testCheck(void) {};
		void Set(const etk::UString& _ref, int32_t _pos, const etk::UString& _input)
		{
			m_ref = _ref;
			m_input = _input;
			m_errorPos = _pos;
		}
};

etk::Vector<testCheck> l_list;

void Init(void)
{
	etk::UString reference;
	etk::UString input;
	testCheck check;
	
	// ======================================================
	check.Set("test ejson::Doc", -2, "");
	l_list.PushBack(check);
	// ======================================================
	reference = "{\n}\n";
	check.Set(reference,
	          -1,
	          "{}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{    \t\r   }\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test ejson::all", -2, "");
	l_list.PushBack(check);
	// ======================================================
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": {\n"
	            "				\"value\": \"Close\",\n"
	            "				\"onclick\": \"CloseDoc()\"\n"
	            "			}\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n"
	            "	\"menu\": {\n"
	            "		\"id\": \"file\",\n"
	            "		\"value\": \"File\",\n"
	            "		\"popup\": {\n"
	            "			\"menuitem\": [\n"
	            "				{\n"
	            "					\"value\": \"Close\",\n"
	            "					\"onclick\": \"CloseDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"New\",\n"
	            "					\"onclick\": \"CreateNewDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"Open\",\n"
	            "					\"onclick\": \"OpenDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					\"value\": \"Close\",\n"
	            "					\"onclick\": \"CloseDoc()\"\n"
	            "				}\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n";
	check.Set(reference,
	          -1,
	          reference);
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{\n"
	            "	menu: {\n"
	            "		id: file,\n"
	            "		value: File,\n"
	            "		popup: {\n"
	            "			menuitem: [\n"
	            "				{\n"
	            "					value: Close,\n"
	            "					onclick: \"CloseDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: New,\n"
	            "					onclick: \"CreateNewDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: Open,\n"
	            "					onclick: \"OpenDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: Close,\n"
	            "					onclick: \"CloseDoc()\"\n"
	            "				}\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n");
	l_list.PushBack(check);
}

int main(int argc, const char *argv[])
{
	GeneralDebugSetLevel(etk::LOG_LEVEL_VERBOSE);
	Init();
	int32_t countError = 0;
	int32_t countSeparator = 0;
	int32_t sectionID = 0;
	for (int32_t iii=0 ; iii<l_list.Size() ; iii++) {
		int32_t jjj= iii-countSeparator+1;
		if (l_list[iii].m_errorPos==-2) {
			countSeparator++;
			sectionID = 0;
			JSON_INFO("-------------------------------------------------------------");
			JSON_INFO("-- " << l_list[iii].m_ref);
			JSON_INFO("-------------------------------------------------------------");
			continue;
		}
		sectionID++;
		ejson::Document doc;
		etk::UString out("");
		//JSON_DEBUG("parse : \n" << l_list[iii].m_input);
		if (false==doc.Parse(l_list[iii].m_input)) {
			if (l_list[iii].m_errorPos==1) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Parsing in error (correct result)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be OK");
				JSON_ERROR("parse : \n" << l_list[iii].m_input);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==1) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be in error ...");
			JSON_ERROR("parse : \n" << l_list[iii].m_input);
			doc.Display();
			countError++;
			continue;
		}
		if (false == doc.Generate(out)) {
			if (l_list[iii].m_errorPos==2) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } generate in error (correct result)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generate output might be OK");
				JSON_ERROR("generate : \n" << out);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==2) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generating might be in error ...");
			countError++;
			continue;
		}
		if (l_list[iii].m_ref != out) {
			if (l_list[iii].m_errorPos==3) {
				JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Result in error (normal case)");
			} else {
				JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } different output");
				JSON_ERROR("generate : \n" << out);
				JSON_ERROR("reference : \n" << l_list[iii].m_ref);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==3) {
			JSON_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR} checking result might be in error...");
			JSON_ERROR("generate : \n" << out);
			JSON_ERROR("reference : \n" << l_list[iii].m_ref);
			countError++;
			continue;
		}
		JSON_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  }");
	}
	if (countError>0) {
		JSON_ERROR("[TEST] produce " << countError << " error on " << l_list.Size()-countSeparator << " test");
	} else {
		JSON_INFO("[TEST] produce " << countError << " error on " << l_list.Size()-countSeparator << " test");
	}
	return 0;
}

