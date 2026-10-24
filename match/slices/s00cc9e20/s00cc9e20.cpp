// Slice s00cc9e20 (cl2 #37): SP::cTribeDisplayStrategy / SP::cPosseSet tribe-UI
// helpers (0x00cc9e20..0x00ccafe1).
//
// Retail layouts recovered from the asm (see s00ccdd70 for the full map):
//   cTribeDisplayStrategy:
//     +0x1c  cModelInstanceSet free-list head          +0x2c allocator index
//     +0x70  civ minimap window (cSPUIMinimapWin*)
//     +0x74  UI layout object
//     +0x78  posse set (cPosseSet*)
//     +0x94  eastl::map<unsigned,...> header, +0x98 anchor, +0x9c end
//     +0xb8  cModelInstanceSet[2] (stride 0x60); slot 0 has a sp_vector at +0xc4
//     +0x178 the two ornament arrays (stride 0xA0), +0x218 the ground-spear arrays
//   cPosseSet:
//     +0x08..+0x1c six AutoRefCount<cSPUIPosse> slots, +0x1c free-list, +0x2c alloc
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH prologue in the original).
#include "types.h"

#pragma warning(disable: 4100)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// external helpers (relocations; the verifier masks call targets)
// ---------------------------------------------------------------------------
void* __cdecl FUN_009512c0();                                        // 0x009512c0
void* __cdecl FUN_009512d0(u32 size, u32 align, const char* what);   // 0x009512d0
void* __cdecl op_new(u32 size, const char* file, int a, int b, const char* what, int line); // 0xf473a0
// ecx-taking citizen helpers (called with mov ecx,X; call).
struct CCitizenOps {
    char  FUN_00c0b770();                             // 0x00c0b770
    u32   FUN_00c22dc0();                             // 0x00c22dc0
    void* FUN_00c22f50();                             // 0x00c22f50 GetTribe
    char  FUN_00c232d0();                             // 0x00c232d0 IsLeader
};
#define CIT(p) ((CCitizenOps*)(p))
void* __cdecl FUN_00cc8830(void* citizen);                           // 0x00cc8830
// ecx-taking helpers modelled as members of a placeholder struct.
struct CPosseSetOps {
    char  FUN_00cc9360();                             // 0x00cc9360
    void  FUN_00e26a90(int a);                        // 0x00e26a90
    void  FUN_00e21960();                             // 0x00e21960
    void  FUN_00e28230();                             // 0x00e28230
    void  FUN_00cc8be0();                             // 0x00cc8be0
    void* FUN_00e24c90(void* citizen);                // 0x00e24c90
    void* FUN_00cc88e0(u32 key);                      // 0x00cc88e0
    void* FUN_00cc90a0(u32 key);                      // 0x00cc90a0
    void  FUN_00cc90f0(void* a, void* b);             // 0x00cc90f0
};
#define POSSE(p) ((CPosseSetOps*)(p))
// ecx-taking helpers on the strategy object itself.
struct CStrategyOps {
    void  FUN_00cc8ed0(void* b);                      // 0x00cc8ed0
    void  FUN_00cc8a30(void* pose, void* citizen);    // 0x00cc8a30
};
#define STRAT(p) ((CStrategyOps*)(p))
void  __cdecl FUN_00e0f9c0(void* minimap, void* a, int b, int c);    // 0x00e0f9c0 RemoveIcon
void  __cdecl FUN_00e10580(void* minimap, void* a, void* b, int c, int d); // 0x00e10580 AddIcon
void* __cdecl FUN_00e25710(void* mem);                               // 0x00e25710 cSPUIPosse ctor
void  __cdecl FUN_00e5c780(void* map, void* out, void* key);         // 0x00e5c780 rbtree::find
void* __cdecl FUN_00921580(void* node);                              // 0x00921580 RBTreeIncrement
void* __cdecl FUN_00bca2c0();                                        // 0x00bca2c0 FirstPending
void* __cdecl FUN_00cca0c0(void* p);                                 // 0x00cca0c0
void* __cdecl FUN_00c9cec0(u32 id);                                  // 0x00c9cec0
void* __cdecl FUN_008061c0(void* layout, u32 id);                    // 0x008061c0 GetImageFromLayout
void* __cdecl FUN_00b3d300();                                        // 0x00b3d300 NounManager
void* __cdecl FUN_00bfc5f0(void* nounManager);                       // 0x00bfc5f0 GetPlayerTribe
char  __cdecl FUN_00c8e870(void* tribe);                             // 0x00c8e870
char  __cdecl FUN_00c8e850(void* tribe);                             // 0x00c8e850
void* __cdecl FUN_00cd40b0();                                        // 0x00cd40b0 cTribeModeStrategy::Instance
void  __cdecl FUN_006b5770(void* self, u32 a, u32 b, const wchar_t* s); // cString ctor 0x6b5770
const wchar_t* __cdecl FUN_006b55c0(void* self);                     // cString::GetText 0x6b55c0
void  __cdecl FUN_006b5240(void* self);                              // cString dtor 0x6b5240
// ecx-taking helpers on sub-objects.
struct CTransformOps { void* Assign(const void* src); };              // 0x537dc0
struct CModelInstSet { void  Update(); };                             // 0x6f3b70
// eastl pool/free-list container (ecx-taking).
struct CPool {
    void* FUN_00ccad10(u8* payload);                  // 0x00ccad10
    void* FUN_00cca170(void* payload);                // 0x00cca170
};

