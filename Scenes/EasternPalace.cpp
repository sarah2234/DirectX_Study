#include "stdafx.h"
#include "EasternPalace.h"
#include "Viewer/Following.h"
#include <math.h>

EasternPalace::EasternPalace(SceneValues* values, D3DXVECTOR2 position)
	:Scene(values, position), on(false)
	, enemyMoveSpeed(200), armo_knights_time(0), currentRoom(0), bBlackout(false), flag(0)
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
	blackout->Scale(3, 3);
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
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(936, 1574), 9, true, true);
	CreateEnemy("skeleton", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1096, 1574), 9, true, true);
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
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1720.5, 1815.5), 11, true, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1720.5, 1799.5), 11, true, true);
	CreateVase("heart", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1720.5, 1783.5), 11, true, true);
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
	CreateChest("big", "bow", D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 1532.5), 9, true, true);
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
	// room 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 2, true, "right"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(639.5, 1862.5), 2, false, "top"); // 1
	// room 3
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 2312.5), 3, true, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(789.5, 1960.5), 3, true, "left"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1257.5, 1960.5), 3, false, "right"); // 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 1862.5), 3, true, "top"); // 3
	// room 4
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1302.5, 1960.5), 4, false, "left"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1513.5, 1960.5), 4, false, "right"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1407.5, 1862.5), 4, false, "top"); // 2
	// room 5
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1557.5, 1960.5), 5, true, "left"); // 0
	// room 6
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(489.5, 1704.5), 6, false, "right"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(383.5, 1606.5), 6, false, "top"); // 1
	// room 7
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(383.5, 1546.5), 7, true, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(466.5, 1448.5), 7, true, "right"); // 1
	// room 8
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(639.5, 1802.5), 8, false, "bottom"); // 0
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
	// room 10
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 10, true, "top"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 10, true, "right"); // 1
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 10, true, "left"); // 2
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 10, true, "left"); // 3
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 10, true, "right"); // 4
	// room 11
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 11, true, "left"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 11, true, "top"); // 1
	// room 12
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1663.5, 1546.5), 12, false, "bottom"); // 0
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(0, 0), 12, true, "left"); // 1
	// room 13
	CreateDoor(D3DXVECTOR2(2.5, 2.5), D3DXVECTOR2(1023.5, 1290.5), 13, false, "bottom"); // 0
	// end of doors

	/// <summary>
	/// Lines
	/// </summary>
	// room 0
	CreateRoomLine(1014, 2824, 1033, 2824, 0, false); // 0-0 bottom
	CreateRoomLine(874, 2774, 874, 2649, 0, false); //3 left
	CreateRoomLine(1174, 2649, 1174, 2774, 0, false); //16 right
	CreateRoomLine(1001, 2649, 1034, 2649, 0, false); //9 top
	CreateRoomLine(1014, 2824, 1014, 2806, 0, false); // 0-1
	CreateRoomLine(1033, 2824, 1033, 2806, 0, false); // 0-2
	CreateRoomLine(1014, 2806, 945, 2806, 0, false); // 0-3
	CreateRoomLine(1033, 2806, 1102, 2806, 0, false); //0-4
	CreateRoomLine(945, 2806, 945, 2774, 0, false); //1
	CreateRoomLine(945, 2774, 874, 2774, 0, false); //2
	CreateRoomLine(874, 2649, 895, 2649, 0, false); //4
	CreateRoomLine(895, 2649, 918, 2649, 0, false); //5
	CreateRoomLine(918, 2649, 918, 2713, 0, false); //6
	CreateRoomLine(918, 2713, 1001, 2713, 0, false); //7
	CreateRoomLine(1001, 2713, 1001, 2649, 0, false); //8
	CreateRoomLine(1034, 2649, 1046, 2649, 0, false); //10
	CreateRoomLine(1046, 2649, 1046, 2713, 0, false); //11
	CreateRoomLine(1046, 2713, 1129, 2713, 0, false); //12
	CreateRoomLine(1129, 2713, 1129, 2649, 0, false); //13
	CreateRoomLine(1129, 2649, 1162, 2649, 0, false); //14
	CreateRoomLine(1162, 2649, 1174, 2649, 0, false); //15
	CreateRoomLine(1174, 2774, 1102, 2774, 0, false); //17
	CreateRoomLine(1102, 2774, 1102, 2806, 0, false); //18
	CreateRoomLine(1102, 2806, 1102, 2806, 0, false); //19
	CreateRoomLine(944, 2743, 975, 2743, 0, false); //20
	CreateRoomLine(944, 2743, 944, 2713, 0, false); //21
	CreateRoomLine(975, 2743, 975, 2713, 0, false); //22
	CreateRoomLine(1072, 2743, 1103, 2743, 0, false); //23
	CreateRoomLine(1072, 2743, 1072, 2713, 0, false); //24
	CreateRoomLine(1103, 2743, 1103, 2713, 0, false); //25

	CreateHallLine(886, 2649, 905, 2649, 0, true); // 0
	CreateHallLine(1014, 2649, 1033, 2649, 0, false, 1.6); // 1
	CreateHallLine(1142, 2649, 1161, 2649, 0, true); // 2

	// room 1
	CreateRoomLine(880, 2551, 911, 2551, 1, false); // 20 bottom
	CreateRoomLine(880, 2551, 880, 2511, 1, false); // 21 left
	CreateRoomLine(1167, 2551, 1167, 2511, 1, false); // 30 right
	CreateRoomLine(992, 2393, 1055, 2393, 1, false); // 27 top
	CreateRoomLine(911, 2551, 911, 2511, 1, false); // 22
	CreateRoomLine(880, 2511, 911, 2511, 1, false); // 23
	CreateRoomLine(992, 2551, 1055, 2551, 1, false); // 24
	CreateRoomLine(992, 2551, 992, 2393, 1, false); // 25
	CreateRoomLine(1055, 2551, 1055, 2393, 1, false); // 26
	CreateRoomLine(1136, 2551, 1167, 2551, 1, false); // 28
	CreateRoomLine(1136, 2551, 1136, 2511, 1, false); // 29
	CreateRoomLine(1136, 2511, 1167, 2511, 1, false); // 31

	CreateHallLine(886, 2551, 905, 2551, 1, true); // 3
	CreateHallLine(1014, 2551, 1033, 2551, 1, true); // 4
	CreateHallLine(1142, 2551, 1161, 2551, 1, true); // 5
	CreateHallLine(1014, 2393, 1033, 2393, 1, false, 1.6); // 6

	// room 2
	CreateRoomLine(569, 2294, 726, 2294, 2, false); // 32 bottom
	CreateRoomLine(569, 2294, 569, 1881, 2, false); // 33 left
	CreateRoomLine(726, 2294, 726, 1881, 2, false); // 34 right
	CreateRoomLine(569, 1881, 726, 1881, 2, false); // 35 top

	CreateRoomLine(616, 2007, 623, 2007, 2, false); // 36
	CreateRoomLine(672, 2007, 679, 2007, 2, false); // 37
	CreateRoomLine(616, 2007, 616, 1999, 2, false); // 38
	CreateRoomLine(679, 2007, 679, 1999, 2, false); // 39
	CreateRoomLine(616, 1999, 592, 1999, 2, false); // 40
	CreateRoomLine(679, 1999, 703, 1999, 2, false); // 41
	CreateRoomLine(592, 1999, 592, 1920, 2, false); // 42
	CreateRoomLine(703, 1999, 703, 1920, 2, false); // 43
	CreateRoomLine(592, 1920, 703, 1920, 2, false); // 44
	CreateRoomLine(623, 2007, 623, 1983, 2, true); // 45
	CreateRoomLine(672, 2007, 672, 1983, 2, true); // 46
	CreateRoomLine(623, 1983, 608, 1983, 2, true); // 47
	CreateRoomLine(672, 1983, 687, 1983, 2, true); // 48
	CreateRoomLine(608, 1983, 608, 1936, 2, true); // 49
	CreateRoomLine(687, 1983, 687, 1936, 2, true); // 50
	CreateRoomLine(608, 1936, 687, 1936, 2, true); // 51
	CreateRoomLine(608, 2255, 623, 2255, 2, false); // 52
	CreateRoomLine(608, 2255, 608, 2208, 2, false); // 53
	CreateRoomLine(623, 2255, 623, 2208, 2, false); // 54
	CreateRoomLine(608, 2208, 623, 2208, 2, false); // 55
	CreateRoomLine(672, 2255, 687, 2255, 2, false); // 56
	CreateRoomLine(672, 2255, 672, 2208, 2, false); // 57
	CreateRoomLine(687, 2255, 687, 2208, 2, false); // 58
	CreateRoomLine(672, 2208, 687, 2208, 2, false); // 59
	CreateRoomLine(608, 2175, 687, 2175, 2, false); // 60
	CreateRoomLine(608, 2175, 608, 2152, 2, false); // 61
	CreateRoomLine(687, 2175, 687, 2152, 2, false); // 62
	CreateRoomLine(608, 2152, 687, 2152, 2, false); // 63
	CreateRoomLine(592, 2127, 607, 2127, 2, false); // 64
	CreateRoomLine(592, 2127, 592, 2032, 2, false); // 65
	CreateRoomLine(607, 2127, 607, 2032, 2, false); // 66
	CreateRoomLine(592, 2032, 607, 2032, 2, false); // 67
	CreateRoomLine(688, 2127, 703, 2127, 2, false); // 68
	CreateRoomLine(688, 2127, 688, 2032, 2, false); // 69
	CreateRoomLine(703, 2127, 703, 2032, 2, false); // 70
	CreateRoomLine(688, 2032, 703, 2032, 2, false); // 71

	CreateStairLine(624, 2007, 671, 2007, 2); // 0
	CreateStairLine(624, 1983, 671, 1983, 2); // 1

	CreateHallLine(726, 1950, 726, 1969, 2, true, 1.2); // 7
	CreateHallLine(630, 1881, 649, 1881, 2, false, 1.8); // 8

	// room 3
	CreateRoomLine(929, 2294, 1166, 2294, 3, false); // 0 bottom
	CreateRoomLine(809, 2166, 809, 2135, 3, false); // 5 left
	CreateRoomLine(1238, 2166, 1238, 2105, 3, false); // 6 right
	CreateRoomLine(961, 1881, 1134, 1881, 3, false); // 21 top
	CreateRoomLine(929, 2294, 929, 2255, 3, false); // 1
	CreateRoomLine(1166, 2294, 1166, 2255, 3, false); // 2	
	CreateRoomLine(929, 2255, 1166, 2255, 3, false); // 3
	CreateRoomLine(809, 2166, 1238, 2166, 3, false); // 4
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
	CreateRoomLine(961, 1920, 1134, 1920, 3, false); // 18 *
	CreateRoomLine(961, 1920, 961, 1881, 3, false); // 19
	CreateRoomLine(1134, 1920, 1134, 1881, 3, false); // 20
	CreateRoomLine(929, 2287, 959, 2287, 3, false); // 50
	CreateRoomLine(959, 2287, 959, 2255, 3, false); // 51
	CreateRoomLine(1136, 2287, 1166, 2287, 3, false); // 52
	CreateRoomLine(1136, 2287, 1136, 2255, 3, false); // 53
	CreateRoomLine(961, 1881, 1134, 1881, 3, false); // 21 top

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
	CreateRoomLine(991, 1945, 1104, 1945, 3, true); // 46
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
	CreateHallLine(809, 1969, 809, 1951, 3, true, 1.2);
	CreateHallLine(1238, 1969, 1238, 1951, 3, false, 1.2);
	CreateHallLine(1014, 1881, 1033, 1881, 3, true);

	CreateStairLine(967, 2255, 984, 2255, 3); // 0
	CreateStairLine(1111, 2255, 1128, 2255, 3); // 1
	CreateStairLine(967, 2224, 984, 2224, 3); // 2
	CreateStairLine(1111, 2224, 1128, 2224, 3); // 3
	CreateStairLine(847, 2135, 864, 2134, 3); // 4
	CreateStairLine(847, 2104, 864, 2104, 3); // 5
	CreateStairLine(967, 1951, 984, 1951, 3); // 6
	CreateStairLine(967, 1920, 984, 1920, 3); // 7
	CreateStairLine(1111, 1951, 1128, 1951, 3); // 8
	CreateStairLine(1111, 1920, 1128, 1920, 3); // 9

	CreateJumpLine(991, 2255, 1025, 2255, 3); // 0
	CreateJumpLine(1071, 2255, 1104, 2255, 3); // 1
	CreateJumpLine(959, 2166, 991, 2166, 3); // 2
	CreateJumpLine(1104, 2166, 1136, 2166, 3); // 3
	CreateJumpLine(991, 1920, 1025, 1920, 3); // 4
	CreateJumpLine(1071, 1920, 1104, 1920, 3); // 5

	// room 4
	CreateRoomLine(1321, 2038, 1494, 2038, 4, false); // 0 bottom
	CreateRoomLine(1321, 2038, 1321, 1881, 4, false); // 2 left
	CreateRoomLine(1494, 2038, 1494, 1881, 4, false); // 5 right
	CreateRoomLine(1321, 1881, 1494, 1881, 4, false); // 7 top
	CreateRoomLine(1350, 2009, 1465, 2009, 4, false); // 1
	CreateRoomLine(1350, 2009, 1350, 1910, 4, false); // 3
	CreateRoomLine(1465, 2009, 1465, 1910, 4, false); // 4
	CreateRoomLine(1350, 1910, 1465, 1910, 4, false); // 6

	CreateHallLine(1321, 1970, 1321, 1949, 4, false, 1.2); // 0
	CreateHallLine(1494, 1970, 1494, 1949, 4, true, 1.2); // 1
	CreateHallLine(1397, 1881, 1418, 1881, 4, true); // 2

	// room 5
	CreateRoomLine(1577, 2038, 1750, 2038, 5, false); // 0 bottom
	CreateRoomLine(1577, 2038, 1577, 1881, 5, false); // 1 left
	CreateRoomLine(1750, 2038, 1750, 1881, 5, false); // 2 right
	CreateRoomLine(1577, 1881, 1750, 1881, 5, false); // 3 top

	CreateHallLine(1577, 1970, 1577, 1950, 5, true, 1.2); // 0

	// room 6
	CreateRoomLine(297, 1782, 470, 1782, 6, false); // 0 bottom
	CreateRoomLine(297, 1782, 297, 1625, 6, false); // 1 left
	CreateRoomLine(470, 1782, 470, 1625, 6, false); // 2 right
	CreateRoomLine(297, 1625, 470, 1625, 6, false); // 3 top

	CreateHallLine(470, 1714, 470, 1693, 6, false, 1.2); // 0
	CreateHallLine(373, 1625, 394, 1625, 6, false, 1.6); // 1

	// room 7
	CreateRoomLine(367, 1526, 408, 1526, 7, false); // 0 bottom
	CreateRoomLine(321, 1457, 321, 1502, 7, true); // 6 left
	CreateRoomLine(446, 1502, 446, 1425, 7, true); // 7 right
	CreateRoomLine(329, 1369, 406, 1369, 7, false); // 4 top
	CreateRoomLine(367, 1526, 367, 1424, 7, false); // 1
	CreateRoomLine(360, 1526, 367, 1526, 7, false); // 10
	CreateRoomLine(360, 1432, 360, 1526, 7, false); // 11
	CreateRoomLine(329, 1432, 329, 1369, 7, false); // 2
	CreateRoomLine(406, 1526, 406, 1369, 7, false); // 3
	CreateRoomLine(321, 1502, 446, 1502, 7, true); // 5
	CreateRoomLine(321, 1457, 327, 1457, 7, true); // 12
	CreateRoomLine(361, 1463, 361, 1425, 7, true); // 8
	CreateRoomLine(361, 1425, 446, 1425, 7, true); // 9

	CreateHallLine(374, 1526, 393, 1526, 7, true); // 0
	CreateHallLine(446, 1457, 446, 1438, 7, true, 2.0); // 1

	CreateStairLine(335, 1463, 352, 1463, 7); // 0
	CreateStairLine(335, 1432, 352, 1432, 7); // 1

	// room 8
	CreateRoomLine(623, 1782, 656, 1782, 8, false); // 0 bottom
	CreateRoomLine(553, 1726, 553, 1503, 8, false); // 5 left
	CreateRoomLine(726, 1726, 726, 1503, 8, false); // 8 right
	CreateRoomLine(577, 1425, 702, 1425, 8, true); // 21 top
	CreateRoomLine(623, 1782, 623, 1759, 8, false); // 1
	CreateRoomLine(656, 1782, 656, 1759, 8, false); // 2
	CreateRoomLine(553, 1726, 592, 1726, 8, false); // 3
	CreateRoomLine(687, 1726, 726, 1726, 8, false); // 4
	CreateRoomLine(592, 1726, 592, 1648, 8, false); // 6
	CreateRoomLine(687, 1726, 687, 1648, 8, false); // 7
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

	CreateHallLine(629, 1782, 650, 1782, 8, false, 1.8); // 0
	CreateHallLine(553, 1713, 553, 1694, 8, true, 1.2); // 1
	CreateHallLine(726, 1585, 726, 1566, 8, true, 1.2); // 2
	CreateHallLine(577, 1457, 577, 1438, 8, true, 2.0); // 3
	CreateHallLine(702, 1457, 702, 1438, 8, true, 2.0); // 4

	CreateStairLine(631, 1759, 648, 1759, 8); // 0
	CreateStairLine(631, 1728, 648, 1728, 8, 1.3); // 1

	// room 9
	CreateRoomLine(1001, 1782, 1046, 1782, 9, false); // 0 bottom
	CreateRoomLine(809, 1654, 809, 1559, 9, false); // 10 left
	CreateRoomLine(1238, 1654, 1238, 1559, 9, false); // 13 right
	CreateRoomLine(983, 1369, 1064, 1369, 9, false); // 43 bottom
	CreateRoomLine(1001, 1782, 1001, 1686, 9, false); // 1
	CreateRoomLine(1046, 1782, 1046, 1686, 9, false); // 2
	CreateRoomLine(1001, 1686, 857, 1686, 9, false); // 3
	CreateRoomLine(1046, 1686, 1190, 1686, 9, false); // 4
	CreateRoomLine(857, 1686, 857, 1654, 9, false); // 5
	CreateRoomLine(1190, 1686, 1190, 1654, 9, false); // 6
	CreateRoomLine(857, 1654, 809, 1654, 9, false); // 7
	CreateRoomLine(1190, 1654, 1238, 1654, 9, false); // 8
	CreateRoomLine(880, 1655, 1167, 1655, 9, false); // 9
	CreateRoomLine(880, 1655, 880, 1591, 9, false); // 11
	CreateRoomLine(1167, 1655, 1167, 1591, 9, false); // 12
	CreateRoomLine(809, 1559, 848, 1559, 9, false); // 14
	CreateRoomLine(848, 1559, 848, 1591, 9, false); // 15
	CreateRoomLine(848, 1591, 880, 1591, 9, false); // 16
	CreateRoomLine(1167, 1591, 1199, 1591, 9, false); // 17
	CreateRoomLine(1199, 1591, 1199, 1559, 9, false); // 18
	CreateRoomLine(1199, 1559, 1238, 1559, 9, false); // 19
	CreateRoomLine(913, 1622, 1134, 1622, 9, true); // 20
	CreateRoomLine(913, 1622, 913, 1526, 9, true); // 21
	CreateRoomLine(1134, 1622, 1134, 1526, 9, true); // 22
	CreateRoomLine(913, 1526, 833, 1526, 9, true); // 23
	CreateRoomLine(1134, 1526, 1214, 1526, 9, true); // 24
	CreateRoomLine(833, 1526, 833, 1424, 9, true); // 25
	CreateRoomLine(1214, 1526, 1214, 1424, 9, true); // 26
	CreateRoomLine(833, 1423, 863, 1423, 9, true); // 27 - 1
	CreateRoomLine(863, 1423, 863, 1393, 9, true); // 27 - 2
	CreateRoomLine(1214, 1423, 1184, 1423, 9, true); // 28 - 1
	CreateRoomLine(1184, 1423, 1184, 1393, 9, true); // 28 - 1
	CreateRoomLine(864, 1393, 950, 1393, 9, true); // 29
	CreateRoomLine(1097, 1393, 1183, 1393, 9, true); // 30
	CreateRoomLine(950, 1425, 950, 1393, 9, true); // 31
	CreateRoomLine(1097, 1425, 1097, 1393, 9, true); // 32
	CreateRoomLine(950, 1425, 976, 1425, 9, true); // 33
	CreateRoomLine(976, 1425, 976, 1455, 9, true); // 34
	CreateRoomLine(976, 1455, 1007, 1455, 9, true); // 35
	CreateRoomLine(1007, 1455, 1007, 1425, 9, true); // 36
	CreateRoomLine(1040, 1455, 1040, 1425, 9, true); // 37
	CreateRoomLine(1040, 1455, 1071, 1455, 9, true); // 38
	CreateRoomLine(1071, 1455, 1071, 1425, 9, true); // 39
	CreateRoomLine(1071, 1425, 1097, 1425, 9, true); // 40
	CreateRoomLine(983, 1400, 983, 1369, 9, true); // 41
	CreateRoomLine(1064, 1400, 1064, 1369, 9, true); // 42
	CreateRoomLine(983, 1400, 1016, 1400, 9, false); // 43 맞은 편의 왼쪽
	CreateRoomLine(1032, 1400, 1071, 1400, 9, false); // 43 맞은 편의 오른쪽
	CreateRoomLine(992, 1591, 999, 1591, 9, true); // 44
	CreateRoomLine(1048, 1591, 1055, 1591, 9, true); // 45
	CreateRoomLine(992, 1591, 992, 1583, 9, true); // 46
	CreateRoomLine(1055, 1591, 1055, 1583, 9, true); // 47
	CreateRoomLine(960, 1583, 992, 1583, 9, true); // 48
	CreateRoomLine(1055, 1583, 1087, 1583, 9, true); // 49
	CreateRoomLine(960, 1583, 960, 1488, 9, true); // 50
	CreateRoomLine(1087, 1583, 1087, 1488, 9, true); // 51
	CreateRoomLine(960, 1488, 1087, 1488, 9, true); // 52
	CreateRoomLine(999, 1591, 999, 1567, 9, true); // 53
	CreateRoomLine(1048, 1591, 1048, 1567, 9, true); // 54
	CreateRoomLine(976, 1567, 999, 1567, 9, true); // 55
	CreateRoomLine(1048, 1567, 1071, 1567, 9, true); // 56
	CreateRoomLine(976, 1567, 976, 1504, 9, true); // 57
	CreateRoomLine(1071, 1567, 1071, 1504, 9, true); // 58
	CreateRoomLine(976, 1504, 1071, 1504, 9, true); // 59

	// 지하의 몬스터 움직임 제어 용도 선
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
	CreateRoomLine(992, 1591, 1055, 1591, 9, false); // 44 + 45
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
	CreateHallLine(809, 1586, 809, 1565, 9, false, 1.2); // 1
	CreateHallLine(1238, 1586, 1238, 1565, 9, false, 1.2); // 2
	CreateHallLine(833, 1457, 833, 1438, 9, true, 2.0); // 3	
	CreateHallLine(1214, 1457, 1214, 1438, 9, true, 2.0); // 4
	CreateHallLine(1013, 1369, 1034, 1369, 9, false, 1.6); // 5

	CreateStairLine(999, 1591, 1048, 1591, 9); // 0
	CreateStairLine(999, 1567, 1048, 1567, 9); // 1
	CreateStairLine(1015, 1431, 1032, 1431, 9); // 2
	CreateStairLine(1015, 1400, 1032, 1400, 9); // 3

	// room 10
	CreateRoomLine(1393, 1782, 1422, 1782, 10, false); // 0
	CreateRoomLine(1321, 1648, 1321, 1487, 10, false); // 1
	CreateRoomLine(1494, 1719, 1494, 1423, 10, false); // 2
	CreateRoomLine(1345, 1393, 1470, 1393, 10, true); // 3
	CreateRoomLine(1393, 1782, 1393, 1727, 10, false); // 4
	CreateRoomLine(1422, 1782, 1422, 1727, 10, false); // 5
	CreateRoomLine(1455, 1720, 1494, 1720, 10, false); // 6
	CreateRoomLine(1455, 1720, 1455, 1648, 10, false); // 7
	CreateRoomLine(1494, 1720, 1494, 1423, 10, false); // 8
	CreateRoomLine(1321, 1648, 1455, 1648, 10, false); // 9
	CreateRoomLine(1352, 1623, 1399, 1623, 10, false); // 10
	CreateRoomLine(1424, 1623, 1471, 1623, 10, false); // 11
	CreateRoomLine(1352, 1623, 1352, 1576, 10, false); // 12
	CreateRoomLine(1399, 1623, 1399, 1576, 10, false); // 13
	CreateRoomLine(1424, 1623, 1424, 1576, 10, false); // 14
	CreateRoomLine(1471, 1623, 1471, 1576, 10, false); // 15
	CreateRoomLine(1352, 1576, 1399, 1576, 10, false); // 16
	CreateRoomLine(1424, 1576, 1471, 1576, 10, false); // 17
	CreateRoomLine(1352, 1559, 1399, 1559, 10, false); // 18
	CreateRoomLine(1424, 1559, 1471, 1559, 10, false); // 19
	CreateRoomLine(1352, 1559, 1352, 1512, 10, false); // 20
	CreateRoomLine(1399, 1559, 1399, 1512, 10, false); // 21
	CreateRoomLine(1424, 1559, 1424, 1512, 10, false); // 22
	CreateRoomLine(1471, 1559, 1471, 1512, 10, false); // 23
	CreateRoomLine(1352, 1512, 1399, 1512, 10, false); // 24
	CreateRoomLine(1424, 1512, 1471, 1512, 10, false); // 25
	CreateRoomLine(1321, 1487, 1399, 1487, 10, false); // 26
	CreateRoomLine(1424, 1495, 1471, 1495, 10, false); // 27
	CreateRoomLine(1399, 1487, 1399, 1423, 10, false); // 28
	CreateRoomLine(1424, 1495, 1424, 1448, 10, false); // 29
	CreateRoomLine(1471, 1495, 1471, 1448, 10, false); // 30
	CreateRoomLine(1424, 1448, 1471, 1448, 10, false); // 31
	CreateRoomLine(1399, 1423, 1494, 1423, 10, false); // 32
	CreateRoomLine(1345, 1702, 1470, 1702, 10, true); // 33
	CreateRoomLine(1345, 1702, 1345, 1393, 10, true); // 34
	CreateRoomLine(1470, 1702, 1470, 1393, 10, true); // 35
	CreateRoomLine(1321, 1648, 1321, 1487, 10, false); // 1
	
	CreateStairLine(1400, 1727, 1415, 1727, 10); // 0
	CreateStairLine(1400, 1696, 1415, 1696, 10); // 1

	CreateHallLine(1398, 1782, 1417, 1782, 10, true); // 0
	CreateHallLine(1494, 1713, 1494, 1694, 10, true, 1.2); // 1
	CreateHallLine(1321, 1585, 1321, 1566, 10, true, 1.2); // 2
	CreateHallLine(1345, 1457, 1345, 1438, 10, true, 2.0); // 3
	CreateHallLine(1494, 1457, 1494, 1438, 10, true, 1.2); // 4

	// room 11
	CreateRoomLine(1577, 1782, 1686, 1782, 11, false); // 0
	CreateRoomLine(1577, 1782, 1577, 1657, 11, false); // 1
	CreateRoomLine(1750, 1750, 1750, 1625, 11, false); // 2
	CreateRoomLine(1625, 1625, 1750, 1625, 11, false); // 3
	CreateRoomLine(1686, 1782, 1686, 1751, 11, false); // 4
	CreateRoomLine(1577, 1657, 1616, 1657, 11, false); // 5
	CreateRoomLine(1625, 1656, 1625, 1625, 11, false); // 6
	CreateRoomLine(1616, 1751, 1616, 1720, 11, false); // 13
	CreateRoomLine(1695, 1751, 1695, 1751, 11, false); // 14
	CreateRoomLine(1616, 1687, 1616, 1657, 11, false); // 15
	CreateRoomLine(1695, 1687, 1695, 1657, 11, false); // 16
	CreateRoomLine(1577, 1726, 1695, 1726, 11, true); // 7
	CreateRoomLine(1695, 1726, 1695, 1824, 11, true); // 8
	CreateRoomLine(1695, 1824, 1750, 1824, 11, true); // 9
	CreateRoomLine(1750, 1824, 1750, 1681, 11, true); // 10
	CreateRoomLine(1577, 1681, 1750, 1681, 11, true); // 11
	CreateRoomLine(1616, 1719, 1616, 1688, 11, true); // 12

	CreateHallLine(1577, 1713, 1577, 1694, 11, true, 1.2); // 0
	CreateHallLine(1654, 1625, 1673, 1625, 11, true); // 1

	CreateStairLine(1639, 1751, 1656, 1751, 11); // 0
	CreateStairLine(1639, 1720, 1656, 1720, 11); // 1

	CreateJumpLine(1616, 1719, 1616, 1688, 11); // 0
	CreateJumpLine(1695, 1719, 1695, 1688, 11); // 1
	CreateRoomLine(1616, 1751, 1686, 1751, 11, false); // 17
	CreateRoomLine(1625, 1656, 1695, 1656, 11, false); // 18
	
	// room 12
	CreateRoomLine(1577, 1526, 1750, 1526, 12, false); // 0
	CreateRoomLine(1577, 1526, 1577, 1369, 12, false); // 1
	CreateRoomLine(1750, 1526, 1750, 1369, 12, false); // 2
	CreateRoomLine(1577, 1369, 1750, 1369, 12, false); // 3

	CreateHallLine(1653, 1526, 1674, 1526, 12, true); // 0
	CreateHallLine(1577, 1457, 1577, 1438, 12, true, 1.2); // 1

	// room 13
	CreateRoomLine(937, 1270, 1110, 1270, 13, false); // 0
	CreateRoomLine(873, 1142, 873, 1113, 13, false); // 1
	CreateRoomLine(1174, 1142, 1174, 1113, 13, false); // 2
	CreateRoomLine(873, 1113, 1174, 1113, 13, false); // 3
	CreateRoomLine(937, 1270, 937, 1142, 13, false); // 4
	CreateRoomLine(1110, 1270, 1110, 1142, 13, false); // 5
	CreateRoomLine(873, 1142, 937, 1142, 13, false); // 6
	CreateRoomLine(1110, 1142, 1174, 1142, 13, false); // 7

	CreateHallLine(1013, 1270, 1034, 1270, 13, false); // 0
	CreateHallLine(1142, 1113, 1161, 1113, 13, true); // 1

	// room 14
	CreateRoomLine(1065, 1014, 1238, 1014, 14, false); // 0
	CreateRoomLine(1065, 1014, 1065, 999, 14, false); // 1
	CreateRoomLine(1238, 1014, 1238, 999, 14, false); // 2
	CreateRoomLine(1089, 873, 1214, 873, 14, true); // 3
	CreateRoomLine(1065, 999, 1095, 999, 14, false); // 4
	CreateRoomLine(1208, 999, 1238, 999, 14, false); // 5
	CreateRoomLine(1095, 999, 1095, 991, 14, false); // 9
	CreateRoomLine(1208, 999, 1208, 991, 14, false); // 10
	CreateRoomLine(1089, 966, 1214, 966, 14, true); // 6
	CreateRoomLine(1089, 966, 1089, 873, 14, true); // 7
	CreateRoomLine(1214, 966, 1214, 873, 14, true); // 8
	
	CreateHallLine(1142, 1014, 1161, 1014, 14, true); // 0

	CreateStairLine(1103, 991, 1120, 991, 14); // 0
	CreateStairLine(1183, 991, 1200, 991, 14); // 1
	CreateStairLine(1103, 960, 1120, 960, 14); // 2
	CreateStairLine(1183, 960, 1200, 960, 14); // 3

	CreateJumpLine(1127, 991, 1176, 991, 14); // 0
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
		if (player->GetBAutoMoving() == false // 플레이어가 자동으로 움직이고 있으면 선 충돌 검사 안 하기
			&& hallLines[currentRoom][i].open)
		{
			HallLineCollision(hallLines[currentRoom][i], i, hallLines[currentRoom][i].speed, hallLines[currentRoom][i].time);
		}
	}
	// 계단 선 충돌
	for (int i = 0; i < stairLines[currentRoom].size(); i++)
	{
		stairLines[currentRoom][i].line->Update(V, P);
		if (!player->GetBAutoMoving()) // 플레이어가 자동으로 움직이고 있으면 선 충돌 검사 안 하기
		{
			if(currentRoom == 2 || (currentRoom == 9 && i <= 1))
				HallLineCollision(stairLines[currentRoom][i], i, stairLines[currentRoom][i].speed, stairLines[currentRoom][i].time, false);
			else
				HallLineCollision(stairLines[currentRoom][i], i, stairLines[currentRoom][i].speed, stairLines[currentRoom][i].time, true);
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
		if (player->GetDirection() == 1)
			blackout->RotationDegree(0, 0, -90);
		else if (player->GetDirection() == 2)
			blackout->RotationDegree(0, 0, 90);
		else if (player->GetDirection() == 3)
			blackout->RotationDegree(0, 0, 0);
		else if (player->GetDirection() == 4)
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
		if (!player->GetBBase() && player->GetBMove() && !player->GetBLifting() && !player->GetBAutoMoving()
			&& RoomLineCollision(jumpLines[currentRoom][i], i, player, true) == player->GetDirection())
		{
			player->Jump();
		}
	}
	// 점프 end

	/// <summary>
	/// currentRoom(현재 있는 방) 설정
	/// </summary>
	// Caution: hallLines / roomLines 건드리면 segment fault
	for (int i = 0; roomLines[i].size() >= 4 && i <= roomLines->size(); i++)
	{
		float top = roomLines[i][3].line->FirstVertexPos().y;
		float bottom = roomLines[i][0].line->FirstVertexPos().y;
		float left = roomLines[i][1].line->FirstVertexPos().x;
		float right = roomLines[i][2].line->FirstVertexPos().x;
		// 0: bottom, 1: left, 2: right, 3: top
		if (bottom < player->BottomPosition().y
			&& player->TopPosition().y < top
			&& left < player->LeftPosition().x
			&& player->RightPosition().x < right)
		{
			currentRoom = i;
		}
	}
	// currentRoom end

	/// <summary>
	/// 카메라 움직임 설정
	/// </summary>
	// 카메라 움직임을 제어하기 위해 방의 경계를 기준으로 두기
	float top = roomLines[currentRoom][3].line->FirstVertexPos().y;
	float bottom = roomLines[currentRoom][0].line->FirstVertexPos().y;
	float left = roomLines[currentRoom][1].line->FirstVertexPos().x;
	float right = roomLines[currentRoom][2].line->FirstVertexPos().x;
	D3DXVECTOR2 PO = player->Position();
	if (player->Position().y - bottom <= 120)
		player->NearBorder(true, "bottom");
	else
		player->NearBorder(false, "bottom");

	if (top - player->Position().y <= 120)
		player->NearBorder(true, "top");
	else
		player->NearBorder(false, "top");

	if (player->Position().x - left <= 120)
		player->NearBorder(true, "left");
	else
		player->NearBorder(false, "left");

	if (right - player->Position().x <= 120)
		player->NearBorder(true, "right");
	else
		player->NearBorder(false, "right");
	// 카메라 end

	/// <summary>
	/// 문(hall) 열리는 시기 결정
	/// </summary>
	// room 1
	if (Sprite::Obb(player->GetSprite(), buttons[0][0]))
	{
		hallLines[0][1].open = true;
		doors[0][1]->Open(true); // 문 열림
		doors[1][1]->Open(true);
	}
	if (currentRoom == 1)
	{
		for (int i = 0, cnt = 0; i < enemies[1].size(); i++)
		{
			if (enemies[1][i]->IsDead())
				cnt++;
			if (cnt == enemies[1].size())
			{
				doors[1][1]->Open(true);
				hallLines[1][1].open = true;
			}
			else if (i == enemies[1].size() - 1)
			{
				doors[1][1]->Open(false); // 해당 방 몬스터 다 못 죽였으면 문 안 열림 
				hallLines[1][1].open = false;
			}
		}
	}
	if (!player->GetBAttacking() && Sprite::Obb(player->GetSprite(), buttons[1][0]))
	{
		hallLines[1][3].open = true;
		doors[1][3]->Open(true); // 문 열림
	}
	// room 2
	if (player->GetItem("key") > 0)
	{
		if (!doors[2][1]->GetBOpen() && HallLineCollision(hallLines[2][1], 1, hallLines[2][1].speed, hallLines[2][1].time) == 0)
		{
			doors[2][1]->Open(true);
			doors[8][0]->Open(true);
		}
		hallLines[2][1].open = true;
		hallLines[8][0].open = true;
	}
	// room 3
	if (player->GetItem("key") > 0)
	{
		if (!doors[3][2]->GetBOpen() && HallLineCollision(hallLines[3][2], 2, hallLines[3][2].speed, hallLines[3][2].time) == 0)
		{
			doors[4][0]->Open(true);
			doors[3][2]->Open(true);
		}
		hallLines[4][0].open = true;
		hallLines[3][2].open = true;
	}
	// room 4
	if (currentRoom != 4) // 방으로 들어가기 전까진 방문 열려있음
	{
		hallLines[4][1].open = true;
		hallLines[4][2].open = true;
		doors[4][1]->Open(true);
		doors[4][2]->Open(true);
	}
	if (Sprite::Obb(player->GetSprite(), buttons[4][0]))
	{
		hallLines[4][1].open = true;
		hallLines[4][2].open = true;
		doors[4][1]->Open(true);
		doors[4][2]->Open(true);
		flag = 1;
	}
	else if (currentRoom == 4 && flag == 0)
	{
		hallLines[4][1].open = false;
		hallLines[4][2].open = false;
		doors[4][1]->Open(false);
		doors[4][2]->Open(false);
		flag = 0;
	}
	if (player->GetItem("key") > 0)
	{
		if (!doors[4][0]->GetBOpen() && HallLineCollision(hallLines[4][0], 0, hallLines[4][0].speed, hallLines[4][0].time) == 0)
		{
			doors[4][0]->Open(true);
			doors[3][2]->Open(true);
		}
		hallLines[4][0].open = true;
		hallLines[3][2].open = true;
	}
	// room 6
	if (currentRoom != 6) // 다른 방에서 넘어올 때는 문이 열려있음
	{
		doors[6][0]->Open(true);
		doors[6][1]->Open(true);
	}
	for (int i = 0, cnt = 0; i < enemies[6].size(); i++)
	{
		if (enemies[6][i]->IsDead())
			cnt++;
		if (cnt == enemies[6].size())
		{
			doors[6][0]->Open(true);
			hallLines[6][0].open = true;
			doors[6][1]->Open(true);
			hallLines[6][1].open = true;
		}
		else if (i == enemies[1].size() - 1 && currentRoom == 6)
		{
			doors[6][0]->Open(false); // 해당 방 몬스터 다 못 죽였으면 문 안 열림 
			hallLines[6][0].open = false;
			doors[6][1]->Open(false);
			hallLines[6][1].open = false;
		}
	}
	// room 8
	if (player->GetItem("key") > 0)
	{
		if (!doors[8][0]->GetBOpen() && HallLineCollision(hallLines[8][0], 0, hallLines[8][0].speed, hallLines[8][0].time) == 0)
		{
			doors[2][1]->Open(true);
			doors[8][0]->Open(true);
		}
		hallLines[2][1].open = true;
		hallLines[8][0].open = true;
	}
	// room 9
	if (Sprite::Obb(player->GetSprite(), buttons[9][0]))
	{
		hallLines[9][1].open = true;
		doors[9][1]->Open(true); // 문 열림
	}
	if (Sprite::Obb(player->GetSprite(), buttons[9][1]))
	{
		hallLines[9][2].open = true;
		doors[9][2]->Open(true); // 문 열림
	}
	if (player->GetItem("boss key") > 0)
	{
		if (!doors[9][5]->GetBOpen() && HallLineCollision(hallLines[9][5], 1, hallLines[9][5].speed, hallLines[9][5].time) == 0)
		{
			doors[9][5]->Open(true);
			doors[13][0]->Open(true);
		}
		hallLines[9][5].open = true;
		hallLines[13][0].open = true;
	}
	// room 12
	if (Sprite::Obb(player->GetSprite(), buttons[12][0]))
	{
		hallLines[12][0].open = true;
		doors[12][0]->Open(true);
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
	// 현재 방
	for (int i = 0; i < objects[currentRoom].size(); i++)
	{
		objects[currentRoom][i]->Update(V, P);
		ObjectCollision(objects[currentRoom][i], i);

	}
	for (Sprite* button : buttons[currentRoom])
		button->Update(V, P);
	for (Enemy* enemy : enemies[currentRoom])
		enemy->Update(V, P);
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < doors[i].size(); j++)
			doors[i][j]->Update(V, P); // 한 번 열린 문은 항상 열려있음을 보여주기 위해

	if (bBlackout)
		blackout->Update(V, P);
	// 방마다 다른 오브젝트 Update end
}

