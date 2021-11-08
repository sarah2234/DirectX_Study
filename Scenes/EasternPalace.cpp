#include "stdafx.h"
#include "EasternPalace.h"
#include "Viewer/Following.h"
#include <math.h>

EasternPalace::EasternPalace(SceneValues* values, D3DXVECTOR2 position)
	:Scene(values, position), on(false), enemyMoveSpeed(200), armo_knights_time(0), currentRoom(0), bBlackout(false)
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

	blackout = new Sprite(Textures + L"Legend of Zelda/Link.png", shaderFile, 22, 714, 422, 1114); // 중심: 222, 914
	blackout->Scale(2.5, 2.5);
	blackout->Position(Width / 2, Height / 2);

	/// <summary>
	/// Enemies
	/// </summary>
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(584, 2182), 2, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(712, 2182), 2, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1672, 1990), 5, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1672, 1926), 5, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1608, 1894), 5, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(368, 1729), 6, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(320, 1681), 6, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(416, 1681), 6, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(368, 1635), 6, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(616, 1606), 8, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(680, 1606), 8, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(616, 1542), 8, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(680, 1542), 8, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(936, 1574), 9, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1096, 1574), 9, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1384, 1494), 10, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1480, 1510), 10, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1480, 1622), 10, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 694), 15, true, false);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 614), 15, true, false);

	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1031, 2453), 1, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1015, 2437), 1, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1031, 2421), 1, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(599, 2005), 2, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(695, 2005), 2, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1416, 2025), 4, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1480, 1976), 4, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1448, 1640), 10, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1448, 1432), 10, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(984, 1192), 13, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1000, 1208), 13, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1016, 1208), 13, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1032, 1208), 13, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1048, 1208), 13, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1064, 1192), 13, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(104, 440), 19, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(104, 424), 19, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(152, 440), 19, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(152, 424), 19, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(120, 408), 19, true, false);
	CreateEnemy("jelly", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 408), 19, true, false);

	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 2139), 2, true, false);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(920, 1403), 9, true, false);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1128, 1403), 9, true, false);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1000, 1179), 13, true, false);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1048, 1179), 13, true, false);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 699), 17, true, false);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 651), 17, true, false);
	CreateEnemy("green eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 603), 17, true, false);

	CreateEnemy("red eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(120, 587), 15, true, false);
	CreateEnemy("red eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(120, 347), 19, true, false);
	CreateEnemy("red eye", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(136, 347), 19, true, false);

	//중심: (128, 125)
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(80, 149), 20, true, false);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(128, 149), 20, true, false);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(176, 149), 20, true, false);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(80, 101), 20, true, false);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(128, 101), 20, true, false);
	CreateEnemy("armo knight", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(176, 101), 20, true, false);

	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1336, 1975), 4, true, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1336, 1927), 4, true, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1672, 1415), 12, true, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(638, 2039), 2, false, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 2049), 2, false, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(658, 2039), 2, false, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(648, 2029), 2, false, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1112, 903), 14, true, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1192, 935), 14, true, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(888, 647), 18, true, false);
	CreateEnemy("flying object", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(904, 647), 18, true, false);

	CreateEnemy("big ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1047, 1912), 3, true, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1053, 2125), 3, true, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1040, 2039), 3, true, true);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(301, 583), 16, true, false);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(346, 583), 16, true, false);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(393, 615), 16, true, false);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(359, 652), 16, true, false);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(359, 690), 16, true, false);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(407, 569), 16, true, false);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(439, 593), 16, true, false);
	CreateEnemy("small ball", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(439, 713), 16, true, false); // 80
	// end of enemies

	/// <summary>
	/// Create Button
	/// </summary>
	// room 0
	CreateButton("yellow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1015.5, 2694.5), 0, true);
	// room 1
	CreateButton("purple", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1015.5, 2487.5), 1, true);
	// room 2
	CreateButton("yellow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(647.5, 2038.5), 2, true);
	// room 4
	CreateButton("purple", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1479.5, 1991.5), 4, true);
	// room 9
	CreateButton("purple", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(823.5, 1639.5), 9, true);
	CreateButton("purple", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(823.5, 1639.5), 9, true);
	CreateButton("purple", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1223.5, 1639.5), 9, true);
	// room 12
	CreateButton("yellow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1663.5, 1446.5), 12, true);
	// room 18
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
	// room 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(895.5, 2630.5), 0, true, "top"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2630.5), 0, false, "top"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1151.5, 2630.5), 0, true, "top"); // 2
	// room 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(895.5, 2568.5), 1, true, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2568.5), 1, false, "bottom"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1151.5, 2568.5), 1, true, "bottom"); // 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2374.5), 1, false, "top"); // 3
	// room 3
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2312.5), 3, true, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(789.5, 1960.5), 3, true, "left"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1257.5, 1960.5), 3, false, "right"); // 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 1862.5), 3, true, "top"); // 3
	// room 4
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1302.5, 1960.5), 4, false, "left"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1513.5, 1960.5), 4, false, "right"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1407.5, 1862.5), 4, true, "top"); // 2
	// room 5
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1557.5, 1960.5), 5, true, "left"); // 0
	// room 6
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(489.5, 1704.5), 6, false, "right"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(383.5, 1606.5), 6, false, "top"); // 1
	// room 7
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(383.5, 1546.5), 7, true, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(466.5, 1448.5), 7, true, "right"); // 1
	// room 8
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(639.5, 1802.5), 8, true, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(533.5, 1704.5), 8, true, "left"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(745.5, 1576.5), 8, true, "right"); // 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(556.5, 1448.5), 8, true, "left"); // 3
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(722.5, 1448.5), 8, true, "right"); // 4
	// room 9
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 1802.5), 9, true, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(789.5, 1576.5), 9, false, "left"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1257.5, 1576.5), 9, false, "right"); // 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(812.5, 1448.5), 9, true, "left"); // 3
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1234.5, 1448.5), 9, true, "right"); // 4
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 1350.5), 9, false, "top"); // 5
	// end of doors

	/// <summary>
	/// Lines
	/// </summary>
	// room 0
	CreateRoomLine(1014, 2824, 1033, 2824, 0, false); // 0-0
	CreateRoomLine(1014, 2824, 1014, 2806, 0, false); // 0-1
	CreateRoomLine(1033, 2824, 1033, 2806, 0, false); // 0-2
	CreateRoomLine(1014, 2806, 945, 2806, 0, false); // 0-3
	CreateRoomLine(1033, 2806, 1102, 2806, 0, false); //0-4
	CreateRoomLine(945, 2806, 945, 2774, 0, false); //1
	CreateRoomLine(945, 2774, 874, 2774, 0, false); //2
	CreateRoomLine(874, 2774, 874, 2649, 0, false); //3
	CreateRoomLine(874, 2649, 895, 2649, 0, false); //4
	CreateRoomLine(895, 2649, 918, 2649, 0, false); //5
	CreateRoomLine(918, 2649, 918, 2713, 0, false); //6
	CreateRoomLine(918, 2713, 1001, 2713, 0, false); //7
	CreateRoomLine(1001, 2713, 1001, 2649, 0, false); //8
	CreateRoomLine(1001, 2649, 1034, 2649, 0, false); //9
	CreateRoomLine(1034, 2649, 1046, 2649, 0, false); //10
	CreateRoomLine(1046, 2649, 1046, 2713, 0, false); //11
	CreateRoomLine(1046, 2713, 1129, 2713, 0, false); //12
	CreateRoomLine(1129, 2713, 1129, 2649, 0, false); //13
	CreateRoomLine(1129, 2649, 1162, 2649, 0, false); //14
	CreateRoomLine(1162, 2649, 1174, 2649, 0, false); //15
	CreateRoomLine(1174, 2649, 1174, 2774, 0, false); //16
	CreateRoomLine(1174, 2774, 1102, 2774, 0, false); //17
	CreateRoomLine(1102, 2774, 1102, 2806, 0, false); //18
	CreateRoomLine(1102, 2806, 1102, 2806, 0, false); //19

	CreateHallLine(886, 2649, 905, 2649, 0, true); // 0
	CreateHallLine(1014, 2649, 1033, 2649, 0, false); // 1
	CreateHallLine(1142, 2649, 1161, 2649, 0, true); // 2

	// room 1
	CreateRoomLine(880, 2551, 911, 2551, 1, false); // 20
	CreateRoomLine(880, 2551, 880, 2511, 1, false); // 21
	CreateRoomLine(911, 2551, 911, 2511, 1, false); // 22
	CreateRoomLine(880, 2511, 911, 2511, 1, false); // 23

	CreateRoomLine(992, 2551, 1055, 2551, 1, false); // 24
	CreateRoomLine(992, 2551, 992, 2393, 1, false); // 25
	CreateRoomLine(1055, 2551, 1055, 2393, 1, false); // 26
	CreateRoomLine(992, 2393, 1055, 2393, 1, false); // 27

	CreateRoomLine(1136, 2551, 1167, 2551, 1, false); // 28
	CreateRoomLine(1136, 2551, 1136, 2511, 1, false); // 29
	CreateRoomLine(1167, 2551, 1167, 2511, 1, false); // 30
	CreateRoomLine(1136, 2511, 1167, 2511, 1, false); // 31

	CreateHallLine(886, 2551, 905, 2551, 1, true); // 3
	CreateHallLine(1014, 2551, 1033, 2551, 1, true); // 4
	CreateHallLine(1142, 2551, 1161, 2551, 1, true); // 5
	CreateHallLine(1014, 2393, 1033, 2393, 1, false); // 6

	// room 2
	CreateRoomLine(569, 2294, 726, 2294, 2, false); // 32
	CreateRoomLine(569, 2294, 569, 1881, 2, false); // 33
	CreateRoomLine(726, 2294, 726, 1881, 2, false); // 34
	CreateRoomLine(569, 1881, 726, 1881, 2, false); // 35

	CreateRoomLine(616, 2007, 623, 2007, 2, false); // 36
	CreateRoomLine(672, 2007, 679, 2007, 2, false); // 37
	CreateRoomLine(616, 2007, 616, 1999, 2, false); // 38
	CreateRoomLine(679, 2007, 679, 1999, 2, false); // 39
	CreateRoomLine(616, 1999, 592, 1999, 2, false); // 40
	CreateRoomLine(679, 1999, 703, 1999, 2, false); // 41
	CreateRoomLine(592, 1999, 592, 1920, 2, false); // 42
	CreateRoomLine(703, 1999, 703, 1920, 2, false); // 43
	CreateRoomLine(592, 1920, 703, 1920, 2, false); // 44
	CreateRoomLine(623, 2007, 623, 1983, 2, false); // 45
	CreateRoomLine(672, 2007, 672, 1983, 2, false); // 46
	CreateRoomLine(623, 1983, 608, 1983, 2, false); // 47
	CreateRoomLine(672, 1983, 687, 1983, 2, false); // 48
	CreateRoomLine(608, 1983, 608, 1936, 2, false); // 49
	CreateRoomLine(687, 1983, 687, 1936, 2, false); // 50
	CreateRoomLine(608, 1936, 687, 1936, 2, false); // 51
	CreateRoomLine(608, 2255, 623, 2255, 2, false); // 52
	CreateRoomLine(608, 2255, 608, 2208, 2, false); // 53
	CreateRoomLine(623, 2255, 623, 2208, 2, false); // 54
	CreateRoomLine(608, 2208, 623, 2208, 2, false); // 55

	CreateHallLine(727, 1950, 727, 1969, 2, true); // 7
	CreateHallLine(630, 1881, 649, 1881, 2, true); // 8

	// room 3
	CreateRoomLine(929, 2294, 1166, 2294, 3, false); // 0
	CreateRoomLine(929, 2294, 929, 2255, 3, false); // 1
	CreateRoomLine(1166, 2294, 1166, 2255, 3, false); // 2	
	CreateRoomLine(929, 2255, 1166, 2255, 3, false); // 3
	CreateRoomLine(809, 2166, 1238, 2166, 3, false); // 4
	CreateRoomLine(809, 2166, 809, 2135, 3, false); // 5
	CreateRoomLine(1238, 2166, 1238, 2105, 3, false); // 6
	CreateRoomLine(809, 2135, 1111, 2135, 3, false); // 7
	CreateRoomLine(1111, 2135, 1111, 2105, 3, false); // 8
	CreateRoomLine(1111, 2105, 1238, 2105, 3, false); // 9
	CreateRoomLine(809, 2038, 1238, 2038, 3, false); // 10
	CreateRoomLine(809, 2038, 809, 1921, 3, false); // 11
	CreateRoomLine(832, 2015, 832, 1921, 3, false); // 12
	CreateRoomLine(832, 2015, 1215, 2015, 3, false); // 13
	CreateRoomLine(1215, 2015, 1215, 1921, 3, false); // 14
	CreateRoomLine(1238, 2038, 1238, 1921, 3, false); // 15
	CreateRoomLine(809, 1921, 832, 1921, 3, false); // 16
	CreateRoomLine(1215, 1921, 1238, 1921, 3, false); // 17
	CreateRoomLine(961, 1920, 1134, 1920, 3, false); // 18
	CreateRoomLine(961, 1920, 961, 1881, 3, false); // 19
	CreateRoomLine(1134, 1920, 1134, 1881, 3, false); // 20
	CreateRoomLine(961, 1881, 1134, 1881, 3, false); // 21
	// 선 충돌에서 문제 있던 선분들
	CreateRoomLine(929, 2294, 1166, 2294, 3, false); // 0
	CreateRoomLine(929, 2294, 929, 2255, 3, false); // 1
	CreateRoomLine(1166, 2294, 1166, 2255, 3, false); // 2	
	CreateRoomLine(929, 2255, 1166, 2255, 3, false); // 3
	CreateRoomLine(809, 2166, 1238, 2166, 3, false); // 4
	CreateRoomLine(809, 2166, 809, 2135, 3, false); // 5
	CreateRoomLine(1238, 2166, 1238, 2105, 3, false); // 6
	CreateRoomLine(809, 2135, 1111, 2135, 3, false); // 7
	CreateRoomLine(1111, 2135, 1111, 2105, 3, false); // 8
	CreateRoomLine(1111, 2105, 1238, 2105, 3, false); // 9

	CreateRoomLine(953, 2230, 960, 2230, 3, true); // 22
	CreateRoomLine(960, 2230, 960, 2224, 3, true); // 23
	CreateRoomLine(991, 2230, 991, 2224, 3, true); // 24
	CreateRoomLine(991, 2230, 1104, 2230, 3, true); // 25
	CreateRoomLine(1104, 2230, 1104, 2224, 3, true); // 26
	CreateRoomLine(1135, 2230, 1135, 2224, 3, true); // 27
	CreateRoomLine(1135, 2230, 1142, 2230, 3, true); // 28
	CreateRoomLine(953, 2230, 953, 2193, 3, true); // 29
	CreateRoomLine(1142, 2230, 1142, 2193, 3, true); // 30
	CreateRoomLine(953, 2193, 1017, 2193, 3, true); // 31
	CreateRoomLine(1078, 2193, 1142, 2193, 3, true); // 32
	CreateRoomLine(1017, 2193, 1017, 1982, 3, true); // 33
	CreateRoomLine(1078, 2193, 1078, 1982, 3, true); // 34
	CreateRoomLine(833, 2110, 840, 2110, 3, true); // 35
	CreateRoomLine(840, 2110, 840, 2104, 3, true); // 36
	CreateRoomLine(871, 2110, 871, 2104, 3, true); // 37
	CreateRoomLine(871, 2110, 878, 2110, 3, true); // 38
	CreateRoomLine(833, 2110, 833, 1945, 3, true); // 39
	CreateRoomLine(878, 2110, 878, 1982, 3, true); // 40
	CreateRoomLine(878, 1982, 1017, 1982, 3, true); // 41
	CreateRoomLine(1078, 1982, 1182, 1982, 3, true); // 42
	CreateRoomLine(1182, 1982, 1182, 1945, 3, true); // 43
	CreateRoomLine(833, 1945, 960, 1945, 3, true); // 44
	CreateRoomLine(960, 1951, 960, 1945, 3, true); // 45
	CreateRoomLine(991, 1951, 991, 1945, 3, true); // 46
	CreateRoomLine(1104, 1951, 1104, 1945, 3, true); // 47
	CreateRoomLine(1135, 1951, 1135, 1945, 3, true); // 48
	CreateRoomLine(1135, 1945, 1182, 1945, 3, true); // 49

	CreateRoomLine(1016, 2191, 1031, 2191, 3, true); // 50
	CreateRoomLine(1031, 2191, 1031, 2144, 3, true); // 51
	CreateRoomLine(1016, 2144, 1031, 2144, 3, true); // 52
	CreateRoomLine(1064, 2175, 1079, 2175, 3, true); // 53
	CreateRoomLine(1064, 2175, 1064, 2104, 3, true); // 54
	CreateRoomLine(1064, 2104, 1079, 2104, 3, true); // 55
	CreateRoomLine(1016, 2111, 1031, 2111, 3, true); // 56
	CreateRoomLine(1031, 2111, 1031, 2064, 3, true); // 57
	CreateRoomLine(1016, 2064, 1031, 2064, 3, true); // 58
	CreateRoomLine(1064, 2079, 1079, 2079, 3, true); // 59
	CreateRoomLine(1064, 2079, 1064, 1984, 3, true); // 60
	CreateRoomLine(1064, 1984, 1079, 1984, 3, true); // 61
	CreateRoomLine(1016, 2047, 1031, 2047, 3, true); // 62
	CreateRoomLine(1031, 2047, 1031, 1984, 3, true); // 63
	CreateRoomLine(1016, 1984, 1031, 1984, 3, true); // 64

	CreateHallLine(1014, 2294, 1033, 2294, 3, true);
	CreateHallLine(809, 1969, 809, 1951, 3, true);
	CreateHallLine(1238, 1969, 1238, 1951, 3, true);
	CreateHallLine(1014, 1881, 1033, 1881, 3, true);

	CreateStairLine(960, 2255, 991, 2255, 3);
	CreateStairLine(1104, 2255, 1135, 2255, 3);
	CreateStairLine(960, 2224, 991, 2224, 3);
	CreateStairLine(1104, 2224, 1135, 2224, 3);
	CreateStairLine(840, 2135, 871, 2134, 3);
	CreateStairLine(840, 2104, 871, 2104, 3);
	CreateStairLine(960, 1951, 991, 1951, 3);
	CreateStairLine(960, 1920, 991, 1920, 3);
	CreateStairLine(1104, 1951, 1135, 1951, 3);
	CreateStairLine(1104, 1920, 1135, 1920, 3);

	CreateJumpLine(991, 2255, 1025, 2255, 3); // 0
	CreateJumpLine(1071, 2255, 1104, 2255, 3); // 1
	CreateJumpLine(959, 2166, 991, 2166, 3); // 2
	CreateJumpLine(1104, 2166, 1136, 2166, 3); // 3
	CreateJumpLine(991, 1920, 1025, 1920, 3); // 4
	CreateJumpLine(1071, 1920, 1104, 1920, 3); // 1

	// room 4
	CreateRoomLine(1321, 2038, 1494, 2038, 4, false); // 0
	CreateRoomLine(1350, 2009, 1465, 2009, 4, false); // 1
	CreateRoomLine(1321, 2038, 1321, 1881, 4, false); // 2
	CreateRoomLine(1350, 2038, 1350, 1910, 4, false); // 3
	CreateRoomLine(1465, 2038, 1465, 1910, 4, false); // 4
	CreateRoomLine(1494, 2038, 1494, 1881, 4, false); // 5
	CreateRoomLine(1350, 1910, 1450, 1910, 4, false); // 6
	CreateRoomLine(1321, 1881, 1494, 1881, 4, false); // 7

	CreateHallLine(1321, 1970, 1321, 1949, 4, true); // 0
	CreateHallLine(1494, 1970, 1494, 1949, 4, true); // 1
	CreateHallLine(1397, 1881, 1418, 1881, 4, true); // 2

	// room 5
	CreateRoomLine(1577, 2038, 1750, 2038, 5, false); // 0
	CreateRoomLine(1577, 2038, 1577, 1881, 5, false); // 1
	CreateRoomLine(1750, 2038, 1750, 1881, 5, false); // 2
	CreateRoomLine(1577, 1881, 1750, 1881, 5, false); // 3

	CreateHallLine(1577, 1970, 1577, 1950, 5, true); // 0

	// room 6
	CreateRoomLine(297, 1782, 470, 1782, 6, false); // 0
	CreateRoomLine(297, 1782, 297, 1625, 6, false); // 1
	CreateRoomLine(470, 1782, 470, 1625, 6, false); // 2
	CreateRoomLine(297, 1625, 470, 470, 6, false); // 3

	CreateHallLine(470, 1714, 470, 1693, 6, false); // 0
	CreateHallLine(373, 1625, 394, 1625, 6, false); // 1

	// room 7
	CreateRoomLine(367, 1526, 408, 1526, 7, false); // 0
	CreateRoomLine(367, 1526, 367, 1424, 7, false); // 1
	CreateRoomLine(360, 1526, 367, 1526, 7, false); // 10
	CreateRoomLine(360, 1432, 360, 1526, 7, false); // 11
	CreateRoomLine(329, 1432, 329, 1369, 7, false); // 2
	CreateRoomLine(406, 1526, 406, 1369, 7, false); // 3
	CreateRoomLine(329, 1369, 406, 1369, 7, false); // 4

	CreateRoomLine(321, 1502, 446, 1502, 7, true); // 5
	CreateRoomLine(321, 1457, 321, 1502, 7, true); // 6
	CreateRoomLine(321, 1457, 327, 1457, 7, true); // 12
	CreateRoomLine(446, 1502, 446, 1425, 7, true); // 7
	CreateRoomLine(361, 1463, 361, 1425, 7, true); // 8
	CreateRoomLine(361, 1425, 446, 1425, 7, true); // 9

	CreateHallLine(374, 1526, 393, 1526, 7, true); // 0
	CreateHallLine(446, 1457, 446, 1438, 7, true); // 1

	// room 8
	CreateRoomLine(623, 1782, 656, 1782, 8, false); // 0
	CreateRoomLine(623, 1782, 623, 1759, 8, false); // 1
	CreateRoomLine(656, 1782, 656, 1759, 8, false); // 2
	CreateRoomLine(553, 1726, 592, 1726, 8, false); // 3
	CreateRoomLine(687, 1726, 726, 1726, 8, false); // 4
	CreateRoomLine(553, 1726, 553, 1503, 8, false); // 5
	CreateRoomLine(592, 1726, 592, 1648, 8, false); // 6
	CreateRoomLine(687, 1726, 687, 1648, 8, false); // 7
	CreateRoomLine(726, 1726, 726, 1503, 8, false); // 8
	CreateRoomLine(592, 1648, 687, 1648, 8, false); // 9
	CreateRoomLine(592, 1591, 687, 1591, 8, false); // 10
	CreateRoomLine(592, 1591, 592, 1560, 8, false); // 11
	CreateRoomLine(687, 1591, 687, 1560, 8, false); // 12
	CreateRoomLine(592, 1560, 687, 1560, 8, false); // 13
	CreateRoomLine(553, 1503, 726, 1503, 8, false); // 14

	CreateRoomLine(625, 1727, 625, 1470, 8, true); // 15
	CreateRoomLine(654, 1727, 654, 1470, 8, true); // 16
	CreateRoomLine(577, 1470, 625, 1470, 8, true); // 17
	CreateRoomLine(654, 1470, 702, 1470, 8, true); // 18
	CreateRoomLine(577, 1470, 577, 1425, 8, true); // 19
	CreateRoomLine(702, 1470, 702, 1425, 8, true); // 20
	CreateRoomLine(577, 1425, 702, 1425, 8, true); // 21

	CreateHallLine(629, 1782, 650, 1782, 8, true); // 0
	CreateHallLine(553, 1713, 553, 1694, 8, true); // 1
	CreateHallLine(726, 1585, 726, 1566, 8, true); // 2
	CreateHallLine(577, 1457, 577, 1438, 8, true); // 3
	CreateHallLine(702, 1457, 702, 1438, 8, true); // 4

	// room 9
	CreateRoomLine(1001, 1782, 1046, 1782, 9, false); // 0
	CreateRoomLine(1001, 1782, 1001, 1686, 9, false); // 1
	CreateRoomLine(1046, 1782, 1046, 1686, 9, false); // 2
	CreateRoomLine(1001, 1686, 857, 1686, 9, false); // 3
	CreateRoomLine(1046, 1686, 1190, 1686, 9, false); // 4
	CreateRoomLine(857, 1686, 857, 1654, 9, false); // 5
	CreateRoomLine(1190, 1686, 1190, 1686, 9, false); // 6
	CreateRoomLine(857, 1654, 809, 1654, 9, false); // 7
	CreateRoomLine(1190, 1654, 1238, 1654, 9, false); // 8
	CreateRoomLine(880, 1655, 1167, 1655, 9, false); // 9
	CreateRoomLine(809, 1654, 809, 1559, 9, false); // 10
	CreateRoomLine(880, 1655, 880, 1591, 9, false); // 11
	CreateRoomLine(1167, 1655, 1167, 1591, 9, false); // 12
	CreateRoomLine(1238, 1654, 1238, 1559, 9, false); // 13
	CreateRoomLine(809, 1559, 848, 1559, 9, false); // 14
	CreateRoomLine(848, 1559, 848, 1591, 9, false); // 15
	CreateRoomLine(848, 1591, 880, 1591, 9, false); // 16
	CreateRoomLine(1167, 1591, 1199, 1591, 9, false); // 17
	CreateRoomLine(1199, 1591, 1199, 1559, 9, false); // 18
	CreateRoomLine(1199, 1559, 1238, 1559, 9, false); // 19
	CreateRoomLine(913, 1622, 1134, 1622, 9, false); // 20
	CreateRoomLine(913, 1622, 913, 1526, 9, false); // 21
	CreateRoomLine(1134, 1622, 1134, 1526, 9, false); // 22
	CreateRoomLine(913, 1526, 833, 1526, 9, false); // 23
	CreateRoomLine(1134, 1526, 1214, 1526, 9, false); // 24
	CreateRoomLine(833, 1526, 833, 1424, 9, false); // 25
	CreateRoomLine(1214, 1526, 1214, 1424, 9, false); // 26
	CreateRoomLine(833, 1423, 863, 1393, 9, false); // 27
	CreateRoomLine(1214, 1423, 1184, 1393, 9, false); // 28
	CreateRoomLine(864, 1393, 950, 1393, 9, false); // 29
	CreateRoomLine(1097, 1393, 1183, 1393, 9, false); // 30
	CreateRoomLine(950, 1425, 950, 1393, 9, false); // 31
	CreateRoomLine(1097, 1425, 1097, 1393, 9, false); // 32
	CreateRoomLine(950, 1425, 976, 1425, 9, false); // 33
	CreateRoomLine(976, 1425, 976, 1455, 9, false); // 34
	CreateRoomLine(976, 1455, 1007, 1455, 9, false); // 35
	CreateRoomLine(1007, 1455, 1007, 1425, 9, false); // 36
	CreateRoomLine(1040, 1455, 1040, 1425, 9, false); // 37
	CreateRoomLine(1040, 1455, 1071, 1455, 9, false); // 38
	CreateRoomLine(1071, 1455, 1071, 1425, 9, false); // 39
	CreateRoomLine(1071, 1425, 1097, 1425, 9, false); // 40
	CreateRoomLine(983, 1400, 983, 1369, 9, false); // 41
	CreateRoomLine(1064, 1400, 1064, 1369, 9, false); // 42
	CreateRoomLine(983, 1369, 1064, 1369, 9, false); // 43

	CreateRoomLine(992, 1591, 999, 1591, 9, false); // 44
	CreateRoomLine(1048, 1591, 1055, 1591, 9, false); // 45
	CreateRoomLine(992, 1591, 992, 1583, 9, false); // 46
	CreateRoomLine(1055, 1591, 1055, 1583, 9, false); // 47
	CreateRoomLine(960, 1583, 992, 1583, 9, false); // 48
	CreateRoomLine(1055, 1583, 1087, 1583, 9, false); // 49
	CreateRoomLine(960, 1583, 960, 1488, 9, false); // 50
	CreateRoomLine(1087, 1583, 1087, 1488, 9, false); // 51
	CreateRoomLine(960, 1488, 1087, 1488, 9, false); // 52
	CreateRoomLine(999, 1591, 999, 1567, 9, false); // 53
	CreateRoomLine(1048, 1591, 1048, 1567, 9, false); // 54
	CreateRoomLine(976, 1567, 999, 1567, 9, false); // 55
	CreateRoomLine(1048, 1567, 1071, 1567, 9, false); // 56
	CreateRoomLine(976, 1567, 976, 1504, 9, false); // 57
	CreateRoomLine(1071, 1567, 1071, 1504, 9, false); // 58
	CreateRoomLine(976, 1504, 1071, 1504, 9, false); // 59

	CreateHallLine(1014, 1782, 1033, 1782, 9, true); // 0
	CreateHallLine(809, 1586, 809, 1565, 9, false); // 1
	CreateHallLine(1238, 1586, 1238, 1565, 9, false); // 2
	CreateHallLine(833, 1457, 833, 1438, 9, true); // 3	
	CreateHallLine(1214, 1457, 1214, 1438, 9, true); // 4
	CreateHallLine(1013, 1369, 1034, 1369, 9, false); // 5
}

