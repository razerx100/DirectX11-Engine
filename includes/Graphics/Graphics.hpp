#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__
#include <CleanWin.hpp>
#include <DxgiInfoManager.hpp>
#include <d3d11.h>
#include <wrl.h>
#include <vector>

using Microsoft::WRL::ComPtr;

class Graphics {
	friend class Bindable;
public:
	Graphics(HWND hwnd, std::uint32_t width, std::uint32_t height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	void EndFrame();
	void BeginFrame(float red, float green, float blue) noexcept;
	void DrawIndexed(std::uint32_t count) noexcept(!IS_DEBUG);

	void EnableImGui() noexcept;
	void DisableImGui() noexcept;
	bool IsImGuiEnabled() const noexcept;

private:
	void ImGuiBegin();
	void ImGuiEnd();

private:
	ComPtr<ID3D11Device> m_pDevice;
	ComPtr<IDXGISwapChain> m_pSwapChain;
	ComPtr<ID3D11DeviceContext> m_pDeviceContext;
	ComPtr<ID3D11RenderTargetView> m_pTargetView;
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;

	std::uint32_t m_width;
	std::uint32_t m_height;

	bool m_imGuiEnabled;
	HRESULT hr;
};
#endif
