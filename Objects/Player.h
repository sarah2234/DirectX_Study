#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size);
	Sprite* GetSprite();

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 scale);

	string Direction();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 position);

	D3DXVECTOR2 Position() { return player->Position(); }
	D3DXVECTOR2 Scale();

	void Jump();

	bool Attacking() { return bAttack; }
	void Attacked();

	void Lift(bool b);
	bool GetBLifting() { return bLifting; }
	void Throw(bool b);
	bool GetBThrowing() { return bThrowing; }
	void Pose(bool b);

	bool IsLastClip() { return player->IsLastClip(); }
	void Stop(bool b);

	void SetItem(string itemType, int n);

	int GetItem(string itemType);

	D3DXVECTOR2 LeftPosition() { return positionVector[0]; }
	D3DXVECTOR2 RightPosition() { return positionVector[1]; }
	D3DXVECTOR2 BottomPosition() { return positionVector[2]; }
	D3DXVECTOR2 TopPosition() { return positionVector[3]; }
	void LineCollision(bool b, int lineIndex, string direction);
	int GetLeftBLineCollisionIndex() { return bLineCollisionIndex[0]; }
	int GetRightBLineCollisionIndex() { return bLineCollisionIndex[1]; }
	int GetBottomBLineCollisionIndex() { return bLineCollisionIndex[2]; }
	int GetTopBLineCollisionIndex() { return bLineCollisionIndex[3]; }

	void ObjectCollision(bool b, int objectIndex, string direction);
	int GetLeftBObjectCollisionIndex() { return bObjectCollisionIndex[0]; }
	int GetRightBObjectCollisionIndex() { return bObjectCollisionIndex[1]; }
	int GetBottomBObjectCollisionIndex() { return bObjectCollisionIndex[2]; }
	int GetTopBObjectCollisionIndex() { return bObjectCollisionIndex[3]; }

	void AutoMoving(string direction, float speed, float time); // �÷��̾� �ڵ� ������(�� �̵��� �� ��)
	bool GetBAutoMoving();

	float GetBInvincibleTime() { return invincibleTime; }

	void SetBBase(bool b);
	bool GetBBase() { return bBase; }

	int GetDirection();
	bool GetBMove() { return bMove; }

private:
	Animation* player;
	D3DXVECTOR2 scale; // player ������ �� ũ�� �Է¹��� �� ����
	D3DXVECTOR2 positionVector[4]; // left, right, bottom, top
	D3DXVECTOR2 autoMovingPlace; // �ڵ����� �ش� ��ġ���� ������
	int bLineCollisionIndex[4];
	int bObjectCollisionIndex[4];

	float autoMovingTime;
	bool bMove;
	bool bJump;
	float moveSpeed;
	bool bAttack;
	bool bAttacked;
	bool bLifting;
	bool bThrowing;
	bool bPose;
	bool bStop;
	bool bLeft;
	bool bRight;
	bool bBottom; // �� �ո��� ���̴� ��
	bool bTop;

	int magic;
	int rupee;
	int bomb;
	int arrow;
	int key;
	int stamina;

	int bossKey;
	int map;
	int compass;
	int bow;

	float invincibleTime;

	bool bBase;

	D3DXVECTOR2 focusOffset;
};