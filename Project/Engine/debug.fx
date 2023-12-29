#ifndef _DEBUG
#define _DEBUG

#include "value.fx"

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    float4 vColor : COLOR;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float4 vColor : COLOR;
};

VS_OUT VS_DebugShape(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

static float g_Thickness = 0.01f;

float4 PS_DebugShape(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (g_Thickness <= _in.vUV.x && _in.vUV.x <= (1.f - g_Thickness)
        && g_Thickness <= _in.vUV.y && _in.vUV.y <= (1.f - g_Thickness))
    {
        discard;
    }
    
    vOutColor = float4(1.f, 0.f, 1.f, 1.f);
    //vOutColor = _in.vColor;
    
    return vOutColor;
}






#endif