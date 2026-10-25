// Slice s00673c50 - `anonymous namespace'::cBuildXHTMLDetokenizer and its
// eastl::vector<cVar, fixed_vector_allocator<...>> internals (cVar stride 0x54).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (same region as s00671840).
#include "types.h"
#include <string.h>
#include <intrin.h>

void DeleteObj(void* p);   // 0x00f47380
void* EditorAlloc(unsigned size, const char* name, int a, int b, const char* file,
                  int line);  // 0x00f473a0

// ---- cVar = a fixed-capacity eastl::basic_string<wchar_t> ------------
struct EStr {
    unsigned short* mpBegin;     // +0x00
    unsigned short* mpEnd;       // +0x04
    unsigned short* mpCapacity;  // +0x08
    void*           mpAlloc;     // +0x0c
    unsigned short* mpInline;    // +0x10
    unsigned short  mBuf[0x20];  // +0x14 .. +0x54

    void  assign(unsigned short* first, unsigned short* last);  // 0x00672750
    EStr* Construct(const unsigned short* src);
};

// ---- vector<EStr> ----------------------------------------------------
struct EStrVec {
    EStr* mpBegin;     // +0x00
    EStr* mpEnd;       // +0x04
    EStr* mpCapacity;  // +0x08
    unsigned padC;     // +0x0c
    EStr* mpInlineStorage;  // +0x10
    unsigned pad14;    // +0x14
    EStr mBuffer[8];   // +0x18 .. +0x2b8
    void DoInsertValue(EStr* pos, const EStr* v);   // 0x00674440
    void  push_back(const EStr& v);
};

// ---- 0x00674170 : eastl fill_n over wchar_t --------------------------
// @ 0x00674170
void* FillN(unsigned short* first, unsigned n, unsigned short value) {
    unsigned short* p = first;
    unsigned short* end = first + n;
    while (p < end) *p++ = value;
    return first;
}

// ---- 0x006741b0 : find text element by wide-string key ---------------
// @ 0x006741b0
int __stdcall FindRange(int* p, unsigned short* key) {
    int i = p[0];
    for (;;) {
        if (i == p[1]) return 0;
        unsigned* q = *(unsigned**)(i + 900);
        unsigned* qEnd = *(unsigned**)(i + 0x388);
        for (; q != qEnd; q += 0x15) {
            unsigned short* s = (unsigned short*)*q;
            unsigned short* k = key;
            int cmp;
            for (;;) {
                unsigned short a = *s, b = *k;
                if (a != b) { cmp = (b < a) ? 1 : -1; break; }
                if (a == 0) { cmp = 0; break; }
                a = s[1]; b = k[1];
                if (a != b) { cmp = (b < a) ? 1 : -1; break; }
                s += 2; k += 2;
                if (a == 0) { cmp = 0; break; }
            }
            if (cmp == 0) return i;
        }
        i += 0x63c;
    }
}

// ---- 0x00674230 : vector fill-insert --------------------------------
struct FillVec {
    unsigned* FillInsert(unsigned count, unsigned value);
    void append_n_char(unsigned count, unsigned value);  // 0x0042d2e0
};
// @ 0x00674230
unsigned* FillVec::FillInsert(unsigned count, unsigned value) {
    unsigned* p = (unsigned*)this;
    unsigned* begin = (unsigned*)p[0];
    unsigned have = (p[1] - (unsigned)begin) >> 1;
    if (have < count) {
        unsigned short* oldEnd = (unsigned short*)((char*)begin + have * 2);
        for (unsigned short* it = (unsigned short*)begin; it < oldEnd; ++it) *it = (unsigned short)value;
        // The binary grows the (wide-string) vector with WString::append_n_char rather than a
        // plain fill: have < count means the existing buffer can't hold the range.
        append_n_char(count - have, value);
    } else {
        unsigned short* mid = (unsigned short*)((char*)begin + count * 2);
        for (unsigned short* it = (unsigned short*)begin; it < mid; ++it) *it = (unsigned short)value;
        void* src = (void*)p[1];
        void* dst = (void*)(p[0] + count * 2);
        if (dst != src) {
            memmove(dst, src, 2);
            p[1] = p[1] + (((char*)src - (char*)dst) >> 1) * -2;
        }
    }
    return p;
}