extern "C" void* memset(void* d, int c, unsigned n);
extern "C" void* memcpy(void* d, const void* s, unsigned n);

// ---------------------------------------------------------------------------
// UI widget model: only the vtable slots this slice calls are named.
// ---------------------------------------------------------------------------
struct UIObj {
    virtual void vf00();                              // +0x00
    virtual void vf04();                              // +0x04
    virtual void vf08();                              // +0x08
    virtual void* vf0c(u32 id);                       // +0x0c
    virtual void vf10(); virtual void vf14(); virtual void vf18();
    virtual void* vf1c();                             // +0x1c
    virtual void* vf20(int a);                        // +0x20
    virtual void vf24(); virtual void vf28();
    virtual void vf2c(); virtual void vf30(); virtual void vf34(); virtual void vf38();
    virtual void vf3c(); virtual void vf40(); virtual void vf44(); virtual void vf48();
    virtual void vf4c(); virtual void vf50(); virtual void vf54();
    virtual void* vf58();                             // +0x58
    virtual void vf5c(); virtual void vf60(); virtual void vf64(); virtual void vf68();
    virtual void vf6c(); virtual void vf70(); virtual void vf74(); virtual void vf78();
    virtual void vf7c(int a, int b);                  // +0x7c
    virtual void vf80(u32 msg, float f, int a, int b);// +0x80
    virtual void vf84(); virtual void vf88(u32 v);    // +0x88
    virtual void vf8c();
    virtual void vf90(); virtual void vf94(u32 v, int a); // +0x94
    virtual void vf98();
    virtual void vf9c(u32 msg, void* p, int a);       // +0x9c
    virtual void vfa0(); virtual void vfa4(int v);    // +0xa4
    virtual void vfa8(void* p, int v);                // +0xa8
    virtual void vfac(); virtual void vfb0(); virtual void vfb4();
    virtual void vfb8(int v);                         // +0xb8
    virtual void vfbc(); virtual void vfc0();
    virtual void vfc4(float f);                       // +0xc4
};

// ---------------------------------------------------------------------------
// SP::cPosseSet / SP::cTribeDisplayStrategy - only the fields this slice uses.
// ---------------------------------------------------------------------------
struct cPosseSet {
    u8    pad_00[0x1c];
    void* mpFreeList;                                 // +0x1c
    u8    pad_20[0x2c - 0x20];
    u32   mAllocIndex;                                // +0x2c

    void Init();                                      // 0x00cca230
};

struct cTribeDisplayStrategy {
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void vf0c(); virtual void vf10(); virtual void vf14(); virtual void vf18();
    virtual void vf1c(); virtual void vf20(); virtual void vf24(); virtual void vf28();
    virtual void vf2c(); virtual void vf30(); virtual void vf34(); virtual void vf38();
    virtual void vf3c(); virtual void vf40(); virtual void vf44(); virtual void vf48();
    virtual void vf4c(); virtual void vf50(); virtual void vf54(); virtual void vf58();
    virtual void vf5c(); virtual void vf60(); virtual void vf64(); virtual void vf68();
    virtual void* GetDisplayStrategy();               // +0x6c

    u8    pad_1c_pre[0x1c - 0x04];
    void* mpFreeList;                                 // +0x1c
    u8    pad_20[0x2c - 0x20];
    u32   mAllocIndex;                                // +0x2c
    u8    pad_30[0x70 - 0x30];
    void* mpMinimap;                                  // +0x70
    void* mpLayout;                                   // +0x74
    void* mpPosseSet;                                 // +0x78
    u8    pad_7c[0x94 - 0x7c];
    u32   mMapCount;                                  // +0x94 (eastl map header)
    void* mMapAnchor;                                 // +0x98
    void* mMapEnd;                                    // +0x9c

