Texture2D Texture : register(t0);
SamplerState ss;

// Pixel Shader
float4 main(float4 position : SV_POSITION, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return Texture.Sample(ss, texcoord);
}
