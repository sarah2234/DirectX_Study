#pragma once
#include "Scene.h"
#include "Objects/Enemy.h"

class Field : public Scene
{
public:
	Field(SceneValues* values, D3DXVECTOR2 position);
	~Field();

	void Update() override;
	void Render() override;

	vector<Enemy*>GetEnemies() { return enemies; }

	void On(bool b);
	bool IsOn() { return on; }

	void SetPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 GetPosition() { return field->Position(); }

private:
	Sprite* field;
	vector<Enemy*> enemies;

	float moveSpeed;

	bool on;
};
