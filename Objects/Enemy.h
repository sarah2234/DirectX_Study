#pragma once

class Enemy
{
public:
	Enemy(string type, D3DXVECTOR2 scale, bool onScene);
	~Enemy();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 position);
	D3DXVECTOR2 Position() { return enemy->Position(); }

	int GetStamina() { return stamina; }

	void Attacked(string direction);
	void Dead();
	bool IsDead() { return dead; }

	void OnScene(bool b);

	void MoveSpeed(float n);

	string GetType() { return type; }

	bool IsLastClip() { return enemy->IsLastClip(); }

	Sprite* GetSprite();

	void Play(int n);

	void Direction(int n);
	int Direction() { return direction; }

	D3DXVECTOR2 LeftPosition() { return positionVector[0]; }
	D3DXVECTOR2 RightPosition() { return positionVector[1]; }
	D3DXVECTOR2 BottomPosition() { return positionVector[2]; }
	D3DXVECTOR2 TopPosition() { return positionVector[3]; }
	void LineCollision(bool b, int lineIndex, D3DXVECTOR2 intersection, string direction);
	int GetLeftBLineCollisionIndex() { return bLineCollisionIndex[0]; }
	int GetRightBLineCollisionIndex() { return bLineCollisionIndex[1]; }
	int GetBottomBLineCollisionIndex() { return bLineCollisionIndex[2]; }
	int GetTopBLineCollisionIndex() { return bLineCollisionIndex[3]; }

private:
	Animation* enemy;
	Animation* slash;
	string type;
	D3DXVECTOR2 scale;
	int direction;
	float moveSpeed;
	int stamina;
	int deadNum;
	bool dead;
	bool onScene;

	// ¼± Ãæµ¹
	D3DXVECTOR2 positionVector[4]; // left, right, bottom, top
	D3DXVECTOR2 intersection[4];
	int bLineCollisionIndex[4];
};