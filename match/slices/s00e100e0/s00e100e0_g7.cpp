// Slice s00e100e0 (gold7) -- cSPUIMinimapWin icon vector + notification helpers.
// The container is an EASTL vector of 0x14-byte records (cRec14) held as three
// pointers: begin, end, capacity (the record is refcounted, see s00e0c2a0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast
#include "types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

#pragma warning(disable : 4100)

// ---------------------------------------------------------------------------
// refcounted sub-record embedded at offset +0x04 of cRec14 (see s00e0df70,
// whose RefHolder::Assign is the 0x00e0ea40 body).
// ---------------------------------------------------------------------------
struct cRecSub {
    void* mp00;                         // +0x00
    u8    mb04;                         // +0x04
    u8    mPad05[3];                    // +0x05
    void* mp08;                         // +0x08  (refcounted interface)
    void* mp0c;                         // +0x0c  (refcounted interface)

    cRecSub* Assign(const cRecSub* o);  // 0x00e0ea40 (thiscall, this = dst)
};

// ---------------------------------------------------------------------------
// 0x14-byte refcounted record stored in the vector.
// ---------------------------------------------------------------------------
struct cRec14 {
    u32     mField00;                   // +0x00
    cRecSub mSub;                       // +0x04

    cRec14* Copy(const cRec14* src);    // 0x00e0c670 (thiscall, this = dst)
};

// record range copy / destroy helpers from s00e0c2a0.
void*   __cdecl CopyRecRange(void* first, void* last, void* dst);        // 0x00e0c710
void*   __cdecl DestroyRecRange(void* first, void* last, void* dst);     // 0x00e0c780
void*   __cdecl MoveBack(const void* src, void* first, void* last);      // 0x00e0f050

extern void* g_allocator;              // 0x013ebb38

// operators used by the allocation path.
void* __cdecl operator_new_rec(u32 size, const char* file, int line,
                               int a, void* alloc, int c);      // 0x00f473a0
void  __cdecl operator_delete_rec(void* p);                     // 0x00f47380

// ---------------------------------------------------------------------------
// EASTL-style vector of cRec14 (three pointers).
// ---------------------------------------------------------------------------
struct VecRec14 {
    cRec14* mpBegin;                    // +0x00
    cRec14* mpEnd;                      // +0x04
    cRec14* mpCap;                      // +0x08

    void    DoInsertValue(cRec14* pos, const cRec14* value);    // 0x00e100e0
    cRec14* insert(cRec14* pos, const cRec14* value);           // 0x00e10c10
};

// @ 0x00e100e0
void VecRec14::DoInsertValue(cRec14* pos, const cRec14* value)
{
    if (mpEnd != mpCap) {
        if (pos <= value && value < mpEnd)
            value = value + 1;
        if (mpEnd != 0)
            mpEnd->Copy(mpEnd - 1);
        MoveBack(pos, mpEnd - 1, mpEnd);
        pos->mField00 = value->mField00;
        pos->mSub.Assign(&value->mSub);
        mpEnd = mpEnd + 1;
        return;
    }

    int count = (int)((char*)mpEnd - (char*)mpBegin) / 0x14;
    int newCap;
    cRec14* newBuf;
    if (count == 0) {
        newCap = 1;
    } else {
        newCap = count * 2;
        if (newCap == 0) {
            newBuf = 0;
            goto build;
        }
    }
    newBuf = (cRec14*)operator_new_rec(newCap * 0x14, "Simulator", 0, 0,
                                       g_allocator, 0xd1);
build:
    {
        cRec14* oldBegin = mpBegin;
        cRec14* mid = (cRec14*)CopyRecRange(oldBegin, pos, newBuf);
        DestroyRecRange(oldBegin, pos, newBuf);
        if (mid != 0)
            mid->Copy(value);
        cRec14* after = (cRec14*)CopyRecRange(pos, mpEnd, mid + 1);
        DestroyRecRange(pos, mpEnd, mid + 1);
        if (mpBegin != 0)
            operator_delete_rec(mpBegin);
        mpEnd = after;
        mpBegin = newBuf;
        mpCap = newBuf + newCap;
    }
}

// @ 0x00e10c10
cRec14* VecRec14::insert(cRec14* pos, const cRec14* value)
{
    int idx = (int)((char*)pos - (char*)mpBegin) / 0x14;
    cRec14* end = mpEnd;
    if (pos == end && end != mpCap) {
        mpEnd = end + 1;
        if (end != 0)
            end->Copy(value);
    } else {
        DoInsertValue(pos, value);
    }
    return mpBegin + idx;
}

