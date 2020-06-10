#include "Basic.hlsli"

VertexPosHWNormalTex VS_3D(VertexPosNormalTex vIn)
{
	VertexPosHWNormalTex vOut;
	float4 posW = mul(float4(vIn.PosL, 1.0f), g_World);
	matrix viewProj = mul(g_View, g_Proj);

	vOut.PosH = mul(posW, viewProj);
	vOut.PosW = posW.xyz;
	vOut.NormalW = mul(vIn.NormalL, (float3x3) g_WorldInvTranspose);
	vOut.Tex = vIn.Tex;
	return vOut;
}
