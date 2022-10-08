cbuffer uniformData
{
	row_major float4x4 modelTransform;
};

struct VSOut
{
	float2 texCoord : TextCoord;
	float4 position : SV_POSITION;
};

VSOut main(float2 position : Position,  float2 texCoord : TextCoord)
{
	VSOut vso;
	vso.position = mul(modelTransform, float4(position, 0.0f, 1.0f));
	vso.texCoord = texCoord;
	return vso;
}