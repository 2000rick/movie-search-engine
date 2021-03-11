#ifndef __SEARCH__HPP
#define __SEARCH__HPP

#include "../header/moviesMock.hpp"

#include <iostream>
#include <string>
#include <sstream>
using std::string;
using std::cout; using std::endl;

TEST(search, normal) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "budget=155";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    else {
        cout << "returned false\n";
    }
    EXPECT_EQ(oStr.str(), "Budget: 155000000\nGenres: Action, Science Fiction\nHomepage: https://www.godzillavskong.com\nSpoken Languages: English\nStatus: Post Production\nTitle: Godzilla vs. Kong\n--------------------------------------------\n");
}

TEST(search, normal2) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "STATUS=Post";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 155000000\nGenres: Action, Science Fiction\nHomepage: https://www.godzillavskong.com\nSpoken Languages: English\nStatus: Post Production\nTitle: Godzilla vs. Kong\n--------------------------------------------\n");
}

TEST(search, normal3) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "GENRES=Animation";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\n");
}

TEST(search, normal4) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "homePAGE=shadowinthecloudfilm";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 0\nGenres: Horror, Action, Drama, War\nHomepage: http://www.shadowinthecloudfilm.com\nSpoken Languages: English\nStatus: Released\nTitle: Shadow in the Cloud\n--------------------------------------------\n");
}

TEST(search, normal5) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "TITLE=Endgame";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 356000000\nGenres: Adventure, Science Fiction, Action\nHomepage: https://www.marvel.com/movies/avengers-endgame\nSpoken Languages: English, \xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E\nStatus: Released\nTitle: Avengers: Endgame\n--------------------------------------------\n");
}

TEST(search, normal6) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "budget=0 and genres=Music and genres=Drama or GENRES=Action AND genres=War";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 0\nGenres: Horror, Action, Drama, War\nHomepage: http://www.shadowinthecloudfilm.com\nSpoken Languages: English\nStatus: Released\nTitle: Shadow in the Cloud\n--------------------------------------------\nBudget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\n");
}

TEST(search, normal7) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "budget=150 and genres=Music and genres=Drama and genres=Family AND GENRES=Animation AND GENRES=Comedy AND GENRES=Fantasy";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\n");
}

TEST(search, edge_emptyString) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 0\nGenres: Horror, Action, Drama, War\nHomepage: http://www.shadowinthecloudfilm.com\nSpoken Languages: English\nStatus: Released\nTitle: Shadow in the Cloud\n--------------------------------------------\nBudget: 150000000\nGenres: Family, Animation, Comedy, Drama, Music, Fantasy\nHomepage: https://movies.disney.com/soul\nSpoken Languages: English\nStatus: Released\nTitle: Soul\n--------------------------------------------\nBudget: 155000000\nGenres: Action, Science Fiction\nHomepage: https://www.godzillavskong.com\nSpoken Languages: English\nStatus: Post Production\nTitle: Godzilla vs. Kong\n--------------------------------------------\nBudget: 356000000\nGenres: Adventure, Science Fiction, Action\nHomepage: https://www.marvel.com/movies/avengers-endgame\nSpoken Languages: English, \xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E\nStatus: Released\nTitle: Avengers: Endgame\n--------------------------------------------\nBudget: 0\nGenres: Drama\nHomepage: https://www.focusfeatures.com/land\nSpoken Languages: English\nStatus: Released\nTitle: Land\n--------------------------------------------\n");
}

TEST(search, invalid_search) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "NOT NOT TITLE=End";
    EXPECT_FALSE(movies.search(test));
}

TEST(search, invalid_search2) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "not and id=1";
    EXPECT_FALSE(movies.search(test));
}

TEST(search, valid_search) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "not genres=Action and not genres=Family";
    EXPECT_TRUE(movies.search(test));
}

TEST(search, normal8) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "not genres=Action and not genres=Family";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 0\nGenres: Drama\nHomepage: https://www.focusfeatures.com/land\nSpoken Languages: English\nStatus: Released\nTitle: Land\n--------------------------------------------\n");
}

TEST(search, edge_noMatch) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "not budget=0";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "");
}

TEST(search, edge_noMatch_extend) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "not budget=0 and genres=Horror or genres=Drama and not BUDGET=0";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "");
}

TEST(search, edge_or_matching) {
    Movies movies;
    movies.movie_update("trending", 5);
    std::stringstream oStr;
    string test = "not budget=0 or GENRES=Drama AND GENRES=Action";
    if(movies.search(test)) {
        movies.print_selection(oStr);
    }
    EXPECT_EQ(oStr.str(), "Budget: 0\nGenres: Horror, Action, Drama, War\nHomepage: http://www.shadowinthecloudfilm.com\nSpoken Languages: English\nStatus: Released\nTitle: Shadow in the Cloud\n--------------------------------------------\n");
}

#endif




