#include "DSVWriter.h"

struct CDSVWriter::SImplmentation{
    SImplementation(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall) {
        //Details here
    }

    bool WriteRow(const std::vector<std::string> &row){

    }
};
        std::unique_ptr<SImplementation> DImplmentation;

CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall) {
    DImplementation = std::make_unique<SImplementation> (sink,delimiter,quoteall);

}

CDSVWriter::~CDSVWriter(){

}

bool CDSVWriter::WriterRow(const std::vector<std::string> &row) {
    return DImplementation ->WriteRow(row);
}