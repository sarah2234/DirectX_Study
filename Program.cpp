#include "stdafx.h"
#include "Systems/Device.h"
#include "Scenes/Scene.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"
#include "Scenes/Field.h"
#include "Scenes/EasternPalace.h"
#include "Scenes/GameOver.h"
#include "Inventory.h"

SceneValues* values;
vector<Scene*> scenes;
Player* player;
Inventory* inventory;

void InitScene()
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	Clip* clip;

	player = new Player(D3DXVECTOR2(Width / 2, Height / 2), D3DXVECTOR2(2.5f, 2.5f));

	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);

	scenes.push_back(new GameOver(values, D3DXVECTOR2(65, 3270)));
	scenes.push_back(new EasternPalace(values, D3DXVECTOR2(65, 3270)));

	inventory = new Inventory(D3DXVECTOR2(2.5f, 2.5f));

}

void DestroyScene()
{
	for (Scene* scene : scenes)
		SAFE_DELETE(scene);

	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);
	SAFE_DELETE(player);
	SAFE_DELETE(inventory);
}

void Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	inventory->Update(V, P);

	values->MainCamera->Update();

	//Projection
	D3DXMatrixOrthoOffCenterLH(&values->Projection, 0, (float)Width, 0, (float)Height, -1, 1);

	if (inventory->IsOn() == false)
		for (Scene* scene : scenes)
			scene->Update();

	if (player->GetItem("stamina") > 0 && inventory->IsOn() == false)
		player->Update(V, P);
	else if (player->GetItem("stamina") <= 0)
		scenes[0]->On(true);
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		for (Scene* scene : scenes)
			scene->Render();
		if (scenes[0]->IsOn())
			scenes[0]->Render();

		inventory->Render();
		//player->Render()은 각 scenes 파일들 내에 호출됨
	}
	ImGui::Render();
	

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text = L"";

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 20;

		text = L"Frame Per Second : " + to_wstring((int)ImGui::GetIO().Framerate);
		DirectWrite::RenderText(text, rect);

		rect.top += 20;
		rect.bottom += 20;

		text = L"Camera Position : ";
		text += to_wstring((int)values->MainCamera->Position().x);
		text += L", ";
		text += to_wstring((int)values->MainCamera->Position().y);

		DirectWrite::RenderText(text, rect);
	}

	DirectWrite::GetDC()->EndDraw();

	SwapChain->Present(0, 0);
}