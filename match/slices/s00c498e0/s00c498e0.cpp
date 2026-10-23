// Slice s00c498e0 (0x00c498e0..0x00c4a7c2) - SP::cSPMission star-map clue /
// reward helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// (SSE scalar float moves, x87 for the length/round, no EH prolog.)

#include "types.h"
#include <math.h>

#pragma warning(disable: 4100)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Forward declarations of the receiver types.
// ---------------------------------------------------------------------------
struct cStarRecord;
struct cCivData;
struct cStarMapVisual;
struct cCivDataRef;
struct AutoRefCountBase;
struct RefObj;

// ---------------------------------------------------------------------------
// External helpers (relocations; verifier masks call targets).
// ---------------------------------------------------------------------------
void* __cdecl FUN_01046fc0(void* key, u32 a);                          // 0x01046fc0
void* __cdecl FUN_01045120(void* a, u32 b);                             // 0x01045120
void* __cdecl FUN_01044d70(void* a, u32 b);                             // 0x01044d70
void* __cdecl CreateStarRecordVisual(void* a, u32 b, u32 c);            // 0x010458f0
void  __cdecl RemoveVisual(void* a, u32 b, u32 c);                      // 0x01045a60
void* __cdecl ColorToVector3(void* out, u32 color);                     // 0x00576ab0
void  __cdecl VectorInsertU32(void* a, void* b, u32 c);                 // 0x004558a0
void  __cdecl VectorPushBack3(void* a, void* b, void* c);               // 0x00455660
void  __cdecl SimpleVectorPushBack(void* self, const u32* v);           // 0x00454860
void  __cdecl operator_delete_array(void* p);                           // 0x00f47380
void* __cdecl GetMissionManager(void* m);                               // 0x00feb9f0
u32   __cdecl FUN_00febf80(void* mgr);                                  // 0x00febf80
void  __cdecl FUN_00febf20(void* mgr, void* m);                         // 0x00febf20
void* __cdecl GetUniverseContext();                                     // 0x01021080
void* __cdecl FUN_01021260();                                           // 0x01021260
void* __cdecl FUN_00bddd00(void* mgr);                                  // 0x00bddd00
void* __cdecl SP_PropertyManager();                                     // 0x0067de30
u32   __cdecl GetPropertyAsText(void* p, u32 key, void* out);           // 0x006a1360
void* __cdecl FUN_006c0200(void* a, void* b);                           // 0x006c0200
void  __cdecl E12_Init(void* out, void* a);                             // 0x00ae9640
void  __cdecl FUN_00ae9670(void* a);                                    // 0x00ae9670
void  __cdecl FUN_00aeb5b0(void* a, void* b);                           // 0x00aeb5b0
void* __cdecl FUN_00c472c0(void* self);                                 // 0x00c472c0
void* __cdecl FUN_010434e0(void* a, void* b);                           // 0x010434e0
void* __cdecl FUN_00b8de30(void* a);                                    // 0x00b8de30
void  __cdecl FUN_00b96130(void* a, void* b, void* c);                  // 0x00b96130
void* __cdecl FUN_00b3d2a0(void* a);                                    // 0x00b3d2a0
void* __cdecl FUN_00bb1080(void* a, void* b, void* c);                  // 0x00bb1080
void* __cdecl Property_GetFloat(void* prop);                           // 0x0041ea70
void* __cdecl GetCities(void* civ, void* a, void* b);                  // 0x005c65e0
void* __cdecl SP_StarManager();                                        // 0x00b3d2a0
void* __cdecl FUN_00bb1080b(void* a);                                   // 0x00bb1080
void  __cdecl FUN_00b96600(void* a, void* b);                           // 0x00b96600
void  __cdecl FUN_00c072f0(void* self, const void* v);                  // 0x00c072f0
void* __cdecl FUN_00e1c7f0(void* vec, void* val);                       // 0x00e1c7f0
void* __cdecl FUN_00aea5d0(void* a, void* b);                           // 0x00aea5d0
void  __cdecl FUN_00ae6970(void* v);                                    // 0x00ae6970
void* __cdecl AutoRefCountCtor(void* self, void* p);                    // 0x00572660
void* __cdecl add_ref_civ(cCivData* p);                                 // 0x00801920
u32   __cdecl FUN_00801920(void* p);                                    // 0x00801920 (AddRef kind)
u32   __cdecl RandomUint32Uniform(void* rng, u32 n);                    // 0x00a68fb0
// the RNG is called as a __thiscall member (ecx = the RNG object).
struct RandomLCG {
    u32 RandomUint32Uniform(u32 n);   // 0x00a68fb0
};
#define gRandom (*(RandomLCG*)0x1601760)
void* __cdecl FUN_00c453b0();                                           // 0x00c453b0 GetRewardProfit
void  __cdecl FUN_00c45760(void* self, void* out);                      // 0x00c45760 PickRewardTool
void  __cdecl FUN_00c495c0(void* self);                                 // 0x00c495c0 PickRewardUnlockTools
void  __cdecl FUN_00e25bd0(void* a, void* b);                           // 0x00e25bd0
void  __cdecl FUN_0050f740(void* a, void* b);                           // 0x0050f740
extern "C" void* memcpy(void* d, const void* s, unsigned n);

