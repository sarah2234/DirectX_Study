#pragma once
#include "Scene.h"
#include "Objects/Enemy.h"
#include "Objects/Chest.h"
#include "Objects/Vase.h"

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

	void CreateEnemy(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool onScene);
	void CreateVase(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary);
	void CreateChest(string size, string item, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary);
	void CreateButton(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary);
	void CreateDoor(D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool open, bool upsideDown);

	void CreateRoomLine(int x1, int y1, int x2, int y2, int room);
	void CreateHallLine(int x1, int y1, int x2, int y2, int room, bool open);
	template <typename T>
	void RoomLineCollision(RoomLine line, int lineIndex, T object);
	void HallLineCollision(HallLine line, int lineIndex);

private:
	Sprite* eastern_palace;
	Sprite* hall;
	Sprite* first_floor;
	Sprite* base_floor;
	vector<RoomLine>roomLines[21];
	vector<HallLine>hallLines[21];
	bool on;

	vector<Enemy*> enemies[21];
	vector<Enemy*> armo_knights;
	float enemyMoveSpeed;

	vector<Animation*>doors[21];
	vector<Sprite*> buttons[21]; // ÃÑ 21°³ÀÇ ¹æ
	vector<Vase*> vases[21];
	vector<Chest*> chests[21];

	float time;
	int currentRoom;
};


