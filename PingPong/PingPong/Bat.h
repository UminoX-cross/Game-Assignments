#ifndef _BAT_H
#define _BAT_H

#include "GSprite.h"

class Bat
{
protected:
	D3DXVECTOR2 posStart;	/// Vị trí đầu tiên
	D3DXVECTOR2 posCur;		/// Vị trí hiện D3DXVECTOR2
	int height;
	int width;

public:
	GSprite *sprite;

	Bat(GSprite* sprite, int posX = 0, int posY = 0);
	~Bat();

	void Draw() { sprite->Draw(posCur.x, posCur.y); }
	void MoveUp(int speed);
	void MoveDown(int speed);
	RECT GetBound();
};
#endif