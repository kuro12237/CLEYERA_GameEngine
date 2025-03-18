#include"../VS_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);


VSOutput main(VSInput input)
{
    VSOutput output;
	

    output.position = mul(input.position, gTransformform.WVP);
    output.normal = input.normal;
    output.instanceId = 0;
    
    return output;
}