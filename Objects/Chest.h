#pragma once


class Chest
{
public:
	Chest(string size, string itemType, D3DXVECTOR2 scale);
	~Chest();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 position);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 scale);

	void DrawBound(bool b);

	void Open();
	bool IsOpen() { return open; }

	Sprite* GetSprite();

	string GetItemType() { return itemType; }

private:
	Animation* chest;
	Sprite* item;
	string itemType;
	bool open;

	float time;
};