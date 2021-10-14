#include "stdafx.h"
#include "Fire.h"

Fire::Fire(wstring shaderFile, D3DXVECTOR2 start)
    :scale(1.5f, 1.5f), rotation(0, 0, 0)
{
    clip = new Clip(PlayMode::Loop);

    for (UINT y = 0; y < 3; y++)
    {
        for (UINT x = 0; x < 5; x++)
        {
            float startX = (float)x * 43;
            float startY = (float)y * 67;

            float endX = (float)(x + 1) * 43;
            float endY = (float)(y + 1) * 67;

            clip->AddFrame(new Sprite(Textures + L"Fire.png", shaderFile, startX, startY, endX, endY), 0.3f);
        }
    }

    position = start;

    clip->Position(position);
    clip->Scale(scale);
    clip->RotationDegree(rotation);
    clip->Play();
    clip->DrawBound(true);
}

Fire::~Fire()
{
    SAFE_DELETE(clip);
}

void Fire::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
    clip->Update(V, P);
}

void Fire::Render()
{
    ImGui::Separator();

    ImGui::SliderFloat2("Fire Scale", (float*)&scale, 1, 5);
    ImGui::SliderFloat3("Fire Rotation", (float*)&rotation, -90, 90);

    clip->Scale(scale);
    clip->RotationDegree(rotation);

    clip->Render();
}