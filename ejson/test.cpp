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
	check.Set("test ejson::null", -2, "");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": null\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:null }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:null \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:null\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test ejson::boolean", -2, "");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": true\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:true }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:true \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:true\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": false\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:false }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:false \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:false\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test ejson::number", -2, "");
	l_list.PushBack(check);
	// ------------------------------------------------------
	reference = "{\n\t\"tmpElement\": 956256.000000\n}\n";
	check.Set(reference,
	          -1,
	          "{ tmpElement:956256 }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "{ \t\ntmpElement:956256 \t\n }\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "tmpElement:956256\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": 956256.000000\n}\n",
	          -1,
	          "{tmpElement:956256}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": -956256.000000\n}\n",
	          -1,
	          "{tmpElement:-956256}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": -956256.000000\n}\n",
	          -1,
	          "{tmpElement:-956256}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("{\n\t\"tmpElement\": -956.256000\n}\n",
	          -1,
	          "{tmpElement:-956.256}\n");
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
	            "		id: \"file\",\n"
	            "		value: \"File\",\n"
	            "		popup: {\n"
	            "			menuitem: [\n"
	            "				{\n"
	            "					value: \"Close\",\n"
	            "					onclick: \"CloseDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: \"New\",\n"
	            "					onclick: \"CreateNewDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: \"Open\",\n"
	            "					onclick: \"OpenDoc()\"\n"
	            "				},\n"
	            "				{\n"
	            "					value: \"Close\",\n"
	            "					onclick: \"CloseDoc()\"\n"
	            "				}\n"
	            "			]\n"
	            "		}\n"
	            "	}\n"
	            "}\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	            "menu: {\n"
	            "	id: \"file\",\n"
	            "	value: \"File\",\n"
	            "	popup: {\n"
	            "		menuitem: [\n"
	            "			{\n"
	            "				value: \"Close\",\n"
	            "				onclick: \"CloseDoc()\"\n"
	            "			},\n"
	            "			{\n"
	            "				value: \"New\",\n"
	            "				onclick: \"CreateNewDoc()\"\n"
	            "			},\n"
	            "			{\n"
	            "				value: \"Open\",\n"
	            "				onclick: \"OpenDoc()\"\n"
	            "			},\n"
	            "			{\n"
	            "				value: \"Close\",\n"
	            "				onclick: \"CloseDoc()\"\n"
	            "			}\n"
	            "		]\n"
	            "	}\n"
	            "}\n");
	l_list.PushBack(check);
	
//////////////////////////////////////////////////////////////////////////
	"
	{
    \"glossary\": {
        \"title\": \"example glossary\",
		\"GlossDiv\": {
            \"title\": \"S\",
			\"GlossList\": {
                \"GlossEntry\": {
                    \"ID\": \"SGML\",
					\"SortAs\": \"SGML\",
					\"GlossTerm\": \"Standard Generalized Markup Language\",
					\"Acronym\": \"SGML\",
					\"Abbrev\": \"ISO 8879:1986\",
					\"GlossDef\": {
                        \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",
						\"GlossSeeAlso\": [\"GML\", \"XML\"]
                    },
					\"GlossSee\": \"markup\"
                }
            }
        }
    }
}
"
//////////////////////////////////////////////////////////////////////////
"
{\"menu\": {
  \"id\": \"file\",
  \"value\": \"File\",
  \"popup\": {
    \"menuitem\": [
      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},
      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},
      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}
    ]
  }
}}
"
//////////////////////////////////////////////////////////////////////////
"
{\"widget\": {
    \"debug\": \"on\",
    \"window\": {
        \"title\": \"Sample Konfabulator Widget\",
        \"name\": \"main_window\",
        \"width\": 500,
        \"height\": 500
    },
    \"image\": { 
        \"src\": \"Images/Sun.png\",
        \"name\": \"sun1\",
        \"hOffset\": 250,
        \"vOffset\": 250,
        \"alignment\": \"center\"
    },
    \"text\": {
        \"data\": \"Click Here\",
        \"size\": 36,
        \"style\": \"bold\",
        \"name\": \"text1\",
        \"hOffset\": 250,
        \"vOffset\": 100,
        \"alignment\": \"center\",
        \"onMouseUp\": \"sun1.opacity = (sun1.opacity / 100) * 90;\"
    }
}}    
"

//////////////////////////////////////////////////////////////////////////




