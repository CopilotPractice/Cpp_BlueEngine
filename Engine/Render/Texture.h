#pragma once

#include "Core/Type.h"
#include <string>
#include <d3d11.h>
#include <memory>

namespace Blue
{
	struct TextureData
	{
		TextureData() = default;
		~TextureData()
		{
			//원시 리소스 해제
			free(data);
			
			shaderResourceView->Release();
			shaderResourceView = nullptr;

			samplerState->Release();
			samplerState = nullptr;
		}

		//텍스처 원시 데이터
		int32 width = 0;
		int32 height = 0;
		int32 channelCount = 0; //RGB or RGBA의 
		void* data = nullptr;

		//DX 리소스
		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		//샘플링 지정
		ID3D11SamplerState* samplerState = nullptr;
	};

	class Texture
	{
		//바인딩할 셰이더 열거형
		enum class BindType
		{
			VertexShader,
			PixelShader
		};

	public:
		Texture();
		Texture(const std::string& name, BindType bindType = BindType::PixelShader, uint32 index = 0u);
		~Texture();

		void Bind();

	private:
		void LoadTexture(const std::string& name);

	private:
		std::string name;
		uint32 index = 0u;
		BindType bindType = BindType::PixelShader;
		
		std::unique_ptr<TextureData> textureData;
	};
}