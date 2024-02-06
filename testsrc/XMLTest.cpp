#include "gtest/gtest.h"
#include "XMLWriter.h"
#include "XMLReader.h"
#include "StringDataSource.h"

TEST(XMLWriter, ) {
auto OutputStream = std::make_shared<CStringDataSink>();
CXMLWriter Writer(OutputStream);

EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "example", {}}));

EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"></example>");
}

TEST(XMLReader, ) {
auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
CXMLReader Reader(InputStream);
SXMLEntity E;

EXPECT_TRUE(Reader.ReadEntity(E));
EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
EXPECT_EQ(E.AttributeValue("attr"), "Hello World");

EXPECT_TRUE(Reader.ReadEntity(E));
EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}