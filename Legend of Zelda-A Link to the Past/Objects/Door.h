#pragma once
#include "Object.h"

class Door
{
public:
	Door(D3DXVECTOR2 scale, D3DXVECTOR2 position, bool open, string direction);
	~Door();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 position);
	D3DXVECTOR2 Position() { return door->Position(); }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 scale);
	D3DXVECTOR2 Scale() { return door->TextureSize(); }

	void DrawBound(bool b);

	Sprite* GetSprite() { return door->GetSprite(); }

	void Open(bool b);
	bool GetBOpen() { return bOpen; }

	UINT currentClip() { return door->CurrentClip(); }

private:
	Animation* door;
	bool bOpen;
	bool visible; // 처음부터 열려있는 문이면 render x
};