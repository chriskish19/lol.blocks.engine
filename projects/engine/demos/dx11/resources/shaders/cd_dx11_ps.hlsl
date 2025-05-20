
struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
};


float4 PS_Main(VS_OUTPUT ps_input) : SV_TARGET
{
    ps_input.pos = float4(0.0f, 1.0f, 0.0f, 1.0f);
    return ps_input.pos;
}