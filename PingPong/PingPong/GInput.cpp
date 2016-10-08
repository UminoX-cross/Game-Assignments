#include "GInput.h"

LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8 diMouse;
LPDIRECTINPUTDEVICE8 diKeyboard;
DIMOUSESTATE mouseState;

char keyStates[256];

int InitGInput(HWND hWnd)
{
	HRESULT result = DirectInput8Create
	(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dInput,
		NULL
	);
	if (FAILED(result))
		return 0;

	// Init Keyboard device
	result = dInput->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL);
	if (FAILED(result))
		return 0;

	// Init Mouse device
	result = dInput->CreateDevice(GUID_SysMouse, &diMouse, NULL);
	if (FAILED(result))
		return 0;
	return 1;
}

void GInputRelease()
{
	if (dInput != NULL)
	{
		dInput->Release();
		dInput = NULL;
	}
	if (diMouse != NULL)
	{
		diMouse->Release();
		diMouse = NULL;
	}
	if (diKeyboard != NULL)
	{
		diKeyboard->Release();
		diKeyboard = NULL;
	}
}



#pragma region Keyboard
	int InitKeyboard(HWND hWnd)
	{
		HRESULT result;
		result = dInput->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result))
			return 0;
		result = diKeyboard->Acquire();
		if (FAILED(result))
			return 0;
		return 1;
	}

	void PollKeyBoard()
	{
		HRESULT result;
		result = diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		if (FAILED(result))
		{
			diKeyboard->Acquire();
			diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		}
	}

	int KeyDown(int keyCode)
	{
		return keyStates[keyCode] & 0x80;
	}

	int KeyUp(int keyCode)
	{
		return !keyStates[keyCode] & 0x80;
	}
#pragma endregion Keyboard



#pragma region Mouse
	int InitMouse(HWND hWnd)
	{
		HRESULT result = diMouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result))
			return 0;
		result = diMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(result))
			return 0;
		result = diMouse->Acquire();
		if (FAILED(result))
			return 0;
		return 1;
	}

	void PollMouse()
	{
		HRESULT result;
		result = diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		if (FAILED(result))
		{
			diMouse->Acquire();
			diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		}
	}

	int MouseButton(int button)
	{
		return mouseState.rgbButtons[button] & 0x80;
	}

	int GetMouseX() { return mouseState.lX; }
	int GetMouseY() { return mouseState.lY; }
#pragma endregion Mouse