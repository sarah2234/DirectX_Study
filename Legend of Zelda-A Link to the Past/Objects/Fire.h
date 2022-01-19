#pragma once

class Fire
{
public:
	Fire(wstring shaderFile, D3DXVECTOR2 start);
	~Fire();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Clip* GetClip() { return clip; }
	D3DXVECTOR2 Position() { return position; }

private:
	Clip* clip;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
};