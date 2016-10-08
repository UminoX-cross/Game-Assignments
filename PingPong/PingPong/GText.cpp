#include "GText.h"
#include <tchar.h>


GText::GText(LPDIRECT3DDEVICE9 device, std::wstring &name, int width, int height)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height = height;
	fontDesc.Width = width;
	fontDesc.Weight = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy_s(fontDesc.FaceName, _T("Segoe UI"));
	D3DXCreateFontIndirect(device, &fontDesc, &font);
}


GText::~GText()
{
	if (font != NULL)
	{
		font->Release();
		font = NULL;
	}
}

void GText::Draw(LPCSTR lpString, int x, int y, D3DCOLOR color)
{
	RECT R = { x, y, 0, 0 };
	font->DrawTextA(0, lpString, -1, &R, DT_NOCLIP, color);
}

void GText::Draw(std::string str, int x, int y, D3DCOLOR color)
{
	RECT R = { x, y, 0, 0 };
	font->DrawTextA(0, const_cast<char*>(str.c_str()), -1, &R, DT_NOCLIP, color);
}