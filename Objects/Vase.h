#pragma once

class Vase
{
public:
	Vase(string itemType);
	~Vase();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 position);
	D3DXVECTOR2 Position() { return vase->Position(); }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 scale);
	D3DXVECTOR2 Scale() { return vase->Scale(); }

	void DrawBound(bool b);

	Sprite* GetSprite() { return vase; }

private:
	Sprite* vase;
	Animation* item;
	string itemType;
	bool lifted;
	bool itemObtainable;
	float time;
};