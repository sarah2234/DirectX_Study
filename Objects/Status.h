#pragma once
#include "Player.h"

class Status
{
public:
	Status(D3DXVECTOR2 scale);
	~Status();
	
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void MoveSpeed(float moveSpeed);
	void Position(D3DXVECTOR2 position);

private:
	Sprite* equipment;
	Sprite* magicBar;
	vector<Sprite*> magics;
	Sprite* life;
	vector<Sprite*> redHearts;
	vector<Sprite*> blackHearts;
	Sprite* rupee;
	Sprite* bomb;
	Sprite* arrow;
	Sprite* key;

	D2D1_RECT_F rectangle;
};