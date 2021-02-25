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
    while(s2 >> word)
    {
        if(word == "AND" || word == "OR" || word == "NOT") {
            if(word == "NOT") {
                s2 >> word;
                if(word == "AND" || word == "OR" || word == "NOT") return false;
            }
            s2 >> word;
            if(word == "AND" || word == "OR" ) return false;
        }
    }

    return true;
}

static size_t WriteCallback(const char* in, size_t size, size_t num, string* out)
{
    out->append(in, size * num);
    return size * num;
}

bool Movies::movie_update(int id){
  string url("https://api.themoviedb.org/3/movie/" + to_string(id) + "?api_key=" + api_key);
  long httpCode(0);
  unique_ptr<string> httpData(new string());

  //Get data from http using CURL
  CURL* curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Set remote url
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4); // IPv4
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // Times out after 10 seconds
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects if necessary (just in case)
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Data handling function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get()); // Data container

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);
  }

  if (httpCode == 200) {
    Json::Value jsonData;
    Json::Reader jsonReader;

    if (jsonReader.parse(*httpData.get(), jsonData)) {
      vector<vector<string>> movieData;

      //Budget
      vector<string> budgetData;
      if (jsonData["budget"].isInt()) {
        budgetData.push_back(jsonData["budget"].asString());
      }
      movieData.push_back(budgetData);

      //Genres
      vector<string> genresData;
      if (jsonData["genres"].isArray()) {
        for (int i = 0; i < jsonData["genres"].size(); i++){
          genresData.push_back(jsonData["genres"][i]["name"].asString());
        }
      }
      movieData.push_back(genresData);

      //Homepage
      vector<string> homepageData;
      if (jsonData["homepage"].isString()) {
        homepageData.push_back(jsonData["homepage"].asString());
      }
      movieData.push_back(homepageData);

      //ID
      vector<string> idData;
      if (jsonData["id"].isInt()) {
        idData.push_back(jsonData["id"].asString());
      }
      movieData.push_back(idData);

      //IMDB_ID
      vector<string> imdbIdData;
      if (jsonData["imdb_id"].isString()) {
        imdbIdData.push_back(jsonData["imdb_id"].asString());
      }
      movieData.push_back(imdbIdData);

      //Original_Language
      vector<string> originalLanguageData;
      if (jsonData["original_language"].isString()) {
        originalLanguageData.push_back(jsonData["original_language"].asString());
      }
      movieData.push_back(originalLanguageData);

      //Original_Title
      vector<string> originalTitleData;
      if (jsonData["original_title"].isString()) {
        originalTitleData.push_back(jsonData["original_title"].asString());
      }
      movieData.push_back(originalTitleData);

      //Overview
      vector<string> overviewData;
      if (jsonData["overview"].isString()) {
        overviewData.push_back(jsonData["overview"].asString());
      }
      movieData.push_back(overviewData);

      //Popularity
      vector<string> popularityData;
      if (jsonData["popularity"].isDouble()) {
        popularityData.push_back(jsonData["popularity"].asString());
      }
      movieData.push_back(popularityData);

      //Production_Companies_Name and Production_Companies_Origin_Country
      vector<string> productionCompaniesNameData;
      vector<string> productionCompaniesOriginCountryData;
      if (jsonData["production_companies"].isArray()) {
        for (int i = 0; i < jsonData["production_companies"].size(); i++){
          productionCompaniesNameData.push_back(jsonData["production_companies"][i]["name"].asString());
          productionCompaniesOriginCountryData.push_back(jsonData["production_companies"][i]["origin_country"].asString());
        }
      }
      movieData.push_back(productionCompaniesNameData);
      movieData.push_back(productionCompaniesOriginCountryData);

      //Production_Countries
      vector<string> productionCountriesData;
      if (jsonData["production_countries"].isArray()) {
        for (int i = 0; i < jsonData["production_countries"].size(); i++){
          productionCountriesData.push_back(jsonData["production_countries"][i]["name"].asString());
        }
      }
      movieData.push_back(productionCountriesData);

      //Release_Date
      vector<string> releaseDateData;
      if (jsonData["release_date"].isString()) {
        releaseDateData.push_back(jsonData["release_date"].asString());
      }
      movieData.push_back(releaseDateData);

      //Revenue
      vector<string> revenueData;
      if (jsonData["revenue"].isInt()) {
        revenueData.push_back(jsonData["revenue"].asString());
      }
      movieData.push_back(revenueData);

      //Runtime
      vector<string> runtimeData;
      if (jsonData["runtime"].isInt()) {
        runtimeData.push_back(jsonData["runtime"].asString());
      }
      movieData.push_back(runtimeData);

      //Spoken_Languages
      vector<string> spokenLanguagesData;
      if (jsonData["spoken_languages"].isArray()) {
        for (int i = 0; i < jsonData["spoken_languages"].size(); i++){
          spokenLanguagesData.push_back(jsonData["spoken_languages"][i]["name"].asString());
        }
      }
      movieData.push_back(spokenLanguagesData);

      //Status
      vector<string> statusData;
      if (jsonData["status"].isString()) {
        statusData.push_back(jsonData["status"].asString());
      }
      movieData.push_back(statusData);

      //Tagline
      vector<string> taglineData;
      if (jsonData["tagline"].isString()) {
        taglineData.push_back(jsonData["tagline"].asString());
      }
      movieData.push_back(taglineData);

      //Title
      vector<string> titleData;
      if (jsonData["title"].isString()) {
        titleData.push_back(jsonData["title"].asString());
      }
      movieData.push_back(titleData);

      //Vote_Average
      vector<string> voteAverageData;
      if (jsonData["vote_average"].isDouble()) {
        voteAverageData.push_back(jsonData["vote_average"].asString());
      }
      movieData.push_back(voteAverageData);

      //Vote_Count
      vector<string> voteCountData;
      if (jsonData["vote_count"].isInt()) {
        voteCountData.push_back(jsonData["vote_count"].asString());
      }
      movieData.push_back(voteCountData);

      add_vector(movieData);
    }
    else {
      //cout << "Movie parse failed!" << endl << "ID: " << id << endl << url << endl;
      return false;
    }
  }
  else {
    //cout << "Movie fetch failed!" << endl << "ID: " << id << endl << "HTTP Code: " << httpCode << endl << url << endl;
    return false;
  }
  return true;
}

