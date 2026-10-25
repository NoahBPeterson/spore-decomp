// Slice s00e47520 -- cSPUIPropertyLayout UI helpers.
//
// 00e47520  rebuild the property-layout text / timeline label after a flag
//           change: notify the child windows, pick the label from the timeline,
//           wrap it in a Variant, forward it to the layout, then reflow the
//           label window.  00e47700 rebuilds the per-property layout objects
//           from the timeline list.
//
// Frozen batch part2.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------
// Windows
// ---------------------------------------------------------------------------
struct IWindow {
    PV8 PV4 PV2                              // +0x00..+0x34  slots 0..13
    virtual float* Rect();                   // +0x38  slot 14 -> {x,y,w,h}
    PV8 PV4 PV2                              // +0x3c..+0x70  slots 15..28
    virtual void   Resize(float w, float h); // +0x74  slot 29
    PV                                       // +0x78  slot 30
    virtual void   Slot7C(int a, int b);     // +0x7c  slot 31
};

// ---------------------------------------------------------------------------
// Data structures
// ---------------------------------------------------------------------------
struct WString {                             // eastl::basic_string<wchar_t>
    const wchar_t* mBegin;                   // +0x00
    const wchar_t* mEnd;                     // +0x04
    const wchar_t* mCapacity;                // +0x08
    void RangeInitialize(const wchar_t* s);  // 0x579a90
};

struct cString {                             // SP::cString
    void* mData[9];                          // 0x24 bytes
    cString();                               // 0x6b5060
    ~cString();                              // 0x6b5240
    const wchar_t* GetText();                // 0x6b55c0
};

struct Variant {                             // EA::Variant
    char          mPad[0x10];                // +0x00..+0x0f
    unsigned char mFlags;                    // +0x10
    char          mPad2[3];                  // +0x11..+0x13
    Variant(const WString& src);             // 0x5a74a0
    void Destruct(bool free);                // 0x93db80
};

struct A8Inner {                             // descriptor reached through +0xa8
    int   m00;                               // +0x00
    float m04;                               // +0x04
};

struct ObjA8 {                               // per-property timeline entry
    char     mPad[0x0c];                     // +0x00..+0x0b
    A8Inner* m0C;                            // +0x0c
};

struct PtrVec {                              // SPVector<ObjA8*> at +0xac
    ObjA8** mBegin;                          // +0x00
    ObjA8** mEnd;                            // +0x04
    ObjA8** mCap;                            // +0x08
    void assignSlow(const PtrVec& src);      // 0xb8ef40
};

struct PL;                                   // cSPUIPropertyLayout

struct ARVec {                               // SPVector<AutoRefCount> at +0xc0
    PL** mBegin;                             // +0x00
    PL** mEnd;                               // +0x04
    PL** mCap;                               // +0x08
    void DoInsertPtr(PL** pos, PL* const& v); // 0xaea5d0
};

// ---------------------------------------------------------------------------
// The object
// ---------------------------------------------------------------------------
struct PL {
    virtual void AddRef();                   // +0x00  slot 0
    virtual void Release();                  // +0x04  slot 1

    char     mPad04[0x18];                   // +0x04..+0x1b
    void*    m1c;                            // +0x1c
    void*    m20;                            // +0x20
    char     mPad24[0x44];                   // +0x24..+0x67
    int      m68;                            // +0x68
    char     mPad6c[0x0c];                   // +0x6c..+0x77
    IWindow* m78;                            // +0x78
    IWindow* m7c;                            // +0x7c
    IWindow* m80;                            // +0x80
    char     mPad84[0x24];                   // +0x84..+0xa7
    ObjA8*   mA8;                            // +0xa8
    PtrVec   mVec;                           // +0xac..+0xb7
    char     mPadB8[0x08];                   // +0xb8..+0xbf
    ARVec    mRefs;                          // +0xc0..+0xcb
    char     mPadCC[0x08];                   // +0xcc..+0xd3
    int      mD4;                            // +0xd4
    char     mPadD8[0x04];                   // +0xd8..+0xdb
    float    mDC;                            // +0xdc
    char     mE0;                            // +0xe0
    char     mPadE1[0x03];                   // +0xe1..+0xe3
    int      mE4;                            // +0xe4
    char     mPadE8[0x05];                   // +0xe8..+0xec
    char     mED;                            // +0xed

    void   SetFlag(int v);                                  // 0x828020
    void   func20h();                                       // 0x828740
    void   Fn828c30(void* key, Variant* v, int a, int b);   // 0x828c30
    void   Fn46600(void* timeline, int e, unsigned a, unsigned b); // 0xe46600
    PL*    Fn471e0();                                       // 0xe471e0
    float  Fn460d0();                                       // 0xe460d0
    char   Fn46140(cString* s);                             // 0xe46140
    char   Fn46180(cString* s);                             // 0xe46180
    void   Fn3cf60(PL* t);                                  // 0xe3cf60
    double Fn37d70(float f);                                // 0xe37d70

