// slice s00f145a0 -- SP::Owner (the verb-icon-tray data owner) and the 0x70-byte verb-icon
// record it feeds: the record's copy-ctor / operator= (with the embedded vector assignments),
// the owner's Reset / Setup / SetLocalized / SetPlain, and Update(record) which forwards every
// field of the record into SetLocalized/SetPlain.
//
// Flags: /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------------------
// calling-convention helpers
// ---------------------------------------------------------------------------
typedef void  (__thiscall *FnV)(void*);
typedef void* (__thiscall *FnP)(void*);
typedef int   (__thiscall *FnI)(void*);
typedef void  (__thiscall *FnVI)(void*, int);
typedef void  (__thiscall *FnVII)(void*, int, int);
typedef int   (__thiscall *FnII)(void*, int);

// ---------------------------------------------------------------------------
// externals (conventions set here; only the marker functions are matched)
// ---------------------------------------------------------------------------
extern "C" void* EAAllocate(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern "C" void  EADelete(void* p);                                                        // 0x00f47380
extern "C" void* memcpy_(void* dst, const void* src, uint32_t n);                          // 0x011e0744
extern "C" void* do_copy(void* first, void* last, void* result);                           // 0x0062ffd0
extern "C" void* uninit_copy(void* out, void* first, void* last, void* dst, void* extra);  // 0x01022c60
extern "C" void  SetNumberString(int lo, int hi, wchar_t* buf, int n);                     // 0x00881ae0
extern "C" void* GetSingleton();                                                           // 0x0067de40

// ---------------------------------------------------------------------------
// SP::cString
// ---------------------------------------------------------------------------
class cString {
public:
    uint32_t mData[5];
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* source);  // 0x006b5770
    ~cString();                                                             // 0x006b5240
    const wchar_t* GetText() const;                                         // 0x006b55c0
};

// ---------------------------------------------------------------------------
// UI::TextZoomName (the per-icon level/name widget, 0x78 bytes)
// ---------------------------------------------------------------------------
struct TextZoomName {
    TextZoomName* Init();                                                // 0x008345c0
    void Shutdown();                                                     // 0x00834e30
    void Setup(int r, int a, void* win, int b, int s0, int s1, int s2);  // 0x00834fa0
};

// ---------------------------------------------------------------------------
// 12-byte vector (begin/end/cap) of 4-byte elements -- the +0x18 member of Rec70.
// ---------------------------------------------------------------------------
struct Vec12 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    Vec12* assign(const Vec12* src);                    // 0x00f145a0
    void*  DoAllocate(int n, void* first, void* last);  // 0x00f137b0
    void   DoDestroy(void* first, void* last);          // 0x00ae6710
    void*  Allocate(int n, void* alloc);                // 0x00b93c60
};

// ---------------------------------------------------------------------------
// vector<float,sp_vector_allocator> -- the +0x30 member of Rec70.
// ---------------------------------------------------------------------------
struct VecF {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAlloc;
    void* Allocate(int n, void* alloc);   // 0x004aa350
    VecF* operator=(const VecF& src);     // 0x0050d4e0
};

// ---------------------------------------------------------------------------
// the 0x70-byte record (vtable 0x147f604).
// ---------------------------------------------------------------------------
struct Rec70 {
    void* mpVtbl;   // +0x00
    void* mRef4;    // +0x04  AutoRefCount
    void* mRef8;    // +0x08  AutoRefCount
    int   mField0c; // +0x0c
    int   mField10; // +0x10
    int   mField14; // +0x14
    Vec12 mVec18;   // +0x18  (+0x24 allocator)
    int   mAlloc24; // +0x24
    int   mField28; // +0x28
    int   mField2c; // +0x2c
    VecF  mVec30;   // +0x30  (+0x3c allocator)
    int   mField40; // +0x40
    float mF44, mF48, mF4c, mF50, mF54, mF58;  // +0x44 .. +0x58
    int   mD5c, mD60, mD64, mD68, mD6c;        // +0x5c .. +0x6c
    Rec70* CopyFrom(const Rec70& src);   // 0x00f14690
    Rec70* operator=(const Rec70& src);  // 0x00f147e0
};

// ---------------------------------------------------------------------------
// cSPUILayout (only FindWindowByID is needed here).
// ---------------------------------------------------------------------------
struct Layout {
    void* FindWindowByID(int id, int flag);  // 0x008105b0
};

