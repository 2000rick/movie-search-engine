#include "../header/movies.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  Movies movies;

  string sort;
  cout << "Choose a sorting method (trending, now_playing, or top_rated)" << endl;
  cin >> sort;

  int num_movies;
  cout << "How many movies should we grab?" << endl;
  cin >> num_movies;

  cout << "Fetching movies..." << endl;
  if (movies.movie_update(sort, num_movies)) {
    cout << "Movies fetched!" << endl << endl;
  } else {
    cout << "Something went wrong!" << endl;
    return 1;
  }

  movies.print_selection(cout);
  cout << endl;

  string search;
  cout << "What do you want to search for? Example: genres=Action AND NOT title=Hard OR production_country=States" << endl;
  cout << "Possible search inputs: budget, genres, homepage, id, imdb_id, original_language, original_title, overview, popularity, production_company_name, production_company_country, production_country, release_date, revenue, runtime, spoken_language, status, tagline, title, vote_average, vote_count" << endl << endl;
  cin.ignore();
  getline(cin, search);
  if (movies.search(search)) {
    cout << "Movies searched!" << endl << endl;
  } else {
    cout << "Something went wrong!" << endl;
    return 1;
  }

  movies.print_selection(cout);
  cout << endl;
}
