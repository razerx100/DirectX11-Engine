#ifndef __INDEX_TRIANGLE_LIST_HPP__
#define __INDEX_TRIANGLE_LIST_HPP__
#include <vector>
#include <DirectXMath.h>
#include <Vertices.hpp>
#include <optional>
#include <functional>

class IndexedTriangleList {
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(
		std::vector<DirectX::XMFLOAT3>&& verticesInput,
		std::vector<std::uint16_t>&& indicesInput);
	IndexedTriangleList(
		std::vector<DirectX::XMFLOAT3>&& verticesInput,
		std::vector<DirectX::XMFLOAT3>&& normalsInput,
		std::vector<std::uint16_t>&& indicesInput);

	void Transform(DirectX::FXMMATRIX matrix);
	void SetNormalsIndependentFlat() noexcept;

	std::uint32_t GetVerticesSize() const noexcept;

public:
	std::vector<std::uint16_t> GetIndices() const noexcept;

	// Positions only
	Vertices GetVerticesObject(
		const VertexLayout& vertexLayout
	) const noexcept;

	// Put Positions first then Normals in VertexLayout
	Vertices GetVerticesObject(
		const VertexLayout& vertexLayout,
		bool normals
	) const noexcept;

private:
	std::vector<DirectX::XMFLOAT3> m_Vertices;
	std::vector<std::uint16_t> m_Indices;
	std::vector<DirectX::XMFLOAT3> m_Normals;
};

#endif
