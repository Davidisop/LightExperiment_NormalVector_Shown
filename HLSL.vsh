//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer cb0 : register(b0)
{
	matrix	g_matWorld		: packoffset(c0); // 4줄이니,
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	matrix  g_matInverseWorld:packoffset(c12);
};


cbuffer cb1 : register(b1)
{
	float3 g_vLightDir: packoffset(c0);
	float4 g_vLightPos: packoffset(c1);
	float4 g_vEyeDir: packoffset(c2);
	float4 g_vEyePos: packoffset(c3);
	float4 g_vSpotInfo: packoffset(c4);
	float4 g_vLightColor: packoffset(c5);
};




/////////////////////////////////////

struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};


struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
	float4 l : TEXCOORD1;
};


VS_OUTPUT VS(VS_INPUT Input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 vWorld = mul(float4(Input.p, 1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	output.p = vProj;
	output.n = Input.n;
	output.c = Input.c;
	output.t = Input.t;
	output.l = float4(0.0f, 0.0f, 0.0f, 0.0f);
	return output;
}


VS_OUTPUT VS_NoMatrix(VS_INPUT v)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	vOut.p = float4(v.p, 1.0f);// float4(v.p, 1.0f);
	vOut.n = v.n;
	vOut.c = v.c;// g_Color;
	vOut.t = v.t;
	vOut.l = float4(0.0f, 0.0f, 0.0f, 0.0f);
	return vOut;
}



VS_OUTPUT VS_SKY(VS_INPUT v)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	float4 vWorld = mul(float4(v.p, 1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	vOut.p = vProj.xyzz;
	vOut.n = v.n;
	vOut.c = v.c;// g_Color;
	vOut.t = v.t;
	vOut.l = float4(0.0f, 0.0f, 0.0f, 0.0f);
	return vOut;
}



VS_OUTPUT VS_Basic_Light(VS_INPUT Input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 vWorld = mul(float4(Input.p, 1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	output.p = vProj;

//

	matrix mat_Transform;
	mat_Transform = transpose(g_matInverseWorld);
	float3 vNormal_vector = normalize(mul(Input.n, (float3x3)mat_Transform));
	float intensity = max(0, dot(vNormal_vector, normalize(-g_vLightDir)));//근데 칼라별도 안들어가잖아요. 오케이. 나중에 텍스쳐 칼라 곱하니까? 그리고, 방향 -붙였으니까, 걍 해도 된다.
	output.l = float4(intensity, intensity, intensity, 1.0f);

//

	output.n = Input.n;
	output.c = Input.c;
	output.t = Input.t;
	return output;
}

