#ifndef __DRAWABLE_BASE_HPP__
#define __DRAWABLE_BASE_HPP__
#include <Drawable.hpp>
#include <Bindable.hpp>
#include <IndexBuffer.hpp>

template<typename T>
class DrawableBase : public Drawable {
public:
	static bool IsDataInitialized() noexcept {
		return !s_Binds.empty();
	}

	// Bind Root Signature before constant buffers
	static void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept {
		s_Binds.emplace_back(std::move(bind));
	}

	static void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) noexcept {
		s_IndexCount = indexBuffer->GetIndexCount();
		s_Binds.emplace_back(std::move(indexBuffer));
	}

protected:
	std::uint32_t GetIndexCount() const noexcept override {
		return s_IndexCount;
	}

private:
	const std::vector<std::unique_ptr<Bindable>>& GetStaticBindables() const noexcept override {
		return s_Binds;
	}

private:
	static std::uint32_t s_IndexCount;
	static std::vector<std::unique_ptr<Bindable>> s_Binds;
};

template<typename T>
std::uint32_t DrawableBase<T>::s_IndexCount = 0;
template<typename T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::s_Binds;

#endif
