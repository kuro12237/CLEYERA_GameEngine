#include"../VS_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);


VSOutput main(VSInput input, uint32_t instanceId : SV_InstanceID)
{
    VSOutput output;
    
    float32_t4x4 resultMatrix = mul(gTransformform.worldmat, gCamera.mtxVP);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = float32_t2(input.position.x, input.position.y);
    output.normal = input.normal;
    output.instanceId = instanceId;
    
    return output;
}