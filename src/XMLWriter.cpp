#include "XMLWriter.h"
#include <expat.h>
#include <queue>

CXMLWriter(std::shared_ptr<CDataSink> sink);

~CXMLWriter();


//outputs all end elements for those that have been started
bool Flush();


//writes out the entity to the output stream
bool WriteEntity(const SXMLEntity &entity);
