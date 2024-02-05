#include "XMLWriter.h"
#include <expat.h>
#include <queue>

CXMLWriter(std::shared_ptr<CDataSink> sink);

~CXMLWriter();

bool Flush();

bool WriteEntity(const SXMLEntity &entity);
