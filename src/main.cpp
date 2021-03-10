#include "../header/movies.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  Movies movies;
  char input = 'a';

  while (input != 'q' && input != 'Q') {
    cout << "Number of movies in list: " << movies.return_num_movies() << endl;
    cout << "Current sort: " << movies.return_sort() << endl;
    cout << "Number of search results: " << movies.num_searched() << endl;
    cout << endl << "(F) Fetch and search movies" << endl;
    cout << "(S) Search movies" << endl;
    cout << "(P) Print current selection" << endl;
    cout << "(Q) Quit" << endl;

    cin >> input;
    cout << endl;

    if (input == 'f' || input == 'F') {
      string sort;
      cout << "Choose a sorting method (trending, now_playing, or top_rated): ";
      cin >> sort;
      cout << endl;

      int num_movies;
      cout << "How many movies should we fetch: ";
      cin >> num_movies;
      cout << endl;

      cout << "Fetching movies..." << endl;
      if (movies.movie_update(sort, num_movies)) {
        cout << "Movies fetched!" << endl;
      } else {
        cout << "Something went wrong!" << endl;
      }
    } else if (input == 's' || input == 'S') {
      string search;
      cout << "What do you want to search for? Example: genres=Action AND NOT title=Hard OR production_country=States" << endl;
      cout << "Possible search inputs: budget, genres, homepage, id, imdb_id, original_language, original_title, overview, popularity, production_company_name, production_company_country, production_country, release_date, revenue, runtime, spoken_language, status, tagline, title, vote_average, vote_count" << endl;
      cin.ignore();
      getline(cin, search);
      cout << endl;

      movies.clear_select();
      if (movies.search(search)) {
        cout << "Movies searched!" << endl;
      } else {
        cout << "Something went wrong!" << endl;
        movies.clear_select();
      }
    } else if (input == 'p' || input == 'P') {
      movies.print_selection(cout);
    }

    cout << endl;
  }

  // READ FROM FILE EXAMPLE
  // CREATE A FILE USING DATA FROM https://api.themoviedb.org/3/movie/<ID>?api_key=8b6eb71dd22c58cfb6125ac835f94e2a
  // movies.init_column_names();
  // movies.movie_from_file("10751.json");
  // movies.movie_from_file("9602.json");
  // movies.print_selection(cout);
}
