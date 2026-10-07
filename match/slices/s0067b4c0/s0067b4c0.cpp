// Slice s0067b4c0 - cUIHints (on-screen hint controller): hint list parsing,
// teardown, per-hint state transitions and visibility toggling.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc: locals with dtors get no EH frame).
#include <string.h>
#include <math.h>
#include "types.h"

// ---- allocation / helpers --------------------------------------------------
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0 (6-arg tagged new)
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}
void __cdecl FreeArray(void* p);                               // 0x00f47380 operator delete[]

struct VObj { void** vt; };
typedef void (__thiscall *FnV1)(void*);
typedef void (__thiscall *FnV1i)(void*, int);
typedef void (__thiscall *FnV1p)(void*, void*);

extern char g_14014b4[];              // vtable of the "killallhints" command
extern char g_killallhints[];         // 0x01401520 "killallhints"
extern wchar_t g_wEmpty[];            // 0x01667bac shared empty wide-string rep

// ---- external callees ---------------------------------------------------
struct EStrSoA {
    void push_back(int ch);                         // 0x004f6510
};
struct Layout0 {
    void Shutdown(int);                             // 0x00811ad0
};
int* __cdecl FUN_00d3b3c0(int a, int b, int c);    // 0x00d3b3c0 (EASTL copy helper)
struct Vec20 {                                      // member at this+0x20: destroy range
    void Insert(int* r, int* end);                  // 0x00a693f0
};

// ---- strings -----------------------------------------------------------
// eastl::basic_string<wchar_t>: begin/end/capacity-end + allocator; an empty string shares g_wEmpty.
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAlloc;
    WStr() { mpBegin = g_wEmpty; mpEnd = g_wEmpty; mpCapacity = g_wEmpty + 1; }
    ~WStr() {
        int n = (int)((char*)mpCapacity - (char*)mpBegin) & ~1;
        if (n > 2 && mpBegin) FreeArray(mpBegin);
    }
    void Assign(const wchar_t* b, const wchar_t* e);      // 0x00423650
    void AppendSz(const wchar_t* s);                      // 0x005c3d90 (eastl append(const wchar_t*))
    unsigned Find(const wchar_t* s, unsigned pos) const;  // 0x00608340
    void Erase(unsigned pos, unsigned n);                 // 0x004228e0
    int Insert(int a, int b);                             // 0x0067bbf0
    int Forward(int a, int b);                            // 0x0067b030 (vector insert, elsewhere)
};

struct cString {                                    // SP::cString
    uint32_t pad[5];
    const wchar_t* GetText();                       // 0x006b55c0
};

// ---- property lists ----------------------------------------------------------
struct Property {
    void* ptr;
    uint32_t pad[3];
    uint8_t flags;      // +0x10 (0x30 = value lives behind ptr)
    uint8_t pad2;
    uint16_t type;      // +0x12
    void* Data() { return (flags & 0x30) ? ptr : (void*)this; }
};
struct PropertyList {
    virtual void s0();
    virtual void Release();                                   // slot 1
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8();
    virtual bool GetProperty(uint32_t id, Property** out);    // slot 9 (+0x24)
    int mRefCount;
    uint32_t mId;       // +8
};
struct PLRef {
    PropertyList* p;
    PLRef() : p(0) {}
    ~PLRef() { if (p) p->Release(); }
    void Reset() { if (p) { PropertyList* t = p; p = 0; t->Release(); } }
};
struct ResKey { uint32_t a, b, c; };

struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    int mAlloc[2];
    void Reserve(unsigned n);                                 // 0x004e0880
    void DoInsertValue(uint32_t* pos, const uint32_t& v);     // 0x004558a0
    void push_back(const uint32_t& v) {
        if (mpEnd < mpCapacity) ::new (mpEnd++) uint32_t(v);
        else DoInsertValue(mpEnd, v);
    }
    ~UIntVec() {
        if (mpBegin) {
            if (((int*)mpBegin)[-1] != 0) FreeArray(mpBegin);
        }
    }
};

