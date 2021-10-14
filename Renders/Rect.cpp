#include "stdafx.h"
#include "Rect.h"

Rect::Rect(wstring shaderFile)
	:position(0,0),scale(1,1), color(1,1,1,1)
{
	CreateBuffer(shaderFile);

	UpdateWorld();
	Color(color);
}

Rect::Rect(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color)
	:position(position), scale(scale), color(color)
{
	CreateBuffer(shaderFile);

	UpdateWorld();
	Color(color);
}

Rect::~Rect()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);
}

void Rect::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
}

void Rect::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->Draw(0, 0, 6);
}

void Rect::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Rect::Position(D3DXVECTOR2 & vec)
{
	position = vec;

	UpdateWorld();
}

void Rect::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Rect::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;

	UpdateWorld();
}

void Rect::Color(float r, float g, float b)
{
	Color(D3DXCOLOR(r, g, b, 1));
}

void Rect::Color(D3DXCOLOR & vec)
{
	color = vec;

	shader->AsVector("Color")->SetFloatVector(color);
}

void Rect::CreateBuffer(wstring shaderFile)
{
	shader = new Shader(shaderFile);

	Vertex vertices[6];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);

		assert(SUCCEEDED(hr));
	}

}

void Rect::UpdateWorld()
{
	D3DXMATRIX W, S, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);

	W = S * T;

	shader->AsMatrix("World")->SetMatrix(W);
}
