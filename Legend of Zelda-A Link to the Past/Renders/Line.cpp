#include "stdafx.h"
#include "Line.h"


Line::Line(D3DXVECTOR2 firstPos, D3DXVECTOR2 secondPos)
	:bLineCollision(false)
{
	shader = new Shader(Shaders + L"010_Bounding.fx");

	D3DXMatrixIdentity(&world);

	Vertex vertices[2];

	if (firstPos.x <= secondPos.x)
	{
		vertices[0].Position = D3DXVECTOR3(firstPos.x, firstPos.y, 0.0f);
		vertices[1].Position = D3DXVECTOR3(secondPos.x, secondPos.y, 0.0f);
		radian = (secondPos.y - firstPos.y) / (secondPos.x - firstPos.x);
	}
	else
	{
		vertices[1].Position = D3DXVECTOR3(firstPos.x, firstPos.y, 0.0f);
		vertices[0].Position = D3DXVECTOR3(secondPos.x, secondPos.y, 0.0f);
		radian = (firstPos.y - secondPos.y) / (firstPos.x - secondPos.x);
	}
	radian = (float)atanf(radian); //���� ����

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 2; //number of vertices
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	this->firstPos = firstPos;
	this->secondPos = secondPos;
}

Line::~Line()
{
	vertexBuffer->Release();
	SAFE_DELETE(shader);
}

void Line::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{//07_Texture ����
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
	shader->AsMatrix("World")->SetMatrix(world);
}

void Line::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	shader->Draw(0, bLineCollision ? 1 : 0, 2); //vertices ��
}

void Line::Swap(D3DXVECTOR2& a, D3DXVECTOR2& b)
{
	D3DXVECTOR2 temp;
	temp = a;
	a = b;
	b = temp;
}

//https://bowbowbow.tistory.com/17
double Line::Cross(const D3DXVECTOR2& first, const D3DXVECTOR2& second) //����
{
	return first.x * second.y - first.y * second.x;
}

bool Line::LineIntersection(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection)
{
	//�� first_a�� �� second_a�� ������ ���� & �� first_b�� �� second_b�� ������ ����
	double external = Cross(D3DXVECTOR2(second_a - first_a), D3DXVECTOR2(second_b - first_b)); //���� a, ���� b
	if (fabs(external) < EPSILON) //����
		return false;

	//ù ��° ������ ���� �� ����
	intersection.x = first_a.x + (second_a.x - first_a.x) * (Cross((first_b - first_a), (second_b - first_b)) / external);
	intersection.y = first_a.y + (second_a.y - first_a.y) * (Cross((first_b - first_a), (second_b - first_b)) / external);

	return true;
}

double Line::Ccw(D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
	//������ ������ �������� �ð�/�ݽð� ����
	return Cross(a, b);
}

double Line::Ccw(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	//�� p ����
	return Cross(a - p, b - p);
}

bool Line::ParallelSegment(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection)
{
	//�� first_a�� �� second_a�� ������ ���� a��, �� first_b�� �� second_b�� ������ ���� b�� ���� ������ ��, ������ �����ϴ��� Ȯ��
	if (second_a.x < first_a.x && second_a.y < first_a.y)
		Swap(first_a, second_a);
	if (second_b.x < first_b.x && second_b.y < first_b.y)
		Swap(first_b, second_b);

	if (Ccw(first_a, second_a, first_b) != 0  //�������� ����
		|| (second_a.x < first_b.x && second_a.y < first_b.y) //���� a�� ���� b�� �Ʒ��� �ְ� ���� �������� ���� ��
		|| (second_b.x < first_a.x && second_b.y < first_a.y)) //���� b�� ���� a�� �Ʒ��� �ְ� ���� �������� ���� ��
		return false;

	if (first_a.x < first_b.x && first_a.y < first_b.y)
		intersection = first_b;
	else
		intersection = first_a;
	return true;
}

bool Line::InBoundingRectangle(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	// p�� �� �� a, b�� ���θ鼭 �� ���� x, y�࿡ ������ �ּһ簢�� ���ο� �ִ��� Ȯ���Ѵ�.
	// a, b, p�� ������ �� �ִٰ� �����Ѵ�.
	float x1 = a.x < b.x ? a.x : b.x;
	float x2 = a.x < b.x ? b.x : a.x;
	float y1 = a.y < b.y ? a.y : b.y;
	float y2 = a.y < b.y ? b.y : a.y;

	return (x1 <= p.x && p.x <= x2) && (y1 <= p.y && p.y <= y2);
}

bool Line::SegmentIntersection(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection)
{//LineIntersection �Լ��� �޸� ������ ���� ����ؼ� boolean ��ȯ
	if (!LineIntersection(first_a, second_a, first_b, second_b, intersection)) //������ ��
		return ParallelSegment(first_a, second_a, first_b, second_b, intersection);

	//intersection�� �� ���п� ���ԵǾ� �ִ� ��� ��
	if (InBoundingRectangle(intersection, first_a, second_a) && InBoundingRectangle(intersection, first_b, second_b))
	{
		bLineCollision = true;
		return true;
	}
	else
	{
		bLineCollision = false;
		return false;
	}
}

void Line::Position(D3DXVECTOR2 firstPos, D3DXVECTOR2 secondPos)
{
	if (firstPos.x <= secondPos.x)
	{
		vertices[0].Position = D3DXVECTOR3(firstPos.x, firstPos.y, 0.0f);
		vertices[1].Position = D3DXVECTOR3(secondPos.x, secondPos.y, 0.0f);
		radian = (secondPos.y - firstPos.y) / (secondPos.x - firstPos.x);
	}
	else
	{
		vertices[1].Position = D3DXVECTOR3(firstPos.x, firstPos.y, 0.0f);
		vertices[0].Position = D3DXVECTOR3(secondPos.x, secondPos.y, 0.0f);
		radian = (firstPos.y - secondPos.y) / (firstPos.x - secondPos.x);
	}
	radian = (float)atanf(radian); //���� ����

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 2; //number of vertices
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	this->firstPos = firstPos;
	this->secondPos = secondPos;
}
