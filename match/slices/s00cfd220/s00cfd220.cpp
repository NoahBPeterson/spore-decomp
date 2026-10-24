// ===========================================================================
// slice s00cfd220 -- event-notify handler (module 0x00cfxxxx).
// Reconstructed from work/SporeApp.analysis.bin.
//
//   0x00cfd220  FUN_00cfd220   notify two event ids through the source lookup
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// ===========================================================================

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma warning(disable: 4100 4189 4244 4311 4312)

// ---- free / cdecl callees -------------------------------------------------
u32   FUN_00b5b800();                                  // 0x00b5b800  frame tag
void* FUN_01021260();                                  // 0x01021260  context lookup
void* FUN_00b3d300();                                  // 0x00b3d300  global manager E
void  FUN_00ba57a0(void* a, u32 b);                     // 0x00ba57a0  (caller cleans)

// ---- thiscall callees (ecx = the receiver passed as pSelf) -----------------
struct CalleeSet {
    void  FUN_00ceb430(void* a);                 // 0x00ceb430
    bool  FUN_00c741a0(void* a);                 // 0x00c741a0
    bool  FUN_00c73f10(void* a);                 // 0x00c73f10
    void* FUN_00ce6950();                        // 0x00ce6950
    void* FUN_00f67d90();                        // 0x00f67d90
    void* FUN_00ba4e60(void* a);                 // 0x00ba4e60
    void* FUN_00ba4520(void* a);                 // 0x00ba4520
};
#define SELF(o) ((CalleeSet*)(o))

// ---- vtable dispatch through a member pointer (thiscall) -------------------
struct VtblObj {
    void  C0(); void  C1(void*); void  C2(void*, void*); void  C3(void*, void*, void*);
    void* R0(); void* R1(void*); void* R2(void*, void*); void* R3(void*, void*, void*);
    bool  B0();
};
typedef void* (VtblObj::*PMR0)();
typedef void* (VtblObj::*PMR1)(void*);
typedef bool  (VtblObj::*PMB0)();
typedef void  (VtblObj::*PMF1)(void*);
typedef void  (VtblObj::*PMF2)(void*, void*);
typedef void  (VtblObj::*PMF3)(void*, void*, void*);

inline void* VRet0(void* p, u32 o)                             { return (((VtblObj*)p)->*(*(PMR0*)((u8*)*(void**)p + o)))(); }
inline void* VRet1(void* p, u32 o, void* a)                    { return (((VtblObj*)p)->*(*(PMR1*)((u8*)*(void**)p + o)))(a); }
inline bool  VBr0(void* p, u32 o)                              { return (((VtblObj*)p)->*(*(PMB0*)((u8*)*(void**)p + o)))(); }
inline void  VCall1(void* p, u32 o, void* a)                   { (((VtblObj*)p)->*(*(PMF1*)((u8*)*(void**)p + o)))(a); }
inline void  VCall2(void* p, u32 o, void* a, void* b)          { (((VtblObj*)p)->*(*(PMF2*)((u8*)*(void**)p + o)))(a, b); }
inline void  VCall3(void* p, u32 o, void* a, void* b, void* c) { (((VtblObj*)p)->*(*(PMF3*)((u8*)*(void**)p + o)))(a, b, c); }

// ---- event record handed back by the source lookup ------------------------
// The dispatch at vtable +0x0c returns one of these; the interesting
// sub-object starts at +0x34.
struct IncEvent {
    u8      mGap00[0x34];      // +0x00 .. +0x34
    void**  mv34;              // +0x34  embedded sub-object vtable
};

// result of 0x01021260 (the notify context)
struct Ctx {
    u8      mGap00[0x13c];     // +0x000 .. +0x13c
    void*   mp13c;             // +0x13c  receiver of 0x00ce6950
};

// 0x00b3d300()  -- global manager whose container lives at +0x11c0
struct MgrE {
    u8      mGap00[0x11c0];    // +0x0000 .. +0x11c0
    u8      mSub11c0[1];       // +0x11c0  receiver of 0x00ba4e60
};

// element returned by 0x00ba4e60 / 0x00ba4520
struct MapEntry {
    u8      mGap00[0x20];      // +0x00 .. +0x20
    u8      mSub20[1];         // +0x20  receiver for the second event
    u8      mGap21[0x17];      // +0x21 .. +0x38
    u8      mSub38[1];         // +0x38  receiver for the first event
};

// the handler this method belongs to
struct CHandler {
    u8      mGap00[0xec];      // +0x000 .. +0xec
    void*   mp_ec;             // +0xec  receiver of 0x00ceb430
    u8      mGap_f0[0x0c];     // +0x0f0 .. +0xfc
    u8      mB_fc;             // +0xfc  state flag set on match

    void FUN_00cfd220(void* pSrc);
};

// @ 0x00cfd220
void CHandler::FUN_00cfd220(void* pSrc)
{
    u8* src = (u8*)pSrc;

    if (VRet1(src, 0x0c, (void*)(size_t)0xee9b2232u))
        mB_fc = 1;

    void* h1 = VRet1(src, 0x0c, (void*)(size_t)0x137e8e0u);
    if (h1 && mp_ec)
        SELF(mp_ec)->FUN_00ceb430(h1);

    if (FUN_00b5b800() == 0x1654c10u)
        return;

    void* ctx = FUN_01021260();

    if (h1) {
        void* sub = (void*)&((IncEvent*)h1)->mv34;
        if (VBr0(sub, 0x58)) {
            void* key = VRet0(sub, 0x98);
            if (!SELF(ctx)->FUN_00c741a0(key)) {
                void* tok = SELF(((Ctx*)ctx)->mp13c)->FUN_00ce6950();
                void* mgr = SELF(FUN_00b3d300())->FUN_00f67d90();
                void* map = SELF(&((MgrE*)mgr)->mSub11c0)->FUN_00ba4e60(&tok);
                void* key2 = VRet0(sub, 0x98);
                u8*   cell = (u8*)SELF(&((MapEntry*)map)->mSub38)->FUN_00ba4520(key2);
                *cell = 1;
                FUN_00ba57a0(h1, 1);
            }
        }
    }

    {
        void* h2 = VRet1(src, 0x0c, (void*)(size_t)0xe9cb8bau);
        if (h2) {
            void* sub = (void*)&((IncEvent*)h2)->mv34;
            if (VBr0(sub, 0x58)) {
                void* key = VRet0(sub, 0x98);
                if (!SELF(ctx)->FUN_00c73f10(key)) {
                    void* tok = SELF(((Ctx*)ctx)->mp13c)->FUN_00ce6950();
                    void* mgr = SELF(FUN_00b3d300())->FUN_00f67d90();
                    void* map = SELF(&((MgrE*)mgr)->mSub11c0)->FUN_00ba4e60(&tok);
                    void* key2 = VRet0(sub, 0x98);
                    u8*   cell = (u8*)SELF(&((MapEntry*)map)->mSub20)->FUN_00ba4520(key2);
                    *cell = 1;
                    FUN_00ba57a0(h2, 1);
                }
            }
        }
    }
}