    void FUN_00e47520(int flag, PL* t);
    void FUN_00e47700(PtrVec* src);
};

// 4-byte refcounted handle: AddRefs on construction, Releases on destruction.
struct AutoRef {
    PL* mpObject;
    AutoRef(PL* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};

// ---------------------------------------------------------------------------
// Free helpers
// ---------------------------------------------------------------------------
void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0xf473a0
void  __cdecl operator_delete(void* p);                          // 0xf47380
void  __cdecl FUN_00806e40(void* win, int a, int b);             // 0x806e40
void  __cdecl FUN_00808b20(void* a, void* b, int c);             // 0x808b20
PL*   __cdecl FUN_00b3d410();                                    // 0xb3d410
extern const char DAT_013f6b3c[];                                // 0x13f6b3c "UI"

// ===========================================================================
// 00e47520  refresh the layout label from the timeline
// ===========================================================================
// @ 0x00e47520
void PL::FUN_00e47520(int flag, PL* t)
{
    if (m78 == 0)
        return;
    SetFlag(flag);
    if (m7c != 0)
        m7c->Slot7C(1, flag);
    if ((char)flag == 0)
        return;
    if (t == 0)
        return;

    cString s;
    char b = t->Fn46140(&s);
    if ((t->mD4 > 1 && t->Fn46180(&s)) || b) {
        FUN_00b3d410()->Fn3cf60(t);

        WString vec = { 0, 0, 0 };
        vec.RangeInitialize(s.GetText());

        Variant var(vec);
        Fn828c30((void*)0x60c6eb8, &var, 1, 0);
        if (var.mFlags & 4)
            var.Destruct(false);
        if (((((int)vec.mCapacity - (int)vec.mBegin) & ~1) > 2) && vec.mBegin != 0)
            operator_delete((void*)vec.mBegin);

        func20h();
        if (m80 != 0) {
            float* r1 = m80->Rect();
            float a = r1[3] - r1[1];
            FUN_00806e40(m80, 0, 1);
            float* r2 = m80->Rect();
            float b2 = (r2[3] - r2[1]) - a;
            float* r3 = m78->Rect();
            m78->Resize(r3[2] - r3[0], (r3[3] - r3[1]) + b2);
        }
    } else {
        SetFlag(0);
    }
    FUN_00808b20(t->m20, m78, 1);
}

// ===========================================================================
// 00e47700  rebuild the property-layout objects from the timeline list
// ===========================================================================
// @ 0x00e47700
void PL::FUN_00e47700(PtrVec* src)
{
    mVec.assignSlow(*src);
    if (mED == 0)
        return;

    PL* p = (PL*)operator_new(0x10c, DAT_013f6b3c, 0, 0, 0, 0);
    if (p != 0)
        p = p->Fn471e0();
    p->mA8 = mA8;
    if (p->mA8 != 0) {
        int e = p->mA8->m0C->m00;
        p->m68 = e;
        p->Fn46600(m1c, e, 1, 0);
    }
    p->mE0 = 1;
    p->mDC = Fn460d0();
    {
        AutoRef ref(p);
        if (mRefs.mEnd < mRefs.mCap) {
            PL** slot = mRefs.mEnd++;
            if (slot != 0) {
                *slot = p;
                p->AddRef();
            }
        } else {
            mRefs.DoInsertPtr(mRefs.mEnd, ref.mpObject);
        }
    }

    int n = (int)(mVec.mEnd - mVec.mBegin);
    for (int i = 0; i < n; ++i) {
        PL* q = (PL*)operator_new(0x10c, DAT_013f6b3c, 0, 0, 0, 0);
        if (q != 0)
            q = q->Fn471e0();
        ObjA8* w = mVec.mBegin[i];
        q->mA8 = w;
        if (q->mA8 != 0) {
            int e = q->mA8->m0C->m00;
            q->m68 = e;
            q->Fn46600(m1c, e, 1, 0);
        }
        q->mE0 = 1;
        if (mE0 != 0) {
            q->mDC = mDC;
        } else {
            float v;
            if (mA8 != 0)
                v = mA8->m0C->m04;
            else
                v = 0.0f;
            if (FUN_00b3d410() != 0 && mE4 != 0xbeb528cb)
                v = (float)FUN_00b3d410()->Fn37d70(v);
            q->mDC = v;
        }

        AutoRef ref(q);
        if (mRefs.mEnd < mRefs.mCap) {
            PL** slot = mRefs.mEnd++;
            if (slot != 0) {
                *slot = q;
                q->AddRef();
            }
        } else {
            mRefs.DoInsertPtr(mRefs.mEnd, ref.mpObject);
        }
    }
}
