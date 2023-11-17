struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	unsigned int m_time;
};

Texture2D gTexture : register(t0);
SamplerState gSampler : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//float4 samp_color = gTexture.Sample(gSampler, float2(0,0));
	float4 color = /*samp_color*/ float4(lerp(input.color, input.color1, (sin(m_time / 500.0f) + 1.0f) / 2.0f),1.0f);

	return color;
}