void EasternPalace::Render()
{
	eastern_palace->Render();
	base_floor->Render();

	/// <summary>
	/// 방마다 다른 오브젝트 Render
	/// </summary>
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

	for (Sprite* button : buttons[currentRoom])
		button->Render();
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < doors[i].size(); j++)
			doors[i][j]->Render();
	for (Object* obj : objects[currentRoom])
		if (obj->GetBBase() == true) // 지하에 존재하는 오브젝트
			obj->Render();
	for (Enemy* enemy : enemies[currentRoom])
		if (enemy->GetBBase() == true) // 지하에 존재하는 몬스터
			enemy->Render();
	// 방마다 다른 오브젝트 Render end

	/// <summary>
	/// player 위치에 따라 지형 렌더링 순서 정하기
	/// </summary>
	if (!player->GetBBase()) //계단 내려가기 전
	{
		first_floor->Render();
		for (Object* obj : objects[currentRoom])
			if (obj->GetBBase() == false) // 1층에 존재하는 오브젝트
				obj->Render();
		for (Enemy* enemy : enemies[currentRoom])
			if (enemy->GetBBase() == false) // 1층에 존재하는 몬스터
				enemy->Render();
		player->Render();
	}
	if (player->GetBBase()) //계단 내려가서 밑층에 위치할 때 (임시로 false 설정)
	{
		player->Render();
		first_floor->Render();
		for (Object* obj : objects[currentRoom])
			if (obj->GetBBase() == false) // 1층에 존재하는 오브젝트
				obj->Render();
		for (Enemy* enemy : enemies[currentRoom])
			if (enemy->GetBBase() == false) // 1층에 존재하는 몬스터
				enemy->Render();
	}
	hall->Render();
	// player 위치에 따른 지형 렌더링 end

	if (bBlackout)
		blackout->Render();
	// 지형 렌더링 end

	//ImGui::SliderFloat("Enemies Move Speed", &enemyMoveSpeed, 50, 400);
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

