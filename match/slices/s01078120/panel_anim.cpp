// Slice s01078120 (part b) -- the 8 "prop-layout panel" behaviour methods that
// live next to cSPPropLayoutPanel::Init (0x01078120, kept in s01078120.cpp):
//   01078820  panel set-up: swap the layout ref, seed the keys, subscribe to messages
//   010788d0  per-frame tick: animate the window position between two layout cells,
//             then walk the layout list updating each entry's interactable children
//   01078b80  move the window to (x,z) either instantly or with the stopwatch running
//   01078bf0  std::list<...>::_Insert node-unlink helper (out-of-line)
//   01078d30  std::vector<...>::_Fill / assign helper (0xc-byte entries)
//   01078ec0  snap the window position to the nearest cell edge (two axes)
//   01078fa0  clamp the window position for the "wrapping" layout mode
//   01079040  select the cell that page `n` should scroll to
//
// The class is the same 0x01078120 panel; its members are laid out here from the
// live disassembly of these methods.  Separate TU so it cannot clash with the
// committed cSPPropLayoutPanel definition in s01078120.cpp.
#include <stddef.h>
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

struct Vec3f { float x, y, z, w; };
struct Rectangle { float x1, y1, x2, y2; };

// ---- interface objects (this family: +0 = vtbl[0], AddRef at +4, Release at +8)
struct RefObj { virtual void v0(); virtual void AddRef(); virtual void Release(); };

template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T** AsOutParam() { if (mpObject) { T* p = mpObject; mpObject = 0; p->Release(); } return &mpObject; }
    __forceinline AutoRef& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

// ---- UTFWin window: GetRealArea +0x38, SetPosition +0x70, FindWindowByID +0xf0,
//      SetFlag +0x7c, AddWinProc +0x104, RemoveWinProc +0x108 -----------------
struct IWindow {
    virtual int  AddRef();                                            // +0x00
    virtual int  Release();                                           // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual const Rectangle& GetRealArea();                          // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void SetPosition(float x, float y);                      // +0x70
    virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void vbc(); virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);    // +0xf0
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(void* pProc);                            // +0x104
    virtual void RemoveWinProc(void* pProc);                         // +0x108
};

struct IMessageServer {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20();
    virtual void AddHandler(void* handler, uint32_t id);             // +0x24
};
IMessageServer* __cdecl MessageServer();                             // 0x0067dcc0
struct Connector {
    void*    mpServer;                                               // +0x00
    void*    mpHandler;                                              // +0x04
    const uint32_t* mpMessageIDs;                                    // +0x08
    int      mCount;                                                 // +0x0c
    int      mFlag;                                                  // +0x10
};
// Connector::Init is inlined; its effect is (server, handler, ids, count, 0).

struct Stopwatch {
    uint32_t ma, mb, mc, md;                                         // +0x00..+0x0c
    long long GetElapsedTimeFloat() const;                           // 0x0093a3a0
    void Restart();                                                  // 0x00571e80
};

// ---- game objects ---------------------------------------------------------
struct cSPUILayout;

