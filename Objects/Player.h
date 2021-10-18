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

	bool Attacking() { return attack; }
	void Attacked();

	void Lift(bool b);
	bool IsLifting() { return lifting; }
	void Throw(bool b);
	bool IsThrowing() { return throwing; }
	void Pose(bool b);

	bool IsLastClip() { return player->IsLastClip(); }
	void Stop(bool b);

	void SetItem(string itemType, int n);

	int GetItem(string itemType);

	D3DXVECTOR2 LeftPosition() { return positionVector[0]; }
	D3DXVECTOR2 RightPosition() { return positionVector[1]; }
	D3DXVECTOR2 BottomPosition() { return positionVector[2]; }
	D3DXVECTOR2 TopPosition() { return positionVector[3]; }
	void LineCollision(bool b, int lineIndex, D3DXVECTOR2 intersection, string direction);
	int GetLeftBLineCollisionIndex() { return bLineCollisionIndex[0]; }
	int GetRightBLineCollisionIndex() { return bLineCollisionIndex[1]; }
	int GetBottomBLineCollisionIndex() { return bLineCollisionIndex[2]; }
	int GetTopBLineCollisionIndex() { return bLineCollisionIndex[3]; }

	void AutoMoving(string direction, float speed, float time); // 플레이어 자동 움직임(방 이동할 때 등)
	bool IsAutoMoving();

	float IsInvincible() { return invincibleTime; }

private:
	Animation* player;
	D3DXVECTOR2 scale; // player 생성할 때 크기 입력받은 거 저장
	D3DXVECTOR2 positionVector[4]; // left, right, bottom, top
	D3DXVECTOR2 intersection[4];
	int bLineCollisionIndex[4];

	float autoMovingTime;
	bool bMove;
	bool bJump;
	float moveSpeed;
	bool attack;
	bool lifting;
	bool throwing;
	bool pose;
	bool stop;
	bool left;
	bool right;
	bool bottom; // 얼굴 앞면이 보이는 쪽
	bool top;

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

	D3DXVECTOR2 focusOffset;
};