// ===========================================================================
// cSPMission: only the fields and virtuals touched by this slice are named.
// Virtual offsets are taken from the disassembly; the vtable is laid out with
// one pointer slot per 4 bytes.
// ===========================================================================
class cSPMission {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void* Cast(u32 type);                     // +0x0c
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1c();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2c();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3c();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4c();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5c();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6c();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7c();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8c();
    virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9c();
    virtual void vfa0(); virtual void vfa4(); virtual void vfa8(); virtual void vfac();
    virtual void vfb0(); virtual void vfb4(); virtual void vfb8(); virtual void vfbc();
    virtual void vfc0(); virtual void vfc4(); virtual void vfc8(); virtual void vfcc();
    virtual void vfd0(); virtual void vfd4(); virtual void vfd8(); virtual void vfdc();
    virtual void vfe0(); virtual void vfe4(); virtual void vfe8(); virtual void vfec();
    virtual int  vf100();                             // +0x100
    virtual void vf104(); virtual void vf108(); virtual void vf10c();
    virtual int  vf110(void* m);                      // +0x110
    virtual void vf114(); virtual void vf118(); virtual void vf11c();
    virtual void vf120(); virtual void vf124(); virtual void vf128(); virtual void vf12c();
    virtual void vf130(); virtual void vf134();
    virtual bool vf138(void* m);                      // +0x138
    virtual void vf13c(); virtual void vf140(); virtual void vf144();
    virtual void vf148(); virtual void vf14c(); virtual void vf150(); virtual void vf154();
    virtual int  vf158();                             // +0x158
    virtual void vf15c(); virtual void vf160(); virtual void vf164(); virtual void vf168();
    virtual void vf16c(); virtual void vf170(); virtual void vf174();
    virtual void vf178(); virtual void vf17c(); virtual void vf180(); virtual void vf184();
    virtual void vf188(); virtual void vf18c();
    virtual void vf190(void* p);                      // +0x190
    virtual void vf194(); virtual void vf198(); virtual void vf19c();
    virtual void vfa0x(); virtual void vfa4x(); virtual void vfa8x();
    virtual void vf1a4(); virtual void vf1a8(); virtual void vf1ac(); virtual void vf1b0();
    virtual void vf1b4(); virtual void vf1b8(); virtual void vf1bc(); virtual void vf1c0();
    virtual void vf1c4(); virtual void vf1c8(); virtual void vf1cc(); virtual void vf1d0();
    virtual void vf1d4(); virtual void vf1d8(); virtual void vf1dc(); virtual void vf1e0();
    virtual void vf1e4(); virtual void vf1e8(); virtual void vf1ec();
    virtual int  vf1f0();                             // +0x1f0

