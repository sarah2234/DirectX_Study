#include "stdafx.h"
#include "Player.h"
#include <math.h>

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusOffset(-180,-120), bMove(false), bJump(false), autoMovingTime(0.0),
	bAttack(false), bAttacked(false), bLifting(false), bThrowing(false), bPose(false), bStop(false),
	bLeft(false), bRight(false), bBottom(false), bTop(true),
	magic(0), rupee(0), bomb(0), arrow(0), key(0), stamina(10), bossKey(0), map(0), compass(0), bow(0),
	invincibleTime(0.0), bBase(false), bStair(false)
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
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 89, 3, 106, 27), 0.3f); // x: 17, y: 24
		player->AddClip(clip);
	}
	//Idle-앞 모습
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 4, 49, 25), 0.3f); // x: 16, y: 21
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

	// Jump-top (19)
	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 14, 626, 31, 650), 0.05f); // x: 17, y: 24
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 41, 623, 58, 650), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 71, 619, 88, 649), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 102, 616, 119, 649), 0.08f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 132, 611, 149, 647), 0.1f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 102, 616, 119, 649), 0.08f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 71, 619, 88, 649), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 41, 623, 58, 650), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 14, 626, 31, 650), 0.05f);
	player->AddClip(clip);
	// Jump-bottom (20)
	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 201, 553, 217, 575), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 230, 550, 246, 576), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 257, 547, 273, 576), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 287, 543, 303, 576), 0.08f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 318, 540, 334, 575), 0.1f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 287, 543, 303, 576), 0.08f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 257, 547, 273, 576), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 230, 550, 246, 576), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 201, 553, 217, 575), 0.05f);
	player->AddClip(clip);
	// Jump-left (21)
	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 141, 552, 162, 576), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 108, 547, 129, 575), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 72, 543, 93, 575), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 39, 541, 59, 575), 0.08f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 11, 538, 31, 574), 0.1f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 39, 541, 59, 575), 0.08f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 72, 543, 93, 575), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 108, 547, 129, 575), 0.05f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 141, 552, 162, 576), 0.05f);
	player->AddClip(clip);

	player->Position(position);
	player->Scale(scale);
	player->Play(1);
	player->DrawBound(true);
	this->scale = scale;

	for (int i = 0; i < 4; i++)
	{
		bLineCollisionIndex[i] = -1; // -1이면 충돌한 선이 없는 상태
		bJumpCollisionIndex[i] = -1;
		bHallCollisionIndex[i] = -1;
		bStairCollisionIndex[i] = -1;
		bObjectCollisionIndex[i] = -1;
	}
	// left right bottom top
	positionVector[0].x = position.x - 4 * scale.x;
	positionVector[0].y = position.y;
	positionVector[1].x = position.x + 4 * scale.x;
	positionVector[1].y = position.y;
	positionVector[2].x = position.x;
	positionVector[2].y = position.y - 12 * scale.y;
	positionVector[3].x = position.x;
	positionVector[3].y = position.y + 12 * scale.y;

	for (int i = 0; i < 4; i++)
		bNearBorder[i] = false;
}

