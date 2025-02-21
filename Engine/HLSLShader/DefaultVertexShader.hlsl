struct VertexInput  // cpu에서 VertexInput으로 넘어옴
{
    //POSITION 이거 자동완성으로 POSITIONT로 됨
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

struct VertexOutPut //정점 shader의 입력은 pixel에 출력
{
    float4 position : SV_Position; //시멘틱
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

VertexOutPut main(VertexInput input) //다음단계 출력으로 쓸려면 입력으로 받아야 함.
{
    VertexOutPut output;
    output.position = float4(input.position, 1);
    output.color = input.color;
    output.texCoord = input.texCoord;
    
    return output;
}