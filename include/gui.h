#pragma once


typedef enum {
    StartMode,
    LevelSelectMode,
    BoxesSelectMode,
    GameStartMode,
    GameMode,
    PushAnimation,
    GameWonMode,
    HighScoreMode,
} GuiMode;

extern GuiMode mode;

// main loop of thie project
void mainloop(void);