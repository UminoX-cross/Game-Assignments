#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include "Game.h"
#include "Bat.h"
#include "Ball.h"
#include "GText.h"

class SceneMain: public CGame
{
public: 	
	SceneMain(int _nCmdShow);
	~SceneMain();

private:
	int scorePlayer_1, scorePlayer_2;
	int distance;	// khoảng cách giữa vợt và biên ngang
	Bat *player_1, *player_2;
	Ball *ball;
	GText *text;
	GSprite *line;

	void CalculateScore(POINT collidedPoint);

protected:
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void SetInput();

};

#endif