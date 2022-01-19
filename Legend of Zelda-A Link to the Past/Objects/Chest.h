#pragma once
#include "Object.h"

class Chest : public Object
{
public:
	Chest(string size, string itemType, D3DXVECTOR2 scale, bool base);
	~Chest();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 position);
	D3DXVECTOR2 Position() { return chest->Position(); }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 scale);
	D3DXVECTOR2 Scale() { return chest->TextureSize(); }

	void DrawBound(bool b);

	void Open();
	bool Exist() { return exist; }

	Sprite* GetSprite();

	string GetItemType() { return itemType; }

private:
	Animation* chest;
	Sprite* item;
	string itemType;
	bool exist;

	float time;
};