bool __cdecl GetPropertyAsText(PropertyList* pl, uint32_t id, void* out);          // 0x006a1360
void __cdecl GetPropertyAsKeyInstance(PropertyList* pl, uint32_t id, uint32_t* out); // 0x006a12a0
bool __cdecl GetPropertyAsKey(PropertyList* pl, uint32_t id, void* out);           // 0x006a1250
void __cdecl GetPropertyArray(PropertyList* pl, uint32_t id, unsigned* count, ResKey** data); // 0x006a0ae0

template <class T>
inline void ReadProp(PLRef& plr, uint32_t id, uint16_t type, T* out) {
    PropertyList* pl = plr.p;
    if (pl) {
        Property* pr;
        if (pl->GetProperty(id, &pr) && pr->type == type) *out = *(T*)pr->Data();
    }
}

struct PropManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual void GetList(uint32_t instance, uint32_t group, PLRef* out);   // slot 11 (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17();
    virtual void GetIds(uint32_t group, UIntVec* out);                     // slot 18 (+0x48)
};
PropManager* __cdecl GetPropManager();                          // 0x0067de30

// ---- windows / layout -----------------------------------------------------------
struct IImage { virtual void s0(); virtual void Release(); };
struct IWin;
struct IWin {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IWin* Find(uint32_t id);                    // 3  (+0x0c)
    virtual IWin* GetOwner();                           // 4  (+0x10)
    virtual void SetImage(void* img);                   // 5  (+0x14)
    virtual void s6();
    virtual void Fn1c(int v);                           // 7  (+0x1c)
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual int Fn30();                                 // 12 (+0x30)
    virtual void s13();
    virtual float* GetArea();                           // 14 (+0x38)
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void Fn5c(uint32_t v);                      // 23 (+0x5c)
    virtual void s24();
    virtual void Fn64(float x, float y);                // 25 (+0x64)
    virtual void s26();
    virtual void Fn6c(const float* r);                  // 27 (+0x6c)
    virtual void Fn70(float x, float y);                // 28 (+0x70)
    virtual void Fn74(float x, float y);                // 29 (+0x74)
    virtual void s30();
    virtual void Fn7c(int a, int b);                    // 31 (+0x7c)
    virtual void Fn80(const wchar_t* s);                // 32 (+0x80)
    virtual void s33(); virtual void s34(); virtual void s35();
    virtual void Fn90();                                // 36 (+0x90)
    virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual IWin* Fna8();                               // 42 (+0xa8)
    virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
    virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void Fne8(IWin* w);                         // 58 (+0xe8)
    virtual void s59(); virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
    virtual void s64();
    virtual void Fn104(void* proc);                     // 65 (+0x104) add window proc
};

struct Layout {                       // cSPUILayout
    uint32_t pad[6];
    Layout();                                                        // 0x00810000
    void Init(const wchar_t* name, uint32_t a, int b, uint32_t c);   // 0x00812160
    IWin* FindWindowByID(int id, int flag);                          // 0x008105b0
    void SetVisibility(int v);                                       // 0x00810590
};

struct Rect4 {
    float l, t, r, b;
    Rect4& operator=(const Rect4& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};
void __cdecl GetMainWindowArea(Rect4* out);                          // 0x00805ea0
void __cdecl CreateImageFromResource(ResKey* key, void** ppOut, int a, int b, int c);   // 0x00806230
struct ImgRef {
    IImage* p;
    ImgRef() : p(0) {}
    void** AsPPTypeParam();                                          // 0x00a16f40
    ~ImgRef() { if (p) p->Release(); }
};

// "killallhints" console command (vtable 0x014014b4)
struct CmdBase { uint32_t pad[4]; CmdBase(); };                     // 0x0083c800
struct KillAllHintsCmd : CmdBase {
    KillAllHintsCmd() { *(void**)this = g_14014b4; }
};
struct CheatMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5();
    virtual void AddCommand(const char* name, CmdBase* cmd, int flag);   // slot 6 (+0x18)
};
CheatMgr* __cdecl GetCheatManager();                                  // 0x0067de20

