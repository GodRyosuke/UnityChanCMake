#version 330 core                                                                      
                                                                                    
const int MAX_POINT_LIGHTS = 2;                                                     
const int MAX_SPOT_LIGHTS = 2;                                                      
                                                                                    
in vec4 LightSpacePos;                                                              
in vec2 TexCoord0;                                                                  
in vec3 Normal0;                                                                    
in vec3 Tangent0;                                                                    
in vec3 WorldPos0;                                                                  
                         
uniform vec3 matAmbientColor;
uniform vec3 matDiffuseColor;
uniform vec3 matSpecColor;
uniform float matSpecPower;
uniform int useNormalMap;

uniform vec3 gEyeWorldPos;
uniform sampler2D gDiffuseTex;                                                                 
uniform sampler2D gNormalMap;                                                                 
uniform sampler2D gAOMap;                                                                 
						 
out vec4 FragColor;

vec3 CalcBumpedNormal()
{
    vec3 Normal = normalize(Normal0);
    vec3 Tangent = normalize(Tangent0);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = texture(gNormalMap, TexCoord0).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;
}

void main()
{
	vec3 aoVec = texture(gAOMap, TexCoord0.xy).xyz;
	float AmbientOcclusion = length(aoVec);
	vec3 Direction = vec3(1.0f, 0.0f, -1.0f);
	vec3 AmbientLight = vec3(0.2, 0.2, 0.2);
	vec3 DiffuseColor = vec3(0.5, 0.5, 0.5) * 2.f;
	vec3 SpecColor = vec3(0.5f, 0.5f, 0.5f) * 0.3f;
	float SpecPower = 0.2f;
    // SpecPoser = matSpecPoser;


    // Surface normal
	vec3 N = normalize(Normal0);
	if (useNormalMap > 0) {
		N = CalcBumpedNormal();
	}
	// Vector from surface to light
	vec3 L = normalize(-Direction);
	// Vector from surface to camera
	vec3 V = normalize(gEyeWorldPos - WorldPos0);
	// Reflection of -L about N
	vec3 R = normalize(reflect(-L, N));

	// Compute phong reflection
	// vec3 Phong = AmbientLight * matAmbientColor;
	vec3 Phong = AmbientLight * AmbientOcclusion;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = DiffuseColor * NdotL;
		// vec3 Diffuse = DiffuseColor * NdotL;
		vec3 Specular = matSpecColor * pow(max(0.0, dot(R, V)), matSpecPower);
		Phong += Diffuse + Specular;
	}

	vec4 SampledColor = texture2D(gDiffuseTex, TexCoord0.xy); 
	// vec4 aoColor = texture2D(gAOMap, TexCoord0.xy); 
	FragColor = SampledColor * vec4(Phong, 1.0f);
	// FragColor = SampledColor;
    // FragColor = vec4(Phong, 1.0f);
	// FragColor = vec4(1.0f);
}

