#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "value.fx"

// mesh : RectMesh
struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

// ==========
// GrayFilter
// ==========
VS_OUT VS_GrayFilter(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_GrayFilter(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
        
    vColor = g_postprocess.Sample(g_sam_0, _in.vUV);
    
    float aver = (vColor.r + vColor.g + vColor.b) / 3.f;
    
    vColor.rgb = float3(aver, aver, aver);
    
    return vColor;
}


// 
VS_OUT VS_Distortion(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Distortion(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
        
    // 픽셀쉐이더에 SV_Position 으로 입력된 값은 픽셀 쉐이더를 호출한 해당 픽셀의 좌표가 들어있다.
    float2 vScreenUV = _in.vPosition.xy / g_RenderResolution;
    
    
    
    //vScreenUV.y += cos((vScreenUV.x + (g_time * (속도) )) * (주파수)) * (진폭);
    //vScreenUV.y += cos((vScreenUV.x + (g_time *  0.1f))   *   40.f)  *  0.1f;
    
    if (g_btex_0)
    {
        //float2 vUV = _in.vUV;
        //vUV.xy += g_time * 0.01f;
        
        //float2 vNoise = g_tex_0.Sample(g_sam_0, vUV);
        ////vNoise = (vNoise.xy - 0.5f) * 0.1f;
        
        //vScreenUV += vNoise;
        
        float2 vWarpUV = vScreenUV * 10.f;
    
        float len = length(vWarpUV);
        float2 st = vWarpUV * 0.1f + 0.2f * float2(cos(0.071f * g_time * 8.f + len), sin(0.073 * g_time * 8.f - len));
        float3 warpedCol = g_tex_0.Sample(g_sam_0, st).xyz * 2.4f;
        float w = max(warpedCol.r, 0.85f);
        
        float2 offset = 0.01f * cos(warpedCol.rgb * PI);
        vColor = float4(g_postprocess.Sample(g_sam_0, vScreenUV + offset).rgb * float3(0.8f, 0.8f, 1.5f), 1.0f);
        vColor *= w * 1.2f;
    }
       
    
   //vColor = g_postprocess.Sample(g_sam_0, vScreenUV);
    
    return vColor;
}


#endif