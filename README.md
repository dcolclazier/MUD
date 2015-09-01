# MUD


So this is pretty bare, as of now; my goal with this project was to design a framework that could be expanded on by introductory programmers, and eventually be turned into a fully-fledged out multiplayer text-based video game. Back in the day, these used to be called MUD's(multi-user dungeon), and were basically the precursor to the first MMORPG.

The concept is dated, yes... text-based video games havent been mainstream for close to 20 years... but if you take any modern video game and strip away the concept of shaders, textures, and other graphical components that beginning coders would probably find overly daunting, what you have left is basically what I'm proposing we create. The things one could learn about game development from a coding perspective... ai, pathfinding techniques, entity/gameobject systems, event-driven programming, data-driven programming, git collaboration... the list is practically limitless! 

This is the main reason I picked it as a project... that, and I've had a secret desire since I was a kid to design my own MUD... So with that said, let me talk you through the game...

You log in, and end up in some field somewhere...You control some sort of virtual character, with attributes and equipment,  After wondering around by typing various commands into the console, you wonder across a computer character who tells you how to start 'playing.' You can see other players around you (it is multiplayer) and can chat with them (think of a glorified chat server built into a rpg video game). The game is then built up of hundreds, even thousands of 'rooms', each with their own behaviour; monsters, puzzles, mini-games, riddles, player-vs-player combat, etc.

Here's what works so far:

You can log in (I host the server from my house) and chat. You can log things to a file... There is a concept of chat channels, and a permission system to join them... There's a framework to build a bunch of commands (the things like say, north, kill, eat, etc) that players would type in, and a framework to use events to communicate between components. Next on the list is to build the concept of components, so we don't end up with a nightmarish multiple-inheritance chain/blob(more on that later) You can log in, create a user with a password, which gets saved PLAIN TEXT to an xml database (don't tell me your bank password, please..)... That's pretty much it so far - it's pretty bare-bones.

A lot of the existing code will be well out of scope for any beginnning c++ programmer, but I will be taking most of that weight of that, and I've tried my best to design the framework/game-engine such that the code that makes the game run is easy to write.

And that's my pitch. Interested? Let me know!

      
