struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

// ConstantBuffer.
cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    //output.position = float4(input.position, 1);       행렬이 gpu쪽에서 안 넘어갔을 때
    output.position = mul(float4(input.position, 1), worldMatrix);
    //                                                  TRS가 곱해져서 들어옴
    output.color = input.color;
    output.texCoord = input.texCoord;
    
    return output;
}