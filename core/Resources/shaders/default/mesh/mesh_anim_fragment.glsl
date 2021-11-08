//Mesh Fragment
#version 330 core
out vec4 color;

//Light structs
struct Material {
	float shininess;
	float metalness;
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
};
struct Global {
    vec3 direction;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 color;
    float intensity;
    int totalLights;
    vec3 cameraPosition;
};
struct Light {
	int type;
	vec3 direction;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 color;
	float intensity;
	float constant;
	float linear;
	float quadratic;
	float cutoff;
};

//Vertex Shader info
in vec3 v_Position;
in float v_Height;
in vec3 v_Normal;
in vec2 v_TexCoord;

//Lighting information
uniform Global u_Global;
uniform Light u_Light[8]; // Only support 8 lights max
uniform Material u_Material;

vec3 CalculateGlobalLighting(vec4 blendColor, vec3 normal, vec3 cameraDir);
vec3 CalculateDirectionalLighting(Light light, vec3 blend, vec3 normal, vec3 cameraDir);
vec3 CalculatePointLighting(Light light, vec3 blend, vec3 normal, vec3 cameraDir);
vec3 CalculateSpotLighting(Light light, vec3 blend, vec3 normal, vec3 cameraDir);

void main()
{
    vec4 blendColor = texture(u_Material.texture_diffuse1, v_TexCoord);

	vec3 norm = normalize(v_Normal);
	vec3 cameraDir = normalize(u_Global.cameraPosition - v_Position);

	vec3 finalColor = CalculateGlobalLighting(blendColor, norm, cameraDir);
	
	if(u_Global.totalLights > 0)
	{
        for(int i = 0; i < u_Global.totalLights; i++)
        {
            if(u_Light[i].type == 0)
            {
                finalColor += CalculateDirectionalLighting(u_Light[i], finalColor, norm, cameraDir);
            }
            else if(u_Light[i].type == 1)
            {
                finalColor += CalculatePointLighting(u_Light[i], finalColor, norm, cameraDir);
            }
            else if(u_Light[i].type == 2)
            {
                finalColor += CalculateSpotLighting(u_Light[i], finalColor, norm, cameraDir);
            }
            else
            {
                color = texture(u_Material.texture_diffuse1, v_TexCoord);
            }
        }
	}

    color = vec4(finalColor, blendColor.a);
	
	//if the alpha channel is less than 0.1, discard as it should be transparent
	if(color.a < 0.1f)
	{
		discard;
	}
}

vec3 CalculateGlobalLighting(vec4 blendColor, vec3 normal, vec3 cameraDir)
{
	vec3 lightDir = normalize(-u_Global.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), u_Material.shininess);
	// combine results
	vec3 ambient  = u_Global.ambient  * vec3(blendColor.rgb);
	vec3 diffuse  = u_Global.diffuse  * diff * vec3(blendColor.rgb);
	vec3 specular = u_Global.specular * spec * vec3(texture(u_Material.texture_specular1, v_TexCoord).rgb);

	vec3 final = (ambient + diffuse + specular);
	return final * u_Global.color * u_Global.intensity;
}

vec3 CalculateDirectionalLighting(Light light, vec3 blend, vec3 normal, vec3 cameraDir)
{
	vec3 ambient = light.ambient * blend.rgb;
	// diffuse 
	vec3 norm = normalize(v_Normal);

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * blend.rgb;
	// specular
	vec3 viewDir = normalize(u_Global.cameraPosition - v_Position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(u_Global.cameraPosition, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Global.specular * spec * texture(u_Material.texture_specular1, v_TexCoord).rgb;

	vec3 result = vec3(ambient + diffuse + specular);
	result = (result * light.intensity) * light.color;
	return result;
}

vec3 CalculatePointLighting(Light light, vec3 blend, vec3 normal, vec3 cameraDir)
{
	vec3 lightDir = normalize(light.position - v_Position);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), u_Material.shininess);
	// attenuation
	float distance    = length(light.position - v_Position);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// combine results
	vec3 ambient  = light.ambient  * vec3(blend.rgb);
	vec3 diffuse  = light.diffuse  * diff * vec3(blend.rgb);
	vec3 specular = light.specular * spec * vec3(texture(u_Material.texture_specular1, v_TexCoord));
	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;
	vec3 result = (ambient + diffuse + specular);
	result *= light.intensity * light.color;
	return result;
}

vec3 CalculateSpotLighting(Light light, vec3 blend, vec3 normal, vec3 cameraDir)
{
	vec3 lightDir = normalize(light.position - v_Position);
	// check if lighting is inside the spotlight cone
	float theta = dot(lightDir, normalize(-light.direction));

	if (theta > light.cutoff)// remember that we're working with angles as cosines instead of degrees so a '>' is used.
	{
		// ambient
		vec3 ambient = light.ambient * blend.rgb;

		// diffuse 
		vec3 norm = normalize(v_Normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * blend.rgb;

		// specular
		vec3 viewDir = normalize(u_Global.cameraPosition - v_Position);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(u_Global.cameraPosition, reflectDir), 0.0), u_Material.shininess);

		vec3 specular = u_Global.specular * spec * texture(u_Material.texture_specular1, v_TexCoord).rgb;

		// attenuation
		float distance    = length(light.position - v_Position);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

		// ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
		diffuse   *= attenuation;
		specular *= attenuation;

		vec3 result = vec3(ambient + diffuse + specular);
		result = (result * light.intensity) * light.color;
		return result;
	}
	else
	{
		// else, use ambient light so scene isn't completely dark outside the spotlight.
		vec3 result = vec3(light.ambient * blend.rgb);
		result = (result * light.intensity) * light.color;
		return result;
	}
}