void EasternPalace::CreateVase(string type, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary, bool base)
{
	Vase* vase;
	vase = new Vase(type, scale, base);
	vase->Scale(scale);
	vase->DrawBound(boundary);
	vase->Position((position.x - 1023) * 2.5 + Width / 2, (2811 - position.y) * 2.5 + Height / 2);
	objects[room].push_back(vase);
}

void EasternPalace::CreateChest(string size, string item, D3DXVECTOR2 scale, D3DXVECTOR2 position, int room, bool boundary, bool base)
{
	Chest* chest;
	chest = new Chest(size, item, scale, base);
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
	Door* door = new Door(scale, position, open, direction);
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

void EasternPalace::CreateHallLine(int x1, int y1, int x2, int y2, int room, bool open, float time, float speed)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	hallLines[room].push_back({ line, D3DXVECTOR2(0, 0), open, time, speed });
}

void EasternPalace::CreateJumpLine(int x1, int y1, int x2, int y2, int room)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	D3DXVECTOR2* intersection = new D3DXVECTOR2(0, 0);
	jumpLines[room].push_back({ line, intersection });
}

void EasternPalace::CreateStairLine(int x1, int y1, int x2, int y2, int room, float time, float speed)
{
	D3DXVECTOR2 position1 = D3DXVECTOR2((x1 - 1023) * 2.5 + Width / 2, (2811 - y1) * 2.5 + Height / 2);
	D3DXVECTOR2 position2 = D3DXVECTOR2((x2 - 1023) * 2.5 + Width / 2, (2811 - y2) * 2.5 + Height / 2);
	Line* line = new Line(position1, position2);
	stairLines[room].push_back({ line, D3DXVECTOR2(0, 0), true, time, speed });
}

