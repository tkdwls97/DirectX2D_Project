#ifndef _STRUCT
#define _STRUCT

struct tLightInfo
{
    float4 vColor; // ���� ����	- ������ ���� ����
    float4 vSpecular; // �ݻ籤	- ������ ��ü ǥ���� �ݻ�� ����
    float4 vAmbient; // ȯ�汤(�ֺ���) - ������ ���ؼ� ����Ǵ� �ּ����� ��

    float3 vWorldPos; // ������ ��ġ
    float3 vWorldDir; // ������ ���ϴ� ����
    float fRadius; // ������ ���� �ݰ�, �Ÿ� ����
    float fAngle; // ������ ���� ����

    int LightType; // ���� Ÿ��
    float3 vPadding;
};


#endif