EasternPalace::~EasternPalace()
{
	SAFE_DELETE(eastern_palace);
	SAFE_DELETE(hall);
	SAFE_DELETE(first_floor);
	SAFE_DELETE(base_floor);
	SAFE_DELETE(blackout);

	for (int i = 0; i < enemies->size(); i++)
		enemies[i].clear();
	for (int i = 0; i < doors->size(); i++)
		doors[i].clear();
	for (int i = 0; i < buttons->size(); i++)
		buttons[i].clear();
	for (int i = 0; i < objects->size(); i++)
		objects[i].clear();

	for (int i = 0; i < roomLines->size(); i++)
		roomLines[i].clear();
	for (int i = 0; i < hallLines->size(); i++)
		hallLines[i].clear();
	for (int i = 0; i < jumpLines->size(); i++)
		jumpLines[i].clear();
	for (int i = 0; i < stairLines->size(); i++)
		stairLines[i].clear();
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
		if (roomLines[currentRoom][i].base == false) // 1층에 대한 선
		{
			if (player->GetBBase() == false) // 플레이어가 1층에 있을 때
			{
				roomLines[currentRoom][i].line->Update(V, P);
				// 선 충돌 처리
				RoomLineCollision(roomLines[currentRoom][i], i, player);
			}


			for (Enemy* enemy : enemies[currentRoom])
			{
				if (enemy->GetType() != "flying object" || (enemy->GetType() == "flying object" && i < 4)) // 선이 복잡?할 때 flying object가 선들에 끼여서 움직이는 범위를 방 전체로 둠
					RoomLineCollision(roomLines[currentRoom][i], i, enemy);
			}
		}
		else if (roomLines[currentRoom][i].base == true) // 지하에 대한 선
		{
			if (player->GetBBase() == true) // 플레이어가 지하에 있을 때
			{
				roomLines[currentRoom][i].line->Update(V, P);
				// 선 충돌 처리
				RoomLineCollision(roomLines[currentRoom][i], i, player);
			}
			// 공 굴러가는 거 선 충돌
		}
	}
	// roomLines 아래에 hallLines 둬서 플레이어의 선 충돌 상태 업데이트
	for (int i = 0; i < hallLines[currentRoom].size(); i++)
	{
		hallLines[currentRoom][i].line->Update(V, P);
		if (player->GetBAutoMoving() == false) // 플레이어가 자동으로 움직이고 있으면 선 충돌 검사 안 하기
			HallLineCollision(hallLines[currentRoom][i], i, 1, 1.6);
	}
	// 계단 선 충돌
	for (int i = 0; i < stairLines[currentRoom].size(); i++)
	{
		stairLines[currentRoom][i].line->Update(V, P);
		if (!player->GetBAutoMoving()) // 플레이어가 자동으로 움직이고 있으면 선 충돌 검사 안 하기
			if (HallLineCollision(stairLines[currentRoom][i], i, 0.5, 1.4) != -1)
			{
				player->SetBBase(!player->GetBBase());
			}
	}
	// 이동 반경 설정 end	

	/// <summary>
	/// blackout 설정
	/// </summary>
	if (currentRoom == 4 || currentRoom == 5)
		bBlackout = true;
	else
		bBlackout = false;

	if (bBlackout)
	{
		if (player->Direction() == "left")
			blackout->RotationDegree(0, 0, -90);
		else if (player->Direction() == "right")
			blackout->RotationDegree(0, 0, 90);
		else if (player->Direction() == "bottom")
			blackout->RotationDegree(0, 0, 0);
		else if (player->Direction() == "top")
			blackout->RotationDegree(180, 0, 0);

		if (player->GetBMove())
		{
			blackout->Position(player->Position());
		}
	}
	// blackout end

	/// <summary>
	/// 점프 조건 충족시키기
	/// </summary>
	for (int i = 0; i < jumpLines[currentRoom].size(); i++)
	{
		jumpLines[currentRoom][i].line->Update(V, P);
		if (player->GetBMove() == true && !player->GetBLifting() && RoomLineCollision(jumpLines[currentRoom][i], i, player) == player->GetDirection())
		{
			player->Jump();
			player->SetBBase(true);
		}
	}
	// 점프 end

	/// <summary>
	/// currentRoom(현재 있는 방) 설정
	/// </summary>
	// Caution: hallLines / roomLines 건드리면 segment fault
	// room 0
	if (roomLines[0][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[0][9].line->FirstVertexPos().y
		&& roomLines[0][3].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[0][16].line->FirstVertexPos().x)
	{
		currentRoom = 0;
	}
	// room 1
	else if (roomLines[1][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[1][7].line->FirstVertexPos().y
		&& roomLines[1][1].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[1][10].line->FirstVertexPos().x)
	{
		currentRoom = 1;
	}
	// room 2
	else if (roomLines[2][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[2][3].line->FirstVertexPos().y
		&& roomLines[2][1].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[2][2].line->FirstVertexPos().x)
	{
		currentRoom = 2;
	}
	// room 3
	else if (roomLines[3][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[3][21].line->FirstVertexPos().y
		&& roomLines[3][5].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[3][6].line->FirstVertexPos().x)
	{
		currentRoom = 3;
	}
	// room 4
	else if (roomLines[4][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[4][7].line->FirstVertexPos().y
		&& roomLines[4][2].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[4][5].line->FirstVertexPos().x)
	{
		currentRoom = 4;
	}
	// room 5
	else if (roomLines[5][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[5][3].line->FirstVertexPos().y
		&& roomLines[5][1].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[5][2].line->FirstVertexPos().x)
	{
		currentRoom = 5;
	}
	// room 6
	else if (roomLines[6][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[6][3].line->FirstVertexPos().y
		&& roomLines[6][1].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[6][2].line->FirstVertexPos().x)
	{
		currentRoom = 6;
	}
	// room 7
	else if (roomLines[7][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[7][4].line->FirstVertexPos().y
		&& roomLines[7][6].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[7][7].line->FirstVertexPos().x)
	{
		currentRoom = 7;
	}
	// room 8
	else if (roomLines[8][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[8][21].line->FirstVertexPos().y
		&& roomLines[8][5].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[8][8].line->FirstVertexPos().x)
	{
		currentRoom = 8;
	}
	// room 9
	else if (roomLines[9][0].line->FirstVertexPos().y < player->BottomPosition().y
		&& player->TopPosition().y < roomLines[9][43].line->FirstVertexPos().y
		&& roomLines[9][10].line->FirstVertexPos().x < player->LeftPosition().x
		&& player->RightPosition().x < roomLines[9][13].line->FirstVertexPos().x)
	{
		currentRoom = 9;
	}
	// currentRoom end

	/// <summary>
	/// 문(hall) 열리는 시기 결정
	/// </summary>
	// room 1
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
			{
				doors[1][1]->Play(1);
				hallLines[1][1].open = true;
			}
			else if (i == enemies[1].size() - 1)
			{
				doors[1][1]->Play(0); // 해당 방 몬스터 다 못 죽였으면 문 안 열림 
				hallLines[1][1].open = false;
			}
		}
	}
	if (!player->Attacking() && Sprite::Obb(player->GetSprite(), buttons[1][0]))
	{
		hallLines[1][3].open = true;
		doors[1][3]->Play(1); // 문 열림
	}
	// room 2
	if (!objects[2][2]->Exist()) // chest의 key 획득
	{
		if (HallLineCollision(hallLines[2][1], 1, 1, 1.6) != 0)
		{
			hallLines[2][1].open = true;
			doors[2][1]->Play(1); // 문 열림
		}
	}
	// room 4
	if (Sprite::Obb(player->GetSprite(), buttons[4][0]))
	{
		hallLines[4][1].open = true;
		hallLines[4][2].open = true;
		doors[4][1]->Play(1);
		doors[4][2]->Play(2);
	}
	// room 6
	for (int i = 0, cnt = 0; i < enemies[6].size(); i++)
	{
		if (enemies[6][i]->IsDead())
			cnt++;
		if (cnt == enemies[6].size())
		{
			doors[6][0]->Play(1);
			hallLines[6][0].open = true;
			doors[6][1]->Play(1);
			hallLines[6][1].open = true;
		}
		else if (i == enemies[1].size() - 1)
		{
			doors[6][0]->Play(0); // 해당 방 몬스터 다 못 죽였으면 문 안 열림 
			hallLines[6][0].open = false;
			doors[6][1]->Play(0);
			hallLines[6][1].open = false;
		}
	}
	// room 9
	if (Sprite::Obb(player->GetSprite(), buttons[9][0]))
	{
		hallLines[9][1].open = true;
		doors[9][1]->Play(1); // 문 열림
	}
	if (Sprite::Obb(player->GetSprite(), buttons[9][1]))
	{
		hallLines[9][2].open = true;
		doors[9][2]->Play(1); // 문 열림
	}
	// 문 열리는 시기 결정 end

	/// <summary>
	/// 버튼 상호작용
	/// </summary>
	if (Sprite::Obb(player->GetSprite(), buttons[2][0]))
	{
		for (Enemy* enemy : enemies[2])
		{
			if (enemy->GetType() == "flying object")
				enemy->OnScene(true);
		}
	}
	// 버튼 end

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
	/*for (Enemy* ball : enemies[16])
	{
		if (ball->Direction() == 1 && ball->Position().x >= (495 - 1023) * 2.5 + Width / 2)
			ball->Position((301 - 1023) * 2.5 + Width / 2, ball->Position().y);
		else if (ball->Direction() == 2 && ball->Position().y <= (2811 - 760) * 2.5 + Width / 2)
			ball->Position(ball->Position().x, (2811 - 544) * 2.5 + Width / 2);
		else if (ball->Direction() == 3 && ball->Position().y >= (2811 - 544) * 2.5 + Width / 2)
			ball->Position(ball->Position().x, (2811 - 760) * 2.5 + Width / 2);
	}*/
	// 공 움직임 end

	/// <summary>
	/// 원형으로 움직이는 몬스터 업데이트(해당 코드 위치 바꿔서 업데이트 시기를 플레이어가 방에 입장하면 하는 걸로)
	/// </summary>
	//if (abs(player->Position().x - armo_knights[0]->Position().x) <= 200 && abs(player->Position().y - armo_knights[0]->Position().y) <= 200)
	//{
	//	armo_knights_time = 0;

	//	if (Key->Press('S') && abs(player->Position().x - armo_knights[0]->Position().x) >= 100 && abs(player->Position().y - armo_knights[0]->Position().y) >= 100)
	//	{
	//		for (Enemy* enemy : armo_knights)
	//			enemy->Play(1);

	//		armo_knights_time += Timer->Elapsed();
	//		if (armo_knights_time <= 6)
	//		{
	//			armo_knights[0]->Position((128 - 1023) * 2.5 + Width / 2 - sin(armo_knights_time + 2.35619) * 30 * 2.5,
	//				(2811 - 125) * 2.5 + Height / 2 + cos(armo_knights_time + 2.35619) * 30 * 2.5); //이거 각도 조정 (현재 45도)
	//			armo_knights[1]->Position((128 - 1023) * 2.5 + Width / 2 - sin(armo_knights_time + 3.14159) * 30 * 2.5,
	//				(2811 - 125) * 2.5 + Height / 2 + cos(armo_knights_time + 3.14159) * 30 * 2.5);
	//			armo_knights[2]->Position((128 - 1023) * 2.5 + Width / 2 - sin(armo_knights_time + 3.92699) * 30 * 2.5,
	//				(2811 - 125) * 2.5 + Height / 2 + cos(armo_knights_time + 3.92699) * 30 * 2.5);
	//			armo_knights[3]->Position((128 - 1023) * 2.5 + Width / 2 - sin(armo_knights_time + 4.71239) * 30 * 2.5,
	//				(2811 - 125) * 2.5 + Height / 2 + cos(armo_knights_time + 4.71239) * 30 * 2.5);
	//			armo_knights[4]->Position((128 - 1023) * 2.5 + Width / 2 - sin(armo_knights_time) * 30 * 2.5,
	//				(2811 - 125) * 2.5 + Height / 2 + cos(armo_knights_time) * 30 * 2.5);
	//			armo_knights[5]->Position((128 - 1023) * 2.5 + Width / 2 - sin(armo_knights_time + 0.785398) * 30 * 2.5,
	//				(2811 - 125) * 2.5 + Height / 2 + cos(armo_knights_time + 0.785398) * 30 * 2.5);
	//		}
	//	}
	//}
	// armo kights moves end

	/// <summary>
	/// 방마다 다른 오브젝트 Update
	/// </summary>
	// 이전 방
	for (Object* obj : objects[abs((currentRoom - 1) % 21)])
		obj->Update(V, P);
	for (Animation* door : doors[abs((currentRoom - 1) % 21)])
		door->Update(V, P);
	for (Sprite* button : buttons[abs((currentRoom - 1) % 21)])
		button->Update(V, P);

	// 다음 방
	for (Object* obj : objects[abs((currentRoom + 1) % 21)])
		obj->Update(V, P);
	for (Animation* door : doors[(currentRoom + 1) % 21])
		door->Update(V, P);
	for (Sprite* button : buttons[(currentRoom + 1) % 21])
		button->Update(V, P);

	// 현재 방
	for (int i = 0; i < objects[currentRoom].size(); i++)
	{
		objects[currentRoom][i]->Update(V, P);
		ObjectCollision(objects[currentRoom][i], i);

	}
	for (Animation* door : doors[currentRoom])
		door->Update(V, P);
	for (Sprite* button : buttons[currentRoom])
		button->Update(V, P);
	for (Enemy* enemy : enemies[currentRoom])
		enemy->Update(V, P);

	if (bBlackout)
		blackout->Update(V, P);
	// 방마다 다른 오브젝트 Update end
}

void EasternPalace::Render()
{
	eastern_palace->Render();
	base_floor->Render();

	/// <summary>
	/// player 위치에 따라 지형 렌더링 순서 정하기
	/// </summary>
	if (!player->GetBBase()) //계단 내려가기 전
	{
		first_floor->Render();
		player->Render();
	}
	if (player->GetBBase()) //계단 내려가서 밑층에 위치할 때 (임시로 false 설정)
	{
		player->Render();
		first_floor->Render();
	}
	hall->Render();
	// player 위치에 따른 지형 렌더링 end

	/// <summary>
	/// 방마다 다른 오브젝트 Render
	/// </summary>
	// 이전 방
	for (Object* obj : objects[abs((currentRoom - 1) % 21)])
		obj->Render();
	for (Animation* door : doors[abs((currentRoom - 1) % 21)])
		door->Render();
	for (Sprite* button : buttons[abs((currentRoom - 1) % 21)])
		button->Render();

	// 다음 방
	for (Object* obj : objects[abs((currentRoom + 1) % 21)])
		obj->Render();
	for (Animation* door : doors[(currentRoom + 1) % 21])
		door->Render();
	for (Sprite* button : buttons[(currentRoom + 1) % 21])
		button->Render();

	// 현재 방
	for (RoomLine roomLine : roomLines[currentRoom])
	{
		if (!player->GetBBase() && !roomLine.base)
			roomLine.line->Render();
		else if (player->GetBBase() && roomLine.base)
			roomLine.line->Render();
	}
	for (HallLine hallLine : hallLines[currentRoom])
		hallLine.line->Render();
	for (RoomLine jumpLine : jumpLines[currentRoom])
		jumpLine.line->Render();

	for (Object* obj : objects[currentRoom])
		obj->Render();
	for (Animation* door : doors[currentRoom])
		door->Render();
	for (Sprite* button : buttons[currentRoom])
		button->Render();
	for (Enemy* enemy : enemies[currentRoom])
		enemy->Render();
	// 방마다 다른 오브젝트 Render end

	if (bBlackout)
		blackout->Render();
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

void EasternPalace::CreateEnemy(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool onScene, bool bBase)
{
	Enemy* enemy = new Enemy(type, scale, onScene);
	enemy->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	enemy->SetBBase(bBase);
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
	objects[room].push_back(vase);
}

void EasternPalace::CreateChest(string size, string item, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary)
{
	Chest* chest;
	chest = new Chest(size, item, scale);
	chest->Scale(scale);
	chest->DrawBound(boundary);
	chest->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	objects[room].push_back(chest);
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

void EasternPalace::CreateDoor(D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool open, string direction)
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
		//clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 2, 68, 36), 0.1); // x: 32, y: 34
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 1, 0, 1), 0.1); // 닫힌 문의 모습이 default
		door->AddClip(clip); // closed

		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 2, 2, 34, 36), 0.1);
		door->AddClip(clip); // open
	}
	door->Scale(scale);
	door->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	door->Play(0);
	if (direction == "top")
		door->RotationDegree(0, 0, 0);
	else if (direction == "bottom")
		door->RotationDegree(180, 0, 0);
	else if (direction == "right")
		door->RotationDegree(0, 0, -90); // 반시계 방향
	else if (direction == "left")
		door->RotationDegree(0, 0, 90);
	doors[room].push_back(door);
}

void EasternPalace::CreateRoomLine(int x1, int y1, int x2, int y2, int room, bool base)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	D3DXVECTOR2* intersection = new D3DXVECTOR2(0, 0);
	roomLines[room].push_back({ line, intersection, base });
}

void EasternPalace::CreateHallLine(int x1, int y1, int x2, int y2, int room, bool open)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	hallLines[room].push_back({ line, D3DXVECTOR2(0, 0), open });
}

