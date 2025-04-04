#include"LineDraw.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"


PSOutput main(VSOutput input)
{
    PSOutput output;
 
    output.color = float32_t4(0.0f, 0.0f, 1.0f, 1.0f);
    
    return output;
}