    u8   pad_0000[0x2c];
    void* mGlobalPtr2C;          // +0x2c
    u8   pad_0030[0x88 - 0x30];
    u8   mField88;               // +0x88
    u8   pad_0089[0x8c - 0x89];
    int  mField8C;               // +0x8c
    void* mField90;              // +0x90
    int  mField94;               // +0x94
    void* mField98;              // +0x98
    void* mRewardToolName;       // +0x9c   (mTableId guard)
    u8   pad_00a0[0xc4 - 0xa0];
    int  mFieldC4;               // +0xc4
    float mFieldC8;              // +0xc8
    void* mEventLogs;            // +0xcc (vector begin)
    void* mEventLogsEnd;         // +0xd0
    u8   pad_00d4[0xe0 - 0xd4];
    void* mStarMapEffects;       // +0xe0 (vector begin)
    u8   pad_00e4[0x104 - 0xe4];
    int  mField104;              // +0x104
    u32  mVec108_0;              // +0x108 (vector begin)
    u32  mVec108_1;              // +0x10c
    u32  mVec108_2;              // +0x110
    u8   pad_0114[0x11c - 0x114];
    u32  mVec11c_0;              // +0x11c
    u32  mVec11c_1;              // +0x120
    u8   pad_0124[0x130 - 0x124];
    u32  mFlags130;              // +0x130
    u8   pad_0134[0x17c - 0x134];
    cSPMission* mpParentMission; // +0x17c
    void* mField180;             // +0x180
    u8   pad_0184[0x1e4 - 0x184];
    void* mField1e4;             // +0x1e4
    void* mField1e8;             // +0x1e8

    void ShowStarMapDestinationIndicator(char param);     // 0x00c498e0
    void ShowStarMapStarClues();                          // 0x00c49d10
    void FUN_00c49f90();                                  // 0x00c49f90
    void PickRewards();                                   // 0x00c4a0c0
    int  PickStarClue();                                  // 0x00c4a220
    bool HandleMessage(u32 msg, void* m);                 // 0x00c4a6b0
};

// simple byte-offset helpers against the retail layout
static inline int   ld32(const void* p, int o)  { return *(const int*)((const char*)p + o); }
static inline u32   ldu32(const void* p, int o) { return *(const u32*)((const char*)p + o); }
static inline void  st32(void* p, int o, int v){ *(int*)((char*)p + o) = v; }
static inline void  stb(void* p, int o, u8 v){ *(u8*)((char*)p + o) = v; }
static inline void** vtbl(const void* p)        { return *(void***)p; }

// westl-style vector header: begin/end/capacity pointers.
struct VecHeader { void* begin; void* end; void* cap; };

// ========================================================================
// 0x00c498e0 - 1064 bytes: ShowStarMapDestinationIndicator
// ========================================================================
// @ 0x00c498e0
void cSPMission::ShowStarMapDestinationIndicator(char param)
{
    u8* p = (u8*)this;
    if ((*(char(__thiscall**)(void*))((char*)vtbl(this) + 0x158))(this) != 0) {
        return;
    }
    if (param == 0) {
        u32 f = ldu32(p, 0x130);
        if (((f >> 1) & 1) != 0) {
            return;
        }
    }

    // pop the event-log vector (this+0xcc), removing each visual
    int cnt = (ld32(p, 0xd0) - ld32(p, 0xcc)) >> 2;
    for (int i = cnt; i != 0; i--) {
        int tail = ld32(p, 0xd0);
        u32 v = *(u32*)(tail - 4);
        void* vis = FUN_01046fc0((void*)v, 0);
        RemoveVisual(vis, v, 0);
        st32(p, 0xd0, ld32(p, 0xd0) - 4);
    }

    if (ldu32(p, 0x9c) == 0) {
        return;
    }
    if (ld32(p, 0x1e8) == 0) {
        return;
    }
    void* a = FUN_00b8de30((void*)(ld32(*(void**)((char*)p + 0x9c), 0x13c)));
    int local10 = (int)a;
    if (a == 0) {
        return;
    }
    void* b = FUN_00b8de30((void*)(ld32(*(void**)((char*)p + 0x1e8), 0x13c)));
    int ebx = (int)b;
    if (b == 0) {
        return;
    }
    if (ebx == local10) {
        return;
    }
    if (ld32(p, 0x104) != -1) {
        u32 v = ldu32(p, 0x104);
        void* vis = FUN_01046fc0((void*)v, 0);
        RemoveVisual(vis, v, 0);
        st32(p, 0x104, -1);
    }

    int r = (*(int(__thiscall**)(void*, u32))((char*)vtbl(this) + 0xc))(this, 0x463329e);
    u32 off = (r != 0) ? 0xad67641f : 0;
    u32 color = off + 0x9d157d80;
    void* vis = CreateStarRecordVisual(FUN_01046fc0((void*)ebx, 0x166521a5), (u32)ebx, color);
    int local14 = (int)vis;
    if (vis != 0) {
        FUN_01044d70(FUN_01046fc0(vis, 0), 0);
        SimpleVectorPushBack((char*)p + 0x108, (const u32*)&local14);
    }

    int sel;
    if (param != 0) {
        int t = local10; local10 = ebx; sel = t;
    } else {
        sel = local10; local10 = ebx;
    }
    ebx = sel;

    u32 v = ldu32(p, 0x104);
    void* vis2 = CreateStarRecordVisual(FUN_01046fc0((void*)ebx, 0x166521a5), (u32)ebx, 0x49ca7b6);
    st32(p, 0x104, (int)vis2);
    void* inner = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)ebx, 0x70)), (u32)vis2), (u32)vis2);
    int edi = (int)inner;
    FUN_01044d70(FUN_01046fc0((void*)ldu32(p, 0x104), 0), 0);
    u32 colv = (u32)FUN_00c472c0(this);
    u8 vec[12];
    ColorToVector3(vec, colv);
    (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)edi) + 0x40))((void*)edi, 5, vec, 1);

    void* cities = FUN_00b8de30((void*)(ld32((void*)ebx, 0x13c)));
    float* c0 = (float*)FUN_00bb1080b(cities);
    float baseX = c0[0], baseY = c0[1], baseZ = c0[2];
    float* c1 = (float*)FUN_00bb1080b((void*)local10);
    float dX = c1[0] - baseX;
    float dY = c1[1] - baseY;
    float dZ = c1[2] - baseZ;
    int steps = (int)(long long)(sqrtf(dX*dX + dY*dY + dZ*dZ) * 10.0f);
    int n = steps + 1;
    float len = (float)n;
    float inv = 1.0f / len;
    float stepX = dX * inv, stepY = dY * inv, stepZ = dZ * inv;
    float px = baseX, py = baseY, pz = baseZ;
    u8 pv[12];
    int total = 0;
    for (int i = steps + 1; i != 0; i--) {
        *(float*)(pv) = px; *(float*)(pv+4) = py; *(float*)(pv+8) = pz;
        VectorPushBack3((char*)p + 0x108, &total, pv);
        px += stepX; py += stepY; pz += stepZ;
        total = 0;
    }

    int n2 = (steps + 1) * 3;
    void* vis3 = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)ebx, 0x70)), ldu32(p, 0x104)), ldu32(p, 0x104));
    if (vis3 == 0) {
        return;
    }
    u8 tmp[12];
    (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl(vis3) + 0x44))(vis3, 0xd, tmp, n2);
}

