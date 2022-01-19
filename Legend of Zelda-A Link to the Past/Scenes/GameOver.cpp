#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver(SceneValues* values, D3DXVECTOR2 position)
	:Scene(values, position)
{
	game_over = new Sprite(Textures + L"Legend of Zelda/Game Over.png", Shaders + L"009_Sprite.fx");
	game_over->Position(position);
	game_over->Scale(1, 1);

	on = false;
}

GameOver::~GameOver()
{
	SAFE_DELETE(game_over);
}

void GameOver::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	if (on || player->GetItem("stamina") <= 0)
	{
		game_over->Update(V, P);
		game_over->Scale(1, 1);
		game_over->Position(player->Position());
		player->Scale(0, 0);
	}
	if (player->GetItem("stamina") > 0)
	{
		on = false;
		game_over->Position(0, 0);
		game_over->Scale(0, 0);
	}
}

void GameOver::Render()
{
	if (on || player->GetItem("stamina") <= 0)
		game_over->Render();
}

void GameOver::On(bool b)
{
	on = b;
}

void GameOver::SetPosition(D3DXVECTOR2 position)
{
	game_over->Position(position);
}
