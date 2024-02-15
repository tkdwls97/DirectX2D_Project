#pragma once


enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
};


enum class ASSET_TYPE
{
	MESH,
	MESHDATA,
	TEXTURE,
	MATERIAL,
	SOUND,
	COMPUTE_SHADER,
	GRAPHICS_SHADER,
	END,
};
extern const char* ASSET_TYPE_STRING[(UINT)ASSET_TYPE::END];

enum class COMPONENT_TYPE
{
	TRANSFORM,	// ������Ʈ�� ��ġ,ũ��,ȸ��

	COLLIDER2D,	// 2���� �浹ü
	COLLIDER3D, // 3���� �浹ü

	ANIMATOR2D,	// ��������Ʈ Animation
	ANIMATOR3D,	// Bone Skinning Animation

	LIGHT2D,	// 2���� ����
	LIGHT3D,	// 3���� ����

	CAMERA,		// ī�޶� ���

	// Render Component
	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	SKYBOX,
	DECAL,
	LANDSCAPE,

	END,

	SCRIPT,
};

enum class PARTICLE_MODULE
{
	SPAWN,				// ��ƼŬ ���� ����
	DRAG,				// ���� ���� ���
	SCALE,				// ũ�� ��ȭ ���
	ADD_VELOCITY,		// �ʱ� �ӵ� ���� ���
	NOISE_FORCE,
	CALCULATE_FORCE,	// �־��� ���� ����ϴ� ���
	RENDER,				// ������ ���� �ɼ� ����

	END,
};

enum class PROJ_TYPE
{
	ORTHOGRAPHIC, // ���� ����
	PERSPECTIVE,  // ���� ����
};


// ������� ����
enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL_CONST,
	ANIM2D_DATA,
	GLOBAL_DATA,
	ANIMATION,

	END,
};

// Rasterizer State Type
enum class RS_TYPE
{
	CULL_BACK,		// �ո� O �޸� X
	CULL_FRONT,		// �ո� x �޸� O
	CULL_NONE,		// �ո� O �޸� O
	WIRE_FRAME,		// ������ �����ϴ� ���θ� ����

	END,
};

// DepthStencil State Type
enum class DS_TYPE
{
	LESS,				// ������ ���			���� ��� O	
	LESS_EQUAL,			// �۰ų� ������ ���		���� ��� O  

	GRATER,				// �� �ָ� ���			���� ��� O
	GRATER_EQUAL,		// �� �ְų� ������ ���	���� ��� O

	NO_TEST,			// ���� �׽�Ʈ X			���� ��� O
	NO_WRITE,			// ���� �׽�Ʈ O			���� ��� X

	NO_TEST_NO_WRITE,	// ���� �׽�Ʈ X			���� ��� X

	END,
};

// Blend State
enum class BS_TYPE
{
	DEFAULT,
	ALPHA_BLEND,
	ONE_ZERO,
	ONE_ONE,
	END,
};

// Task
enum class TASK_TYPE
{
	// Param1 : Layer Index, Param2 : Object Adress
	CREATE_OBJECT,

	// Param1 : Object Adress
	DELETE_OBJECT,

	// Param1 : LEVEL_TYPE
	LEVEL_CHANGE,

	// Param1 : Parent Object, Param2 : Child Object
	ADD_CHILD,

	// Param1 : Parent Object, Param2 : Child Object
	DISCONNECT_PARENT,
};

// Debug Object
enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	CROSS,

	CUBE,
	SPHERE,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
};

enum class SHADER_DOMAIN
{
	DOMAIN_OPAQUE,			// ������
	DOMAIN_MASKED,			// ������ or ����
	DOMAIN_TRANSPARENT,		// ������
	DOMAIN_POSTPROCESS,		// ��ó��

	DOMAIN_DEBUG,
};

// ScalarParam
enum SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,
};

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEXCUBE_0,
	TEXCUBE_1,

	TEXARR_0,
	TEXARR_1,

	END,
};

// Key Value
enum KEY
{
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	TAB,
	LSHIFT,
	LALT,
	LCTRL,
	SPACE,

	ESC,
	ENTER,
	BACK,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	KEY_END,
};

enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};
