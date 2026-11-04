#include <thirdparty/imgui-bundle/dcimgui.h>
#include <thirdparty/raylib/raylib.h>
#include <thirdparty/rlImGui/rlImGui.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void);

static const int screenWidth  = 1280;
static const int screenHeight = 800;
static Texture2D logo;

int main(void) {
    InitWindow(screenWidth, screenHeight, "MyGame - Basic Window");
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    rlImGuiSetup(true); // sets up ImGui with either a dark or light default theme

    logo = LoadTexture("contents/raylib_logo.png");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();
    rlImGuiShutdown();

    return 0;
}

void UpdateDrawFrame(void) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    rlImGuiBegin();

    ImGui_ShowDemoWindow(NULL);

    rlImGuiEnd();

    DrawText("Congrats! You created your first window!", 190, 50, 20, LIGHTGRAY);

    DrawTexture(
        logo, screenHeight / 2 - logo.width / 2 - 200, screenHeight / 2 - logo.height / 2, WHITE
    );

    EndDrawing();
}