"
{\"web-app\": {
  \"servlet\": [   
    {
      \"servlet-name\": \"cofaxCDS\",
      \"servlet-class\": \"org.cofax.cds.CDSServlet\",
      \"init-param\": {
        \"configGlossary:installationAt\": \"Philadelphia, PA\",
        \"configGlossary:adminEmail\": \"ksm@pobox.com\",
        \"configGlossary:poweredBy\": \"Cofax\",
        \"configGlossary:poweredByIcon\": \"/images/cofax.gif\",
        \"configGlossary:staticPath\": \"/content/static\",
        \"templateProcessorClass\": \"org.cofax.WysiwygTemplate\",
        \"templateLoaderClass\": \"org.cofax.FilesTemplateLoader\",
        \"templatePath\": \"templates\",
        \"templateOverridePath\": \"\",
        \"defaultListTemplate\": \"listTemplate.htm\",
        \"defaultFileTemplate\": \"articleTemplate.htm\",
        \"useJSP\": false,
        \"jspListTemplate\": \"listTemplate.jsp\",
        \"jspFileTemplate\": \"articleTemplate.jsp\",
        \"cachePackageTagsTrack\": 200,
        \"cachePackageTagsStore\": 200,
        \"cachePackageTagsRefresh\": 60,
        \"cacheTemplatesTrack\": 100,
        \"cacheTemplatesStore\": 50,
        \"cacheTemplatesRefresh\": 15,
        \"cachePagesTrack\": 200,
        \"cachePagesStore\": 100,
        \"cachePagesRefresh\": 10,
        \"cachePagesDirtyRead\": 10,
        \"searchEngineListTemplate\": \"forSearchEnginesList.htm\",
        \"searchEngineFileTemplate\": \"forSearchEngines.htm\",
        \"searchEngineRobotsDb\": \"WEB-INF/robots.db\",
        \"useDataStore\": true,
        \"dataStoreClass\": \"org.cofax.SqlDataStore\",
        \"redirectionClass\": \"org.cofax.SqlRedirection\",
        \"dataStoreName\": \"cofax\",
        \"dataStoreDriver\": \"com.microsoft.jdbc.sqlserver.SQLServerDriver\",
        \"dataStoreUrl\": \"jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon\",
        \"dataStoreUser\": \"sa\",
        \"dataStorePassword\": \"dataStoreTestQuery\",
        \"dataStoreTestQuery\": \"SET NOCOUNT ON;select test='test';\",
        \"dataStoreLogFile\": \"/usr/local/tomcat/logs/datastore.log\",
        \"dataStoreInitConns\": 10,
        \"dataStoreMaxConns\": 100,
        \"dataStoreConnUsageLimit\": 100,
        \"dataStoreLogLevel\": \"debug\",
        \"maxUrlLength\": 500}},
    {
      \"servlet-name\": \"cofaxEmail\",
      \"servlet-class\": \"org.cofax.cds.EmailServlet\",
      \"init-param\": {
      \"mailHost\": \"mail1\",
      \"mailHostOverride\": \"mail2\"}},
    {
      \"servlet-name\": \"cofaxAdmin\",
      \"servlet-class\": \"org.cofax.cds.AdminServlet\"},
 
    {
      \"servlet-name\": \"fileServlet\",
      \"servlet-class\": \"org.cofax.cds.FileServlet\"},
    {
      \"servlet-name\": \"cofaxTools\",
      \"servlet-class\": \"org.cofax.cms.CofaxToolsServlet\",
      \"init-param\": {
        \"templatePath\": \"toolstemplates/\",
        \"log\": 1,
        \"logLocation\": \"/usr/local/tomcat/logs/CofaxTools.log\",
        \"logMaxSize\": \"\",
        \"dataLog\": 1,
        \"dataLogLocation\": \"/usr/local/tomcat/logs/dataLog.log\",
        \"dataLogMaxSize\": \"\",
        \"removePageCache\": \"/content/admin/remove?cache=pages&id=\",
        \"removeTemplateCache\": \"/content/admin/remove?cache=templates&id=\",
        \"fileTransferFolder\": \"/usr/local/tomcat/webapps/content/fileTransferFolder\",
        \"lookInContext\": 1,
        \"adminGroupID\": 4,
        \"betaServer\": true}}],
  \"servlet-mapping\": {
    \"cofaxCDS\": \"/\",
    \"cofaxEmail\": \"/cofaxutil/aemail/*\",
    \"cofaxAdmin\": \"/admin/*\",
    \"fileServlet\": \"/static/*\",
    \"cofaxTools\": \"/tools/*\"},
 
  \"taglib\": {
    \"taglib-uri\": \"cofax.tld\",
    \"taglib-location\": \"/WEB-INF/tlds/cofax.tld\"}}}
    
"
//////////////////////////////////////////////////////////////////////////

"
{\"menu\": {
    \"header\": \"SVG Viewer\",
    \"items\": [
        {\"id\": \"Open\"},
        {\"id\": \"OpenNew\", \"label\": \"Open New\"},
        null,
        {\"id\": \"ZoomIn\", \"label\": \"Zoom In\"},
        {\"id\": \"ZoomOut\", \"label\": \"Zoom Out\"},
        {\"id\": \"OriginalView\", \"label\": \"Original View\"},
        null,
        {\"id\": \"Quality\"},
        {\"id\": \"Pause\"},
        {\"id\": \"Mute\"},
        null,
        {\"id\": \"Find\", \"label\": \"Find...\"},
        {\"id\": \"FindAgain\", \"label\": \"Find Again\"},
        {\"id\": \"Copy\"},
        {\"id\": \"CopyAgain\", \"label\": \"Copy Again\"},
        {\"id\": \"CopySVG\", \"label\": \"Copy SVG\"},
        {\"id\": \"ViewSVG\", \"label\": \"View SVG\"},
        {\"id\": \"ViewSource\", \"label\": \"View Source\"},
        {\"id\": \"SaveAs\", \"label\": \"Save As\"},
        null,
        {\"id\": \"Help\"},
        {\"id\": \"About\", \"label\": \"About Adobe CVG Viewer...\"}
    ]
}}
"
//////////////////////////////////////////////////////////////////////////


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

