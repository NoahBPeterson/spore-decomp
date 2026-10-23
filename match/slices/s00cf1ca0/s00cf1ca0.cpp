// Slice s00cf1ca0 -- Simulator city-input strategy helpers (SPCityInputStrategy.obj).
// eaSTL heap/partition helpers over AutoRefCount arrays, plus SP::cCityInputStrategy methods
// (RestoreCommunityEditorOrShopping, EndSelection, SetDefaultPickPriorities) and the free-camera
// toggle / pick-priority registrar helpers.
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail offsets in this
// object are read from the disassembly and modelled with locally declared stub classes, following
// the sibling-slice style.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

extern "C" long _InterlockedExchange(volatile long* Target, long Value);

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
namespace EA { namespace Audio {
void* GetSystemAT();                                   // 0x00a206f0
}}

extern "C" {
void* __cdecl GetGameTerrainCursor();                  // 0x00b30d70 SP::GetGameTerrainCursor
void* __cdecl FUN_00b3d280();                          // GetCameraCtl
void* __cdecl FUN_00b3d290();                          // 0x00b3d290
void* __cdecl FUN_00b3d240();                          // 0x00b3d240
void* __cdecl FUN_00b3d320();                          // 0x00b3d320
void* __cdecl FUN_00b3d350();                          // PlanetModel
void  __cdecl FUN_00b11870(void* cam, u32 id);         // 0x00b11870
void* __cdecl FUN_00ac15e0(void* o);                   // 0x00ac15e0
char  __cdecl FUN_00ac0730(void* a, void* b);          // 0x00ac0730 Less comparator
void  __cdecl FUN_00afba10(void* o);                   // 0x00afba10
int   __cdecl FUN_00af9dd0(float f, int n);            // 0x00af9dd0
void  __cdecl FUN_00af9cf0(float* center, float r, float* facing, float altitude);  // cActionCircle::SetAtCenter
void  __cdecl FUN_00afef10(int a, float f);            // 0x00afef10
void* __cdecl FUN_00af1450(void* o);                   // TimerOwner::Add
void  __cdecl FUN_00b535d0(void* pos, const void* val);  // 0x00b535d0 vector insert
void  __cdecl FUN_00b2af00(void* a, void* b);          // 0x00b2af00 swap
void  __cdecl FUN_00b1dfc0(void* o);                   // 0x00b1dfc0
void  __cdecl FUN_00cf1380(void* base, int dummy, int pos);     // 0x00cf1380 heap-replace
void  __cdecl FUN_00cf1e70(int* a, int* b, float f, float g, float h);  // 0x00cf1e70
void  __cdecl FUN_00cf1ee0(int* a, int* b, float f, float g, float h);  // 0x00cf1ee0
void* __cdecl FUN_00cf74c0();                          // SP::cCivModeStrategy::Get
void* __cdecl FUN_00cf7500(void* o);                   // 0x00cf7500
void* __cdecl FUN_00579a90(const wchar_t* s);          // 0x00579a90 RangeInitialize
void* __cdecl FUN_0067dcc0();                          // 0x0067dcc0 MessageServer
void* __cdecl FUN_0067cab0(int id);                    // 0x0067cab0
char  __cdecl FUN_00801bb0(void* mgr, u32 id);         // 0x00801bb0 CurMgr::FindLocal
void* __cdecl FUN_00f473a0(u32 size, const char* file, int a, int b, int c, int d);  // EAAllocate
void  __cdecl FUN_00f47380(void* p);                   // ??3 operator delete
void  __cdecl FUN_00e25bd0(void* vec, void* first, void* last);  // vector::erase
void* __cdecl FUN_00ad92d0(void* vec);                 // vector dtor
void  __cdecl FUN_00afbad0(void* o);                   // cActionCircle dtor
void  __cdecl FUN_00435ed0(void* p, u32 id);           // cSPUISpace::KillSetiEffects
void* __cdecl FUN_00b7f190(void* planet, void* out, const void* pos);  // BuildSurfaceOrientation
void  __cdecl FUN_00c9ee30(void* o, void* a);          // 0x00c9ee30
void  __cdecl FUN_00cac0e0(void* o, float f, float g, float h, int i);  // 0x00cac0e0
void  __cdecl FUN_00cfa990(void* o, int a, int b);     // SP::cCivModeStrategy::DoNextCivTutorial
char  __cdecl FUN_00cf7830(void* o, int a);            // SP::cCivModeStrategy::HasCivTutorialOccurred
void  __cdecl FUN_00c9e960(void* veh, float* pos);     // SP::cVehicle::CanOccupyTerrain
void  __cdecl FUN_00afa030(void* slot, void* gd);      // SP::cActionCircle::tSlot::Reserve
void  __cdecl FUN_00cf74c0_void();                     // (unused)
}

