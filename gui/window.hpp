#pragma once

struct GLFWwindow;
struct ImGuiContext;

struct Window {
  GLFWwindow *window;
  ImGuiContext *context;
};

int InitWindow(Window &wnd, int width, int height, const char *name,
               Window *share = nullptr);
void SwitchWindow(Window &wnd);
void WindowBegin(Window &wnd);
void WindowEnd(Window &wnd);
void DestroyWindow(Window &wnd);
void WarmColors();
