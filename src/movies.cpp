#include "../header/spreadsheet.hpp"
#include "../header/select.hpp"

#include <string>
#include <iostream>
#include <cstdint>
#include <memory>

#include <jsoncpp/json/json.h>
#include <curl/curl.h>

using namespace std;

static size_t WriteCallback(const char* in, size_t size, size_t num, string* out)
{
    out->append(in, size * num);
    return size * num;
}

bool Movies::update(int id){
  string baseUrl("https://api.themoviedb.org/3/movie/" + to_string(id) + "?api_key=" + to_string(api_key));
  long httpCode(0);
  unique_ptr<string> httpData(new string());

  //Get data from http using CURL
  CURL* curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Set remote url
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
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
      if (jsonData["budget"].asBool()) {
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
      if (jsonData["homepage"].asBool()) {
        homepageData.push_back(jsonData["homepage"].asString());
      }
      movieData.push_back(homepageData);

      //ID
      vector<string> idData;
      if (jsonData["id"].asBool()) {
        idData.push_back(jsonData["id"].asString());
      }
      movieData.push_back(idData);

      //IMDB_ID
      vector<string> imdbIdData;
      if (jsonData["imdb_id"].asBool()) {
        imdbIdData.push_back(jsonData["imdb_id"].asString());
      }
      movieData.push_back(imdbIdData);

      //Original_Language
      vector<string> originalLanguageData;
      if (jsonData["original_language"].asBool()) {
        originalLanguageData.push_back(jsonData["original_language"].asString());
      }
      movieData.push_back(originalLanguageData);

      //Original_Title
      vector<string> originalTitleData;
      if (jsonData["original_title"].asBool()) {
        originalTitleData.push_back(jsonData["original_title"].asString());
      }
      movieData.push_back(originalTitleData);

      //Overview
      vector<string> overviewData;
      if (jsonData["overview"].asBool()) {
        overviewData.push_back(jsonData["overview"].asString());
      }
      movieData.push_back(overviewData);

      //Popularity
      vector<string> popularityData;
      if (jsonData["popularity"].asBool()) {
        popularityData.push_back(jsonData["overview"].asString());
      }
      movieData.push_back(overviewData);

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
      if (jsonData["release_date"].asBool()) {
        releaseDateData.push_back(jsonData["release_date"].asString());
      }
      movieData.push_back(releaseDateData);

      //Revenue
      vector<string> revenueData;
      if (jsonData["revenue"].asBool()) {
        revenueData.push_back(jsonData["revenue"].asString());
      }
      movieData.push_back(revenueData);

      //Runtime
      vector<string> runtimeData;
      if (jsonData["runtime"].asBool()) {
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
      if (jsonData["status"].asBool()) {
        statusData.push_back(jsonData["status"].asString());
      }
      movieData.push_back(statusData);

      //Tagline
      vector<string> taglineData;
      if (jsonData["tagline"].asBool()) {
        taglineData.push_back(jsonData["tagline"].asString());
      }
      movieData.push_back(taglineData);

      //Title
      vector<string> titleData;
      if (jsonData["title"].asBool()) {
        titleData.push_back(jsonData["title"].asString());
      }
      movieData.push_back(titleData);

      //Vote_Average
      vector<string> voteAverageData;
      if (jsonData["vote_average"].asBool()) {
        voteAverageData.push_back(jsonData["vote_average"].asString());
      }
      movieData.push_back(voteAverageData);

      //Vote_Count
      vector<string> voteCountData;
      if (jsonData["vote_count"].asBool()) {
        voteCountData.push_back(jsonData["vote_count"].asString());
      }
      movieData.push_back(voteCountData);

      add_vector(movieData);
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
  return true;
}
