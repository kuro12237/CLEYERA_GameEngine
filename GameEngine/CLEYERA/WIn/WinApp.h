#pragma once
#include "../SystemLogManager/ISystemObserver.h"

namespace CLEYERA::Base::Win {

class WinApp {
public:
  static WinApp *GetInstance();

  /// <summary>
  ///
  /// </summary>
  void Create();

  /// <summary>
  ///
  /// </summary>
  void Finalize();

  /// <summary>
  ///
  /// </summary>
  /// <returns></returns>
  bool WinMsg();

#pragma region Get

  static int32_t GetKWindowWidth() { return kWindowWidth; }
  static int32_t GetKWindowHeight() { return kWindowHeight; }
  
  HWND GetHWND() { return hwnd_; }
#pragma endregion

private:
  /// <summary>
  ///
  /// </summary>
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam,
                                     LPARAM lparam);

  static const int32_t kWindowWidth = 1280;
  static const int32_t kWindowHeight = 720;

  MSG msg{};
  WNDCLASS wc_{};
  HWND hwnd_ = {};
  HWND DebugHwnd_{};

  WinApp() = default;
  ~WinApp() = default;
  WinApp(const WinApp &) = delete;
  const WinApp &operator=(const WinApp &) = delete;
};
} // namespace CLEYERA::Base::Win