    void FUN_00cc9e20(void* citizen);                 // 0x00cc9e20
    void FUN_00cca060();                              // 0x00cca060
    char FUN_00cca090();                              // 0x00cca090
    void FUN_00cca0a0();                              // 0x00cca0a0
    u32  FUN_00cca3d0(void* citizen);                 // 0x00cca3d0
    void SetPosseActivity(void* key, int activity);   // 0x00cca5b0
    void FUN_00cca880(void* citizen, int a);          // 0x00cca880
    char SetGroundSpearTransform(char slot, u32 index, const void* xform, char ref); // 0x00cca9e0
    void FUN_00ccaa80(void* arg);                     // 0x00ccaa80
    void FUN_00ccab80();                              // 0x00ccab80
};

// ---------------------------------------------------------------------------
// byte-offset helpers
// ---------------------------------------------------------------------------
static inline int   ld32(const void* p, int o)  { return *(const int*)((const char*)p + o); }
static inline u32   ldu32(const void* p, int o) { return *(const u32*)((const char*)p + o); }
static inline u8    ldu8(const void* p, int o)  { return *(const u8*)((const char*)p + o); }
static inline void  st32(void* p, int o, int v){ *(int*)((char*)p + o) = v; }
static inline void  stb(void* p, int o, u8 v)  { *(u8*)((char*)p + o) = v; }
static inline void** vtbl(const void* p)       { return *(void***)p; }
static inline u8*   at(void* p, int o)         { return (u8*)p + o; }

// ===========================================================================
// 0x00cc9e20 - 478 bytes: CreateMinimapIcon
// ===========================================================================
// @ 0x00cc9e20
void cTribeDisplayStrategy::FUN_00cc9e20(void* citizen)
{
    u8* p = (u8*)this;
    u8* c = (u8*)citizen;
    if (ld32(p, 0x70) != 0 && CIT(citizen)->FUN_00c22f50() != 0) {
        FUN_00e0f9c0(*(void**)((char*)p + 0x70), citizen, 1, 0);

        u8 rec[0x20];
        *(u32*)(rec + 0x00) = 0;
        *(u32*)(rec + 0x04) = 0;
        *(u32*)(rec + 0x08) = 0;
        *(u32*)(rec + 0x0c) = 0xbf800000;
        *(u32*)(rec + 0x10) = 0x2008;
        *(u32*)(rec + 0x14) = 0;
        *(u32*)(rec + 0x18) = 0;
        *(u32*)(rec + 0x1c) = 0;

        float* col = (float*)(*(void*(__thiscall**)(void*))((char*)vtbl(c) + 0xe0))((void*)c);
        u32 r = (u32)(long long)(col[0] * 255.0f);
        u32 g = (u32)(long long)(col[1] * 255.0f);
        u32 b = (u32)(long long)(col[2] * 255.0f);
        *(u32*)(rec + 0x00) = ((((r | 0xffffff00) << 8) | (g & 0xff)) << 8) | (b & 0xff);

        u8* pos = (u8*)(*(void*(__thiscall**)(void*))((char*)vtbl(c) + 0xc0))((void*)c);
        *(u32*)(rec + 0x04) = *(u32*)(pos + 0x00);
        *(u32*)(rec + 0x08) = *(u32*)(pos + 0x04);
        *(u32*)(rec + 0x0c) = *(u32*)(pos + 0x08);

        FUN_00e10580(*(void**)((char*)p + 0x70), citizen, rec, 0, 0);
    }

    void* ps = *(void**)((char*)p + 0x78);
    u32 kind;
    if (CIT(citizen)->FUN_00c0b770() != 0) {
        kind = (u32)POSSE(ps)->FUN_00cc88e0(CIT(citizen)->FUN_00c22dc0());
    } else {
        kind = 5;
    }
    void* pose = *(void**)((char*)ps + 8 + kind * 4);
    void* item = POSSE(pose)->FUN_00e24c90(citizen);
    if (citizen != 0 && item != 0) {
        (*(void(__thiscall**)(void*, u32, float, int, int))((char*)vtbl(item) + 0x80))(item, 0x3dea7f0, 0.0f, 1, 1);
    }
}

