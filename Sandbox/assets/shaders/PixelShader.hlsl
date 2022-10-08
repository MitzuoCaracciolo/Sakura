Texture2D tex;
SamplerState smpl;

float4 main(float2 texCoord : TextCoord) : SV_Target
{
	return tex.Sample(smpl, texCoord);
}