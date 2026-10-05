// Slice 11: nSPSkinner paint-request setters/factories and related helpers.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* FUN_00507c70(void* p);              // 0x00507c70
void* FUN_00529d30(void* p);              // 0x00529d30
void  FUN_00523690(void* self);           // 0x00523690
void  FUN_00522b40(void* self, void* a, void* b);  // 0x00522b40
void  RefCountTemplate_Release(void* p);  // 0x00453540

extern float g_userColors[3];             // 0x015df0f0
extern float g_userColors2[3];            // 0x015df204

struct PaintReq {
    void Set(int a2, int a3, int a4, int a5, char a6, char a7, char a8);
};
struct Factory {
    void* Make();
};

// @ 0x00522ad0
void PaintReq::Set(int a2, int a3, int a4, int a5, char a6, char a7, char a8)
{
    *(int*)((char*)this + 0x68) = a2;
    *(int*)((char*)this + 0x6c) = a3;
    *(int*)((char*)this + 0x70) = a4;
    *(int*)((char*)this + 0x74) = a5;
    *(char*)((char*)this + 0x78) = a6;
    *(char*)((char*)this + 0x79) = a7;
    *(char*)((char*)this + 0x7a) = a8;
}

// @ 0x00523570
void* Factory::Make()
{
    void* mem = EA_alloc(0x1d0, "Skinner", 0, 0, 0, 0);
    void* result;
    if (mem != 0)
        result = FUN_00507c70(this);
    else
        result = 0;
    return result;
}

// @ 0x005229c0
void FUN_005229c0(int idx, float* v)
{
    int* g1 = (int*)((char*)g_userColors + idx * 0xc);
    g1[0] = *(int*)&v[0];
    g1[1] = *(int*)&v[1];
    g1[2] = *(int*)&v[2];
    float tmp[3];
    tmp[0] = v[0];
    tmp[1] = v[1];
    tmp[2] = v[2];
    int* r = (int*)FUN_00529d30(tmp);
    int* g2 = (int*)((char*)g_userColors2 + idx * 0xc);
    g2[0] = r[0];
    g2[1] = r[1];
    g2[2] = r[2];
}

// @ 0x00522800 -- PARTIAL skeleton (444-byte /Od body not reconstructed)
void FUN_00522800(void* self) { (void)self; }
// @ 0x00522b40 nSPSkinner::cPaintSystem::SetCreatureSkin -- PARTIAL skeleton
void FUN_00522b40(void* self) { (void)self; }
// @ 0x005235c0 -- PARTIAL skeleton (203-byte /Od body not reconstructed)
void FUN_005235c0(void* self) { (void)self; }
// @ 0x00522a40 -- PARTIAL skeleton (135-byte /Od body: request complete + release)
void FUN_00522a40(void* self) { (void)self; }