// ===========================================================================
// 0x00cca000 - 94 bytes: minimap-icon helper (free-shaped; ecx = a helper obj)
// ===========================================================================
// @ 0x00cca000
void FUN_00cca000_impl(void* self, void* a, float f)
{
    u8* p = (u8*)self;
    void* ps = *(void**)((char*)p + 0x78);
    u32 kind;
    if (CIT(a)->FUN_00c0b770() != 0) {
        kind = (u32)POSSE(ps)->FUN_00cc88e0(CIT(a)->FUN_00c22dc0());
    } else {
        kind = 5;
    }
    void* pose = *(void**)((char*)ps + 8 + kind * 4);
    void* item = POSSE(pose)->FUN_00e24c90(a);
    if (a != 0 && item != 0) {
        (*(void(__thiscall**)(void*, u32, float, int, int))((char*)vtbl(item) + 0x80))(item, 0x3dea7f0, f, 1, 1);
    }
}

// ===========================================================================
// 0x00cca060 - 39 bytes: release the six posse items
// ===========================================================================
// @ 0x00cca060
void cTribeDisplayStrategy::FUN_00cca060()
{
    u8* p = (u8*)this;
    void* ps = *(void**)((char*)p + 0x78);
    if (ps != 0) {
        u8* slot = (u8*)ps + 8;
        for (int i = 6; i != 0; i--) {
            void* q = *(void**)slot;
            if (q != 0) {
                POSSE(q)->FUN_00e21960();
            }
            slot += 4;
        }
    }
}

// ===========================================================================
// 0x00cca090 - 15 bytes: tail-jump to FUN_00cc9360
// ===========================================================================
// @ 0x00cca090
char cTribeDisplayStrategy::FUN_00cca090()
{
    u8* p = (u8*)this;
    void* ps = *(void**)((char*)p + 0x78);
    if (ps != 0) {
        return POSSE(ps)->FUN_00cc9360();
    }
    return 0;
}

// ===========================================================================
// 0x00cca0a0 - 24 bytes
// ===========================================================================
// @ 0x00cca0a0
void cTribeDisplayStrategy::FUN_00cca0a0()
{
    u8* p = (u8*)this;
    void* ps = *(void**)((char*)p + 0x78);
    if (ps != 0) {
        void* q = *(void**)((char*)ps + 8);
        if (q != 0) {
            POSSE(q)->FUN_00e26a90(0);
        }
    }
}

// ===========================================================================
// 0x00cca0e0 - 43 bytes: copy `count` 3-float records
// ===========================================================================
// @ 0x00cca0e0
void FUN_00cca0e0_impl(void* dst, unsigned count, const void* src)
{
    struct P3 { u32 a, b, c; };
    P3* d = (P3*)dst;
    const P3* s = (const P3*)src;
    for (unsigned i = count; i > 0; i--) {
        *d = *s;
        d++;
        s++;
    }
}

// ===========================================================================
// 0x00cca110 - 94 bytes: uninitialised_copy_construct_n of 0x18-byte records
// ===========================================================================
// @ 0x00cca110
void FUN_00cca110_impl(void** out, u8* first, u8* last, u8* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                *(u32*)(dst + 0x00) = *(u32*)(first + 0x00);
                *(u32*)(dst + 0x04) = *(u32*)(first + 0x04);
                *(float*)(dst + 0x08) = *(float*)(first + 0x08);
                *(float*)(dst + 0x0c) = *(float*)(first + 0x0c);
                *(float*)(dst + 0x10) = *(float*)(first + 0x10);
            }
            first += 0x18;
            dst   += 0x18;
        } while (first != last);
        *out = dst;
    }
}

// ===========================================================================
// 0x00cca170 - 90 bytes: allocate a 0x20 refcounted node, copy a 0x10 payload
// ===========================================================================
// @ 0x00cca170
void* CPool::FUN_00cca170(void* payload)
{
    u8* mem = (u8*)op_new(0x20, "Simulator", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                          0xd1);
    u8* node = mem + 0x10;
    if (node != 0) {
        void* p = *(void**)payload;
        *(void**)node = p;
        if (p != 0) {
            (*(void(__thiscall**)(void*))vtbl(p))(p);
        }
        struct Tail { u32 a, b, c; };
        *(Tail*)(node + 4) = *(Tail*)((u8*)payload + 4);
    }
    return mem;
}

// ===========================================================================
// 0x00cca1d0 - 82 bytes: move-assign a run of 0x18-byte records
// ===========================================================================
// @ 0x00cca1d0
void FUN_00cca1d0_impl(u8* first, u8* last, u8* dst)
{
    if (first != last) {
        do {
            if (dst != 0) {
                *(u32*)(dst + 0x00) = *(u32*)(first + 0x00);
                *(u32*)(dst + 0x04) = *(u32*)(first + 0x04);
                *(float*)(dst + 0x08) = *(float*)(first + 0x08);
                *(float*)(dst + 0x0c) = *(float*)(first + 0x0c);
                *(float*)(dst + 0x10) = *(float*)(first + 0x10);
            }
            first += 0x18;
            dst   += 0x18;
        } while (first != last);
    }
}

