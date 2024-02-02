#ifndef _STRUCT
#define _STRUCT

struct tLightColor
{
    float4 vColor; // ���� ����	- ������ ���� ����
    float4 vSpecular; // �ݻ籤	- ������ ��ü ǥ���� �ݻ�� ����
    float4 vAmbient; // ȯ�汤(�ֺ���) - ������ ���ؼ� ����Ǵ� �ּ����� ��
};

struct tLightInfo
{
    tLightColor Color;

    float3      vWorldPos; // ������ ��ġ
    float3      vWorldDir; // ������ ���ϴ� ����
    float       fRadius; // ������ ���� �ݰ�, �Ÿ� ����
    float       fAngle; // ������ ���� ����

    int         LightType; // ���� Ÿ�� (0 : Directional, 1 : Point, 2 : Spot)
    float3      vPadding;
};


struct tTileInfo
{
    float2  vLeftTopUV;
    int     bRender;
    int     padding;
};

struct tParticle
{
    float4 vWorldPos; // ��ġ
    float4 vWorldScale; // ũ��
    float4 vWorldRotation; // ȸ����
    float4 vVelocity; // �ӵ�
    float4 vColor; // ����

    float Mass; // ����
    float Age; // ���� ����
    float Life; // ����
    int Active; // Ȱ��ȭ, ��Ȱ��ȭ ����
};

#endif
