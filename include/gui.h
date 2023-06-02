#pragma once


typedef enum {
    StartMode,
    MenuMode,
    GameMode,
    PushingMode,
    GameWonMode,
    HighScoreMode,
} GuiMode;

extern GuiMode guiMode;

// main loop of thie project
void guiMainLoop(void);