// ---- 0x006742f0 : copy-assign backward (uninitialized_move tail) -----
// @ 0x006742f0
EStr* MoveAssignBackward(EStr* first, EStr* last, EStr* dst) {
    if (first != last) {
        EStr* s = last - 1;
        EStr* d = dst - 1;
        do {
            if (d != s) {
                unsigned short* b = d->mpBegin;
                if (b != d->mpEnd) { *b = 0; d->mpEnd = d->mpBegin; }
                d->assign(s->mpBegin, s->mpEnd);
            }
            --s; --d;
        } while (s != first);
        return d;
    }
    return dst;
}

// ---- 0x00674340 : uninitialized copy-construct forward --------------
// @ 0x00674340
EStr* UninitCopy(EStr* first, EStr* last, EStr* dst) {
    while (first != last) {
        if (dst) {
            unsigned short* inl = (unsigned short*)((char*)dst + 0x14);
            dst->mpInline = inl;
            dst->mpEnd = inl;
            dst->mpBegin = inl;
            dst->mpCapacity = inl + 0x20;
            *inl = 0;
            dst->assign(first->mpBegin, first->mpEnd);
        }
        ++first; ++dst;
    }
    return dst;
}

// ---- 0x006743a0 : destroy-value range -------------------------------
// @ 0x006743a0
EStr* DestroyValues(EStr* first, EStr* last, EStr* dst) {
    while (first != last) {
        unsigned short* b = first->mpBegin;
        if ((((char*)first->mpCapacity - (char*)b) & ~1) > 2 && b && b != first->mpInline)
            DeleteObj(b);
        ++first;
        ++dst;
    }
    return dst;
}

// ---- 0x006743f0 : cVar constructor from wide C string ---------------
// @ 0x006743f0
EStr* EStr::Construct(const unsigned short* src) {
    unsigned short* inl = (unsigned short*)((char*)this + 0x14);
    mpInline = inl;
    _ReadWriteBarrier();
    mpCapacity = inl + 0x20;
    mpEnd = inl;
    mpBegin = inl;
    *inl = 0;
    const unsigned short* p = src;
    while (*p) ++p;
    assign((unsigned short*)src, (unsigned short*)src + (p - src));
    return this;
}

// ---- 0x00674440 : vector::DoInsertValue -----------------------------
// @ 0x00674440
void EStrVec::DoInsertValue(EStr* pos, const EStr* v) {
    if (mpEnd != mpCapacity) {
        EStr* end = mpEnd;
        const EStr* value = v;
        if (value >= pos && value < end)
            value = value + 1;

        if (end != 0) {
            unsigned short* inl = (unsigned short*)((char*)end + 0x14);
            end->mpInline = inl;
            _ReadWriteBarrier();
            end->mpCapacity = inl + 0x20;
            end->mpEnd = inl;
            end->mpBegin = inl;
            _ReadWriteBarrier();
            *inl = 0;
            end->assign((end - 1)->mpBegin, (end - 1)->mpEnd);
        }

        MoveAssignBackward(pos, mpEnd - 1, mpEnd);

        if (pos != value) {
            if (pos->mpBegin != pos->mpEnd) {
                *pos->mpBegin = 0;
                pos->mpEnd = pos->mpBegin;
            }
            pos->assign(value->mpBegin, value->mpEnd);
        }
        mpEnd++;
        return;
    }

    int count = (int)(mpEnd - mpBegin);
    int newCapacity = count != 0 ? count * 2 : 1;
    EStr* newBegin = newCapacity != 0
        ? (EStr*)EditorAlloc(
              (unsigned)(newCapacity * sizeof(EStr)), "Editor", 0, 0,
              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
              0xd1)
        : (EStr*)0;

    EStr* first = UninitCopy(mpBegin, pos, newBegin);
    DestroyValues(mpBegin, pos, newBegin);
    if (first != 0) {
        unsigned short* inl = (unsigned short*)((char*)first + 0x14);
        first->mpInline = inl;
        _ReadWriteBarrier();
        first->mpEnd = inl;
        first->mpBegin = inl;
        first->mpCapacity = inl + 0x20;
        *inl = 0;
        first->assign(v->mpBegin, v->mpEnd);
    }

    EStr* oldEnd = mpEnd;
    EStr* newEnd = UninitCopy(pos, oldEnd, first + 1);
    DestroyValues(pos, oldEnd, first + 1);

    if (mpBegin != 0 && mpBegin != (EStr*)mpInlineStorage)
        DeleteObj(mpBegin);

    mpEnd = newEnd;
    mpBegin = newBegin;
    mpCapacity = newBegin + newCapacity;
}

