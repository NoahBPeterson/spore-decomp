// Slice s00f15890 -- eastl container helpers (Simulator module).
//  00f16260  tiny cleanup: release the object's parts, then destroy the member at +0x08
//  00f16280  fixed_vector<__int64,32>::assign over a linked-list iterator range
//  00f16330  vector<Element>::erase over 0x70-byte elements with virtual destructors
//  00f16390  vector<Element>::insert (grow path / in-place path)
// Flags: /O2 /MD /Gy /EHsc /TP /arch=SSE /fp:fast.  Callees are masked relocations.
typedef unsigned int uint;
typedef long long int64;

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int size);

// ---------------------------------------------------------------------------------------------
// 00f16260: release parts, then destroy the member object at +0x08 (tail call)
// ---------------------------------------------------------------------------------------------
struct PartHolder {
    char pad00[8];
    struct Part { void Destroy(); } mPart;                  // +0x08, 0x00e0a5c0
    void ReleaseParts();                                    // 0x00f14980
    void Cleanup();                                         // 0x00f16260
};

// ---------------------------------------------------------------------------------------------
// fixed_vector<int64,32>: three pointers, list iterators are singly linked nodes with the value
// at +0x08 (next at +0x00)
// ---------------------------------------------------------------------------------------------
struct ListNode {
    ListNode* mpNext;                                       // +0x00
    int       mPad;                                         // +0x04
    int64     mValue;                                       // +0x08
};

// singly linked list iterator: the object stays in its stack slot (its member is updated in place
// by operator++), which is why the retail loop reloads and stores the parameter slot each step
struct ListIterator {
    ListNode* mpNode;
    ListIterator& operator++()      { mpNode = mpNode->mpNext; return *this; }
    int64&        operator*() const { return mpNode->mValue; }
    bool operator==(const ListIterator& other) const { return mpNode == other.mpNode; }
};

inline int64* CopyRange64(const int64* first, const int64* last, int64* dst)
{
    memcpy(dst, first, (uint)((const char*)last - (const char*)first));
    return dst + (last - first);
}

struct Int64ListVector {
    int64* mpBegin;                                         // +0x00
    int64* mpEnd;                                           // +0x04
    int64* mpCapacity;                                      // +0x08

    void InsertList(int64* pos, ListIterator first, ListIterator last, ListIterator first2); // 0x00f143c0
    void AssignFromList(ListIterator first, ListIterator last, int tag);   // 0x00f16280
};

// ---------------------------------------------------------------------------------------------
// vector of 0x70-byte elements with a virtual destructor
// ---------------------------------------------------------------------------------------------
const int kElementSize = 0x70;

struct Element {
    Element(const Element* other);                          // 0x00f14690
    virtual void Destroy(int flags);                        // +0x00
    void DestroySelf();                                     // 0x00e0a400
    int mData[0x1b];
};

// allocation header the SD node allocator keeps in front of the payload; a zero size means the
// block was not heap allocated and must not be released
struct BlockHeader {
    unsigned int mSize;
};

Element* MoveElements(Element* first, Element* last, Element* dst);          // 0x00f14900
Element* CopyConstructRange(Element* first, Element* last, Element* dst);    // 0x00f148c0
Element* DestroyRange(Element* first, Element* last, Element* dst);          // 0x00f120e0
Element* CopyConstructBackward(Element* first, Element* last, Element* dstEnd); // 0x00f14940
Element** CopyConstructSaved(Element** result, Element* first, Element* last,
                             Element* dst);                                  // 0x00f147a0
void     FillUninitialized(Element* dst, unsigned int n, const Element* value); // 0x00f16230
void     FillAssigned(Element* first, Element* last, const Element* value);  // 0x00f16300
void     FreeRawBlock(void* block);                                          // 0x00f47380

void* operator new(unsigned int size, const char* name, int flags, int align,
                   const char* file, int line);

inline void* AllocElementBlock(unsigned int size, int line)
{
    return ::operator new(size, "Simulator", 0, 0, "EASTL/allocator.h", line);
}

struct ElementVector {
    Element* mpBegin;                                       // +0x00
    Element* mpEnd;                                         // +0x04
    Element* mpCapacity;                                    // +0x08

    Element* EraseRange(Element* last, Element* pos);       // 0x00f16330
    void     InsertN(Element* position, unsigned int n, const Element* value); // 0x00f16390
};

