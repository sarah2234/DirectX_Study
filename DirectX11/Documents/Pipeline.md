Pipeline
===
https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline   

<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d11-pipeline-stages.jpg"></img></br>

*** 
Input Assembler Stage
---
메모리에서 기하 자료(vertex, index)를 읽어 기본 도형을 생성한다. 기본 도형은 primitive topology(D3D_PRIMITIVE_TOPOLOGY)로 생성 가능하다.   

***
Vertex Shader Stage
---
Input assembler에서 만든 vertices는 vertex shader으로 넘어와 각 정점에 대한 연산들(transformations, skinning, morphing, and per-vertex lighting)을 수행한다. 한 정점에만 연산이 가능하다.   
***
Tessellation
--- 

주어진 메시의 삼각형을 세분화하여 더 작은 삼각형들로 이루게 한다.   
* 장점
1. LOD(Level of Detail) 구현: 카메라와 거리가 가까운 곳에만 테셀레이션을 적용하여 세부도를 높여, 삼각형을 효율적으로 사용할 수 있다.
2. 메모리에 Low-Poly 메시를 저장하고, 필요할 때만 즉석으로 삼각형을 추가하는 방식으로 메모리를 절약할 수 있다.
3. 애니메이션이나 물리 처리 같은 연산들을 Low-Poly 메시에서 수행하여 계산량을 줄이고, 테셀레이션 된 High-Poly 메시는 렌더링에만 사용함으로써 계산량을 줄일 수 있다.
   
* **Hull Shader Stage**   
This produces Geometry Patch. Input control points define a low-order surface into control points that make up a patch. It also producese per patch calculation for the tessellation stage and the domain stage. The hull shader can be implemented using HLSL.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d11-hull-shader.png"></img></br>   
   
*Patch: lower-detail input primitive   
Control Point: a point used to determine the shape of a surface or higher-dimensional object*
   
* **Domain Shader Stage**   
This shader calculates the positions of vertices using  the data made from the hull shader stage and tessellator stage.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d11-domain-shader.png"></img></br>
***
Geometry Shader Stage
---
This stage operates on the vertices for a full primitives and generates vertices forming a single topolgy as an output.   
A geometry shader outputs data one vertex at a time by appending vertices to an output stream object(PointStream, LineStream, TriangleStream).   
* **PointStream**   
A sequence of point primitives
* **LineStream**   
A sequence of line primitives
* **TriangleStream**   
A sequence of triangle primitives
***
Rasterizer Stage
---
The rasterization stage converts vector information (composed of shapes or primitives) into a raster image (composed of pixels) for the purpose of displaying real-time 3D graphics. Rasterization includes clipping vertices to the view frustum, performing a divide by z to provide perspective, mapping primitives to a 2D viewport, anddetermining how to invoke the pixel shader.   
You can disable rasterization by setting the pixel shader stage to NULL(ID3D11DeviceContext::PSSetShader) and disabling depth and stencil test(set DepthEnable and StencilEnable to FALSE in D3D11_DEPTH_STENCIL_DESC).   
   
*View Frustum: the region of space in the modeled world that may appear on the screen*
***
Pixel Shader Stage
---
A pixel shader is a program that combines constant variables, texture data, interpolated per-vertex values, and other data to produce per-pixel outputs. The rasterizer stage can invoke a pixel shader once for each pixel.
***
Output Merger Stage (OM Stage)
---
This generates the final rendered pixel color using a combination of pipeline state, the pixel data produced by the pixel shader, the contents of render targets and the contents of depth/stencil buffers. 8 seperate render targets with the same type and size in all dimensions can be rendered simultaneously. (However, a resource view cannot be bound to multiple render target slots at the same time.)

* Depth-Stencil Buffer   
The depth data is used to determine which pixel lies the closest to the camera, and the stencil data is used to mask which pixel can be updated.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d10-depth-stencil-test.png"></img></br>   

* Blending
Blending combines one or more pixel values to create a final pixel color.   
<img src="https://docs.microsoft.com/en-us/windows/win32/direct3d11/images/d3d10-blend-state.png"></img></br>
 
    
*Render Target View(RTV): https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-resources-intro*   
*Render targets enable a scene to be rendered to a temporary intermediate buffer, rather than to the back buffer to be rendered to the screen. This feature enables use of the complex scene or add additional pixel shader effects to the scene before rendering.*   

*Resource: Resources are areas in memory that can be accessed by the Direct3D pipeline. They can be mainly divided into buffers and textures. These resources can be accessed by the pipeline so that the GPU can use them.*   
 
 *- The lifecycle of a Direct3D resource:*      
*1. Create a resource using one of the create methods of the ID3D11Device interface.*   
*2. Bind a resource to the pipeline using a context and one of the set methods of the ID3D11DeviceContext interface.*   
*3. Deallocate a resource by calling the Release method of the resource interface.*  

*Resource View: A pipeline stage interprets resource data using a view. A resource view is conceptually similar to casting the resource data so that it can be used in a particular context.*    
*ID3D11DepthStencilView: Access a texture resource during depth-stencil testing.*   
*ID3D11RenderTargetView: Access a texture resource that is used as a render-target.*   
*ID3D11ShaderResourceView: Access a shader resource such as a constant buffer, a texture buffer, a texture or a sampler.*   
*ID3D11UnorderedAccessView: Access an unordered resource using a pixel shader or a compute shader.*