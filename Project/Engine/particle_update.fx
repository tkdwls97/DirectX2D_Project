#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<tParticleModule> g_Module : register(t20);
RWStructuredBuffer<tParticle> g_ParticleBuffer : register(u0);
RWStructuredBuffer<tSpawnCount> g_SpawnCount : register(u1);

#define MAX_COUNT   g_int_0 
#define SpawnCount  g_SpawnCount[0].iSpawnCount
#define Particle    g_ParticleBuffer[id.x]
#define Module      g_Module[0]


[numthreads(32, 1, 1)]
void CS_ParticleUpdate(uint3 id : SV_DispatchThreadID)
{
    if (MAX_COUNT <= id.x)
        return;
    
    // ��ƼŬ�� ��Ȱ��ȭ ���¶��
    if (0 == Particle.Active)
    {
        // ���� ��� Ȱ��ȭ üũ
        if (Module.arrModuleCheck[0])
            return;
        
        while (0 < SpawnCount)
        {
            // Atomic �Լ� 
            int AliveCount = SpawnCount;
            int Exchange = SpawnCount - 1;
            int Origin = 0;
           
            // InterlockedExchange �Լ��� �Ἥ SpawnCount �� ��ü, �����ϸ�
            // �ʱ� �õ��� ���尡 ���� �����尡 ������ ���Ŀ� �����ϴ� ��찡 �ִ�. 
            // �̶� SpawnCount �� ������ �÷������� ������ �߻��� �� �ִ�. 
            // InterlockedCompareExchange �� ���ؼ� ������ ���� ��ġ�� ��쿡�� 
            // ��ü�� �ϵ��� �ϴ� �Լ��� ����Ѵ�.
            InterlockedCompareExchange(SpawnCount, AliveCount, Exchange, Origin);
            
            if (AliveCount == Origin)
            {
                Particle.Active = 1;
                
                // ����
                float2 vUV = float2((1.f / (MAX_COUNT - 1)) * id.x, 0.f);
                                
                float4 vColor = g_NoiseTex.SampleLevel(g_sam_0, vUV, 0);
                        
                // SpawnShape �� Sphere Ÿ���̶��
                if (0 == Module.SpawnShape)
                {
                    float RandomRadius = vColor.x * Module.Radius;
                    
                    // Particle ������Ʈ(��ü) �� �߽���ġ(����) ���� �˾ƾ��Ѵ�.
                    
                    // Space Ÿ�Կ� ���� ��������� �ٸ��� �ؾ��Ѵ�.
                    // 0 : LocalSpace
                    // 1 : WorldSpalce
                    Module.SpaceType;
                }
                
                break;
            }
        }
    }
    
    // ��ƼŬ�� Ȱ��ȭ ���¶��
    else
    {
        Particle.vWorldPos.y += g_dt * 100.f;
    }
}

#endif