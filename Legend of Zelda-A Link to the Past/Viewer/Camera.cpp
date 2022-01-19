#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	position = D3DXVECTOR2(player->Position().x - Width / 2, player->Position().y - Height / 2);
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (!player->GetTopBNearBorder() && !player->GetBottomBNearBorder())
		position.y = player->Position().y - Height / 2;
	if (!player->GetLeftBNearBorder() && !player->GetRightBNearBorder())
		position.x = player->Position().x - Width / 2;
	if (player->GetBAutoMoving() && !player->GetBAttacked())
		position = D3DXVECTOR2(player->Position().x - Width / 2, player->Position().y - Height / 2);
	D3DXMatrixTranslation(&view, -position.x, -position.y, 0.0f);
	//D3DXMatrixTranslation(&view, -player->Position().x + Width / 2, -player->Position().y + Height / 2, 0.0f);
}
