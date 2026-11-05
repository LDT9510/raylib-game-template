#include "app.h"

#include <thirdparty/imgui-bundle/dcimgui.h>
#include <thirdparty/raylib/raylib.h>
#include <thirdparty/rlImGui/rlImGui.h>

#include <string.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define WINDOWS_WIDTH  1280
#define WINDOWS_HEIGHT 800
#define WINDOWS_TITLE  "Raylib Game"
#define UI_FONT_SIZE   18
#define TARGET_FPS     60

// default constructors are missing from Dear Bindings
static void ImFontConfig_default(ImFontConfig* config);
static void load_ui_fonts(void);

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, WINDOWS_TITLE);
    rlImGuiSetLoadFontsCallback(load_ui_fonts);
    rlImGuiSetup(true);
    SetTargetFPS(TARGET_FPS);

    load_resources();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(draw_frame, 0, 1);
#else
    while (!WindowShouldClose()) {
    BeginDrawing();
        draw_frame();

        rlImGuiBegin();
        draw_ui();
        rlImGuiEnd();
    EndDrawing();
    }
#endif

    CloseWindow();
    rlImGuiShutdown();

    return 0;
}

static void ImFontConfig_default(ImFontConfig* config) {
    memset(config, 0, sizeof(*config));
    config->FontDataOwnedByAtlas = true;
    config->ExtraSizeScale = 1.0f;
    config->GlyphMaxAdvanceX = ((float)3.40282346638528860e+38); // FLT_MAX
    config->RasterizerMultiply = 1.0f;
    config->RasterizerDensity = 1.0f;
}

static void load_ui_fonts(void) {
    ImFontConfig default_config;
    ImFontConfig_default(&default_config);

    default_config.SizePixels = UI_FONT_SIZE;

    ImGuiIO* io = ImGui_GetIO();
    ImFontAtlas_AddFontDefault(io->Fonts, &default_config);
}
