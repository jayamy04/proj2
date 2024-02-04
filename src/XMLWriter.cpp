#include "XMLWriter.h"
#include <expat.h>
#include <queue>

CSMLWriter(std::shared_ptr<CDataSink> sink);

~CXMLWriter();

bool Flush();

bool WriteEntity(const SXMLEntity &entity);
