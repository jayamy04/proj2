#include "DSVWriter.h"

struct CDSVWriter::SImplementation {
    SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
        
    }

    bool WriteRow(const std::vector<std::string> &row) {

    }
};

    std::unique_ptr<SImplementation> DImplementation;

CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
    DImplementation = std::make_unique<SImplementation>(sink,delimiter,quoteall);
}

CDSVWriter::~CDSVWriter(){

}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
    return DImplementation->WriteRow(row);
}

CDSVWriter::~CDSVWriter(){

}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {

}
