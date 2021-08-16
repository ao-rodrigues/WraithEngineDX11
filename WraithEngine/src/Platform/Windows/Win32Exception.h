#pragma once
#include "Core/WraithException.h"

namespace Wraith
{
	class Win32Exception : public WraithException
	{
	public:
		Win32Exception(int line, const char* file, HRESULT hr);
		
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		
		virtual HRESULT GetErrorCode() const noexcept;
		virtual std::string GetErrorString() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;

	protected:
		HRESULT _hr;
	};

#define WRAITH_WIN32_EXCEPTION(hr) Win32Exception(__LINE__, __FILE__, hr)
#define WRAITH_WIN32_LAST_EXCEPTION() Win32Exception(__LINE__, __FILE__, GetLastError())
#define WRAITH_WIN32_ERROR_CHECK(hrCall) if(FAILED(hr = (hrCall))) throw Win32Exception(__LINE__, __FILE__, hr)
}
