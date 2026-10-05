// Slice s00742b30 (0x00742b30-0x00743b00): SP::cModelWorld highlight/curve getters/setters.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"

// External callees (masked relocations).
extern "C" void FUN_00741aa0(void* a, void* b);      // 0x741aa0
extern "C" void FUN_00b41ea0();                       // 0xb41ea0
extern "C" void FUN_006ec390(void* a, void* b);       // 0x6ec390
extern "C" void FUN_007403c0(void* p);                // 0x7403c0

// ===========================================================================
// Small getters / comparators / curve accessors.
// ===========================================================================

// @ 0x00743910
uint8_t __cdecl FlagsNotBit0(int param_1)
{
    uint8_t v = *(uint8_t*)(param_1 + 4);
    return (uint8_t)(~v) & 1;
}

// @ 0x00743920  (strict comparator on +0x10 float)
int __cdecl CompareFloatAt10(int param_1, int param_2)
{
    return *(float*)(param_1 + 0x10) > *(float*)(param_2 + 0x10);
}

// @ 0x00743950  SP::cModelWorld::SetTimeScale
void __stdcall SetTimeScale(int param_1, float scale)
{
    if (param_1 != 0) {
        *(float*)(param_1 + 0x114) = scale;
        return;
    }
    *(float*)0x11c = scale;
}

// @ 0x007439b0
int __stdcall OffsetOrE4(int param_1)
{
    if (param_1 != 0)
        return param_1 + 0xdc;
    return 0xe4;
}

// ---------------------------------------------------------------------------
// Highlight-curve entry accessors (stride 0x20, base offset 0x1b4).
// ---------------------------------------------------------------------------
struct cModelWorld56 {
    // @ 0x00743940  vtable adjustor helper
    int Adjustor(int unused);

    // @ 0x007439d0
    void SetCurveSegment(int* a, int* b, int index);

    // @ 0x00743a20
    void GetCurveSegment(int* a, int* b, int index);

    // @ 0x00743a60
    void SetCurveRange(int index, int begin, int end);

    // @ 0x00743a80
    void GetCurveRange(int index, int* begin, int* end);

    // @ 0x00743b00  SP::cModelWorld::ResetHighlightCurve
    void ResetHighlightCurve();

    // @ 0x00742ca0  rbtree-ish insert
    void MapInsert(int* pos, int* value);

    // @ 0x00742cf0
    void SetAnimationResource(int* p);

    // @ 0x00742b30
    void Sub2b30(int a2, int a3);
    // @ 0x00742db0  SP::cModelInstance::ConstructFromGameModelResource
    void ConstructFromGameModelResource(void* a2);
    // @ 0x00742f60
    void Sub2f60(int a2);
    // @ 0x00743030  SP::cModelInstance::GetBoneParents
    int GetBoneParents(void* a2);
    // @ 0x00743150
    void Sub3150(int a2);
    // @ 0x00743270
    void Sub3270(int a2, int a3);
    // @ 0x007434b0
    void Sub34b0(int a2);
};

// @ 0x00743940
int cModelWorld56::Adjustor(int unused)
{
    (void)unused;
    return (int)((char*)this - 0xc);
}

// @ 0x007439d0
void cModelWorld56::SetCurveSegment(int* a, int* b, int index)
{
    char* p = (char*)this + index * 0x20;
    *(int*)(p + 0x1bc) = a[0];
    *(int*)(p + 0x1c0) = a[1];
    *(int*)(p + 0x1c4) = b[0];
    *(int*)(p + 0x1c8) = b[1];
    if (*(int*)(p + 0x1b4) < 0)
        *(int*)(p + 0x1b4) = 0;
}

// @ 0x00743a20
void cModelWorld56::GetCurveSegment(int* a, int* b, int index)
{
    char* p = (char*)this + index * 0x20;
    a[0] = *(int*)(p + 0x1bc);
    a[1] = *(int*)(p + 0x1c0);
    b[0] = *(int*)(p + 0x1c4);
    b[1] = *(int*)(p + 0x1c8);
}

// @ 0x00743a60
void cModelWorld56::SetCurveRange(int index, int begin, int end)
{
    char* p = (char*)this + index * 0x20;
    *(int*)(p + 0x1b4) = begin;
    *(int*)(p + 0x1b8) = end;
}

// @ 0x00743a80
void cModelWorld56::GetCurveRange(int index, int* begin, int* end)
{
    if (begin)
        *begin = *(int*)((char*)this + index * 0x20 + 0x1b4);
    if (end)
        *end = *(int*)((char*)this + index * 0x20 + 0x1b8);
}

// @ 0x00743b00
void cModelWorld56::ResetHighlightCurve()
{
    float v = *(float*)((char*)this + 0x890);
    *(float*)((char*)this + 0x87c) = v;
    *(float*)((char*)this + 0x860) = 0.0f;
}

// @ 0x00742ca0
void cModelWorld56::MapInsert(int* pos, int* value) { (void)pos; (void)value; }

// @ 0x00742cf0
void cModelWorld56::SetAnimationResource(int* p) { (void)p; }

// @ 0x00742b30
void cModelWorld56::Sub2b30(int a2, int a3) { (void)a2; (void)a3; }
// @ 0x00742db0
void cModelWorld56::ConstructFromGameModelResource(void* a2) { (void)a2; }
// @ 0x00742f60
void cModelWorld56::Sub2f60(int a2) { (void)a2; }
// @ 0x00743030
int cModelWorld56::GetBoneParents(void* a2) { (void)a2; return 0; }
// @ 0x00743150
void cModelWorld56::Sub3150(int a2) { (void)a2; }
// @ 0x00743270
void cModelWorld56::Sub3270(int a2, int a3) { (void)a2; (void)a3; }
// @ 0x007434b0
void cModelWorld56::Sub34b0(int a2) { (void)a2; }
