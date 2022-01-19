#pragma once
#include "Object.h"

class Vase : public Object
{
public:
	Vase(string itemType, D3DXVECTOR2 scale, bool base);
	~Vase();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 position);
	D3DXVECTOR2 Position() { return vase->Position(); }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 scale);
	D3DXVECTOR2 Scale() { return vase->TextureSize(); }

	void DrawBound(bool b);

	Sprite* GetSprite() { return vase; }

	bool Exist() { return exist; }

private:
	Sprite* vase;
	Animation* item;
	string itemType;
	bool exist;
	bool lifted;
	bool itemObtainable;
	float time;
};