/////////////
// GLOBALS //
/////////////
// Generally you will put most globals in buffer object types called "cbuffer" even if it is just a single global variable.
// Logically organizing these buffers is important for efficient execution of shaders as well as how the graphics card will store the buffers.
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

//////////////
// TYPEDEFS //
//////////////
// The input to the vertex shader must match the data format in the vertex buffer 
// as well as the type definition in the shader source file which in this case is VertexInputType.
struct VertexInputType
{
	float4 position: POSITION; // works for vertex shader
	float4 color: COLOR;
}

// The output of the vertex shader will be sent to the pixel shader.
// In this case the output type is called PixelInputType which is defined above as well.
struct PixelInputType
{
	float4 position: SV_POSITION; // works for pixel shader
	float4 color: COLOR;
}

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
// This vertex shader which I named ColorVertexShader will be called for every single vertex in the vertex buffer.
PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    

    // Change the position vector to be 4 units for proper matrix calculations.(µ¿Â÷ÁÂÇ¥)
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the input color for the pixel shader to use.
    output.color = input.color;
    
    return output;
}