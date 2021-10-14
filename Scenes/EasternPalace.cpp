#include "stdafx.h"
#include "EasternPalace.h"
#include "Viewer/Following.h"
#include <math.h>

EasternPalace::EasternPalace(SceneValues* values, D3DXVECTOR2 position)
	:Scene(values, position), on(false), enemyMoveSpeed(200), time(0), currentRoom(0)
{
	//wstring spriteFile = Textures + L"Legend of Zelda/Eastern Palace Parts.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	Clip* clip;

	// rooms
	eastern_palace = new Sprite(Textures + L"Legend of Zelda/Eastern Palace.png", shaderFile);
	eastern_palace->Scale(2.5, 2.5);
	eastern_palace->Position(position);

	hall = new Sprite(Textures + L"Legend of Zelda/Eastern Palace Hall.png", shaderFile);
	hall->Scale(2.5, 2.5);
	hall->Position(position);

	first_floor = new Sprite(Textures + L"Legend of Zelda/Eastern Palace First Floor.png", shaderFile);
	first_floor->Scale(2.5, 2.5);
	first_floor->Position(position);

	base_floor = new Sprite(Textures + L"Legend of Zelda/Eastern Palace Base Floor.png", shaderFile);
	base_floor->Scale(2.5, 2.5);
	base_floor->Position(position);

	/// <summary>
	/// Enemies
	/// </summary>
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(584, 2182), 2, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(712, 2182), 2, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1672, 1990), 5, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1672, 1926), 5, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1608, 1894), 5, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(368, 1729), 6, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(320, 1681), 6, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(416, 1681), 6, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(368, 1635), 6, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(616, 1606), 8, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(680, 1606), 8, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(616, 1542), 8, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(680, 1542), 8, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(936, 1574), 9, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1096, 1574), 9, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1384, 1494), 10, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1480, 1510), 10, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1480, 1622), 10, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 694), 15, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 614), 15, true);

	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1031, 2453), 1, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1015, 2437), 1, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1031, 2421), 1, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(599, 2005), 2, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(695, 2005), 2, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1416, 2025), 4, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1480, 1976), 4, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1448, 1640), 10, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1448, 1432), 10, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(984, 1192), 13, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1000, 1208), 13, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1016, 1208), 13, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1032, 1208), 13, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1048, 1208), 13, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1064, 1192), 13, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(104, 440), 19, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(104, 424), 19, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(152, 440), 19, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(152, 424), 19, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(120, 408), 19, true);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 408), 19, true);

	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 2139), 2, true);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(920, 1403), 9, true);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1128, 1403), 9, true);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1000, 1179), 13, true);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1048, 1179), 13, true);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 699), 17, true);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 651), 17, true);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 603), 17, true);

	CreateEnemy("red eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(120, 587), 15, true);
	CreateEnemy("red eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(120, 347), 19, true);
	CreateEnemy("red eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 347), 19, true);

	//중심: (128, 125)
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(80, 149), 20, true);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(128, 149), 20, true);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(176, 149), 20, true);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(80, 101), 20, true);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(128, 101), 20, true);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(176, 101), 20, true);

	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1336, 1975), 4, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1336, 1927), 4, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1672, 1415), 12, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(638, 2039), 2, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 2049), 2, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(658, 2039), 2, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 2029), 2, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1112, 903), 14, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1192, 935), 14, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(888, 647), 18, true);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(904, 647), 18, true);

	CreateEnemy("big ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1056, 1912), 3, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1055, 2125), 3, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1040, 2039), 3, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(301, 583), 16, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(346, 583), 16, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(393, 615), 16, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(359, 652), 16, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(359, 690), 16, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(407, 569), 16, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(439, 593), 16, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(439, 713), 16, true); // 80
	// end of enemies

	/// <summary>
	/// Create Button
	/// </summary>
	CreateButton("yellow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1015.5, 2694.5), 0, true);
	CreateButton("purple", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1015.5, 2487.5), 1, true);
	CreateButton("yellow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(647.5, 2038.5), 2, true);
	CreateButton("yellow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1663.5, 1446.5), 12, true);
	CreateButton("yellow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(871.5, 662.5), 18, true);
	// end of buttons

	/// <summary>
	/// Create Vase
	/// </summary>
	CreateVase("green rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(895.5, 2694.5), 0, true);
	CreateVase("green rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1151.5, 2694.5), 0, true);
	CreateVase("green rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1144.5, 2118.5), 3, true);
	CreateVase("green rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1207.5, 2118.5), 3, true);
	CreateVase("green rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1663.5, 2022.5), 5, true);
	CreateVase("green rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1663.5, 1894.5), 5, true);
	CreateVase("green rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(383.5, 1702.5), 6, true);

	CreateVase("blue rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1159.5, 2118.5), 3, true);
	CreateVase("blue rupee", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1191.5, 2118.5), 3, true);

	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(615.5, 2086.5), 2, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(679.5, 2086.5), 2, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1591.5, 1990.5), 5, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1591.5, 1926.5), 5, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(303.5, 1630.5), 6, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(839.5, 1638.5), 9, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1207.5, 1638.5), 9, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1207.5, 1518.5), 9, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1720.5, 1815.5), 11, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1720.5, 1799.5), 11, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1720.5, 1783.5), 11, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1623.5, 1406.5), 12, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1111.5, 1126.5), 13, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(119.5, 646.5), 15, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(631.5, 710.5), 17, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(919.5, 662.5), 18, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(47.5, 398.5), 19, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(207.5, 462.5), 19, true);

	CreateVase("small magic powder", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1735.5, 1990.5), 5, true);
	CreateVase("small magic powder", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(935.5, 1126.5), 13, true);

	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(839.5, 1502.5), 9, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(839.5, 1518.5), 9, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1207.5, 1502.5), 9, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(135.5, 646.5), 15, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(631.5, 582.5), 17, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(871.5, 630.5), 18, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(919.5, 630.5), 18, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(47.5, 462.5), 19, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(47.5, 430.5), 19, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(207.5, 430.5), 19, true);
	CreateVase("5 arrows", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(47.5, 398.5), 19, true);
	
	CreateVase("small key", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1735.5, 1926.5), 5, true);
	// end of vases

	/// <summary>
	/// Create Chest
	/// </summary>
	CreateChest("small", "boss key", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(647.5, 1960.5), 2, true);
	CreateChest("small", "100 rupees", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1175.5, 2120.5), 3, true);
	CreateChest("small", "compass", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(367.5, 1392.5), 7, true);
	CreateChest("big", "bow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 1532.5), 9, true);
	CreateChest("small", "map", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1719.5, 1687.5), 11, true);
	// end of chests

	/// <summary>
	/// Doors
	/// </summary>
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(895.5, 2630.5), 0, true, false); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2630.5), 0, false, false); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1151.5, 2630.5), 0, true, false); // 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(895.5, 2568.5), 1, true, true); // 3
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2568.5), 1, false, true); // 4
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1151.5, 2568.5), 1, true, true); // 5
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2374.5), 1, false, false); // 6
	// end of doors

	/// <summary>
	/// Lines
	/// </summary>
	// room 0
	CreateRoomLine(1014, 2824, 1033, 2824, 0); // 0-0
	CreateRoomLine(1014, 2824, 1014, 2806, 0); // 0-1
	CreateRoomLine(1033, 2824, 1033, 2806, 0); // 0-2
	CreateRoomLine(1014, 2806, 945, 2806, 0); // 0-3
	CreateRoomLine(1033, 2806, 1102, 2806, 0); //0-4
	CreateRoomLine(945, 2806, 945, 2774, 0); //1
	CreateRoomLine(945, 2774, 874, 2774, 0); //2
	CreateRoomLine(874, 2774, 874, 2649, 0); //3
	CreateRoomLine(874, 2649, 895, 2649, 0); //4
	CreateRoomLine(895, 2649, 918, 2649, 0); //5
	CreateRoomLine(918, 2649, 918, 2713, 0); //6
	CreateRoomLine(918, 2713, 1001, 2713, 0); //7
	CreateRoomLine(1001, 2713, 1001, 2649, 0); //8
	CreateRoomLine(1001, 2649, 1034, 2649, 0); //9
	CreateRoomLine(1034, 2649, 1046, 2649, 0); //10
	CreateRoomLine(1046, 2649, 1046, 2713, 0); //11
	CreateRoomLine(1046, 2713, 1129, 2713, 0); //12
	CreateRoomLine(1129, 2713, 1129 , 2649, 0); //13
	CreateRoomLine(1129, 2649, 1162 , 2649, 0); //14
	CreateRoomLine(1162, 2649, 1174, 2649, 0); //15
	CreateRoomLine(1174, 2649, 1174, 2774, 0); //16
	CreateRoomLine(1174, 2774, 1102, 2774, 0); //17
	CreateRoomLine(1102, 2774, 1102, 2806, 0); //18
	CreateRoomLine(1102, 2806, 1102, 2806, 0); //19
	
	CreateHallLine(886, 2649, 905, 2649, 0, true); // 0
	CreateHallLine(1014, 2649, 1033, 2649, 0, false); // 1
	CreateHallLine(1142, 2649, 1161, 2649, 0, true); // 2

	// room 1
	CreateRoomLine(880, 2551, 911, 2551, 1); // 20
	CreateRoomLine(880, 2551, 880, 2511, 1); // 21
	CreateRoomLine(911, 2551, 911, 2511, 1); // 22
	CreateRoomLine(880, 2511, 911, 2511, 1); // 23

	CreateRoomLine(992, 2551, 1055, 2551, 1); // 24
	CreateRoomLine(992, 2551, 992, 2393, 1); // 25
	CreateRoomLine(1055, 2551, 1055, 2393, 1); // 26
	CreateRoomLine(992, 2393, 1055, 2393, 1); // 27

	CreateRoomLine(1136, 2551, 1167, 2551, 1); // 28
	CreateRoomLine(1136, 2551, 1136, 2511, 1); // 29
	CreateRoomLine(1167, 2551, 1167, 2511, 1); // 30
	CreateRoomLine(1136, 2511, 1167, 2511, 1); // 31

	CreateHallLine(886, 2551, 905, 2551, 1, true); // 3
	CreateHallLine(1014, 2551, 1033, 2551, 1, true); // 4
	CreateHallLine(1142, 2551, 1161, 2551, 1, true); // 5
	CreateHallLine(1014, 2393, 1033, 2393, 1, false); // 6

	// room 2
	CreateRoomLine(569, 2294, 726, 2294, 2); // 32
	CreateRoomLine(569, 2294, 569, 1881, 2); // 33
	CreateRoomLine(726, 2294, 726, 1881, 2); // 34
	CreateRoomLine(569, 1881, 726, 1881, 2); // 35

	CreateRoomLine(616, 2007, 623, 2007, 2); // 36
	CreateRoomLine(672, 2007, 679, 2007, 2); // 37
	CreateRoomLine(616, 2007, 616, 1999, 2); // 38
	CreateRoomLine(679, 2007, 679, 1999, 2); // 39
	CreateRoomLine(616, 1999, 592, 1999, 2); // 40
	CreateRoomLine(679, 1999, 703, 1999, 2); // 41
	CreateRoomLine(592, 1999, 592, 1920, 2); // 42
	CreateRoomLine(703, 1999, 703, 1920, 2); // 43
	CreateRoomLine(592, 1920, 703, 1920, 2); // 44
	CreateRoomLine(623, 2007, 623, 1983, 2); // 45
	CreateRoomLine(672, 2007, 672, 1983, 2); // 46
	CreateRoomLine(623, 1983, 608, 1983, 2); // 47
	CreateRoomLine(672, 1983, 687, 1983, 2); // 48
	CreateRoomLine(608, 1983, 608, 1936, 2); // 49
	CreateRoomLine(687, 1983, 687, 1936, 2); // 50
	CreateRoomLine(608, 1936, 687, 1936, 2); // 51
	CreateRoomLine(608, 2255, 623, 2255, 2); // 52
	CreateRoomLine(608, 2255, 608, 2208, 2); // 53
	CreateRoomLine(623, 2255, 623, 2208, 2); // 54
	CreateRoomLine(608, 2208, 623, 2208, 2); // 55

	CreateHallLine(727, 1950, 727, 1969, 2, true); // 7
	CreateHallLine(630, 1879, 649, 1879, 2, true); // 8
}

