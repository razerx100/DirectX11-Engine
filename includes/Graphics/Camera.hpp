#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__
#include <DirectXMath.h>

class Camera {
public:
	Camera() = default;

	static void SetCamera(DirectX::XMMATRIX camera) noexcept;
	static void SetProjection(DirectX::XMMATRIX projection) noexcept;
	static DirectX::XMMATRIX GetCamera() noexcept;
	static DirectX::XMMATRIX GetProjection() noexcept;

private:
	static DirectX::XMMATRIX s_Camera;
	static DirectX::XMMATRIX s_Projection;
};
#endif
