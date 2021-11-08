//Physics Collider Fragment
#version 330 core

// Uniform variables
uniform bool u_isGlobalVertexColorEnabled;          // True if we need to use the global vertex color
uniform vec4 u_GlobalVertexColor;                   // Vertex color

// In variables
in vec4 v_VertexColor;

// Out variables
out vec4 color;                        // Output color

void main()
 {

    // Compute the final color
    if (u_isGlobalVertexColorEnabled) 
    {
        color = u_GlobalVertexColor;
    }
    else 
    {
        color = v_VertexColor;
    }
}