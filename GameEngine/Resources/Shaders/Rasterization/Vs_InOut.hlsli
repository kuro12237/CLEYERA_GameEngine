struct VSInput
{
    float32_t4 position : POSITION0;
    float32_t3 normal : NORMAL0;
};

struct VSOutput
{
    float32_t4 position : SV_POSITION;
    float32_t3 normal : NORMAL0;
    float32_t2 texcoord : TEXCOORD0;
    int32_t instanceId : INSTANCEID0;
};
