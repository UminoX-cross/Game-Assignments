#ifndef _G_INPUT_H_
#define _G_INPUT_H_
#include <dinput.h>

extern LPDIRECTINPUT8 dInput;
extern LPDIRECTINPUTDEVICE8 diMouse;
extern LPDIRECTINPUTDEVICE8 diKeyboard;
extern DIMOUSESTATE mouseState;


int InitGInput(HWND hWnd);
void GInputRelease();

/// Keyboard
int InitKeyboard(HWND hWnd);
void PollKeyBoard();
int KeyDown(int keyCode);
int KeyUp(int keyCode);



/// Mouse
int InitMouse(HWND hWnd);
void PollMouse();
int MouseButton(int button);
int GetMouseX();
int GetMouseY();

#endif