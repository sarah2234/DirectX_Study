#include "stdafx.h"
#include "Vase.h"
#include <math.h>

Vase::Vase(string itemType)
	:lifted(false), itemObtainable(false), time(0)
{
	wstring spriteFile = Textures + L"Legend of Zelda/Items.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	Clip* clip;

	vase = new Sprite(Textures + L"Legend of Zelda/Eastern Palace Parts.png", shaderFile, 102, 111, 114, 124);
	
	//아이템 나타날 때 통통 튀는 거 2번 표현하기 위해 밑에 공백 3px, 1px 추가
	if (itemType == "green rupee")
	{
		item = new Animation;
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 249, 44, 263), 0.08f);
		item->AddClip(clip);
		clip = new Clip(PlayMode::End); //266, 264
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 249, 44, 264), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 249, 60, 265), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 68, 249, 76, 266), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 249, 44, 265), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 249, 60, 264), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 68, 249, 76, 263), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 249, 44, 264), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 52, 249, 60, 263), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 68, 249, 76, 263), 0.08f); //3
		item->AddClip(clip);
		item->Scale(0, 0);
		item->Play(0);
	}
	else if (itemType == "blue rupee")
	{
		item = new Animation;
		clip = new Clip(PlayMode::Loop); //266, 264
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 84, 249, 92, 263), 0.08f);
		item->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 84, 249, 92, 264), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 100, 249, 108, 265), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 116, 249, 124, 266), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 84, 249, 92, 265), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 100, 249, 108, 264), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 116, 249, 124, 263), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 84, 249, 92, 264), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 100, 249, 108, 263), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 116, 249, 124, 263), 0.08f); //3
		item->AddClip(clip);
		item->Scale(0, 0);
		item->Play(0);
	}
	else if (itemType == "5 arrows")
	{
		item = new Animation;
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 48), 0.08f);
		item->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 49), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 50), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 51), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 50), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 49), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 48), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 49), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 48), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 32, 161, 48), 0.08f); //3
		item->AddClip(clip);
		item->Scale(0, 0);
		item->Play(0);
	}
	else if (itemType == "small key")
	{
		item = new Animation;
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 184), 0.08f);
		item->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 185), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 186), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 187), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 186), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 185), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 184), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 185), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 184), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 232, 169, 240, 1874), 0.08f); //3
		item->AddClip(clip);
		item->Scale(0, 0);
		item->Play(0);
	}
	else if (itemType == "small magic powder")
	{
		item = new Animation;
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 288), 0.08f);
		item->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 289), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 290), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 291), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 290), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 289), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 288), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 289), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 288), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 280, 128, 288), 0.08f); //3
		item->AddClip(clip);
		item->Scale(0, 0);
		item->Play(0);
	}
	else if (itemType == "heart")
	{
		item = new Animation;
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 287), 0.08f);
		item->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 288), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 289), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 290), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 289), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 288), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 287), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 288), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 287), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 104, 280, 112, 287), 0.08f); //3
		item->AddClip(clip);
		item->Scale(0, 0);
		item->Play(0);
	}
	else if (itemType == "none")
	{
		item = new Animation;
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 0, 1, 1), 0.08f);
		item->AddClip(clip);
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 0, 1, 1), 0.08f);
		item->AddClip(clip);
		item->Scale(0, 0);
		item->Play(0);
	}
	this->itemType = itemType;
}

Vase::~Vase()
{
	SAFE_DELETE(vase);
	SAFE_DELETE(item);
}

void Vase::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	vase->Update(V, P);
	item->Update(V, P);
	
	if (Sprite::Obb(player->GetSprite(), vase) && !lifted) //항아리 아직 안 들린 상태
	{
		player->Position(player->Position());
		if (Key->Down('C') && !player->IsLifting()) //항아리 들기
		{
			player->Lift(true);
			item->Scale(vase->Scale());
			item->Play(1);
			lifted = true;
			itemObtainable = true;
			vase->Position(0, 0);
		}
	}
	if (lifted && Key->Down('C')) //항아리 들은 상태에서 던지기
	{
		player->Throw(true);
		lifted = false;
	}
	if (Sprite::Obb(player->GetSprite(), item->GetSprite()) && itemObtainable && item->IsLastClip()) //항아리의 아이템 먹기
	{
		item->Scale(0, 0);
		if (itemType == "green rupee")
			player->SetItem("rupee", 1);
		else if (itemType == "blue rupee")
			player->SetItem("rupee", 10);
		else if (itemType == "5 arrows")
			player->SetItem("arrow", 5);
		else if (itemType == "small key")
			player->SetItem("key", 1);
		else if (itemType == "small magic powder")
			player->SetItem("magic", 2);
		else if (itemType == "heart")
			player->SetItem("stamina", 1);

		itemObtainable = false;
	}
}

void Vase::Render()
{
	vase->Render();
	item->Render();
}

void Vase::Position(float x, float y)
{
	vase->Position(x, y);
	item->Position(x, y);
}

void Vase::Position(D3DXVECTOR2 position)
{
	vase->Position(position);
	item->Position(position);
}

void Vase::Scale(float x, float y)
{
	vase->Scale(x, y);
	//item->Scale(x, y);
}

void Vase::Scale(D3DXVECTOR2 scale)
{
	vase->Scale(scale);
	//item->Scale(scale);
}

void Vase::DrawBound(bool b)
{
	vase->DrawBound(b);
	item->DrawBound(b);
}
