#include "../header/moviesMock.hpp"

#include <iostream>
#include <string>
#include <sstream>
using std::string;

TEST(search, normal) {
    MoviesMock movies;
    movies.movie_update("mock", 5);
    std::stringstream oStr;
    string test = "budget=155";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    //std::cout << oStr.str() << std::endl;
    EXPECT_EQ(oStr.str(), "");
    //EXPECT_EQ(oStr.str(), "Budget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\n");
}