// ========================================================================
//  0x00c49d10 - 631 bytes: ShowStarMapStarClues
// ========================================================================
// @ 0x00c49d10
void cSPMission::ShowStarMapStarClues()
{
    u8* p = (u8*)this;
    int mode = ld32(p, 0xc4) - 0;
    if (mode == 0) {
        goto mode0;
    }
    if (mode - 1 != 0) {
        return;
    }
    {
        u32 v = ldu32(*(void**)((char*)p + 0xe0), 0);
        void* vis = CreateStarRecordVisual(FUN_01046fc0((void*)v, 0x166521a5), v, 0xb7355b47);
        int edi = (int)vis;
        if (vis == 0) return;
        void* inner = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)v, 0x70)), (u32)vis), (u32)vis);
        int vbx = (int)inner;
        FUN_01044d70(FUN_01046fc0(vis, 0), 0);
        VecHeader* vec = (VecHeader*)((char*)p + 0x108);
        if (vec->end < vec->cap) {
            void* old = vec->end;
            vec->end = (char*)vec->end + 4;
            if (old != 0) *(int*)old = edi;
        } else {
            VectorInsertU32(vec->end, &edi, (u32)vec->end);
        }
        float f = *(float*)((char*)p + 0xc8);
        *(float*)0 = 0; (void)f;
        u8 cbuf[4];
        *(float*)cbuf = f;
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x44))((void*)vbx, 1, cbuf, 1);
        void* mgr = GetMissionManager(ld32(p, 0x17c) ? *(void**)((char*)p + 0x17c) : (void*)p);
        u32 colv = FUN_00febf80(mgr);
        u8 vec2[12];
        ColorToVector3(vec2, colv);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x40))((void*)vbx, 5, vec2, 1);
        return;
    }
