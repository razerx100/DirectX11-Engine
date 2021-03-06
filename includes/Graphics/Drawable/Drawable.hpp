#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__
#include <Transform.hpp>
#include <memory>
#include <vector>
#include <string>

struct BindPtr;

class Drawable {
public:
	Drawable() = default;
	virtual ~Drawable();

	virtual void Draw(class Graphics& gfx) const noexcept;

	// Bind Root Signature before constant buffers
	void AddBind(BindPtr* bind) noexcept;
	void AddBind(std::unique_ptr<class Bindable> bind) noexcept;

protected:
	std::uint32_t m_indexCount;
	std::vector<BindPtr*> m_pBindRefs;
	std::vector<std::unique_ptr<class Bindable>> m_pBinds;

	Transform m_transform;
};
#endif
