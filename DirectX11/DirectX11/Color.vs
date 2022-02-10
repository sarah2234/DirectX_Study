// Vertex Shader

// Most globals are located in buffer called "cbuffer"(constant buffer) to efficiently execute shaders & store the buffers by the graphic card
// these globals will be updated each frame at the same time.
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


// Type definition is made below. (Created 2 structures since the semantics are different for vertex and pixel shaders.)
// 셰이더에는 여러 가지 종류의 값을 넘길 수 있으므로, 식별하는 작업이 필요하다.
// 이는 semantics에 의해 이뤄지고, 대소문자를 구분하지 않는다. 다만, SV_로 시작하는 semantics는 렌더링 파이프라인에서 특별한 의미를 갖는 semantics로 취급된다.
struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};


// The vertex shader below will be called for every single vertex in the vertex buffer.
// The input to the vertex shader must match the data format in the vertex buffer and type definition in the shader source(= 'VertexInputType').
// Ouput of Vertex Shader(= 'PixelInputType') => The Input of Pixel Shader 
PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    

	// Change the position vector to be 4 units for proper matrix calculations.
    // 동차 좌표
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// Store the input color for the pixel shader to use.
    output.color = input.color;
    
    return output;
}