struct VSInput
{
    float32_t4 position : POSITION0;
    uint vertexId : SV_VertexID;
};
struct VSOutput
{
    float32_t4 position : SV_POSITION;
};

struct PSOutput
{
    float32_t4 color : SV_TARGET0;
};