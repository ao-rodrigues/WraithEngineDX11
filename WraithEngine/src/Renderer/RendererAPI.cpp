﻿#include "wrpch.h"
#include "RendererAPI.h"
#include "Platform/DirectX11/DirectX11RendererAPI.h"

namespace Wraith
{
#pragma region RendererAPI
	
	// TODO set the API through a config file on Init
	RendererAPI::API RendererAPI::s_API = API::DirectX11;

	std::unique_ptr<RendererAPI> RendererAPI::Create(void* windowHandle)
	{
		switch (s_API)
		{
		case API::DirectX11:
			return std::make_unique<DirectX11RendererAPI>(static_cast<HWND>(windowHandle));
		default:
			throw WR_RENDERER_API_EXCEPTION(s_API);
		}
	}

#pragma endregion

#pragma region RendererAPI::UnsupportedAPIException

	UnsupportedAPIException::UnsupportedAPIException(int line, const char* file, RendererAPI::API renderingAPI)
		: WraithException(line, file)
		, _renderingAPI(renderingAPI)
	{ }

	const char* UnsupportedAPIException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Description] " << GetErrorString() << std::endl
			<< GetOriginString();

		_whatBuffer = oss.str();
		return _whatBuffer.c_str();
	}

	const char* UnsupportedAPIException::GetType() const noexcept
	{
		return "Unsupported Rendering API Exception";
	}

	std::string UnsupportedAPIException::GetErrorString() const
	{
		const char* unsupportedAPI;
		switch (_renderingAPI)
		{
		case RendererAPI::API::None:
			unsupportedAPI = "None";
			break;
		case RendererAPI::API::DirectX11:
			unsupportedAPI = "DirectX11";
			break;
		case RendererAPI::API::DirectX12: 
			unsupportedAPI = "DirectX12";
			break;
		case RendererAPI::API::Vulkan: 
			unsupportedAPI = "Vulkan";
			break;
		default: 
			unsupportedAPI = "Unknown";
			break;
		}
		
		std::ostringstream oss;
		oss << "The " << unsupportedAPI << " API is currently not supported!";
		return oss.str();
	}

#pragma endregion 

}
