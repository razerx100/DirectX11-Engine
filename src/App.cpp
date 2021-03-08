#include <App.hpp>
#include <sstream>
#include <iomanip>

App::App()
	: m_wnd(1280, 720, "DirectX11 Window") {}

int App::Go() {
	while (true) {
		if (const auto ecode = Window::ProcessMessages())
			return *ecode;

		DoFrame();
	}
}

void App::DoFrame() {

}