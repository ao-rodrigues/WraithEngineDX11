#include "wrpch.h"
#include "Core/Window.h"

#ifdef WR_PLATFORM_WINDOWS
#include "Platform/Windows/Win32Window.h"
#endif

namespace Wraith
{
	std::shared_ptr<Window> Window::Create(const std::string& title, unsigned int width, unsigned int height)
	{
		#ifdef WR_PLATFORM_WINDOWS
			return std::make_shared<Win32Window>(title, width, height);
		#endif
	}

}
