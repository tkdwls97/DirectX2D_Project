#ifndef _STD2D
#define _STD2D

#include "value.fx"
#include "func.fx"



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
    
    float3 vWorldPos : POSITION;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_vec4_1.w == 3.14f)
        return float4(1.f, 1.f, 0.f, 1.f);
    
    if (g_UseAnim2D)
    {
        float2 vBackgroundLeftTop = g_vLeftTop + (g_vSlizeSize / 2.f) - (g_vBackground / 2.f);
        vBackgroundLeftTop -= g_vOffset;
        float2 vUV = vBackgroundLeftTop + (g_vBackground * _in.vUV);
        
        if (vUV.x < g_vLeftTop.x || (g_vLeftTop.x + g_vSlizeSize.x) < vUV.x
            || vUV.y < g_vLeftTop.y || (g_vLeftTop.y + g_vSlizeSize.y) < vUV.y)
        {
            discard;
        }
        else
        {
            vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
            
            //// outline
            //vColor = float4(0.f, 0.f, 0.f, 0.f);
            //float3 targetColor = float3(sin(g_time), cos(g_time), 1.f); //The color of the outline
            //float samples = 10;
            //float rads = ((360.0 / float(samples)) * PI) / 180.f;
            //float mag = 0.01;
            //for (int i = 0; i < samples; i++)
            //{
            //    if (vColor.w < 0.1f)
            //    {
            //        float r = float(i + 1) * rads;
            //        float2 offset = float2(cos(r) * 0.1f, -sin(r)) * mag; //calculate vector based on current radians and multiply by magnitude
            //        vColor = g_anim2d_tex.Sample(g_sam_1, vUV + offset); //render the texture to the pixel on an offset UV
            //        if (vColor.w > 0.0f)
            //        {
            //            vColor.xyz = targetColor;
            //        }
            //    }
            //}
            
            //float4 tex = g_anim2d_tex.Sample(g_sam_1, vUV);
            //if (tex.w > 0.0)
            //{
            //    vColor = tex; //if the centered texture's alpha is greater than 0, set finalcol to tex
            //}
        }
    }
    else
    {
        if (g_btex_0)
        {
            //vColor = g_tex_0.Sample(g_sam_1, _in.vUV + float2(g_time * 0.1, 0.f));
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
                    
            //saturate 0 ~ 1 �� ���� �ʰ� ����
            float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
            if (fAlpha < 0.1f)
            {
                // �ȼ� ���̴��� �߰��� ���ó��
                discard; //clip(-1);  
            }
        }
    }
        
    // ���� ó��
    // ������ Ÿ�Ժ� ó��
    // ������ �������� �� ó��
    //g_Light2DCount;    
    tLightColor LightColor = (tLightColor) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalLight2D(_in.vWorldPos, i, LightColor);
    }
    
    vColor.rgb *= (LightColor.vColor.rgb + LightColor.vAmbient.rgb);
        
    if (0.f == vColor.a)
        discard;
    
    return vColor;
}


// EffectShader
float4 PS_Std2D_Effect(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_UseAnim2D)
    {
        float2 vBackgroundLeftTop = g_vLeftTop + (g_vSlizeSize / 2.f) - (g_vBackground / 2.f);
        vBackgroundLeftTop -= g_vOffset;
        float2 vUV = vBackgroundLeftTop + (g_vBackground * _in.vUV);
        
        if (vUV.x < g_vLeftTop.x || (g_vLeftTop.x + g_vSlizeSize.x) < vUV.x
            || vUV.y < g_vLeftTop.y || (g_vLeftTop.y + g_vSlizeSize.y) < vUV.y)
        {
            //vColor = float4(1.f, 1.f, 0.f, 1.f);
            discard;
        }
        else
        {
            vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
        }
    }
    else
    {
        if (g_btex_0)
        {
            //vColor = g_tex_0.Sample(g_sam_1, _in.vUV + float2(g_time * 0.1, 0.f));
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
                    
            //saturate 0 ~ 1 �� ���� �ʰ� ����
            float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
            if (fAlpha < 0.1f)
            {
            // �ȼ� ���̴��� �߰��� ���ó��
                discard; //clip(-1);            
            }
        }
    }
        
    // ���� ó��
    // ������ Ÿ�Ժ� ó��
    // ������ �������� �� ó��
    //g_Light2DCount;    
    tLightColor LightColor = (tLightColor) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalLight2D(_in.vWorldPos, i, LightColor);
    }
    
    vColor.rgb *= (LightColor.vColor.rgb + LightColor.vAmbient.rgb);
    
    return vColor;
}




#endif