#pragma once

class Sprite
{
public:
	Sprite(wstring textureFile, wstring shaderFile);
	Sprite(wstring textureFile, wstring shaderFile, float endX, float endY);
	Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	virtual ~Sprite();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);

	void Render();

	void DrawBound(bool val) { bDrawBound = val; }
	void DrawCollision(bool val) { bDrawCollision = val; }

public:
	bool Aabb(D3DXVECTOR2& position);
	bool Aabb(Sprite* b);

	bool Obb(Sprite* b);

	static bool Aabb(Sprite* a, D3DXVECTOR2& position);
	static bool Aabb(Sprite* a, Sprite* b);
	static bool Obb(Sprite* a, Sprite* b);

private:
	struct ObbDesc
	{
		D3DXVECTOR2 Position;
		D3DXVECTOR2 Direction[2];
		float Length[2];
	};

	static void CreateObb(OUT ObbDesc* out, D3DXVECTOR2& position, D3DXMATRIX& world, D3DXVECTOR2& length);
	static float SeperateAxis(D3DXVECTOR2& seperate, D3DXVECTOR2& e1, D3DXVECTOR2& e2);
	static bool CheckObb(ObbDesc& obbA, ObbDesc& obbB);


private:
	void CreateBound();

public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 RotationDegree();

	D3DXVECTOR2 TextureSize() { return textureSize; }

private:
	void Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY);

private:
	bool bDrawBound;
	bool bDrawCollision;
	wstring textureFile;

	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	Shader* boundShader;
	ID3D11Buffer* boundVertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 textureSize;

	D3DXMATRIX world;

	ID3D11ShaderResourceView* srv;

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};
	struct BoundVertex
	{
		D3DXVECTOR3 Position;
	};
};

///////////////////////////////////////////////////////////////////////////////

class Sprites
{
private:
	friend class Sprite;

private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);

private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = NULL;
	};

	static map<wstring, SpriteDesc> spriteMap;
};
