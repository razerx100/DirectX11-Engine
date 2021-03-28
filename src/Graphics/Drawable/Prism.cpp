#include <Prism.hpp>

IndexedTriangleList Prism::MakeTesselated(std::uint16_t longDiv) {
	assert(longDiv > 2);

	const DirectX::XMVECTOR base = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
	const DirectX::XMVECTOR offset = DirectX::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
	const float longitudeAngle = DirectX::XM_2PI / longDiv;

	// Near center
	std::vector<DirectX::XMFLOAT3> vertices;
	vertices.emplace_back();
	vertices.back() = { 0.0f, 0.0f, -1.0f };
	const std::uint16_t iCenterNear = static_cast<std::uint16_t>(vertices.size() - 1);

	// Far center
	vertices.emplace_back();
	vertices.back() = { 0.0f, 0.0f, 1.0f };
	const std::uint16_t iCenterFar = static_cast<std::uint16_t>(vertices.size() - 1);

	// Base vertices
	for (int iLong = 0; iLong < longDiv; iLong++) {
		// Near Base
		vertices.emplace_back();
		DirectX::XMVECTOR v = DirectX::XMVector3Transform(
			base,
			DirectX::XMMatrixRotationZ(longitudeAngle * iLong)
		);
		DirectX::XMStoreFloat3(&vertices.back(), v);

		// Far Base
		vertices.emplace_back();
		v = DirectX::XMVector3Transform(
			base,
			DirectX::XMMatrixRotationZ(longitudeAngle * iLong)
		);
		v = DirectX::XMVectorAdd(v, offset);
		DirectX::XMStoreFloat3(&vertices.back(), v);
	}

	// Side indices
	std::vector<std::uint16_t> indices;
	for (std::uint16_t iLong = 0; iLong < longDiv; iLong++) {
		const std::uint16_t i = iLong * 2u;
		const std::uint16_t mod = longDiv * 2u;

		indices.push_back(i + 2u);
		indices.push_back((i + 2u) % mod + 2u);
		indices.push_back(i + 1u + 2u);
		indices.push_back((i + 2u) % mod + 2u);
		indices.push_back((i + 3u) % mod + 2u);
		indices.push_back(i + 1u + 2u);
	}

	// Base indices
	for (std::uint16_t iLong = 0; iLong < longDiv; iLong++) {
		const std::uint16_t i = iLong * 2u;
		const std::uint16_t mod = longDiv * 2u;

		indices.push_back(i + 2u);
		indices.push_back(iCenterNear);
		indices.push_back((i + 2u) % mod + 2u);
		indices.push_back(iCenterFar);
		indices.push_back(i + 1u + 2u);
		indices.push_back((i + 3u) % mod + 2u);
	}

	return IndexedTriangleList(std::move(vertices), std::move(indices));
}

IndexedTriangleList Prism::Make() {
	return MakeTesselated(6u);
}
