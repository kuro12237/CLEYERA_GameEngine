#pragma once

namespace CLEYERA {

namespace Graphics {

namespace Shader {

/// <summary>
/// シェーダーの種類
/// </summary>
enum class ShaderMode {

   PS,
   VS,
   DS,
   HS,
   GS,
   CS,
   RAYGEN,
   MISS,
   CLOSEST_HIT,
   ANY_HIT,
   INTERSECTION
};
}
} // namespace Graphics
} // namespace CLEYERA