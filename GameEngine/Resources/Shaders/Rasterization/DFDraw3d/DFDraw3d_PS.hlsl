#include"../VS_InOut.hlsli"
#include"../PS_Output.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"


PSOutput main(VSOutput input)
{
    PSOutput output;
 
    output.color = float32_t4(1.0f, 1.0f, 1.0f, 1.0f);
    
    return output;
}
