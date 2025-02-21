struct PixelInput // vectex shader에 출력이 넘어옴
{
    // 픽셀 쉐이더에서 위치 값넣어야지 색깔 반영됨
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

Texture2D diffuseMap : register(t0); // texture index 0
SamplerState diffuseSampler : register(s0); // sample index 0


float4 main(PixelInput input) : SV_TARGET
{
    //sampling
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
	//return float4(input.color, 1.0f);
    //return float4(input.texCoord, 0.0f, 1.0f);
    return texColor;
}