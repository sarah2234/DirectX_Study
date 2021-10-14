#include "stdafx.h"
#include "Player.h"
#include <math.h>

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusOffset(-180,-120), bMove(false), autoMovingTime(0.0),
	attack(false), lifting(false), throwing(false), pose(false), stop(false),
	left(false), right(false), bottom(false), top(true),
	magic(0), rupee(0), bomb(0), arrow(0), key(0), stamina(10), bossKey(0), map(0), compass(0), bow(0),
	invincibleTime(0.0)
{
	//얼굴 앞면이 보이면 bottom, 아니면 top
	//오른쪽으로 향하면(왼쪽 얼굴) right, 아니면 left
	player = new Animation;

	player->Scale(2.5, 2.5);
	player->Position(Width / 2, Height / 2);

	wstring spriteFile = Textures + L"Legend of Zelda/Link.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle-뒷 모습
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 89, 3, 106, 29), 0.3f); // x: 17, y: 26
		player->AddClip(clip);
	}
	//Idle-앞 모습
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 0, 49, 25), 0.3f); // x: 16, y: 25
		player->AddClip(clip);
	}
	//Idle-left
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 151, 2, 173, 25), 0.3f); // x: 22, y: 23
		player->AddClip(clip);
	}

	//Run-top
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 2, 143, 19, 166), 0.1f);  //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 32, 143, 49, 166), 0.1f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 62, 143, 79, 166), 0.1f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 92, 143, 109, 166), 0.1f); //4
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 122, 143, 139, 166), 0.1f); //5
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 152, 143, 169, 166), 0.1f); //6
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 182, 143, 199, 166), 0.1f); //7
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 212, 143, 229, 166), 0.1f); //8
		player->AddClip(clip);
	}
	//Run-bottom
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 3, 33, 18, 55), 0.1f);  //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 33, 49, 55), 0.1f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 63, 33, 79, 55), 0.1f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 93, 33, 109, 55), 0.1f); //4
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 123, 33, 139, 55), 0.1f); //5
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 153, 33, 169, 55), 0.1f); //6
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 183, 33, 199, 55), 0.1f); //7
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 213, 33, 229, 55), 0.1f); //8
		player->AddClip(clip);
	}
	//Run-left
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 241, 0, 261, 24), 0.1f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 265, 0, 286, 24), 0.1f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 290, 0, 309, 24), 0.1f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 314, 0, 334, 24), 0.1f); //4
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 338, 0, 357, 24), 0.1f); //5
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 362, 0, 382, 24), 0.1f); //6
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 386, 0, 405, 24), 0.1f); //7
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 409, 0, 430, 24), 0.1f); //8
		player->AddClip(clip);
	}

	//Sword-top
	//y: 40
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 189, 29, 211), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 34, 185, 62, 222), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 73, 176, 93, 222), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 100, 185, 126, 219), 0.08f); //4
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 126, 176, 167, 217), 0.08f); //5
		player->AddClip(clip);
	}
	//Sword-bottom
	//y: 46
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 106, 20, 129), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 26, 102, 53, 130), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 60, 90, 80, 136), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 90, 90, 110, 136), 0.08f); //4
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 116, 96, 149, 134), 0.08f); //5
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 156, 99, 197, 133), 0.08f); //6
		player->AddClip(clip);
	}
	//Sword-left
	//x: 40
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 199, 92, 217, 116), 0.08f); //1
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 244, 92, 278, 118), 0.08f); //2
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 288, 93, 337, 114), 0.08f); //3
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 341, 93, 377, 114), 0.08f); //4
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 391, 90, 419, 112), 0.08f); //5
		player->AddClip(clip);
	}

	//Lift Idle-top
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 13, 474, 29, 508), 0.1f);
		player->AddClip(clip);
	}
	//Lift Idle-bottom
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 11, 382, 27, 418), 0.1f);
		player->AddClip(clip);
	}
	//Lift Idle-left
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 13, 432, 29, 470), 0.1f);
		player->AddClip(clip);
	}

	//Lift Walk-top
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 13, 474, 29, 508), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 474, 49, 508), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 54, 474, 70, 508), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 74, 474, 90, 508), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 95, 474, 111, 508), 0.1f);
		player->AddClip(clip);
	}
	//Lift Walk-bottom
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 11, 382, 27, 418), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 382, 49, 418), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 11, 382, 27, 418), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 53, 382, 69, 418), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 72, 383, 88, 419), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 11, 382, 27, 418), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 92, 383, 108, 419), 0.1f);
		player->AddClip(clip);
	}
	//Lift Walk-left
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 13, 432, 29, 470), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 38, 433, 54, 471), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 434, 80, 472), 0.1f);
		player->AddClip(clip);
	}

	//Throw-top
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 132, 487, 148, 521), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 156, 483, 172, 525), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 179, 480, 195, 530), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 204, 476, 220, 532), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 224, 473, 246, 535), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 251, 481, 275, 527), 0.06f);
		player->AddClip(clip);
	}
	//Throw-bottom
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 124, 370, 140, 406), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 149, 370, 165, 406), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 174, 370, 190, 406), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 197, 370, 213, 406), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 216, 364, 238, 410), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 244, 364, 268, 410), 0.06f);
		player->AddClip(clip);
	}
	//Throw-Left
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 13, 432, 29, 470), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 137, 431, 167, 469), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 172, 434, 208, 466), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 211, 437, 261, 465), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 265, 436, 327, 464), 0.06f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 331, 437, 395, 463), 0.06f);
		player->AddClip(clip);
	}

	//Pose
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 422, 55, 438, 78), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 422, 55, 438, 78), 0.1f);
		player->AddClip(clip);
	}

	player->Position(position);
	player->Scale(scale);
	player->Play(1);
	player->DrawBound(true);
	this->scale = scale;

	for (int i = 0; i < 4; i++)
	{
		bLineCollisionIndex[i] = -1; // -1이면 충돌한 선이 없는 상태
	}
	// left right bottom top
	positionVector[0].x = position.x - 12 * scale.x;
	positionVector[0].y = position.y;
	positionVector[1].x = position.x + 12 * scale.x;
	positionVector[1].y = position.y;
	positionVector[2].x = position.x;
	positionVector[2].y = position.y - 12 * scale.y;
	positionVector[3].x = position.x;
	positionVector[3].y = position.y + 12 * scale.y;
}