template<typename T>
int EasternPalace::RoomLineCollision(RoomLine line, int lineIndex, T object, bool jumpLine)
{
	string type;
	if (jumpLine)
		type = "jump";
	else
		type = "room";
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. 플레이어 위 선분
	if (line.line->SegmentIntersection(object->Position(), object->TopPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "top", type);
		return 4;
	}

	else if (object->GetTopBLineCollisionIndex(type) == lineIndex && // 서로 평행한 선분 2개 위치할 경우 인덱스가 작은 선과 충돌했는데 인덱스가 큰 선과는 충돌하지 않으므로 최종적으로 플레이어가 선 충돌하지 않았다고 판별하는 거... 방지
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->BottomPosition(), object->TopPosition())))
	{
		object->LineCollision(false, lineIndex, "top", type);
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 플레이어 아래
	if (line.line->SegmentIntersection(object->Position(), object->BottomPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "bottom", type);
		return 3;
	}

	else if (object->GetBottomBLineCollisionIndex(type) == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->TopPosition(), object->BottomPosition())))
	{
		object->LineCollision(false, lineIndex, "bottom", type);
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 플레이어 왼쪽
	if (line.line->SegmentIntersection(object->Position(), object->LeftPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "left", type);
		return 1;
	}

	else if (object->GetLeftBLineCollisionIndex(type) == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->RightPosition(), object->LeftPosition())))
	{
		object->LineCollision(false, lineIndex, "left", type);
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. 플레이어 오른쪽
	if (line.line->SegmentIntersection(object->Position(), object->RightPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), *line.intersection))
	{
		object->LineCollision(true, lineIndex, "right", type);
		return 2;
	}

	else if (object->GetRightBLineCollisionIndex(type) == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(*line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(*line.intersection, object->LeftPosition(), object->RightPosition())))
	{
		object->LineCollision(false, lineIndex, "right", type);
		return 0;
	}
}