bool Movies::movie_update(string sort, int n){
  string baseUrl;
  int movieCount = n;
  int totalPages = 1;

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
  column_names.push_back("id");
  column_names.push_back("imdb_id");
  column_names.push_back("original_language");
  column_names.push_back("original_title");
  column_names.push_back("overview");
  column_names.push_back("popularity");
  column_names.push_back("production_company_name");
  column_names.push_back("production_company_country");
  column_names.push_back("production_country");
  column_names.push_back("release_date");
  column_names.push_back("revenue");
  column_names.push_back("runtime");
  column_names.push_back("spoken_language");
  column_names.push_back("status");
  column_names.push_back("tagline");
  column_names.push_back("title");
  column_names.push_back("vote_average");
  column_names.push_back("vote_count");
  set_column_names(column_names);

  for (int i = 1; i <= n/20+1 && i <= totalPages; i++){
    string url(baseUrl + "&page=" + to_string(i+1));
    long httpCode(0);
    unique_ptr<string> httpData(new string());

    //Get data from http using CURL
    CURL* curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Set remote url
      curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4); // IPv4
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // Times out after 10 seconds
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects if necessary (just in case)
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Data handling function
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get()); // Data container

      curl_easy_perform(curl);
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
      curl_easy_cleanup(curl);
    }

    if (httpCode == 200) {
      Json::Value jsonData;
      Json::Reader jsonReader;

      if (jsonReader.parse(*httpData.get(), jsonData)) {
        totalPages = jsonData["total_pages"].asInt();

        for (int j = 0; j < jsonData["results"].size() && movieCount > 0; j++) {
          //count << movieCount << endl;
          if (movie_update(jsonData["results"][j]["id"].asInt())) {
            clear();
            movieCount--;
          } else {
            //cout << "Movie update failed!" << endl << url << endl;
          }
      }
      else {
        //cout << "Movie list parse failed!" << endl << "Page: " << i+1 << endl << url << endl;
        clear();
        return false;
      }
    }
    else {
      //cout << "Movie list fetch failed!" << endl << "Page: " << i+1 << endl << "HTTP Code: " << httpCode << endl << url << endl;
      clear();
      return false;
    }
  }
    return true;
}

