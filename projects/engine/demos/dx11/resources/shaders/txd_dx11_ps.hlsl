Texture2D m_tx : register(t0);
SamplerState m_cms : register(s0);

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD0;
};

float4 PS_Main(PS_Input frag) : SV_TARGET
{
    return m_tx.Sample(m_cms, frag.tex0);
}