// ===========================================================================
//  Minimap window notification handler + teardown (gold7 00e10220 / 00e10c80).
//  Member offsets are named; both routines share the helper set used by the
//  pre-existing 00e10580 AddIcon (same object).
// ===========================================================================

// A refcounted interface with a virtual Release at slot +0x04 (and +0x08).
class IRefcount {
public:
    virtual int  AddRef();                          // +0x00
    virtual int  Release();                         // +0x04
    virtual int  v08();                             // +0x08
};

// Queryable object (virtual Query at +0x0c, slot +0x1c returns a value).
class IUnknownInt {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Query(unsigned id);                // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void* v1c();                             // +0x1c
};

class IWindowInt {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual float* GetArea();                        // +0x34
    virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60();
    virtual void SetVisible(int v);                  // +0x64
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, int enable);      // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(float* out, float a, int b);    // +0xc0
};

struct cFeedbackEvent {
    IUnknownInt* mpObject;              // +0x00
    u32          mField04;              // +0x04
    u32          mMessageId;            // +0x08
    u32          mField0c;              // +0x0c
    u32          mField10;              // +0x10
    u32          mField14;              // +0x14
    u32          mFlags18;              // +0x18
    u32          mField1c;              // +0x1c
    u32          mField20;              // +0x20
    u32          mField24;              // +0x24
    void*        mpCity;                // +0x28
};

struct cIconInfo;

// Foreign entry points.
void* __cdecl SP_PlanetModel();                                 // 0x00b3d350
void* __cdecl SP_GetCurrentGameMode();                          // 0x00b5b800
void* __cdecl SP_NounManager(void*);                            // 0x00b3d300
float* __cdecl SP_PlanetModel_DirectionToSurfacePosition(void* model, float* out, float* dir);  // 0x00b815a0
void* __cdecl cSPUIPropertyLayout_GetRootWindow(void* layout);  // 0x00828100
void* __cdecl FUN_0067cab0(int a);                              // 0x0067cab0
bool  __cdecl FUN_008017f0(void* p);                            // 0x008017f0
void* __cdecl FUN_00b1fc00(unsigned id);                        // 0x00b1fc00
void* __cdecl FUN_00c6aa30(void* p);                            // 0x00c6aa30
void* __cdecl FUN_010666a0(void* a, void* b);                   // 0x010666a0
void  __cdecl FUN_01067e70(void* a, void* b);                   // 0x01067e70
void  __cdecl FUN_00e2e8d0(void* a, int b, int c, void* d);     // 0x00e2e8d0
bool  __cdecl FUN_00950bb0(void* event);                        // 0x00950bb0
void  __cdecl FUN_00e0b990(void* self, void* pos, u32 flags, int a, int b);   // 0x00e0b990
void* __cdecl FUN_00e0ff80(void* tree, const unsigned* key, void* out);       // 0x00e0ff80
void  __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e);      // 0x00571db0
void* __cdecl FUN_00bdde70(void* self, void* city);             // 0x00bdde70
void* __cdecl FUN_00bd9bf0(void* city);                         // 0x00bd9bf0
void  __cdecl FUN_00b25f40(void* p);                            // 0x00b25f40
void  __cdecl FUN_00e0f160(void* node);                         // 0x00e0f160
void* __cdecl FUN_00e0f010(void* a, void* b, void* c);          // 0x00e0f010
void* __cdecl FUN_00e0e9a0(void* a, void* b);                   // 0x00e0e9a0
void* __cdecl eastl_rbtree_find(void* out, void* tree, const void* key);   // 0x00e5c780
// Foreign helpers modelled as member calls so `this` travels in ECX.
struct CBaseWindow {
    void Shutdown();                    // 0x00961e80
};
struct CVec3Store {
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void* erase(void* a, void* b);      // 0x0050f740
};
void* __cdecl FUN_00b5f950(void* self, void* p);                // 0x00b5f950

extern u32 g_modeCityHall;              // 0x01654c04
extern u32 g_modeTribe;                 // 0x01654c05
extern void* g_feedbackBegin;           // 0x016a204c
extern void* g_feedbackEnd;             // 0x016a2050
extern const float g_halfConst;         // 0x01471064 (=0.5f)

