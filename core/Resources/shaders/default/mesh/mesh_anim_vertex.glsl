//Mesh Vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in ivec4 a_BoneIds;
layout (locaiton = 4) in vec4 a_Weights;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 u_FinalBonesMatrices[MAX_BONES];

out vec2 v_TexCoords;

void main()
{
	vec4 v_totalPosition = vec4(0.0f);
	
	for(int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		if(a_BoneIds[i] == -1)
			continue;
		if(a_BoneIds[i] >= MAX_BONES)
		{
			v_totalPosition = vec4(a_Position, 1.0f);
			break;
		}
		vec4 v_localPosition = u_FinalBonesMatrices[a_BoneIds[i]] * vec4(a_Position, 1.0f);
		v_totalPosition += v_localPosition * a_Weights[i];
		vec3 v_localNormal = mat3(u_FinalBonesMatrices[a_BoneIds[i]]) * a_Normal;
	}
	
	gl_Position = u_ViewProjection * u_Transform;
	v_TexCoords = a_TexCoord;
}
