#include "wrpch.h"
#include "Win32Exception.h"

namespace Wraith
{
	Win32Exception::Win32Exception(int line, const char* file, HRESULT hr)
		: WraithException(line, file)
		, _hr(hr)
	{}

	const char* Win32Exception::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Code] " << GetErrorCode() << std::endl
			<< "[Description] " << GetErrorString() << std::endl
			<< GetOriginString();

		_whatBuffer = oss.str();
		return _whatBuffer.c_str();
	}

	const char* Win32Exception::GetType() const noexcept
	{
		return "Win32 Exception";
	}

	HRESULT Win32Exception::GetErrorCode() const noexcept
	{
		return _hr;
	}

	std::string Win32Exception::GetErrorString() const noexcept
	{
		return TranslateErrorCode(_hr);
	}

	std::string Win32Exception::TranslateErrorCode(HRESULT hr) noexcept
	{
		char* pMsgBuffer = nullptr;
		DWORD msgLength = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPSTR>(&pMsgBuffer),
			0,
			nullptr
		);

		if(msgLength == 0)
		{
			return "Unidentified error code";
		}

		std::string errorString = pMsgBuffer;
		LocalFree(pMsgBuffer);
		return errorString;
	}
}
