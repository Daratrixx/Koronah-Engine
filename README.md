# Koronah-Engine
C++ game engine using SDL2 and OpenGL

# How to use
 - The Game class is a factory, that creates all engines such as GraphicEngine and SoundEngine (soon™), as well as all differents GameStates
 - GameStates are different state (dah!) that can have the program. It can be anything, from a hard-coded level to an awesome menu or a sick loading screen.
 - When rendering a scene (like in the GameStatePlayGround), all entities must be sent to the GraphicEngine using addToRender(...) before the call to renderPlayGround() wich will render all entities sent.
 - 3D Models need to be .obj, without animation, material, nor quads. If a model doesn't load, open it in say Blender and re-export it (normals, no quad, -Z forward, +Y up, no animation, no material)

# TO DO
 - *Organisation* : put *.h* and *.cpp* files into folders, not in the root like a total thrash.
 - *Organisation* : add some more comments you damn retard!
 - *Programation* : create the SoundEngine (soon™).
 - *Programation* : create a file parser, to load datas from disc instead of hard coding everything.
 - *Programation* : clear the OpenGL calls logic wich is currently messy (everything in GraphicEngine or everything spreaded out?).
 - ... put more stuff here.
