#pragma once
#include "Platform/Windows/Win32Exception.h"

#ifdef WRAITH_DEBUG
#include "DXGIInfoManager.h"
#endif

namespace Wraith
{
	class DirectX11Exception : public Win32Exception
	{
	public:
		DirectX11Exception(int line, const char* file, HRESULT hr, std::vector<std::string> infoMessages = {});

		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		const char* GetErrorInfo() const;
	private:
		std::string _info;
	};

	class DirectX11ExceptionNoHR : public WraithException
	{
	public:
		DirectX11ExceptionNoHR(int line, const char* file, std::vector<std::string> infoMessages);

		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;

	private:
		std::string _info;
	};

#ifdef WRAITH_DEBUG
	#define WRAITH_DX11_ERROR_CHECK(hrCall) DXGIInfoManager::GetInstance().Mark(); if(FAILED(hr = (hrCall))) throw DirectX11Exception(__LINE__, __FILE__, hr, DXGIInfoManager::GetInstance().GetMessages())
	#define WRAITH_DX11_ERROR_CHECK_NO_HR(exp) DXGIInfoManager::GetInstance().Mark(); (exp); { auto msgs = DXGIInfoManager::GetInstance().GetMessages(); if(!msgs.empty()) { throw  DirectX11ExceptionNoHR(__LINE__, __FILE__, msgs); }}
#else
	#define WRAITH_DX11_ERROR_CHECK(hrCall) if(FAILED(hr = (hrCall))) throw DirectX11Exception(__LINE__, __FILE__, hr)
	#define WRAITH_DX11_ERROR_CHECK_NO_HR(exp) (exp);
#endif
}
