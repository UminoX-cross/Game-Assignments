#include "Bat.h"


Bat::Bat(GSprite* sprite, int posX, int posY)
{
	this->sprite = sprite;

	this->height = sprite->_texture->FrameHeight;
	this->width = sprite->_texture->FrameWidth;

	this->posStart.x = posX;
	this->posStart.y = posY;
	this->posCur = this->posStart;
}

Bat::~Bat()
{
	if (sprite != NULL)
	{
		delete sprite;
		sprite = NULL;
	}
}


void Bat::MoveUp(int speed)
{
	posCur.y -= speed;
	if (posCur.y - height/2 < 0)
		posCur.y = height/2;
}


void Bat::MoveDown(int speed)
{
	posCur.y += speed;
	if (posCur.y + height/2 > G_ScreenHeight)
		posCur.y = G_ScreenHeight - height/2;
}

RECT Bat::GetBound()
{
	RECT bound;
	bound.left = posCur.x - width / 2;
	bound.right = posCur.x + width / 2;
	bound.top = posCur.y - height / 2;
	bound.bottom = posCur.y + height / 2;

	return bound;
}
