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

// ConstantBuffer.
cbuffer Camera : register(b1)
{
    matrix view;
    matrix projection;
};

struct VertexOutput
{
    float4 position : SV_POSITION; //레스터 라이저 처리
    float3 color :  COLOR; //sv 안붙은거는 보간기가 처리
    float2 texCoord : TEXCOORD; //sv 안붙은거는 보간기가 처리
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    //output.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    output.color = input.color;
    output.texCoord = input.texCoord;
    
    return output;
}