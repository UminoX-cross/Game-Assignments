#include "Ball.h"


Ball::Ball(GSprite* sprite, int posX, int posY, int speed)
{
	this->sprite = sprite;
	this->radius = (sprite->_texture->FrameWidth) > (sprite->_texture->FrameHeight)
					? sprite->_texture->FrameWidth / 2 : sprite->_texture->FrameHeight / 2;

	this->posStart.x = posX;
	this->posStart.y = posY;
	this->posCur = this->colPosBefore = posStart;
	this->speed = speed;

	/// Random velocity
	do
	{
		srand(time(NULL));
		velocity.x = -(rand() % 6); // random -10 -> 10
		velocity.y = -(rand() % 6);
	} while (velocity.x == 0 || velocity.y == 0);
}


Ball::~Ball()
{
	if (sprite != NULL)
	{
		delete sprite;
		sprite = NULL;
	}
}

void Ball::Restart()
{
	posCur = colPosBefore = posStart;
	/// Random velocity
	do
	{
		srand(time(NULL));
		velocity.x = -(rand() % 10); // random -10 -> 10
		velocity.y = -(rand() % 10);
	} while (velocity.x == 0 || velocity.y == 0);
}

void Ball::Move()
{
	posCur.x += velocity.x;
	posCur.y += velocity.y;
}

void Ball::CalculatePositionCurrentY()
{
	posCur.y = (float)(velocity.y * (posCur.x - colPosBefore.x) / velocity.x + colPosBefore.y);
}

void Ball::CalculatePositionCurrentX()
{
	posCur.x = (float)(velocity.x * (posCur.y - colPosBefore.y) / velocity.y + colPosBefore.x);
}

POINT Ball::SetCollideRect(const RECT & rect)
{
	if (posCur.y - radius <= rect.bottom
		&& posCur.y + radius >= rect.top
		&& posCur.x - radius <= rect.right
		&& posCur.x + radius >= rect.left)
	{
		if ((posCur.x - radius < rect.right)
			&& (posCur.x > rect.left)
			&& (posCur.y > rect.top)
			&& (posCur.y < rect.bottom))
		{
			posCur.x = rect.right + radius;
			CalculatePositionCurrentY();
			velocity.x *= -1;
		}
		if ((posCur.x + radius > rect.left)
			&& (posCur.x < rect.right)
			&& (posCur.y > rect.top)
			&& (posCur.y < rect.bottom))
		{
			posCur.x = rect.left - radius;
			CalculatePositionCurrentY();
			velocity.x *= -1;
		}
		if ((posCur.y + radius > rect.top)
			&& (posCur.y < rect.bottom)
			&& (posCur.x < rect.right)
			&& (posCur.x > rect.left))
		{
			posCur.y = rect.top - radius;
			CalculatePositionCurrentX();
			velocity.y *= -1;
		}
		if ((posCur.y - radius < rect.bottom)
			&& (posCur.y > rect.top)
			&& (posCur.x < rect.right)
			&& (posCur.x > rect.left))
		{
			posCur.y = rect.bottom + radius;
			CalculatePositionCurrentX();
			velocity.y *= -1;
		}
		colPosBefore = posCur;
		return posCur;
	}
	return POINT{ -1,-1 };
}

POINT Ball::SetCollideScreenBound(const int & width, const int & height)
{
	RECT screenBound;
	screenBound.left = 0;
	screenBound.right = width;
	screenBound.top = 0;
	screenBound.bottom = height;

	/// check if the ball still stay into screen
	if (posCur.x - radius >= screenBound.left
		&& posCur.x + radius <= screenBound.right
		&& posCur.y - radius >= screenBound.top
		&& posCur.y + radius <= screenBound.bottom)
		return POINT{ -1, -1 };

	// translate ball to touch the screen bound
	if (posCur.x - radius < screenBound.left)
	{
		posCur.x = screenBound.left + radius;
		CalculatePositionCurrentY();
	}
	if (posCur.x + radius > screenBound.right)
	{
		posCur.x = screenBound.right - radius;
		CalculatePositionCurrentY();
	}
	if (posCur.y - radius < screenBound.top)
	{
		posCur.y = screenBound.top + radius;
		CalculatePositionCurrentX();
	}
	if (posCur.y + radius > screenBound.bottom)
	{
		posCur.y = screenBound.bottom - radius;
		CalculatePositionCurrentX();
	}

	// Respone collision
	// Find min distance to screen edge
	int dis[4];	// distance to: left, right, top, bottom
	int disMin;
	dis[0] = posCur.x - screenBound.left;
	dis[1] = screenBound.right - posCur.x;
	dis[2] = posCur.y - screenBound.top;
	dis[3] = screenBound.bottom - posCur.y;
	disMin = dis[0];

	for each (int d in dis)
		if (disMin > d) disMin = d;
	if (disMin == dis[0] || disMin == dis[1])
		velocity.x *= -1;
	else
		velocity.y *= -1;

	colPosBefore = posCur;
	return posCur;
}