// ---------------------------------------------------------------------------------------------
// @ 0x00f16260
void PartHolder::Cleanup()
{
    ReleaseParts();
    mPart.Destroy();
}

// @ 0x00f16280
void Int64ListVector::AssignFromList(ListIterator first, ListIterator last, int tag)
{
    int64* p = mpBegin;
    if (p != mpEnd) {
        do {
            if (first == last)
                break;
            *p = *first;
            ++first;
            ++p;
        } while (p != mpEnd);
    }
    if (first == last) {
        int64* lastPos = mpEnd;
        CopyRange64(lastPos, mpEnd, p);
        mpEnd -= lastPos - p;
    } else {
        InsertList(mpEnd, first, last, first);
    }
}

// @ 0x00f16330
Element* ElementVector::EraseRange(Element* last, Element* pos)
{
    Element* p = MoveElements(pos, mpEnd, last);
    Element* end = mpEnd;
    for (; p < end; ++p)
        p->Destroy(0);
    mpEnd -= pos - last;
    return last;
}

// @ 0x00f16390
void ElementVector::InsertN(Element* position, unsigned int n, const Element* value)
{
    unsigned int freeCount = (unsigned int)(mpCapacity - mpEnd);
    if (n <= freeCount) {
        if (n == 0)
            return;

        Element temp(value);

        Element* oldEnd = mpEnd;
        unsigned int tail = (unsigned int)(oldEnd - position);
        if (n < tail) {
            // the new elements fit before the end: move the last n elements into the unused space,
            // then shift the middle part right
            Element* src = oldEnd - n;
            Element* dst = oldEnd;
            CopyConstructSaved(&dst, src, oldEnd, oldEnd);
            mpEnd = mpEnd + n;
            CopyConstructBackward(position, src, mpEnd);
            FillAssigned(position, position + n, &temp);
        } else {
            // the tail is shorter than the insert: fill the unused space, then move the tail behind
            // the inserted block
            FillUninitialized(oldEnd, n - tail, &temp);
            mpEnd = mpEnd + (n - tail);
            Element* dst = oldEnd;
            CopyConstructSaved(&dst, position, oldEnd, mpEnd);
            mpEnd = mpEnd + tail;
            FillAssigned(position, oldEnd, &temp);
        }
        temp.DestroySelf();
        return;
    }

    int oldSize = (int)(mpEnd - mpBegin);
    int newCapacity = oldSize * 2;
    if (oldSize == 0)
        newCapacity = 1;
    int total = oldSize + (int)n;
    if (total < newCapacity)
        total = newCapacity;

    Element* newData = 0;
    if (total != 0)
        newData = (Element*)AllocElementBlock((unsigned int)(total * (int)sizeof(Element)), 0xd1);

    Element* p = CopyConstructRange(mpBegin, position, newData);
    DestroyRange(mpBegin, position, newData);
    FillUninitialized(p, n, value);
    p += n;
    Element* newEnd = CopyConstructRange(position, mpEnd, p);
    DestroyRange(position, mpEnd, p);

    if (mpBegin != 0 && ((BlockHeader*)mpBegin)[-1].mSize != 0)
        FreeRawBlock(mpBegin);

    mpBegin = newData;
    mpEnd = newEnd;
    mpCapacity = newData + total;
}

// ---------------------------------------------------------------------------------------------
// 00f15890: SP::cSPCreatureBase::OnPathCompleted (thiscall, `this` in ecx)
//
// Refresh of the "path completed" UI: window visibility, the progress numbers, the elapsed time
// text and the achievement/debug hooks.  Frame 0x114, 2458 bytes.
// ---------------------------------------------------------------------------------------------

