#include "XMLReader.h"
#include <expat.h>

struct CXMLReader::SImplementation{
    std::shared_ptr< CDataSource > DDataSource;
    XML_Parser DXMLParser;

    void XML_StartElementHandlerCallBack(void *userData, const XML_Char *name, const XML_Char **atts);

    SImplementation(std::shared_ptr< CDataSource > src){
        DDataSource = src;
        DXMLParser = XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, XML_StartElementHandler start);

    };

    bool End() const{

    };

    bool ReadEntity(SXMLEntity &entity, bool skipdata){

    };
};