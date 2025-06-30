#include "UtilFunc.h"

uint32_t CalcDeltaTime(float &flame) {

   flame += 1.0f / 60.0f;
   if (flame >= 1.0f) {
      flame = 0.0f;
      return 1;
   }
   return 0;
}