EasternPalace::~EasternPalace()
{
	SAFE_DELETE(eastern_palace);
	SAFE_DELETE(hall);
	SAFE_DELETE(first_floor);
	SAFE_DELETE(base_floor);

	for (int i = 0; i < enemies->size(); i++)
		enemies[i].clear();
	for (int i = 0; i < doors->size(); i++)
		doors[i].clear();
	for (int i = 0; i < buttons->size(); i++)
		buttons[i].clear();
	for (int i = 0; i < vases->size(); i++)
		vases[i].clear();
	for (int i = 0; i < chests->size(); i++)
		chests[i].clear();

	for (int i = 0; i < roomLines->size(); i++)
		roomLines[i].clear();
	for (int i = 0; i < hallLines->size(); i++)
		hallLines[i].clear();
}

void EasternPalace::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	eastern_palace->Update(V, P);
	hall->Update(V, P);
	first_floor->Update(V, P);
	base_floor->Update(V, P);

	/// <summary>
	/// 플레이어, 적 이동 반경
	/// </summary>
	for (int i = 0; i < roomLines[currentRoom].size(); i++)
	{
		roomLines[currentRoom][i].line->Update(V, P);
		// 선 충돌 처리
		RoomLineCollision(roomLines[currentRoom][i], i, player);
		for (Enemy* enemy : enemies[currentRoom])
			RoomLineCollision(roomLines[currentRoom][i], i, enemy);
	} 
	// roomLines 아래에 hallLines 둬서 플레이어의 선 충돌 상태 업데이트
	for (int i = 0; i < hallLines[currentRoom].size(); i++)
	{
		hallLines[currentRoom][i].line->Update(V, P);
		if (!player->IsAutoMoving()) // 플레이어가 자동으로 움직이고 있으면 선 충돌 검사 안 하기
			HallLineCollision(hallLines[currentRoom][i], i);
	}
	// 이동 반경 설정 end	

	/// <summary>
	/// 문(hall) 열리는 시기 결정
	/// </summary>
	if (Sprite::Obb(player->GetSprite(), buttons[0][0]))
	{
		hallLines[0][1].open = true;
		doors[0][1]->Play(1); // 문 열림
		doors[1][1]->Play(1);
	}
	if (currentRoom == 1)
	{
		for (int i = 0, cnt = 0; i < enemies[1].size(); i++)
		{
			if (enemies[1][i]->IsDead())
				cnt++;
			if (cnt == enemies[1].size())
				doors[1][1]->Play(1);
			else if(i == enemies[1].size() - 1)
				doors[1][1]->Play(0); // 해당 방 몬스터 다 못 죽였으면 문 안 열림 
		}
	}
	if (!player->Attacking() && Sprite::Obb(player->GetSprite(), buttons[1][0]))
	{
		hallLines[1][3].open = true;
		doors[1][3]->Play(1); // 문 열림
	}
	// 문 열리는 시기 결정 end
	
	/// <summary>
	/// 공 움직임
	/// </summary>
	for (Enemy* ball : enemies[3])
	{
		ball->Direction(2);

		if (ball->Position().y <= (2814 - 2263) * 2.5 + Height / 2)
		{
			ball->Position(ball->Position().x, (2814 - 1912) * 2.5 + Height / 2);
		}
	}
	for (Enemy* ball : enemies[16])
	{
		if (ball->Direction() == 1 && ball->Position().x >= (495 - 1023) * 2.5 + Width / 2)
			ball->Position((301 - 1023) * 2.5 + Width / 2, ball->Position().y);
		else if (ball->Direction() == 2 && ball->Position().y <= (2811 - 760) * 2.5 + Width / 2)
			ball->Position(ball->Position().x, (2811 - 544) * 2.5 + Width / 2);
		else if (ball->Direction() == 3 && ball->Position().y >= (2811 - 544) * 2.5 + Width / 2)
			ball->Position(ball->Position().x, (2811 - 760) * 2.5 + Width / 2);
	}
	// 공 움직임 end

	/// <summary>
	/// 원형으로 움직이는 몬스터 업데이트(해당 코드 위치 바꿔서 업데이트 시기를 플레이어가 방에 입장하면 하는 걸로)
	/// </summary>
	if (abs(player->Position().x - armo_knights[0]->Position().x) <= 200 && abs(player->Position().y - armo_knights[0]->Position().y) <= 200)
	{
		time = 0;

		if (Key->Press('S') && abs(player->Position().x - armo_knights[0]->Position().x) >= 100 && abs(player->Position().y - armo_knights[0]->Position().y) >= 100)
		{
			for (Enemy* enemy : armo_knights)
				enemy->Play(1);

			time += Timer->Elapsed();
			if (time <= 6)
			{
				armo_knights[0]->Position((128 - 1023) * 2.5 + Width / 2 - sin(time + 2.35619) * 30 * 2.5,
					(2811 - 125) * 2.5 + Height / 2 + cos(time + 2.35619) * 30 * 2.5); //이거 각도 조정 (현재 45도)
				armo_knights[1]->Position((128 - 1023) * 2.5 + Width / 2 - sin(time + 3.14159) * 30 * 2.5,
					(2811 - 125) * 2.5 + Height / 2 + cos(time + 3.14159) * 30 * 2.5);
				armo_knights[2]->Position((128 - 1023) * 2.5 + Width / 2 - sin(time + 3.92699) * 30 * 2.5,
					(2811 - 125) * 2.5 + Height / 2 + cos(time + 3.92699) * 30 * 2.5);
				armo_knights[3]->Position((128 - 1023) * 2.5 + Width / 2 - sin(time + 4.71239) * 30 * 2.5,
					(2811 - 125) * 2.5 + Height / 2 + cos(time + 4.71239) * 30 * 2.5);
				armo_knights[4]->Position((128 - 1023) * 2.5 + Width / 2 - sin(time) * 30 * 2.5,
					(2811 - 125) * 2.5 + Height / 2 + cos(time) * 30 * 2.5);
				armo_knights[5]->Position((128 - 1023) * 2.5 + Width / 2 - sin(time + 0.785398) * 30 * 2.5,
					(2811 - 125) * 2.5 + Height / 2 + cos(time + 0.785398) * 30 * 2.5);
			}
		}
	}
	// armo kights moves end

	/// <summary>
	/// 방마다 다른 오브젝트 Update
	/// </summary>
	// room 0
	if (hallLines[0][1].line->FirstVertexPos().y > player->BottomPosition().y)
	{
		currentRoom = 0;
	}

	// room 1
	if (hallLines[1][0].line->FirstVertexPos().y < player->TopPosition().y
		&& player->BottomPosition().y < hallLines[1][3].line->FirstVertexPos().y)
	{
		currentRoom = 1;
	}

	// room 2
	if (hallLines[2][0].line->FirstVertexPos().x > player->LeftPosition().x
		&& player->BottomPosition().y < hallLines[2][1].line->FirstVertexPos().y)
	{
		currentRoom = 2;
	}

	for (Vase* vase : vases[currentRoom])
		vase->Update(V, P); // vase.cpp 내 선 충돌 처리해서 항아리 있는 위치에 플레이어가 안 겹치도록 하기
	for (Chest* chest : chests[currentRoom])
		chest->Update(V, P); // 선 충돌 처리해서 상자 있는 위치에 플레이어가 안 겹치도록 하기(는 시간이 없어서 안 될 듯)
	for (Animation* door : doors[currentRoom])
		door->Update(V, P);
	for (Sprite* button : buttons[currentRoom])
		button->Update(V, P);
	for (Enemy* enemy : enemies[currentRoom])
		enemy->Update(V, P);

	// 이전 방
	for (Vase* vase : vases[abs((currentRoom - 1) % 21)])
		vase->Update(V, P); // vase.cpp 내 선 충돌 처리해서 항아리 있는 위치에 플레이어가 안 겹치도록 하기
	for (Chest* chest : chests[abs((currentRoom - 1) % 21)])
		chest->Update(V, P); // 선 충돌 처리해서 상자 있는 위치에 플레이어가 안 겹치도록 하기(는 시간이 없어서 안 될 듯)
	for (Animation* door : doors[abs((currentRoom - 1) % 21)])
		door->Update(V, P);
	for (Sprite* button : buttons[abs((currentRoom - 1) % 21)])
		button->Update(V, P);

	// 다음 방
	for (Vase* vase : vases[(currentRoom + 1) % 21])
		vase->Update(V, P); // vase.cpp 내 선 충돌 처리해서 항아리 있는 위치에 플레이어가 안 겹치도록 하기
	for (Chest* chest : chests[(currentRoom + 1) % 21])
		chest->Update(V, P); // 선 충돌 처리해서 상자 있는 위치에 플레이어가 안 겹치도록 하기(는 시간이 없어서 안 될 듯)
	for (Animation* door : doors[(currentRoom + 1) % 21])
		door->Update(V, P);
	for (Sprite* button : buttons[(currentRoom + 1) % 21])
		button->Update(V, P);
	// 방마다 다른 오브젝트 Update end
}

