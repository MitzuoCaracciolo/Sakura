cbuffer uniformData
{
	float4x4 modelTransform;
};

struct VSOut
{
	float3 normal : Normal;
	float4 position : SV_POSITION;
};

VSOut main(float3 position : Position,  float3 normal : Normal)
{
	VSOut vso;
	vso.position = mul(modelTransform, float4(position, 1.0f));
	vso.normal = normal;
	return vso;
}