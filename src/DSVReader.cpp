#include "DSVReader.h"

CDSVReader(std::shared_ptr<CDataSource> src, char delimiter);
~CDSVReader();
bool End() const;
bool ReadRow(std::vector<std::string> &row);