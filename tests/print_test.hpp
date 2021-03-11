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

TEST(print, caseSensitive) {
    MoviesMock movies;
    movies.movie_update("trending", 3);
    std::stringstream oStr;
    string test = "STATUS=POST";
    if(movies.search(test)) movies.print_selection(oStr);
    EXPECT_EQ(oStr.str(), "Budget: 155000000\nGenres: Action, Science Fiction\nHomepage: https://www.godzillavskong.com\nSpoken Languages: English\nStatus: Post Production\nTitle: Godzilla vs. Kong\n--------------------------------------------\n");
}

TEST(print, caseS2) {
    MoviesMock movies;
    movies.movie_update("now_playing", 4);
    std::stringstream oStr;
    string test = "genres=animation";
    if(movies.search(test)) movies.print_selection(oStr);
    EXPECT_EQ(oStr.str(), "Budget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\n");
}

TEST(print, caseS3) {
    MoviesMock movies;
    std::stringstream oStr;
    movies.movie_update("top_rated", 5);
    string test = "TITLE=ENDGAME";
    if(movies.search(test)) movies.print_selection(oStr);
    EXPECT_EQ(oStr.str(), "Budget: 356000000\nGenres: Adventure, Science Fiction, Action\nHomepage: https://www.marvel.com/movies/avengers-endgame\nSpoken Languages: English, \xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E\nStatus: Released\nTitle: Avengers: Endgame\n--------------------------------------------\n");
}

TEST(print, caseS4) {
    MoviesMock movies;
    std::stringstream oStr;
    movies.movie_update("top_rated", 5);
    string test = "budget=0 and genres=MUSIC and GENRES=drama or GENRES=acTIon AND genres=war";
    if(movies.search(test)) movies.print_selection(oStr);
    EXPECT_EQ(oStr.str(), "Budget: 0\nGenres: Horror, Action, Drama, War\nHomepage: http://www.shadowinthecloudfilm.com\nSpoken Languages: English\nStatus: Released\nTitle: Shadow in the Cloud\n--------------------------------------------\nBudget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\n");
}

TEST(print, caseS5) {
    MoviesMock movies;
    std::stringstream oStr;
    movies.movie_update("top_rated", 5);
    string test = "BUDGET=150 AND GENRES=MUSIC AND GENRES=DRAMA AND GENRES=FAMILY AND GENRES=ANIMATION AND GENRES=COMEDY AND GENRES=FANTASY";
    if(movies.search(test)) movies.print_selection(oStr);
    EXPECT_EQ(oStr.str(), "Budget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\n");
}

TEST(movieUpdate, typical1) {
    MoviesMock movies;
    EXPECT_TRUE(movies.movie_update("top_rated", 5));
}

TEST(movieUpdate, typical2) {
    MoviesMock movies;
    EXPECT_TRUE(movies.movie_update("now_playing", 1));
}

TEST(movieUpdate, typical3) {
    MoviesMock movies;
    EXPECT_TRUE(movies.movie_update("trending", 3));
}

TEST(movieUpdate, invalid1) {
    MoviesMock movies;
    EXPECT_FALSE(movies.movie_update("TRENDING", 8));
}

TEST(movieUpdate, invalid2) {
    MoviesMock movies;
    EXPECT_FALSE(movies.movie_update("NOW", 5));
}

TEST(movieUpdate, invalid3) {
    MoviesMock movies;
    EXPECT_FALSE(movies.movie_update("knockKnock", 20));
}




