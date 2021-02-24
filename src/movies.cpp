#include "../header/movies.hpp"
#include "../header/select.hpp"

#include <string>
#include <iostream>
#include <cstdint>
#include <memory>
#include <sstream>

#include <jsoncpp/json/json.h>
#include <curl/curl.h>

using namespace std;

void Movies::set_selection(Select* new_select) {
    delete select;
    select = new_select;
}

bool Movies::search(std::string& query) {
    if(!valid(query)) return false;
	std::stringstream stream(query);
	std::string word = "";
    while (stream >> word)
    {
        if(word == "NOT") {
            stream >> word;
            unsigned i = word.find('=');
            std::string left = word.substr(0,i);    //left is column name
            std::string right = word.substr(i+1,word.size()-1); //right is desired criterion
            set_selection(new Select_Not(new Select_Contains(this, left, right)));
        }
        else if(word == "AND") {
            stream >> word;
            if(word == "NOT") {
                stream >> word;
                unsigned i = word.find('=');
                std::string left = word.substr(0,i);    
                std::string right = word.substr(i+1,word.size()-1);
                set_selection( new Select_And(select, new Select_Not(new Select_Contains(this, left, right))) );
            }
            else {
                unsigned i = word.find('=');
                std::string left = word.substr(0,i);
                std::string right = word.substr(i+1,word.size()-1);
                set_selection(new Select_And(select, new Select_Contains(this,left,right))); 
            }
        }
        else if(word == "OR") {
            stream >> word;
            if(word == "NOT") {
                stream >> word;
                unsigned i = word.find('=');
                std::string left = word.substr(0,i);    
                std::string right = word.substr(i+1,word.size()-1);
                set_selection( new Select_Or(select, new Select_Not(new Select_Contains(this, left, right))) );
            }
            else {
                unsigned i = word.find('=');
                std::string left = word.substr(0,i);
                std::string right = word.substr(i+1,word.size()-1);
                set_selection(new Select_Or(select, new Select_Contains(this,left,right))); 
            }
        }
        else {
            unsigned i = word.find('=');
            std::string left = word.substr(0,i);    //left is column name
            std::string right = word.substr(i+1,word.size()-1); //right is desired criterion
            set_selection(new Select_Contains(this, left, right));
        }
    }

    return true;
}

bool Movies::valid(std::string &query) {
    //All queries must have an '='
    if(query.find('=') == string::npos) return false;
    //Query cannot begin with a binary operator (AND or OR)
    std::stringstream s(query);
	std::string word = "";
    s >> word;
    if(word == "AND" || word == "OR") return false;
    //If an element in the query is not an operator, then it must contain '='
    if(word != "NOT" && word.find('=') == string::npos) return false;
    while(s >> word)
    {
        if(word != "NOT" && word != "AND" && word != "OR") {
            if(word.find('=') == string::npos) return false;
        }
    }
    //Query cannot end with an operator
    if(word == "NOT" || word == "AND" || word == "OR") return false;
    /*NO binary operator should be immedidately followed by another binary operator
    e.g. Genre=Action AND OR Actor=Elizabeth IS INVALID
    Operator NOT cannot be followed by another operator
    e.g. "NOT NOT Genre=Action" is not allowed, "Genre=Action AND NOT OR Actor=Matt" is invalid
    */
    std::stringstream s2(query);
    while(s >> word)
    {
        if(word == "AND" || word == "OR" || word == "NOT") {
            if(word == "NOT") {
                s >> word;
                if(word == "AND" || word == "OR" || word == "NOT") return false;
            }
            s >> word;
            if(word == "AND" || word == "OR" ) return false;
        }
    }

    return true;
}