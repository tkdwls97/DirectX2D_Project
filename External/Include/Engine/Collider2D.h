#pragma once
#include "Component.h"

enum class COLLIDER2D_TYPE
{
	RECT,
	CIRCLE,
};

class CCollider2D : public CComponent
{
public:
	CCollider2D();
	~CCollider2D();

public:
	virtual void Finaltick() override;

public:
	void BeginOverlap(CCollider2D* _OtherCollider);
	void Overlap(CCollider2D* _OtherCollider);
	void EndOverlap(CCollider2D* _OtherCollider);

public:
	void SetAbsolute(bool _bAbsol) { m_bAbsolute = _bAbsol; }
	void SetOffsetRadius(float _fRadius) { m_fOffsetRadius = _fRadius; }
	void SetOffsetPos(Vec2 _vOffset) { m_vOffsetPos = Vec3(_vOffset.x, _vOffset.y, 0.f); }
	void SetOffsetScale(Vec2 _vOffsetScale) { m_vOffsetScale = Vec3(_vOffsetScale.x, _vOffsetScale.y, 1.f); }
	void SetColliderType(COLLIDER2D_TYPE _Type) { m_Type = _Type; }
	const Matrix& GetColliderWorldMat() { return m_matColWorld; }

	bool IsAbsolute() { return m_bAbsolute; }
	Vec2 GetOffsetPos() { return Vec2(m_vOffsetPos.x, m_vOffsetPos.y); }
	float GetOffsetRadius() { return m_fOffsetRadius; }
	Vec2 GetOffsetScale() { return Vec2(m_vOffsetScale.x, m_vOffsetScale.y); }
	int GetCollisionCount() { return m_CollisionCount; }
	COLLIDER2D_TYPE GetType() { return m_Type; }


private:
	Vec3            m_vOffsetPos;
	Vec3            m_vOffsetScale;
	float           m_fOffsetRadius;
	int             m_CollisionCount;   // 다른 충돌체와 충돌중인 횟수
	bool            m_bAbsolute;

	Matrix          m_matColWorld;
	COLLIDER2D_TYPE m_Type;
};