// ---- 0x006745d0 : vector::push_back ---------------------------------
// @ 0x006745d0
void EStrVec::push_back(const EStr& v) {
    EStr* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e) {
            unsigned short* inl = (unsigned short*)((char*)e + 0x14);
            e->mpInline = inl;
            _ReadWriteBarrier();
            e->mpCapacity = inl + 0x20;
            e->mpEnd = inl;
            e->mpBegin = inl;
            *inl = 0;
            e->assign(v.mpBegin, v.mpEnd);
        }
        return;
    }
    DoInsertValue(e, &v);
}

// ---- 0x00673c50 : cBuildXHTMLDetokenizer ctor ------------------------
// Layout mirrors the class in slice s00672bd0 (cVar stride 0x63c).
struct CVar;

struct CAction {
    EStr  mString;   // +0x00
    void* mAction;   // +0x54
};

struct CActionVec {
    CAction* mpBegin;         // +0x00
    CAction* mpEnd;           // +0x04
    CAction* mpCapacity;      // +0x08
    unsigned padC;            // +0x0c
    CAction* mpInlineStorage; // +0x10
    unsigned pad14;           // +0x14
    CAction  mBuffer[8];      // +0x18 .. +0x2d8
    void DoInsertValue(CAction* pos, const CAction& v);  // 0x00673410
};

struct CVar {
    int       mId;        // +0x000
    EStr      mName;      // +0x004
    EStr      mValue;     // +0x058
    CActionVec mActions;  // +0x0ac
    EStrVec   mStrings;   // +0x384
    void DefaultConstruct();                 // 0x006732e0
    void CopyConstruct(const CVar& other);   // 0x00673870
    void Destruct();                         // 0x00673360
};

struct CVarVec {
    CVar* mpBegin;         // +0x000
    CVar* mpEnd;           // +0x004
    CVar* mpCapacity;      // +0x008
    unsigned padC;         // +0x00c
    CVar* mpInlineStorage; // +0x010
    unsigned pad14;        // +0x014
    CVar  mBuffer[16];     // +0x018 .. +0x63d8
    void DoInsertValue(CVar* pos, const CVar& v);  // 0x00673b00
};

// basic_string<wchar_t, eastl::allocator>
struct WString {
    unsigned short* mpBegin;     // +0x00
    unsigned short* mpEnd;       // +0x04
    unsigned short* mpCapacity;  // +0x08
    int             mAllocator;  // +0x0c
    void set_capacity(unsigned n);  // 0x0042f360
};

struct String8 {
    char* mpBegin;     // +0x00
    char* mpEnd;       // +0x04
    char* mpCapacity;  // +0x08
};

// 4-byte element vector used by cPropertyList::GetArguments.
struct PtrVec {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    void** mpCapacity;  // +0x08
};

// cPropertyList virtual layout: AddRef at +0x00, argument getter at +0x44.
class cPropertyList {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void GetArguments(PtrVec* out);  // vtable +0x44
};