// "entry" object reached through a layout node.  vtable slots are named a<hex>
// so the +offset in the comment is guaranteed: a<NN> is at +0xNN.
struct LayoutEntryObj {
    virtual void a00(); virtual void a04(); virtual void a08();
    virtual void* GetChild(uint32_t id);                             // +0x0c
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24();
    virtual void SetByte28(int flag, uint8_t v);                     // +0x28
    virtual void a2c(); virtual void a30(); virtual void a34(); virtual void a38();
    virtual void a3c();
    virtual bool GetBool40();                                        // +0x40
    virtual bool GetBool44();                                        // +0x44
    virtual void a48(); virtual void a4c(); virtual void a50(); virtual void a54();
    virtual void a58();
    virtual void Call5c(void* arg);                                  // +0x5c
    virtual void a60(); virtual void a64(); virtual void a68(); virtual void a6c();
    virtual void a70(); virtual void a74(); virtual void a78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void a80(); virtual void a84(); virtual void a88(); virtual void a8c();
    virtual void Call90();                                           // +0x90
    virtual void a94(); virtual void a98(); virtual void a9c(); virtual void aa0();
    virtual void aa4(); virtual void aa8(); virtual void aac(); virtual void ab0();
    virtual void* GetObject(uint32_t id);                            // +0xb4
    virtual void ab8(); virtual void abc(); virtual void ac0(); virtual void ac4();
    virtual void ac8(); virtual void acc(); virtual void ad0(); virtual void ad4();
    virtual void ad8(); virtual void adc(); virtual void ae0(); virtual void ae4();
    virtual void ae8(); virtual void aec(); virtual void af0(); virtual void af4();
    virtual void af8(); virtual void afc(); virtual void b00(); virtual void b04();
    virtual void b08(); virtual void b0c(); virtual void b10(); virtual void b14();
    virtual void b18(); virtual void b1c(); virtual void b20(); virtual void b24();
    virtual void b28(); virtual void b2c(); virtual void b30(); virtual void b34();
    virtual void b38(); virtual void b3c(); virtual void b40(); virtual void b44();
    virtual void b48(); virtual void b4c(); virtual void b50(); virtual void b54();
    virtual void b58(); virtual void b5c(); virtual void b60(); virtual void b64();
    virtual void b68(); virtual void b6c(); virtual void b70(); virtual void b74();
    virtual void b78(); virtual void b7c(); virtual void b80(); virtual void b84();
    virtual void b88(); virtual void b8c(); virtual void b90(); virtual void b94();
    virtual void b98(); virtual void b9c(); virtual void ba0(); virtual void ba4();
    virtual void ba8(); virtual void bac(); virtual void bb0(); virtual void bb4();
    virtual void bb8(); virtual void bbc(); virtual void bc0(); virtual void bc4();
    virtual void bc8(); virtual void bcc(); virtual void bd0(); virtual void bd4();
    virtual void bd8(); virtual void bdc(); virtual void be0(); virtual void be4();
    virtual void be8(); virtual void bec(); virtual void bf0(); virtual void bf4();
    virtual void bf8(); virtual void bfc(); virtual void c00(); virtual void c04();
    virtual void c08(); virtual void c0c(); virtual void c10(); virtual void c14();
    virtual void c18(); virtual void c1c(); virtual void c20(); virtual void c24();
    virtual void c28(); virtual void c2c(); virtual void c30(); virtual void c34();
    virtual void c38(); virtual void c3c(); virtual void c40(); virtual void c44();
    virtual void c48(); virtual void c4c(); virtual void c50(); virtual void c54();
    virtual void c58(); virtual void c5c(); virtual void c60(); virtual void c64();
    virtual void c68(); virtual void c6c(); virtual void c70(); virtual void c74();
    virtual void c78(); virtual void c7c(); virtual void c80(); virtual void c84();
    virtual void c88(); virtual void c8c(); virtual void c90(); virtual void c94();
    virtual void c98(); virtual void c9c(); virtual void ca0(); virtual void ca4();
    virtual void ca8(); virtual void cac(); virtual void cb0(); virtual void cb4();
    virtual void cb8(); virtual void cbc(); virtual void cc0(); virtual void cc4();
    virtual void cc8(); virtual void ccc(); virtual void cd0(); virtual void cd4();
    virtual void cd8(); virtual void cdc(); virtual void ce0(); virtual void ce4();
    virtual void ce8(); virtual void cec(); virtual void cf0(); virtual void cf4();
    virtual void cf8(); virtual void cfc(); virtual void d00(); virtual void d04();
    virtual void d08(); virtual void d0c(); virtual void d10(); virtual void d14();
    virtual void d18(); virtual void d1c(); virtual void d20(); virtual void d24();
    virtual void d28(); virtual void d2c(); virtual void d30(); virtual void d34();
    virtual void d38(); virtual void d3c(); virtual void d40(); virtual void d44();
    virtual void d48(); virtual void d4c(); virtual void d50(); virtual void d54();
    virtual void d58(); virtual void d5c(); virtual void d60(); virtual void d64();
    virtual void d68(); virtual void d6c(); virtual void d70(); virtual void d74();
    virtual void d78(); virtual void d7c(); virtual void d80(); virtual void d84();
    virtual void d88(); virtual void d8c(); virtual void d90(); virtual void d94();
    virtual void d98(); virtual void d9c(); virtual void da0(); virtual void da4();
    virtual void da8(); virtual void dac(); virtual void db0(); virtual void db4();
    virtual void db8(); virtual void dbc(); virtual void dc0(); virtual void dc4();
    virtual void dc8(); virtual void dcc(); virtual void dd0(); virtual void dd4();
    virtual void dd8(); virtual void ddc(); virtual void de0(); virtual void de4();
    virtual void de8(); virtual void dec(); virtual void df0(); virtual void df4();
    virtual void df8(); virtual void dfc(); virtual void e00(); virtual void e04();
    virtual void e08(); virtual void e0c(); virtual void e10(); virtual void e14();
    virtual void e18(); virtual void e1c(); virtual void e20(); virtual void e24();
    virtual void e28(); virtual void e2c(); virtual void e30(); virtual void e34();
    virtual void e38(); virtual void e3c(); virtual void e40(); virtual void e44();
    virtual void e48(); virtual void e4c(); virtual void e50(); virtual void e54();
    virtual void e58(); virtual void e5c(); virtual void e60(); virtual void e64();
    virtual void e68(); virtual void e6c(); virtual void e70(); virtual void e74();
    virtual void e78(); virtual void e7c(); virtual void e80(); virtual void e84();
    virtual void e88(); virtual void e8c(); virtual void e90(); virtual void e94();
    virtual void e98(); virtual void e9c(); virtual void ea0(); virtual void ea4();
    virtual void ea8(); virtual void eac(); virtual void eb0(); virtual void eb4();
    virtual void eb8(); virtual void ebc(); virtual void ec0(); virtual void ec4();
    virtual void ec8(); virtual void ecc(); virtual void ed0(); virtual void ed4();
    virtual void ed8(); virtual void edc(); virtual void ee0(); virtual void ee4();
    virtual void ee8(); virtual void eec(); virtual void ef0(); virtual void ef4();
    virtual void ef8(); virtual void efc();
    virtual void* FindInChildren(uint32_t id, int n);                // +0xf0
    virtual void f04(); virtual void f08();
    virtual void Call104(void* self);                                // +0x104
    virtual void Call108(void* self);                                // +0x108
    uint32_t pad04[9];                                               // +0x04..+0x27
    uint8_t  mb28;                                                   // +0x28 (read as a byte by 010788d0)
};