void EasternPalace::CreateJumpLine(int x1, int y1, int x2, int y2, int room)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	D3DXVECTOR2* intersection = new D3DXVECTOR2(0, 0);
	jumpLines[room].push_back({ line, intersection });
}

void EasternPalace::CreateStairLine(int x1, int y1, int x2, int y2, int room)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	stairLines[room].push_back({ line, D3DXVECTOR2(0, 0), true });
}

template<typename T>
int EasternPalace::RoomLineCollision(RoomLine line, int lineIndex, T object)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. 플레이어 위 선분
	if (line.line->SegmentIntersection(object->Position(), object->TopPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "top");
		return 4;
	}

	else if (object->GetTopBLineCollisionIndex() == lineIndex && // 서로 평행한 선분 2개 위치할 경우 인덱스가 작은 선과 충돌했는데 인덱스가 큰 선과는 충돌하지 않으므로 최종적으로 플레이어가 선 충돌하지 않았다고 판별하는 거... 방지
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->BottomPosition(), object->TopPosition())))
	{
		object->LineCollision(false, lineIndex, "top");
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 플레이어 아래
	if (line.line->SegmentIntersection(object->Position(), object->BottomPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "bottom");
		return 3;
	}

	else if (object->GetBottomBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->TopPosition(), object->BottomPosition())))
	{
		object->LineCollision(false, lineIndex, "bottom");
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 플레이어 왼쪽
	if (line.line->SegmentIntersection(object->Position(), object->LeftPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "left");
		return 1;
	}

	else if (object->GetLeftBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->RightPosition(), object->LeftPosition())))
	{
		object->LineCollision(false, lineIndex, "left");
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. 플레이어 오른쪽
	if (line.line->SegmentIntersection(object->Position(), object->RightPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "right");
		return 2;
	}

	else if (object->GetRightBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->LeftPosition(), object->RightPosition())))
	{
		object->LineCollision(false, lineIndex, "right");
		return 0;
	}
}

