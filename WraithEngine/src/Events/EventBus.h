#pragma once

#include "Event.h"

#include <unordered_map>
#include <typeinfo>

namespace Wraith
{
	template<typename T>
	using EventCallback = std::function<void(const T&)>;
	
	class EventBus
	{
	public:
		template<typename T>
		static void Register(const EventCallback<T>& callback)
		{
			static_assert(std::is_base_of<Event, T>(), "Class not derived from Event!");

			const auto key = typeid(T).hash_code();
			if (s_listeners.count(key))
			{
				s_listeners.at(key).push_back(callback);
			}
			else
			{
				s_listeners.emplace(key, std::vector<EventCallback<Event>>());
				s_listeners.at(key).push_back(callback);
			}
		}

		template<typename T, typename... TArgs>
		static void Send(TArgs&&... args)
		{
			static_assert(std::is_base_of<Event, T>(), "Class not derived from Event!");

			const T event{args...};
			
			const auto key = typeid(T).hash_code();
			if(const auto listeners = s_listeners.find(key); listeners != s_listeners.end())
			{
				for (const auto& listener : listeners->second)
				{
					listener(event);
				}
			}
		}

	private:
		static std::unordered_map<size_t, std::vector<EventCallback<Event>>> s_listeners;
	};

	std::unordered_map<size_t, std::vector<EventCallback<Event>>> EventBus::s_listeners;
}
