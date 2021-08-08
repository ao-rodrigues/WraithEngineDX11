#pragma once

namespace Wraith
{
	using EventType = unsigned int;
	
	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetType() const = 0;
		virtual std::string ToString() const = 0;
	};
}