void EasternPalace::Render()
{
	eastern_palace->Render();
	base_floor->Render();

	/// <summary>
	/// 방마다 다른 오브젝트 Render
	/// </summary>
	for (Vase* vase : vases[currentRoom])
		vase->Render(); // vase.cpp 내 선 충돌 처리해서 항아리 있는 위치에 플레이어가 안 겹치도록 하기
	for (Chest* chest : chests[currentRoom])
		chest->Render(); // 선 충돌 처리해서 상자 있는 위치에 플레이어가 안 겹치도록 하기(는 시간이 없어서 안 될 듯)
	for (Animation* door : doors[currentRoom])
		door->Render();
	for (Sprite* button : buttons[currentRoom])
		button->Render();
	for (Enemy* enemy : enemies[currentRoom])
		enemy->Render();
	
	// 이전 방
	for (Vase* vase : vases[abs((currentRoom - 1) % 21)])
		vase->Render(); // vase.cpp 내 선 충돌 처리해서 항아리 있는 위치에 플레이어가 안 겹치도록 하기
	for (Chest* chest : chests[abs((currentRoom - 1) % 21)])
		chest->Render(); // 선 충돌 처리해서 상자 있는 위치에 플레이어가 안 겹치도록 하기(는 시간이 없어서 안 될 듯)
	for (Animation* door : doors[abs((currentRoom - 1) % 21)])
		door->Render();
	for (Sprite* button : buttons[abs((currentRoom - 1) % 21)])
		button->Render();

	// 다음 방
	for (Vase* vase : vases[(currentRoom + 1) % 21])
		vase->Render(); // vase.cpp 내 선 충돌 처리해서 항아리 있는 위치에 플레이어가 안 겹치도록 하기
	for (Chest* chest : chests[(currentRoom + 1) % 21])
		chest->Render(); // 선 충돌 처리해서 상자 있는 위치에 플레이어가 안 겹치도록 하기(는 시간이 없어서 안 될 듯)
	for (Animation* door : doors[(currentRoom + 1) % 21])
		door->Render();
	for (Sprite* button : buttons[(currentRoom + 1) % 21])
		button->Render();
	// 방마다 다른 오브젝트 Render end

	/// <summary>
	/// player 위치에 따라 지형 렌더링 순서 정하기
	/// </summary>
	if (true) //계단 내려가기 전
	{
		first_floor->Render();
	}
	for (int i = 0; i < buttons->size(); i++)
		for (Sprite* button : buttons[i])
			button->Render();
	player->Render();
	if (false) //계단 내려가서 밑층에 위치할 때 (임시로 false 설정)
	{
		first_floor->Render();
	}
	hall->Render();
	// 지형 렌더링 end

	ImGui::SliderFloat("Enemies Move Speed", &enemyMoveSpeed, 50, 400);
}