// The editor UI objects are only ever used through their vtable here, so the layouts below only
// declare the slots the calling code touches (slot index = byte offset / 4).
struct IWindow {
    virtual void AddRef() = 0;                                  // +0x00  (slot 0)
    virtual void Release() = 0;                                 // +0x04  (slot 1)
    virtual void s02() = 0; virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
    virtual void s06() = 0; virtual void s07() = 0; virtual void s08() = 0;
    virtual bool GetTag(void** out, unsigned int id) = 0;       // +0x24  (slot 9)
    virtual void s10() = 0; virtual void s11() = 0; virtual void s12() = 0; virtual void s13() = 0;
    virtual const float* GetVertex() = 0;                       // +0x38  (slot 14)
    virtual void s15() = 0; virtual void s16() = 0; virtual void s17() = 0; virtual void s18() = 0;
    virtual void s19() = 0; virtual void s20() = 0; virtual void s21() = 0; virtual void s22() = 0;
    virtual void s23() = 0; virtual void s24() = 0; virtual void s25() = 0; virtual void s26() = 0;
    virtual void SetVertex(const float* v) = 0;                 // +0x6c  (slot 27)
    virtual void s28() = 0; virtual void s29() = 0; virtual void s30() = 0;
    virtual void SetVisible(int visible, int state) = 0;        // +0x7c  (slot 31)
    virtual void SetText(const wchar_t* text) = 0;              // +0x80  (slot 32)
    virtual void s33() = 0; virtual void s34() = 0; virtual void s35() = 0; virtual void s36() = 0;
    virtual void s37() = 0; virtual void s38() = 0; virtual void s39() = 0; virtual void s40() = 0;
    virtual void s41() = 0; virtual void s42() = 0; virtual void s43() = 0; virtual void s44() = 0;
    virtual void s45() = 0; virtual void s46() = 0; virtual void s47() = 0; virtual void s48() = 0;
    virtual void s49() = 0; virtual void s50() = 0; virtual void s51() = 0; virtual void s52() = 0;
    virtual void s53() = 0; virtual void s54() = 0; virtual void s55() = 0; virtual void s56() = 0;
    virtual void s57() = 0; virtual void s58() = 0; virtual void s59() = 0;
    virtual IWindow* FindChild(unsigned int id, int flag) = 0;  // +0xf0  (slot 60)
};

struct IWindowManager {
    virtual void w00() = 0; virtual void w01() = 0; virtual void w02() = 0; virtual void w03() = 0;
    virtual void w04() = 0; virtual void w05() = 0; virtual void w06() = 0; virtual void w07() = 0;
    virtual void w08() = 0; virtual void w09() = 0; virtual void w10() = 0; virtual void w11() = 0;
    virtual void w12() = 0; virtual void w13() = 0; virtual void w14() = 0; virtual void w15() = 0;
    virtual void w16() = 0; virtual void w17() = 0;
    virtual void ShowWindow(int mode, IWindow* window) = 0;     // +0x4c  (slot 19)
};

struct cSPUILayout {
    IWindow* FindWindowByID(unsigned int id);                   // 0x008105b0
    IWindow* FindWindowByID(unsigned int id, int flag);         // 0x008105b0
};

// the object the creature keeps at +0x10 (the creature "info"); only these members are touched
struct cCreatureInfo {
    char           mPad00[0x54];    // +0x00
    const wchar_t* mpText54;        // +0x54  label text handed to the window (slot 0x80)
    char        mPad58[0x38];       // +0x58
    int         mState90;           // +0x90  compared with 5 (path finished)
    int  Count();                   // 0x00f191a0
    int  ElapsedMs();               // 0x00f19190
    float Ratio();                  // 0x00f19d10  (x87 float return)
};

template <class T> struct AutoRefCount {
    T* mpObject;                                            // +0x00
    void Assign(T* p)
    {
        if (p != mpObject) {
            if (p)
                p->AddRef();
            T* old = mpObject;
            mpObject = p;
            if (old)
                old->Release();
        }
    }
};

struct cPathFollower {                                      // the object at +0x28
    void SetTarget(void* target);                           // 0x00f14d90
};

struct cPathStepper {                                       // the object at +0x20
    void Step(int a, int b, int c);                          // 0x00f46cf0
};

struct cSPCreatureBase {
    char                       mPad00[0x10];                // +0x00
    cCreatureInfo*             mpInfo;                      // +0x10
    cSPUILayout*               mpLayout;                    // +0x18
    char                       mPad1c[4];                   // +0x1c
    cPathStepper*              mpStepper;                   // +0x20
    char                       mPad24[4];                   // +0x24
    cPathFollower              mFollower;                   // +0x28
    char                       mPad2c[0x8c];                // +0x2c
    void*                      mpDataB8;                    // +0xb8  tagged data object (vtable +0x24)
    float                      mBc;                         // +0xbc
    float                      mC0;                         // +0xc0
    float                      mC4;                         // +0xc4
    float                      mC8;                         // +0xc8
    float                      mCc;                         // +0xcc
    int                        mD0;                         // +0xd0
    AutoRefCount<IWindow>      mWndDc;                      // +0xdc
    AutoRefCount<IWindow>      mWndE0;                      // +0xe0

