RaytracingAccelerationStructure gRtScene : register(t0);

struct SCamera
{
    float32_t4x4 mtxProj;
    float32_t4x4 mtxProjInv;
    float32_t4x4 mtxView;
    float32_t4x4 mtxViewInv;
};

ConstantBuffer<SCamera> gCamera : register(b0);
RWTexture2D<float4> gOutput : register(u0);

struct Vertex
{
    float3 Position;
    float3 normal;
};
// Local Root Signature (for HitGroup)
StructuredBuffer<uint> indexBuffer : register(t0, space1);
StructuredBuffer<Vertex> vertexBuffer : register(t1, space1);

struct Payload
{
    float3 color;
};
struct MyAttribute
{
    float2 barys;
};

[shader("raygeneration")]
void mainRayGen()
{
    uint2 launchIndex = DispatchRaysIndex().xy;
    float2 dims = float2(DispatchRaysDimensions().xy);
    
    float2 d = (launchIndex.xy + 0.5) / dims.xy * 2.0 - 1.0;
    float aspect = dims.x / dims.y;

    matrix mtxViewInv = gCamera.mtxViewInv;
    matrix mtxProjInv = gCamera.mtxProjInv;

    RayDesc rayDesc;
    rayDesc.Origin = mul(mtxViewInv, float4(0, 0, 0, 1)).xyz;

    float4 target = mul(mtxProjInv, float4(d.x, -d.y, 1, 1));
    rayDesc.Direction = mul(mtxViewInv, float4(target.xyz, 0)).xyz;

    rayDesc.TMin = 0;
    rayDesc.TMax = 100000;

    Payload payload;
    payload.color = float3(0, 0, 0.5);

    RAY_FLAG flags = RAY_FLAG_NONE;
    uint rayMask = 0xFF;

    TraceRay(
        gRtScene,
        flags,
        rayMask,
        0, // ray index
        1, // MultiplierForGeometryContrib
        0, // miss index
        rayDesc,
        payload);
    float3 col = payload.color;

    // 結果格納.
    gOutput[launchIndex.xy] = float4(col, 1);
}

[shader("miss")]
void mainMS(inout Payload payload)
{
    payload.color = float3(0.0, 0.0, 0.0);
}


inline float3 CalcBarycentrics(float2 barys)
{
    return float3(
        1.0 - barys.x - barys.y,
        barys.x,
        barys.y);
}

Vertex GetHitVertex(MyAttribute attrib)
{
    Vertex v = (Vertex) 0;
    float3 barycentrics = CalcBarycentrics(attrib.barys);
    uint vertexId = PrimitiveIndex() * 3; // Triangle List のため.

    float weights[3] =
    {
        barycentrics.x, barycentrics.y, barycentrics.z
    };
    for (int i = 0; i < 3; ++i)
    {
        uint index = indexBuffer[vertexId + i];
        float w = weights[i];
        v.Position += vertexBuffer[index].Position * w;
        v.normal += vertexBuffer[index].normal * w;
    }
    v.normal = normalize(v.normal);
    return v;
}


[shader("closesthit")]
void mainCHS(inout Payload payload, MyAttribute attrib)
{
    Vertex vtx = GetHitVertex(attrib);
    payload.color.rgb = float32_t3(1.0f,0.0f,0.0f);
}
