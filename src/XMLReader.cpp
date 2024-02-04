#include "XMLReader.h"
#include <expat.h>

struct CXMLReader::SImplementation{
    std::shared_ptr< CDataSource > DDataSource;
    XML_Parser DXMLParser;

    void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs){

    }

    static void XML_StartElementHandlerCallBack(void *userData, const XML_Char *name, const XML_Char **atts);
        SInplementation *ReaderObject = static_cast<SImplementation *>(context);

    static void EndElementHandlerCallBack(void *context, const) XML_Char *name){

    };

    static void CharacterDataHandlerCallback(void *context, const XML_Char *s, int len){

    };

    SImplementation(std::shared_ptr< CDataSource > src){
        DDataSource = src;
        DXMLParser = XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, XML_StartElementHandler start);

    };

    bool End() const{

    };

    bool ReadEntity(SXMLEntity &entity, bool skipcdata){

    };
};