Player::~Player()
{
	SAFE_DELETE(player);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	pos = player->Position();
	bMove = false;
	D3DXVECTOR2 position = player->Position();

	// left right bottom top
	positionVector[0].x = position.x - 4 * scale.x;
	positionVector[0].y = position.y;
	positionVector[1].x = position.x + 4 * scale.x;
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
		if (bAttacked) // 공격받아서 자동으로 움직인 거면 공격 받은 쪽으로 얼굴을 보여야 함
		{
			if (bLeft)
			{
				player->Play(2);
				player->RotationDegree(0, 180, 0);
				bLeft = false;
				bRight = true;
			}
			else if (bRight)
			{
				player->Play(2);
				player->RotationDegree(0, 0, 0);
				bLeft = true;
				bRight = false;
			}
			else if (bTop)
			{
				player->Play(0);
				bTop = false;
				bBottom = true;
			}
			else if (bBottom)
			{
				player->Play(1);
				bTop = true;
				bBottom = false;
			}
			bAttacked = false;
		}
		else if (bStair == true) // 계단 오르내리기
		{
			bStair = false;
		}
	}
	else if (autoMovingTime > 0) // 자동으로 플레이어가 정해진 시간(autoMovingTime)만큼 움직임
	{
		for (int i = 0; i < 4; i++)
		{
			if (bLineCollisionIndex[i] != -1 && bAttacked) // 공격받아서 튕기는데 벽이 있을 때
			{
				autoMovingTime = -1.0f;
				break;
			}
		}
		autoMovingTime -= Timer->Elapsed();
		bMove = true;
	}

	if (!bAttack && !bPose && !bStop && !bThrowing && !bJump && !autoMovingTime) // autoMovingTime이 0일 때 입력받기
	{
		if (Key->Press('S')) // 아래쪽으로 이동
		{
			bMove = true;

			bLeft = false; // 현재는 false여도 A누르면 left = true
			bRight = false;
			bBottom = true;
			bTop = false;
		}
		if (Key->Press('W')) // 위쪽으로 이동
		{
			bMove = true;

			bLeft = false; // 현재는 false여도 A누르면 left = true
			bRight = false;
			bBottom = false;
			bTop = true;
		}

		if (Key->Press('A')) // 왼쪽으로 이동
		{
			bMove = true;
			
			bLeft = true;
			bRight = false;
			if (!Key->Press('S') || bLineCollisionIndex[2] != -1)
				bBottom = false;
			if (!Key->Press('W') || bLineCollisionIndex[3] != -1)
				bTop = false;
		}
		if (Key->Press('D')) // 오른쪽으로 이동
		{
			bMove = true;
			
			bLeft = false;
			bRight = true;
			if (!Key->Press('S') || bLineCollisionIndex[2] != -1)
				bBottom = false;
			if (!Key->Press('W') || bLineCollisionIndex[3] != -1)
				bTop = false;
		}
		
		if (Key->Down(VK_SPACE) && !bLifting)
		{
			bAttack = true;
		}
	}

	if (bPose == true)
	{
		player->Play(18);
		if (player->IsLastClip())
			bPose = false;
	}
	else if (bThrowing == true)
	{
		if (bLeft)
		{
			player->Play(17);
			player->RotationDegree(0, 0, 0);
		}
		else if (bRight)
		{
			player->Play(17);
			player->RotationDegree(0, 180, 0);
		}
		else if (bBottom)
			player->Play(16);
		else if (bTop)
			player->Play(15);

		if (player->IsLastClip())
			bThrowing = false;
	}
	else if (bAttack == true)
	{
		if (bLeft)
		{
			player->Play(8);
			player->RotationDegree(0, 0, 0);
		}
		else if (bRight)
		{
			player->Play(8);
			player->RotationDegree(0, 180, 0);
		}
		else if (bBottom)
			player->Play(7);
		else if (bTop)
			player->Play(6);

		if (player->IsLastClip())
		{
			bAttack = false;
			//bMove = false;
		}
	}
	else if (bMove == true)
	{
		if (bLeft)
		{
			if ((bLineCollisionIndex[0] == -1 && bHallCollisionIndex[0] == -1 && bObjectCollisionIndex[0] == -1) 
				|| autoMovingTime > 0)
			{
				if (!bTop && !bBottom)
					position.x -= moveSpeed * Timer->Elapsed();
				else
					position.x -= moveSpeed * Timer->Elapsed() / sqrt(2);
			}
			player->RotationDegree(0, 0, 0);
			if (bJump)
				player->Play(21); // jump
			else if (bLifting)
				player->Play(14); // 항아리 들고 걷는 모션
			else
				player->Play(5); // 그냥 걷는 모션
		}
		if (bRight)
		{
			if ((bLineCollisionIndex[1] == -1 && bHallCollisionIndex[1] == -1 && bObjectCollisionIndex[1] == -1)
				|| autoMovingTime > 0)
			{
				if (!bTop && !bBottom)
					position.x += moveSpeed * Timer->Elapsed();
				else
					position.x += moveSpeed * Timer->Elapsed() / sqrt(2);
			}
			player->RotationDegree(0, 180, 0);
			if (bJump)
				player->Play(21);
			else if (bLifting)
				player->Play(14);
			else
				player->Play(5);
		}

		if (bBottom)
		{
			if ((bLineCollisionIndex[2] == -1 && bHallCollisionIndex[2] == -1 && bObjectCollisionIndex[2] == -1)
 				|| autoMovingTime > 0)
			{
				if (!bLeft && !bRight)
					position.y -= moveSpeed * Timer->Elapsed();
				else
					position.y -= moveSpeed * Timer->Elapsed() / sqrt(2);
			}
			if (bJump)
				player->Play(20);
			else if (bLifting && !bLeft && !bRight)
				player->Play(13); // 항아리 들고 걷는 모션
			else if (!bLeft && !bRight)
				player->Play(4); // 그냥 걷는 모션
			
		}
		if (bTop)
		{
			if ((bLineCollisionIndex[3] == -1 && bHallCollisionIndex[2] == -1 && bObjectCollisionIndex[3] == -1)
				|| autoMovingTime > 0)
			{
				if (!bLeft && !bRight)
					position.y += moveSpeed * Timer->Elapsed();
				else
					position.y += moveSpeed * Timer->Elapsed() / sqrt(2);
			}
			if (bJump)
				player->Play(19);
			else if (bLifting && !bLeft && !bRight)
				player->Play(12);
			else if (!bLeft && !bRight)
				player->Play(3);
		}
	}
	else if (bMove == false) // 가만히 서있는 모션
	{
		if (bLeft)
		{
			if (!bLifting)
				player->Play(2); // 항아리 x
			else
				player->Play(11); // 항아리 들고 서있음
			player->RotationDegree(0, 0, 0);
		}
		else if (bRight)
		{
			if (!bLifting)
				player->Play(2);
			else
				player->Play(11);
			player->RotationDegree(0, 180, 0);
		}
		else if (bBottom) // 확인하기
		{
			if (!bLifting)
				player->Play(1);
			else
				player->Play(10);
		}
		else if (bTop)
		{
			if (!bLifting)
				player->Play(0);
			else
				player->Play(9);
		}
	}

	if (bJump && player->IsLastClip())
	{
		bJump = false;
		bBase = true;
	}

	if (!bStop && stamina > 0)
	{
		player->Position(position);
		player->Update(V, P);
	}

	/// <summary>
	/// 무적 시간
	/// </summary>
	if (invincibleTime > 0)
	{
		invincibleTime -= Timer->Elapsed();
		if (player->Scale().x == 2.5)
			player->Scale(0, 0);
		else if (player->Scale().x == 0)
			player->Scale(2.5, 2.5);
	}
	else
	{
		invincibleTime = 0;
		player->Scale(2.5, 2.5);
	}
	// 무적 시간 end
}