struct Vec3 { float x, y, z; };

extern float gZeroF;              // 0x01485378  0.0f
extern Vec3  gSurfaceDir;         // 0x0169d2ac
extern int   gMaxPickups;         // 0x01581994

namespace SP {

// ---------------------------------------------------------------------------------------------
// AutoRefCount<T>: intrusive refcounted handle, vtable [0]=AddRef, [4]=Release.
// ---------------------------------------------------------------------------------------------
class AutoRefCount
{
  public:
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
};

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t> local (begin/end/cap). Init = zero + RangeInitialize(literal).
// ---------------------------------------------------------------------------------------------
class WStr
{
  public:
    u32* mBegin;                        // +0x00
    u32* mEnd;                          // +0x04
    u32* mCap;                          // +0x08

    void Init(const wchar_t* s) {
        mBegin = 0; mEnd = 0; mCap = 0;
        RangeInit(s);
    }
    void RangeInit(const wchar_t* s);   // 0x00579a90 (thiscall on this)
    void Release() {
        int cnt = (int)((char*)mEnd - (char*)mBegin);
        cnt &= 0xfffffffe;
        if (cnt > 2 && mBegin != 0) {
            FUN_00f47380(mBegin);
        }
    }
};

void WStr::RangeInit(const wchar_t* s) { FUN_00579a90(s); }

// ---------------------------------------------------------------------------------------------
// cCityInputStrategy (retail offsets from the disassembly).
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00cf1ca0(void* ecx_this, void* edx, int first, int last, int pos,
                             AutoRefCount* pivot, int a, int b);

class cCityInputStrategy
{
  public:
    bool RestoreCommunityEditorOrShopping(int id);          // 0x00cf1f50 (ret 4)
    bool EndSelection(const Vec3* dir, const void* picked);  // 0x00cf2520 (ret 0xc)
    void SetDefaultPickPriorities();                        // 0x00cf28f0

    unsigned char pad000[0x80];
    int  mAutoHandlerPriority;          // 0x080
    unsigned char pad084[0xfc - 0x84];
    void* mpCreatureSelected;           // 0x0fc
};

// ---------------------------------------------------------------------------------------------
// a community-editor behaviour message (operator new'ed, 0x40 bytes).
// ---------------------------------------------------------------------------------------------
class BehaviorMessage
{
  public:
    virtual void v00();                 // +0x00 AddRef-like
    virtual void v04();                 // +0x04 Release-like
    virtual void v08();                 // +0x08
    virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
};

// ---------------------------------------------------------------------------------------------
// MessageServer with a +0x18 Send slot.
// ---------------------------------------------------------------------------------------------
class MessageServer
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Send(u32 id, void* msg, int a, int b);     // +0x18
};

// An intrusive refcounted list local (begin/end/cap) used by EndSelection.
class RefList
{
  public:
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
};

// The world object reached via FUN_00b3d240, with +0x2c (SetPickPriorities) and +0x60 slots.
class PickWorld
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void SetPickPriorities(void* vec, int flag);    // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(void* a, void* b, void* c);            // +0x60
};

// The audio system object with a +0x20 slot.
class AudioSystem
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual u32  GetId();                                   // +0x20
};

// A picked spatial: vtable +0x00 AddRef, +0xb8 AsInterface.
class Pickable
{
  public:
    virtual void AddRef();                                  // +0x00
    virtual void Release();                                 // +0x04
    unsigned char pad008[0xb8 - 0x8];
    void* AsInterface(u32 id);                              // +0xb8
};

// The game terrain cursor, with the slots used by EndSelection.
class TerrainCursor
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual void GetPickedList(void* vec);                  // +0x5c
    virtual void v60(void* a, void* b, void* c);            // +0x60
    virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void HideCursor();                              // +0x70 is level 0x70 -> +0x74
    virtual void v74();
};

