#include <gtest/gtest.h>
#include "StringUtils.h"

//You want your tests to fail first
TEST(StringUtilsTest, SliceTest){
    std::string Base = "Hello";

    EXPECT_EQ(StringUtils::Slice(Base,0),"Hello");
    EXPECT_EQ(StringUtils::Slice(Base,1),"ello");
}  

TEST(StringUtilsTest, Capitalize){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::Capitalize(Base),"Hello");
    EXPECT_EQ(StringUtils::Capitalize(std::string()),"");
    EXPECT_EQ(StringUtils::Capitalize(" hello")," hello");
    EXPECT_EQ(StringUtils::Capitalize("HELLO"),"Hello"); 
}

TEST(StringUtilsTest, Upper){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::Upper(Base),"HELLO");
    EXPECT_EQ(StringUtils::Upper(std::string()),"");
    EXPECT_EQ(StringUtils::Upper(" hello")," HELLO");
    EXPECT_EQ(StringUtils::Upper("HELLO"),"HELLO"); 
}

TEST(StringUtilsTest, Lower){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::Lower(Base),"hello");
    EXPECT_EQ(StringUtils::Lower(std::string()),"");
    EXPECT_EQ(StringUtils::Lower(" hello")," hello");
    EXPECT_EQ(StringUtils::Lower("HELLO"),"hello");
}

TEST(StringUtilsTest, LStrip){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::LStrip(Base),"hello");
    EXPECT_EQ(StringUtils::LStrip(std::string()),"");
    EXPECT_EQ(StringUtils::LStrip(" hello"),"hello");
    EXPECT_EQ(StringUtils::LStrip("      hello"),"hello");
    EXPECT_EQ(StringUtils::LStrip("      hello    "),"hello    ");
    EXPECT_EQ(StringUtils::LStrip("      hel   lo    "),"hel   lo    ");
    EXPECT_EQ(StringUtils::LStrip("      hel   lo    lo      "),"hel   lo    lo      ");
    EXPECT_EQ(StringUtils::LStrip("    "),"");
}

TEST(StringUtilsTest, RStrip){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::RStrip(Base),"hello");
    EXPECT_EQ(StringUtils::RStrip(std::string()),"");
    EXPECT_EQ(StringUtils::RStrip(" hello")," hello");
    EXPECT_EQ(StringUtils::RStrip("      hello"),"      hello");
    EXPECT_EQ(StringUtils::RStrip("      hello    "),"      hello");
    EXPECT_EQ(StringUtils::RStrip("      hel   lo    "),"      hel   lo");
    EXPECT_EQ(StringUtils::RStrip("      hel   lo    lo      "),"      hel   lo    lo");
    EXPECT_EQ(StringUtils::RStrip("    "),"");
}

TEST(StringUtilsTest, Strip){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::Strip(Base),"hello");
    EXPECT_EQ(StringUtils::Strip(std::string()),"");
    EXPECT_EQ(StringUtils::Strip(" hello"),"hello");
    EXPECT_EQ(StringUtils::Strip("      hello"),"hello");
    EXPECT_EQ(StringUtils::Strip("      hello    "),"hello");
    EXPECT_EQ(StringUtils::Strip("      hel   lo    "),"hel   lo");
    EXPECT_EQ(StringUtils::Strip("      hel   lo    lo      "),"hel   lo    lo");
    EXPECT_EQ(StringUtils::Strip("    "),"");
}

// Returns the center/left/right justified strings
TEST(StringUtilsTest, Center){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::Center(Base, 6, ' '), "   hello   ");
    EXPECT_EQ(StringUtils::Center(Base, 7, ' '), "   hello    ");
}

TEST(StringUtilsTest, LJust){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::LJust(Base, 6, ' '), "hello      ");
    EXPECT_EQ(StringUtils::LJust(Base, 7, ' '), "hello       ");    
}

TEST(StringUtilsTest, RJust){
    std::string Base = "hello";

    EXPECT_EQ(StringUtils::RJust(Base, 6, ' '), "      hello");
    EXPECT_EQ(StringUtils::RJust(Base, 7, ' '), "       hello");    
}

// Returns the string str with all instances of old replaced with rep
TEST(StringUtilsTest, Replace){
    std::string Base = "a";
    EXPECT_EQ(StringUtils::Replace(Base, "a", "b"), "b");
    EXPECT_EQ(StringUtils::Replace("aa", "aa", "b"), "b");
    EXPECT_EQ(StringUtils::Replace("aaa", "a", "b"), "bbb");
    EXPECT_EQ(StringUtils::Replace(" aaa", " ", "b"), "baaa");
    EXPECT_EQ(StringUtils::Replace(" a  a a", "a  a", "b"), " b a");
}

// Splits the string up into a vector of strings based on splt parameter, if
// splt parameter is empty string, then split on white space
TEST(StringUtilsTest, Split){
    std::string Base = "bab";
    EXPECT_EQ(StringUtils::Split(Base, "a"), (std::vector<std::string>{"b", "b"}));
    EXPECT_EQ(StringUtils::Split("a a", " "), (std::vector<std::string>{"a", "a"}));
    EXPECT_EQ(StringUtils::Split("a a a", " "), (std::vector<std::string>{"a", "a", "a"}));
    EXPECT_EQ(StringUtils::Split("bb a a", " "), (std::vector<std::string>{"bb", "a", "a"}));
}

TEST(StringUtilsTest, Join){
    std::string Base = "a";
    EXPECT_EQ(StringUtils::Join(" ", (std::vector<std::string>{"b", "b"})), "b b");
    EXPECT_EQ(StringUtils::Join(" ", (std::vector<std::string>{"bb", "a", "a"})), "bb a a");
    EXPECT_EQ(StringUtils::Join(" ", (std::vector<std::string>{"a", "a", "a"})), "a a a");
    EXPECT_EQ(StringUtils::Join(" ", (std::vector<std::string>{"a", "a"})), "a a");
}

TEST(StringUtilsTest, ExpandTabs){
    std::string Base = "a";
    EXPECT_EQ(StringUtils::ExpandTabs("\ta", 3), "   a");
    EXPECT_EQ(StringUtils::ExpandTabs("\taaa", 3), "   aaa");
    EXPECT_EQ(StringUtils::ExpandTabs("\ta", 4), "    a");
    EXPECT_EQ(StringUtils::ExpandTabs("\ta\t", 3), "   a   ");
    EXPECT_EQ(StringUtils::ExpandTabs("\ta\t ", 3), "   a    ");
}

TEST(StringUtilsTest, EditDistance){
    std::string Base = "a";
    EXPECT_EQ(StringUtils::EditDistance("a", "b", true), 1);
    EXPECT_EQ(StringUtils::EditDistance("aaa", "bbb", false), 3);
    EXPECT_EQ(StringUtils::EditDistance("bb", "cccd", false), 4);
    EXPECT_EQ(StringUtils::EditDistance("pets", "cats", true), 2);
    EXPECT_EQ(StringUtils::EditDistance("bb", "Bccd", false), 4);
    EXPECT_EQ(StringUtils::EditDistance("bb", "Bccd", true), 3);
}
