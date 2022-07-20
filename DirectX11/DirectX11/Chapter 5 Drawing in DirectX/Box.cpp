#include "Box.h"

Box::Box(HINSTANCE hInstance)
	:D3DApp(hInstance), mVertexBuffer(0), mIndexBuffer(0),
	mTheta(1.5f * MathHelper::Pi), mPhi(0.25f * MathHelper::Pi), mRadius(5.0f)
{
	mMainWndCaption = L"3D Box";

	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);
}

Box::~Box()
{
	ReleaseCOM(mVertexBuffer);
	ReleaseCOM(mIndexBuffer);
}

bool Box::Init()
{
	if (!D3DApp::Init())
		return false;

	bool result = InitializeBuffers();
	if (!result)
	{
		ErrorLogger::Log(E_FAIL, "Cannot initialize buffers");
		return false;
	}
	
	return true;
}

void Box::OnResize()
{
	D3DApp::OnResize();

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}

void Box::UpdateScene(float dt)
{
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius * sinf(mPhi) * cosf(mTheta);
	float z = mRadius * sinf(mPhi) * sinf(mTheta);
	float y = mRadius * cosf(mPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, V);
}

void Box::DrawScene()
{
}

int Box::GetIndexCount()
{
	return 0;
}

void Box::OnMouseDown(WPARAM btnState, int x, int y)
{
}

void Box::OnMouseUp(WPARAM btnState, int x, int y)
{
}

void Box::OnMouseMove(WPARAM btnState, int x, int y)
{
}

bool Box::InitializeBuffers()
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array
	mVertexCount = 8;
	// Set the number of indices in the index array
	mIndexCount = 8;
	// Create the vertex array
	vertices = new VertexType[mVertexCount];
	if (!vertices)
	{
		ErrorLogger::Log(E_INVALIDARG, "Wrong mVertexCount in Box.cpp");
		return false;
	}
	// Create the index array
	indices = new unsigned long[mIndexCount];
	if (!indices)
	{
		ErrorLogger::Log(E_INVALIDARG, "Wrong mIndexCount in Box.cpp");
		return false;
	}
	

	// Load the vertex array with data
	vertices[0].position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vertices[1].position = D3DXVECTOR3(-1.0f, +1.0f, -1.0f);
	vertices[2].position = D3DXVECTOR3(+1.0f, +1.0f, -1.0f);
	vertices[3].position = D3DXVECTOR3(+1.0f, -1.0f, -1.0f);
	vertices[4].position = D3DXVECTOR3(-1.0f, -1.0f, +1.0f);
	vertices[5].position = D3DXVECTOR3(-1.0f, +1.0f, +1.0f);
	vertices[6].position = D3DXVECTOR3(+1.0f, +1.0f, +1.0f);
	vertices[7].position = D3DXVECTOR3(+1.0f, -1.0f, +1.0f);

	// Set up the descriptio of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = md3dDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);
	if (FAILED(result))
	{
		ErrorLogger::Log(E_FAIL, "Cannot create vertex buffer");
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = md3dDevice->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);
	if (FAILED(result))
	{
		ErrorLogger::Log(E_FAIL, "Cannot create index buffer");
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = NULL;

	delete[] indices;
	indices = NULL;

	return true;
}

void Box::RenderBuffers()
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendere
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered
	md3dImmediateContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
