#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	:position(0,0)
{
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//D3DXMatrixTranslation(&view, -position.x, -position.y, 0.0f);
	D3DXMatrixTranslation(&view, -player->Position().x + Width / 2, -player->Position().y + Height / 2, 0.0f);
}
