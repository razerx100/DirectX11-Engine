#include <DxgiInfoManager.hpp>
#include <Window.hpp>
#include <dxgidebug.h>
#include <memory>

#define GFX_THROW_NOINFO(hr, hrCall) if(FAILED(hr = (hrCall))) throw Graphics::HrException(__LINE__, __FILE__, hr)

DxgiInfoManager::DxgiInfoManager()
	: m_next(0u), m_pDxgiInfoQueue(nullptr) {
	// define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	// load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (!hModDxgiDebug)
		throw HWND_LAST_EXCEPT();

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
	if (!DxgiGetDebugInterface)
		throw HWND_LAST_EXCEPT();

	HRESULT hr;
	GFX_THROW_NOINFO(hr, DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void**>(&m_pDxgiInfoQueue)));
}

DxgiInfoManager::~DxgiInfoManager() {
	if (m_pDxgiInfoQueue)
		m_pDxgiInfoQueue->Release();
}

void DxgiInfoManager::Set() noexcept {
	// Set the index (next) so that the next call to GetMessages()
	// will only get errors generated after this call
	m_next = m_pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::GetMessages() const {
	std::vector<std::string> messages;
	const std::uint64_t end = m_pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);

	for (std::uint64_t i = m_next; i < end; i++) {
		HRESULT hr;
		SIZE_T messageLength = 0;
		GFX_THROW_NOINFO(hr, m_pDxgiInfoQueue->GetMessage(
			DXGI_DEBUG_ALL, i, nullptr, &messageLength
		));

		std::unique_ptr<byte[]> bytes = std::make_unique<byte[]>(messageLength);
		DXGI_INFO_QUEUE_MESSAGE* pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());

		GFX_THROW_NOINFO(hr, m_pDxgiInfoQueue->GetMessage(
			DXGI_DEBUG_ALL, i, pMessage, &messageLength
		));
		messages.emplace_back(pMessage->pDescription);
	}

	return messages;
}
