#include "../header/moviesMock.hpp"
#include "../header/selectMock.hpp"

#include <string>
#include <iostream>
#include <cstdint>
#include <memory>
#include <sstream>
#include <set>

using namespace std;

MoviesMock::~MoviesMock() {
  delete select;
}

void MoviesMock::set_selection(Select* new_select) {
    select = new_select;
}

int MoviesMock::get_column_by_name(const std::string& name) const
{
	for(int i=0; i<column_names.size(); i++)
		if(column_names.at(i) == name)
			return i;
	return -1;
}

void MoviesMock::set_column_names(const std::vector<std::string>& names)
{
	    column_names=names;
}

void MoviesMock::clear()
{
	column_names.clear();
	data.clear();
	delete select;
	select = nullptr;
}

const std::vector<std::string>& MoviesMock::cell_data(int row, int column) const
{
	return data.at(row).at(column);
}

void MoviesMock::add_vector(const std::vector<std::vector<std::string>>& row_data)
{//fix, reference from l5 add_row
	data.push_back(row_data);
}

bool MoviesMock::search(std::string& query) {
    if(query == "") return true;
    if(!valid(query)) return false;
	  std::stringstream stream(query);
	  std::string word = "";
    while (stream >> word)
    {
        if(word == "NOT" || word == "not") {
            stream >> word;
            unsigned i = word.find('=');
            std::string temp_left = word.substr(0, i);    //left is column name
            std::string right = word.substr(i+1, word.size()-1); //right is desired criterion
            std::string left = "";
            for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); }
            set_selection(new Select_Not(new Select_Contains(this, left, right)));
        }
        else if(word == "AND" || word == "and") {
            stream >> word;
            if(word == "NOT" || word == "not") {
              stream >> word;
              unsigned i = word.find('=');
              std::string temp_left = word.substr(0, i);    
              std::string right = word.substr(i+1, word.size()-1);
              std::string left = "";
              for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); }
              set_selection( new Select_And(select, new Select_Not(new Select_Contains(this, left, right))) );
            }
            else {
              unsigned i = word.find('=');
              std::string temp_left = word.substr(0, i);    
              std::string right = word.substr(i+1, word.size()-1);
              std::string left = "";
              for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); }
              set_selection(new Select_And(select, new Select_Contains(this,left,right)));
            }
        }
        else if(word == "OR" || word == "or") {
          set_selection(new Select_Or(select, search_helper(stream))); 
        }
        else {
          unsigned i = word.find('=');
          std::string temp_left = word.substr(0, i);    
          std::string right = word.substr(i+1, word.size()-1);
          std::string left = "";
          for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); }
          set_selection(new Select_Contains(this, left, right));
        }
    }

    return true;
}

Select* MoviesMock::search_helper(std::stringstream& stream) {
  	std::string word = "";
    Select* temp = nullptr;
    while (stream >> word)
    {
        if(word == "NOT" || word == "not") {
            stream >> word;
            unsigned i = word.find('=');
            std::string temp_left = word.substr(0, i);    //left is column name
            std::string right = word.substr(i+1, word.size()-1); //right is desired criterion
            std::string left = "";
            for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); } //Converts the user input column name to lowercase
            temp = new Select_Not(new Select_Contains(this, left, right));
        }
        else if(word == "AND" || word == "and") {
            stream >> word;
            if(word == "NOT" || word == "not") {
              stream >> word;
              unsigned i = word.find('=');
              std::string temp_left = word.substr(0, i);    
              std::string right = word.substr(i+1, word.size()-1);
              std::string left = "";
              for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); }
              temp = new Select_And(temp, new Select_Not(new Select_Contains(this, left, right)));
            }
            else {
              unsigned i = word.find('=');
              std::string temp_left = word.substr(0, i);    
              std::string right = word.substr(i+1, word.size()-1);
              std::string left = "";
              for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); }
              temp = new Select_And(temp, new Select_Contains(this,left,right));
            }
        }
        else if(word == "OR" || word == "or") {
          temp = new Select_Or(temp, search_helper(stream)); 
        }
        else {
          unsigned i = word.find('=');
          std::string temp_left = word.substr(0, i);    
          std::string right = word.substr(i+1, word.size()-1);
          std::string left = "";
          for(int i=0; i<temp_left.size(); ++i) { left += tolower(temp_left[i]); }
          temp = new Select_Contains(this, left, right);
        }
    }

    return temp;
}

