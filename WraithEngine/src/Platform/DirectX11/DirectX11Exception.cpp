#include "wrpch.h"
#include "DirectX11Exception.h"

namespace Wraith
{
	DirectX11Exception::DirectX11Exception(int line, const char* file, HRESULT hr, std::vector<std::string> infoMessages)
		: Win32Exception(line, file, hr)
	{
		for (const auto& msg : infoMessages)
		{
			_info += msg;
			_info.push_back('\n');
		}

		if (!_info.empty())
		{
			_info.pop_back();
		}
	}

	const char* DirectX11Exception::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Code] " << GetErrorCode() << std::endl
			<< "[Description] " << GetErrorString() << std::endl;

		if (!_info.empty())
		{
			oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
		}
		
		oss << GetOriginString();

		_whatBuffer = oss.str();
		return _whatBuffer.c_str();
	}

	const char* DirectX11Exception::GetType() const noexcept
	{
		return "DirectX11 Wraith Exception";
	}

	const char* DirectX11Exception::GetErrorInfo() const
	{
		return _info.c_str();
	}
}
