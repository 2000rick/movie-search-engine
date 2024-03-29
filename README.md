 [![CI](https://github.com/cs100/final-project-chard007-eyao004-mthom106-qlian015/actions/workflows/main.yml/badge.svg)](https://github.com/cs100/final-project-chard007-eyao004-mthom106-qlian015/actions/workflows/main.yml)
 
 # Movie Search Engine

Authors:

[Matthew Thompson](https://github.com/matthew-cs)

[Qipeng Liang](https://github.com/2000rick)

[Evelyn Yao](https://github.com/eyao004)

[Connor Hardenburgh](https://github.com/siaech)


## Project Description
Application that allows the user to search movies in various categories (based on the movie genre, director, actors, rating, release date, etc). Then the application will display a list of matching movies to the user, based on their input.

Why is it important or interesting?

It’s hard to search for the perfect movie. Therefore, we want to build a movie search engine that works for everyone - without tracking users and violating their privacy.

Languages/tools/technologies we plan to use:

Languages:
C++


Tools:

[Google Test](https://github.com/google/googletest)

[CMake](https://cmake.org/)

[GNU make](https://www.gnu.org/software/make/)

[JsonCpp](https://github.com/open-source-parsers/jsoncpp), from `libjsoncpp-dev`

[libcurl](https://curl.se/libcurl/), from `libcurl4-openssl-dev`

[The Movie Database API](https://developers.themoviedb.org/3/getting-started/introduction)

Input/output of project:

Input: User specifies how the movies are sorted (trending, upcoming, or top_rated), how many movies to display, and a search query.

Output: A list of movies that matches the user's search query.

The design patterns we will be using:

Design Pattern 1: Composite Design Pattern

We have chosen the composite design pattern because it will allow us to create different objects that extends from a common base class. Each movie will have its own sub categories (Ex movie genre, director, actors, rating, release date). The pattern will allow us to include the various categories for each movie and allow the user to select multiple criteria for recommendation (e.g. this actor AND this genre). The client, user, will manipulate the objects through interactions with the menu interface. The chosen design pattern will be sufficient for the project because it will allow the database to have a complex category and search system. The composite design pattern will allow tree like structures where the composite class and the leaves are treated the same. They will allow us to use the same base class, the component class. For example, a movie genre can be described as a tree when compared to its subgenres.

Design Pattern 2: Strategy Design Pattern

We picked the Strategy design pattern because its features fit our project, our program will have different search queries based on the user input. We will implement different strategies with the design pattern, such as: Select_Contains, Select_And, Select_Not, etc. The user search query will be parsed by a factory method, where it updates the Select method(the pointer) to match the criteria. By using the Strategy design pattern, we can create new separate classes for each strategy method and implement all strategy-specific behaviors into them. This will allow the user to search for both specific movies or a broad-range of movies.

Design Pattern 3: Factory Design Pattern

We have added the factory design pattern because it will allow us to make the creation of the Selection object abstract. We are going to use the factory pattern to parse a user search query(string). This method will return or update root node(pointer) containing a tree of Select classes. In other words, the factory method will be creating a product of Select object.


## Class Diagram

![Movie Search Engine](https://user-images.githubusercontent.com/66210660/110410050-19414380-803d-11eb-9d32-e0c581c6da2b.png)

Movies: This is the context class, it holds a Select pointer, movie data, among others. The search function is intended to be a factory method. This class is what the end user will mostly be interacting with.

Select: Interface, abstract class. 

Select_Contains: A concrete strategy. The select function returns true if the row(the movie) should be printed.

Select_Not: A concrete strategy that takes another Select pointer as input and performs the NOT logic operation. The method determines if some movie should be printed (if calling select from the input returns false).

Select_And: A concrete strategy that takes other Select pointers as input and performs the AND logic operation. The method determines if some movie should be printed (if calling select for both inputs returns true).

Select_Or: A concrete strategy that takes two Select pointers as input and performs the OR logic operation. The method determines if some movie should be displayed (if calling select for either one of the inputs returns true).

## Screenshots
![finalScreen1 0](https://user-images.githubusercontent.com/65573447/110528323-e0e94600-80cc-11eb-9a78-58904c043053.png)
![finalScreen4 1](https://user-images.githubusercontent.com/65573447/110528346-e6df2700-80cc-11eb-8912-a15ea70564ca.png)

## Installation/Usage

Downloading Movie Search Engine:

    git clone --recursive https://github.com/cs100/final-project-chard007-eyao004-mthom106-qlian015.git

Downloading dependencies using [APT](https://salsa.debian.org/apt-team/apt.git):

    sudo apt install libjsoncpp-dev
    sudo apt install libcurl4-openssl-dev
    
Potential dependencies, likely already installed but just in case:

    sudo apt install cmake
    sudo apt install make
    sudo apt install g++

Build using [CMake](https://cmake.org)

    cmake .
    make

Run program:

    ./movies
    
Run tests:

    ./test

### Search Query Input/Format
There are currently about 20 categories that the user search from, some of them are: budget, genres, homepage, spoken languages, title, etc. (Run the program to see more)

#### Logical operators:
Unary operator: "NOT"

Binary operators: "AND" & "OR"

#### All search queries should follow the formats below for optimal results:

    Bracket [ ] means optional. 

1. Simple query: [UnaryOp] &lt;categoryName>=&lt;desiredCriteria>

2. Complexy query: [UnaryOp] &lt;categoryName>=&lt;desiredCriteria> &lt;BinaryOp> [UnaryOp] &lt;category2>=&lt;criteria> &lt;BinaryOp> [UnaryOp] &lt;category3>=&lt;criteria> (extend...)

#### Examples:

    "STATUS=Released" or "genres=animation" or "TITLE=Endgame"

    "not genres=action and not genres=family"

    "budget=150 and genres=Music and genres=Drama and genres=Family AND GENRES=Animation AND GENRES=Comedy AND GENRES=Fantasy"

#### Invalid Inputs Description:

    Search query can be an empty string, in which case all fetched movie data are selected.

    Unless query is an empty string, all queries must have an equal sign '='.

    If an element in the query is not a logic operator, then it must contain '='.

    The search query cannot begin with a binary operator ("AND" or "OR").

    Search query cannot end with an operator (e.g. "title=endgame and").

    No binary operator should be immedidately followed by another binary operator (e.g. "Genre=Action AND OR Actor=Elizabeth" IS INVALID).

    Operator "NOT" cannot be followed by another operator (e.g. "NOT NOT Genre=Action" is not allowed, "Genre=Action AND NOT OR Actor=Matt" is invalid).


## Testing
Unit tests are written for individual functions, or a small set of functions if they are closely related or intertwined.

For functions that make sense to be tested individually but are private, we get around this by extracting them out to a test file. As in the case of a helper function to search - `bool valid(std::string& query)`. 
A fundamental flaw is the need to update the test file if changes are made to this function inside the Movies class.

Because of the nature of some functions working closely with one another, some functions are tested together in the same set of tests. This is seen in the case of the functions `bool search(std::string& query)` and ` void print_selection(std::ostream& out)` and the `select` classes.
The user search query is passed to `search`, which processes the query and updates the print selection criteria. When `print_selection` is called, it uses the `select` classes to help determine what should be printed.

Due to the dynamic nature of the application, we also created mock classes to help us test the program, which also makes testing easier as we can set and limit the movie data in the mock classes.

Additionally, manual testing is performed to ensure that the application runs and behaves as expected.

Finally, we utilized Github Actions to assist with integration testing.