void EasternPalace::On(bool b)
{
	on = b;
}

void EasternPalace::SetPosition(D3DXVECTOR2 position)
{
	eastern_palace->Position(position);
	//base->Position(position);
}

void EasternPalace::CreateEnemy(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool onScene)
{
	Enemy* enemy = new Enemy(type, scale, onScene);
	enemy->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	enemies[room].push_back(enemy);
	if (type == "armo knight")
		armo_knights.push_back(enemy);
}

void EasternPalace::CreateVase(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary)
{
	Vase* vase;
	vase = new Vase(type);
	vase->Scale(scale);
	vase->DrawBound(boundary);
	vase->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	vases[room].push_back(vase);
}

void EasternPalace::CreateChest(string size, string item, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary)
{
	Chest* chest;
	chest = new Chest(size, item, scale);
	chest->Scale(scale);
	chest->DrawBound(boundary);
	chest->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	chests[room].push_back(chest);
}

void EasternPalace::CreateButton(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary)
{
	wstring spriteFile = Textures + L"Legend of Zelda/Eastern Palace Parts.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	Sprite* button;
	if (type == "yellow")
		button = new Sprite(spriteFile, shaderFile, 82, 161, 98, 177);
	else if (type == "purple")
		button = new Sprite(spriteFile, shaderFile, 342, 449, 358, 465); // x: 16, y: 16
	button->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	button->Scale(scale);
	button->DrawBound(boundary);
	buttons[room].push_back(button);
}

