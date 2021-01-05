# RED VOID

Unofficial rollback.

## Building and running

You'll need Microsoft Visual Studio Community.
- Clone the repository, and open the solution file ``RED VOID.sln``.
- Build all projects (``inject`` and ``redvoid``), and browse to the folder you've cloned the solution to.
- After building, there will be the folder ``bin`` on the solution folder; open it. 
- Open it, and copy the files ``inject.exe`` and ``redvoid.dll`` to the game folder. (If you've built in the Debug configuration, the name of the files will have ``_d`` at the end)
- Launch the game with ``inject.exe``.

## Features

Currently, the project is able to do the following:

- Load and save game states (only during battles) with ``F5`` and ``F6``, respectively.
- Reroutes Network mode to Single Player Versus to prevent problems.

## Known bugs/problems
- After selecting Network mode, returning to the Main Menu will cause a soft-lock if you select Network mode once more.
- Currently does not know whether or not the players are in the air when saving/loading the game state. This can cause some weird interactions.
