#pragma once


// 3���� ������ ��ġ�Ǵ� ����
struct Vtx
{
	Vec3 vPos;		 // ������ ��ǥ	
	Vec4 vColor;	 // ������ ���� ����
	Vec2 vUV;		 // UV ��ǥ�� or Texture Coodinate
};


// ==================
// ������� ���� ����ü
// ==================
struct tTransform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;
};


extern tTransform g_Transform;