// ---------------------------------------------------------------------------
// the sub-object embedded at Owner+8.
// ---------------------------------------------------------------------------
struct Sub8 {
    void  Clear();      // 0x00e0a640
    int   Check(int);   // 0x00e0a800
    int   Count();      // 0x00e09c80
    void* At(int);      // 0x00e09c90
};

// ---------------------------------------------------------------------------
// eastl::vector<EA::AutoRefCount<UI::TextZoomName>,sp_vector_allocator> -- Owner+0x78.
// ---------------------------------------------------------------------------
struct Vec78 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    void  DoInsertValue(void* pos, void* value);  // 0x00f14270
    void* Erase(void* first, void* last);         // 0x005c2170
};

// ---------------------------------------------------------------------------
// the plain value record Update() reads (a different type from Rec70).
// ---------------------------------------------------------------------------
struct RecV {
    int   f00;   // +0x00
    int   f04;   // +0x04
    int   f08;   // +0x08
    int   f0c;   // +0x0c
    int   f10;   // +0x10
    int   f14;   // +0x14
    int   f18;   // +0x18
    int   f1c;   // +0x1c
    int   f20;   // +0x20
    int   f24;   // +0x24
    int   f28;   // +0x28
    int   f2c;   // +0x2c
    int   f30;   // +0x30
    int   f34;   // +0x34
    int   f38;   // +0x38
    float f3c;   // +0x3c
    float f40;   // +0x40
    float f44;   // +0x44
};

// ---------------------------------------------------------------------------
// SP::Owner
// ---------------------------------------------------------------------------
struct Owner {
    void Reset();                                                     // 0x00f14980
    void Setup(const wchar_t* text, int flag, uint32_t id);           // 0x00f149d0
    void SetLocalized(int value, const cString& name, uint32_t id);   // 0x00f14b30
    void SetPlain(int seconds, uint32_t id);                          // 0x00f14ba0
    void Update(const RecV& rec);                                     // 0x00f14d90
};

