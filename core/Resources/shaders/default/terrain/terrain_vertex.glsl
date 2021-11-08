//Terrain Vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec3 a_TexCoord;
layout(location = 3) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out float v_Height;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main()
{
	v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_Normal = mat3(transpose(inverse(u_Transform))) * vec3(a_Normal.xyz);
	v_Height = a_Color.y * 255;
	v_TexCoord = a_TexCoord.xy;
}