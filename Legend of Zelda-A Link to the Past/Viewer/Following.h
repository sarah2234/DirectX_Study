#pragma once
#include "IFollowing.h"
#include "Camera.h"

class Following : public Camera
{
public:
	Following(IFollowing* focus = NULL);
	~Following();

	void Change(IFollowing* focus);
	void Update();

private:
	IFollowing* focus;
};