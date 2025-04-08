#pragma once
#include "../../pch/Pch.h"

#include "InputKeybord.h"

namespace CLEYERA {

namespace Manager {

class InputManager {
 public:
   static InputManager *GetInstance() {
      static InputManager instance;
      return &instance;
   };

   void Init();
   void Finalize();

   void Begin();

   /// <summary>
   /// 押されているか
   /// </summary>
   /// <param name="keyNum"></param>
   /// <returns></returns>
   bool PushKey(uint8_t keyNum) { return keyBord_->PushKey(keyNum); };

   /// <summary>
   /// 一瞬　押したか
   /// </summary>
   bool PushKeyPressed(uint32_t keyNum) { return keyBord_->PushKeyPressed(keyNum); };

 private:
   std::unique_ptr<Util::InputKeyBord> keyBord_ = nullptr;

#pragma region Singleton

   InputManager() = default;
   ~InputManager() = default;
   InputManager(const InputManager &) = delete;
   InputManager &operator=(const InputManager &) = delete;

#pragma endregion
};

} // namespace Manager

} // namespace CLEYERA