// ---- hint record (retail layout: 0x98 bytes) ----------------------------------
struct cHint {
    virtual ~cHint();                 // slot 0 (scalar deleting dtor)
    int mRefCount;                    // +4
    uint32_t mTriggerID;              // +8
    UIntVec mPresentList;             // +0x0c
    UIntVec mAbsentList;              // +0x20
    UIntVec mCancelList;              // +0x34
    float mPeriod;                    // +0x48
    float mF4c;                       // +0x4c
    float mWait;                      // +0x50
    float mLife;                      // +0x54
    float mF58;                       // +0x58
    uint32_t mPriority;               // +0x5c
    ResKey mIcon;                     // +0x60
    uint32_t mFlashInstance;          // +0x6c
    uint32_t mTypeInstance;           // +0x70
    uint8_t mbHasText;                // +0x74
    uint8_t mbB75;                    // +0x75
    uint8_t mbB76;                    // +0x76
    uint8_t pad77;
    cString mText;                    // +0x78 (0x14 bytes)
    uint32_t pad8c[3];
    cHint();                          // 0x0067b150
};

template <class T>
struct HintRef {
    T* p;
    HintRef(T* q) : p(q) { if (p) p->mRefCount++; }
    ~HintRef() {
        if (p) {
            int n = (*(volatile int*)&p->mRefCount += -1);
            if (n == 0) {
                p->mRefCount = 1;
                delete p;
            }
        }
    }
};

struct HintVec {                      // eastl::vector<AutoRefCount<cHint>> at this+0x20
    cHint** mpBegin;
    cHint** mpEnd;
    cHint** mpCapacity;
    void Reserve(unsigned n);                                    // 0x00646c00
    void DoInsertValue(cHint** pos, HintRef<cHint>* v);          // 0x0067b370
    void DestroyRange(cHint** a, cHint** b);                     // 0x00a693f0
};
cHint** __cdecl HintCopy(cHint** last, cHint** end, cHint** first);   // 0x00d3b3c0

struct cUIHints {
    uint32_t pad0[3];
    uint32_t* mCondBegin;   // +0x0c  (vector of condition processors)
    uint32_t* mCondEnd;     // +0x10
    uint32_t pad1[3];
    HintVec mHintList;      // +0x20 (begin/end/cap)
    uint32_t pad2[4];
    Layout* mpLayout;       // +0x3c
    float mFlashTime;       // +0x40
    float mOriginalFlash;   // +0x44 (a float despite the PDB's unsigned)
    int mState;             // +0x48
    cHint* mCur;            // +0x4c
    float mF50;             // +0x50
    uint32_t mV54;          // +0x54
    Rect4 mIconArea;        // +0x58

    __declspec(noinline) char ParseHints();            // 0x0067b4c0
    void InitHints();                                  // 0x0067ba10
    void Destroy2();                                   // 0x0067bb80
    IWin* GetFlashParent();                            // 0x0067acc0
    void SetVisibility(int show, cHint* h);           // 0x0067bc30
    __declspec(noinline) void UpdateHints(char b, char c); // 0x0067c350
    void Next(int a, char b);                          // 0x0067c3b0
    void SetFlag(char a, int b);                       // 0x0067c420
};