    void OnPathCompleted();                                 // 0x00f15890
};

// --- callees --------------------------------------------------------------------------------
IWindowManager* __cdecl WindowManager();                                 // 0x0067caa0
int*   __cdecl EA_Hash_FNV1_String8();                                   // 0x0041e990
int    __cdecl FUN_00eec540(int key);                                    // 0x00eec540
int    __cdecl FUN_00eec580(int value);                                  // 0x00eec580
int    __cdecl FUN_00eec570();                                           // 0x00eec570
float  __cdecl FUN_00eec5b0();                                           // 0x00eec5b0
bool   __cdecl FUN_00552450(void* owner, void** out);                    // 0x00552450
void*  __cdecl FUN_005507a0(void* handle);                               // 0x005507a0
void   __cdecl FUN_0054e530(void* owner, void* data, void* out, int f);  // 0x0054e530
bool   __cdecl FUN_00f19640();                                           // 0x00f19640
void   __cdecl FUN_00f39110(void* out);                                  // 0x00f39110
void   __cdecl FUN_00f14d90(cPathFollower* self, void* target);          // 0x00f14d90
void   __cdecl FUN_00f46cf0(cPathStepper* self, int a, int b, int c);    // 0x00f46cf0
void*  __cdecl FUN_00f3bcb0(void* owner);                                // 0x00f3bcb0
bool   __cdecl FUN_00f3cb60(void* owner);                                // 0x00f3cb60
void*  __cdecl FUN_008dc790(cCreatureInfo* self);                        // 0x008dc790
void*  __cdecl FUN_00675250(unsigned int id, int flag);                  // 0x00675250
void   __cdecl FUN_00676e90(void* controller);                           // 0x00676e90
void*  __cdecl FUN_0067cb30(void* owner);                                // 0x0067cb30
void   __cdecl FUN_0060e600(void* owner, const long long* values, int n); // 0x0060e600
void   __cdecl FUN_00806a60(IWindow* w);                                 // 0x00806a60
void   __cdecl SetNumberString(wchar_t* buf, int size, long long value);  // 0x00881ae0
void   __cdecl SetNumberStringReal(double value, int size, wchar_t* buf, int flag); // 0x00881f00

// the localized-text handle (0x1c bytes): 0x006b5770 ctor, 0x006b5240 dtor, 0x006b55c0 c_str
struct cLocalizedText {
    cLocalizedText(unsigned int table, unsigned int id, int flags);  // 0x006b5770
    ~cLocalizedText();                                               // 0x006b5240
    const wchar_t* c_str();                                          // 0x006b55c0
    char mData[0x1c];
};

// 0x00f39110 fills a time structure whose members at +0x04 and +0x0c are localized strings; only
// their c_str() is used here, so the two are modelled as 4-byte handles at the real offsets.
struct cStringRef {
    const wchar_t* c_str();                                          // 0x006b55c0
    int mTableId;                                                    // +0x00
};
struct cTimeStrings {
    int         mKind;                                               // +0x00
    cStringRef  mOuter;                                              // +0x04
    int         mPad08;                                              // +0x08
    cStringRef  mInner;                                              // +0x0c
};

// SP::cString (0x1c bytes; the three ctors and the dtor below are the ones the original calls)
struct cString {
    cString() {}                                                     // no constructor call in the original
    cString(int value);                                              // 0x006b55c0
    cString(unsigned int key, unsigned int id, int flag);             // 0x006b5770
    ~cString();                                                      // 0x006b5240
    const wchar_t* Data() const { return mpData; }
    int            mTableId;                                        // +0x00
    wchar_t*       mpData;                                          // +0x04
    int            mLength;                                         // +0x08
    int            mCapacity;                                       // +0x0c
    wchar_t        mInline[6];                                      // +0x10 (inline buffer)
};

cString* __cdecl FormatString(cString* out, const wchar_t* fmt, ...);    // 0x00f14120

extern void* gSporeApp;                                     // 0x016c7aa4

