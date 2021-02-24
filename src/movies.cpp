#include "../header/spreadsheet.hpp"
#include "../header/select.hpp"

#include <string>
#include <iostream>
#include <cstdint>
#include <memory>
#include <sstream>

#include <jsoncpp/json/json.h>
#include <curl/curl.h>

using namespace std;

bool search(std::string& query) {
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
}
