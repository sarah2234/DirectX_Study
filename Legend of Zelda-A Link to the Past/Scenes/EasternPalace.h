#pragma once
#include "Scene.h"
#include "Objects/Enemy.h"
#include "Objects/Object.h"
#include "Objects/Chest.h"
#include "Objects/Vase.h"
#include "Objects/Door.h"

class EasternPalace : public Scene
{
public:
	EasternPalace(SceneValues* values, D3DXVECTOR2 position);
	~EasternPalace();

	void Update() override;
	void Render() override;

	void On(bool b);
	bool IsOn() { return on; }

	void SetPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 GetPosition() { return eastern_palace->Position(); }

	void CreateEnemy(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool onScene, bool bBase);
	void CreateVase(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary, bool base = false);
	void CreateChest(string size, string item, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary, bool base = false);
	void CreateButton(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary);
	void CreateDoor(D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool open, string direction);

	void CreateRoomLine(int x1, int y1, int x2, int y2, int room, bool base);
	void CreateHallLine(int x1, int y1, int x2, int y2, int room, bool open, float time = 1.6, float speed = 1);
	void CreateJumpLine(int x1, int y1, int x2, int y2, int room);
	void CreateStairLine(int x1, int y1, int x2, int y2, int room, float time = 1.4, float speed = 0.5);
	// (player�� direction�� ��ġ) none-0, left-1, right-2, bottom-3, top-4
	template <typename T>
	int RoomLineCollision(RoomLine line, int lineIndex, T object, bool jumpLine = false); // return 0 �ƴϸ� �浹 ����
	int HallLineCollision(HallLine line, int lineIndex, float speed, float time, bool stair = false); // return 0 �ƴϸ� �浹 ����
	int ObjectCollision(Object* obj, int objIndex); // return 0 �ƴϸ� �浹 ����

private:
	Sprite* eastern_palace;
	Sprite* hall;
	Sprite* first_floor;
	Sprite* base_floor;
	vector<RoomLine>roomLines[21];
	vector<HallLine>hallLines[21];
	vector<RoomLine>jumpLines[21];
	vector<HallLine>stairLines[21];
	int flag; // �濡 ���� flag (�� ������ �ñ� �� üũ)
	bool on;

	vector<Enemy*> enemies[21];
	vector<Enemy*> armo_knights;
	float enemyMoveSpeed;

	vector<Door*>doors[21];
	vector<Sprite*> buttons[21]; // �� 21���� ��
	vector<Object*> objects[21]; // vase + chests

	Sprite* blackout;
	bool bBlackout;

	float armo_knights_time;
	int currentRoom;
};


