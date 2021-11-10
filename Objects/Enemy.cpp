#include "stdafx.h"
#include "Enemy.h"
#include <time.h>
#include <math.h>

Enemy::Enemy(string type, D3DXVECTOR2 scale, bool onScene)
	:moveSpeed(200), direction(-1), bBase(false)
{
	srand(time(NULL));
	enemy = new Animation;
	wstring spriteFile = Textures + L"Legend of Zelda/Enemy.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	Clip* clip;

	//left는 rotationDegree로 해결
	if (type == "skeleton")
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 17, 430, 31, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 430, 45, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 94, 430, 110, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 430, 45, 456), 0.3f);
		enemy->AddClip(clip); //right

		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 127, 430, 143, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 113, 430, 125, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 144, 430, 160, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 113, 430, 125, 456), 0.3f);
		enemy->AddClip(clip); //bottom

		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 60, 430, 76, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 47, 430, 59, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 77, 430, 93, 456), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 47, 430, 59, 456), 0.3f);
		enemy->AddClip(clip); //top

		stamina = 2;
		deadNum = 2;
	}

	if (type == "flying skeleton")
	{
		clip = new Clip(PlayMode::Loop);

		enemy->AddClip(clip); //right

		clip = new Clip(PlayMode::Loop);

		enemy->AddClip(clip); //bottom

		clip = new Clip(PlayMode::Loop);

		enemy->AddClip(clip); //top

		stamina = 5;
		deadNum = 2;
	}

	else if (type == "flying object")
	{//x: 18 y: 18
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 439, 47, 457, 65), 0.2f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 460, 47, 478, 65), 0.2f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 504, 47, 522, 65), 0.2f); //4
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 525, 47, 543, 65), 0.2f); //5
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 482, 47, 500, 65), 0.2f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 548, 47, 566, 65), 0.2f); //6
		enemy->AddClip(clip);

		stamina = 1;
		deadNum = 2;
	}

	else if (type == "jelly")
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 440, 80, 456, 96), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 459, 79, 475, 96), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 479, 79, 495, 96), 0.3f);
		enemy->AddClip(clip);

		stamina = 1;
		deadNum = 1;
	}

	else if (type == "small ball")
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 440, 328, 456, 344), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 457, 328, 473, 344), 0.2f);
		enemy->AddClip(clip);

		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 440, 328, 456, 344), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 457, 328, 473, 344), 0.2f);
		enemy->AddClip(clip);

		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 440, 328, 456, 344), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 457, 328, 473, 344), 0.2f);
		enemy->AddClip(clip);

		stamina = 1;
	}

	else if (type == "big ball")
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 482, 311, 512, 343), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 514, 311, 544, 343), 0.2f);
		enemy->AddClip(clip);

		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 482, 311, 512, 343), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 514, 311, 544, 343), 0.2f);
		enemy->AddClip(clip);

		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 482, 311, 512, 343), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 514, 311, 544, 343), 0.2f);
		enemy->AddClip(clip);

		stamina = 1;
	}

	else if (type == "armo knight")
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 10, 21, 42, 56), 0.3f);
		enemy->AddClip(clip);

		clip = new Clip(PlayMode::Loop); //blue
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 10, 21, 42, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 48, 18, 80, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 85, 13, 117, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 125, 9, 157, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 164, 7, 196, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 203, 4, 235, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 243, 9, 275, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 282, 11, 314, 56), 0.05f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 320, 13, 352, 56), 0.02f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 360, 15, 392, 56), 0.02f);
		enemy->AddClip(clip);

		clip = new Clip(PlayMode::End); //red standing
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 11, 205, 43, 240), 0.3f);
		enemy->AddClip(clip);
		clip = new Clip(PlayMode::Loop); //red jump
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 11, 205, 43, 240), 0.1f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 48, 203, 80, 240), 0.1f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 85, 201, 117, 240), 0.1f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 123, 199, 155, 240), 0.1f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 161, 197, 193, 240), 0.1f);
		clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 202, 172, 234, 240), 0.3f);
		enemy->AddClip(clip);

		stamina = 3;
		deadNum = 3;
	}

	else if (type == "green eye")
	{
		//Closed eye
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 408, 423, 432, 448), 0.3f);
		enemy->AddClip(clip);

		//open the eye
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 408, 423, 432, 448), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 437, 423, 461, 448), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 538, 424, 562, 449), 0.3f);
		enemy->AddClip(clip);

		//walk right
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 467, 424, 483, 448), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 489, 423, 504, 448), 0.3f);
		enemy->AddClip(clip);

		//walk front (bottom)
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 511, 424, 535, 449), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 538, 424, 562, 449), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 567, 425, 591, 449), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 538, 424, 562, 449), 0.3f);
		enemy->AddClip(clip);

		//walk back (top)
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 598, 425, 619, 449), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 625, 424, 647, 449), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 653, 424, 674, 448), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 625, 424, 647, 449), 0.3f);
		enemy->AddClip(clip);

		stamina = 1;
		deadNum = 2;
	}

	else if (type == "red eye")
	{
		//closed eye
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 409, 459, 433, 484), 0.3f);
		enemy->AddClip(clip);

		//open the eye
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 409, 459, 433, 484), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 438, 459, 462, 484), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 540, 460, 564, 485), 0.3f);
		enemy->AddClip(clip);

		//walk right
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 468, 460, 484, 484), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 491, 459, 506, 484), 0.3f);
		enemy->AddClip(clip);

		//walk front (bottom)
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 512, 460, 536, 484), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 540, 460, 564, 485), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 568, 461, 592, 485), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 540, 460, 564, 485), 0.3f);
		enemy->AddClip(clip);

		//walk back (top)
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 599, 461, 620, 485), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 627, 460, 649, 485), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 655, 461, 676, 485), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 627, 460, 649, 485), 0.3f);
		enemy->AddClip(clip);


		stamina = 2;
		deadNum = 2;
	}

	this->type = type;
	dead = false;
	enemy->Position(D3DXVECTOR2(Width / 2 + 50, Height / 2 + 50));
	enemy->Scale(2.5, 2.5);
	enemy->DrawBound(true);
	enemy->Play(0);
	this->onScene = onScene;

	slash = new Animation;
	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 0, 0, 1, 1), 0.1f);
	slash->AddClip(clip); //가짜 공격 모션(slash->Play()에는 1 또는 2 또는 3)

	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 5, 7, 21, 23), 0.1f);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 35, 12, 43, 20), 0.1f);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 57, 7, 73, 23), 0.1f);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 83, 8, 99, 23), 0.1f); //해골
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 110, 9, 124, 23), 0.1f);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 132, 4, 154, 26), 0.1f);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 157, 5, 181, 27), 0.1f);
	slash->AddClip(clip);

	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 83, 8, 99, 23), 0.1f); //해골
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 110, 9, 124, 23), 0.1f);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 132, 4, 154, 26), 0.1f);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/Death Effect.png", shaderFile, 157, 5, 181, 27), 0.1f);
	slash->AddClip(clip);

	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 155, 116, 199, 160), 0.2f); //점프하면서 공격하는 적
	clip->AddFrame(new Sprite(Textures + L"Legend of Zelda/armos-knight.png", shaderFile, 359, 116, 407, 164), 0.2f);
	slash->AddClip(clip);

	slash->Scale(0, 0);
	slash->Play(0);
	slash->Position(enemy->Position());
	this->scale = scale;

	for (int i = 0; i < 4; i++)
	{
		bLineCollisionIndex[i] = -1; // -1이면 충돌한 선이 없는 상태
		// 0 ~ 3 : 위, 아래, 양 옆으로 움직이는 몬스터
		// 4 ~ 7 : 대각선으로 움직이는 몬스터
	}

	if (type == "skeleton")
		direction = Math::Random(0, 3);
	else if (type == "flying object")
		direction = Math::Random(4, 7);

	// left right bottom top
	positionVector[0].x = enemy->Position().x - enemy->TextureSize().x * scale.x / 2;
	positionVector[0].y = enemy->Position().y;
	positionVector[1].x = enemy->Position().x + enemy->TextureSize().x * scale.x / 2;
	positionVector[1].y = enemy->Position().y;
	positionVector[2].x = enemy->Position().x;
	positionVector[2].y = enemy->Position().y - enemy->TextureSize().y * scale.y / 2;
	positionVector[3].x = enemy->Position().x;
	positionVector[3].y = enemy->Position().y + enemy->TextureSize().y * scale.y / 2;
}

