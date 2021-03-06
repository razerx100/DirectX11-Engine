#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__
#include <Bindable.hpp>
#include <vector>

class IndexBuffer : public Bindable {
public:
	IndexBuffer(const std::vector<std::uint16_t>& indices);

	void BindCommand(Graphics& gfx) noexcept override;

	std::uint32_t GetIndexCount() const noexcept;

private:
	std::unique_ptr<struct Memory> m_pBuffer;
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;
	std::uint32_t m_indexCount;
};

#endif