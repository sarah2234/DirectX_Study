#pragma once
#define EPSILON 0.0001

struct Vertex
{
	D3DXVECTOR3 Position; //position of a vertex
};

class Line
{
public:
	Line(D3DXVECTOR2 firstPos, D3DXVECTOR2 secondPos);
	~Line();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	float Radian() { return radian; }
	bool GetBLineCollision() { return bLineCollision; }
	bool SegmentIntersection(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection);

	D3DXVECTOR2 FirstVertexPos() { return firstPos; }
	D3DXVECTOR2 SecondVertexPos() { return secondPos; }

	bool LineIntersection(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection);
	bool ParallelSegment(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection);
	bool InBoundingRectangle(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b);
	//���� ���� �Լ� �߰�

	void Position(D3DXVECTOR2 firstPos, D3DXVECTOR2 secondPos);
private:
	Vertex vertices[2];
	ID3D11Buffer* vertexBuffer;
	Shader* shader;
	D3DXMATRIX world;
	D3DXVECTOR2 firstPos;
	D3DXVECTOR2 secondPos;

	void Swap(D3DXVECTOR2& a, D3DXVECTOR2& b);
	double Cross(const D3DXVECTOR2& first, const D3DXVECTOR2& second); //����
	double Ccw(D3DXVECTOR2 a, D3DXVECTOR2 b); //�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
	double Ccw(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b);

	float radian;
	bool bLineCollision;
};