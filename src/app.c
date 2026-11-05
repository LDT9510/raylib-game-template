#include "app.h"

#include <thirdparty/imgui-bundle/dcimgui.h>
#include <thirdparty/raylib/raylib.h>

void load_resources(void) {

}

void draw_ui(void) {
    ImGui_ShowDemoWindow(NULL);
}

void draw_frame(void) {
    ClearBackground(RAYWHITE);
}