struct CMinimapWin {
    unsigned char mPad000[4];
    void*        mpWinIface;            // +0x004
    unsigned char mPad008[0x224 - 8];
    IRefcount*   mpHandlerTarget;       // +0x224
    void*        mHandlerArg228;        // +0x228
    void*        mHandlerArg22c;        // +0x22c
    void*        mHandlerArg230;        // +0x230
    void*        mHandlerArg234;        // +0x234
    unsigned char mPad238[0x244 - 0x238];
    IRefcount*   mpRef244;              // +0x244
    IRefcount*   mpRef248;              // +0x248
    IRefcount*   mpRef24c;              // +0x24c
    IRefcount*   mpRef250;              // +0x250
    IRefcount*   mpRef254;              // +0x254
    IRefcount*   mpRef258;              // +0x258
    unsigned char mPad25c[0x27c - 0x25c];
    u32          mField27c;             // +0x27c
    unsigned char mPad280[0x320 - 0x280];
    void*        mpTreeAnchor;          // +0x320
    void*        mpTreeEnd;             // +0x324
    void*        mpTreeRoot;            // +0x328
    u8           mbTreeFlag;            // +0x32c
    unsigned char mPad32d[3];
    u32          mTreeCount;            // +0x330
    unsigned char mPad334[0x368 - 0x334];
    void*        mVecBegin;             // +0x368
    void*        mVecEnd;               // +0x36c
    unsigned char mPad370[0x980 - 0x370];
    IRefcount*   mpRef980;              // +0x980
    IRefcount*   mpRef984;              // +0x984
    IRefcount*   mpRef988;              // +0x988

    bool HandleNotification(cFeedbackEvent* event);     // 0x00e10220
    void Shutdown();                    // 0x00e10c80
};

// @ 0x00e10220
bool CMinimapWin::HandleNotification(cFeedbackEvent* event)
{
    float pos[3];
    void* self = this;
    if (event->mMessageId == 0x287259f6) {
        if (SP_PlanetModel()) {
            void* obj = event->mpObject;
            void* dir = (*(void* (__thiscall**)(void*))(*(u32*)obj + 0x1c))(obj);
            void* v = &dir;
            cIconInfo* info = (cIconInfo*)FUN_00e0ff80((char*)self + 0x31c, (const unsigned*)v, v);
            void* p = (char*)info + 4;
            SP_PlanetModel_DirectionToSurfacePosition(SP_PlanetModel(), pos, (float*)p);
            u32 flags = (~(event->mFlags18 >> 2) & 2) | 0x3e8;
            FUN_00e0b990(self, pos, flags, 0, 0);
        }
        return true;
    }

    if (event->mMessageId != 0x13 || event->mpObject == 0)
        goto l_ret;

    {
        void* obj = event->mpObject;
        void* found = (*(void* (__thiscall**)(void*, unsigned))(*(u32*)obj + 0xc))(obj, 0x8ed27e7a);
        if (!found)
            goto l_ret;

        void* obj2 = event->mpObject;
        u32 v = (u32)(*(void* (__thiscall**)(void*))(*(u32*)obj2 + 0x1c))(obj2);

        u32 f0c = event->mField0c;
        u32 f10 = event->mField10;
        if (((f0c >> 3) & 1) == 0) {
            if (((f10 >> 3) & 1) != 0) {
                void* layout = *(void**)((char*)self + 0x988);
                if (*(char*)((char*)layout + 0x44) != 0) {
                    void* root = cSPUIPropertyLayout_GetRootWindow(layout);
                    (*(void (__thiscall**)(void*, int, int))(*(u32*)root + 0x7c))(root, 1, 0);
                    layout = *(void**)((char*)self + 0x988);
                    (*(void (__thiscall**)(void*))(*(u32*)layout + 0x24))(layout);
                }
                FUN_0067cab0(0);
                FUN_008017f0(0);
                void* h = *(void**)((char*)self + 0x980);
                if (h != 0) {
                    *(void**)((char*)self + 0x980) = 0;
                    (*(void (__thiscall**)(void*))(*(u32*)h + 4))(h);
                    return FUN_00950bb0(event);
                }
            }
            goto l_ret;
        }

        if (((f10 >> 3) & 1) != 0)
            goto l_ret;

        void* it;
        eastl_rbtree_find(&it, (char*)self + 0x31c, &v);
        if (it == (char*)self + 0x320)
            goto l_ret;

        {
            void* city = *(void**)((char*)it + 0x28);
            u32 key10 = *(u32*)((char*)it + 0x10);
            if (city == 0)
                goto l_ret;
            u32 fl = *(u32*)((char*)it + 0x24);
            if (fl & 1) {
                if (SP_GetCurrentGameMode() == &g_modeCityHall) {
                    void* layout = *(void**)((char*)self + 0x988);
                    (*(void (__thiscall**)(void*, unsigned))(*(u32*)layout + 0x28))(layout, 0x5b598f6);
                    FUN_00bdde70(layout, city);
                    void* root = cSPUIPropertyLayout_GetRootWindow(layout);
                    void* btn = (*(void* (__thiscall**)(void*, int))(*(u32*)found + 0x10))(found, 0);
                    void* bwin = (*(void* (__thiscall**)(void*))(*(u32*)btn + 0x10))(btn);
                    float* area = (*(float* (__thiscall**)(void*))(*(u32*)bwin + 0x34))(bwin);
                    (*(void (__thiscall**)(void*, float*, float, int))(*(u32*)btn + 0xc0))(btn, pos, (area[2] - area[0]) * g_halfConst, 0);
                    (*(void (__thiscall**)(void*, void*, void*, void*))(*(u32*)root + 0x34))(root, &pos[0], &pos[1], &pos[2]);
                    FUN_00e2e8d0(btn, 0, 0x41600000, 0);
                    (*(void (__thiscall**)(void*, void*, void*))(*(u32*)root + 0x64))(root, 0, 0);
                    (*(void (__thiscall**)(void*, int, int))(*(u32*)root + 0x7c))(root, 1, 1);
                }
                FUN_00b5f950((char*)self + 0x980, FUN_00bd9bf0(city));
            } else if (fl & 0x100) {
                void* p = (*(void* (__thiscall**)(void*))(*(u32*)city + 0x10))(city);
                FUN_00b25f40(SP_NounManager(p));
                FUN_00b5f950((char*)self + 0x980, FUN_00bd9bf0(city));
            } else if (fl & 0x4000) {
                void* r = (*(void* (__thiscall**)(void*))(*(u32*)city + 0x4c))(city);
                if (r != (void*)-1) {
                    r = (*(void* (__thiscall**)(void*))(*(u32*)city + 0x4c))(city);
                    FUN_00b25f40(SP_NounManager(r));
                    FUN_00b5f950((char*)self + 0x980, FUN_00bd9bf0(city));
                }
            } else if (fl & 0x20) {
                SP_GetCurrentGameMode();
                if (SP_GetCurrentGameMode() == &g_modeTribe) {
                    void* win = (*(void* (__thiscall**)(void*, u32, int))(*(u32*)((char*)self + 4) + 0xf0))((char*)self + 4, key10, 1);
                    if (win) {
                        void* city2 = FUN_00b1fc00(*(u32*)((char*)it + 0x28));
                        if (city2) {
                            void* q = FUN_00c6aa30(city2);
                            if (q) {
                                void* arg = (char*)q + 0x504;
                                void* r = FUN_010666a0(win, arg);
                                FUN_01067e70(r, arg);
                            }
                        }
                    }
                }
            }
        }
    }

l_ret:
    return FUN_00950bb0(event);
}

