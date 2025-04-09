#pragma once

#include "Math/Vector2.h" //마우스 클릭 위치를 제공해야하기 때문에 include

//입력 처리 담당 클래스
namespace Blue
{
	//키 입력 처리를 위한 구조체
	struct KeyInputData
	{
		// 입력 관련 변수
		bool isKeyDown = false;
		bool isKeyUp = false;
		bool isKey = false;

		//키 값 설정 함수
		void SetKeyUpDown(bool isKeyUp, bool isKeyDown)
		{
			this->isKeyUp = isKeyUp;
			this->isKeyDown = isKeyDown;

			isKey = isKeyDown && !isKeyUp;  //down이 되었는데, Up이 아니면 눌림 상태

		}
	};

	//마우스 입력처리를 위한 구조체
	struct MouseInputData
	{
		//축을 처리할 때 부드럽게 입력 가속도를 처리하는데 여기선 안 함

		// 입력 관련 변수
		bool isButtonDown = false;
		bool isButtonUp = false;
		bool isButton = false;

		void SetButtonUpDown(bool isButtonUp, bool isButtonDown)
		{
			this->isButtonUp = isButtonUp;
			this->isButtonDown = isButtonDown;

			isButton = isButtonDown && !isButtonUp;  //down이 되었는데, Up이 아니면 눌림 상태

		}
	};

	//입력 관리자 클래스
	class InputController
	{
	public:
		InputController();
		~InputController();
		
		//편의 함수
		//KeyCode -> 버튼 값(예 :'A')
		bool IsKeyDown(unsigned int keyCode);
		bool IsKeyUp(unsigned int keyCode);
		bool IsKey(unsigned int keyCode);

		//마우스 입력 관련 함수.
		bool IsBouttonDown(unsigned int Button);
		bool IsBouttonUp(unsigned int Button);
		bool IsBoutton(unsigned int Button);

		//입력 정리 함수
		void ResetInputs();

		Vector2 GetMousePosition();
		float GetMouseDeltaX();    // 이전 프레임 대비 이동한 거리(x)
		float GetMouseDeltaY();    // 이전 프레임 대비 이동한 거리(y)

		//값 설정 함수
		void SetKeyUpDown(unsigned int keyCode, bool isKeyUp, bool isKeyDown);
		void SetButtonUpDown(unsigned int button, bool isButtonUp, bool isButtonDown);
		void SetMousePosition(int x, int y);

		//싱글톤은 명확하게 만들어지고, 접근하는지 확인해야함
		//싱글톤 접근 함수
		static InputController& Get();
 
		//생성 여부(유효성 판단)
		static bool IsVaild();

	private:

		// 키/버튼 입력 관련 변수
		KeyInputData keyInputData[256];
		MouseInputData mouseInputData[3];

		//마우스 위치 변수.
		Vector2 mousePosition = Vector2::Zero;
		Vector2 mousePreviousPosition = Vector2::Zero; //드래그를 위한 변수(이전의 위치) = delta 구하기 위한 값


		//싱글톤 구현을 위한 변수
		static InputController* instance;
	};
}