// vector entry used by 010788d0 / 01078d30 (0xc bytes)
struct LayoutEntry {
    RefObj* mp;                                                      // +0x00
    float   mf4;                                                     // +0x04
    uint8_t mb8;                                                     // +0x08
    uint8_t pad_09[3];
};

// std::list node: +0x00 payload, +0x04 next pointer (used by 01078bf0)
struct ListNode { void* mp0; ListNode* mpNext; };

// the std::list<...> instantiation owning 01078bf0 (count at +0x0c)
struct List {
    uint32_t pad00[3];                                               // +0x00..+0x0b
    int      mCount;                                                 // +0x0c
    int* FUN_01078bf0(int* out, ListNode* head, ListNode** where);   // 0x01078bf0
};

void __cdecl operator_delete(void* p);                               // 0x00f47380

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

// the panel class -- only the members these 8 methods touch -----------------
class PropPanelAnim {
public:
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20();
    virtual void On24();                                             // +0x24
    virtual void On28();                                             // +0x28
    uint32_t    pad04[2];                                            // +0x04
    void*       mpHandler;                                           // +0x0c (base of the handler sub-object)
    ResourceKey mLayoutKey;                                          // +0x10
    AutoRef<RefObj> mpLayout;                                   // +0x1c
    uint32_t    pad20[3];                                            // +0x20..+0x2b
    IWindow*    mpWindow;                                            // +0x2c
    uint32_t    mVecBegin;                                           // +0x30 (entries, 0xc bytes)
    uint32_t    mVecEnd;                                             // +0x34
    uint32_t    pad38[(0x80 - 0x38) / 4];
    uint32_t    mMode80;                                             // +0x80 (0x120ad1fb => "vertical" mode)
    float       mf84;                                                // +0x84 (animation duration)
    int         mCols88;                                             // +0x88
    int         mRows8c;                                             // +0x8c
    uint32_t    m90;                                                 // +0x90
    float       mPadX;                                               // +0x94
    float       mPadY;                                               // +0x98
    bool        mbFlag9c;                                            // +0x9c
    uint32_t    mMode;                                               // +0xa0
    uint32_t    ma4, ma8, mac;                                       // +0xa4..+0xac
    float       mb0, mb4;                                            // +0xb0, +0xb4
    float       mb8;                                                 // +0xb8
    float       mStepX;                                              // +0xbc
    float       mStepZ;                                              // +0xc0
    uint32_t    pad_c4;                                              // +0xc4
    Stopwatch   mStopwatch;                                          // +0xc8..+0xd7
    uint32_t    pad_d8[1];                                           // +0xd8
    float       mfDc;                                                // +0xdc (duration again / speed)
    float       mTargetX;                                            // +0xe0
    float       mTargetZ;                                            // +0xe4
    bool        mbE8;                                                // +0xe8
    bool        mbE9;                                                // +0xe9
    uint8_t     pad_ea[2];                                           // +0xea
    Connector   mConnector;                                          // +0xec