int EasternPalace::HallLineCollision(HallLine line, int lineIndex, float speed, float time, bool stair)
{
	int collision = 0;

	if (player->GetBAttacked())
		return 0;

	string type;
	if (stair)
		type = "stair";
	else
		type = "hall";
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. 플레이어 위 선분
	if (line.line->SegmentIntersection(player->Position(), player->TopPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (player->GetDirection() == 4 && line.open)
		{
			player->LineCollision(false, lineIndex, "top", type); // 이동해야 하는 선이므로 false
			player->AutoMoving("top", speed, time, stair);
			collision = 4;
		}
		else
		{
			player->LineCollision(true, lineIndex, "top", type);
			collision = 0;
		}
	}

	else if (player->GetTopBLineCollisionIndex(type) == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->TopPosition(), player->BottomPosition())))
	{
		player->LineCollision(false, lineIndex, "top", type);
		collision = -1;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 플레이어 아래 선분
	if (line.line->SegmentIntersection(player->Position(), player->BottomPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (player->GetDirection() == 3 && line.open)
		{
			player->LineCollision(false, lineIndex, "bottom", type);
			player->AutoMoving("bottom", speed, time, stair);
			collision = 3;
		}
		else
		{
			player->LineCollision(true, lineIndex, "bottom", type);
			collision = 0;
		}
	}

	else if (player->GetBottomBLineCollisionIndex(type) == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->TopPosition(), player->BottomPosition())))
	{
		player->LineCollision(false, lineIndex, "bottom", type);
		collision = -1;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 플레이어 왼쪽
	if (line.line->SegmentIntersection(player->Position(), player->LeftPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (player->GetDirection() == 1 && line.open)
		{
			player->LineCollision(false, lineIndex, "left", type);
			player->AutoMoving("left", speed, time, stair);
			collision = 1;
		}
		else
		{
			player->LineCollision(true, lineIndex, "left", type);
			collision = 0;
		}
	}

	else if (player->GetLeftBLineCollisionIndex(type) == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->RightPosition(), player->LeftPosition())))
	{
		player->LineCollision(false, lineIndex, "left", type);
		collision = -1;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. 플레이어 오른쪽
	if (line.line->SegmentIntersection(player->Position(), player->RightPosition(), line.line->FirstVertexPos(), line.line->SecondVertexPos(), line.intersection))
	{
		if (player->GetDirection() == 2 && line.open)
		{
			player->LineCollision(false, lineIndex, "right", type);
			player->AutoMoving("right", speed, time, stair);
			collision = 2;
		}
		else
		{
			player->LineCollision(true, lineIndex, "right", type);
			collision = 0;
		}
	}

	else if (player->GetRightBLineCollisionIndex(type) == lineIndex &&
		// 교차점이 선분 위에 존재하지 않음
		(!line.line->InBoundingRectangle(line.intersection, line.line->FirstVertexPos(), line.line->SecondVertexPos()) ||
			// 교차점이 플레이어 위에 존재하지 않음
			!line.line->InBoundingRectangle(line.intersection, player->LeftPosition(), player->RightPosition())))
	{
		player->LineCollision(false, lineIndex, "right", type);
		collision = -1;
	}
	
	if (collision > 0)
	{
		player->LineCollision(false, -1, "top", "room");
		player->LineCollision(false, -1, "bottom", "room");
		player->LineCollision(false, -1, "left", "room");
		player->LineCollision(false, -1, "right", "room");
	}

	return collision;
}