void Player::Render()
{
	if (ImGui::Button("Reset player's stamina") == true)
		stamina = 10;
	if (ImGui::Button("Reset player's position") == true)
	{
		player->Position(Width / 2, Height / 2);
		bBase = false;
		for (int i = 0; i < 4; i++)
		{
			bLineCollisionIndex[i] = -1;
			bHallCollisionIndex[i] = -1;
			bObjectCollisionIndex[i] = -1;
		}
	}

	/*ImGui::SliderFloat("Player Move Speed", &moveSpeed, 50, 400);
	ImGui::Text("Player.X: %f", player->Position().x);
	ImGui::Text("Player.Y: %f", player->Position().y);*/

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

//string Player::Direction()
//{
//	if (bLeft)
//		return "left";
//	else if (bRight)
//		return "right";
//	else if (bBottom)
//		return "bottom";
//	else if (bTop)
//		return "top";
//}

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

void Player::Jump()
{
	bJump = true;
	if (bLeft)
		AutoMoving("left", 1, 0.6);
	else if (bRight)
		AutoMoving("right", 1, 0.6);
	else if (bTop)
		AutoMoving("top", 1, 0.6);
	else if (bBottom)
		AutoMoving("bottom", 1, 0.6);
}

void Player::Attacked()
{
	D3DXVECTOR2 position = player->Position();
	bAttacked = true;

	stamina--;
	invincibleTime = 1;
	// 플레이어가 움직이는 방향의 반대 방향으로 밀쳐지기
	if (bTop == true)
		AutoMoving("bottom", 3, 0.1);
	else if (bBottom == true)
		AutoMoving("top", 3, 0.1);
	else if (bRight == true)
		AutoMoving("left", 3, 0.1);
	else if (bLeft == true)
		AutoMoving("right", 3, 0.1);
}

void Player::Lift(bool b)
{
	bLifting = b;
}

void Player::Throw(bool b)
{
	bThrowing = b;
	if (bThrowing)
		bLifting = false;
}

void Player::Pose(bool b)
{
	bPose = b;
}

void Player::Stop(bool b)
{
	if (b == true)
	{
		bStop = true;
		player->Stop();
	}
	else
		bStop = false;
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

void Player::LineCollision(bool b, int lineIndex, string direction, string type_of_line)
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
		if (type_of_line == "room")
			bLineCollisionIndex[i] = -1;
		else if (type_of_line == "hall")
			bHallCollisionIndex[i] = -1;
		else if (type_of_line == "jump")
			bJumpCollisionIndex[i] = -1;
		else if (type_of_line == "object")
			bObjectCollisionIndex[i] = -1;
		else if (type_of_line == "stair")
			bStairCollisionIndex[i] = -1;
		return;
	}

	if (type_of_line == "room")
		bLineCollisionIndex[i] = lineIndex;
	else if (type_of_line == "hall")
		bHallCollisionIndex[i] = lineIndex;
	else if (type_of_line == "jump")
		bJumpCollisionIndex[i] = lineIndex;
	else if (type_of_line == "object")
		bObjectCollisionIndex[i] = lineIndex;
	else if (type_of_line == "stair")
		bStairCollisionIndex[i] = lineIndex;
}