    bool Init();                                                     // 0x01078120
    IWindow* FUN_01077ae0(void* node);                               // 0x01077ae0
    void     FUN_01077e20();                                         // 0x01077e20
    char FUN_01078820(void* layout, uint32_t unused2, uint32_t unused3, uint32_t a3);   // 0x01078820
    void FUN_010788d0();                                             // 0x010788d0
    void FUN_01078b80(float x, float z);                             // 0x01078b80
    void FUN_01078ec0();                                             // 0x01078ec0
    void FUN_01078fa0();                                             // 0x01078fa0
    void FUN_01079040(unsigned page);                                // 0x01079040
};

void* __cdecl SpaceGameGet(void* obj);                               // 0x01002bd0
void* __cdecl GetPlayerInventory(void* game);                        // 0x00a1ad60
void* __cdecl FUN_00ff3fb0(void* obj);                               // 0x00ff3fb0
long long __cdecl FUN_01050a60();                                    // 0x01050a60

void __cdecl FUN_01078d30(LayoutEntry* first, LayoutEntry* last, const LayoutEntry* value);  // 0x01078d30

extern "C" float _HK_REAL_ZERO;                                      // 0x01485378
extern "C" float _HK_REAL_ONE;                                       // 0x01485720

// =================================================================== @ 0x01078820
// Panel set-up: install the new layout, seed the resource key, run Init() and,
// if it succeeded, register this object with the message server.
char PropPanelAnim::FUN_01078820(void* layout, uint32_t, uint32_t, uint32_t a3)
{
    void* old = mpLayout.mpObject;
    if (layout != old) {
        if (layout) ((RefObj*)layout)->AddRef();
        mpLayout.mpObject = (RefObj*)layout;
        if (old) ((RefObj*)old)->Release();
    }
    mLayoutKey.instanceID = a3;
    mLayoutKey.typeID = 0xb1b104;
    mLayoutKey.groupID = 0x5f4d5e7;
    mbE8 = 0;
    mbE9 = 0;

    bool ok = Init();
    if (ok) {
        mConnector.mpServer = MessageServer();
        mConnector.mpHandler = &mpHandler;
        mConnector.mpMessageIDs = (const uint32_t*)0x0149c618;
        mConnector.mCount = 1;
        mConnector.mFlag = 0;
        if (mConnector.mpServer && mConnector.mpHandler)
            ((IMessageServer*)mConnector.mpServer)->AddHandler(mConnector.mpHandler, (uint32_t)0xf62def);
    }
    return ok;
}

