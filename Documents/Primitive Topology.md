Direct3D 응용 프로그램에서는 3차원 물체를 triangle mesh로 근사(approximation)해서 표현한다. 즉, 물체의 기본적인 구축 요소는 삼각형이다. (이외에 점이나 선도 물체를 근사하는 데 사용한다.)

### Primitive Topology를 정의한 열거형

```
typedef enum D3D11_PRIMITIVE_TOPOLOGY
{
    D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
    D3D11_PRIMITIVE_TOPOLOGY_POINTLIST = 1,
    D3D11_PRIMITIVE_TOPOLOGY_LINELIST = 2, // OpenGL에서 GL_LINES
    D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP = 3, // GL_LINE_STRIP
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4, // GL_TRIANGLES
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5, // GL_TRIANGLES_STRIP
    D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
    D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
    D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = 33,
    D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = 34,
    .
    .
    .
    D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = 64,
} D3D11_PRIMITIVE_TOPOLOGY;
```
<!--OpenGL의 GL Library에서 사용할 수 있는 Geometry Primitives랑 유사-->

### 예제 코드
```
ID3D11DeviceContext* deviceContext;
.
.
.
// D3D11CreateDevice 또는 D3D11CreateDeviceAndSwapChain으로 디바이스 생성 후
deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
```
***
### 인접성 정보를 가진 기본도형
![Adjacent Primitives](https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d10-gs.png)   
_(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ와 D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ의 모습)_      
인접성(adjacency) 정보를 가진 삼각형 목록에서는 각 삼각형마다 인접 삼각형이라고 부르는 이웃한 삼각형 세 개를 포함시킬 수 있다.
***
### Control Point Patch List
D3D11_PRIMITIVE_TOPOLOGY_*N*_CONTROL_POINT_PATCHLIST: N개의 control point로 이루어진 패치 목록으로 해석해야 한다. Control point들은 Tessellation 단계에서 쓰인다. (제 13장)
***
### Using Vertex Indices
3차원 물체의 기본 구축 요소는 삼각형이므로 사각형 하나와 팔각형 하나를 삼각형을 이용해서 만들 수 있다.
```
Vertex quad[6] = {
    v0, v1, v2, // 삼각형 0
    v0, v2, v3, // 삼각형 1
};

Vertex octagon[24] = {
    v0, v1, v2, // 삼각형 0
    v0, v2, v3, // 삼각형 1
    v0, v3, v4, // 삼각형 2
    v0, v4, v5, // 삼각형 3
    v0, v5, v6, // 삼각형 4
    v0, v6, v7, // 삼각형 5
    v0, v7, v8, // 삼각형 6
    v0, v8, v1 // 삼각형 7
};
```
이렇게 만들 시 정점들이 중복되는데, 메모리 요구량과 그래픽 하드웨어의 처리량이 증가한다는 점에서 이는 바람직하지 않다. 따라서 index를 사용하여 어떤 정점들을 어떤 순서로 사용해서 삼각형을 형성할지 지정한다.   
index를 사용하여 사각형을 다음과 같이 그릴 수 있다.
```
Vertex quad[4] = {v0, v1, v2, v3};
UINT indexList[6] = {0, 1, 2, // 삼각형 0
                     0, 2, 3}; // 삼각형 1
```
(index의 중복이 생겼지만 index는 정수이므로 Vertex 구조체보다 적은 양의 메모리를 차지하고, 정점 캐시 순서가 좋은 경우 그래픽 하드웨어는 중복된 정점들을 너무 자주 처리하지 않아도 된다.)
<!--OpenGL에서 glDrawElements와 동일한 기능-->