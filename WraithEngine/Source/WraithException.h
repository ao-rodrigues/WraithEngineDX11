#pragma once

#include <exception>
#include <string>

namespace Wraith
{
	class WraithException : public std::exception
	{
	public:
		WraithException(int line, const char* file) noexcept;
		
		const char* what() const noexcept override;
		
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetOriginString() const noexcept;

	protected:
		mutable std::string _whatBuffer;

	private:
		int _line;
		std::string _file;
	};
}

