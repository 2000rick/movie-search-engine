 # Latest Movie Recommendations
 
Authors: 

[Matthew Thompson](https://github.com/matthew-cs)

[Qipeng Liang](https://github.com/2000rick)

[Evelyn Yao](https://github.com/eyao004)

[Connor Hardenburgh](https://github.com/siaech)


## Project Description
Application that outputs movies as recommendations in various categories (based on the movie genre, director, actors, rating, release date, etc). Then the application will recommend a list of movies to the user, based on their input. They can then ask for more details about a recommended movie.

Why is it important or interesting?

It’s hard to get good movie recommendations. Therefore, we want to build a movie recommender that works for everyone - without tracking users and violating their privacy.

Languages/tools/technologies we plan to use:

Languages:
C++


Tools:
Google Test

[JsonCpp](https://github.com/open-source-parsers/jsoncpp), from `libjsoncpp-dev`

[libcurl](https://curl.se/libcurl/), from `libcurl4-openssl-dev`

[The Movie Database API](https://developers.themoviedb.org/3/getting-started/introduction)

Input/output of project:

Input: Answer 2 menus. First menu input is (trending or upcoming movies), Second Menu is the user's genre of choice.

Output: A list of movie recommendations (trending or upcoming movies) within the user's chosen genre. The user can then choose a specific movie from the list to see more details.

The two design patterns we will be using:

Design Pattern 1: Composite Design Pattern

We have chosen the composite design pattern because it will allow us to create different objects that extends from a common base class. Each movie will have its own sub categories (Ex movie genre, director, actors, rating, release date). The pattern will allow us to include the various categories for each movie and allow the user to select multiple criteria for recommendation (e.g. this actor AND this genre). The client, user, will manipulate the objects through interactions with the menu interface. The chosen design pattern will be sufficient for the project because it will allow the database to have a complex category and search system. The composite design pattern will allow tree like structures where the composite class and the leaves are treated the same. They will us to use the same base class, the component class. For example, a movie genre can be described as a tree when compared to its subgenres. 

Design Pattern 2: State Design Pattern

We picked the State design pattern because its features fit our project, our program will have different and finite states based on the user input. We will implement different menus with the design pattern, such as: trending movies, upcoming movies, or a specific genre. The program behaves differently in different states, and it can switch from one state to another instantly (transitions). By using the State design pattern, we can create new classes for each state and implement all state-specific behaviors into these classes. For example, in the state where the user is presented with trending movies, the user has the option to transition to a specific movie in the list (with details) or go back to the previous menu.


## Class Diagram

![Movie Search Engine](https://user-images.githubusercontent.com/77033594/108788556-161e6180-752d-11eb-868d-17c9c6bba4af.png)

Movies: This is the context class, it holds a Select pointer, movie data, among others. The search function is intended to be a factory method (which we might extract to its own class). This class is what the end user will mostly be interacting with.

Select: Interface, abstract class.

Select_Contains: A concrete strategy. Returns true if row(the movie) should be printed.

Select_Not: A concrete strategy that takes another Select pointer as input and performs the NOT logic operation. Returns true if the row(the movie) should be printed.

Select_And: A concrete strategy that takes other Select pointers as input and performs the AND logic operation. Returns true if the row(the movie) should be printed.

Select_Or: A concrete strategy that takes two Select pointers as input and performs the OR logic operation. Returns true if the row(the movie) should be printed.


 
 > ## Phase III
 > You will need to schedule a check-in with the TA (during lab hours or office hours). Your entire team must be present. 
 > * Before the meeting you should perform a sprint plan like you did in Phase II
 > * In the meeting with your TA you will discuss: 
 >   - How effective your last sprint was (each member should talk about what they did)
 >   - Any tasks that did not get completed last sprint, and how you took them into consideration for this sprint
 >   - Any bugs you've identified and created issues for during the sprint. Do you plan on fixing them in the next sprint or are they lower priority?
 >   - What tasks you are planning for this next sprint.

 > ## Final deliverable
 > All group members will give a demo to the TA during lab time. The TA will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Kanban board. 
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
