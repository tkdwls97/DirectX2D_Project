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
    
    // ����(��) ��ǥ�� -> ���� -> �� -> ���� ��ǥ��� ���������� ��ȯ      
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
        
        //saturate 0 ~ 1 �� ���� �ʰ� ����
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f); // rgb�� rb�� 1.0f�� ������ ����Ÿ ���̴� �̸�
                                                                        // �����ؼ� ������ ���� 0.9f ~ 1.0f ������ ���� 1.f���� ���ش�
        if (fAlpha < 0.1f)
        {
            
            discard; // �ȼ� ���̴��� �߰��� ���ó��
            //clip(-1);  ���� ��� �Լ�        
        }
    }
    
    return vColor;
}

#endif