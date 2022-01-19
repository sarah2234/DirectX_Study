#pragma once

class Inventory
{
public:
	Inventory(D3DXVECTOR2 scale);
	~Inventory();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void On(bool b);
	bool IsOn() { return on; }

private:
	Sprite* inventory;
	Sprite* bossKey;
	Sprite* map;
	Sprite* compass;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	bool on;
};
