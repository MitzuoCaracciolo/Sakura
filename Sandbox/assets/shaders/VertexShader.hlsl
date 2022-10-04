cbuffer uniformData
{
	row_major float4x4 modelTransform;
};

float4 main( float2 pos : POSITION ) : SV_POSITION
{
	return mul(modelTransform, float4(pos, 0.0f, 1.0f));
}