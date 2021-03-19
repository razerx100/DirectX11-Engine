cbuffer CBuf {
	matrix transform;
};

float4 main(float3 data : Position) : SV_POSITION {
	return mul(transform, float4(data, 1.0f));
}