// ---- 0x0067b4c0 : cUIHints::ParseHints ---------------------------------------
// Rebuilds mHintList from the "hint" property lists (group 0x522de06).
// @ 0x0067b4c0
char cUIHints::ParseHints() {
    HintVec* vec = &mHintList;
    cHint** first = vec->mpBegin;
    cHint** last = vec->mpEnd;
    cHint** pos = HintCopy(last, last, first);
    vec->DestroyRange(pos, vec->mpEnd);
    vec->mpEnd -= (last - first);

    UIntVec ids;
    ids.mpBegin = 0; ids.mpEnd = 0; ids.mpCapacity = 0;
    GetPropManager()->GetIds(0x522de06, &ids);
    int n = (int)(ids.mpEnd - ids.mpBegin);
    vec->Reserve(n);
    for (int i = 0; i < n; i++) {
        cHint* h = new ("cHint", 0, 0, 0, 0) cHint();
        HintRef<cHint> ref(h);
        PLRef pl;
        unsigned count = 0;
        ResKey* data = 0;
        PropManager* pm = GetPropManager();
        pl.Reset();
        pm->GetList(ids.mpBegin[i], 0x522de06, &pl);
        h->mTriggerID = pl.p->mId;

        GetPropertyArray(pl.p, 0x522de07, &count, &data);
        h->mPresentList.Reserve(count);
        for (unsigned k = 0; (int)k < (int)count; k++) h->mPresentList.push_back(data[k].a);

        count = 0;
        GetPropertyArray(pl.p, 0x522de08, &count, &data);
        h->mAbsentList.Reserve(count);
        for (unsigned k = 0; (int)k < (int)count; k++) h->mAbsentList.push_back(data[k].a);

        count = 0;
        GetPropertyArray(pl.p, 0x522de09, &count, &data);
        h->mCancelList.Reserve(count);
        for (unsigned k = 0; (int)k < (int)count; k++) h->mCancelList.push_back(data[k].a);

        ReadProp(pl, 0x60472a7, 1, &h->mbB75);
        ReadProp(pl, 0x60472a8, 1, &h->mbB76);
        ReadProp(pl, 0x522de0a, 0xd, &h->mPeriod);
        ReadProp(pl, 0x522de0b, 0xd, &h->mWait);
        ReadProp(pl, 0x7e8708c, 0xd, &h->mLife);
        ReadProp(pl, 0x7e87096, 0xd, &h->mF58);
        ReadProp(pl, 0x522de0c, 0xd, &h->mF4c);
        ReadProp(pl, 0x522de0d, 9, &h->mPriority);

        h->mbHasText = GetPropertyAsText(pl.p, 0x522de0e, &h->mText);
        GetPropertyAsKeyInstance(pl.p, 0x522de11, &h->mFlashInstance);
        GetPropertyAsKeyInstance(pl.p, 0x5234ce1, &h->mTypeInstance);
        if (GetPropertyAsKey(pl.p, 0x522de10, &h->mIcon)) h->mIcon.b = 0x2f7d0004;
        ReadProp(pl, 0x522de12, 0xa, &h->pad8c[0]);
        h->pad8c[1] = (h->mTypeInstance != 0x1f9e21e8);

        if (vec->mpEnd < vec->mpCapacity) {
            ::new (vec->mpEnd++) HintRef<cHint>(h);
        } else {
            vec->DoInsertValue(vec->mpEnd, &ref);
        }
    }
    return 0;
}

// ---- 0x0067ba10 : cUIHints::InitHints ----------------------------------------
// Clears the condition list, parses the hints, builds the "Hint" layout, caches its
// geometry and registers the "killallhints" command.
// @ 0x0067ba10
void cUIHints::InitHints() {
    uint32_t* first = mCondBegin;
    uint32_t* last = mCondEnd;
    memcpy(first, last, (char*)mCondEnd - (char*)last);
    mCondEnd -= (last - first);
    ParseHints();

    Layout* lay = new ("cSPUILayout", 0, 0, 0, 0) Layout();
    mpLayout = lay;
    lay->Init(L"Hint", 0x40464100, 1, 0xcbdf6e1d);
    IWin* w = mpLayout->FindWindowByID(-1, 1);
    if (w) ((FnV1p)(*(void***)w)[0x104 / 4])(w, (char*)this + 8);
    mpLayout->SetVisibility(0);
    w = mpLayout->FindWindowByID(0x5244c08, 1);
    mIconArea = *(Rect4*)w->GetArea();
    w = mpLayout->FindWindowByID(0x5246048, 1);
    if (w) {
        float* r = w->GetArea();
        mFlashTime = r[3] - r[1];
    }
    w = mpLayout->FindWindowByID(0x52432e0, 1);
    if (w) {
        float* r = w->GetArea();
        mOriginalFlash = r[3] - r[1];
    }
    mState = 0;
    KillAllHintsCmd* cmd = new ("cCommand", 0, 0, 0, 0) KillAllHintsCmd();
    GetCheatManager()->AddCommand(g_killallhints, cmd, 0);
}

// ---- 0x0067bb80 : teardown hints list + layout -----------------------
// @ 0x0067bb80
void cUIHints::Destroy2() {
    char* p = (char*)this;
    int* begin = *(int**)(p + 0x20);
    int* end = *(int**)(p + 0x24);
    int* r = FUN_00d3b3c0((int)end, (int)end, (int)begin);
    ((Vec20*)(p + 0x20))->Insert(r, end);
    *(int*)(p + 0x24) += (end - begin) * -4;
    if (*(void**)(p + 0x3c)) {
        ((Layout0*)*(void**)(p + 0x3c))->Shutdown(1);
        if (*(void**)(p + 0x3c)) {
            void* x = *(void**)(p + 0x3c);
            ((FnV1i)((VObj*)x)->vt[0])(x, 1);
        }
        *(int*)(p + 0x3c) = 0;
    }
    void* cm = GetCheatManager();
    ((FnV1i)((VObj*)cm)->vt[0x1c / 4])(cm, (int)g_killallhints);
}

