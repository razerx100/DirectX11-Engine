#include <Pyramid.hpp>
#include <Cone.hpp>
#include <BindAll.hpp>
#include <App.hpp>

Pyramid::Pyramid(Graphics& gfx,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	std::uniform_int_distribution<int>& tdist)
	:
	m_TObj(rng, adist, ddist, odist, rdist) {

	VertexLayout vertexLayout = {
		{"Position", 12u},
		{"Normal", 12u},
		{"Color", 16u}
	};

	if (!IsDataInitialized()) {
		PSODesc pso = PSODesc();

		pso.SetInputLayout(vertexLayout);

		std::unique_ptr<RootSignature> rootSig = std::make_unique<RootSignature>(
			gfx, App::GetShaderPath() + L"RSPixelLight.cso"
			);

		pso.SetRootSignature(rootSig.get());

		pso.SetPixelShader(App::GetShaderPath() + L"PSPixelLightVColor.cso");

		pso.SetVertexShader(App::GetShaderPath() + L"VSPixelLightVColor.cso");

		std::unique_ptr<Topology> topo = std::make_unique<Topology>(
			D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST
			);

		pso.SetTopology(topo.get());

		AddStaticBind(std::make_unique<PipelineState>(gfx, pso));

		AddStaticBind(std::move(rootSig));

		AddStaticBind(std::move(topo));

		AddStaticBind(std::make_unique<ConstantBuffer<LightData>>(
			3u, static_cast<std::uint32_t>(sizeof(LightData) / 4u),
			std::bind(&Light::GetLightData, App::GetLight())
			));
	}

	const int tesselation = tdist(rng);

	IndexedTriangleList model = Cone::MakeTesselatedIndependentFaces(tesselation);

	std::vector<DirectX::XMFLOAT4> vertexColors(model.GetVerticesSize());

	for (DirectX::XMFLOAT4& vColor : vertexColors)
		vColor = { 0.16f, 0.16f, 1.0f, 1.0f };

	for(int i = 0; i < tesselation; i++)
		vertexColors[i * 3] = { 1.0f, 0.08f, 0.08f, 1.0f };

	model.Transform(DirectX::XMMatrixScaling(1.0f, 1.0f, 0.7f));

	model.SetNormalsIndependentFlat();

	AddBind(std::make_unique<VertexBuffer>(
		model.GetVerticesObject(vertexLayout, true, vertexColors))
	);

	AddIndexBuffer(std::make_unique<IndexBuffer>(model.GetIndices()));

	struct PSMaterial {
		float specularIntensity;
		float specularPower;
	};

	PSMaterial matData = {
		0.6f,
		30.0f
	};

	AddBind(std::make_unique<ConstantBufferCBVStatic<PSMaterial>>(
		2u, &matData
		));

	AddBind(std::make_unique<ConstantBufferMat>(
		0u, 16u, std::bind(&Transform::GetTransformWithProjectionCM, &m_Transform)
		));

	AddBind(std::make_unique<ConstantBufferCBVDynamic<DirectX::XMMATRIX>>(
		1u, std::bind(&Transform::GetTransformCM, &m_Transform)
		));
}

void Pyramid::Update(float deltaTime) noexcept {
	m_Transform = m_TObj.GetMomentum(deltaTime);
}

std::uint32_t Pyramid::GetIndexCount() const noexcept {
	return m_IndexCount;
}
