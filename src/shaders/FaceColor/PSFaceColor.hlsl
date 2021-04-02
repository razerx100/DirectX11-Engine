cbuffer ColorBuf : register(b0, space1) {
	float4 faceColors[6];
};

float4 main(uint id : SV_PrimitiveID) : SV_TARGET{
	return faceColors[(id / 2) % 6];
}
