struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL; // 조명처리
};

// ConstantBuffer.
cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

// Camera Buffer.
cbuffer Camera : register(b1)
{
    matrix view;
    matrix projection; //cpp의 상수버퍼 크기 레이아웃과 동일해야 함
                        //투영변환은 좌표 기준 값을 월드로 바꾸고, 가상의 공간의 물체를 모아둔 것을(기준으로삼은 좌표 축)
                        //기준을 다시 세우는 것이 = 뷰변환
                        // 거리가 멀어지면 그 멀어진 거리 만큼 크기를 줄임 = 원근 투영
                        // 직교 투영은 멀어져도 크기를 줄이는 것을 안 함
    
    float3 cameraPosition; // 월드 기준의 위치
    float padding;
}; 

struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    //output.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix);
    float3 worldPosition = output.position.xyz;
    
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    //정점 쉐이더 변환 = 좌표변환
    
    output.color = input.color;
    output.texCoord = input.texCoord;
    
    // ->transpose(inverse(worldMatrix));
    output.normal = mul(input.normal, (float3x3) worldMatrix); //셰이더에서의 모든 변환은 공간을 맞추고 시작
    
    output.cameraDirection = normalize(worldPosition - cameraPosition);
    
    return output;
}