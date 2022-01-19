#include "stdafx.h"
#include "Field.h"
#include "Viewer/Following.h"
#include "EasternPalace.h"


Field::Field(SceneValues * values, D3DXVECTOR2 position)
	:Scene(values, position), moveSpeed(200), on(true)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	field = new Sprite(Textures + L"Legend of Zelda/Light World.png", shaderFile);
	field->Scale(2.5, 2.5);

	field->Position(position);
}

Field::~Field()
{
	SAFE_DELETE(field);
}

void Field::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	D3DXVECTOR2 position = field->Position();

	if (Key->Press('A'))
	{
		position.x += moveSpeed * Timer->Elapsed();
	}
	else if (Key->Press('D'))
	{
		position.x -= moveSpeed * Timer->Elapsed();
	}
	else if (Key->Press('S'))
	{
		position.y += moveSpeed * Timer->Elapsed();
	}
	else if (Key->Press('W'))
	{
		position.y -= moveSpeed * Timer->Elapsed();
	}

	field->Position(position);
	field->Update(V, P);
}

void Field::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);

	field->Render();
}

void Field::On(bool b)
{
	on = b;
}

void Field::SetPosition(D3DXVECTOR2 position)
{
	field->Position(position);
}
