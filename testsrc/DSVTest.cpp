#include "XMLReader.h"
#include "StringDataSource.h"
#include "gtest/gtest.h"

TEST(DSVWriter, WriteRow) {
    std::string Base = "Hello";

    EXPECT_EQ(StringUtils::Slice(Base,0),"Hello");
    EXPECT_EQ(StringUtils::Slice(Base,1),"ello");
}

TEST(DSVWrite, )