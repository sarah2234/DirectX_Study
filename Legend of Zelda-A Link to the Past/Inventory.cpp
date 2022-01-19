#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory(D3DXVECTOR2 scale)
	:on(false)
{
	wstring spriteFile = Textures + L"Legend of Zelda/Items.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	inventory = new Sprite(spriteFile, shaderFile, 21, 450, 260, 601);
	inventory->Scale(0, 0);

	bossKey = new Sprite(spriteFile, shaderFile, 229, 192, 243, 208);
	bossKey->Scale(0, 0);
	map = new Sprite(spriteFile, shaderFile, 180, 192, 196, 208);
	map->Scale(0, 0);
	compass = new Sprite(spriteFile, shaderFile, 205, 193, 219, 208);
	compass->Scale(0, 0);

	this->scale = scale;
	this->position = D3DXVECTOR2(0, 0);
}

Inventory::~Inventory()
{
	SAFE_DELETE(inventory);
	SAFE_DELETE(bossKey);
	SAFE_DELETE(map);
	SAFE_DELETE(compass);
}

void Inventory::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	if (on == true)
	{
		inventory->Scale(scale);
		inventory->Position(position);
		position = D3DXVECTOR2(player->Position().x, player->Position().y);

		if (player->GetItem("map") == 1)
		{
			map->Scale(scale);
			map->Position(inventory->Position().x + 120, inventory->Position().y - 150);
		}
		if (player->GetItem("compass") == 1)
		{
			player->Scale(10, 10);
			compass->Scale(scale);
			compass->Position(inventory->Position().x + 180, inventory->Position().y - 150);
		}
		if (player->GetItem("boss key") == 1)
		{
			bossKey->Scale(scale);
			bossKey->Position(inventory->Position().x + 240, inventory->Position().y - 150);
		}		
	}
	else
	{
		inventory->Scale(0, 0);
		bossKey->Scale(0, 0);
		map->Scale(0, 0);
		compass->Scale(0, 0);
	}
	inventory->Update(V, P);
	bossKey->Update(V, P);
	map->Update(V, P);
	compass->Update(V, P);
}

void Inventory::Render()
{
	inventory->Render();
	bossKey->Render();
	map->Render();
	compass->Render();

	if (ImGui::MenuItem("Open the inventory", NULL, false, true))
	{
		on =true;
	}
	if (ImGui::MenuItem("Close the inventory", NULL, false))
	{
		on = false;
	}

	ImGui::Text("stamina: %d", player->GetItem("stamina"));
	ImGui::Text("rupee: %d", player->GetItem("rupee"));
	ImGui::Text("key: %d", player->GetItem("key"));
	ImGui::Text("compass: %d", player->GetItem("compass"));
}

void Inventory::On(bool b)
{
	on = b;
}
