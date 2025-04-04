#include"LineDraw.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);
StructuredBuffer<float32_t3> gLine : register(t0);

VSOutput main(VSInput input, uint32_t instanceId : SV_InstanceID)
{
    VSOutput output;
    
    float32_t4x4 resultMatrix = mul(gTransformform.worldmat, gCamera.mtxVP);

    output.position = mul(float32_t4(gLine[input.vertexId + (instanceId * 2)].xyz, 1.0f), gTransformform.VPV);
   
    return output;
}