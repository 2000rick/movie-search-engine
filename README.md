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

We have chosen the composite design pattern because it will allow us to create different objects that extends from a common base class. Each movie will have its own sub categories (Ex movie genre, director, actors, rating, release date). The pattern will allow us to include the various categories for each movie and allow the user to select multiple criteria for recommendation (e.g. this actor AND this genre). The client, user, will manipulate the objects through interactions with the menu interface. The chosen design pattern will be sufficient for the project because it will allow the database to have a complex category and search system. The composite design pattern will allow tree like structures where the composite class and the leaves are treated the same. They will us to use the same base class, the component class. For example, the a movie genre can be described as a tree when compared to its subgenres. 

Design Pattern 2: State Design Pattern

We picked the State design pattern because its features fit our project, our program will have different and finite states based on the user input. We will implement different menus with the design pattern, such as: trending movies, upcoming movies, or a specific genre. The program behaves differently in different states, and it can switch from one state to another instantly (transitions). By using the State design pattern, we can create new classes for each state and implement all state-specific behaviors into these classes. For example, in the state where the user is presented with trending movies, the user has the option to transition to a specific movie in the list (with details) or go back to the previous menu.


 > ## Phase II
 > In addition to completing the "Class Diagram" section below, you will need to 
 > * Set up your GitHub project board as a Kanban board for the project. It should have columns that map roughly to 
 >   * Backlog, TODO, In progress, In testing, Done
 >   * You can change these or add more if you'd like, but we should be able to identify at least these.
 > * There is no requirement for automation in the project board but feel free to explore those options.
 > * Create an "Epic" (note) for each feature and each design pattern and assign them to the appropriate team member. Place these in the `Backlog` column
 > * Complete your first *sprint planning* meeting to plan out the next 7 days of work.
 >   * Create smaller development tasks as issues and assign them to team members. Place these in the `Backlog` column.
 >   * These cards should represent roughly 7 days worth of development time for your team, taking you until your first meeting with the TA
## Class Diagram

![Design Pattern](https://user-images.githubusercontent.com/77033594/108158289-775fb400-7099-11eb-82bf-4ded7d4585fd.png)

MainMenu: This is the context class, it holds a State pointer, an apiKey, among others. This is what the end user will mostly be interacting with.

State: Interface, abstract class.

Movie: Movie object, it holds the detailed information on the movies.

Trending Movies: This is one of the possible states, the display function will output trending movies with user-defined criteria. User can then choose to get details about a specific movie.

Upcoming Movies: The display function will output upcoming movies with user-defined criteria. User can then choose to get details about a specific movie.


 > Include a class diagram(s) for each design pattern and a description of the diagram(s). Your class diagram(s) should include all the main classes you plan for the project. This should be in sufficient detail that another group could pick up the project this point and successfully complete it. Use proper OMT notation (as discussed in the course slides). You may combine multiple design patterns into one diagram if you'd like, but it needs to be clear which portion of the diagram represents which design pattern (either in the diagram or in the description). 
 
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
 