// @ 0x00e10c80
void CMinimapWin::Shutdown()
{
    if (mpHandlerTarget != 0) {
        IRefcount* h = mpHandlerTarget;
        mpHandlerTarget = 0;
        FUN_00571db0(h, mHandlerArg228, mHandlerArg22c, mHandlerArg230, mHandlerArg234);
    }
    if (mpRef24c != 0) { IRefcount* p = mpRef24c; mpRef24c = 0; p->Release(); }
    if (mpRef250 != 0) { IRefcount* p = mpRef250; mpRef250 = 0; p->Release(); }
    if (mpRef258 != 0) { IRefcount* p = mpRef258; mpRef258 = 0; p->v08(); }
    if (mpRef244 != 0) { IRefcount* p = mpRef244; mpRef244 = 0; p->Release(); }
    if (mpRef248 != 0) { IRefcount* p = mpRef248; mpRef248 = 0; p->Release(); }
    mField27c = 0;
    if (mpRef254 != 0) { IRefcount* p = mpRef254; mpRef254 = 0; p->Release(); }

    FUN_00e0f160(mpTreeRoot);
    mpTreeAnchor = (char*)this + 0x320;
    mpTreeEnd = (char*)this + 0x320;
    mpTreeRoot = 0;
    mbTreeFlag = 0;
    mTreeCount = 0;

    if (mpRef988 != 0) { IRefcount* p = mpRef988; mpRef988 = 0; p->Release(); }

    ((CVec3Store*)&mVecBegin)->erase(mVecEnd, mVecBegin);

    {
        void* begin = g_feedbackBegin;
        void* end = g_feedbackEnd;
        void* r = FUN_00e0f010(end, end, begin);
        FUN_00e0e9a0(r, g_feedbackEnd);
        int n = (int)((char*)begin - (char*)end) / 0x14;
        g_feedbackEnd = (char*)end + n * 0x14;
    }

    if (mpRef980 != 0) { IRefcount* p = mpRef980; mpRef980 = 0; p->Release(); }
    if (mpRef984 != 0) { IRefcount* p = mpRef984; mpRef984 = 0; p->Release(); }
    ((CBaseWindow*)this)->Shutdown();
}
