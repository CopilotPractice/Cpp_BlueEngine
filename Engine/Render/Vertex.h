#pragma once
#include "Math/Vector3.h" //현재경로 우선
#include "Math/Vector2.h"

//텍스처매핑 = 텍스터는 2차원 오브젝트는 3차원 = 2->3, 3->2;
//UV좌표 = 텍스처의 좌표
//UV매핑 = 텍스처와 오브젝트를 1:1 대응 할 수 있게 만들어주는 

//파일 업로드 => 데이터 => 리소스 => vs,ps =>
//RGB = 모니터 전구의 밝기

namespace Blue
{
	class Vertex // data의 성격, 
	{
	public:
		Vertex(const Vector3& position, const Vector3& color, const Vector2& texCoord)
			: position(position), color(color),texCoord(texCoord) //정점 쉐이더가 바뀌면 inputlayout도 같이 바뀌어야함
		{

		}
		static unsigned int Stride() { return sizeof(Vertex); }

	public:
		//정점 위치
		Vector3 position;
		//정점 색상
		Vector3 color;
		//정점 기준 텍스처 좌표
		Vector2 texCoord;
	};
}