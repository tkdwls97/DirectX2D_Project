#ifndef _STD2D
#define _STD2D

// 상수 버퍼
cbuffer TRANSFORM : register(b0) // 레지스터는 b name이 붙음, 0부터 시작한다는 의미
{
    float4 g_vWorldPos;
    float4 g_vWorldScale;
}

struct VS_IN
{
    float3 vPos : POSITION; // Sementic
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    float2 vFinalPos = _in.vPos.xy * g_vWorldScale.xy + g_vWorldPos.xy; // 연산순서 바뀌면 결과 달라짐
    
    output.vPosition = float4(vFinalPos, 0.f, 1.f);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    //return float4(0.f, 0.f, 1.f, 1.f);
    
    
    return _in.vColor;
}

#endif