// @ 0x00f15890
void cSPCreatureBase::OnPathCompleted()
{
    const char bFinished = (char)(mpInfo->mState90 == 5);   // "path completed" flag
    const int  nTotal = mpInfo->Count();                    // 0x00f191a0

    if (mpDataB8 == 0) {
        // no tagged data: just swap the two progress windows
        mWndDc.Assign(mpLayout->FindWindowByID(0x7c79820));
        IWindow* wIdle = mpLayout->FindWindowByID(0x7c796d0, 1);
        if (wIdle)
            wIdle->SetVisible(1, 0);
    } else {
        mWndDc.Assign(mpLayout->FindWindowByID(0x7c796d0, 1));
        IWindow* wDone = mpLayout->FindWindowByID(0x7c79820, 1);
        if (wDone)
            wDone->SetVisible(1, 0);

        int nKey = 0;
        if (mpDataB8 != 0) {
            void* tag = 0;
            if (((IWindow*)mpDataB8)->GetTag(&tag, 0xcf837237) && *(short*)((char*)tag + 0x12) == 9)
                nKey = *EA_Hash_FNV1_String8();
        }

        mD0 = FUN_00eec540(nKey);
        mC4 = (float)FUN_00eec580(mD0);
        mCc = (float)FUN_00eec580(mD0 + 1);
        mC0 = (float)nKey;
        mC8 = (float)nTotal + (float)nKey;

        if (FUN_00eec570() <= mD0 + 1)
            if (mC8 > mCc)
                mC8 = mCc;
        if (mC4 > mCc - 1.0f)
            mC4 = mCc - 1.0f;
        if (mC0 != mC8)
            mBc = FUN_00eec5b0();

        // the progress bar: take the bar rectangle of the two helper windows and move its low edge
        IWindow* wBar = mpLayout->FindWindowByID(0x7c7a310, 1);
        IWindow* wRange = mpLayout->FindWindowByID(0x7c7a318, 1);
        const float* range = wRange->GetVertex();
        const float lo = range[1];
        const float hi = range[3];
        float bar[4];
        memcpy(bar, wBar->GetVertex(), sizeof(bar));
        float t = 1.0f - (mC0 - mC4) / (mCc - mC4);
        if (t < 0.0f)
            t = 0.0f;
        bar[1] = lo + (hi - lo) * t;
        wBar->SetVertex(bar);

        // the progress label
        wchar_t text[0x10];
        IWindow* wLabel = mpLayout->FindWindowByID(0x7c7a088, 1);
        SetNumberString(text, 0x20, (long long)mCc);
        if (wLabel)
            wLabel->SetText(text);
        const char bMoved = (char)(bar[1] != lo);          // NaN counts as moved
        if (wLabel)
            wLabel->SetVisible(1, bMoved);

        SetNumberString(text, 0x20, (long long)mC0);
        IWindow* wLabel2 = mpLayout->FindWindowByID(0x7c79fd8, 1);
        if (wLabel2)
            wLabel2->SetText(text);

        cString progress;
        FormatString(&progress, L"%d/%d", mD0, FUN_00eec570());
        IWindow* wProgress = mpLayout->FindWindowByID(0x7c79af8, 1);
        if (wProgress)
            wProgress->SetText(progress.Data());

        FUN_00806a60(mpLayout->FindWindowByID(0x7c55300, 1));
        void* info = FUN_00f3bcb0(gSporeApp);
        int* dest = (int*)((char*)gSporeApp + 0x7c);   // the UI state block follows the app object
        dest[5] = *(int*)info;                          // +0x14
        dest[6] = ((int*)info)[1];                      // +0x18
        dest[7] = ((int*)info)[2];                      // +0x1c
        dest[8] = -1;                                   // +0x20

        cLocalizedText flagA(0x623d2fc0, 0x7ceb16a, 0);   // 0x006b5770
        IWindow* wFlagA = mpLayout->FindWindowByID(0x7c79b20, 1);
        if (wFlagA)
            wFlagA->SetText(flagA.c_str());
        cLocalizedText flagB(0x623d2fc0, 0x7ceb16b, 0);
        IWindow* wFlagB = mpLayout->FindWindowByID(0x7c79b21, 1);
        if (wFlagB)
            wFlagB->SetText(flagB.c_str());
    }

    if (mWndDc.mpObject)
        mWndDc.mpObject->SetVisible(1, 1);
    IWindowManager* wm = WindowManager();
    wm->ShowWindow(0, mWndDc.mpObject);

    if (mWndDc.mpObject) {
        IWindow* w = mWndDc.mpObject->FindChild(0x7c7aa60, 1);
        if (w)
            w->SetVisible(1, bFinished);
        IWindow* w2 = mWndDc.mpObject->FindChild(0x7c7aa50, 1);
        if (w2)
            w2->SetVisible(1, !bFinished);
    }

    wchar_t buf[0x10];
    SetNumberString(buf, 0x20, (long long)nTotal);
    if (mWndDc.mpObject) {
        IWindow* w = mWndDc.mpObject->FindChild(0x7c79d78, 1);
        if (w)
            w->SetText(buf);
    }

    {
        const int nTicks = (int)(mpInfo->Ratio() * *(const float*)0x13ec4d0);
        SetNumberStringReal((double)nTicks, 0x20, buf, 0);
        if (mWndDc.mpObject) {
            IWindow* w = mWndDc.mpObject->FindChild(0x7c79e00, 1);
            if (w)
                w->SetText(buf);
        }
    }

    {
        cTimeStrings timeStrings;
        FUN_00f39110(&timeStrings);
        const int ms = mpInfo->ElapsedMs();
        const int minutes = ms / 60000;
        const int hours = minutes / 60;
        const int days = hours / 60;
        cString text;
        FormatString(&text, L"%02d%s%02d%s%02d", days, timeStrings.mInner.c_str(),
                     hours % 60, timeStrings.mOuter.c_str(), minutes % 60);
        if (mWndDc.mpObject) {
            IWindow* w = mWndDc.mpObject->FindChild(0x7c79d98, 1);
            if (w)
                w->SetText(text.Data());
        }
    }

    if (mWndDc.mpObject) {
        IWindow* w = mWndDc.mpObject->FindChild(0x7c7c590, 1);
        if (w) {
            w->SetVisible(1, !bFinished);
            if (!bFinished)
                w->SetText(mpInfo->mpText54);
        }
    }

    mWndE0.Assign(mpLayout->FindWindowByID(0x7c79918, 1));
    if (mWndE0.mpObject) {
        mWndE0.mpObject->SetVisible(1, 0);
        IWindow* w = mWndE0.mpObject->FindChild(0x7c7aa60, 1);
        if (w)
            w->SetVisible(1, bFinished);
        IWindow* w2 = mWndE0.mpObject->FindChild(0x7c7aa50, 1);
        if (w2)
            w2->SetVisible(1, !bFinished);
    }

    // simulator bookkeeping / achievements
    void* pair[2] = {0, 0};
    int  v0 = 0, v1 = 0;
    void* mgr = *(void**)((char*)gSporeApp + 0x74);
    if (FUN_00552450(*(void**)((char*)mgr + 0x10), pair)) {
        void* p = FUN_005507a0(pair[0]);
        v0 = *(int*)p;
        v1 = ((int*)p)[1];
    }

    {
        const int ms = mpInfo->ElapsedMs();
        const int nTicks = (int)(mpInfo->Ratio() * *(const float*)0x13ec5b4);
        FUN_00f46cf0(mpStepper, v0, v1, nTicks);
        FUN_00f14d90(&mFollower, FUN_008dc790(mpInfo));
    }

    if (FUN_00f19640()) {
        if (!FUN_00f3cb60(*(void**)((char*)gSporeApp + 0x74))) {
            const unsigned int id = bFinished ? 0xf332be69u : 0x23346746u;
            FUN_00676e90(FUN_00675250(id, 1));
        }
        const int key = 0x706ccb27 + (bFinished ? 0xbcecb854 : 0);
        int dbg[2] = {0, 0};
        if (mpDataB8 != 0) {
            void* p = FUN_00f3bcb0(*(void**)((char*)gSporeApp + 0x74));
            void* q = FUN_0067cb30(*(void**)((char*)gSporeApp + 0x74));
            FUN_0054e530(q, p, dbg, 0);
        }
        long long values[4];
        values[0] = (long long)(int)(mpInfo->Ratio() * *(const float*)0x13ec5b4);
        values[1] = (long long)mpInfo->ElapsedMs();
        values[2] = (long long)mpInfo->Count();
        values[3] = (long long)dbg[0] | ((long long)dbg[1] << 32);
        void* ctrl = FUN_0067cb30(*(void**)((char*)gSporeApp + 0x74));
        FUN_0060e600(ctrl, values, 4);
        (void)key;
    }

    if (pair[1])
        ((IWindow*)pair[1])->Release();
}
