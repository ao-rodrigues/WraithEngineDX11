#include "wrpch.h"
#include "DXGIInfoManager.h"
#include "Platform/Windows/Win32Exception.h"
#include <dxgidebug.h>

namespace Wraith
{
	DXGIInfoManager::DXGIInfoManager()
	{
		typedef HRESULT (WINAPI* DXGIGetDebugInterface)(REFIID, void**);

		const auto hModDXGIDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		if (!hModDXGIDebug)
		{
			throw WRAITH_WIN32_LAST_EXCEPTION();
		}

		const auto dxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
			reinterpret_cast<void*>(GetProcAddress(hModDXGIDebug, "DXGIGetDebugInterface"))
		);

		if(!dxgiGetDebugInterface)
		{
			throw WRAITH_WIN32_LAST_EXCEPTION();
		}

		HRESULT hr;
		WRAITH_WIN32_ERROR_CHECK(dxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void**>(&_dxgiInfoQueue)));
	}

	DXGIInfoManager::~DXGIInfoManager()
	{
		if (_dxgiInfoQueue)
		{
			_dxgiInfoQueue->Release();
		}
	}

	void DXGIInfoManager::Mark()
	{
		_nextMsg = _dxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	}

	std::vector<std::string> DXGIInfoManager::GetMessages() const
	{
		std::vector<std::string> messages;
		const auto end = _dxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
		for (auto i = _nextMsg; i < end; i++)
		{
			HRESULT hr;
			SIZE_T messageLength = 0u;
			// Get the size of message i in bytes
			WRAITH_WIN32_ERROR_CHECK(_dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));

			auto bytes = std::make_unique<byte[]>(messageLength);
			auto message = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());

			// Get the message and push its description into the vector
			WRAITH_WIN32_ERROR_CHECK(_dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, message, &messageLength));
			messages.emplace_back(message->pDescription);
		}

		return messages;
	}
}
