#pragma once


#include <stdlib.h>
#include <Windows.h>
#include <string>

using std::wstring;
using std::string;



#include <wrl.h>
using namespace Microsoft::WRL;

// Directx 11 ��� �� ���̺귯�� ����
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")



// SimpleMath
#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;




// ���� ��� ����
#include "singleton.h"
#include "define.h"
#include "struct.h"