int EasternPalace::HallLineCollision(HallLine line, int lineIndex, float speed, float time)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. 플레이어 위 선분
	if (line.line->SegmentIntersection(player->Position(), player->TopPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, "top");
			player->AutoMoving("top", speed, time);
			return 4;
		}
		else
		{
			player->LineCollision(true, lineIndex, "top");
			return 0;
		}
	}

	else if (player->GetTopBLineCollisionIndex() == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->TopPosition(), player->BottomPosition())))
	{
		player->LineCollision(false, lineIndex, "top");
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 플레이어 아래 선분
	if (line.line->SegmentIntersection(player->Position(), player->BottomPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, "bottom");
			player->AutoMoving("bottom", speed, time);
			return 3;
		}
		else
		{
			player->LineCollision(true, lineIndex, "bottom");
			return 0;
		}
	}

	else if (player->GetBottomBLineCollisionIndex() == lineIndex && // 이거 필요??
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->TopPosition(), player->BottomPosition())))
	{
		player->LineCollision(false, lineIndex, "bottom");
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 플레이어 왼쪽
	if (line.line->SegmentIntersection(player->Position(), player->LeftPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, "left");
			player->AutoMoving("left", speed, time);
			return 1;
		}
		else
		{
			player->LineCollision(true, lineIndex, "left");
			return 0;
		}
	}

	else if (player->GetLeftBLineCollisionIndex() == lineIndex && // 이거 필요??
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->RightPosition(), player->LeftPosition())))
	{
		player->LineCollision(false, lineIndex, "left");
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. 플레이어 오른쪽
	if (line.line->SegmentIntersection(player->Position(), player->RightPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (line.open)
		{
			player->LineCollision(false, lineIndex, "right");
			player->AutoMoving("right", speed, time);
			return 2;
		}
		else
		{
			player->LineCollision(true, lineIndex, "right");
			return 0;
		}
	}

	else if (player->GetRightBLineCollisionIndex() == lineIndex && // 이거 필요??
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->LeftPosition(), player->RightPosition())))
	{
		player->LineCollision(false, lineIndex, "right");
		return 0;
	}
}

