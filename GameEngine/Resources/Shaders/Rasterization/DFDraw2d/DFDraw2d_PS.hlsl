#include"../VS_InOut.hlsli"
#include"../PS_Output.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"


Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

ConstantBuffer<WtTransform> gTransformform : register(b1);
ConstantBuffer<SCamera> gCamera : register(b2);

PS2dOutput main(VS2dOutput input)
{
    PS2dOutput output;

    output.color.rgb = input.position.xyz;
    output.color.a = 1.0f;
    
    return output;
}