// EA argument-script parser object (opaque storage; methods are in the binary).
struct CArgumentsEH {
    int mData[0x11];  // 0x44 bytes
    void Construct(const char* text);       // 0x008386d0
    void CollectOptions(PtrVec* out);       // 0x00838350
    char** OptionArguments(const char* name, int* count, int min, int max);  // 0x00838130
    void Destroy();                         // 0x00837fa0
};

extern void* gXHTMLVTable;             // 0x01400f90
extern unsigned short gEmptyWide;      // 0x01667bac
extern unsigned short gEmptyWideCap;   // 0x01667bae

bool SP_GetPropertyAsString16(cPropertyList* props, unsigned id, WString* out);  // 0x006a1400
char* EA_ConvertToString8(String8* out, const WString* src);                     // 0x0093c570
WString* EA_ConvertToString16Impl(WString* out, const char* src, unsigned len); // 0x0093c5a0
void TokenActionCopy(CVar* var, const unsigned short* const* args);             // 0x00672b50
void TokenActionReplace(CVar* var, const unsigned short* const* args);          // 0x00672f70

struct Detokenizer {
    void* mpVTable;              // +0x000
    char  mBaseData[0x58];       // +0x004
    cPropertyList* mpOwner;      // +0x05c
    int   mState;                // +0x060
    WString mTemp;               // +0x064
    WString mScratch;            // +0x074
    WString mText;               // +0x084
    void* mpTextResult;          // +0x094
    CVar* mpCurrentVar;          // +0x098
    CAction* mpCurrentAction;    // +0x09c
    CVarVec mVars;               // +0x0a0
    CVarVec mListVars;           // +0x6478

    Detokenizer(cPropertyList* owner);
    void BaseConstruct();        // 0x006b6490
};

void EStr_Init(EStr* s) {
    s->mpInline = s->mBuf;
    s->mpCapacity = s->mBuf + 0x20;
    s->mpEnd = s->mBuf;
    s->mpBegin = s->mBuf;
    s->mBuf[0] = 0;
}

void EStr_Destroy(EStr* s) {
    if (s->mpBegin && s->mpBegin != s->mpInline &&
        (s->mpCapacity - s->mpBegin) > 1) {
        DeleteObj(s->mpBegin);
    }
}

void WString_Init(WString* s) {
    s->mpBegin = &gEmptyWide;
    s->mpEnd = &gEmptyWide;
    s->mpCapacity = &gEmptyWideCap;
}

void WString_Reserve(WString* s) {
    int size = (int)(s->mpEnd - s->mpBegin);
    int want = size > 1000 ? size : 1000;
    int capacity = (int)(s->mpCapacity - s->mpBegin);
    if (capacity < want + 1)
        s->set_capacity((unsigned)(want + 1));
}

void CVarVec_Init(CVarVec* v) {
    v->mpBegin = &v->mBuffer[0];
    v->mpEnd = &v->mBuffer[0];
    v->mpInlineStorage = &v->mBuffer[0];
    v->mpCapacity = &v->mBuffer[16];
}

void PushCVar(CVarVec* v, const CVar& value) {
    if (v->mpEnd < v->mpCapacity) {
        CVar* e = v->mpEnd;
        v->mpEnd = e + 1;
        if (e)
            e->CopyConstruct(value);
    } else {
        v->DoInsertValue(v->mpEnd, value);
    }
}

void PushCAction(CActionVec* v, const CAction& value) {
    if (v->mpEnd < v->mpCapacity) {
        CAction* e = v->mpEnd;
        v->mpEnd = e + 1;
        if (e) {
            EStr_Init(&e->mString);
            e->mString.assign(value.mString.mpBegin, value.mString.mpEnd);
            e->mAction = value.mAction;
        }
    } else {
        v->DoInsertValue(v->mpEnd, value);
    }
}

