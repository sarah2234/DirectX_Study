#include "stdafx.h"
#include "Door.h"

Door::Door(D3DXVECTOR2 scale, D3DXVECTOR2 position, bool open, string direction)
{
	wstring spriteFile = Textures + L"Legend of Zelda/Eastern Palace Parts.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	door = new Animation;
	Clip* clip;
	if (open == true)
	{
		visible = false;

		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 70, 2, 102, 36), 0.1); // x: 32, y: 34
		door->AddClip(clip);
	}
	else if (open == false)
	{
		visible = true;

		clip = new Clip(PlayMode::End);
		//clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 2, 68, 36), 0.1); // x: 32, y: 34
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 1, 0, 1), 0.1); // 닫힌 문의 모습이 default
		door->AddClip(clip); // closed

		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 2, 2, 34, 36), 0.1);
		door->AddClip(clip); // open
	}
	door->Scale(scale);
	door->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	door->Play(0);
	if (direction == "top")
		door->RotationDegree(0, 0, 0);
	else if (direction == "bottom")
		door->RotationDegree(180, 0, 0);
	else if (direction == "right")
		door->RotationDegree(0, 0, -90); // 반시계 방향
	else if (direction == "left")
		door->RotationDegree(0, 0, 90);

	door->Scale(scale);
	bOpen = open;
}

Door::~Door()
{
	SAFE_DELETE(door);
}

void Door::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	door->Update(V, P);
}

void Door::Render()
{
	if (visible)
		door->Render();
}

void Door::Position(float x, float y)
{
	door->Position(x, y);
}

void Door::Position(D3DXVECTOR2 position)
{
	door->Position(position);
}

void Door::Scale(float x, float y)
{
	door->Scale(x, y);
}

void Door::Scale(D3DXVECTOR2 scale)
{
	door->Scale(scale);
}

void Door::DrawBound(bool b)
{
	door->DrawBound(b);
}

void Door::Open(bool b)
{
	if (visible && b)
	{
		door->Play(1);
		bOpen = true;
	}
	else if (visible && !b)
		door->Play(0);
}