int EasternPalace::ObjectCollision(Object* obj, int objIndex)
{
	int collision = 0;

	if (player->GetTopBLineCollisionIndex("object") == objIndex || player->GetBottomBLineCollisionIndex("object") == objIndex
		|| player->GetRightBLineCollisionIndex("object") == objIndex || player->GetLeftBLineCollisionIndex("object") == objIndex)
		if (!obj->Exist() || !Sprite::Obb(obj->GetSprite(), player->GetSprite()))
		{
			player->LineCollision(false, objIndex, "top", "object");
			player->LineCollision(false, objIndex, "bottom", "object");
			player->LineCollision(false, objIndex, "right", "object");
			player->LineCollision(false, objIndex, "left", "object");
			return 0;
		} // object가 없을 때 선 충돌 x

	// top
	if (obj->BottomPosition().y <= player->TopPosition().y && obj->BottomPosition().y > player->BottomPosition().y
		&& obj->LeftPosition().x < player->Position().x && player->Position().x < obj->RightPosition().x)
	{
		player->LineCollision(true, objIndex, "top", "object");
		collision = 4;
	}
	else if(player->GetTopBLineCollisionIndex("object") == objIndex && obj->BottomPosition().y >= player->TopPosition().y)
	{
		player->LineCollision(false, objIndex, "top", "object");
	}

	// bottom
	if (obj->TopPosition().y >= player->BottomPosition().y && obj->BottomPosition().y < player->BottomPosition().y
		&& obj->LeftPosition().x < player->Position().x && player->Position().x < obj->RightPosition().x)
	{
		player->LineCollision(true, objIndex, "bottom", "object");
		collision = 3;
	}
	else if (player->GetBottomBLineCollisionIndex("object") == objIndex && obj->TopPosition().y <= player->BottomPosition().y)
	{
		player->LineCollision(false, objIndex, "bottom", "object");
	}

	// right
	if (obj->LeftPosition().x <= player->RightPosition().x && obj->RightPosition().x > player->RightPosition().x
		&& obj->BottomPosition().y < player->Position().y && player->BottomPosition().y < obj->TopPosition().y)
	{
		player->LineCollision(true, objIndex, "right", "object");
		collision = 2;
	}
	else if (player->GetRightBLineCollisionIndex("object") == objIndex && obj->LeftPosition().x >= player->RightPosition().x)
	{
		player->LineCollision(false, objIndex, "right", "object");
	}

	// left
	if (obj->RightPosition().x >= player->LeftPosition().x && obj->RightPosition().x < player->RightPosition().x
		&& obj->BottomPosition().y < player->Position().y && player->BottomPosition().y < obj->TopPosition().y)
	{
		player->LineCollision(true, objIndex, "left", "object");
		collision = 1;
	}
	else if (player->GetLeftBLineCollisionIndex("object") == objIndex && obj->RightPosition().x <= player->LeftPosition().x)
	{
		player->LineCollision(false, objIndex, "left", "object");
	}

	return collision;
}