// ---- 0x0067bbf0 : wide-string insert(p, ch): push_back at end, else forward ----
// @ 0x0067bbf0
int WStr::Insert(int a, int b) {
    if (a == *(int*)((char*)this + 4)) {
        ((EStrSoA*)this)->push_back(b);
        return *(int*)((char*)this + 4) - 2;
    }
    return Forward(a, b);
}

// ---- 0x0067bc30 : cUIHints::SetVisibility ------------------------------------
// Shows/hides the hint layout for hint h: lays out the text (optionally split around a
// "<hinticon>" marker), the icon image, and the flash window.
// @ 0x0067bc30
void cUIHints::SetVisibility(int show, cHint* h) {
    mpLayout->SetVisibility(show);
    mF50 = 0.0f;
    if ((char)show == 0) {
        if (mCur) {
            IWin* fp = GetFlashParent();
            if (fp) fp->Fn5c(mV54);
        }
        mCur = 0;
        return;
    }
    if (!h) return;
    mCur = h;
    IWin* fp;
    if (h->mFlashInstance == 0) {
        fp = 0;
    } else {
        fp = GetFlashParent();
        if (fp) mV54 = fp->Fn30();
    }
    IWin* w0 = mpLayout->FindWindowByID(-1, 1);
    IWin* w1 = mpLayout->FindWindowByID(0x52432e0, 1);
    IWin* w2 = mpLayout->FindWindowByID(0x5244c68, 1);
    IWin* w3 = mpLayout->FindWindowByID(0x52432e1, 1);
    IWin* w4 = mpLayout->FindWindowByID(0x52432e2, 1);
    IWin* w5 = mpLayout->FindWindowByID(0x5244c08, 1);
    IWin* w6 = mpLayout->FindWindowByID(0x6525790, 1);
    if (h->mbB76) {
        w1->Fn7c(1, 0);
        w2->Fn7c(1, 0);
        w3->Fn7c(1, 1);
        w4->Fn7c(1, 1);
    } else {
        w1->Fn7c(1, 1);
        w2->Fn7c(1, 1);
        w3->Fn7c(1, 0);
        w4->Fn7c(1, 0);
    }
    w6->Fn7c(1, h->mbB76);
    w0->GetOwner()->Fne8(w0);

    WStr s1;
    WStr s2;
    bool bSplit = false;
    s2.Assign(L"", L"");
    if (h->mbHasText) {
        s1.AppendSz(h->mText.GetText());
        unsigned pos = s1.Find(L"<hinticon>", 0);
        if (pos != (unsigned)-1) {
            s2.Assign(s1.mpBegin, s1.mpEnd);
            bSplit = (s2.mpBegin[0] == 0xffff);
            s1.Erase(pos, (unsigned)(s1.mpEnd - s1.mpBegin));
            s2.Erase(0, pos + 10);
            if (bSplit) s2.Insert((int)s2.mpBegin, 0xffff);
            bSplit = true;
        }
        w1->Fn80(s1.mpBegin);
    } else {
        w1->Fn80(L"");
    }
    w1->Fn5c(h->pad8c[0]);
    Rect4 area;
    GetMainWindowArea(&area);
    w1->Find(0xf15f4bd)->Fn1c(0);
    float f2c = 0.0f;
    float* r = w1->GetArea();
    float aw = area.r - area.l;
    if ((r[2] - r[0]) + 20.0f > aw) {
        w1->Fn74(aw - 20.0f, mOriginalFlash * 2.0f);
        f2c = mOriginalFlash;
    } else {
        r = w1->GetArea();
        w1->Fn74(r[2] - r[0], mOriginalFlash);
    }
    float f10 = w1->GetArea()[2];
    if (h->mIcon.a == 0 && h->mIcon.b == 0 && h->mIcon.c == 0) {
        w5->Fn7c(1, 0);
    } else {
        w5->Fn7c(1, 1);
        ImgRef img;
        if (w5->Fna8()) {
            IWin* p = w5->Fna8();
            IWin* y;
            if (p) y = p->Find(0xef3c47cf);
            else y = 0;
            if (h->mIcon.a != 0) {
                CreateImageFromResource(&h->mIcon, img.AsPPTypeParam(), 0, -1, -1);
                y->SetImage(img.p);
            }
            w5->Fn90();
            w5->Fn6c(&mIconArea.l);
            f10 += 3.0f;
            float* rr = w1->GetArea();
            float mid = (rr[3] + rr[1]) * 0.5f;
            float* r5 = w5->GetArea();
            w5->Fn70(f10, mid - (r5[3] - r5[1]) * 0.5f);
            if (fp) {
                float* fr = fp->GetArea();
                float t = ((fr[3] - fr[1]) * (mIconArea.r - mIconArea.l) * 0.5f) / (fr[2] - fr[0]);
                float cy = (mIconArea.b + mIconArea.t) * 0.5f;
                Rect4 rc;
                rc.t = cy - t;
                rc.l = f10;
                rc.r = (mIconArea.r - mIconArea.l) + f10;
                rc.b = cy + t;
                w5->Fn6c(&rc.l);
            }
            float* r5b = w5->GetArea();
            f10 = ((r5b[2] - r5b[0]) + f10) + 3.0f;
        }
    }
    if (bSplit) {
        w2->Fn7c(1, 1);
        w2->Fn80(s2.mpBegin);
        w2->Fn5c(h->pad8c[0]);
        w2->Find(0xf15f4bd)->Fn1c(0);
        float* r2 = w2->GetArea();
        w2->Fn70(f10, r2[1]);
        float* r2b = w2->GetArea();
        f10 = (r2b[2] - r2b[0]) + f10;
    } else {
        w2->Fn7c(1, 0);
    }
    IWin* w7 = mpLayout->FindWindowByID(0x5246048, 1);
    w7->Fn74(f10 + 10.0f, mFlashTime + f2c);
    float* r7 = w7->GetArea();
    w7->Fn64((float)floor((double)(area.l + ((area.r - area.l) - (r7[2] - r7[0])) * 0.5f)), r7[1]);
}

