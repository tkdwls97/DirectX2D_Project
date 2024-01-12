#ifndef _FUNC
#define _FUNC

#include "struct.fx"
#include "value.fx"


void CalLight2D(float3 _WorldPos, int _LightIdx, inout tLightColor _output)
{
    // 빛을 적용시킬 광원의 정보
    tLightInfo info = g_Light2D[_LightIdx];
    
    // Directional Light
    if (0 == info.LightType)
    {
        _output.vAmbient += info.Color.vAmbient;
    }
    
    // Point Light
    else if (1 == info.LightType)
    {
        float fAttenu = 1.f;
        
        float fDist = distance(info.vWorldPos.xy, _WorldPos.xy);
        if (fDist < info.fRadius)
        {
            if (g_int_0)
            {
                float fTheta = (fDist / info.fRadius) * (PI / 2.f);
                fAttenu = saturate(cos(fTheta));
            }
            else
            {
                fAttenu = saturate(1.f - fDist / g_Light2D[0].fRadius);
            }
            
            _output.vColor += info.Color.vColor * fAttenu;
        }
    }
    
    // Spot Light
    else
    {
        float fAttenu = 1.f; 
        
        float fDist = distance(info.vWorldPos.xy, _WorldPos.xy);
        
        if (fDist < info.fRadius)
        {
           
            float3 vecLen = _WorldPos - info.vWorldPos;
            
            float fDot = dot(vecLen, info.vWorldDir);
            
            float fAngle = acos(fDot / fDist);
           
            if (fAngle < info.fAngle)
            {
                if (g_int_0)
                {
                    float fTheta = (fDist / info.fRadius) * (PI / 2.f);
                    fAttenu = saturate(cos(fTheta));
                }
                else
                {
                    fAttenu = saturate(1.f - fDist / g_Light2D[0].fRadius);
                }
            
                _output.vColor += info.Color.vColor * fAttenu;
            }
        }
        
    }
}




#endif