// ===========================================================================
// 0x00cca230 - 408 bytes: SP::cPosseSet::Init
// ===========================================================================
// @ 0x00cca230
void cPosseSet::Init()
{
    u8* self = (u8*)this;
    // the six AutoRefCount<cSPUIPosse> slots start at +8 and are walked
    // downwards: slot index i -> +8 + i*4.
    int stop = 5;
    u8* slot = (u8*)self + 0x8 + 5 * 4;    // &mPosse[5]
    for (;;) {
        u8* mem = (u8*)FUN_009512c0();
        (void)mem;
        u8* raw = (u8*)FUN_009512d0(0x20c, 4, "UI/Posse");
        u8* novo;
        if (raw != 0) {
            novo = (u8*)FUN_00e25710(raw);
        } else {
            novo = 0;
        }
        void* old = *(void**)slot;
        if (novo != old) {
            if (novo != 0) {
                (*(void(__thiscall**)(void*))vtbl(novo))(novo);
            }
            *(void**)slot = novo;
            if (old != 0) {
                (*(void(__thiscall**)(void*))((char*)vtbl(old) + 4))(old);
            }
        }
        void* cur = *(void**)slot;
        (*(void(__thiscall**)(void*, float, const wchar_t*))((char*)vtbl(cur) + 0x80))(cur, 0x40464100, L"PosseBar");
        stop--;
        slot -= 4;
        if (stop < 0) {
            break;
        }
    }

    wchar_t name[0x10];
    FUN_006b5770(name, 0xf71fa311, 0xf37c273b, L"~Tribe");
    u8* posseAdults = (u8*)self + 0x8;
    void* first = *(void**)posseAdults;
    u8* cur = (u8*)first;
    (*(void(__thiscall**)(void*, const wchar_t*))((char*)vtbl(cur) + 0xb8))(cur, FUN_006b55c0(name));
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x1c)) + 0xb8))(*(void**)((char*)self + 0x1c), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x10)) + 0xb8))(*(void**)((char*)self + 0x10), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x0c)) + 0xb8))(*(void**)((char*)self + 0x0c), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x14)) + 0xb8))(*(void**)((char*)self + 0x14), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x18)) + 0xb8))(*(void**)((char*)self + 0x18), (u32*)0x13ec468);

    u8* ptr = (u8*)posseAdults;
    for (int i = 0; i < 6; i++) {
        void* pose = *(void**)ptr;
        float f = *(float*)0x1476a90;
        (*(void(__thiscall**)(void*, float))((char*)vtbl(pose) + 0xc4))(pose, f);
        if (i != 0) {
            void* wnd = (void*)FUN_008061c0((void*)(*(u8**)((char*)pose + 0x0) + 0x1bc), 0x3dae412);
            (*(void(__thiscall**)(void*, int, int))((char*)vtbl(wnd) + 0x7c))(wnd, 1, 0x10);
            (*(void(__thiscall**)(void*, int, int))((char*)vtbl(wnd) + 0x7c))(wnd, 2, 0);
            (*(void(__thiscall**)(void*, int, int))((char*)vtbl(wnd) + 0x7c))(wnd, 1, 0);
        }
        ptr += 4;
    }
    POSSE(self)->FUN_00cc8be0();
    FUN_006b5240(name);
}

// ===========================================================================
// 0x00cca3d0 - 472 bytes
// ===========================================================================
// @ 0x00cca3d0
u32 cTribeDisplayStrategy::FUN_00cca3d0(void* citizen)
{
    u8* p = (u8*)this;
    u8* c = (u8*)citizen;
    if (ldu8(p, 0xb5e) != 0) {
        return 0;
    }
    u32 v = ldu32(*(void**)((char*)p + 0xb4c), 0x1d8);
    if (v < 0x4639cd2) {
        if (v == 0x4639cd1) return 7;
        if (v < 0x4625f65) {
            if (v == 0x4625f64) return 9;
            if (v == 0x4611ff4) return 8;
            if (v == 0x461300f) return 3;
            if (v == 0x4623e0c) {
                void* o = FUN_00bca2c0();
                if (o != 0) {
                    int k = *(int*)o;
                    if (k == 8) return 4;
                    if (k == 9) return 0xe;
                }
            }
        } else if (v == 0x462854d) {
            void* o = FUN_00bca2c0();
            if (o != 0 && *(int*)o == 3) {
                void* a = FUN_00cca0c0((char*)o + 0x28);
                if (a != 0) {
                    u32 s = (u32)(*(int(__thiscall**)(void*))((char*)vtbl(a) + 0x58))(a);
                    s -= 1;
                    if (s <= 8) {
                        static const u8 tbl[9] = { 10, 10, 10, 13, 13, 13, 12, 11, 10 };
                        return tbl[s];
                    }
                }
            }
        } else if (v == 0x462854e) {
            return 1;
        } else if (v == 0x462855e) {
            return 0xe;
        }
    } else {
        if (v < 0x569236f) {
            if (v == 0x569236e) return 7;
            if (v == 0x5218bb3) return 1;
            if (v == 0x562aa6f) return 8;
            if (v == 0x562c0fb) return 8;
        } else if (v == 0x5b9b7f5) {
            return 7;
        } else if (v == 0xb46e8803) {
            return 5;
        } else if (v == 0xf56baff5) {
            return 0xe;
        }
    }
    void* q = (void*)(*(int(__thiscall**)(void*))((char*)vtbl(p) + 0x20))(p);
    if (q != 0) {
        u32 id = (u32)(*(int(__thiscall**)(void*))((char*)vtbl(q) + 0x1c))(q);
        if (id == 0x3c19bc97) return 6;
        if (id == 0xf09b40e0) return 2;
    }
    (void)c;
    return 0;
}

