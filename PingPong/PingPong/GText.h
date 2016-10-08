#ifndef _G_TEXT_H_
#define _G_TEXT_H_
#include <d3dx9core.h>
#include <string>

class GText
{
protected:
	LPD3DXFONT font;

public:
	GText(LPDIRECT3DDEVICE9 device, std::wstring &name, int width, int height);
	~GText();
	void Draw(LPCSTR lpString, int x, int y, D3DCOLOR color);
	void Draw(std::string str, int x, int y, D3DCOLOR color);
};

#endif