#include"../VS_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);


VSOutput main(VSIput input, uint32_t instanceId : SV_InstanceID)
{
    VSOutput output;
	

    output.position = mul(input.position, gTransformform.WVP);
    output.normal = input.normal;
    output.instanceId = instanceId;
    
    return output;
}