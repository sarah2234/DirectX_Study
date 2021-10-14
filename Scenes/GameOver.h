#pragma once
#include "Scene.h"

class GameOver : public Scene
{
public:
	GameOver(SceneValues* values, D3DXVECTOR2 position);
	~GameOver();

	void Update() override;
	void Render() override;

	void On(bool b);
	bool IsOn() { return on; }

	void SetPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 GetPosition() { return game_over->Position(); }

private:
	Sprite* game_over;
	bool on;
};