//Mesh Vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec3 a_Bitangent;
layout (location = 4) in vec2 a_TexCoord;
layout (location = 5) in ivec4 a_BoneIds;
layout (location = 6) in vec4 a_Weights;

out vec3 v_Position;
out vec2 v_TexCoord;
out vec3 v_Normal;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform bool u_Animated;
uniform mat4 u_FinalBonesMatrices[MAX_BONES];

void main()
{

	if(u_Animated)
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

		gl_Position = u_ViewProjection * u_Transform * v_totalPosition;
		v_TexCoord = a_TexCoord;
	}
	else
	{
		v_TexCoord = a_TexCoord;
		v_Normal = a_Normal;
		v_Position = a_Position;
		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);

	}
}
