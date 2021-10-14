#include "stdafx.h"
#include "Chest.h"

//extern Player* player;

Chest::Chest(string size, string itemType, D3DXVECTOR2 scale)
	:open(false)
{
	Clip* clip;
	wstring textureFile = Textures + L"Legend of Zelda/Eastern Palace Parts.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	chest = new Animation;
	if (size == "small")
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 13, 143, 29, 159), 0.3f); //closed
		chest->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 13, 161, 29, 177), 0.3f); //open
		chest->AddClip(clip);
	}
	else if (size == "big")
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 30, 127, 62, 151), 0.3f); //closed
		chest->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 30, 153, 62, 177), 0.3f); //open
		chest->AddClip(clip);
	}
	chest->Play(0);

	textureFile = Textures + L"Legend of Zelda/Items.png";
	if (itemType == "100 rupees")
	{
		item = new Sprite(textureFile, shaderFile, 204, 249, 220, 264);
		item->Scale(0, 0);
	}
	else if (itemType == "map")
	{
		item = new Sprite(textureFile, shaderFile, 180, 192, 198, 208);
		item->Scale(0, 0);
	}
	else if (itemType == "compass")
	{
		item = new Sprite(textureFile, shaderFile, 205, 193, 219, 208);
		item->Scale(0, 0);
	}
	else if (itemType == "boss key")
	{
		item = new Sprite(textureFile, shaderFile, 229, 192, 243, 208);
		item->Scale(0, 0);
	}
	else if (itemType == "bow")
	{
		item = new Sprite(textureFile, shaderFile, 69, 32, 76, 48);
		item->Scale(0, 0);
	}

	this->itemType = itemType;
}

Chest::~Chest()
{
	SAFE_DELETE(chest);
	SAFE_DELETE(item);
}

void Chest::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	chest->Update(V, P);
	item->Update(V, P);

	if (Sprite::Obb(player->GetSprite(), chest->GetSprite()) && !open && Key->Down('C')) //chest 연 후에 if문 실행되지 않도록 조정하기
	{//선 & 면 충돌로 해결보기
		Open();
		if (itemType == "boss key")
			player->SetItem("boss key", 1);
		else if (itemType == "map")
			player->SetItem("map", 1);
		else if (itemType == "compass")
			player->SetItem("compass", 1);
		else if (itemType == "bow")
			player->SetItem("bow", 1);
		else if (itemType == "100 rupees")
			player->SetItem("rupee", 100);
	}

	if (open)
	{
		time += Timer->Elapsed();
		chest->Play(1);
		D3DXVECTOR2 position = item->Position();
		if (time <= 0.8)
		{
			item->Position(position.x, position.y + Timer->Elapsed() * 60);
			item->Scale(2.5, 2.5);
			player->Stop(true);
		}
		else if (time <= 1.5)
		{
			item->Scale(2.5, 2.5);
			player->Stop(true);
		}
		else
		{
			item->Scale(0, 0);
			player->Stop(false);
		}

		/*if (player->IsLastClip())
		{
			open = false;
		}*/

		//item->Position(position);
	}
	else
		item->Scale(0, 0);
}

void Chest::Render()
{
	chest->Render();
	item->Render();
}

void Chest::Position(float x, float y)
{
	chest->Position(x, y);
	item->Position(x, y);
}

void Chest::Position(D3DXVECTOR2 position)
{
	chest->Position(position);
	item->Position(position);
}

void Chest::Scale(float x, float y)
{
	chest->Scale(x, y);
}

void Chest::Scale(D3DXVECTOR2 scale)
{
	chest->Scale(scale);
}

void Chest::DrawBound(bool b)
{
	chest->DrawBound(b);
}

void Chest::Open()
{
	if (open == false)
	{
		open = true;
		time = 0;
	}
}

Sprite* Chest::GetSprite()
{
	return chest->GetSprite();
}
