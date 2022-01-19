#pragma once
#include "stdafx.h"
#include "Viewer/Camera.h"
#include "Objects/Enemy.h"

struct SceneValues
{
	Camera* MainCamera;
	D3DXMATRIX Projection;
};

class Scene
{
public:
	Scene(SceneValues* values, D3DXVECTOR2 position)
	{
		this->values = values;
	}
	virtual ~Scene(){}

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void On(bool b) = 0;
	virtual bool IsOn() = 0;
	virtual void SetPosition(D3DXVECTOR2 position) = 0;
	virtual D3DXVECTOR2 GetPosition() = 0;
	//virtual vector<Enemy*> GetEnemies() = 0;
	//virtual Sprite* GetBase() = 0;

protected:
	SceneValues* values;
};