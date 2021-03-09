#include "../header/moviesMock.hpp"

#include <iostream>
#include <string>
#include <sstream>

TEST(print, typical) {
    MoviesMock movies;
    movies.movie_update("trending", 2);
    std::stringstream oStr;
    movies.print_selection(oStr);
    //std::cout << oStr.str() << std::endl;
    EXPECT_EQ(oStr.str(), "Budget: 0\nGenres: Horror, Action, Drama, War\nHomepage: http://www.shadowinthecloudfilm.com\nSpoken Languages: English\nStatus: Released\nTitle: Shadow in the Cloud\n--------------------------------------------\nBudget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\nBudget: 155000000\nGenres: Action, Science Fiction\nHomepage: https://www.godzillavskong.com\nSpoken Languages: English\nStatus: Post Production\nTitle: Godzilla vs. Kong\n--------------------------------------------\nBudget: 356000000\nGenres: Adventure, Science Fiction, Action\nHomepage: https://www.marvel.com/movies/avengers-endgame\nSpoken Languages: English, \xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E\nStatus: Released\nTitle: Avengers: Endgame\n--------------------------------------------\nBudget: 0\nGenres: Drama\nHomepage: https://www.focusfeatures.com/land\nSpoken Languages: English\nStatus: Released\nTitle: Land\n--------------------------------------------\n");
}

