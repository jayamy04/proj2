#include "XMLReader.h"
#include <expat.h>
#include <queue>


//most recent edits: 2/18/24 @ 2 ish

//be warned: making lots of comments to aid in my understanding :)





struct CXMLReader::SImplementation{              //SImplementation structure within CXMLReader class
    std::shared_ptr< CDataSource > DDataSource;  //shared pointer called DDataSource of type CDataSource
    XML_Parser DXMLParser;                       //declares DXMLParser of type XML_Parser -> XML_parser is a type from the Expat library
    std::queue<SXMLEntity> DEntityQueue;         //declares queue called DEntityQueue



    //member function of SImplementation, is called when XML parser encounters the start of an element
    void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs){   
        SXMLEntity TempEntity;   //creates a SXMLEntity object to represent the start element and adds to queue
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::StartElement;
        for (size_t Index = 0; Index < attrs.size(); Index += 2) {
            TempEntity.SetAttribute(attrs[Index], attrs[Index+1]);
        }
        DEntityQueue.push(TempEntity);
    }



    void EndElementHandler(const std::string &name) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::EndElement;
        DEntityQueue.push(TempEntity);

    }

    void CharacterDataHandler(const std::string &cdata) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = cdata;
        TempEntity.Dtype = SXMLEntity::EType::CharData;
        DEntityQueue.push(TempEntity);
    }



    //static member function that servesa as a callback to the expat library
    //gets called when the XML parser encounters the start of an element
    static void StartElementHandlerCallBack(void *context, const XML_Char *name, const XML_Char **atts){
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);   //type casts the context pointer to a SImplementation pointer 
        std::vector<std::string> Attributes;                                       //declares a vector called attributes to store names and values 
        auto AttrPtr = atts;                                                       //initializes the AttrPtr with the atts pointer
        while(*AttrPtr){                                                           //iterates through the attribute array until a null pointer
            Attributes.push_back(*AttrPtr);                                        //pushes current attribute name into the attributes pointer
            AttrPtr++;
        }
        ReaderObject -> StartElementHandler(name, Attributes);                     //calls the StartElementHandler pointer to by ReaderObject
                                                                                   //passes the XML element "name" and the vector of attributes to the startElementHandler function
    }


    //callback for the expact library, called when the XML parser encounters the end of an element
    static void EndElementHandlerCallBack(void *context, const XML_Char *name){
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);    //type cast of the context ptr to a ptr of type SImplementation
        ReaderObject->EndElementHandler(name);                                      //calls the EndElementHandler method of the SImp... object pointed to by ReaderObject
    };                                                                              //passes XML element "name"




    //callback for expat library, called when the XML parser encounters character data within an element
    static void CharacterDataHandlerCallback(void *context, const XML_Char *s, int len){      
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);        //type cast of the context ptr to a ptr of type SImplementation
        ReaderObject->CharacterDataHandler(std::string(s, len));                        //calls the characterDataHandler...
    };




    //the constructor of the SImplementation structure
    //takes a shared pointer to CDataSource 
    //creates a DXML_Parser and sets the callback functions 
    SImplementation(std::shared_ptr< CDataSource > src){
        DDataSource = src;
        DXMLParser = XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
        XML_SetUserData(DXMLParser, this);
    };



    bool CXMLReader::End() const{
        // attempt 1: return DDataSource->End() && DEntityQueue.empty();
        return DImplementation->End();
    };



    //reads an XML entity from the XML source
    //reads from DDataSource and passes it to XML_parse function and then fills the DEntityQueue
    //if the queue is not empty, it returns the front entity and removes it from the queue
    bool ReadEntity(SXMLEntity &entity, bool skipcdata){
        std::string DataBuffer;

        while(DEntityQueue.empty()) {
            if(DDataSource->Read(DataBuffer,256)) {
                XML_Parse(DXMLParser,DataBuffer.size()<256);
            }
            else {
                XML_Parse(DXMLParser,DataBuffer.data(),0,true);
            }
        }
    };
    if (DEntityQueue.empty()) {
        return false;
    }
    entity = DEntityQueue.front();
    DEntityQueue.pop();
    return true;
};


//initializes DImplementation, the unique pointer to SImplementation, with a shared pointer to CDataSource
CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) {
    DImplementation = std::make_unique< SImplementation >(src);
}