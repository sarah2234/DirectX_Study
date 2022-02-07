### Vertex Buffer
Every model consists of triangles. 
Each point of a triangle is called 'vertex'. 
Computers save this vertices into an array called 'vertex buffer' and send this vertex buffer to the GPU so that it can render the model.

### Index Buffer
This buffer records the location of each vertex in the vertex buffer. It is used to increase the possibility of caching the vertex data faster, which improves performance.

### Vertex Shader
This is mainly used for transforming vertices from the vertex buffer into 3D space.
The vertex shader program will be called by the GPU for each vertex that needs to be processed.   
(e.g. a 5,000 polygon model needs to call vertex shader program 15,000 times for each frame. 
A program with 60 fps will call your vertex shader 900,000 times a second to draw the 5,000 triangles.) => Writing efficient vertex shaders is important.

### Pixel Shader
This is for doing the coloring of the polygons. It is run by the GPU, and the shader program includes coloring, texturing, lighting and other effects.
It also has to be used efficiently due to the number of times it will be called by the GPU.

### HLSL
DirectX 11 use this to code small vertex & pixel shader programs.