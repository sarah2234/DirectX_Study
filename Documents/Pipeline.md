**Pipeline**
===
https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline   

<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d11-pipeline-stages.jpg"></img></br>

----------------------------------------

**Input Assembler Stage**
---
메모리에서 기하 자료(vertex, index)를 읽어 기본 도형을 생성한다. 기본 도형은 primitive topology(D3D_PRIMITIVE_TOPOLOGY)로 생성 가능하다.   

----------------------------------------

**Vertex Shader Stage**
---
Input assembler에서 만든 vertices는 vertex shader으로 넘어와 각 정점에 대한 연산들(transformations, skinning, morphing, and per-vertex lighting)을 수행한다.   
   
<a href="http://ycpcs.github.io/cs470-fall2014/labs/lab07-2.html">변환 행렬 설명</a>
1. **World Transform**: model coordinates -> world coordinates   
    W = SRT (Transformation -> Rotation -> Scaling 순서로 행렬 곱셈)

2. __View Transform__: world coordinates -> camera space   
```
    XMMATRIX XMMatrixLookAtLH( // 계산된 시야 행렬 v 출력
        FXMVECTOR EyePosition, // 입력된 카메라 위치 Q
        FXMVECTOR FocusPosition, // 입력 대상 점 T
        FXMVECTOR UpDirection); // 입력 세계 상향 벡터 j
```

3. __Projection Transformation__: (가상의 물체가 존재하는) 3차원 공간에서 (이미지 화면에 해당하는) 2차원 공간으로의 변환   
장면의 범위인 가시 부피의 영역을 결정하고, 정규화된 가시부피 영역으로 view mapping하는 과정

<span>
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d9/images/frustum.png" height="200"></img>
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d9/images/fovdiag.png" height="200"></img>
</span>

    * frustum: 카메라가 바라보는 공간 영역
    * Perspective Projection(원근 투영): 시점이 물체로부터 유한한 거리에 있다고 간주
    * Parallel Projection(평행 투영): 시점이 물체로부터 무한대의 거리에 있다고 간주

* 시점 좌표에 투영 행렬을 곱하면 절단 좌표, 그리고 원근분할(투영 행렬에서 각 좌표를 w=z로 나누기)을 거쳐 정규화 장치 좌표로 변환

__Normalized Device Coordinate(정규화된 장치 좌표)__: 가시 부피를 가로와 세로 높이가 각각 2인 정육면체로 투상함 (x 좌표와 y 좌표를 [-1, 1] 구간으로 비례시킴)    
z 좌표는 [0, 1] 구간으로 정규화 => 정점 사이의 상대적인 깊이는 유지
* 평행 투영, 원근 투영 모두 동일한 모습의 정규화 가시 부피를 사용함으로써 파이프라인 처리 구조가 동일해짐
* 가시 부피 밖 영역을 절단하는 데 있어서 정규화 가시 부피를 기준으로 하는 것이 훨씬 단순
* 시점 좌표계 원점을 중심으로 가로, 세로 길이를 1로 정규화함으로써 화면 좌표계로 변환하기 수월
```
    XMMATRIX XMMatrixPerspectiveFovLH( // 원근 투영 행렬 반환
    float FovAngleY, // 수직 시야각(라디안 단위)
    float AspectRatio, // 종횡비 = 너비 / 높이
    float NearZ, // 가까운 평면까지의 거리
    float FarZ); // 먼 평면까지의 거리
```

4. 이후 레스터레이저 단계에서 뷰포트 변환 수행 (ID3D11DeviceContext::RSSetViewports)

----------------------------------------

**Tessellation** *(생략 가능한 단계)*
--- 

주어진 메시의 삼각형을 세분화하여 더 작은 삼각형들로 이루게 한다.   
* 장점
1. LOD(Level of Detail) 구현: 카메라와 거리가 가까운 곳에만 테셀레이션을 적용하여 세부도를 높여, 삼각형을 효율적으로 사용할 수 있다.
2. 메모리에 Low-Poly 메시를 저장하고, 필요할 때만 즉석으로 삼각형을 추가하는 방식으로 메모리를 절약할 수 있다.
3. 애니메이션이나 물리 처리 같은 연산들을 Low-Poly 메시에서 수행하여 계산량을 줄이고, 테셀레이션 된 High-Poly 메시는 렌더링에만 사용함으로써 계산량을 줄일 수 있다.
   
