#ifndef __VALID__HPP__
#define __VALID__HPP__

#include <string>
using std::string;
bool valid(std::string &query);

TEST(queryChecker, typical1) {
    string str1 = "Genres=Action AND NOT Actor=Harry";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, typical2) {
    string str1 = "genres=Action AND NOT actor=Harry";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, typical3) {
    string str1 = "GENRES=Action AND NOT ACTOR=Harry";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, typical4) {
    string str1 = "not genres=Action and genres=Drama";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, typical5) {
    string str1 = "NOT geNREs=Family AND genres=Drama";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, typical6) {
    string str1 = "NOT geNREs=Action AND genres=Drama or title=ten and ACtoR=Chris";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, typical7) {
    string str1 = "NOT Genres=Adventure OR Actor=Harry";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, typical8) {
    string str1 = "Genres=Action AND not Title=Hard OR Actor=Harry";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, invalid1) {
    string str1 = "Genres Action AND NOT Title Hard OR Actor Harry";
    EXPECT_FALSE(valid(str1));
}

TEST(queryChecker, invalid2) {
    string str1 = "AND Genres=Fantasy AND NOT Title=Hard OR Actor=Harry";
    EXPECT_FALSE(valid(str1));
}

TEST(queryChecker, invalid3) {
    string str1 = "Genres=Action AND Title=Hard OR Actor=Harry AND";
    EXPECT_FALSE(valid(str1));
}

TEST(queryChecker, invalid4) {
    string str1 = "Genres=Action AND NOT NOT Actor=Harry";
    EXPECT_FALSE(valid(str1));
}

TEST(queryChecker, invalid5) {
    string str1 = "Genres=Drama AND OR NOT Title=ea OR Actor=Terry";
    EXPECT_FALSE(valid(str1));
}

TEST(queryChecker, invalid6) {
    string str1 = "Genres=Thriller OR AND NOT Title=a OR Actor=Marry";
    EXPECT_FALSE(valid(str1));
}

TEST(queryChecker, edge_valid) {
    string str1 = "";
    EXPECT_TRUE(valid(str1));
}

TEST(queryChecker, edge_valid2) {
    string str1 = "=";
    EXPECT_TRUE(valid(str1));
}


bool valid(std::string &query) {
    if(query == "") return true;
    std::set<std::string> logicOps = { "NOT", "not", "AND", "and", "OR", "or"};
    //All queries must have an '='
    if(query.find('=') == string::npos) return false;
    //Query cannot begin with a binary operator (AND or OR)
    std::stringstream s(query);
	  std::string word = "";
    s >> word;
    if(word == "AND" || word == "and" || word == "OR" || word == "or") return false;
    //If an element in the query is not an operator, then it must contain '='
    if(word != "NOT" && word != "not" && word.find('=') == string::npos) return false;
    while(s >> word)
    {
        //if(word != "NOT" && word != "not" && word != "AND" && word != "and" && word != "OR" && word != "or") 
        if(logicOps.find(word) == logicOps.end()) {
            if(word.find('=') == string::npos) return false;
        }
    }
    //Query cannot end with an operator
    //if(word == "NOT" || word == "AND" || word == "OR" || word == "or" || word == "and" || word == "not") return false;
    if(logicOps.find(word) != logicOps.end()) return false;

    /*NO binary operator should be immedidately followed by another binary operator
    e.g. Genre=Action AND OR Actor=Elizabeth IS INVALID
    Operator NOT cannot be followed by another operator
    e.g. "NOT NOT Genre=Action" is not allowed, "Genre=Action AND NOT OR Actor=Matt" is invalid
    */
    std::stringstream s2(query);
    while(s2 >> word)
    {
        if(logicOps.find(word) != logicOps.end()) {
            if(word == "NOT" || word == "not") {
              s2 >> word;
              if( logicOps.find(word) != logicOps.end() ) return false;
            }
            else {
              s2 >> word;
              if(word == "AND" || word == "and" || word == "OR" || word == "or" ) return false;
            }
        }
    }

    std::stringstream s3(query);  //Explicitly checks for double negations "not not" because
    while(s3 >> word)             //the previous check might fail to to do for certain cases(i.e. "Genres=Action AND NOT NOT Actor=Harry")
    {                               
      if(word == "NOT" || word == "not") {
        s3 >> word;
        if( logicOps.find(word) != logicOps.end() ) return false;
      }
    }
    
    return true;
}


#endif
