# RED-VOID

Unofficial rollback.

## Building

You'll need Microsoft Visual Studio Community.
Clone the repository, and open the solution file ``RED VOID.sln``. Build all projects (``inject`` and ``redvoid``), and browse to the folder you've cloned the solution to. There will be the folder ``bin``; open, and copy the files ``inject.exe`` and ``redvoid.dll``. (if you've built in the Debug configuration, the name of the files will have ``_d`` at the end) to the game folder. Launch the game with ``inject.exe``.

## Features

Currently, the project is able to do the following:

- Load and save game states (only during battles) with ``F5`` and ``F6``, respectively.
- Reroutes Network mode to Single Player Versus.

## Known bugs
- After selecting Network mode, returning to the Main Menu will cause a soft-lock if you select Network mode once more.
