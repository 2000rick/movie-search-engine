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
	    while(stream >> word) {
		    if(word == "NOT") {}
		    else if(word == "AND"){}
		    else if(word == "OR") {}
		    else {}
	    }

	        return true;

}
