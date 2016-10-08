
#include "SceneMain.h"
#include <string>

SceneMain::SceneMain(int _nCmdShow): CGame(_nCmdShow)
{
}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	line->Draw(distance, G_ScreenHeight / 2);
	line->Draw(G_ScreenWidth - distance, G_ScreenHeight / 2);

	player_1->Draw();
	player_2->Draw();
	ball->Draw();

	ball->Move();
	ball->SetCollideRect(player_1->GetBound());
	ball->SetCollideRect(player_2->GetBound());
	POINT pointColScreen = ball->SetCollideScreenBound(G_ScreenWidth, G_ScreenHeight);
	CalculateScore(pointColScreen);

	text->Draw(std::to_string(scorePlayer_1), 100, 50, D3DCOLOR_XRGB(120, 180, 210));
	text->Draw(std::to_string(scorePlayer_2), G_ScreenWidth-100, 50, D3DCOLOR_XRGB(120, 180, 210));
	text->Draw("W-S", 100, 0, D3DCOLOR_XRGB(90, 90, 90));
	text->Draw("Up-Down", G_ScreenWidth-200, 0, D3DCOLOR_XRGB(90, 90, 90));

	SetInput();
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	distance = 150;
	scorePlayer_1 = scorePlayer_2 = 0;

	player_1 = new Bat
	(
		new GSprite(new GTexture("Resources/bat.png"), 0),
		distance,
		G_ScreenHeight / 2
	);
	player_2 = new Bat
	(
		new GSprite(new GTexture("Resources/bat.png"), 0),
		G_ScreenWidth - distance,
		G_ScreenHeight / 2
	);
	ball = new Ball
	(
		new GSprite(new GTexture("Resources/ball.png"), 0),
		G_ScreenWidth / 2,
		G_ScreenHeight / 2,
		10
	);
	text = new GText(G_Device, std::wstring(L"playersScore"), 20, 30);
	line = new GSprite(new GTexture("Resources/line.png"), 0);
}

void SceneMain::SetInput()
{
	const int speed = 10;

	/// player 1
	if (KeyDown(DIK_W))
		player_1->MoveUp(speed);
	if (KeyDown(DIK_S))
		player_1->MoveDown(speed);

	/// player 2
	if (KeyDown(DIK_UP))
		player_2->MoveUp(speed);
	if (KeyDown(DIK_DOWN))
		player_2->MoveDown(speed);
}

SceneMain::~SceneMain(void)
{
	if (player_1 != NULL)
	{
		delete player_1;
		player_1 = NULL;
	}
	if (player_2 != NULL)
	{
		delete player_2;
		player_2 != NULL;
	}
	if (ball != NULL)
	{
		delete ball;
		ball = NULL;
	}
	if (text != NULL)
	{
		delete text;
		text = NULL;
	}
	if (line != NULL)
	{
		delete line;
		line = NULL;
	}
}

void SceneMain::CalculateScore(POINT collidedPoint)
{
	if (collidedPoint.x - ball->GetRadius() == 0
		|| (collidedPoint.y - ball->GetRadius() == 0 && collidedPoint.x <= distance)
		|| (collidedPoint.y + ball->GetRadius() == G_ScreenHeight && collidedPoint.x <= distance))
	{
		scorePlayer_2++;
		ball->Restart();
	}
	if (collidedPoint.x + ball->GetRadius() == G_ScreenWidth
		|| (collidedPoint.y - ball->GetRadius() == 0 && collidedPoint.x >= G_ScreenWidth - distance)
		|| (collidedPoint.y + ball->GetRadius() == G_ScreenHeight && collidedPoint.x >= G_ScreenWidth - distance))
	{
		scorePlayer_1++;
		ball->Restart();
	}
}