// ===========================================================================
// 0x00cca5b0 - 712 bytes: SetPosseActivity
// ===========================================================================
// @ 0x00cca5b0
void cTribeDisplayStrategy::SetPosseActivity(void* key, int activity)
{
    u8* p = (u8*)this;
    if (ld32(p, 0x78) == 0) {
        return;
    }
    u8* k = (u8*)key;
    if (k != 0) {
        (*(void(__thiscall**)(void*))vtbl(k))(k);
    }
    u8 nodeOut[4];
    FUN_00e5c780((char*)p + 0x94, nodeOut, &k);
    if (k != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(k) + 4))(k);
    }
    u8* node = *(u8**)nodeOut;
    if (node == p + 0x98) {
        return;
    }
    if (ld32(node, 0x1c) == activity) {
        return;
    }
    void* pose = (void*)POSSE(*(void**)((char*)p + 0x78))->FUN_00cc90a0(ldu32(node, 0x14));
    if (pose == 0) {
        return;
    }
    st32(node, 0x1c, activity);
    switch (activity) {
    case 1:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x74e57247, ldu32(p, 0x74), 0);
        return;
    case 2:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xe7032112, ldu32(p, 0x74), 0);
        return;
    case 3: {
        void* tribe = FUN_00bfc5f0(FUN_00b3d300());
        if (FUN_00c8e870(tribe) == 0) {
            (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xaf899239, ldu32(p, 0x74), 0);
            return;
        }
        if (FUN_00c8e850(tribe) != 0) {
            (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x1088670e, ldu32(p, 0x74), 0);
        } else {
            (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x9f9c8136, ldu32(p, 0x74), 0);
        }
        return;
    }
    case 4:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xbfffc8aa, ldu32(p, 0x74), 0);
        return;
    case 5:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x3ee93e5d, ldu32(p, 0x74), 0);
        return;
    case 6:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x2f96d59d, ldu32(p, 0x74), 0);
        return;
    case 7:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xfb0e7c68, ldu32(p, 0x74), 0);
        return;
    case 8:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x76de3589, ldu32(p, 0x74), 0);
        return;
    case 9:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x5b47d20e, ldu32(p, 0x74), 0);
        return;
    case 10:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x2b5af9b8, ldu32(p, 0x74), 0);
        return;
    case 0xb:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x6c7ef657, ldu32(p, 0x74), 0);
        return;
    case 0xc:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x7e91c364, ldu32(p, 0x74), 0);
        return;
    case 0xd:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x6f50def7, ldu32(p, 0x74), 0);
        return;
    default:
        (*(void(__thiscall**)(void*, int))((char*)vtbl(pose) + 0xa4))(pose, 0);
        return;
    }
}

