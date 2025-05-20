cbuffer CameraBuffer : register(b0)
{
    matrix view;
    matrix projection;
};

struct VS_INPUT
{
    float3 pos : POSITION;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
};

VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output;
    float4 worldPos = float4(input.pos, 1.0f);
    output.pos = mul(worldPos, view);
    output.pos = mul(output.pos, projection);
    return output;
}
