cbuffer CVertexBuf : register(b0, space0) {
	matrix modelWithProjection;
};

cbuffer CVertexBuf1 : register(b1, space0) {
// ROW MAJOR
	matrix model;
};

struct VSOut {
    float3 worldPos : Position;
    float3 normal : Normal;
    float4 position : SV_Position;
};

VSOut main(float3 position : Position, float3 normals : Normal){
    VSOut vso;

    vso.worldPos = (float3) mul(model, float4(position, 1.0f));
    vso.normal = mul((float3x3) model, normals);
    vso.position = mul(float4(position, 1.0f), modelWithProjection);

	return vso;
}
