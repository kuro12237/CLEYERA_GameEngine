#pragma once
#include"pch/Pch.h"

namespace CLEYERA {

namespace Util {

class InputController {
 public:
   InputController() {};
   ~InputController() {};

   void Init();

   void Begin();


   /// <summary>
   /// Lstic
   /// </summary>
   /// <param name="mode"></param>
   /// <returns></returns>
   Math::Vector::Vec2 GetJoyLStickPos(const float &mode = SHRT_MAX);


   /// <summary>
   /// Rstic
   /// </summary>
   /// <param name="mode"></param>
   /// <returns></returns>
   Math::Vector::Vec2 GetJoyRStickPos(const float &mode = SHRT_MAX);


 private:
   XINPUT_STATE joyState_{};
   XINPUT_STATE preJoyState_{};

};


}
} // namespace CLEYERA