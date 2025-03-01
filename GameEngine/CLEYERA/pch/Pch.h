#pragma once

/// コンパイルファイル

#include <cassert>
#include <thread>

#include <cstdint>
#include <format>
#include <wrl.h>

#include <chrono>
#include <numbers>
#include <random>

#include <array>
#include <list>
#include <map>
#include <queue>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <variant>
#include <vector>

#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>

#include <iostream>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#pragma region DirectX

#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxcapi.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <wrl.h>
#pragma comment(lib, "d3dcompiler.lib")

#define DIRECTINPUT_VERSION 0x0800 // DirectInput�̃o�[�W�����w��
#include <Xinput.h>
#include <dinput.h>
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dinput8.lib")

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

#pragma endregion