// @ 0x00673c50
Detokenizer::Detokenizer(cPropertyList* owner) {
    BaseConstruct();
    mpVTable = &gXHTMLVTable;
    mpOwner = owner;
    if (owner)
        owner->v00();
    mState = 0;

    WString_Init(&mTemp);
    WString_Init(&mScratch);
    WString_Init(&mText);
    mpTextResult = 0;
    mpCurrentVar = 0;
    mpCurrentAction = 0;

    WString_Reserve(&mScratch);
    WString_Reserve(&mText);
    WString_Reserve(&mTemp);

    CVarVec_Init(&mVars);
    CVarVec_Init(&mListVars);

    PtrVec args;
    args.mpBegin = 0;
    args.mpEnd = 0;
    args.mpCapacity = 0;
    owner->GetArguments(&args);

    while (args.mpBegin != args.mpEnd) {
        args.mpEnd -= 1;
        unsigned id = (unsigned)(unsigned long)args.mpEnd[0];
        SP_GetPropertyAsString16(owner, id, &mTemp);

        if (mTemp.mpBegin != mTemp.mpEnd && mTemp.mpBegin[0] == 0x2d) {
            CVar temp;
            temp.DefaultConstruct();
            PushCVar(&mListVars, temp);
            temp.Destruct();

            CVar* var = &mListVars.mpEnd[-1];
            var->mId = (int)id;

            String8 str8;
            str8.mpBegin = 0;
            str8.mpEnd = 0;
            str8.mpCapacity = 0;
            char* name8 = EA_ConvertToString8(&str8, &mTemp);

            CArgumentsEH cargs;
            cargs.Construct(name8);

            PtrVec options;
            options.mpBegin = 0;
            options.mpEnd = 0;
            options.mpCapacity = 0;
            cargs.CollectOptions(&options);

            unsigned optionCount = (unsigned)(options.mpEnd - options.mpBegin);
            for (unsigned i = 0; i < optionCount; ++i) {
                const char* optName = (const char*)options.mpBegin[i];

                CAction action;
                EStr_Init(&action.mString);
                action.mAction = 0;
                PushCAction(&var->mActions, action);
                EStr_Destroy(&action.mString);

                CAction* pushed = &var->mActions.mpEnd[-1];
                if (strcmp(optName, "copy") == 0)
                    pushed->mAction = (void*)&TokenActionCopy;
                else if (strcmp(optName, "replace") == 0)
                    pushed->mAction = (void*)&TokenActionReplace;
                else {
                    var->mActions.mpEnd -= 1;
                    EStr_Destroy(&pushed->mString);
                    continue;
                }

                int count = 0;
                char** optArgs = cargs.OptionArguments(optName, &count, 0, 0x7fffffff);
                if (count > 0) {
                    const char* value8 = *optArgs;
                    WString wide;
                    WString_Init(&wide);
                    EA_ConvertToString16Impl(&wide, value8, (unsigned)strlen(value8));

                    if (pushed->mString.mpBegin != wide.mpBegin) {
                        if (pushed->mString.mpBegin != pushed->mString.mpEnd) {
                            pushed->mString.mpBegin[0] = 0;
                            pushed->mString.mpEnd = pushed->mString.mpBegin;
                        }
                        unsigned short* end = wide.mpBegin;
                        while (*end)
                            ++end;
                        pushed->mString.assign(wide.mpBegin, end);
                    }

                    if (wide.mpBegin && wide.mpBegin != &gEmptyWide &&
                        (wide.mpCapacity - wide.mpBegin) > 1)
                        DeleteObj(wide.mpBegin);
                }
            }

            if (options.mpBegin && ((int*)options.mpBegin)[-1] != 0)
                DeleteObj(options.mpBegin);
            cargs.Destroy();
            if (str8.mpBegin && (str8.mpCapacity - str8.mpBegin) > 1)
                DeleteObj(str8.mpBegin);
        }
    }

    if (args.mpBegin && ((int*)args.mpBegin)[-1] != 0)
        DeleteObj(args.mpBegin);
}
