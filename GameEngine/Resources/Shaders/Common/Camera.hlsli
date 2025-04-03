struct SCamera
{
    float32_t4x4 mtxProj;
    float32_t4x4 mtxProjInv;
    float32_t4x4 mtxView;
    float32_t4x4 mtxViewInv;
    float32_t4x4 mtxVP;
};