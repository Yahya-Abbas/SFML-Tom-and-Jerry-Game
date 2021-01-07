# SFML-Tom-and-Jerry-Game
A simple cat and mouse game using C++ &amp; SFML library

## Game Layout & Rules
The game consists of: **Island, Water, Bridge, Mouse, and Four Cats**
- We have an island surronded by water and there is a bridge leading to safety on the middle of the right side of the island.
-	The player can quit the game by pressing Escape or by closing the Window.
-	The player can know the state of the game (i.e. # of moves left and game result) by the count and state displayed .
-	All characters must move either horizontally or vertically (There are no diagonal moves).

### Cats
-	There are **4** cats on this island that will eat the mouse if they encountered it.  
-	The cats move randomly on the island, they never go to the water around the island.

### Mouse
- The player tries to help the mouse escape from the island without drowning or being eaten.
-	The mouse will move by the arrow keys (one direction at a time).
-	If **100** moves pass without escaping from the island, the mouse dies of *starvation*.
-	If the mouse touches the water, it will *drown*.
-	If the mouse touches a cat, it gets *eaten*.
-	If the mouse touches the bridge, it *escapes*.
