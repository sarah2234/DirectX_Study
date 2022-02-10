// This file is responsible for encapsulating the geometry of 3D objects.
#pragma once
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

class TriangleModel
{
private:
	struct VertexType
	{
		XMFLOAT3 position; // 3D vector consiting of three single-precision floating-pointing values
		XMFLOAT4 color; // 4D vector consiting of four single-precision floating-pointing values
	};

public:
	TriangleModel();
	TriangleModel(const TriangleModel&);
	~TriangleModel();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	// Two integers are used for tracking the size of each buffer.
	int m_vertexCount, m_indexCount;
};