#include "Texture.h"
#include "Core/Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Library/stbi_image.h"
#include <iostream>

namespace Blue {


	Blue::Texture::Texture()
	{
	}
	Texture::Texture(const std::string& name, BindType bindType, uint32 index)
		: name(name),bindType(bindType),index(index)
	{
		LoadTexture(name);
	}

	Texture::~Texture()
	{
	}

    void Texture::Bind()
    {
        // 예외 처리.
        if (!textureData)
        {
            return;
        }

        // 컨텍스트 얻기.
        static ID3D11DeviceContext& context = Engine::Get().Context();

        // 바인딩.
        if (bindType == BindType::VertexShader)
        {
            context.VSSetShaderResources(index, 1, &textureData->shaderResourceView);
            context.VSSetSamplers(index, 1, &textureData->samplerState);
        }
        else if (bindType == BindType::PixelShader)
        {
            context.PSSetShaderResources(index, 1, &textureData->shaderResourceView);
            context.PSSetSamplers(index, 1, &textureData->samplerState);
        }
    }

	void Texture::LoadTexture(const std::string& name)
	{
        char path[256] = {};
        sprintf_s(path, 256, "../Assets/Textures/%s", name.c_str());

        textureData = std::make_unique<TextureData>();

        textureData->data = stbi_load(path, &textureData->width, &textureData->height, 
            &textureData->channelCount,0);

        if (!textureData->data)
        {
            std::cout << "Filed to load texture file: " << name << "\n";
            __debugbreak();
        }

        //DX 리소스 생성
        //장치
        static ID3D11Device& device = Engine::Get().Device();
        
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.ArraySize = 1;
        textureDesc.MipLevels = 1;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        textureDesc.Width = textureData->width;
        textureDesc.Height = textureData->height;

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = textureData->data;
        data.SysMemPitch = textureData->width * textureData->channelCount;

        ID3D11Texture2D* texture = nullptr;
        auto result = device.CreateTexture2D(&textureDesc, &data, &texture);
        if (FAILED(result))
        {
            std::cout << "Error: Failed to create texture2d.\n";
            __debugbreak();
        }

        result = device.CreateShaderResourceView(texture, nullptr, &textureData->shaderResourceView);
	
        if (FAILED(result))
        {
            std::cout << "Error: Failed to create shader resource view.\n";
            __debugbreak();
        }

        if (texture) {
            texture->Release();
            texture = nullptr;
        } 

        D3D11_SAMPLER_DESC sampleDesc = {};
        sampleDesc.Filter = D3D11_FILTER_ANISOTROPIC;
        sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampleDesc.MaxLOD = FLT_MAX;
        sampleDesc.MinLOD = -FLT_MAX;
        sampleDesc.MaxAnisotropy = 3;
        sampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;


        result = device.CreateSamplerState(&sampleDesc, &textureData->samplerState);
        if (FAILED(result))
        {
            std::cout << "Error: Failed to Create Sampler State.\n";
            __debugbreak();
        }


    }
}