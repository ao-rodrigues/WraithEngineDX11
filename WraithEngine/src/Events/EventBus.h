#pragma once
#include "Event.h"

#define WRAITH_BIND_EVENT_CALLBACK(callback) [this](auto&&... args) -> decltype(auto) { return  this->callback(std::forward<decltype(args)>(args)...); }
#define WRAITH_BIND_EVENT_CALLBACK_STATIC(callback) [](auto&&... args) -> decltype(auto) { return  callback(std::forward<decltype(args)>(args)...); }

namespace Wraith
{
	template<typename EventType>
	using EventCallback = std::function<void(const EventType&)>;
	
	class EventBus
	{
	public:
		template<typename EventType>
		static void Register(EventCallback<EventType> callback)
		{
			static_assert(std::is_base_of<Event, EventType>(), "Class not derived from Event!");

			const auto key = typeid(EventType).hash_code();
			s_listeners[key].emplace_back(CallbackWrapper<EventType>(callback));
		}

		template<typename T, typename... TArgs>
		static void Send(TArgs&&... args)
		{
			static_assert(std::is_base_of<Event, T>(), "Class not derived from Event!");

			const T event(std::forward<TArgs>(args)...);
			
			const auto key = typeid(T).hash_code();
			if(s_listeners.find(key) == s_listeners.end())
			{
				return;
			}

			for (auto&& listener : s_listeners.at(key))
			{
				listener(event);
			}
		}

	private:
		template<typename EventType>
		struct CallbackWrapper
		{
			CallbackWrapper(EventCallback<EventType> callback)
				: callback(callback)
			{}

			void operator()(const Event& event)
			{
				callback(static_cast<const EventType&>(event));
			}
			
			EventCallback<EventType> callback;
		};
		
		static std::unordered_map<size_t, std::vector<EventCallback<Event>>> s_listeners;
	};
}