bool MoviesMock::valid(std::string &query) {
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

static size_t WriteCallback(const char* in, size_t size, size_t num, string* out)
{
    out->append(in, size * num);
    return size * num;
}

bool MoviesMock::movie_update(int id){
      vector<vector<string>> movieData;

        return true;

      //Budget
      vector<string> budgetData;
      budgetData.push_back("0");
      movieData.push_back(budgetData);

      //Genres
      vector<string> genresData;
      genresData.push_back("Horror");
      genresData.push_back("Action");
      genresData.push_back("Drama");
      genresData.push_back("War");
      movieData.push_back(genresData);

      //Homepage
      vector<string> homepageData;
     
      movieData.push_back(homepageData);

      //Spoken_Languages
      vector<string> spokenLanguagesData;
      
      movieData.push_back(spokenLanguagesData);

      //Status
      vector<string> statusData;
      
      movieData.push_back(statusData);

      //Title
      vector<string> titleData;
      
      movieData.push_back(titleData);

      add_vector(movieData);

  return true;
}

bool MoviesMock::movie_update(string sort, int n){
  string baseUrl;
  int movieCount = n;
  int totalPages = 1;

  //cout << "Updating!" << endl;

  if (sort == "trending") {
    baseUrl = "https://api.themoviedb.org/3/trending/movie/day?api_key=" + api_key;
  } else if (sort == "now_playing") {
    baseUrl = "https://api.themoviedb.org/3/movie/now_playing?api_key=" + api_key;
  } else if (sort == "top_rated") {
    baseUrl = "https://api.themoviedb.org/3/movie/top_rated?api_key=" + api_key;
  } else {
    //cout << "Sort name failed!" << endl << "Input: " << sort << endl;
    clear();
    return false;
  }

  clear();

  vector<string> column_names;
  column_names.push_back("budget");
  column_names.push_back("genres");
  column_names.push_back("homepage");
  column_names.push_back("spoken_language");
  column_names.push_back("status");
  column_names.push_back("title");
  set_column_names(column_names);

  //cout << "Columns added!" << endl;

      vector<vector<string>> movieData;
      //Budget
      vector<string> budgetData;
      budgetData.push_back("0");
      movieData.push_back(budgetData);

      //Genres
      vector<string> genresData;
      genresData.push_back("Horror");
      genresData.push_back("Action");
      genresData.push_back("Drama");
      genresData.push_back("War");
      movieData.push_back(genresData);

      //Homepage
      vector<string> homepageData;
      homepageData.push_back("http://www.shadowinthecloudfilm.com");
      movieData.push_back(homepageData);

      //Spoken_Languages
      vector<string> spokenLanguagesData;
      spokenLanguagesData.push_back("English");
      movieData.push_back(spokenLanguagesData);

      //Status
      vector<string> statusData;
      statusData.push_back("Released");
      movieData.push_back(statusData);

      //Title
      vector<string> titleData;
      titleData.push_back("Shadow in the Cloud");
      movieData.push_back(titleData);

      add_vector(movieData);
//--------------------------------------------------------------------------------------------------------------
      vector<vector<string>> movieData1;
      //Budget
      vector<string> budgetData1;
      budgetData1.push_back("150000000");
      movieData1.push_back(budgetData1);

      //Genres
      vector<string> genresData1;
      genresData1.push_back("Family");
      genresData1.push_back("Animation");
      genresData1.push_back("Comedy");
      genresData1.push_back("Drama");
      genresData1.push_back("Music");
      genresData1.push_back("Fantasy");
      movieData1.push_back(genresData1);

      //Homepage
      vector<string> homepageData1;
      homepageData1.push_back("https://movies.disney.com/soul");
      movieData1.push_back(homepageData1);

      //Spoken_Languages
      vector<string> spokenLanguagesData1;
      spokenLanguagesData1.push_back("English");
      movieData1.push_back(spokenLanguagesData1);

      //Status
      vector<string> statusData1;
      statusData1.push_back("Released");
      movieData1.push_back(statusData1);

      //Title
      vector<string> titleData1;
      titleData1.push_back("Soul");
      movieData1.push_back(titleData1);

      add_vector(movieData1);
//------------------------------------------------------------------------------------
      if(true) {
        vector<vector<string>> movieData;
        //Budget
        vector<string> budgetData;
        budgetData.push_back("155000000");
        movieData.push_back(budgetData);

        //Genres
        vector<string> genresData;
        genresData.push_back("Action");
        genresData.push_back("Science Fiction");
        movieData.push_back(genresData);

        //Homepage
        vector<string> homepageData;
        homepageData.push_back("https://www.godzillavskong.com");
        movieData.push_back(homepageData);

        //Spoken_Languages
        vector<string> spokenLanguagesData;
        spokenLanguagesData.push_back("English");
        movieData.push_back(spokenLanguagesData);

        //Status
        vector<string> statusData;
        statusData.push_back("Post Production");
        movieData.push_back(statusData);

        //Title
        vector<string> titleData;
        titleData.push_back("Godzilla vs. Kong");
        movieData.push_back(titleData);

        add_vector(movieData);
      }
//--------------------------------------------------------------------------------------------
      if(true) {
        vector<vector<string>> movieData;
        //Budget
        vector<string> budgetData;
        budgetData.push_back("356000000");
        movieData.push_back(budgetData);

        //Genres
        vector<string> genresData;
        genresData.push_back("Adventure");
        genresData.push_back("Science Fiction");
        genresData.push_back("Action");
        
        movieData.push_back(genresData);

        //Homepage
        vector<string> homepageData;
        homepageData.push_back("https://www.marvel.com/movies/avengers-endgame");
        movieData.push_back(homepageData);

        //Spoken_Languages
        vector<string> spokenLanguagesData;
        spokenLanguagesData.push_back("English");
        spokenLanguagesData.push_back("日本語");
        movieData.push_back(spokenLanguagesData);

        //Status
        vector<string> statusData;
        statusData.push_back("Released");
        movieData.push_back(statusData);

        //Title
        vector<string> titleData;
        titleData.push_back("Avengers: Endgame");
        movieData.push_back(titleData);

        add_vector(movieData);
      }
//------------------------------------------------------------------
      if(true) {
        vector<vector<string>> movieData;
        //Budget
        vector<string> budgetData;
        budgetData.push_back("0");
        movieData.push_back(budgetData);

        //Genres
        vector<string> genresData;
        genresData.push_back("Drama");
        movieData.push_back(genresData);

        //Homepage
        vector<string> homepageData;
        homepageData.push_back("https://www.focusfeatures.com/land");
        movieData.push_back(homepageData);

        //Spoken_Languages
        vector<string> spokenLanguagesData;
        spokenLanguagesData.push_back("English");
        movieData.push_back(spokenLanguagesData);

        //Status
        vector<string> statusData;
        statusData.push_back("Released");
        movieData.push_back(statusData);

        //Title
        vector<string> titleData;
        titleData.push_back("Land");
        movieData.push_back(titleData);

        add_vector(movieData);
      }

    return true;
}

void MoviesMock::print_selection(std::ostream& out) const {
  if (column_names.size() != 6) {
    return;
  }
  else if (select == nullptr) {
    for(int i = 0; i < data.size(); i++){
      out << "Budget: ";
      if (!data[i][0].empty()) out << data[i][0][0];

      out << endl << "Genres: ";
      if (!data[i][1].empty()) {
        for (int j = 0; j < data[i][1].size()-1; j++){
          out << data[i][1][j] << ", ";
        }
        out << data[i][1].back();
      }

      out << endl << "Homepage: ";
      if (!data[i][2].empty()) out << data[i][2][0];

      out << endl << "Spoken Languages: ";
      if (!data[i][3].empty()){
        for (int j = 0; j < data[i][3].size()-1; j++){
          out << data[i][3][j] << ", ";
        }
        out << data[i][3].back() << endl;
      }

      out << "Status: ";
      if (!data[i][4].empty()) out << data[i][4][0] << endl;

      out << "Title: ";
      if (!data[i][5].empty()) out << data[i][5][0] << endl;

      out << "--------------------------------------------" << endl;
    }
  } else {
    for(int i = 0; i < data.size(); i++){
      if (select->select(this, i)) {
        out << "Budget: ";
        if (!data[i][0].empty()) out << data[i][0][0];

        out << endl << "Genres: ";
        if (!data[i][1].empty()) {
            for (int j = 0; j < data[i][1].size()-1; j++){
            out << data[i][1][j] << ", ";
            }
            out << data[i][1].back();
        }

        out << endl << "Homepage: ";
        if (!data[i][2].empty()) out << data[i][2][0];

        out << endl << "Spoken Languages: ";
        if (!data[i][3].empty()){
            for (int j = 0; j < data[i][3].size()-1; j++){
            out << data[i][3][j] << ", ";
            }
            out << data[i][3].back() << endl;
        }

        out << "Status: ";
        if (!data[i][4].empty()) out << data[i][4][0] << endl;

        out << "Title: ";
        if (!data[i][5].empty()) out << data[i][5][0] << endl;

        out << "--------------------------------------------" << endl;
      }
    }
  }
}
