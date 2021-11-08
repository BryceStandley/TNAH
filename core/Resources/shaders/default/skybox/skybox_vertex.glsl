#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_View;
uniform mat4 u_ViewProjection;
uniform vec3 u_CameraPosition;

void main()
{
	v_TexCoords = a_Position;
	gl_Position = u_ViewProjection * vec4(a_Position + u_CameraPosition, 1.0f);	
}