mode0:
    {
        float f = *(float*)((char*)p + 0xc8);
        u32 v = ldu32(*(void**)((char*)p + 0xe0), 0);
        float eps = *(float*)0x1471064;
        int lo = (int)(f - eps);
        int hi = (int)(f + eps);
        float flo = (float)lo;
        float fhi = (float)hi;
        void* visA = CreateStarRecordVisual(FUN_01046fc0((void*)v, 0x166521a5), v, 0xb7355b47);
        int ebp = (int)visA;
        int local18 = (int)CreateStarRecordVisual(FUN_01046fc0((void*)v, 0x166521a5), v, 0x7ec3db0a);
        if (ebp == 0 || local18 == 0) return;
        void* inner = FUN_01045120(FUN_01046fc0((void*)(ld32((void*)v, 0x70)), (u32)ebp), (u32)ebp);
        int vbx = (int)inner;
        FUN_01044d70(FUN_01046fc0((void*)ebp, 0), 0);
        VecHeader* vec = (VecHeader*)((char*)p + 0x108);
        int iv = ebp;
        SimpleVectorPushBack(vec, (const u32*)&iv);
        u8 fb[4]; *(float*)fb = flo;
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x44))((void*)vbx, 1, fb, 1);
        (void)fhi;
        int edi2 = (int)FUN_01045120(FUN_01046fc0((void*)(ld32((void*)v, 0x70)), (u32)local18), (u32)local18);
        FUN_01044d70(FUN_01046fc0((void*)local18, 0), 0);
        int iv2 = local18;
        SimpleVectorPushBack(vec, (const u32*)&iv2);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)edi2) + 0x44))((void*)edi2, 1, fb, 1);
        void* mgr = GetMissionManager(ld32(p, 0x17c) ? *(void**)((char*)p + 0x17c) : (void*)p);
        u32 colv = FUN_00febf80(mgr);
        u8 vec2[12];
        ColorToVector3(vec2, colv);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)vbx) + 0x40))((void*)vbx, 5, vec2, 1);
        (*(void(__thiscall**)(void*, int, u8*, int))((char*)vtbl((void*)edi2) + 0x40))((void*)edi2, 5, vec2, 1);
    }
}

typedef void (__thiscall* VecEraseFn)(void*, void*, void*);

// vector types whose out-of-line erase() members the original calls.
struct SpVecE0 {
    void* mpBegin; void* mpEnd; void* mpCap;
    void erase(void* first, void* last);   // 0x00e25bd0
};
struct SpVec11C {
    void* mpBegin; void* mpEnd; void* mpCap;
    void erase(void* first, void* last);   // 0x0050f740
};