Player::~Player()
{
	SAFE_DELETE(player);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	bMove = false;
	D3DXVECTOR2 position = player->Position();

	// left right bottom top
	positionVector[0].x = position.x - 12 * scale.x;
	positionVector[0].y = position.y;
	positionVector[1].x = position.x + 12 * scale.x;
	positionVector[1].y = position.y;
	positionVector[2].x = position.x;
	positionVector[2].y = position.y - 12 * scale.y;
	positionVector[3].x = position.x;
	positionVector[3].y = position.y + 12 * scale.y;

	if (autoMovingTime < 0)
	{
		autoMovingTime = 0.0;
		moveSpeed = 200.0f;
		bMove = false;
	}
	else if (autoMovingTime > 0)
	{
		autoMovingTime -= Timer->Elapsed();
		bMove = true;
	}

	if (!attack && !pose /*&& !stop*/ && !throwing && !autoMovingTime) // autoMovingTime이 0일 때 입력받기
	{
		if (Key->Press('S') && bLineCollisionIndex[2] == -1) // 아래쪽으로 이동
		{
			bMove = true;

			left = false; // 현재는 false여도 A누르면 left = true
			right = false;
			bottom = true;
			top = false;
		}
		if (Key->Press('W') && bLineCollisionIndex[3] == -1) // 위쪽으로 이동
		{
			bMove = true;

			left = false; // 현재는 false여도 A누르면 left = true
			right = false;
			bottom = false;
			top = true;
		}

		if (Key->Press('A') && bLineCollisionIndex[0] == -1) // 왼쪽으로 이동
		{
			bMove = true;
			
			left = true;
			right = false;
			if (!Key->Press('S'))
				bottom = false;
			if (!Key->Press('W'))
				top = false;
		}
		if (Key->Press('D') && bLineCollisionIndex[1] == -1) // 오른쪽으로 이동
		{
			bMove = true;
			
			left = false;
			right = true;
			if (!Key->Press('S'))
				bottom = false;
			if (!Key->Press('W'))
				top = false;
		}
		
		if (Key->Down(VK_SPACE) && !lifting)
		{
			attack = true;
		}
	}

	if (pose == true)
	{
		player->Play(18);
		if (player->IsLastClip())
			pose = false;
	}
	else if (throwing == true)
	{
		if (left)
		{
			player->Play(17);
			player->RotationDegree(0, 0, 0);
		}
		else if (right)
		{
			player->Play(17);
			player->RotationDegree(0, 180, 0);
		}
		else if (bottom)
			player->Play(16);
		else if (top)
			player->Play(15);

		if (player->IsLastClip())
			throwing = false;
	}
	else if (attack == true)
	{
		if (left)
		{
			player->Play(8);
			player->RotationDegree(0, 0, 0);
		}
		else if (right)
		{
			player->Play(8);
			player->RotationDegree(0, 180, 0);
		}
		else if (bottom)
			player->Play(7);
		else if (top)
			player->Play(6);

		if (player->IsLastClip())
		{
			attack = false;
			//bMove = false;
		}
	}
	else if (bMove == true)
	{
		if (left)
		{
			if (!top && !bottom)
				position.x -= moveSpeed * Timer->Elapsed();
			else
				position.x -= moveSpeed * Timer->Elapsed() / sqrt(2);
			player->RotationDegree(0, 0, 0);
			if (!lifting)
				player->Play(5); // 그냥 걷는 모션
			else
				player->Play(14); // 항아리 들고 걷는 모션
		}
		if (right)
		{
			if (!top && !bottom)
				position.x += moveSpeed * Timer->Elapsed();
			else
				position.x += moveSpeed * Timer->Elapsed() / sqrt(2);
			player->RotationDegree(0, 180, 0);
			if (!lifting)
				player->Play(5);
			else
				player->Play(14);
		}

		if (bottom)
		{
			if (!left && !right)
				position.y -= moveSpeed * Timer->Elapsed();
			else
				position.y -= moveSpeed * Timer->Elapsed() / sqrt(2);
			if (!lifting && !left && !right)
				player->Play(4);
			else if (!left && !right)
				player->Play(13);
		}
		if (top)
		{
			if (!left && !right)
				position.y += moveSpeed * Timer->Elapsed();
			else
				position.y += moveSpeed * Timer->Elapsed() / sqrt(2);
			if (!lifting && !left && !right)
				player->Play(3);
			else if (!left && !right)
				player->Play(12);
		}
	}
	else if (bMove == false) // 가만히 서있는 모션
	{
		if (left)
		{
			if (!lifting)
				player->Play(2); // 항아리 x
			else
				player->Play(11); // 항아리 들고 서있음
			player->RotationDegree(0, 0, 0);
		}
		else if (right)
		{
			if (!lifting)
				player->Play(2);
			else
				player->Play(11);
			player->RotationDegree(0, 180, 0);
		}
		else if (bottom) // 확인하기
		{
			if (!lifting)
				player->Play(1);
			else
				player->Play(10);
		}
		else if (top)
		{
			if (!lifting)
				player->Play(0);
			else
				player->Play(9);
		}
	}

	if (!stop && stamina > 0)
	{
		player->Position(position);
		player->Update(V, P);
	}

	/// <summary>
	/// 무적 시간
	/// </summary>
	if (invincibleTime > 0)
		invincibleTime -= Timer->Elapsed();
	else
		invincibleTime = 0;
	// 무적 시간 end
}

