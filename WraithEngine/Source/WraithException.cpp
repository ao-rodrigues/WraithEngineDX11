#include "pch.h"
#include "WraithException.h"

using namespace Wraith;

WraithException::WraithException(int line, const char* file) noexcept
	: _line(line)
	, _file(file)
{ }

const char* WraithException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();

	_whatBuffer = oss.str();
	return _whatBuffer.c_str();
}

const char* WraithException::GetType() const noexcept
{
	return "Wraith Exception";
}

int WraithException::GetLine() const noexcept
{
	return _line;
}

const std::string& WraithException::GetFile() const noexcept
{
	return _file;
}

std::string WraithException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << _file << std::endl << "[Line] " << _line;

	return oss.str();
}
