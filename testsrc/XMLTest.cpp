#include "gtest/gtest.h"
#include "XMLWriter.h"
#include "XMLReader.h"
#include "StringDataSource.h"
#include "StringDataSink.h"
#include "gtest/gtest.h"

////most recent edits: 2/18/24 @ 2:30 ish

TEST(XMLTest, WriteEntity) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    //test writing a simple XML entity
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "example", {}}));

    //verify the output
    EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"></example>");
}

TEST(XMLTest, ReadEntity) {
    auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
    CXMLReader Reader(InputStream);
    SXMLEntity entity;

    //test reading a simple XML Entity
    EXPECT_TRUE(Reader.ReadEntity(entity));
    EXPECT_EQ(entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(entity.AttributeValue("attr"), "Hello World");

    EXPECT_TRUE(Reader.ReadEntity(entity));
    EXPECT_EQ(entity.DType, SXMLEntity::EType::EndElement);
}


TEST(XMLTest, ErrorHandling) {
    //testing for invalid XML
    auto InputStream = std::make_shared<CStringDataSource>("example attr=\"Hello World\">");
    CXMLReader reader(InputStream);
    SXMLEntity entity;

    //incomplete or malformed XML should fail
    EXPECT_FALSE(reader.ReadEntity(entity));

}


TEST(XMLTest, LargeXML) {
    //test for reading and writing large XML 
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter writer(OutputStream);

    //write large XML
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(writer.WriteEntity({SXMLEntity::EType::StartElement, "item", {{"id", std::to_string(i)}}}));
        EXPECT_TRUE(writer.WriteEntity({SXMLEntity::EType::CharData, "", {}, "This is an item " + std::to_string(i)}));
        EXPECT_TRUE(writer.WriteEntity({SXMLEntity::EType::EndElement, "item", {}}));
    }

    //read the large XML
    auto InputStream = std::make_shared<CStringDataSource>(OutputStream->String());
    CXMLReader reader(InputStream);
    SXMLEntity entity;

    for(int i = 0; i < 10000; ++i){
        EXPECT_TRUE(reader.ReadEntity(entity));
        EXPECT_EQ(entity.DType, SXMLEntity::EType::StartElement);
        EXPECT_EQ(entity.AttributeValue("id"), std::to_string(i));

        EXPECT_TRUE(reader.ReadEntity(entity));
        EXPECT_EQ(entity.DType, SXMLEntity::EType::CharData);
        EXPECT_EQ(entity.DNameData, "This is item " + std::to_string(i));

        EXPECT_TRUE(reader.ReadEntity(entity));
        EXPECT_EQ(entity.DType, SXMLEntity::EType::EndElement);
    }
}
//__________________________________________________________________________________________________________________________
//more test cases to consider adding:

/*  - edge cases -> special characters, empty attributes, nested elements, etc
    - boundary cases -> max depth or size
    
    */

