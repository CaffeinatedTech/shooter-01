# shooter

Just a vertical shoot-em-up to learn C++ and SFML with.

The plan is to build the same game over and over and improve on 
code style and features with each iteration.

### Iteration 1
This is the first iteration of this project.  Future iterations will
improve on this, and include new features.

#### Review
This is a short self review of this iteration.  A place to identify problem areas
and possible improvements.

This iteration was built ad-hoc, meaning little planning was done before project start.
This has lead to some hacky solutions to adding features.

**Some problem areas include:**
* Engine
    * The New-Game feature has lead to some messy state reset code.  It would be 
    better if we had a 'newGame' function for setting up the game and resetting
    timers, variables and arrays
    * State - We are using several variable to identify the game state, it would be better
    if we just had one state variable and a handy enum so we can use something like
    `state::RUNNING` or `state::INTERMISSION`
    * GUI text - this is a large part of the constructor, we should make a function for generating
    the Text elements so we can do something like `scoreLabel = guiText(scoreFont, fontSize, fontColour, string);`
* Update
    * Break into multiple function.  The update function is quite large.
* Debug Text
    * The console is flooded with debug text, we could add that to the game screen and
    toggle it with a keypress.  Shows player position, shooting status, number of enemies, number of bullets, 
    wave number etc.
* Sound
    * We don't have any sound at all
* High Score
    * We don't have a high score feature

### Features

#### Controls
* Movement
    * Keyboard - Arrow keys
    * Joystick 0 - D-Pad
* Firing
    * Keyboard - Space (hold for continuous fire)
    * Joystick - Button 0 (hold for continuous fire)
* Other
    * P or PAUSE to pause the game
    * ENTER to start a new game on the game-over screen

#### Gameplay
* Complete increasingly difficult waves of enemies (12 each wave)
* Each wave increases difficulty by shifting the weighted enemy spawn chances
* Three enemy types with different sprites, health and score
* Random enemy spawn locations and timing
* Enemy shooting - Some enemies are able to shoot, either straight down, or at the player
* Collisions - If you crash your ship into an enemy, you will destroy it and get the
destroy score, but you will damage your ship.  Be careful.
* Health regen - Stop shooting for a second to begin ship repairs.
* One life - You only get one ship, look after it.


#### Game World
* Game field is wider than the window.  The camera keeps the 
player ship centered horizontally until the edge of the field.
* Continuously scrolling background
* Wave score and kills are shown between waves
* Game Over screen shows total score and allows you to start a new game

### Build
You'll need a cpp compiler like gcc, cmake and SFML installed  
`cmake .` to configure the build  
`cmake --build .` to build the project  
Or just build it in your IDE