#include "stdafx.h"
#include "Status.h"

Status::Status(D3DXVECTOR2 scale)
{

	/*wstring spriteFile = Textures + L"Legend of Zelda/Items.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	equipment = new Sprite(spriteFile, shaderFile, 0, 343, 26, 368);
	equipment->Scale(scale);
	magicBar = new Sprite(spriteFile, shaderFile, 30, 342, 46, 383);
	magicBar->Scale(scale);
	Sprite* magic = new Sprite(spriteFile, shaderFile, 53, 370, 63, 381);
	magics.push_back(magic);
	magic = new Sprite(spriteFile, shaderFile, 53, 359, 63, 369);
	magics.push_back(magic);
	magic = new Sprite(spriteFile, shaderFile, 53, 348, 63, 358);
	magics.push_back(magic);
	for (int i = 0; i < 3; i++)
	{
		magics[i]->Scale(scale);
	}
	life = new Sprite(spriteFile, shaderFile, 96, 355, 163, 364);
	life->Scale(scale);
	for (int i = 0; i < 5; i++)
	{
		Sprite* redHeart = new Sprite(spriteFile, shaderFile, 55, 395, 64, 403);
		redHeart->Scale(scale);
		redHearts.push_back(redHeart);
	}
	for (int i = 0; i < 5; i++)
	{
		Sprite* blackHeart = new Sprite(spriteFile, shaderFile, 55, 395, 64, 403);
		blackHeart->Scale(0, 0);
		blackHearts.push_back(blackHeart);
	}
	rupee = new Sprite(spriteFile, shaderFile, 4, 376, 13, 385);
	rupee->Scale(scale);
	bomb = new Sprite(spriteFile, shaderFile, 3, 393, 11, 402);
	bomb->Scale(scale);
	arrow = new Sprite(spriteFile, shaderFile, 16, 396, 30, 404);
	arrow->Scale(scale);
	key = new Sprite(spriteFile, shaderFile, 36, 394, 44, 402);
	key->Scale(scale);

	magicBar->Position(50, 50);
	equipment->Position(magicBar->Position().x + magicBar->Scale().x / 2, 50);
	rupee->Position(200, 25);
	bomb->Position(300, 25);
	arrow->Position(400, 25);
	key->Position(500, 25);
	life->Position(700, 15);
	for (int i = 0; i < redHearts.capacity(); i++)
	{
		redHearts[i]->Position(700 + redHearts[i]->Scale().x, 40);
		blackHearts[i]->Position(700 + redHearts[i]->Scale().x, 40);
	}*/
}

Status::~Status()
{
	/*SAFE_DELETE(equipment);
	SAFE_DELETE(magicBar);
	for (Sprite* magic : magics)
		SAFE_DELETE(magic);
	SAFE_DELETE(life);
	for (Sprite* redHeart : redHearts)
		SAFE_DELETE(redHeart);
	for (Sprite* blackHeart : blackHearts)
		SAFE_DELETE(blackHeart);
	SAFE_DELETE(rupee);
	SAFE_DELETE(bomb);
	SAFE_DELETE(arrow);
	SAFE_DELETE(key);*/
}

void Status::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	/*equipment->Update(V, P);
	magicBar->Update(V, P);
	
	for (Sprite* magic : magics)
		magic->Update(V, P);
	life->Update(V, P);
	for (Sprite* redHeart : redHearts)
		redHeart->Update(V, P);
	for (Sprite* blackHeart : blackHearts)
		blackHeart->Update(V, P);
	rupee->Update(V, P);
	bomb->Update(V, P);
	arrow->Update(V, P);
	key->Update(V, P);*/
}

void Status::Render()
{
	/*equipment->Render();
	magicBar->Render();
	for (Sprite* magic : magics)
		magic->Render();
	life->Render();
	for (Sprite* redHeart : redHearts)
		redHeart->Render();
	for (Sprite* blackHeart : blackHearts)
		blackHeart->Render();
	rupee->Render();
	bomb->Render();
	arrow->Render();
	key->Render();*/
}

void Status::MoveSpeed(float moveSpeed)
{
}

void Status::Position(D3DXVECTOR2 position)
{//400, 300
	//magicBar->Position(position.x - 350, position.y - 250);
	//equipment->Position(magicBar->Position().x + magicBar->Scale().x / 2, 50);
}