int EasternPalace::ObjectCollision(Object* obj, int objIndex)
{
	int collision = 0;

	if ((player->GetTopBObjectCollisionIndex() == objIndex || player->GetBottomBObjectCollisionIndex() == objIndex
		|| player->GetRightBObjectCollisionIndex() == objIndex || player->GetLeftBObjectCollisionIndex() == objIndex)
		&& !obj->Exist())
	{
		player->ObjectCollision(false, objIndex, "top");
		player->ObjectCollision(false, objIndex, "bottom");
		player->ObjectCollision(false, objIndex, "right");
		player->ObjectCollision(false, objIndex, "left");
	} // object가 없을 때 선 충돌 x

	// top
	if (Sprite::Obb(obj->GetSprite(), player->GetSprite()) && obj->Position().y >= player->Position().y)
	{
		player->ObjectCollision(true, objIndex, "top");
		collision = 4;
	}
	else if(player->GetTopBObjectCollisionIndex() == objIndex && obj->Position().y >= player->Position().y )
	{
		player->ObjectCollision(false, objIndex, "top");
	}

	// bottom
	if (Sprite::Obb(obj->GetSprite(), player->GetSprite()) && obj->Position().y < player->Position().y)
	{
		player->ObjectCollision(true, objIndex, "bottom");
		collision = 3;
	}
	else if (player->GetBottomBObjectCollisionIndex() == objIndex && obj->Position().y < player->Position().y)
	{
		player->ObjectCollision(false, objIndex, "bottom");
	}

	// right
	if (Sprite::Obb(obj->GetSprite(), player->GetSprite()) && obj->Position().x >= player->Position().x)
	{
		player->ObjectCollision(true, objIndex, "right");
		collision = 2;
	}
	else if (player->GetRightBObjectCollisionIndex() == objIndex && obj->Position().x >= player->Position().x)
	{
		player->ObjectCollision(false, objIndex, "right");
	}

	// left
	if (Sprite::Obb(obj->GetSprite(), player->GetSprite()) && obj->Position().x < player->Position().x)
	{
		player->ObjectCollision(true, objIndex, "left");
		collision = 1;
	}
	else if (player->GetLeftBObjectCollisionIndex() == objIndex && obj->Position().x < player->Position().x)
	{
		player->ObjectCollision(false, objIndex, "left");
	}

	return collision;
}