void Movies::print_selection(std::ostream& out) const {
  if (column_names.size() != 21) {
    return;
  }
  else if (select == nullptr) {
    for(int i = 0; i < data.size(); i++){
      cout << "Budget: ";
      if (!data[i][0].empty()) cout << data[i][0][0];

      cout << endl << "Genres: ";
      if (!data[i][1].empty()) {
        for (int j = 0; j < data[i][1].size()-1; j++){
          cout << data[i][1][j] << ", ";
        }
        cout << data[i][1].back();
      }

      cout << endl << "Homepage: ";
      if (!data[i][2].empty()) cout << data[i][2][0];

      cout << endl << "ID: ";
      if (!data[i][3].empty()) cout << data[i][3][0];

      cout << endl << "IMDB ID: ";
      if (!data[i][4].empty()) cout << data[i][4][0];

      cout << endl << "Original Language: ";
      if (!data[i][5].empty()) cout << data[i][5][0];

      cout << endl << "Original Title: ";
      if (!data[i][6].empty()) cout << data[i][6][0];

      cout << endl << "Overview: ";
      if (!data[i][7].empty()) cout << data[i][7][0];

      cout << endl << "Popularity: ";
      if (!data[i][8].empty()) cout << data[i][8][0];

      cout << endl << "Production Companies: ";
      if (!data[i][9].empty() && !data[i][10].empty()){
        for (int j = 0; j < data[i][9].size()-1; j++){
          cout << data[i][9][j] << " (" << data[i][10][j] << "), ";
        }
        cout << data[i][9].back() << " (" << data[i][10].back() << ")" << endl;
      }

      cout << "Production Countries: ";
      if (!data[i][11].empty()){
        for (int j = 0; j < data[i][11].size()-1; j++){
          cout << data[i][11][j] << ", ";
        }
        cout << data[i][11].back() << endl;
      }

      cout << "Release Date: ";
      if (!data[i][12].empty()) cout << data[i][12][0] << endl;

      cout << "Revenue: ";
      if (!data[i][13].empty()) cout << data[i][13][0] << endl;

      cout << "Runtime: ";
      if (!data[i][14].empty()) cout << data[i][14][0] << endl;

      cout << "Spoken Languages: ";
      if (!data[i][15].empty()){
        for (int j = 0; j < data[i][15].size()-1; j++){
          cout << data[i][15][j] << ", ";
        }
        cout << data[i][15].back() << endl;
      }

      cout << "Status: ";
      if (!data[i][16].empty()) cout << data[i][16][0] << endl;

      cout << "Tagline: ";
      if (!data[i][17].empty()) cout << data[i][17][0] << endl;

      cout << "Title: ";
      if (!data[i][18].empty()) cout << data[i][18][0] << endl;

      cout << "Vote Average: ";
      if (!data[i][19].empty()) cout << data[i][19][0] << endl;

      cout << "Vote Count: ";
      if (!data[i][20].empty()) cout << data[i][20][0] << endl;

      cout << "--------------------------------------------" << endl;
    }
  } else {
    for(int i = 0; i < data.size(); i++){
      if (select->select(this, i)) {
        cout << "Budget: ";
        if (!data[i][0].empty()) cout << data[i][0][0];

        cout << endl << "Genres: ";
        if (!data[i][1].empty()) {
          for (int j = 0; j < data[i][1].size()-1; j++){
            cout << data[i][1][j] << ", ";
          }
          cout << data[i][1].back();
        }

        cout << endl << "Homepage: ";
        if (!data[i][2].empty()) cout << data[i][2][0];

        cout << endl << "ID: ";
        if (!data[i][3].empty()) cout << data[i][3][0];

        cout << endl << "IMDB ID: ";
        if (!data[i][4].empty()) cout << data[i][4][0];

        cout << endl << "Original Language: ";
        if (!data[i][5].empty()) cout << data[i][5][0];

        cout << endl << "Original Title: ";
        if (!data[i][6].empty()) cout << data[i][6][0];

        cout << endl << "Overview: ";
        if (!data[i][7].empty()) cout << data[i][7][0];

        cout << endl << "Popularity: ";
        if (!data[i][8].empty()) cout << data[i][8][0];

        cout << endl << "Production Companies: ";
        if (!data[i][9].empty() && !data[i][10].empty()){
          for (int j = 0; j < data[i][9].size()-1; j++){
            cout << data[i][9][j] << " (" << data[i][10][j] << "), ";
          }
          cout << data[i][9].back() << " (" << data[i][10].back() << ")" << endl;
        }

        cout << "Production Countries: ";
        if (!data[i][11].empty()){
          for (int j = 0; j < data[i][11].size()-1; j++){
            cout << data[i][11][j] << ", ";
          }
          cout << data[i][11].back() << endl;
        }

        cout << "Release Date: ";
        if (!data[i][12].empty()) cout << data[i][12][0] << endl;

        cout << "Revenue: ";
        if (!data[i][13].empty()) cout << data[i][13][0] << endl;

        cout << "Runtime: ";
        if (!data[i][14].empty()) cout << data[i][14][0] << endl;

        cout << "Spoken Languages: ";
        if (!data[i][15].empty()){
          for (int j = 0; j < data[i][15].size()-1; j++){
            cout << data[i][15][j] << ", ";
          }
          cout << data[i][15].back() << endl;
        }

        cout << "Status: ";
        if (!data[i][16].empty()) cout << data[i][16][0] << endl;

        cout << "Tagline: ";
        if (!data[i][17].empty()) cout << data[i][17][0] << endl;

        cout << "Title: ";
        if (!data[i][18].empty()) cout << data[i][18][0] << endl;

        cout << "Vote Average: ";
        if (!data[i][19].empty()) cout << data[i][19][0] << endl;

        cout << "Vote Count: ";
        if (!data[i][20].empty()) cout << data[i][20][0] << endl;

        cout << "--------------------------------------------" << endl;
      }
    }
  }
}
