#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	float mPositionX, mPositionY, mPositionZ;
	float mRotationX, mRotationY, mRotationZ;
	D3DXMATRIX mViewMatrix;
};
