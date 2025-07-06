
cbuffer TimeBuffer : register(b0)
{
    float gTime;
    float3 padding; // Optional, but helps alignment on older shaders
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

float3 RainbowColor(float t)
{
    float3 color;
    color.r = 0.5 + 0.5 * sin(6.28318 * t + 0.0);
    color.g = 0.5 + 0.5 * sin(6.28318 * t + 2.09439);
    color.b = 0.5 + 0.5 * sin(6.28318 * t + 4.18879);
    return color;
}

float4 PS_Main(VS_OUTPUT ps_input) : SV_TARGET
{
    float3 color = RainbowColor(gTime);
    return float4(color, 1.0);
}
