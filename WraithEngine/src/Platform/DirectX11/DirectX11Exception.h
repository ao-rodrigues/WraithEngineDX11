#pragma once
#include "Platform/Windows/Win32Exception.h"

#ifdef WR_DEBUG
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

#ifdef WR_DEBUG
	#define WR_DX11_ERROR_CHECK(hrCall) if(FAILED(hr = (hrCall))) throw DirectX11Exception(__LINE__, __FILE__, hr, DXGIInfoManager::GetInstance().GetMessages())
#else
	#define WR_DX11_ERROR_CHECK(hrCall) if(FAILED(hr = (hrCall))) throw DirectX11Exception(__LINE__, __FILE__, hr)
#endif
}
