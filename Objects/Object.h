#pragma once
#include "stdafx.h"

class Object
{
public:
	virtual ~Object() {};

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;

	virtual void Position(float x, float y) = 0;
	virtual void Position(D3DXVECTOR2 position) = 0;
	virtual D3DXVECTOR2 Position() = 0;

	virtual void Scale(float x, float y) = 0;
	virtual void Scale(D3DXVECTOR2 scale) = 0;
	virtual D3DXVECTOR2 Scale() = 0;

	virtual Sprite* GetSprite() = 0;

	virtual bool Exist() = 0;

	D3DXVECTOR2 LeftPosition() { return positionVector[0]; }
	D3DXVECTOR2 RightPosition() { return positionVector[1]; }
	D3DXVECTOR2 BottomPosition() { return positionVector[2]; }
	D3DXVECTOR2 TopPosition() { return positionVector[3]; }

	bool GetBBase() { return bBase; }

protected:
	D3DXVECTOR2 positionVector[4]; // left, right, bottom, top
	D3DXVECTOR2 scale;
	bool bBase;
};