void EasternPalace::CreateDoor(D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool open, bool upsideDown)
{
	wstring spriteFile = Textures + L"Legend of Zelda/Eastern Palace Parts.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	Animation* door = new Animation;
	Clip* clip;
	if (open)
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 70, 2, 102, 36), 0.1); // x: 32, y: 34
		door->AddClip(clip);
	}
	else
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 2, 68, 36), 0.1); // x: 32, y: 34
		door->AddClip(clip); // closed

		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 2, 2, 34, 36), 0.1);
		door->AddClip(clip); // open
	}
	door->Scale(scale);
	door->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	door->Play(0);
	if (upsideDown)
		door->RotationDegree(180, 0, 0);
	doors[room].push_back(door);
}

void EasternPalace::CreateRoomLine(int x1, int y1, int x2, int y2, int room)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	D3DXVECTOR2* intersection = new D3DXVECTOR2(0, 0);
	roomLines[room].push_back({ line, intersection });
}

void EasternPalace::CreateHallLine(int x1, int y1, int x2, int y2, int room, bool open)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	hallLines[room].push_back({ line, D3DXVECTOR2(0, 0), open });
}

template<typename T>
void EasternPalace::RoomLineCollision(RoomLine line, int lineIndex, T object)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. 플레이어 위 선분
	if (line.line->SegmentIntersection(object->Position(), object->TopPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, *line.intersection, "top");
	}

	else if (object->GetTopBLineCollisionIndex() == lineIndex && // 서로 평행한 선분 2개 위치할 경우 인덱스가 작은 선과 충돌했는데 인덱스가 큰 선과는 충돌하지 않으므로 최종적으로 플레이어가 선 충돌하지 않았다고 판별하는 거... 방지
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->Position(), object->TopPosition())))
	{
		object->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "top");
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 플레이어 아래
	if (line.line->SegmentIntersection(object->Position(), object->BottomPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, *line.intersection, "bottom");
	}

	else if (object->GetBottomBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->Position(), object->BottomPosition())))
	{
		object->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "bottom");
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 플레이어 왼쪽
	if (line.line->SegmentIntersection(object->Position(), object->LeftPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, *line.intersection, "left");
	}

	else if (object->GetLeftBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->Position(), object->LeftPosition())))
	{
		object->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "left");
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. 플레이어 오른쪽
	if (line.line->SegmentIntersection(object->Position(), object->RightPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, *line.intersection, "right");
	}

	else if (object->GetRightBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->Position(), object->RightPosition())))
	{
		object->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "right");
	}
}