// ---- 0x0067c350 : cUIHints::UpdateHints ------------------------------
// @ 0x0067c350
void cUIHints::UpdateHints(char b, char c) {
    char* e = *(char**)((char*)this + 0x4c);
    if (e) {
        char v;
        if (c == 0 || *(int*)(e + 0x70) != 0x1f9e21e8) v = b; else v = 1;
        *(int*)(e + 0x90) = (v == 0);
        char* e2 = *(char**)((char*)this + 0x4c);
        *(float*)(e2 + 0x94) = 0.0f;
        SetVisibility(0, *(cHint**)((char*)this + 0x4c));
    }
    *(int*)((char*)this + 0x4c) = 0;
}

// ---- 0x0067c3b0 : next hint (complete, non-matching) -----------------
// @ 0x0067c3b0
void cUIHints::Next(int a, char b) {
    char* p = (char*)this;
    int** it = *(int***)(p + 0x20);
    int** end = *(int***)(p + 0x24);
    if (it != end) {
        int* e;
        while ((e = *it, *(int*)((char*)e + 8) != a)) {
            ++it;
            if (it == end) return;
        }
        if (b == 0) {
            if (*(int*)((char*)e + 0x90) == 0) return;
            if ((int*)*(int*)(p + 0x4c) == e) UpdateHints(0, 1);
            *(int*)((char*)e + 0x90) = 0;
        } else {
            if (*(int*)((char*)e + 0x90) == 1) return;
            *(int*)((char*)e + 0x90) = 1;
        }
        *(int*)((char*)e + 0x94) = 0;
    }
}

// ---- 0x0067c420 : cUIHints::SetFlag ----------------------------------
// @ 0x0067c420
void cUIHints::SetFlag(char a, int b) {
    if (*(unsigned*)((char*)this + 0x48) > 2) return;
    if (a != 0) {
        *(int*)((char*)this + 0x48) = 0;
    } else {
        *(int*)((char*)this + 0x48) = 2;
        UpdateHints(0, (char)b);
    }
}