// ===========================================================================
// 0x00cca880 - 316 bytes: SetCreaturePosseIcon
// ===========================================================================
// @ 0x00cca880
void cTribeDisplayStrategy::FUN_00cca880(void* citizen, int a)
{
    u8* p = (u8*)this;
    u8* c = (u8*)citizen;
    if (c != 0) {
        (*(void(__thiscall**)(void*))vtbl(c))(c);
    }
    u8 nodeOut[4];
    FUN_00e5c780((char*)p + 0x94, nodeOut, &c);
    if (c != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(c) + 4))(c);
    }
    u8* node = *(u8**)nodeOut;
    if (node == p + 0x98) {
        return;
    }
    if (ld32(p, 0x78) == 0) {
        return;
    }
    u32 kind = (u32)CIT(c)->FUN_00c22dc0();
    if (a != (int)kind) {
        POSSE(*(void**)((char*)p + 0x78))->FUN_00cc90f0(c, (void*)a);
    }
    void* pose = (void*)POSSE(*(void**)((char*)p + 0x78))->FUN_00cc90a0(ldu32(node, 0x14));
    if (pose == 0) {
        return;
    }
    if (CIT(c)->FUN_00c232d0() != 0 && kind == 0) {
        void* img = FUN_008061c0(*(void**)((char*)p + 0x74), 0xc37a78d7);
        (*(void(__thiscall**)(void*, void*, int))((char*)vtbl(pose) + 0x94))(pose, img, 0);
    } else if ((int)kind >= 1) {
        void* o = FUN_00c9cec0(kind);
        void* img = *(void**)((char*)o + 0x20);
        if (img != 0) {
            void* im = FUN_008061c0(*(void**)((char*)p + 0x74), (u32)img);
            (*(void(__thiscall**)(void*, void*, int))((char*)vtbl(pose) + 0x94))(pose, im, 0);
        } else {
            STRAT(p)->FUN_00cc8a30(pose, c);
        }
    } else {
        STRAT(p)->FUN_00cc8a30(pose, c);
    }
    void* v = FUN_00cc8830(c);
    (*(void(__thiscall**)(void*, void*))((char*)vtbl(pose) + 0x88))(pose, v);
    if (CIT(c)->FUN_00c0b770() != 0) {
        void* ps = *(void**)((char*)p + 0x78);
        u32 k = (u32)POSSE(ps)->FUN_00cc88e0(CIT(c)->FUN_00c22dc0());
        POSSE(*(void**)((char*)ps + k * 4 + 8))->FUN_00e28230();
    } else {
        POSSE(*(void**)((char*)p + 0x78) ? *(void**)((char*)*(void**)((char*)p + 0x78) + 0x8 + 5 * 4) : 0)->FUN_00e28230();
    }
}