// =================================================================== @ 0x01078b80
// Move the window to (x, z).  If the animation duration is <= 0 set it directly,
// otherwise (re)start the interpolation stopwatch and refresh the layout.
void PropPanelAnim::FUN_01078b80(float x, float z)
{
    mTargetX = x;
    mTargetZ = z;
    if (mf84 <= 0.0f) {
        mpWindow->SetPosition(x, z);
        FUN_01077e20();
        return;
    }
    mStopwatch.Restart();
    FUN_01077e20();
}

// =================================================================== @ 0x01078ec0
// Snap the window to the nearer cell boundary: horizontal in mode 0x120ad1fb,
// vertical otherwise.  Picks the larger of the two candidate distances.
void PropPanelAnim::FUN_01078ec0()
{
    const Rectangle& r = mpWindow->GetRealArea();
    float x1 = r.x1, y1 = r.y1, x2 = r.x2, y2 = r.y2;
    if (mMode80 == 0x120ad1fb) {
        float a = mStepZ - (y2 - y1);
        float b = mTargetZ - mStepZ;
        const float* p;
        if (a > b) p = &a; else p = &b;
        FUN_01078b80(mTargetX, *p);
    } else {
        float a = mStepX - (x2 - x1);
        float b = mTargetX - mStepX;
        const float* p;
        if (a > b) p = &a; else p = &b;
        FUN_01078b80(*p, mTargetZ);
    }
}

// =================================================================== @ 0x01078fa0
// Clamp the window position to the layout bounds in the perpendicular axis.
void PropPanelAnim::FUN_01078fa0()
{
    if (mMode80 == 0x120ad1fb) {
        float zero = 0.0f;
        float sum = mTargetZ + mStepZ;
        const float* p;
        if (sum > zero) p = &zero; else p = &sum;
        FUN_01078b80(mTargetX, *p);
        return;
    }
    float zero = 0.0f;
    float sum = mTargetX + mStepX;
    const float* p;
    if (sum > zero) p = &zero; else p = &sum;
    FUN_01078b80(*p, mTargetZ);
}

// =================================================================== @ 0x01079040
// Scroll so that page `page` is visible: offset by (page * cellPitch) toward the
// near edge, in the mode's perpendicular axis.
void PropPanelAnim::FUN_01079040(unsigned page)
{
    int count = ((int)mVecEnd - (int)mVecBegin) / 0xc;
    int one = 1;
    const int* pCount = &one;
    if ((unsigned)count >= 1u) pCount = &count;
    if (page < (unsigned)((*pCount - 1) / (unsigned)(mRows8c * mCols88) + 1)) {
        if (mMode80 == 0x120ad1fb) {
            float f = (float)page;
            FUN_01078b80(mTargetX, -(f * mStepZ));
            return;
        }
        float f = (float)page;
        FUN_01078b80(-(f * mStepX), mTargetZ);
    }
}

// =================================================================== @ 0x01078bf0
// std::list<...>::erase / _Insert helper (out-of-line instantiation): unlinks and
// frees the node `head`, writing the resulting iterator into `out`.
int* List::FUN_01078bf0(int* out, ListNode* head, ListNode** where)
{
    out[1] = (int)where;
    ListNode* n = head->mpNext;
    out[0] = (int)n;
    while (n == 0) {
        out[1] += 4;
        n = *(ListNode**)out[1];
        out[0] = (int)n;
    }
    ListNode* first = *where;
    if (first != head) {
        ListNode* it = first->mpNext;
        for (; it != head; it = it->mpNext)
            first = it;
        first->mpNext = it->mpNext;
        operator_delete(head);
        mCount = mCount - 1;
        return out;
    }
    *where = first->mpNext;
    operator_delete(head);
    mCount = mCount - 1;
    return out;
}

