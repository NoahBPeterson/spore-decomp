// Slice s006775f0: Simulator::cSpaceInventory (UI inventory panel): ctor/dtor, item refresh,
// two message handlers, EA::RectT<float>::Contains, window-tree find callbacks (AutoRefCount
// handoff), and an eastl::deque<T(0x134),4> DequeBase::DoReallocPtrArray / DoInit.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc in this module).
#include "types.h"

typedef unsigned int uint32_t;

void  EAFree(void* p);                                                                    // 0x00F47380
void* EAAllocate(uint32_t n, const char* name, int a, int b, const char* file, int line);  // 0x00F473A0

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, uint32_t);

inline const unsigned& MaxU(const unsigned& a, const unsigned& b) { return (a < b) ? b : a; }

// ---------------------------------------------------------------------------
// generic refcounted object (vt0 = AddRef, vt1 = Release)
// ---------------------------------------------------------------------------
struct CamObj0;
struct RectF {
    float mLeft, mTop, mRight, mBottom;
    int Contains(float x, float y);   // 0x00677E80
};

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float px, float py) { x = px; y = py; }
    Vector2(const Vector2& o) { x = o.x; y = o.y; }
};

struct RefObj {
    virtual void AddRef();                      // +0x00
    virtual void Release();                     // +0x04
    virtual void v02();
    virtual int GetSub(int key);                // +0x0c = slot 3
    virtual CamObj0* GetCam();                  // +0x10 = slot 4
    virtual void v05(); virtual void v06();
    virtual int  GetType();                     // +0x1c = slot 7
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
    virtual void v0C(); virtual void v0D();
    virtual void* GetRect2();                   // +0x38 = slot 14
    virtual void v0F(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual int  GetSelf();                     // +0x4c = slot 19
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v1B(); virtual void v1C(); virtual void v1D(); virtual void v1E();
    virtual void SetView(float x, float y);     // +0x70 = slot 28
    virtual void v1F(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24();
    virtual void SetSel(void*);                 // +0x8c = slot 35
    virtual void Refresh();                     // +0x90 = slot 36
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v2A(); virtual void v2B(); virtual void v2C();
    virtual RefObj* GetData(int key);           // +0xb4 = slot 45
    virtual void SetData(int key, void* val);   // +0xb8 = slot 46
    virtual void v2F(); virtual void v30(); virtual void v31(); virtual void v32();
    virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
    virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v3A(); virtual void v3B(); virtual void v3C(); virtual void v3D();
    virtual void v3E(); virtual void v3F(); virtual void v40();
    virtual void HandleSelect(void*);           // +0x104 = slot 65
};

// camera object returned by RefObj::GetCam
struct CamObj0 {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c0A(); virtual void c0B();
    virtual void c0C(); virtual void c0D(); virtual void c0E(); virtual void c0F();
    virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13();
    virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17();
    virtual void c18(); virtual void c19(); virtual void c1A(); virtual void c1B();
    virtual void c1C(); virtual void c1D(); virtual void c1E(); virtual void c1F();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
    virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
    virtual void c28(); virtual void c29(); virtual void c2A(); virtual void c2B();
    virtual void c2C(); virtual void c2D(); virtual void c2E(); virtual void c2F();
    virtual void c30();
    virtual void ShowVec(Vector2 v, Vector2* out);   // +0xc4 = slot 49
    virtual void c50(); virtual void c51(); virtual void c52(); virtual void c53();
    virtual void c54(); virtual void c55(); virtual void c56(); virtual void c57();
    virtual void SetThing(void*);               // +0xe8 = slot 58
};

// window with the layout vtable
struct LayoutWin {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
    virtual void v0C(); virtual void v0D();
    virtual void* GetRect();                    // +0x38 = slot 14
    virtual void v0F(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void SetImage(uint32_t);            // +0x5c = slot 23
    virtual void v18b(); virtual void v19b(); virtual void v19c();
    virtual void Move(struct RectF*);           // +0x6c = slot 27
    virtual void v1Cb(); virtual void v1Db(); virtual void v1Eb();
    virtual void SetState(int a, int b);        // +0x7c = slot 31
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2A(); virtual void v2B();
    virtual void v2C(); virtual void v2D(); virtual void v2E(); virtual void v2F();
    virtual void v30();
    virtual void ShowVec2(Vector2 v, void* p);  // +0xc4 = slot 49
};

struct cSPUILayout {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    LayoutWin* FindWindowByID(int id, int b);   // 0x008105B0
};

// ---------------------------------------------------------------------------
// property helpers (externals)
// ---------------------------------------------------------------------------
struct Key { uint32_t instanceID; uint32_t typeID; uint32_t groupID; };

struct PropMgr {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p0A();
    virtual bool GetOrCreate(uint32_t id, uint32_t group, void* out);   // +0x2c = slot 11
};

void* __cdecl GetPropertyManager();                                        // 0x0067DE30
bool  __cdecl GetPropertyAsText(void* src, uint32_t key, void* dst);        // 0x006A1360
bool  __cdecl GetPropertyAsColorRGB(void* src, uint32_t key, void* dst);    // 0x006A11B0
bool  __cdecl GetPropertyAsKey(void* src, uint32_t key, void* dst);         // 0x006A1250
bool  __cdecl GetPropertyAsKeyInstance(void* src, uint32_t key, void* dst); // 0x006A12A0
struct SlotEnt { uint32_t a, b, c; };
bool  __cdecl GetFloatArray(void* src, uint32_t key, uint32_t* cnt, SlotEnt** dst); // 0x006A0AE0

struct String16 {                     // basic_string at +0x54 (16 bytes with allocator)
    char pad[16];
    String16();                       // 0x006B5060
    ~String16();                      // 0x006B5240
    const wchar_t* c_str();           // 0x006B55C0
};

// string temp built by RangeInitialize (12 bytes), dtor = dealloc guard
struct StrTemp {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacityEnd;
    void RangeInitialize(const wchar_t* psz);   // 0x00579A90
    ~StrTemp() {
        if ((((int)((char*)mpCapacityEnd - (char*)mpBegin)) & -2) > 2 && mpBegin)
            EAFree(mpBegin);
    }
};

// eastl vector<bool>-like member (12 bytes; fixed empty repr at 0x01667BAC)
void* gpEmptyVec;   // 0x01667BAC

struct VecB {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacityEnd;
    VecB() { mpBegin = &gpEmptyVec; mpEnd = &gpEmptyVec; mpCapacityEnd = (char*)&gpEmptyVec + 2; }
    ~VecB() {
        if ((((int)((char*)mpCapacityEnd - (char*)mpBegin)) & -2) > 2 && mpBegin)
            EAFree(mpBegin);
    }
    void clear() {
        if (mpBegin != mpEnd) {
            *(unsigned short*)mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    void assign(const wchar_t*);        // 0x005C3D90
};

struct Variant {                    // EA::Variant-ish, 16 bytes
    char pad[12];
    int  mFlags;
    void Init(StrTemp* arg);        // 0x005A74A0
    void Destruct(int a);           // 0x0093DB80
};

// ---------------------------------------------------------------------------
// cSpaceInventory
// ---------------------------------------------------------------------------
struct IWinProcVt {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
    virtual void Refresh();         // +0x20 = slot 8 on the inventory vtable
};
struct RefCountVt { virtual void r00(); };

struct cSPUIPropertyLayout : IWinProcVt, RefCountVt {
    char pad8[4];                               // +0x08
    cSPUILayout mLayout;                        // +0x0c
    char pad10[0x14];                           // +0x10..0x24
    char pad24[0x54];                           // +0x24..0x78
    void SetFlag(bool b);                       // 0x00828020 (writes +0x74)
    void SetCargoKey(uint32_t a, uint32_t b);   // 0x00827FA0 (writes +0x24/+0x28)
    cSPUIPropertyLayout();                      // 0x008286D0
    ~cSPUIPropertyLayout();                     // 0x00828670
};

void __cdecl DoScreenThing(void* a, void* b, void* c);                  // 0x00808B20
void __cdecl GetBoundingScreenRect(void* rect, void* w);                // 0x00808D20
uint32_t __cdecl FloatToByte(void* v);                                  // 0x00458A40
void __cdecl VisitWindowTreeDepthFirst(void* root, bool(__cdecl*cb)(RefObj*, void*), void* ctx); // 0x00807D30
void* __cdecl CopyPtrs(void* dst, void* src, uint32_t n);               // 0x011E0744
bool  __cdecl ThingIsA(void* p);                                        // 0x008050B0

extern float gS1471064;   // 0x01471064
extern float gS1485378;   // 0x01485378
extern float gS1486110;   // 0x01486110

struct cSpaceInventory : cSPUIPropertyLayout {
    struct RcN { RefObj* p; RcN() : p(0) {} ~RcN() { if (p) p->Release(); }
                 void reset() { RefObj* q = p; if (q) { p = 0; q->Release(); } } };
    RcN      m78;       // +0x78
    RcN      m7c;       // +0x7c
    RcN      m80;       // +0x80
    VecB     mVec84;    // +0x84
    char     pad90[4];  // +0x90
    int      m94;       // +0x94
    bool     mb98;      // +0x98
    char     pad99[3];
    uint32_t m9c;       // +0x9c

    cSpaceInventory();                                  // 0x006775F0
    ~cSpaceInventory();                                 // 0x00677670
    void Update(bool bEnable, Key* key, uint32_t c);    // 0x00677700
    bool HandleMsgA(uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00677D90
    bool HandleMsgB(uint32_t a, uint32_t b, uint32_t c);              // 0x00677DF0
    void SetMaxCargoAmount(uint32_t n);                 // 0x00C87BC0 (external)
    void ShowInv(uint32_t a);                           // 0x00677190 (external)
    void SelectItem(LayoutWin* w, Key* key);            // 0x00677530 (external)
    void DoLayoutThing(void* a, Variant* v, int b, int c); // 0x00828C30 (external)
};

extern "C" bool __stdcall ShowThing(uint32_t a, uint32_t b, uint32_t c);   // 0x00677220

// @ 0x006775F0
cSpaceInventory::cSpaceInventory()
{
    m9c = 0;
    SetCargoKey((mb98 = 1, 0x646739ac), *(uint32_t*)0x0152976c);
    SetMaxCargoAmount(0x125f2c4f);
}

// @ 0x00677670
cSpaceInventory::~cSpaceInventory()
{
}

// @ 0x00677700
void cSpaceInventory::Update(bool bEnable, Key* key, uint32_t c)
{
    m9c = key->instanceID;
    if (m78.p)
    {
        SetFlag(bEnable);
        if (bEnable)
        {
            if (m78.p->GetCam()) {
                CamObj0* pCam = m78.p->GetCam();
                pCam->SetThing(m78.p);
            }
            RcN* pSel = &m80;
            PropMgr* pMgr = (PropMgr*)GetPropertyManager();
            pSel->reset();
            if (pMgr->GetOrCreate(key->instanceID, key->groupID, pSel))
            {
                String16 str;
                mVec84.clear();
                if (GetPropertyAsText(pSel->p, 0x54d95160, &str))
                {
                    {
                        StrTemp t2;
                        const wchar_t* psz = str.c_str();
                        t2.mpBegin = 0; t2.mpEnd = 0; t2.mpCapacityEnd = 0;
                        t2.RangeInitialize(psz);
                        Variant v;
                        v.Init(&t2);
                        DoLayoutThing((void*)0x6036c70, &v, 1, 0);
                        if (v.mFlags & 4)
                            v.Destruct(0);
                    }
                    mVec84.assign(str.c_str());
                }
                uint32_t color[4];
                if (GetPropertyAsColorRGB(pSel->p, 0xd4f639cd, &color))
                {
                    uint32_t colorByte = FloatToByte(&color);
                    LayoutWin* w1 = mLayout.FindWindowByID(0x54f63a3e, 1);
                    if (w1)
                        w1->SetImage(colorByte);
                    LayoutWin* w2 = mLayout.FindWindowByID(0x667d3f8, 1);
                    if (w2)
                        w2->SetImage(colorByte);
                }
                LayoutWin* w3 = mLayout.FindWindowByID(0x603a678, 1);
                if (w3)
                {
                    Key key2;
                    key2.instanceID = 0; key2.typeID = 0; key2.groupID = 0;
                    if (GetPropertyAsKey(pSel->p, 0x54d95162, &key2))
                        SelectItem(w3, &key2);
                }
                m94 = 0;
                if (GetPropertyAsKeyInstance(pSel->p, 0x54d95164, &m94))
                {
                    int page = 0;
                    switch (m94)
                    {
                        case (int)0xa426730b: page = 0x6133600; break;
                        case (int)0xad56080c: page = 0x6133601; break;
                        case (int)0xf71fa311: page = 0x6133602; break;
                        case (int)0xbeb528cb: page = 0x6133603; break;
                        case (int)0x2db6dad3: page = 0x6133604; break;
                    }
                    for (int id = 0x6133600; id < 0x6133605; ++id)
                    {
                        LayoutWin* w = mLayout.FindWindowByID(id, 1);
                        if (w) {
                            bool bSel = (id == page);
                            w->SetState(1, bSel);
                        }
                    }
                }
                float fWidth = 0.0f;
                uint32_t count = 0;
                SlotEnt* arr = 0;
                GetFloatArray(pSel->p, 0x54d95163, &count, &arr);
                int nSkip = 4 - (int)count;
                for (int i = 0; i < 4; ++i)
                {
                    bool bValid = (i >= nSkip);
                    LayoutWin* w = mLayout.FindWindowByID(0x4c01bbe + i, 1);
                    if (w)
                    {
                        RectF* r = (RectF*)w->GetRect();
                        fWidth = r->mRight - r->mLeft;
                        w->SetState(1, bValid);
                    }
                    if (bValid)
                    {
                        RcN sel2;
                        PropMgr* pm2 = (PropMgr*)GetPropertyManager();
                        sel2.reset();
                        if (pm2->GetOrCreate(arr[i - nSkip].a, 0x449505af, &sel2))
                        {
                            Key k2;
                            k2.instanceID = 0; k2.typeID = 0; k2.groupID = 0;
                            if (GetPropertyAsKey(sel2.p, 0xd4d959e2, &k2))
                                SelectItem(w, &k2);
                            if (m7c.p)
                                w->SetState(0x10, 0);
                        }
                    }
                }
                {
                    // reposition the selected-tool window by how many slots are filled
                    LayoutWin* wa = mLayout.FindWindowByID(0x54f63a3e, 1);
                    uint32_t kk = 0;
                    switch ((int)count)
                    {
                        case 1: kk = 0xd570ede2; break;
                        case 2: kk = 0xd570ede1; break;
                        case 3: kk = 0xd570ede0; break;
                    }
                    if (kk)
                    {
                        LayoutWin* wb = mLayout.FindWindowByID((int)kk, 1);
                        if (wb && wa)
                        {
                            if (fWidth > gS1485378)
                            {
                                RectF* r1p = (RectF*)wb->GetRect();
                                RectF rc1 = *r1p;
                                RectF* r2 = (RectF*)wa->GetRect();
                                float width1 = rc1.mRight - rc1.mLeft;
                                float width2 = r2->mRight - r2->mLeft;
                                float vx = (width2 - width1) * gS1471064 - (float)(3 - (int)count) * fWidth;
                                RectF nr;
                                nr.mLeft = vx; nr.mTop = rc1.mTop;
                                nr.mRight = width1 + vx; nr.mBottom = rc1.mBottom;
                                wb->Move(&nr);
                            }
                        }
                    }
                }
            }
            // part 2: camera-facing update
            if (c && m78.p && m78.p->GetCam())
            {
                if (!mb98)
                {
                    RectF rect;
                    GetBoundingScreenRect(&rect, (void*)c);
                    RectF* r = (RectF*)m78.p->GetRect2();
                    float width = r->mRight - r->mLeft + gS1486110;
                    float fx;
                    if (rect.mLeft >= width)
                        fx = rect.mLeft - width;
                    else
                        fx = rect.mRight + gS1486110;
                    float fy = rect.mTop + (rect.mBottom - rect.mTop) * gS1471064
                               - (r->mBottom - r->mTop) * gS1471064;
                    Vector2 vv(fx, fy);
                    Vector2 pos;
                    m78.p->GetCam()->ShowVec(vv, &pos);
                    m78.p->SetView(pos.x, pos.y);
                }
                else
                {
                    DoScreenThing((void*)c, m78.p, 0);
                }
            }
            Refresh();
        }
    }
}

// @ 0x00677D90
bool cSpaceInventory::HandleMsgA(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    bool r = ShowThing(a, 1, 1);
    ShowInv(b);
    Key key;
    key.instanceID = d;
    key.typeID = 0xb1b104;
    key.groupID = 0xf865c777;
    Update(1, &key, 0);
    return r;
}

// @ 0x00677DF0
bool cSpaceInventory::HandleMsgB(uint32_t a, uint32_t b, uint32_t c)
{
    bool r = ShowThing(a, 1, 1);
    ShowInv(b);
    Key key;
    key.instanceID = c;
    key.typeID = 0xb1b104;
    key.groupID = 0xf865c777;
    Update(1, &key, 0);
    return r;
}

// @ 0x00677E80
int RectF::Contains(float x, float y)
{
    return x >= mLeft && y >= mTop && x < mRight && y < mBottom;
}

// @ 0x00678000-forward decls
struct Slot { uint32_t mId; RefObj* mpObj; };

// ---------------------------------------------------------------------------
// window-tree find callbacks
// ---------------------------------------------------------------------------
struct FindCtx { RefObj* mpFound; bool mFlag; };

// @ 0x00677EC0
bool __cdecl FindCB(RefObj* pWin, FindCtx* pCtx)
{
    RefObj* found = pCtx->mpFound;
    if (pWin->GetSelf() != (int)found)
    {
        pWin->SetData(0x64e5a6a, found);
        pWin->SetData(0x64e5a6b, (void*)pWin->GetSelf());
        pWin->SetSel(found);
    }
    pWin->Refresh();
    return pCtx->mFlag;
}

// @ 0x00677F30
bool __cdecl FindAllCB(RefObj* pWin, FindCtx* pCtx)
{
    RefObj* pA = pWin->GetData(0x64e5a6a);
    int idA = pA ? pA->GetSub(0x6ed3e59b) : 0;
    RefObj* pB = pWin->GetData(0x64e5a6b);
    int idB = pB ? pB->GetSub(0x6ed3e59b) : 0;
    if (idA != 0)
        pWin->SetSel((void*)idB);
    pWin->SetData(0x64e5a6a, 0);
    pWin->SetData(0x64e5a6b, 0);
    pWin->Refresh();
    return pCtx->mFlag;
}

// @ 0x00677FE0
bool __cdecl SelectCB(RefObj* pWin, void* const* pp)
{
    pWin->HandleSelect((void*)*pp);
    return true;
}

// @ 0x00678000
bool __cdecl AcquireSlot(RefObj* pObj, Slot* pSlot)
{
    if (pObj->GetType() == pSlot->mId)
    {
        RefObj* pOld = pSlot->mpObj;
        if (pObj != pOld)
        {
            pObj->AddRef();
            pSlot->mpObj = pObj;
            if (pOld)
                pOld->Release();
        }
    }
    return pSlot->mpObj == 0;
}

// @ 0x00678050
bool __cdecl AcquireSlotIf(RefObj* pObj, Slot* pSlot)
{
    if (pObj->GetType() == pSlot->mId && ThingIsA(pObj))
    {
        RefObj* pOld = pSlot->mpObj;
        if (pObj != pOld)
        {
            pObj->AddRef();
            pSlot->mpObj = pObj;
            if (pOld)
                pOld->Release();
        }
    }
    return pSlot->mpObj == 0;
}

// @ 0x00678310
void __cdecl FindWindowShow(RefObj* pFind, void* pRoot, bool bFlag)
{
    FindCtx ctx;
    ctx.mpFound = 0;
    ctx.mFlag = bFlag;
    if (pFind)
    {
        pFind->AddRef();
        ctx.mpFound = pFind;
    }
    VisitWindowTreeDepthFirst(pRoot, (bool(__cdecl*)(RefObj*, void*))FindCB, &ctx);
    if (ctx.mpFound)
        ctx.mpFound->Release();
}

// @ 0x00678370
void __cdecl SelectWindow(RefObj* pWin, void* pRoot)
{
    RefObj* pFound = 0;
    if (pWin)
    {
        pWin->AddRef();
        pFound = pWin;
    }
    VisitWindowTreeDepthFirst(pRoot, (bool(__cdecl*)(RefObj*, void*))SelectCB, &pFound);
    if (pFound)
        pFound->Release();
}

// ---------------------------------------------------------------------------
// eastl::deque<Block308, alloc, 4> DequeBase
// ---------------------------------------------------------------------------
struct Block308 { char bytes[0x134]; };

struct DequeIt {
    Block308*  mpCurrent;
    Block308*  mpBegin;
    Block308*  mpEnd;
    char*      mpCurrentArrayPtr;   // byte-typed pointer into the ptr array
    void SetSubarray(void** p) {
        mpCurrentArrayPtr = (char*)p;
        mpBegin = (Block308*)*(void**)p;
        mpEnd = mpBegin + 4;
    }
};

struct DequeBaseB4 {
    void**       mpPtrArray;      // +0x00
    uint32_t     mnPtrArraySize;  // +0x04
    DequeIt      mItBegin;        // +0x08
    DequeIt      mItEnd;          // +0x18
    char         mAllocator[4];   // +0x28

    void** DoAllocatePtrArray(uint32_t n) { return (void**)EAAllocate(n * 4, "Editor", 0, 0, ALLOC_FILE, 0xd1); }
    Block308* DoAllocateSubarray() { return (Block308*)EAAllocate(0x4d0, "Editor", 0, 0, ALLOC_FILE, 0xd1); }

    void DoReallocPtrArray(uint32_t nAdditionalCapacity, int allocationSide);  // 0x006780A0
    void DoInit(uint32_t n);                                                   // 0x006781D0
};

// @ 0x006780A0
void DequeBaseB4::DoReallocPtrArray(uint32_t nAdditionalCapacity, int allocationSide)
{
    uint32_t nUsedPtrCount = ((mItEnd.mpCurrentArrayPtr - mItBegin.mpCurrentArrayPtr) >> 2) + 1;
    uint32_t nNeed = nUsedPtrCount + nAdditionalCapacity;
    void** pPtrArrayBegin;
    if (mnPtrArraySize <= nNeed * 2)
    {
        uint32_t nNewPtrArraySize = mnPtrArraySize + MaxU(mnPtrArraySize, nAdditionalCapacity) + 2;
        void** pNewPtrArray = DoAllocatePtrArray(nNewPtrArraySize);
        void** pBegin = (void**)mItBegin.mpCurrentArrayPtr;
        void** pOld = mpPtrArray;
        int nFront = ((char*)pBegin - (char*)pOld) >> 2;
        pPtrArrayBegin = pNewPtrArray + (nFront + (allocationSide == 0 ? nAdditionalCapacity : 0));
        if (pOld)
            CopyPtrs(pPtrArrayBegin, pBegin, (mItEnd.mpCurrentArrayPtr - mItBegin.mpCurrentArrayPtr) + 4);
        if (mpPtrArray)
            EAFree(mpPtrArray);
        mpPtrArray = pNewPtrArray;
        mnPtrArraySize = nNewPtrArraySize;
    }
    else
    {
        pPtrArrayBegin = mpPtrArray +
            (((mnPtrArraySize - nNeed) >> 1) + (allocationSide == 0 ? nAdditionalCapacity : 0));
        if ((char*)pPtrArrayBegin < mItBegin.mpCurrentArrayPtr)
            CopyPtrs(pPtrArrayBegin, (void**)mItBegin.mpCurrentArrayPtr,
                     (mItEnd.mpCurrentArrayPtr - mItBegin.mpCurrentArrayPtr) + 4);
        else
            memmove(pPtrArrayBegin + (nUsedPtrCount -
                    (((mItEnd.mpCurrentArrayPtr - mItBegin.mpCurrentArrayPtr) + 4) >> 2)),
                    (void**)mItBegin.mpCurrentArrayPtr,
                    (mItEnd.mpCurrentArrayPtr - mItBegin.mpCurrentArrayPtr) + 4);
    }
    mItBegin.SetSubarray(pPtrArrayBegin);
    mItEnd.SetSubarray(pPtrArrayBegin + (nUsedPtrCount - 1));
}

// @ 0x006781D0
void DequeBaseB4::DoInit(uint32_t n)
{
    uint32_t nNewPtrArraySize = (n >> 2) + 1;
    const uint32_t kMinPtrArraySize_ = 8;
    mnPtrArraySize = MaxU(kMinPtrArraySize_, nNewPtrArraySize + 2);
    mpPtrArray = DoAllocatePtrArray(mnPtrArraySize);
    void** pPtrArrayBegin = mpPtrArray + ((mnPtrArraySize - nNewPtrArraySize) >> 1);
    void** pPtrArrayEnd = pPtrArrayBegin + nNewPtrArraySize;
    for (void** p = pPtrArrayBegin; p < pPtrArrayEnd; ++p)
        *p = DoAllocateSubarray();
    mItBegin.SetSubarray(pPtrArrayBegin);
    mItBegin.mpCurrent = mItBegin.mpBegin;
    mItEnd.SetSubarray(pPtrArrayEnd - 1);
    mItEnd.mpCurrent = mItEnd.mpBegin + (n & 3);
}

// @ 0x006782C0
struct AutoRef { RefObj* mpObj; };

struct CopyImpl {
    static AutoRef* do_copy(const AutoRef* first, const AutoRef* last, AutoRef* dest);
};

AutoRef* CopyImpl::do_copy(const AutoRef* first, const AutoRef* last, AutoRef* dest)
{
    if (first != last)
    {
        do
        {
            RefObj* src = first->mpObj;
            RefObj* old = dest->mpObj;
            if (src != old)
            {
                if (src)
                    src->AddRef();
                dest->mpObj = src;
                if (old)
                    old->Release();
            }
            ++first;
            ++dest;
        } while (first != last);
    }
    return (AutoRef*)dest;
}
