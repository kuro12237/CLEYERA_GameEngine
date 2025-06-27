#include"../VS_InOut.hlsli"
#include"../PS_Output.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"


Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);


PS2dOutput main(VS2dOutput input)
{
    PS2dOutput output;
    
    output.color.rgba = gTexture.Sample(gSampler, input.texcoord);
    
    
    return output;
}
