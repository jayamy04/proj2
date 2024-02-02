#include "StringUtils.h"
#include <algorithm>
#include <cctype>

namespace StringUtils{

// Returns a substring of the string str, allows for negative values as in
// python end == 0 means to include end of string
std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    // Replace code here
    return str.substr(start,str.length()-start);
}

// Returns the capitalized string as in python
std::string Capitalize(const std::string &str) noexcept{
    auto Copy = str;
    
    // Replace code here
    Copy[0] = toupper(str[0]);
    for(size_t Index = 1; Index < Copy.length(); Index++) {
        Copy[Index] = tolower(Copy[Index]);
    }
    return Copy;
}

std::string Upper(const std::string &str) noexcept{
    auto Copy = str;
    
    // Replace code here
    for(size_t Index = 0; Index < Copy.length(); Index++) {
        Copy[Index] = toupper(Copy[Index]);
    }
    return Copy;
}

// Returns the upper- or lower-case strings as in python
std::string Lower(const std::string &str) noexcept{
    auto Copy = str;
    
    // Replace code here
    for(size_t Index = 0; Index < Copy.length(); Index++) {
        Copy[Index] = tolower(Copy[Index]);
    }
    return Copy;
}

// Returns the left/right/both stripped strings (white space characters are
// removed from left, right or both) 
std::string LStrip(const std::string &str) noexcept{
    auto Copy = str;

    // Replace code here
    for(size_t Index = 0; Index < Copy.length(); Index++) {
        if (isspace(Copy[Index])) {
            Copy.erase(Index, 1);
            Index -= 1;
        }
        else {
            return Copy;
        }
    }
    return Copy;
}

std::string RStrip(const std::string &str) noexcept{
    auto Copy = str;

    // Replace code here
    for(size_t Index = Copy.length()-1; Index >= 0; Index--) {
        if (isspace(Copy[Index])) {
            Copy.erase(Index, 1);
        }
        else {
            return Copy;
        }
    }
    return Copy;
}

std::string Strip(const std::string &str) noexcept{
    auto Copy = str;

    // Replace code here
    for(size_t Index = 0; Index < Copy.length(); Index++) {
        if (isspace(Copy[Index])) {
            Copy.erase(Index, 1);
            Index -= 1;
        }
        else {
            for(size_t Index = Copy.length()-1; Index >= 0; Index--) {
                if (isspace(Copy[Index])) {
                    Copy.erase(Index, 1);
                }
                else {
                    return Copy;
                }
            }
        }
    }
    return Copy;
}

// Returns the center justified strings
std::string Center(const std::string &str, int width, char fill) noexcept{
    // Replace code here
    auto Copy = str;

    if (width % 2 !=0) {
        Copy = std::string((width-1)/2, fill) + Copy + std::string(((width-1)/2)+1, fill);
    } else {
        Copy = std::string(width/2, fill) + Copy + std::string((width/2), fill);
    }
    return Copy;
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    // Replace code here
    auto Copy = str;
    Copy = Copy + std::string(width, fill);
    return Copy;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    // Replace code here
    auto Copy = str;
    Copy = std::string(width, fill) + Copy;
    return Copy;
}

// Returns the string str with all instances of old replaced with rep
std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    // Replace code here
    auto Copy = str;
    size_t Index = 0;
    size_t z = 0;

    while (Copy.find(old, Index) != std::string::npos) {
        z = Copy.find(old, Index);
        Copy.replace(z, old.length(), rep);
        Index ++;
    }
    return Copy;
}

// Splits the string up into a vector of strings based on splt parameter, if
// splt parameter is empty string, then split on white space
std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> vect;
    auto Copy = str;
    size_t Index = 0;
    size_t z = 0;
    while (Copy.find(splt, Index) != std::string::npos) {
        z = Copy.find(splt, Index);
        vect.push_back(Copy.substr(Index, z-Index));
        Index = z+1;
    }
    vect.push_back(Copy.substr(Index));

    return vect;
}

// Joins a vector of strings into a single string
std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    // Replace code here
    auto Copy = str;
    std::string joined;

    joined += vect[0];
    for (size_t z = 1; z < vect.size(); z++) {
        joined += str + vect[z];
    }
    return joined;
}

// Replaces tabs with spaces aligning at the tabstops
std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    // Replace code here
    auto Copy = str;
    size_t Index = 0;
    size_t z = 0;

    while (Copy.find("\t", Index) != std::string::npos) {
        z = Copy.find("\t", Index);
        Copy.replace(z, 1, std::string(tabsize, ' '));
        Index ++;
    }
    return Copy;
}

// Calculates the Levenshtein distance (edit distance) between the two
// strings. See https://en.wikipedia.org/wiki/Levenshtein_distance for
// more information.
int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    size_t r = left.length();
    size_t c = right.length();
    auto LeftCopy = left;
    auto RightCopy = right;
    int d[r][c];
    int substitutionCost = 0;

    if (ignorecase == true) {
        for(size_t Index = 0; Index < left.length(); Index++) {
            LeftCopy[Index] = tolower(left[Index]);
        }
        for(size_t Index = 0; Index < right.length(); Index++) {
            RightCopy[Index] = tolower(right[Index]);
        }
    }

    // setting all values in matrix to zero
    for (size_t Index = 0; Index < r; Index++) {
        for (size_t z = 0; z < c; z++) {
            d[Index][z] = 0;
        }
    } 

    for (int i=1; i <= r; i++) {
        d[i][0] = i;
    }
    for (int i=1; i <= c; i++) {
        d[0][i] = i;
    }

    for (int y=1; y<=r; y++) {
        for (int z=1; z<=c; z++) {
            if (LeftCopy[y-1] == RightCopy[z-1]) {
                substitutionCost = 0;
            }
            else {
                substitutionCost = 1;
            }
            d[y][z] = std::min({d[y-1][z] + 1, d[y][z-1]+1, d[y-1][z-1] + substitutionCost});
        }
    }

    return d[r][c];
}
};