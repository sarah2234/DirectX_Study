#pragma once
#include "Camera.h"

class Freedom : public Camera
{
public:
	Freedom(float speed = 200.0f);
	~Freedom();

	void Update();

	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);


private:
	void Move(D3DXVECTOR2& translation);
private:
	float speed;
};
