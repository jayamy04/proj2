#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSource.h"
#include "gtest/gtest.h"

TEST(DSVWriter, WriteRow) {
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");
}

TEST(DSVReader, ReadRow) {
    auto Source = std::make_shared<CStringDataSource>("Hello&World!");
    CDSVReader Reader(Source,'&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"Hello");
    EXPECT_EQ(output[1],"World!");
}