// ===========================================================================
// 0x00f145a0 -- vector(4-byte elements)::operator= / assign.
// ===========================================================================
// @ 0x00f145a0
Vec12* Vec12::assign(const Vec12* src)
{
    if (src == this)
        return this;

    int n = (int)((char*)src->mpEnd - (char*)src->mpBegin) >> 2;
    if (((int)((char*)mpCapacity - (char*)mpBegin) >> 2) < n) {
        void* pNew = DoAllocate(n, src->mpBegin, src->mpEnd);
        DoDestroy(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EADelete(mpBegin);
        mpCapacity = (char*)pNew + n * 4;
        mpEnd = (char*)pNew + n * 4;
        mpBegin = pNew;
        return this;
    }

    int sz = (int)((char*)mpEnd - (char*)mpBegin) >> 2;
    if (sz < n) {
        do_copy(src->mpBegin, (char*)src->mpBegin + sz * 4, mpBegin);
        void* out = 0;
        uninit_copy(&out, (char*)src->mpBegin + sz * 4, src->mpEnd, mpEnd, (void*)src);
        mpEnd = (char*)mpBegin + n * 4;
        return this;
    }

    void* r = do_copy(src->mpBegin, src->mpEnd, mpBegin);
    DoDestroy(r, mpEnd);
    mpEnd = (char*)mpBegin + n * 4;
    return this;
}

// ===========================================================================
// 0x00f14690 -- copy constructor of the 0x70-byte record.
// ===========================================================================
// @ 0x00f14690
Rec70* Rec70::CopyFrom(const Rec70& src)
{
    mpVtbl = (void*)0x147f604;

    mRef4 = src.mRef4;
    if (mRef4)
        ((FnV)(*(void***)mRef4)[0])(mRef4);
    mRef8 = src.mRef8;
    if (mRef8)
        ((FnV)(*(void***)mRef8)[0])(mRef8);

    mField0c = src.mField0c;
    mField10 = src.mField10;
    mField14 = src.mField14;

    int n = (int)((char*)src.mVec18.mpEnd - (char*)src.mVec18.mpBegin) >> 2;
    mVec18.Allocate(n, (void*)&src.mAlloc24);
    void* out = 0;
    uninit_copy(&out, src.mVec18.mpBegin, src.mVec18.mpEnd, mVec18.mpBegin, (void*)&src);
    mVec18.mpEnd = out;

    mField2c = src.mField2c;

    int fn = (int)((char*)src.mVec30.mpEnd - (char*)src.mVec30.mpBegin) >> 2;
    mVec30.Allocate(fn, (void*)&src.mVec30.mAlloc);
    void* r = memcpy_(mVec30.mpBegin, src.mVec30.mpBegin,
                      (uint32_t)((char*)src.mVec30.mpEnd - (char*)src.mVec30.mpBegin));
    mVec30.mpEnd = (char*)r + fn * 4;

    mF44 = src.mF44; mF48 = src.mF48; mF4c = src.mF4c;
    mF50 = src.mF50; mF54 = src.mF54; mF58 = src.mF58;

    mD5c = src.mD5c; mD60 = src.mD60; mD64 = src.mD64;
    mD68 = src.mD68; mD6c = src.mD6c;

    return this;
}

// ===========================================================================
// 0x00f147e0 -- operator= of the 0x70-byte record.
// ===========================================================================
// @ 0x00f147e0
Rec70* Rec70::operator=(const Rec70& src)
{
    void* s4 = src.mRef4;
    if (s4 != mRef4) {
        if (s4)
            ((FnV)(*(void***)s4)[0])(s4);
        void* old4 = mRef4;
        mRef4 = s4;
        if (old4)
            ((FnV)(*(void***)old4)[1])(old4);
    }

    void* s8 = src.mRef8;
    if (s8 != mRef8) {
        if (s8)
            ((FnV)(*(void***)s8)[0])(s8);
        void* old8 = mRef8;
        mRef8 = s8;
        if (old8)
            ((FnV)(*(void***)old8)[1])(old8);
    }

    mField0c = src.mField0c;
    mField10 = src.mField10;
    mField14 = src.mField14;

    mVec18.assign(&src.mVec18);
    mField2c = src.mField2c;
    mVec30.operator=(src.mVec30);

    mF44 = src.mF44; mF48 = src.mF48; mF4c = src.mF4c;
    mF50 = src.mF50; mF54 = src.mF54; mF58 = src.mF58;

    mD5c = src.mD5c; mD60 = src.mD60; mD64 = src.mD64;
    mD68 = src.mD68; mD6c = src.mD6c;

    return this;
}

// ===========================================================================
// 0x00f14980 -- Owner::Reset: clear the embedded list, shut down every icon.
// ===========================================================================
// @ 0x00f14980
void Owner::Reset()
{
    char* self = (char*)this;
    ((Sub8*)(self + 8))->Clear();

    Vec78* vec = (Vec78*)(self + 0x78);
    int n = (int)((char*)vec->mpEnd - (char*)vec->mpBegin) >> 2;
    for (int i = 0; i < n; ++i)
        ((TextZoomName**)vec->mpBegin)[i]->Shutdown();
    vec->Erase(vec->mpBegin, vec->mpEnd);
}

// ===========================================================================
// 0x00f149d0 -- Owner::Setup: build a TextZoomName for the current layout.
// ===========================================================================
// @ 0x00f149d0
void Owner::Setup(const wchar_t* text, int flag, uint32_t id)
{
    char* self = (char*)this;
    Sub8* sub = (Sub8*)(self + 8);
    if (!sub->Check(1))
        return;

    void* layout = sub->At(sub->Count() - 1);

    TextZoomName* zoom = (TextZoomName*)EAAllocate(0x78, "Simulator", 0, 0, 0, 0);
    if (zoom)
        zoom = zoom->Init();
    else
        zoom = 0;

    TextZoomName* tmp = zoom;
    if (zoom)
        ((FnV)(*(void***)zoom)[1])(zoom);          // AddRef

    Vec78* vec = (Vec78*)(self + 0x78);
    if (vec->mpEnd < vec->mpCapacity) {
        TextZoomName** slot = (TextZoomName**)vec->mpEnd;
        vec->mpEnd = (char*)vec->mpEnd + 4;
        if (slot) {
            *slot = zoom;
            if (zoom)
                ((FnV)(*(void***)zoom)[1])(zoom);  // AddRef
        }
    } else {
        vec->DoInsertValue(vec->mpEnd, &tmp);
        zoom = tmp;
    }

    if (zoom)
        ((FnV)(*(void***)zoom)[2])(zoom);          // Release

    TextZoomName* z = *(TextZoomName**)((char*)vec->mpEnd - 4);

    void* win1 = ((Layout*)layout)->FindWindowByID(0x7fb67c0, 1);
    void* win2 = ((Layout*)layout)->FindWindowByID(0x7c7e1e0, 1);

    int r = 0;
    if (win2)
        r = ((FnII)(*(void***)win2)[3])(win2, 0xf15f4bd);

    z->Setup(r, 0, win1, 1, 0, 0, 0);

    if (win1)
        ((FnVII)(*(void***)win1)[0x7c / 4])(win1, 2, flag);
    if (win2)
        ((FnVI)(*(void***)win2)[0x80 / 4])(win2, (int)text);

    void* w = ((Layout*)layout)->FindWindowByID((int)id, 1);
    if (w)
        ((FnVII)(*(void***)w)[0x7c / 4])(w, 1, 1);
}

// ===========================================================================
// 0x00f14b30 -- Owner::SetLocalized: format an int and forward it with a name.
// ===========================================================================
// @ 0x00f14b30
void Owner::SetLocalized(int value, const cString& name, uint32_t id)
{
    wchar_t buf[0x20];
    SetNumberString(value, value >> 31, buf, 0x20);

    void* mgr = GetSingleton();
    void* fmt = ((FnP)(*(void***)mgr)[0x20 / 4])(mgr);
    ((FnVII)(*(void***)fmt)[0x34 / 4])(fmt, (int)buf, 0);

    Setup(name.GetText(), value != 0, id);
}

// ===========================================================================
// 0x00f14ba0 -- Owner::SetPlain: format a duration and forward it.
// ===========================================================================
// @ 0x00f14ba0
void Owner::SetPlain(int seconds, uint32_t id)
{
    bool flag = seconds != 0;

    int totalMinutes = seconds / 60;
    int hoursFull = totalMinutes / 60;
    int days = hoursFull / 24;
    int hours = hoursFull - days * 24;
    int minutes = totalMinutes - hoursFull * 60;
    int secs = seconds - totalMinutes * 60;

    wchar_t buf0[0x20], buf1[0x20], buf2[0x20], buf3[0x20];

    SetNumberString(secs, secs >> 31, buf0, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf0, 0); }

    SetNumberString(minutes, minutes >> 31, buf1, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf1, 1); }

    SetNumberString(hours, hours >> 31, buf2, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf2, 2); }

    SetNumberString(days, days >> 31, buf3, 0x20);
    { void* m = GetSingleton(); void* f = ((FnP)(*(void***)m)[0x20 / 4])(m);
      ((FnVII)(*(void***)f)[0x34 / 4])(f, (int)buf3, 3); }

    uint32_t nameId;
    if (days > 0)
        nameId = 0x773632d;
    else if (hours > 0)
        nameId = 0x773632c;
    else if (minutes > 0)
        nameId = 0x773632b;
    else
        nameId = 0x773632a;

    cString name(0xea25b547, nameId, 0);
    Setup(name.GetText(), flag, id);
}

