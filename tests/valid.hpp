#ifndef __VALID__HPP__
#define __VALID__HPP__

#include <string>
using std::string;
bool valid(std::string &query);

TEST(queryChecker, typical1) {
    string str1 = "Genres=Action AND NOT Actor=Harry";
    EXPECT_TRUE(valid(str1));
}

bool valid(std::string &query) {
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

    return true;
}


#endif