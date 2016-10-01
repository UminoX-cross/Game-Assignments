#ifndef _BALL_H
#define _BALL_H

#include "GSprite.h"

class Ball : public GSprite
{
protected:
	POINT posStart;	// điểm bắt đầu
	POINT colPosBefore;	// điểm va chạm trước
	POINT posCur;
	int speed;
	D3DXVECTOR2 velocity;	// vận tốc
	int radius;				// bán kính
	void CalculatePositionCurrentY();
	void CalculatePositionCurrentX();

public:
	GSprite *sprite;
	Ball(GSprite *sprite, int posX = 0, int posY = 0, int speed = 0);
	~Ball();

	int GetRadius() { return this->radius; }
	void Restart();
	void Draw() { sprite->Draw(posCur.x, posCur.y); }
	void Move();
	POINT SetCollideRect(const RECT & rect);
	POINT SetCollideScreenBound(const int & width, const int & height);
};
#endif