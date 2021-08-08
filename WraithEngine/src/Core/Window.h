#pragma once

#include <memory>
#include <optional>
#include <string>

namespace Wraith
{	
	class Window
	{
	public:
		static std::shared_ptr<Window> Create(const std::string& title, unsigned int width, unsigned int height);
		
		virtual ~Window() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual std::optional<int> ProcessMessages() = 0;
	};
}
