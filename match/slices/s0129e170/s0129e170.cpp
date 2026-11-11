// Slice s0129e170 -- a four-float global cleared to zero by one generated initializer.
// flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

struct Vec4f {
    float x, y, z, w;
};

extern Vec4f g_clearVec129e170;                                             // 0x0165f3990

// @ 0x0129e170
void ClearVec129e170()
{
    g_clearVec129e170.x = 0.0f;
    g_clearVec129e170.y = 0.0f;
    g_clearVec129e170.z = 0.0f;
    g_clearVec129e170.w = 0.0f;
}
