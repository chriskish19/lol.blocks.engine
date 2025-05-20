/***********************************************
* File: td_dx11_ps.hlsl (triangle demo direct x 11 pixel shader)
* 
* Purpose: shade pixels
* 
* 
* 
************************************************/

float4 PS_Main(float4 pos : SV_POSITION) : SV_TARGET
{
	return float4(0.0f, 1.0f, 0.0f, 1.0f);
}