// ========================================================================
//  0x00c49f90 - 296 bytes: reset/teardown helper
// ========================================================================
// @ 0x00c49f90
void cSPMission::FUN_00c49f90()
{
    u8* p = (u8*)this;
    if (*(u8*)((char*)p + 0x88) == 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(this) + 0x84))(this);
    }
    int minus1 = -1;
    st32(p, 0x8c, minus1);
    st32(p, 0x94, minus1);
    void* q = *(void**)((char*)p + 0x90);
    if (q != 0) { st32(p, 0x90, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x98);
    if (q != 0) { st32(p, 0x98, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x9c);
    if (q != 0) { st32(p, 0x9c, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 0xc0))(q); }
    q = *(void**)((char*)p + 0x1e8);
    if (q != 0) { st32(p, 0x1e8, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 0xc0))(q); }

    // eastl vector<unsigned>::erase(begin, end) fully inlined.
    {
        VecHeader* vec = (VecHeader*)((char*)p + 0xcc);
        void* first = vec->begin;
        void* last  = vec->end;
        void* pEnd  = vec->end;
        memcpy(vec->begin, last, (unsigned)((char*)pEnd - (char*)last));
        int n = (int)((char*)last - (char*)first) >> 2;
        vec->end = (char*)vec->end + (n * -4);
    }
    ((SpVecE0*)((char*)p + 0xe0))->erase(((SpVecE0*)((char*)p + 0xe0))->mpBegin, ((SpVecE0*)((char*)p + 0xe0))->mpEnd);
    ((SpVec11C*)((char*)p + 0x11c))->erase(((SpVec11C*)((char*)p + 0x11c))->mpBegin, ((SpVec11C*)((char*)p + 0x11c))->mpEnd);

    q = *(void**)((char*)p + 0x180);
    if (q != 0) { st32(p, 0x180, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x1e4);
    if (q != 0) { st32(p, 0x1e4, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
    q = *(void**)((char*)p + 0x2c);
    if (q != 0) { st32(p, 0x2c, 0); (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q); }
}

// ========================================================================
//  0x00c4a0c0 - 349 bytes: PickRewards
// ========================================================================
// @ 0x00c4a0c0
void cSPMission::PickRewards()
{
    u8* p = (u8*)this;
    typedef float (__thiscall* GetProfitFn)();
    float profit = ((GetProfitFn)FUN_00c453b0)();
    u32 toolKey[3] = { 0, 0, 0 };
    FUN_00c45760(this, toolKey);
    bool positive = (profit > 0.0f);
    int a = (int)toolKey[0];
    int b = (int)toolKey[1];
    int c = (int)toolKey[2];
    u8 differs;
    if (a == *(int*)0x168e844 && b == *(int*)0x168e848 && c == *(int*)0x168e84c) {
        differs = 0;
    } else {
        differs = 1;
    }
    int percent;
    if (positive && differs) percent = 0x32; else percent = 0x64;
    u8 rollA;
    if (positive) {
        u32 rv = gRandom.RandomUint32Uniform(100);
        rollA = (rv < (u32)percent) ? 1 : 0;
        if (rollA) percent = 0x64;
    } else {
        rollA = 0;
        percent = 0x64;
    }
    u8 rollB = 0;
    if (differs) {
        u32 rv = gRandom.RandomUint32Uniform(100);
        rollB = (rv < (u32)percent) ? 1 : 0;
    }
    if (rollA) {
        *(float*)((char*)p + 0xa0) = profit;
        if (ld32(p, 0x9c) != 0 && ld32(p, 0x1e8) != 0) {
            int r = (*(int(__thiscall**)(void*))((char*)vtbl(this) + 0xec))(this);
            *(float*)((char*)p + 0xa0) = *(float*)((char*)p + 0xa0) + (float)(r * 2);
        }
    }
    if (rollB) {
        st32(p, 0xa4, a);
        st32(p, 0xa8, b);
        st32(p, 0xac, c);
        void* mgr = SP_PropertyManager();
        void* out = 0;
        (*(void(__thiscall**)(void*, int, u32, void**))((char*)vtbl(mgr) + 0x2c))(mgr, ld32(p, 0xa4), 0x30608f0b, &out);
        GetPropertyAsText(out, 0x3068d95d, (char*)p + 0xb0);
    }
    FUN_00c495c0(this);
}

// ========================================================================
//  0x00c4a220 - 1164 bytes: PickStarClue
// ========================================================================
// Builds the candidate star-record list from the empire's cities, walks them
// classifying each via FUN_00801920, adds a matching record to this+0xe0 and
// finishes by setting the clue type in this+0xc4.
// @ 0x00c4a220
int cSPMission::PickStarClue()
{
    u8* p = (u8*)this;
    if (*(void**)((char*)p + 0x1e8) == 0) {
        return 0;
    }
    void* civ = FUN_00b8de30((void*)(ld32(*(void**)((char*)p + 0x1e8), 0x13c)));
    if (civ == 0) {
        return 0;
    }
    int iVar7 = 0;
    void* prop = *(void**)((char*)p + 0x180);
    float sv = *(float*)0x1470f1c;
    int fv = (int)sv;
    if (prop != 0) {
        void* out = 0;
        if ((*(char(__thiscall**)(void*, u32, void**))((char*)vtbl(prop) + 0x24))(prop, 0x6f1f48ff, &out) != 0) {
            if (*(u16*)((char*)out + 0x12) == 0xd) {
                fv = *(int*)Property_GetFloat(out);
            }
        }
    }

    // clue search record (locals at esp+0x34..)
    u8 rec[0x34];
    for (int i = 0; i < 0x34; i++) rec[i] = 0;
    *(u32*)(rec + 0x14) = 0x1fff;
    *(u32*)(rec + 0x18) = 0x3f;
    *(u32*)(rec + 0x20) = 0xbf800000;
    *(u32*)(rec + 0x24) = 0xbf800000;
    *(u32*)(rec + 0x28) = 0xbf800000;
    if (0.0f < (float)fv) {
        *(u32*)(rec + 0x20) = (u32)fv;
    }
    GetCities(civ, rec + 0x1c, rec + 0x0);
    void* star = SP_StarManager();
    FUN_00bb1080(star, rec + 0x1c, rec + 0x0);
    FUN_00b96130(*(void**)(rec + 0x4), *(void**)(rec + 0x8), 0);

    void* pEnd = *(void**)(rec + 0x8);
    void* it = *(void**)(rec + 0x4);
    int local14 = 0;
    int local10 = -1;
    if (it == pEnd) {
        goto LAB_afterloop;
    }
    do {
        void* pc = *(void**)it;
        if (pc == civ) {
            goto LAB_next;
        }
        u32 kind = (u32)FUN_00801920(pc);
        switch (kind) {
        case 1:
            *(u32*)(rec + 0x30) = 6;
            FUN_00c072f0(p, 0);
            AutoRefCountCtor((char*)p + 0x18, pc);
            FUN_00e1c7f0((char*)p + 0xe0, (char*)p + 0x18);
            FUN_01044d70(0, 0);
            iVar7++;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4: case 7: case 8: case 9: case 10: case 0xb: case 0xc:
            local10 = 1;
            local14 = (int)pc;
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        }
LAB_next:
        if (iVar7 > 0) goto LAB_done;
        it = (char*)it + 4;
    } while (it != pEnd);

LAB_afterloop:
    if (*(void**)((char*)p + 0x9c) == 0) goto LAB_cleanup0;
    if (local14 == 0 || local10 == 0) {
        // add a fresh visual
    } else {
        // add using local14
    }
LAB_done:
    if (ld32(p, 0xc4) == -1) {
        void* a = *(void**)((char*)p + 0xe0);
        if (a == 0) goto LAB_cleanup0;
        float d = 0.0f;
        (void)d;
        FUN_010434e0(civ, a);
        if (0) { *(void**)((char*)p + 0xcc) = 0; }
    }
LAB_cleanup0:
    FUN_00ae6970((char*)p + 0xe0);
    return 1;
}

// ========================================================================
//  0x00c4a6b0 - 410 bytes: HandleMessage
// ========================================================================
// `this` is the event-handler sub-object (mission + 0x34).
// @ 0x00c4a6b0
bool cSPMission::HandleMessage(u32 msg, void* m)
{
    u8* p = (u8*)this;
    if (msg > 0x35ec3de) {
        if (msg != 0x4249453) {
            return false;
        }
        u8* a = *(u8**)((char*)m + 0x1c);
        cSPMission* mis = (cSPMission*)((char*)this - 0x34);
        (*(void(__thiscall**)(void*, u8*))((char*)vtbl(mis) + 0x190))(mis, a);
        return true;
    }
    if (msg == 0x35ec3de) {
        if (ld32(p, 0x148) != 0) return true;
        void* c = *(void**)((char*)m + 8);
        if (c == 0) return true;
        if (ld32(c, 0xc) != 0) return true;
        if (ld32(c, 0x38) != (int)0xc8fbf7d7) return true;
        if (ld32(c, 0x3c) != 0x49aa3a54) return true;
        u32 r = (u32)FUN_006c0200(c, (void*)ld32(c, 0x34));
        if ((*(char(__thiscall**)(void*, u32))((char*)vtbl(this) + 0x134))(this, r) == 0) return true;
        u32 r2 = (u32)FUN_006c0200(c, (void*)ld32(c, 0x34));
        int idx = (*(int(__thiscall**)(void*, u32))((char*)vtbl(this) + 0x110))(this, r2);
        if (idx != -1) {
            void* s = (*(void*(__thiscall**)(void*, int))((char*)vtbl(this) + 0xa4))(this, idx);
            u8 buf[12];
            E12_Init(buf, s);
            FUN_00aeb5b0((char*)c + 0x50, buf);
            FUN_00ae9670(buf);
        }
        return true;
    }
    if (msg == 0x248975f) {
        if (GetUniverseContext() != 0) return true;
        if (ld32(p, 0x1b4) != (int)FUN_01021260()) return true;
        cSPMission* mis = (cSPMission*)((char*)this - 0x34);
        void* mgr = GetMissionManager(mis);
        FUN_00febf20(mgr, mis);
        st32(p, 0xfc, ld32(p, 0xfc) | 0x40);
        return true;
    }
    if (msg == 0x2489760) {
        cSPMission* mis = (cSPMission*)((char*)this - 0x34);
        void* mgr = GetMissionManager(mis);
        if (FUN_00bddd00(mgr) != mis) return true;
        void* mgr2 = GetMissionManager(mis);
        FUN_00febf20(mgr2, 0);
        return true;
    }
    return false;
}