// =================================================================== @ 0x01078d30
// std::vector<LayoutEntry>::_Fill / assign helper: overwrite [first,last) with
// `value`, AddRef/Release on the entry reference.
void __cdecl FUN_01078d30(LayoutEntry* first, LayoutEntry* last, const LayoutEntry* value)
{
    for (; first != last; first++) {
        RefObj* nv = value->mp;
        RefObj* ov = first->mp;
        if (nv != ov) {
            if (nv) ((RefObj*)nv)->AddRef();
            first->mp = nv;
            if (ov) ((RefObj*)ov)->Release();
        }
        first->mf4 = value->mf4;
        first->mb8 = value->mb8;
    }
}

// =================================================================== @ 0x010788d0
// Per-frame tick: animate the window between two layout cells (interpolating
// toward mTarget* by the stopwatch progress), then walk the entry vector and
// refresh each entry's interactable children.
void PropPanelAnim::FUN_010788d0()
{
    if (mStopwatch.ma | mStopwatch.mb) {
        const Rectangle& r = mpWindow->GetRealArea();
        float f = 1.0f;
        if (mf84 > 0.0f) {
            float t = (float)mStopwatch.GetElapsedTimeFloat() * mfDc / mf84;
            if (t < 1.0f)
                f = t;
            else {
                mStopwatch.ma = 0; mStopwatch.mb = 0; mStopwatch.mc = 0; mStopwatch.md = 0;
                f = 1.0f;
            }
        } else {
            mStopwatch.ma = 0; mStopwatch.mb = 0; mStopwatch.mc = 0; mStopwatch.md = 0;
            f = 1.0f;
        }
        mpWindow->SetPosition(mTargetX * f + (1.0f - f) * r.x1,
                              mTargetZ * f + (1.0f - f) * r.y1);
    }

    LayoutEntry* it = (LayoutEntry*)mVecBegin;
    LayoutEntry* end = (LayoutEntry*)mVecEnd;
    for (; it != end; it++) {
        if (it->mb8 != 0)
            continue;
        LayoutEntryObj* obj = (LayoutEntryObj*)FUN_01077ae0(it->mp);
        LayoutEntryObj* a = (LayoutEntryObj*)obj->GetObject(0x600db9c);
        if (a == 0) continue;
        LayoutEntryObj* b = (LayoutEntryObj*)a->GetChild(0x707459dd);
        if (b == 0) continue;

        bool flag = b->GetBool40();
        obj->SetFlag(2, flag);

        LayoutEntryObj* c = (LayoutEntryObj*)obj->FindInChildren(0x62840d8, 0);
        if (c != 0)
            c->Call5c(flag ? (void*)ma4 : (void*)ma8);

        LayoutEntryObj* d = (LayoutEntryObj*)obj->GetChild(0x8ed27e7a);
        if (d != 0)
            d->SetByte28(4, b->mb28);
        LayoutEntryObj* e = (LayoutEntryObj*)obj->FindInChildren(0x5f792ed, 0);
        if (e != 0)
            e->SetFlag(1, b->GetBool44());

        void* game = SpaceGameGet(b);
        void* inv = GetPlayerInventory(game);
        void* holder = FUN_00ff3fb0(inv);
        if (holder != 0) {
            float old = it->mf4;
            float nf = (float)FUN_01050a60();
            it->mf4 = nf;
            if (old != nf) {
                if (nf == 0.0f)
                    obj->Call108(this);
                else if (old == 0.0f)
                    obj->Call104(this);
                obj->Call90();
            }
        }
    }
}
