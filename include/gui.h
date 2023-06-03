#pragma once


typedef enum {
    StartModeFadeIn,
    StartMode,
    StartModeFadeOut,
    LevelSelectModeFadeIn,
    LevelSelectMode,
    LevelSelectModeFadeOut,
    BoxesSelectModeFadeIn,
    BoxesSelectMode,
    BoxesSelectModeFadeOut,
    GameModeStart,
    GameModeFadeIn,
    GameMode,
    GameModeFadeOut,
    GameWonModeFadeIn,
    GameMode3DFadeIn,
    GameMode3D,
    GameMode3DFadeOut,
    GameWonModeFadeOut,
    PushAnimation,
    PushAnimation3D,
    HighScoreModeFadeIn,
    HighScoreMode,
    HighScoreModeFadeOut,
} GuiMode;

extern GuiMode mode;

// main loop of thie project
void mainloop(void);