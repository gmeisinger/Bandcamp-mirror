# Team Bandcamp
CS 1666 - Group game design project 

## Our Game
The year is 2025, a coalition of Earths great powers have come together to fund Man's furthest exploration into space to date.  It is believed that on the distant Galilean moon Europa, orbiting Jupiter, there may be liquid water underneath the dense frozen surface.  Earth scientists are eager to find out if there may be any bacterium or any signs of life in this liquid water.  Your mission is to take the 8 month journey to Europa, safely land on the planets surface, search for any evidence of life and safely return to report any of your findings.  If this mission is successful, Earth may fund another mission several years from now, but if you don't find anything or fail to return to report your findings, if may be the end of this exploratory endeavor.  

After landing, you discover much more than bacteria.  You and your crew came equiped to take small ice samples and explore an open planet. You discover the remnants of an alien base on a battle field that took place between two alien races.  The freezing temperatures of Europa has left the battlefield almost perfectly preserved in ice and everything you find is a new discovery for mankind.  Your mission has taken on a whole new life.  Now there is technology to be found, bases and crashed ships to explore, and aliens to understand.  But why were these races fighting?  How was so much damage done?  And are the aliens that did this still here?...  


Should state the goals for this game for the term (i.e., what criteria must be met for the term project to be complete)
Our goals for this game are to develop an adventure game that randomly generates new areas for a player to explore every time they play the game.  We intend to develop enemies that behave intelligently based on their strength and the strength of the players, so the enemies are not suicidal. 


### Advanced Topics
For our advanced featues, we will explore the topics of Advanced AI, advanced physics and procedurally generated maps.  We will use advanced AI to to make enemies behave with different levels of intelligence and strategy.  Using advanced physics, we will simulate heat distribution and exploye the effects of different levels of atmospheric pressure.  Finally, we will develop a procedure for randomly generating areas to explore to reenfore the exploration aspect of our game.  

##### Advanced AI
- Ness Colihan (Group Lead)
- Graeme Rock
- Christian Brill


##### Physics Engine 
- Kyle Hartenstein (Group Lead)
- Tyler Thompson
- Brad Munson

##### Procedural Generation 
- Brendan Valley (Group Lead)
- George Meisinger
- Jacob Bader
- Justin Budd

#### Team organization and communication
Our team is divided into three groups to focus on each of the advanced features.  We will have temporary leadership positions for each week including a team leader, assistant to the team leader and a group leader for each feature group.  We hope this will increase accountability and establish clear lines of communication.  We will be using slack to communicate, and may use skype for virtual meetings as needed.  

##### Agile Development 
We will be using Agile development, here are the basic principles of agile: 
1. Customer satisfaction by early and continuous delivery of valuable software
1. Welcome changing requirements, even in late development
1. Working software is delivered frequently (weeks rather than months)
1. Close, daily cooperation between business people and developers
1. Projects are built around motivated individuals, who should be trusted
1. Face-to-face conversation is the best form of communication (co-location)
1. Working software is the primary measure of progress
1. Sustainable development, able to maintain a constant pace
1. Continuous attention to technical excellence and good design
1. Simplicity—the art of maximizing the amount of work not done—is essential
1. Best architectures, requirements, and designs emerge from self-organizing teams
1. Regularly, the team reflects on how to become more effective, and adjusts

##### Style Guidelines 
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

Functions should accomplish small and simple tasks.  For complicated functions, call multiple smaller functions.  This will make debugging easier and should ultimately make code dryer.  Here are some important principles to start off:

- Commenting before each method with any applicable params. and a good description 
```
// This functions is for doing something specific 
// inputNum: Describe where this number came from and what it's for 
somethingFunction(int inputNum){
}
```

- Commenting each end bracket of a method with the mehthod name for clarity.
```
fooFunction(){
}end of fooFunction 
```

#### Changes to repository 
When you make any changes, create a new branch in the format of your initials_TOPIC_what_your_working_on.  This will keep code safe and changes trackable


exp: jb_AI_playertracking

```
git checkout -b jb_user_tokens
```

This way we can check each other's code, make a pull request and merge.


When you are ready to add your changes, push your changes to your branch on github with the following commands

```
# stage your changes 
git add . 

# commit your change.  The -m is a message tag for describing your change 
git commit -m "title for change"

# push your changes to your branch 
git push
``` 

Proper use of github means you will push to a branch of your own creation as shown above 

### NEVER PUSH TO MASTER OR STABLE

Once you have pushed your changes to your branch on github, you can make a pull request (PR) to unstable or whatever branch your team is using.  Also NEVER MERGE YOUR OWN BRANCH. Ask someone else, preferably your team leader, assistant to the regional manager or regional manager to merge your PR.

If you have any dificulties with this or anything else, ASK FOR HELP.  Life is a team sport