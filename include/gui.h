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

void guiUpdate(void);