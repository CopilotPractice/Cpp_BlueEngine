#include "Common.hlsli"

struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1; 
};

// Texture.
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling.
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
    //Light Dir
    float3 lightDir = -float3(500.0f, 500.0f, -500.0f);
    lightDir = normalize(lightDir);
    
    //World Normal
    float3 worldNormal = normalize(input.normal);
    
    //Dot (Lambert Cosine Law)
    
    //float nDotl = saturate(dot(worldNormal, -lightDir)); // 사이각을 구할 수 있게 lightDir의 
                                                                   //saturate 함수를 통해 cos 함수에서 0이하의 값은 제외
    float nDotl = CalcLambert(worldNormal, lightDir);
        // Half Lambert.
    //nDotl = pow((nDotl * 0.8f) + (1.0 - 0.8), 1.5);
    
    //Phone(Specular)
    
    //float4 ambient = texColor + float4(0.1f, 0.1f, 0.1f, 1);
    float4 ambient = texColor * float4(0.1f, 0.1f, 0.1f, 1);
    float4 diffuse = texColor * nDotl;
    float4 finalColor = ambient + diffuse;
    
    //float specular = CalcPhong(worldNormal, lightDir, input.cameraDirection);
    float specular = 0;
    if(nDotl)
    {
        float3 viewDirection = normalize(input.cameraDirection);
        float3 halfVector = normalize((-lightDir) + (-viewDirection));
        
        //nDoth
        float nDoth = saturate(dot(worldNormal, halfVector));
        float shineness = 32.0f;
        specular = pow(nDoth, shineness);

    }
    
    
    finalColor += specular;
    return finalColor;
}