void EasternPalace::HallLineCollision(HallLine line, int lineIndex)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. 플레이어 위 선분
	if (line.line->SegmentIntersection(player->Position(), player->TopPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, line.intersection, "top");
			player->AutoMoving("top", 1, 1.6);
		}
		else
			player->LineCollision(true, lineIndex, line.intersection, "top");
	}

	else if (player->GetTopBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->Position(), player->BottomPosition())))
	{
		player->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "top");
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 플레이어 아래 선분
	if (line.line->SegmentIntersection(player->Position(), player->BottomPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, line.intersection, "bottom");
			player->AutoMoving("bottom", 1, 1.6);
		}
		else
			player->LineCollision(true, lineIndex, line.intersection, "bottom");
	}

	else if (player->GetBottomBLineCollisionIndex() == lineIndex && // 이거 필요??
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->Position(), player->BottomPosition())))
	{
		player->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "bottom");
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 플레이어 왼쪽
	if (line.line->SegmentIntersection(player->Position(), player->LeftPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, line.intersection, "left");
			player->AutoMoving("left", 1, 1.6);
		}
		else
			player->LineCollision(true, lineIndex, line.intersection, "left");
	}

	else if (player->GetLeftBLineCollisionIndex() == lineIndex && // 이거 필요??
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->Position(), player->LeftPosition())))
	{
		player->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "left");
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. 플레이어 오른쪽
	if (line.line->SegmentIntersection(player->Position(), player->RightPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, line.intersection, "right");
			player->AutoMoving("right", 1, 1.6);
		}
		else
			player->LineCollision(true, lineIndex, line.intersection, "right");
	}

	else if (player->GetRightBLineCollisionIndex() == lineIndex && // 이거 필요??
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->Position(), player->RightPosition())))
	{
		player->LineCollision(false, lineIndex, D3DXVECTOR2(0, 0), "right");
	}
}
