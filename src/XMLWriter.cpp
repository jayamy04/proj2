#include "XMLWriter.h"
#include <expat.h>
#include <queue>


//most recent edits: 2/18/24 @ 2 ish

//constructor
CXMLWriter::CXMLWriter(std::shared_ptr<CDataSink> sink) {
    DImplementation = std::make_unique<SImplementation>(sink);
}


//destructor
CXMLWriter::~CXMLWriter();


//outputs all end elements for those that have been started
bool CXMLWriter::Flush(){
    return DImplementation->Flush();
}


//writes out the entity to the output stream
bool CXMLWriter::WriteEntity(const SXMLEntity &entity){
    return DImplementation->WriteEntity(entity);
}


//implementation of SImplementation specifically for CXMLWriter class
struct CXMLWriter::SImplementation{
    std::shared_ptr<CDataSink> DSink;  //shared ptr to data sink
    std::queue<SXMLEntity> DEndElementQueue;  //queue to store elements that have been started

    //constructor
    SImplementation(std::shared_ptr<CDataSink> sink) : DSink(sink) {}

    //flushes all end elements that have been started
    bool Flush() {
        //Write all end elements to the data sink
        while (!DEndElementQueue.empty()){
            SXMLEntity entity = DEndElementQueue.front();
            if (!DSink->Write(entity)){
                return false; //coun't write to data sink
            }
            DEndElementQueue.pop();
        }
        return true;
    }

    //writes given XML Entity to the output stream
    bool WriteEntity(const SXMLEntity &entity) {
        //writes the entity to the data sink
        if (!DSink->Write(entity)) {
            return false; //unable to write to the data sink

        }

        //if start element, push to the end element queue
        if (entity.DType == SXMLEntity::EType::StartElement) {
            DEndElementQueue.push(entity);
        }
        //if end element, pop corresponding end element from queue
        else if (entity.DType == SXMLEntity::EType::EndElement) {
            if (!DEndElements.empty()) {
                DEndElementQueue.pop();
            }
            else{
                //no corresponding start element in the queue
                return false;
            }
        }

        return true;
    }

};
