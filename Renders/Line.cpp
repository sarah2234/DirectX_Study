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
	radian = (float)atanf(radian); //라디안 단위

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
{//07_Texture 참고
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

	shader->Draw(0, bLineCollision ? 1 : 0, 2); //vertices 수
}

void Line::Swap(D3DXVECTOR2& a, D3DXVECTOR2& b)
{
	D3DXVECTOR2 temp;
	temp = a;
	a = b;
	b = temp;
}

//https://bowbowbow.tistory.com/17
double Line::Cross(const D3DXVECTOR2& first, const D3DXVECTOR2& second) //외적
{
	return first.x * second.y - first.y * second.x;
}

bool Line::LineIntersection(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection)
{
	//점 first_a와 점 second_a를 지나는 직선 & 점 first_b와 점 second_b를 지나는 직선
	double external = Cross(D3DXVECTOR2(second_a - first_a), D3DXVECTOR2(second_b - first_b)); //벡터 a, 벡터 b
	if (fabs(external) < EPSILON) //평행
		return false;

	//첫 번째 직선에 외적 값 대입
	intersection.x = first_a.x + (second_a.x - first_a.x) * (Cross((first_b - first_a), (second_b - first_b)) / external);
	intersection.y = first_a.y + (second_a.y - first_a.y) * (Cross((first_b - first_a), (second_b - first_b)) / external);

	return true;
}

double Line::Ccw(D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
	//평행인 직선을 기준으로 시계/반시계 결정
	return Cross(a, b);
}

double Line::Ccw(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	//점 p 기준
	return Cross(a - p, b - p);
}

bool Line::ParallelSegment(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection)
{
	//점 first_a와 점 second_a를 지나는 직선 a와, 점 first_b와 점 second_b를 지나는 직선 b가 서로 평행할 때, 교점이 존재하는지 확인
	if (second_a.x < first_a.x && second_a.y < first_a.y)
		Swap(first_a, second_a);
	if (second_b.x < first_b.x && second_b.y < first_b.y)
		Swap(first_b, second_b);

	if (Ccw(first_a, second_a, first_b) != 0  //평행하지 않음
		|| (second_a.x < first_b.x && second_a.y < first_b.y) //직선 a가 직선 b의 아래에 있고 서로 교차하지 않을 때
		|| (second_b.x < first_a.x && second_b.y < first_a.y)) //직선 b가 직선 a의 아래에 있고 서로 교차하지 않을 때
		return false;

	if (first_a.x < first_b.x && first_a.y < first_b.y)
		intersection = first_b;
	else
		intersection = first_a;
	return true;
}

bool Line::InBoundingRectangle(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	// p가 두 점 a, b를 감싸면서 각 변이 x, y축에 평행한 최소사각형 내부에 있는지 확인한다.
	// a, b, p는 일직선 상에 있다고 가정한다.
	float x1 = a.x < b.x ? a.x : b.x;
	float x2 = a.x < b.x ? b.x : a.x;
	float y1 = a.y < b.y ? a.y : b.y;
	float y2 = a.y < b.y ? b.y : a.y;

	return (x1 <= p.x && p.x <= x2) && (y1 <= p.y && p.y <= y2);
}

bool Line::SegmentIntersection(D3DXVECTOR2 first_a, D3DXVECTOR2 second_a, D3DXVECTOR2 first_b, D3DXVECTOR2 second_b, D3DXVECTOR2& intersection)
{//LineIntersection 함수와 달리 평행할 때도 고려해서 boolean 반환
	if (!LineIntersection(first_a, second_a, first_b, second_b, intersection)) //평행할 때
		return ParallelSegment(first_a, second_a, first_b, second_b, intersection);

	//intersection이 두 선분에 포함되어 있는 경우 참
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
	radian = (float)atanf(radian); //라디안 단위

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