Enemy::~Enemy()
{
	SAFE_DELETE(enemy);
	SAFE_DELETE(slash);
}

void Enemy::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	if (!onScene)
		return;

	D3DXVECTOR2 position = enemy->Position();

	// left right bottom top
	positionVector[0].x = enemy->Position().x - enemy->TextureSize().x * scale.x / 2;
	positionVector[0].y = enemy->Position().y;
	positionVector[1].x = enemy->Position().x + enemy->TextureSize().x * scale.x / 2;
	positionVector[1].y = enemy->Position().y;
	positionVector[2].x = enemy->Position().x;
	positionVector[2].y = enemy->Position().y - enemy->TextureSize().y * scale.y / 2;
	positionVector[3].x = enemy->Position().x;
	positionVector[3].y = enemy->Position().y + enemy->TextureSize().y * scale.y / 2;

	if (stamina <= 0)
	{
		Dead();
	}
	if (Sprite::Obb(player->GetSprite(), enemy->GetSprite())
		&& player->GetItem("stamina") > 0 && player->GetBInvincibleTime() == 0)
	{
		if (player->GetBBase() == bBase)
		{
			if (player->GetBAttacking()) //선 & 면 충돌로 해결보기... 는 시간 부족
			{
				Attacked(player->GetDirection());
			}
			else if (stamina > 0)
			{
				player->Attacked();
			}
		}
	}

	//적들 이동하는 거
	if (enemy->IsLastClip())
	{
		if (type == "skeleton")
			direction = Math::Random(0, 3);
		else if (type == "flying object")
			direction = Math::Random(4, 7);
	}

	if ((bLineCollisionIndex[0] != -1 && (direction == 0 || direction == 5 || direction == 7)) 
		|| (bLineCollisionIndex[1] != -1 && (direction == 1 || direction == 4 || direction == 6))
		|| (bLineCollisionIndex[2] != -1 && (direction == 2 || direction == 6 || direction == 7)) 
		|| (bLineCollisionIndex[3] != -1 && (direction == 3 || direction == 4 || direction == 5)))
	{
		if (type == "skeleton")
			direction = (direction + 1) % 4; // 선 충돌(벽에 부딪힘) 했을 때 방향 다시 설정
		else if (type == "flying object")
			direction = (direction + 1) % 4 + 4;
	}

	switch (direction) // 계속 움직이기 위해 이동 부분은 밖으로 빼냄
	{
	case 0:
		position.x -= moveSpeed * Timer->Elapsed() / 3; //left
		enemy->Play(0);
		enemy->RotationDegree(0, 180, 0);
		break;
	case 1:
		position.x += moveSpeed * Timer->Elapsed() / 3; //right
		enemy->Play(0);
		enemy->RotationDegree(0, 0, 0);
		break;
	case 2:
		position.y -= moveSpeed * Timer->Elapsed() / 3; //bottom
		enemy->Play(1);
		break;
	case 3:
		position.y += moveSpeed * Timer->Elapsed() / 3; //top
		enemy->Play(2);
		break;
	case 4:
		position.x += moveSpeed * Timer->Elapsed() / 3; // 우측 상단
		position.y += moveSpeed * Timer->Elapsed() / 3;
		break;
	case 5:
		position.x -= moveSpeed * Timer->Elapsed() / 3; // 좌측 상단
		position.y += moveSpeed * Timer->Elapsed() / 3;
		break;
	case 6:
		position.x += moveSpeed * Timer->Elapsed() / 3; // 우측 하단
		position.y -= moveSpeed * Timer->Elapsed() / 3;
		break;
	case 7:
		position.x -= moveSpeed * Timer->Elapsed() / 3; // 좌측 하단
		position.y -= moveSpeed * Timer->Elapsed() / 3;
		break;
	default:
		break;
	}

	enemy->Position(position);
	enemy->Update(V, P);
	slash->Update(V, P);
}