// ---------------------------------------------------------------------------------------------
// 0x00cf1f50 -- cCityInputStrategy::RestoreCommunityEditorOrShopping  (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00cf1f50
bool cCityInputStrategy::RestoreCommunityEditorOrShopping(int id)
{
    if (mAutoHandlerPriority == 0 || id == -1) {
        return mpCreatureSelected != 0;
    }
    BehaviorMessage* msg = (BehaviorMessage*)FUN_00f473a0(0x40, "App", 0, 0, 0, 0);
    if (msg != 0) {
        *(u32*)((char*)msg + 0x30) = 0;
        *(u32*)((char*)msg + 0x00) = 0x013eb90c;
        _InterlockedExchange((volatile long*)((char*)msg + 0x04), (long)0);
        *(u32*)((char*)msg + 0x00) = 0x013eb844;
        *(u32*)((char*)msg + 0x38) = 0;
        ((void(__thiscall**)(BehaviorMessage*))(*(char**)msg + 4))[0](msg);
    }
    *(u32*)((char*)msg + 0x30) = 0xb2699148;
    *(int*)((char*)msg + 0x08) = id;
    MessageServer* srv = (MessageServer*)FUN_0067dcc0();
    ((void(__thiscall**)(MessageServer*, u32, void*, int, int))(*(char**)srv + 0x18))[0](
        srv, *(u32*)((char*)msg + 0x30), msg, 0, 0);
    void* a = FUN_00b3d320();
    FUN_00b1dfc0(a);
    ((void(__thiscall**)(BehaviorMessage*))(*(char**)msg + 8))[0](msg);
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x00cf2010 -- eaSTL partition-style overlap test / swap over AutoRefCount array.
// ---------------------------------------------------------------------------------------------
// @ 0x00cf2010
int* __fastcall FUN_00cf2010(int* ecx_this, void* edx, int* last, int* value)
{
    int* first = ecx_this;
    int* vp;
    while (true) {
        int a;
        vp = (value == 0) ? 0 : value + 0x0d;
        a  = (*first == 0) ? 0 : *first + 0x34;
        if (!FUN_00ac0730((void*)a, (void*)vp)) break;
        first++;
    }
    do {
        int a;
        int* vp2;
        last--;
        a   = (*last == 0) ? 0 : *last + 0x34;
        vp2 = (value == 0) ? 0 : value + 0x0d;
        if (FUN_00ac0730((void*)vp2, (void*)a)) break;
    } while (true);
    if (first < last) {
        FUN_00b2af00(first, last);
        first++;
    }
    if (value != 0) {
        ((void(__thiscall**)(int*))(*(int**)value + 4))[0](value);
    }
    return last;
}

// ---------------------------------------------------------------------------------------------
// 0x00cf2330 -- free-camera toggle.
// ---------------------------------------------------------------------------------------------
// @ 0x00cf2330
void __fastcall FUN_00cf2330(void* ecx_this, void* edx)
{
    char* self = (char*)ecx_this;
    WStr msg;                                   // local eastl::wstring (12 bytes: begin/end/cap)
    if (*(int*)(self + 0xe0) == 1) {
        *(int*)(self + 0xe0) = 0;
        if (FUN_00b3d280() != 0) {
            void* cam = FUN_00b3d280();
            FUN_00b11870(cam, 0xf31f49a1);
        }
        msg.Init(L"Free Camera OFF");
        FUN_00af1450(FUN_00cf7500(FUN_00cf74c0()));
        msg.Release();
    } else {
        *(int*)(self + 0xe0) = 1;
        msg.Init(L"Free Camera ON");
        FUN_00af1450(FUN_00cf7500(FUN_00cf74c0()));
        msg.Release();
        if (FUN_00b3d280() != 0) {
            void* cam = FUN_00b3d280();
            FUN_00b11870(cam, 0xcf14603b);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00cf1ca0 -- eaSTL heap sift-down over an AutoRefCount array (make_heap/pop_heap helper).
// @ 0x00cf1ca0
void __fastcall FUN_00cf1ca0(void* ecx_this, void* edx, int first, int last, int pos,
                             AutoRefCount* pivot, int a, int b)
{
    int* base = (int*)first;
    int* base2 = (int*)ecx_this;
    (void)base2;
    int i = pos;
    int child = i * 2 + 2;
    while (child < last) {
        int l = *(int*)((char*)base + (child - 1) * 4);
        void* lp = (l == 0) ? 0 : (void*)(l + 0x34);
        int r = *(int*)((char*)base + child * 4);
        void* rp = (r == 0) ? 0 : (void*)(r + 0x34);
        if (FUN_00ac0730(rp, lp)) {
            child = i * 2 + 1;
        }
        AutoRefCount* cl = (AutoRefCount*)*(int*)((char*)base + child * 4);
        AutoRefCount* ci = (AutoRefCount*)*(int*)((char*)base + i * 4);
        if (cl != ci) {
            if (cl) cl->AddRef();
            *(int*)((char*)base + i * 4) = (int)cl;
            if (ci) ci->Release();
        }
        i = child;
        child = i * 2 + 2;
    }
    if (child == last) {
        AutoRefCount* cl = (AutoRefCount*)*(int*)((char*)base + (child - 1) * 4);
        AutoRefCount* ci = (AutoRefCount*)*(int*)((char*)base + i * 4);
        if (cl != ci) {
            if (cl) cl->AddRef();
            *(int*)((char*)base + i * 4) = (int)cl;
            if (ci) ci->Release();
        }
        i = child - 1;
    }
    if (pivot) {
        ((void(__thiscall**)(AutoRefCount*, int, int))(*(char**)pivot))[0](pivot, a, b);
    }
    FUN_00cf1380(base, 0, i);
    if (pivot) {
        ((void(__thiscall**)(AutoRefCount*))(*(char**)pivot + 4))[0](pivot);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00cf20b0 -- eaSTL insertion-sort / partition driver over AutoRefCount array + floats.
// @ 0x00cf20b0
void __fastcall FUN_00cf20b0(void* ecx_this, void* edx, int* last, int* value,
                             float f1, float f2, float f3)
{
    int* first = (int*)ecx_this;
    FUN_00cf1e70(first, last, f1, f2, f3);
    int* p = last;
    while (p < value) {
        int lp = (*first == 0) ? 0 : *first + 0x34;
        int vp = (*p == 0) ? 0 : *p + 0x34;
        if (!FUN_00ac0730((void*)vp, (void*)lp)) {
            p++;
            continue;
        }
        AutoRefCount* save = (AutoRefCount*)*p;
        if (save) save->AddRef();
        AutoRefCount* cur = (AutoRefCount*)*first;
        AutoRefCount* oth = (AutoRefCount*)*p;
        if (cur != oth) {
            if (cur) cur->AddRef();
            *p = (int)cur;
            if (oth) oth->Release();
        }
        if (save) {
            ((void(__thiscall**)(AutoRefCount*, float, float, float))(*(char**)save))[0](save, f1, f2, f3);
        }
        FUN_00cf1ca0(first, (void*)0, (int)first, (int)last - (int)first, 0, *(AutoRefCount**)&save, 0, 0);
        if (save) save->Release();
        p++;
    }
    FUN_00cf1ee0(first, last, f1, f2, f3);
}

// ---------------------------------------------------------------------------------------------
// A 12-byte pick-priority record pushed into an eaSTL vector.
// ---------------------------------------------------------------------------------------------
struct PickPriority
{
    u32 mId;        // +0x00
    int mPriority;  // +0x04
    int mWeight;    // +0x08
};

// ---------------------------------------------------------------------------------------------
// 0x00cf28f0 -- cCityInputStrategy::SetDefaultPickPriorities
// ---------------------------------------------------------------------------------------------
// @ 0x00cf28f0
void cCityInputStrategy::SetDefaultPickPriorities()
{
    PickPriority* begin = 0;
    PickPriority* end   = 0;
    PickPriority* cap   = 0;

    PickPriority rec;
    u32 ids[] = {
        0x137e8e0, 0x436f315, 0xecade42, 0xff10521, 0x1a55e4d,
        0x137e8e0, 0x175cdc9, 0x1007ae63, 0xd0036e08
    };
    int prios[] = { 1, 0, 0, 0, 0, 2, 0, 0, 0 };

    for (int i = 0; i < 9; i++) {
        rec.mId = ids[i];
        rec.mPriority = prios[i];
        rec.mWeight = 100;
        if (end < cap) {
            if (end) *end = rec;
            end++;
        } else {
            FUN_00b535d0(end, &rec);
            end = cap; // slow path reallocates; approximate
        }
    }

    PickWorld* w = (PickWorld*)FUN_00b3d240();
    ((void(__thiscall**)(PickWorld*, PickPriority**, int))(*(char**)w + 0x2c))[0](w, &begin, 1);
    (void)end;
}

// ---------------------------------------------------------------------------------------------
// 0x00cf2b70 -- pick-priority registrar (variant B).
// ---------------------------------------------------------------------------------------------
// @ 0x00cf2b70
void __fastcall FUN_00cf2b70(void* ecx_this, void* edx)
{
    PickPriority* begin = 0;
    PickPriority* end   = 0;
    PickPriority* cap   = 0;

    PickPriority rec;
    u32 ids[] = {
        0x137e8e0, 0x436f315, 0xecade42, 0xff10521,
        0x1a55e4d, 0x4f176642, 0x1007ae63, 0xd0036e08
    };
    for (int i = 0; i < 8; i++) {
        rec.mId = ids[i];
        rec.mPriority = 0;
        rec.mWeight = 100;
        if (end < cap) {
            if (end) *end = rec;
            end++;
        } else {
            FUN_00b535d0(end, &rec);
            end = cap;
        }
    }
    PickWorld* w = (PickWorld*)FUN_00b3d240();
    ((void(__thiscall**)(PickWorld*, PickPriority**, int))(*(char**)w + 0x2c))[0](w, &begin, 1);
    (void)end;
}

// ---------------------------------------------------------------------------------------------
// 0x00cf2d60 -- pick-priority registrar (variant C).
// ---------------------------------------------------------------------------------------------
// @ 0x00cf2d60
void __fastcall FUN_00cf2d60(void* ecx_this, void* edx)
{
    PickPriority* begin = 0;
    PickPriority* end   = 0;
    PickPriority* cap   = 0;

    PickPriority rec;
    u32 ids[] = {
        0x137e8e0, 0xecade42, 0xff10521, 0x1a55e4d, 0x4f176642,
        0xaeb336b4, 0xd0036e08, 0xce9f6639, 0x1007ae63
    };
    for (int i = 0; i < 9; i++) {
        rec.mId = ids[i];
        rec.mPriority = 0;
        rec.mWeight = 100;
        if (end < cap) {
            if (end) *end = rec;
            end++;
        } else {
            FUN_00b535d0(end, &rec);
            end = cap;
        }
    }
    PickWorld* w = (PickWorld*)FUN_00b3d240();
    ((void(__thiscall**)(PickWorld*, PickPriority**, int))(*(char**)w + 0x2c))[0](w, &begin, 1);
    (void)end;
}

// ---------------------------------------------------------------------------------------------
// 0x00cf2520 -- cCityInputStrategy::EndSelection  (ret 0xc)
// ---------------------------------------------------------------------------------------------
// @ 0x00cf2520
bool cCityInputStrategy::EndSelection(const Vec3* dir, const void* picked)
{
    (void)picked;
    int success = 0;

    TerrainCursor* c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, int))(*(char**)c + 0xb8))[0](c, 0);
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*))(*(char**)c + 0xa4))[0](c);
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, float))(*(char**)c + 0xac))[0](c, 1.0f);
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, float))(*(char**)c + 0xb0))[0](c, 1.0f);

    void* mgr = FUN_0067cab0(0x1002);
    FUN_00801bb0(mgr, 0x1002);

    if ((success & 2) == 0) {
        return success;
    }

    // gather the picked spatial list
    RefList list;
    list.mBegin = 0; list.mEnd = 0; list.mCap = 0;
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, void*))(*(char**)c + 0x5c))[0](c, &list);

    if (list.mBegin == list.mEnd) {
        success = 1;
    } else {
        float len2 = dir->x * dir->x + dir->y * dir->y + dir->z * dir->z;
        if (len2 > gZeroF) {
            // build a circle at the picked position and try to place vehicles
            FUN_00b3d290();
            void* gd = FUN_00ac15e0(0);
            FUN_00afba10(0);
            int n = FUN_00af9dd0(16.0f, (int)((char*)list.mEnd - (char*)list.mBegin) >> 2);
            Vec3 facing = gSurfaceDir;
            void* planet = FUN_00b3d350();
            FUN_00b7f190(planet, &facing, dir);
            FUN_00af9cf0((float*)dir, (float)n + 16.0f, (float*)&facing, 0.0f);
            FUN_00afef10(0, 16.0f);
            char* vec = (char*)this + 0xe8;
            void* first = *(void**)(vec);
            void* last  = *(void**)(vec + 4);
            FUN_00e25bd0(vec, first, last);
        }
    }
    (void)success;
    return false;
}

} // namespace SP
