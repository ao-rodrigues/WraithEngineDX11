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
		
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;

	protected:
		HRESULT _hr;
	};
}
