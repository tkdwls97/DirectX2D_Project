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

enum class COMPONENT_TYPE
{
	TRANSFORM,	// 오브젝트의 위치,크기,회전

	COLLIDER2D,	// 2차원 충돌체
	COLLIDER3D, // 3차원 충돌체

	ANIMATOR2D,	// 스프라이트 Animation
	ANIMATOR3D,	// Bone Skinning Animation

	LIGHT2D,	// 2차원 광원
	LIGHT3D,	// 3차원 광원

	CAMERA,		// 카메라 기능

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

enum class PROJ_TYPE
{
	ORTHOGRAPHIC, // 직교 투영
	PERSPECTIVE,  // 원근 투영
};


// 상수버퍼 종류
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
	CULL_BACK,		// 앞면 O 뒷면 X
	CULL_FRONT,		// 앞면 x 뒷면 O
	CULL_NONE,		// 앞면 O 뒷면 O
	WIRE_FRAME,		// 정점을 연결하는 라인만 보임

	END,
};

// DepthStencil State Type
enum class DS_TYPE
{
	LESS,				// 작은게 통과			깊이 기록 O	
	LESS_EQUAL,			// 작거나 같으면 통과		깊이 기록 O  

	GRATER,				// 더 멀면 통과			깊이 기록 O
	GRATER_EQUAL,		// 더 멀거나 같으면 통과	깊이 기록 O

	NO_TEST,			// 깊이 테스트 X			깊이 기록 O
	NO_WRITE,			// 깊이 테스트 O			깊이 기록 X

	NO_TEST_NO_WRITE,	// 깊이 테스트 X			깊이 기록 X

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
