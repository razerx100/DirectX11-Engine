#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__
#include <CleanWin.hpp>
#include <Xception.hpp>
#include <Keyboard.hpp>
#include <Mouse.hpp>
#include <Graphics.hpp>
#include <optional>
#include <memory>

class Window {
public:

	class Exception : public Xception {
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;

	private:
		HRESULT m_hr;
	};

	class NoGfxException : public Xception {
	public:
		using Xception::Xception;
		const char* GetType() const noexcept override;
	};

private:

	class WindowClass {
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Direct3D Engine Window";
		static WindowClass s_wndClass;
		HINSTANCE m_hInst;
	};

public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
	Graphics& GetGfx() const;
	static std::optional<int> ProcessMessages();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgWrap(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
	Keyboard m_kb;
	Mouse m_mouse;

private:
	int m_width;
	int m_height;
	HWND m_hWnd;
	std::unique_ptr<Graphics> m_pGfx;
};

#define HWND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define HWND_NOGFX_EXCEPT() Window::NoGfxException(__LINE__, __FILE__)
#define HWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, static_cast<HRESULT>(GetLastError()))

#endif