void Player::Render()
{
	ImGui::SliderFloat("Player Move Speed", &moveSpeed, 50, 400);
	ImGui::Text("Player.X: %f", player->Position().x);
	ImGui::Text("Player.Y: %f", player->Position().y);
	if (stamina <= 0)
	{

	}
	player->Render();
}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = player->Position() - focusOffset;

	(*size) = D3DXVECTOR2(1, 1);
}

Sprite* Player::GetSprite()
{
	return player->GetSprite();
}

void Player::Scale(float x, float y)
{
	player->Scale(x, y);
}

void Player::Scale(D3DXVECTOR2 scale)
{
	player->Scale(scale);
}

string Player::Direction()
{
	if (left)
		return "left";
	else if (right)
		return "right";
	else if (bottom)
		return "bottom";
	else if (top)
		return "top";
}

void Player::Position(float x, float y)
{
	player->Position(x, y);
}

void Player::Position(D3DXVECTOR2 position)
{
	player->Position(position);
}

D3DXVECTOR2 Player::Scale()
{
	return D3DXVECTOR2(player->Scale().x * player->TextureSize().x, player->Scale().y * player->TextureSize().y);
}

void Player::Attacked()
{
	D3DXVECTOR2 position = player->Position();
	float time = 0;
	while (time <= 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (bLineCollisionIndex[i] != -1)
			{
				player->Position(intersection[i] + player->Position() - positionVector[i]);
				stamina--;
				invincibleTime = 1;
				return;
			}
		}
		if (bottom)
			player->Position(player->Position().x, player->Position().y + moveSpeed * Timer->Elapsed() / 2);
		else if (top)
			player->Position(player->Position().x, player->Position().y - moveSpeed * Timer->Elapsed() / 2);
		else if (left)
			player->Position(player->Position().x + moveSpeed * Timer->Elapsed() / 2, player->Position().y);
		else if (right)
			player->Position(player->Position().x - moveSpeed * Timer->Elapsed() / 2, player->Position().y);
		time += Timer->Elapsed();
	}

	stamina--;
	invincibleTime = 1;
}