// ===========================================================================
// 0x00cca9e0 - 146 bytes: SetGroundSpearTransform
// ===========================================================================
// @ 0x00cca9e0
char cTribeDisplayStrategy::SetGroundSpearTransform(char slot, u32 index, const void* xform, char ref)
{
    u8* p = (u8*)this;
    int b = (slot == 0);
    u8* arrBase = b ? ((u8*)p + 0x178) : ((u8*)p + 0x218);
    u8* arr = (u8*)p + b * 0x60;
    u32 count = (ldu32(arr, 0xc8) - ldu32(arr, 0xc4)) / 0x38;
    if (index < count) {
        u8* item = (u8*)(ldu32(arr, 0xc4) + (index * 0x38));
        ((CTransformOps*)item)->Assign(xform);
        *(u32*)(arrBase + index * 4) = (u32)ref;
        ((CModelInstSet*)(arr + 0xb8))->Update();
        return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00ccaa80 - 247 bytes
// ===========================================================================
// @ 0x00ccaa80
void cTribeDisplayStrategy::FUN_00ccaa80(void* arg)
{
    u8* p = (u8*)this;
    u8* node = *(u8**)((char*)p + 0x9c);
    u8* end = p + 0x98;
    if (node == end) {
        return;
    }
    do {
        void* cit = *(void**)((char*)node + 0x14);
        void* ps = *(void**)((char*)p + 0x78);
        void* key = *(void**)((char*)node + 0x10);
        u32 idx;
        if (CIT(cit)->FUN_00c0b770() == 0) {
            idx = 5;
        } else {
            switch (CIT(cit)->FUN_00c22dc0()) {
            case 0xb:
                idx = 0;
                break;
            case 1:
            case 2:
            case 3:
            case 9:
                idx = 2;
                break;
            case 4:
            case 5:
            case 6:
                idx = 1;
                break;
            case 7:
            case 8:
                idx = 3;
                break;
            default:
                idx = 4;
                break;
            }
        }
        void* pose = *(void**)((char*)ps + idx * 4 + 8);
        void* item = POSSE(pose)->FUN_00e24c90(cit);
        if (key != 0 && item != 0) {
            u32 a = (u32)CIT(key)->FUN_00c22dc0();
            u32 bb = (u32)CIT(arg)->FUN_00c22dc0();
            if (a == bb) {
                (*(void(__thiscall**)(void*, int))((char*)vtbl(item) + 0xb8))(item, 2);
            }
        }
        node = (u8*)FUN_00921580(node);
    } while (node != end);
}

// ===========================================================================
// 0x00ccab80 - 219 bytes
// ===========================================================================
// @ 0x00ccab80
void cTribeDisplayStrategy::FUN_00ccab80()
{
    u8* p = (u8*)this;
    u8* node = *(u8**)((char*)p + 0x9c);
    if (node == p + 0x98) {
        return;
    }
    do {
        void* cit = *(void**)((char*)node + 0x14);
        void* ps = *(void**)((char*)p + 0x78);
        void* key = *(void**)((char*)node + 0x10);
        u32 idx;
        if (CIT(cit)->FUN_00c0b770() == 0) {
            idx = 5;
        } else {
            switch (CIT(cit)->FUN_00c22dc0()) {
            case 0xb:
                idx = 0;
                break;
            case 1:
            case 2:
            case 3:
            case 9:
                idx = 2;
                break;
            case 4:
            case 5:
            case 6:
                idx = 1;
                break;
            case 7:
            case 8:
                idx = 3;
                break;
            default:
                idx = 4;
                break;
            }
        }
        void* pose = *(void**)((char*)ps + idx * 4 + 8);
        void* item = POSSE(pose)->FUN_00e24c90(cit);
        if (key != 0 && item != 0) {
            (*(void(__thiscall**)(void*, int))((char*)vtbl(item) + 0xb8))(item, 2);
        }
        node = (u8*)FUN_00921580(node);
    } while (node != p + 0x98);
}

// ===========================================================================
// 0x00ccad10 - 103 bytes: pool-allocate a 0x14 node and copy a payload
// ===========================================================================
// @ 0x00ccad10
void* CPool::FUN_00ccad10(u8* payload)
{
    u8* self = (u8*)this;
    u8* node = *(u8**)(self + 0x1c);
    if (node != 0) {
        *(u8**)(self + 0x1c) = *(u8**)node;
    } else {
        node = (u8*)op_new(*(u32*)(self + 0x2c), "Simulator", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    }
    if (node != 0) {
        struct Payload { u32 a, b; void* p; u8 c; };
        Payload* np = (Payload*)node;
        Payload* pp = (Payload*)payload;
        np->a = pp->a;
        np->b = pp->b;
        void* p2 = pp->p;
        np->p = p2;
        if (p2 != 0) {
            (*(void(__thiscall**)(void*))vtbl(p2))(p2);
        }
        np->c = pp->c;
    }
    *(u32*)(node + 0x10) = 0;
    return node;
}

// ===========================================================================
// 0x00ccad80 - 99 bytes: lower_bound over 0x18-byte records
// ===========================================================================
// @ 0x00ccad80
u8* FUN_00ccad80_impl(u8* first, u8* last, const void* key)
{
    int n = (int)(last - first) / 0x18;
    const u32* k = (const u32*)key;
    if (n > 0) {
        u32 k0 = k[0];
        u32 k1 = k[1];
        do {
            int half = n >> 1;
            u8* mid = first + half * 0x18;
            if (ldu32(mid, 4) <= k1 && (ldu32(mid, 4) < k1 || ldu32(mid, 0) < k0)) {
                first = mid + 0x18;
                half = n - (half + 1);
            }
            n = half;
        } while (n > 0);
    }
    return first;
}

// ===========================================================================
// 0x00ccaf60 - 129 bytes: sCheckForBabiesThatGrewUp handler
// ===========================================================================
// @ 0x00ccaf60
char __cdecl FUN_00ccaf60(void* self)
{
    u8* p = (u8*)self;
    u8* c = (u8*)self;
    void* a = (void*)(*(void*(__thiscall**)(void*))((char*)vtbl(c) + 0xc4))(c);
    if (a == 0) {
        return 1;
    }
    void* b = (void*)(*(void*(__thiscall**)(void*, u32))((char*)vtbl(a) + 0xc))(a, 0x4f176642);
    if (b != 0) {
        if (CIT(b)->FUN_00c0b770() != 0) {
            void* h = *(void**)((char*)p + 0x1c);
            (*(void(__thiscall**)(void*, void*, int))((char*)vtbl(h) + 0xa8))(h, c, 1);
            ((CStrategyOps*)p)->FUN_00cc8ed0(b);
            void* inst = FUN_00cd40b0();
            u32 k = (u32)CIT(b)->FUN_00c22dc0();
            void* r = (void*)(*(void*(__thiscall**)(void*, void*, u32))((char*)vtbl(inst) + 0x6c))(inst, b, k);
            ((cTribeDisplayStrategy*)r)->FUN_00cca880(b, (int)k);
            return 1;
        }
    }
    return 1;
}