* __Hull Shader Stage__   
This produces Geometry Patch. Input control points define a low-order surface into control points that make up a patch. It also producese per patch calculation for the tessellation stage and the domain stage. The hull shader can be implemented using HLSL.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d11-hull-shader.png"></img></br>   
   
*Patch: lower-detail input primitive   
Control Point: a point used to determine the shape of a surface or higher-dimensional object*
   
* __Domain Shader Stage__   
This shader calculates the positions of vertices using  the data made from the hull shader stage and tessellator stage.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d11-domain-shader.png"></img></br>

----------------------------------------

**Geometry Shader Stage** *(생략 가능한 단계)*
---
This stage operates on the vertices for a full primitives and generates vertices forming a single topolgy as an output.   
A geometry shader outputs data one vertex at a time by appending vertices to an output stream object(PointStream, LineStream, TriangleStream).   
* __PointStream__   
A sequence of point primitives
* __LineStream__   
A sequence of line primitives
* __TriangleStream__   
A sequence of triangle primitives

----------------------------------------

**Rasterizer Stage**
---
The rasterization stage converts vector information (composed of shapes or primitives) into a raster image (composed of pixels) for the purpose of displaying real-time 3D graphics. Rasterization includes clipping vertices to the view frustum, performing a divide by z to provide perspective, mapping primitives to a 2D viewport, and determining how to invoke the pixel shader.   
You can disable rasterization by setting the pixel shader stage to NULL(ID3D11DeviceContext::PSSetShader) and disabling depth and stencil test(set DepthEnable and StencilEnable to FALSE in D3D11_DEPTH_STENCIL_DESC).   
   
_View Frustum: the region of space in the modeled world that may appear on the screen_   
<br>

__가시성 판단__   
 * 관찰자를 기준으로 시계방향 순서로 정점을 정의하면 전면, 반시계방향 순서로 정점을 정의하면 후면이다. (OpenGL과 반대)
 * __backface culling__: 파이프라인에서 후면을 판단하고 제거 (시점벡터와 법선벡터의 내적에 의해 판단)
 <br>

 ```
    void RSSetViewports(
        UINT numViewports,
        const D3D11_VIEWPORT *pViewports
    );
 ```

----------------------------------------

**Pixel Shader Stage**
---
A pixel shader is a program that combines constant variables, texture data, interpolated per-vertex values, and other data to produce per-pixel outputs. The rasterizer stage can invoke a pixel shader once for each pixel. This is executed by GPU.

----------------------------------------

**Output Merger Stage (OM Stage)**
---
This generates the final rendered pixel color using a combination of pipeline state, the pixel data produced by the pixel shader, the contents of render targets and the contents of depth/stencil buffers. 8 seperate render targets with the same type and size in all dimensions can be rendered simultaneously. (However, a resource view cannot be bound to multiple render target slots at the same time.)

* __Depth-Stencil Buffer__   
The depth data is used to determine which pixel lies the closest to the camera, and the stencil data is used to mask which pixel can be updated.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d10-depth-stencil-test.png"></img></br>   

* __Blending__
Blending combines one or more pixel values to create a final pixel color.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d10-blend-state.png"></img></br>
 
    
_Render Target View(RTV): https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-resources-intro_   
_Render targets enable a scene to be rendered to a temporary intermediate buffer, rather than to the back buffer to be rendered to the screen. This feature enables use of the complex scene or add additional pixel shader effects to the scene before rendering._   

_Resource: Resources are areas in memory that can be accessed by the Direct3D pipeline. They can be mainly divided into buffers and textures. These resources can be accessed by the pipeline so that the GPU can use them._   
 
 _- The lifecycle of a Direct3D resource:_      
_1. Create a resource using one of the create methods of the ID3D11Device interface._   
_2. Bind a resource to the pipeline using a context and one of the set methods of the ID3D11DeviceContext interface._   
_3. Deallocate a resource by calling the Release method of the resource interface._  

_Resource View: A pipeline stage interprets resource data using a view. A resource view is conceptually similar to casting the resource data so that it can be used in a particular context._    
_ID3D11DepthStencilView: Access a texture resource during depth-stencil testing._   
_ID3D11RenderTargetView: Access a texture resource that is used as a render-target._   
_ID3D11ShaderResourceView: Access a shader resource such as a constant buffer, a texture buffer, a texture or a sampler._   
_ID3D11UnorderedAccessView: Access an unordered resource using a pixel shader or a compute shader._