int Player::GetLeftBLineCollisionIndex(string type_of_line)
{
	int i = -1;
	if (type_of_line == "room")
		i = bLineCollisionIndex[0];
	else if (type_of_line == "hall")
		i = bHallCollisionIndex[0];
	else if (type_of_line == "jump")
		i = bJumpCollisionIndex[0];
	else if (type_of_line == "object")
		i = bObjectCollisionIndex[0];
	else if (type_of_line == "stair")
		i = bStairCollisionIndex[0];
	return i;
}

int Player::GetRightBLineCollisionIndex(string type_of_line)
{
	int i = -1;
	if (type_of_line == "room")
		i = bLineCollisionIndex[1];
	else if (type_of_line == "hall")
		i = bHallCollisionIndex[1];
	else if (type_of_line == "jump")
		i = bJumpCollisionIndex[1];
	else if (type_of_line == "object")
		i = bObjectCollisionIndex[1];
	else if (type_of_line == "stair")
		i = bStairCollisionIndex[1];
	return i;
}

int Player::GetBottomBLineCollisionIndex(string type_of_line)
{
	int i = -1;
	if (type_of_line == "room")
		i = bLineCollisionIndex[2];
	else if (type_of_line == "hall")
		i = bHallCollisionIndex[2];
	else if (type_of_line == "jump")
		i = bJumpCollisionIndex[2];
	else if (type_of_line == "object")
		i = bObjectCollisionIndex[2];
	else if (type_of_line == "stair")
		i = bStairCollisionIndex[2];
	return i;
}

int Player::GetTopBLineCollisionIndex(string type_of_line)
{
	int i = -1;
	if (type_of_line == "room")
		i = bLineCollisionIndex[3];
	else if (type_of_line == "hall")
		i = bHallCollisionIndex[3];
	else if (type_of_line == "jump")
		i = bJumpCollisionIndex[3];
	else if (type_of_line == "object")
		i = bObjectCollisionIndex[3];
	else if (type_of_line == "stair")
		i = bStairCollisionIndex[3];
	return i;
}


void Player::NearBorder(bool b, string direction)
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

	bNearBorder[i] = b;
}

void Player::AutoMoving(string direction, float speed, float time, bool stair)
{
	D3DXVECTOR2 position = player->Position();
	float currentTime = 0;
	if (direction == "left")
	{
		bLeft = true;
		bRight = false;
		bBottom = false;
		bTop = false;
	}
	else if (direction == "right")
	{
		bLeft = false;
		bRight = true;
		bBottom = false;
		bTop = false;
	}
	else if (direction == "bottom")
	{
		bLeft = false;
		bRight = false;
		bBottom = true;
		bTop = false;
	}
	else if (direction == "top")
	{
		bLeft = false;
		bRight = false;
		bBottom = false;
		bTop = true;
	}
	autoMovingTime = time;
	moveSpeed *= speed;

	if (stair == true)
	{
		bStair = true;
		bBase = !bBase;
	}
}

bool Player::GetBAutoMoving()
{
	if (autoMovingTime > 0)
		return true;
	return false;
}

void Player::SetBBase(bool b)
{
	bBase = b;
}

int Player::GetDirection()
{
	if (bLeft)
		return 1;
	else if (bRight)
		return 2;
	else if (bBottom)
		return 3;
	else if (bTop)
		return 4;
	else
		return 0;
}
