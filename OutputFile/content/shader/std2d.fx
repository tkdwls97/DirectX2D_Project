#ifndef _STD2D
#define _STD2D

#include "value.fx"


struct VS_IN
{
    float4 vColor : COLOR;
    float3 vPos : POSITION; // Sementic
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
    
    // 로컬(모델) 좌표를 -> 월드 -> 뷰 -> 투영 좌표계로 순차적으로 변환      
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    //float4 vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    
    //uint width = 0;
    //uint height = 0;
    //g_tex_1.GetDimensions(width, height);
    
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        
        //saturate 0 ~ 1 을 넘지 않게 보정
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f); // rgb중 rb가 1.0f에 가까우면 마젠타 색이다 이를
                                                                        // 내적해서 보정한 값인 0.9f ~ 1.0f 사이의 값을 1.f에서 빼준다
        if (fAlpha < 0.1f)
        {
            
            discard; // 픽셀 쉐이더를 중간에 폐기처리
            //clip(-1);  같은 기능 함수        
        }
    }
    
    return vColor;
}

#endif