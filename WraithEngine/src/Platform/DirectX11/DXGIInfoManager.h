#pragma once
#include "Core/Singleton.h"

struct IDXGIInfoQueue;

namespace Wraith
{
	class DXGIInfoManager : public Singleton<DXGIInfoManager>
	{
	public:
		DXGIInfoManager();
		~DXGIInfoManager();

		void Mark();
		std::vector<std::string> GetMessages() const;
	
	private:
		unsigned long long _nextMsg = 0u;
		IDXGIInfoQueue* _dxgiInfoQueue = nullptr;
	};
}