// ===========================================================================
// 0x00f14d90 -- Owner::Update: forward every field of a value record.
// ===========================================================================
// @ 0x00f14d90
void Owner::Update(const RecV& rec)
{
    Reset();

    SetLocalized(rec.f1c, cString(0xea25b547, 0x7736316, 0), 0x7ca2b50);
    SetLocalized(rec.f20, cString(0xea25b547, 0x773631c, 0), 0x7ca2b66);
    SetLocalized(rec.f24, cString(0xea25b547, 0x773631d, 0), 0x7ca2b61);
    SetLocalized(rec.f28, cString(0xea25b547, 0x773631e, 0), 0x7ca2b63);
    SetLocalized((int)rec.f44, cString(0xea25b547, 0x7736323, 0), 0x7ca2b62);
    SetLocalized((int)rec.f40, cString(0xea25b547, 0x773631f, 0), 0x7ca2b64);
    SetLocalized((int)rec.f3c, cString(0xea25b547, 0x7736322, 0), 0x7ca2b65);
    SetLocalized(rec.f00, cString(0xea25b547, 0x7736317, 0), 0x7ca2b51);
    SetLocalized(rec.f08, cString(0xea25b547, 0x7736319, 0), 0x7ca2b51);
    SetLocalized(rec.f04, cString(0xea25b547, 0x7736318, 0), 0x7ca2b51);
    SetLocalized(rec.f34, cString(0xea25b547, 0x7736324, 0), 0x7ca2b51);
    SetLocalized(rec.f38, cString(0xea25b547, 0x7736325, 0), 0x7ca2b54);
    SetLocalized(rec.f10, cString(0xea25b547, 0x773631a, 0), 0x7ca2b52);
    SetLocalized(rec.f0c, cString(0xea25b547, 0x7736326, 0), 0x7ca2b55);
    SetLocalized(rec.f14, cString(0xea25b547, 0x773631b, 0), 0x7ca2b53);
    SetLocalized(rec.f2c, cString(0xea25b547, 0x7736320, 0), 0x7ca2b68);
    SetLocalized(rec.f30, cString(0xea25b547, 0x7736321, 0), 0x7ca2b67);
}
