#include "CameraComponent.h"

#include "Core/Engine.h"
#include "Core/Common.h"

#include "Math/Transform.h"
#include "Actor/Actor.h"

#include "Core/InputController.h"

namespace Blue
{
	CameraComponent::CameraComponent() 
	{
		// 뷰행렬 업데이트 및 바인딩.
		//data.viewMatrix
		//	= Matrix4::Translation(owner->transform.position * -1.0f)
		//	* Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));

		// 행렬 전치.
		data.viewMatrix = Matrix4::Transpose(data.viewMatrix);

		//투영 행렬 설정
		data.projectionMatrix = Matrix4::Perspective(90.0f, (float)Engine::Get().Width(), (float)Engine::Get().Height(), 0.1f, 100.0f);
		data.projectionMatrix = Matrix4::Transpose(data.projectionMatrix);

		// 데이터 담아서 버퍼 생성.
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(CameraBuffer);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		// 버퍼 데이터.
		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &data;

		// 버퍼 생성.
		ID3D11Device& device = Engine::Get().Device();
		ThrowIfFailed(
			device.CreateBuffer(&bufferDesc, &bufferData, &cameraBuffer),
			TEXT("Failed to create camera buffer."));
	}
	
	void CameraComponent::Tick(float deltaTime)
	{
		Component::Tick(deltaTime);

		// 입력 관리자 포인터 저장

		static InputController& input = InputController::Get();

		// @Test : 입력 테스트
		if (InputController::Get().IsKeyDown(VK_ESCAPE)) 
		{
			if (MessageBox(nullptr, TEXT("Want to Quit?"), TEXT("Quit Engine"), MB_YESNO) == IDYES)
			{
				Engine::Get().Quit(); // esc 누르면 종료
			}
		}

		//카메라 이동처리           ... 원래는 카메라는 렌더만 하는 게 이상적
		if (input.IsKey('A') || input.IsKey(VK_LEFT))
		{
			owner->transform.position.x -= 1.0f * deltaTime;
		}

		if (input.IsKey('D') || input.IsKey(VK_RIGHT))
		{
			owner->transform.position.x += 1.0f * deltaTime;
		}

		if (input.IsKey('W') || input.IsKey(VK_UP))
		{
			owner->transform.position.y += 1.0f * deltaTime;
		}

		if (input.IsKey('S') || input.IsKey(VK_DOWN))
		{
			owner->transform.position.y -= 1.0f * deltaTime;
		}

		if (input.IsKey('Q'))
		{
			owner->transform.position.z += 1.0f * deltaTime;
			
		}
		if (input.IsKey('E'))
		{
			owner->transform.position.z -= 1.0f * deltaTime;
		}
	}

	void CameraComponent::Draw()
	{
		Component::Draw();

		// 뷰행렬 업데이트 및 바인딩.
		data.viewMatrix
			= Matrix4::Translation(owner->transform.position * -1.0f)
			* Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));

		// 뷰행렬 업데이트 후 투영 행렬 설정
		data.projectionMatrix = Matrix4::Perspective(90.0f, (float)Engine::Get().Width(), (float)Engine::Get().Height(), 0.1f, 100.0f);
		
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 전치 행렬 (CPU와 GPU가 행렬을 다루는 방식이 달라서).
		// 행기준 행렬을 열기준 행렬로 변환하기 위해 전치행렬 처리.
		data.viewMatrix = Matrix4::Transpose(data.viewMatrix);
		data.projectionMatrix = Matrix4::Transpose(data.projectionMatrix);

		// 버퍼 업데이트.
		D3D11_MAPPED_SUBRESOURCE resource = {};
		context.Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &data, sizeof(CameraBuffer));
		context.Unmap(cameraBuffer, 0);

		// 버퍼 바인딩.
		context.VSSetConstantBuffers(1, 1, &cameraBuffer); //상수버퍼 : 2번째 버퍼에서 1개, cameraBuffer 주소로
	}
}