void Player::Lift(bool b)
{
	lifting = b;
}

void Player::Throw(bool b)
{
	throwing = b;
	if (throwing)
		lifting = false;
}

void Player::Pose(bool b)
{
	pose = b;
}

void Player::Stop(bool b)
{
	if (b == true)
	{
		stop = true;
		player->Stop();
	}
	else
		stop = false;
}

void Player::SetItem(string itemType, int n)
{
	if (itemType == "magic")
	{
		if (magic >= 10)
			return;
		magic += n;
	}
	else if (itemType == "rupee")
		rupee += n;
	else if (itemType == "bomb")
		bomb += n;
	else if (itemType == "arrow")
		arrow += n;
	else if (itemType == "key")
		key += n;
	else if (itemType == "stamina")
	{
		if (stamina < 0 || stamina > 10)
			return;
		stamina += n;
	}
	else if (itemType == "boss key")
		bossKey += n;
	else if (itemType == "map")
		map += n;
	else if (itemType == "compass")
		compass += n;
	else if (itemType == "bow")
		bow += n;
}

int Player::GetItem(string itemType)
{
	if (itemType == "magic")
		return magic;
	else if (itemType == "rupee")
		return rupee;
	else if (itemType == "bomb")
		return bomb;
	else if (itemType == "arrow")
		return arrow;
	else if (itemType == "key")
		return key;
	else if (itemType == "stamina")
		return stamina;
	else if (itemType == "boss key")
		return bossKey;
	else if (itemType == "map")
		return map;
	else if (itemType == "compass")
		return compass;
	else if (itemType == "bow")
		return bow;
}

void Player::LineCollision(bool b, int lineIndex, D3DXVECTOR2 intersection, string direction)
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
	this->intersection[i] = intersection;
}

void Player::AutoMoving(string direction, float speed, float time)
{
	D3DXVECTOR2 position = player->Position();
	float currentTime = 0;
	if (direction == "left")
	{
		left = true;
		right = false;
		/*bottom = false;
		top = false;*/
	}
	else if (direction == "right")
	{
		left = false;
		right = true;
	}
	else if (direction == "bottom")
	{
		left = false;
		right = false;
		bottom = true;
		top = false;
	}
	else if (direction == "top")
	{
		left = false;
		right = false;
		bottom = false;
		top = true;
	}
	autoMovingTime = time;
	moveSpeed *= speed;
}

bool Player::IsAutoMoving()
{
	if (autoMovingTime > 0)
		return true;
	return false;
}