void Enemy::Render()
{
	if (!onScene)
		return;

	enemy->Render();
	slash->Render();
}

void Enemy::Position(float x, float y)
{
	enemy->Position(D3DXVECTOR2(x, y));
}

void Enemy::Position(D3DXVECTOR2 position)
{
	enemy->Position(position);
}

void Enemy::Attacked(int direction)
{
	if (type == "small ball" || type == "big ball")
		return;

	D3DXVECTOR2 position = enemy->Position();
	float time = 0;
	while (time <= 1)
	{
		if (direction == 3)
			enemy->Position(enemy->Position().x, enemy->Position().y - 0.5);
		else if (direction == 4)
			enemy->Position(enemy->Position().x, enemy->Position().y + 0.5);
		else if (direction == 1)
			enemy->Position(enemy->Position().x - 0.5, enemy->Position().y);
		else if (direction == 2)
			enemy->Position(enemy->Position().x + 0.5, enemy->Position().y);
		time += Timer->Elapsed();
	}
	if (stamina >= 1)
		stamina--;
}

void Enemy::Dead()
{
	slash->Position(enemy->Position());
	slash->Scale(enemy->Scale());
	slash->Play(deadNum);

	if (slash->IsLastClip())
	{
		enemy->Scale(0, 0);
		slash->Scale(0, 0);
	}

	direction = -1;
	dead = true;
}

void Enemy::OnScene(bool b)
{
	onScene = b;
}

void Enemy::MoveSpeed(float n)
{
	moveSpeed = n;
}

void Enemy::SetBBase(bool b)
{
	bBase = b;
}

Sprite* Enemy::GetSprite()
{
	return enemy->GetSprite();
}

void Enemy::Play(int n)
{
	enemy->Play(n);
}

void Enemy::Direction(int n)
{
	direction = n;
}

void Enemy::LineCollision(bool b, int lineIndex, string direction, string type_of_line)
{
	int i;
	if (direction == "left")
		i = 0;
	else if (direction == "right")
		i = 1;
	else if (direction == "bottom")
		i = 2;
	else if (direction == "top")
		i = 3;

	if (b == false)
	{
		bLineCollisionIndex[i] = -1;
		return;
	}

	bLineCollisionIndex[i] = lineIndex;
}
