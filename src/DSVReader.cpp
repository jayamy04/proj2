#include "DSVReader.h"
#include <expat.h>
#include <queue>

CDSVReader(std::shared_ptr<CDataSource> src, char delimiter);
~CDSVReader();
bool End() const;
bool ReadRow(std::vector<std::string> &row);