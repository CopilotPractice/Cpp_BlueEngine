#include "Core//Engine.h"
#include <iostream>

//#include "Math/Vector2.h"

using namespace Blue;
int main()
{
    // 엔진 생성 및 실행
    Engine engine(1280, 800, TEXT("ENGINE DEMO"), GetModuleHandle(nullptr));
    engine.Run();
}