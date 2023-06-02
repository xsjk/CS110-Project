#pragma once


typedef enum {
    StartMode,
    LevelSelectMode,
    BoxesSelectMode,
    GameMode,
    PushingMode,
    GameWonMode,
    HighScoreMode,
} GuiMode;

extern GuiMode guiMode;

// main loop of thie project
void guiMainLoop(void);