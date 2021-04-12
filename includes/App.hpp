#ifndef __APP_HPP__
#define __APP_HPP__
#include <Window.hpp>
#include <Drawable.hpp>
#include <Timer.hpp>
#include <vector>
#include <ImGuiMan.hpp>
#include <Camera.hpp>

class App {
public:
	App();
	~App() = default;

	int Go();

private:
	void DoFrame();

private:
	ImGuiMan m_imgui;
	Window m_wnd;
	Timer m_timer;
	Camera m_camera;

	std::vector<std::unique_ptr<Drawable>> m_drawables;

	static constexpr std::uint64_t nDrawables = 380u;
	float m_speedFactor;
};
#endif