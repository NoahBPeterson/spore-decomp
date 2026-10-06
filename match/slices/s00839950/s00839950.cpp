// Slice s00839950 (batch w2g7).
// EA::ArgScript::cArgumentSpec / cOptionsSpec / cArguments and the EASTL
// vector/string/copy helpers they instantiate (compiled /O2; 8/16-byte value
// copies use fld/fstp, so no /arch:SSE).
// Built /O2 /MD /Gy /EHsc /TP.

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef int            int32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p);
void* __cdecl memcpy(void* dst, const void* src, unsigned n);
}
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";

namespace eastl {
struct allocator { unsigned char pad[4]; };
struct sp_vector_allocator : allocator {};

// ---- basic_string<char, allocator> (0x10) ----
struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    void assign(const char* first, const char* last);   // 0x00454cb0
    void append(const char* first, const char* last);   // 0x00455d60
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8(const string8& x);                          // 0x0057cb10
};

// generic vector layout used only for field offsets
template <typename T>
struct vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
};
}  // namespace eastl

// ---------------------------------------------------------------------------
// ArgScript types
// ---------------------------------------------------------------------------

// ---- cArgInfo (0x20) ----
struct cArgInfo {
    int mType;                       // +0x00
    eastl::string8 mName;            // +0x04
    void* mLocation;                 // +0x14
    bool mIsDependent;               // +0x18
    int mFlagToSet;                  // +0x1c

    cArgInfo(const cArgInfo& x);     // 0x00838ab0
    cArgInfo& operator=(const cArgInfo& x) {
        mType = x.mType;
        if (&mName != &x.mName)
            mName.assign(x.mName.mpBegin, x.mName.mpEnd);
        mLocation = x.mLocation;
        mIsDependent = x.mIsDependent;
        mFlagToSet = x.mFlagToSet;
        return *this;
    }
};

// ---- cEnumParseInfo (0x08) / cEnumSpec (0x18) ----
struct cEnumParseInfo { char* mToken; int mValue; };

struct cEnumSpec {
    eastl::string8 mName;            // +0x00
    cEnumParseInfo* mEnumInfo;       // +0x10
    int mPad14;                      // +0x14

    cEnumSpec(const cEnumSpec& x);   // 0x00e84850
    cEnumSpec& operator=(const cEnumSpec& x) {
        if (this != &x)
            mName.assign(x.mName.mpBegin, x.mName.mpEnd);
        mEnumInfo = x.mEnumInfo;
        mPad14 = x.mPad14;
        return *this;
    }
};

// ---- eastl::vector<cArgInfo, sp_vector_allocator> (0x10) ----
cArgInfo* __cdecl MoveArgRange(cArgInfo* first, cArgInfo* last, cArgInfo* dest);        // 0x00838f20
void      __cdecl UninitCopyArgEH(cArgInfo** pp, cArgInfo* first, cArgInfo* last,
                                  cArgInfo* dest, const void* x);                        // 0x00838bc0

struct VecArgInfo {
    cArgInfo* mpBegin;               // +0x00
    cArgInfo* mpEnd;                 // +0x04
    cArgInfo* mpCapacity;            // +0x08
    eastl::sp_vector_allocator mAllocator;  // +0x0c

    VecArgInfo(const VecArgInfo& x);                                    // 0x00839950
    ~VecArgInfo();                                                      // 0x00838d?0 VectorBase dtor
    VecArgInfo& operator=(const VecArgInfo& x);                         // 0x0083a740
    void DoInsertValue(cArgInfo* pos, const cArgInfo& v);               // 0x0083a3c0
    void DoAllocate(unsigned n, const eastl::sp_vector_allocator& a);   // 0x00838b30
    cArgInfo* DoAllocateCopy(unsigned n, cArgInfo* f, cArgInfo* l);     // 0x00838e20
    void FreeRange(cArgInfo* f, cArgInfo* l);                           // 0x0076e430
};

// ---- eastl::vector<cEnumSpec, sp_vector_allocator> (0x10) ----
cEnumSpec* __cdecl UninitCopyEnum(cEnumSpec* first, cEnumSpec* last, cEnumSpec* dest);       // 0x00838cd0
void       __cdecl UninitDestroyEnum(cEnumSpec* first, cEnumSpec* last, cEnumSpec* dest);    // 0x00838ed0
cEnumSpec* __cdecl CopyBackwardEnum(cEnumSpec* first, cEnumSpec* last, cEnumSpec* destEnd);  // 0x00839040

struct VecEnumSpec {
    cEnumSpec* mpBegin;
    cEnumSpec* mpEnd;
    cEnumSpec* mpCapacity;
    eastl::sp_vector_allocator mAllocator;

    void DoInsertValue(cEnumSpec* pos, const cEnumSpec& v);             // 0x0083a580
};

// ---- cOptionsSpec (0x38) ----
struct cOptionsSpec {
    eastl::string8 mName;            // +0x00
    eastl::string8 mDescription;     // +0x10
    VecArgInfo     mArguments;       // +0x20
    int            mPad30;           // +0x30
    int            mFlagToSet;       // +0x34

    cOptionsSpec& operator=(const cOptionsSpec& x);
};
typedef eastl::vec<cOptionsSpec> VecOptionsSpec;

// ---- cArguments (0x38) ----
struct cOptionArgInfo {
    char* mName;
    int   mFirstArgumentIndex;
    int   mNumArguments;
    bool  mProcessed;
};
struct cArguments {
    eastl::vec<char>              mArgStorage;         // +0x00
    eastl::vec<char*>             mArguments;          // +0x10
    eastl::vec<cOptionArgInfo>    mOptionArguments;    // +0x20
    int                           mMainArgumentsStart; // +0x30
    int                           mNumMainArguments;   // +0x34
};

// ---- cArgumentSpec (retail fields used here) ----
struct cArgumentSpec {
    char pad00[0x10];
    eastl::string8 mBriefDescription;   // +0x10
    eastl::string8 mFullDescription;    // +0x20
    VecArgInfo     mDefaultArguments;   // +0x30
    char pad40[0x4];                    // +0x40
    VecOptionsSpec mOptions;            // +0x44
    char pad54[0x4];                    // +0x54
    VecEnumSpec    mEnumSpecs;          // +0x58
    char pad68[0xb8 - 0x68];
    eastl::string8 mErrorString;        // +0xb8

    void NameFromArgType(int type, eastl::string8* out);                              // 0x008397a0
    void AddArgDocs(eastl::string8* out, VecArgInfo* args, int style);                // 0x00839c00
    void CreateHelpString(const char* name, eastl::string8* out, int style);          // 0x00839f90
    const char* HelpString(const char* name, int style);                              // 0x0083a2f0
};

void __cdecl SprintfAppend(eastl::string8* out, const char* fmt, ...);   // 0x00840c70
void __cdecl Sprintf(eastl::string8* out, const char* fmt, ...);         // 0x00840c20
void __cdecl AddDocString(eastl::string8* out, const char* prefix, eastl::string8 desc);  // 0x008392b0
void __cdecl AddEnumDocs(eastl::string8* out, const char* prefix, VecEnumSpec* enums, int style);  // 0x008393a0

// helpers for the 8/16-byte float vectors
struct E8 { float x, y; E8(const E8& o) { x = o.x; y = o.y; } };
E8* __cdecl UninitCopy8(E8* first, E8* last, E8* dest) throw();                      // 0x00838b90
struct V8 {
    E8* mpBegin; E8* mpEnd; E8* mpCapacity;
    void push_back(const E8& v);
    void DoInsertValue(E8* pos, const E8& v);
};

struct E16 { float x, y, z, w; E16(const E16& o) { x = o.x; y = o.y; z = o.z; w = o.w; } };
E16* __cdecl UninitCopy16(E16* first, E16* last, E16* dest) throw();                 // 0x00b115c0
E16* __cdecl CopyBackward16(E16* first, E16* last, E16* destEnd) throw();            // 0x00edba80
struct V16 {
    E16* mpBegin; E16* mpEnd; E16* mpCapacity;
    void push_back(const E16& v);
    void DoInsertValue(E16* pos, const E16& v);
};

cArgInfo* __cdecl CopyBackwardArg(cArgInfo* first, cArgInfo* last, cArgInfo* destEnd);  // 0x00838f80
cArgInfo* __cdecl UninitCopyArg(cArgInfo* first, cArgInfo* last, cArgInfo* dest);       // 0x00838c40
void      __cdecl UninitDestroyArg(cArgInfo* first, cArgInfo* last, cArgInfo* dest);    // 0x00838e80

// ===========================================================================
// 0x00839950  eastl::vector<cArgInfo>::vector(const vector&)  (copy ctor)
// ===========================================================================
// @ 0x00839950
VecArgInfo::VecArgInfo(const VecArgInfo& x) {
    DoAllocate((unsigned)(x.mpEnd - x.mpBegin), x.mAllocator);
    cArgInfo* pEnd = x.mpBegin;
    UninitCopyArgEH(&pEnd, x.mpBegin, x.mpEnd, mpBegin, &x);
    mpEnd = pEnd;
}

// ===========================================================================
// 0x008399d0  eastl::vector<8-byte float pair>::DoInsertValue(pos, v)
// ===========================================================================
// @ 0x008399d0
void V8::DoInsertValue(E8* pos, const E8& v) {
    if (mpEnd != mpCapacity) {
        const E8* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) E8(*(mpEnd - 1));
        E8* d = mpEnd;
        E8* s = mpEnd - 1;
        while (s != pos) { --s; --d; *d = *s; }
        *pos = *pv;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        E8* nb = n ? (E8*)EASTL_allocator_allocate(n * 8, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        E8* np = UninitCopy8(mpBegin, pos, nb);
        if (np) ::new((void*)np) E8(v);
        E8* ne = UninitCopy8(pos, mpEnd, np + 1);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = ne; mpCapacity = nb + n;
    }
}

// ===========================================================================
// 0x00839ae0  eastl::vector<16-byte float quad>::DoInsertValue(pos, v)
// ===========================================================================
// @ 0x00839ae0
void V16::DoInsertValue(E16* pos, const E16& v) {
    if (mpEnd != mpCapacity) {
        const E16* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) E16(*(mpEnd - 1));
        CopyBackward16(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        E16* nb = n ? (E16*)EASTL_allocator_allocate(n * 16, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        E16* beg = mpBegin;
        E16* np = UninitCopy16(beg, pos, nb);
        if (np) ::new((void*)np) E16(v);
        E16* end = mpEnd;
        ++np;
        np = UninitCopy16(pos, end, np);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = np; mpCapacity = nb + n;
    }
}

// ===========================================================================
// 0x00839c00  EA::ArgScript::cArgumentSpec::AddArgDocs
// ===========================================================================
// @ 0x00839c00
void cArgumentSpec::AddArgDocs(eastl::string8* out, VecArgInfo* args, int style) {
    int nDependents = 0;
    if (style == 2)
        out->append("<i>", "<i>" + 3);
    for (int i = 0; i < (int)(args->mpEnd - args->mpBegin); ++i) {
        cArgInfo* a = &args->mpBegin[i];
        if (i != 0)
            out->append(" ", " " + 1);
        if (!a->mIsDependent) {
            out->append("[", "[" + 1);
            ++nDependents;
        }
        if (style == 2)
            out->append("&lt;", "&lt;" + 4);
        else
            out->append("<", "<" + 1);
        if (a->mName.mpBegin != a->mName.mpEnd)
            SprintfAppend(out, "%s:", a->mName.mpBegin);
        NameFromArgType(a->mType, out);
        if (style == 2)
            out->append("&gt;", "&gt;" + 4);
        else
            out->append(">", ">" + 1);
        if (a->mType & 0x8000)
            out->append(" ...", " ..." + 4);
    }
    while (nDependents > 0) {
        out->append("]", "]" + 1);
        --nDependents;
    }
    if (style == 2)
        out->append("</i>", "</i>" + 4);
    out->append("\n", "\n" + 1);
}

// ===========================================================================
// 0x00839d80  eastl::vector<8-byte float pair>::push_back(v)
// ===========================================================================
// @ 0x00839d80
void V8::push_back(const E8& v) {
    if (mpEnd < mpCapacity) {
        ::new((void*)mpEnd++) E8(v);
    } else {
        DoInsertValue(mpEnd, v);
    }
}

// ===========================================================================
// 0x00839dc0  eastl::vector<16-byte float quad>::push_back(v)
// ===========================================================================
// @ 0x00839dc0
void V16::push_back(const E16& v) {
    if (mpEnd < mpCapacity) {
        ::new((void*)mpEnd++) E16(v);
    } else {
        DoInsertValue(mpEnd, v);
    }
}

// ===========================================================================
// 0x00839e00  EA::ArgScript::cOptionsSpec copy constructor
// ===========================================================================
// @ 0x00839e00
void __cdecl cOptionsSpec_CopyCtor(cOptionsSpec* self, const cOptionsSpec* x) {
    self->mName.mpBegin = 0;
    self->mName.mpEnd = 0;
    self->mName.mpCapacity = 0;
    int len = (int)(x->mName.mpEnd - x->mName.mpBegin);
    self->mName.RangeInitialize((unsigned)(len + 1));
    memcpy(self->mName.mpBegin, x->mName.mpBegin, (unsigned)len);
    self->mName.mpEnd = self->mName.mpBegin + len;
    *self->mName.mpEnd = 0;

    self->mDescription.mpBegin = 0;
    self->mDescription.mpEnd = 0;
    self->mDescription.mpCapacity = 0;
    int len2 = (int)(x->mDescription.mpEnd - x->mDescription.mpBegin);
    self->mDescription.RangeInitialize((unsigned)(len2 + 1));
    memcpy(self->mDescription.mpBegin, x->mDescription.mpBegin, (unsigned)len2);
    self->mDescription.mpEnd = self->mDescription.mpBegin + len2;
    *self->mDescription.mpEnd = 0;

    new (&self->mArguments) VecArgInfo(x->mArguments);
    self->mFlagToSet = x->mFlagToSet;
}

// ===========================================================================
// 0x00839f90  EA::ArgScript::cArgumentSpec::CreateHelpString
// ===========================================================================
// @ 0x00839f90
void cArgumentSpec::CreateHelpString(const char* name, eastl::string8* out, int style) {
    if (style == 0) {
        Sprintf(out, "%s", mBriefDescription.mpBegin);
        return;
    }
    if (style == 2) {
        Sprintf(out, "<tr><td><a name=\"%s\"></a><b>%s</b> ", name, name);
    } else {
        const char* p = name;
        while (*p) ++p;
        out->assign(name, p);
        out->append(" ", " " + 1);
    }

    AddArgDocs(out, &mDefaultArguments, style);

    if (style == 2) {
        out->append("<br><blockquote><p>", "<br><blockquote><p>" + 18);
        AddDocString(out, "", mFullDescription);
        SprintfAppend(out, " Options:</p>");
    } else {
        AddDocString(out, "    ", mFullDescription);
        SprintfAppend(out, "\n    Options:\n");
    }

    int nOptions = (int)(mOptions.mpEnd - mOptions.mpBegin);
    for (int i = 0; i < nOptions; ++i) {
        cOptionsSpec* opt = &mOptions.mpBegin[i];
        if (style == 2)
            SprintfAppend(out, "<b>-%s</b> ", opt->mName.mpBegin);
        else
            SprintfAppend(out, "    -%s ", opt->mName.mpBegin);
        AddArgDocs(out, &opt->mArguments, style);
        if (style == 2) {
            out->append("<br><blockquote>", "<br><blockquote>" + 15);
            AddDocString(out, "", opt->mDescription);
            out->append("</blockquote>", "</blockquote>" + 13);
        } else {
            AddDocString(out, "        ", opt->mDescription);
        }
    }

    if (mEnumSpecs.mpBegin != mEnumSpecs.mpEnd) {
        if (style == 2)
            out->append("\n<p>Types:</p>", "\n<p>Types:</p>" + 14);
        AddEnumDocs(out, "    ", &mEnumSpecs, style);
    }
    if (style == 2)
        out->append("</blockquote></td></tr>", "</blockquote></td></tr>" + 21);
}

// ===========================================================================
// 0x0083a2f0  EA::ArgScript::cArgumentSpec::HelpString
// ===========================================================================
// @ 0x0083a2f0
const char* cArgumentSpec::HelpString(const char* name, int style) {
    CreateHelpString(name, &mErrorString, style);
    return mErrorString.mpBegin;
}

// ===========================================================================
// 0x0083a310  destroy range of cOptionsSpec (advance dest)
// ===========================================================================
// @ 0x0083a310
cOptionsSpec* __cdecl DestroyOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* result) {
    if (first != last) {
        do {
            cArgInfo* end = first->mArguments.mpEnd;
            for (cArgInfo* p = first->mArguments.mpBegin; p < end; ++p) {
                if ((p->mName.mpCapacity - p->mName.mpBegin) > 1 && p->mName.mpBegin)
                    EASTL_allocator_deallocate(p->mName.mpBegin);
            }
            if (first->mArguments.mpBegin && ((int*)first->mArguments.mpBegin)[-1])
                EASTL_allocator_deallocate(first->mArguments.mpBegin);
            if ((first->mDescription.mpCapacity - first->mDescription.mpBegin) > 1 && first->mDescription.mpBegin)
                EASTL_allocator_deallocate(first->mDescription.mpBegin);
            if ((first->mName.mpCapacity - first->mName.mpBegin) > 1 && first->mName.mpBegin)
                EASTL_allocator_deallocate(first->mName.mpBegin);
            ++first;
            ++result;
        } while (first != last);
        return result;
    }
    return result;
}

// ===========================================================================
// 0x0083a3c0  eastl::vector<cArgInfo>::DoInsertValue(pos, v)
// ===========================================================================
// @ 0x0083a3c0
void VecArgInfo::DoInsertValue(cArgInfo* pos, const cArgInfo& v) {
    if (mpEnd != mpCapacity) {
        const cArgInfo* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) cArgInfo(*(mpEnd - 1));
        CopyBackwardArg(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        cArgInfo* nb = n ? (cArgInfo*)EASTL_allocator_allocate(n * 0x20, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        cArgInfo* np = UninitCopyArg(mpBegin, pos, nb);
        UninitDestroyArg(mpBegin, pos, nb);
        if (np) ::new((void*)np) cArgInfo(v);
        cArgInfo* ne = UninitCopyArg(pos, mpEnd, np + 1);
        UninitDestroyArg(pos, mpEnd, np + 1);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = ne; mpCapacity = nb + n;
    }
}

// ===========================================================================
// 0x0083a580  eastl::vector<cEnumSpec>::DoInsertValue(pos, v)
// ===========================================================================
// @ 0x0083a580
void VecEnumSpec::DoInsertValue(cEnumSpec* pos, const cEnumSpec& v) {
    if (mpEnd != mpCapacity) {
        const cEnumSpec* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) cEnumSpec(*(mpEnd - 1));
        CopyBackwardEnum(pos, mpEnd - 1, mpEnd);
        if (pos != pv) pos->mName.assign(pv->mName.mpBegin, pv->mName.mpEnd);
        pos->mEnumInfo = pv->mEnumInfo;
        pos->mPad14 = pv->mPad14;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        cEnumSpec* nb = n ? (cEnumSpec*)EASTL_allocator_allocate(n * 0x18, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        cEnumSpec* np = UninitCopyEnum(mpBegin, pos, nb);
        UninitDestroyEnum(mpBegin, pos, nb);
        if (np) ::new((void*)np) cEnumSpec(v);
        cEnumSpec* ne = UninitCopyEnum(pos, mpEnd, np + 1);
        UninitDestroyEnum(pos, mpEnd, np + 1);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = ne; mpCapacity = nb + n;
    }
}

// ===========================================================================
// 0x0083a740  eastl::vector<cArgInfo>::operator=(const vector&)
// ===========================================================================
// @ 0x0083a740
VecArgInfo& VecArgInfo::operator=(const VecArgInfo& x) {
    if (&x != this) {
        unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCapacity - mpBegin)) {
            cArgInfo* p = DoAllocateCopy(n, x.mpBegin, x.mpEnd);
            FreeRange(mpBegin, mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
            mpBegin = p; mpEnd = p + n; mpCapacity = p + n;
        } else if (n > (unsigned)(mpEnd - mpBegin)) {
            unsigned m = (unsigned)(mpEnd - mpBegin);
            MoveArgRange(x.mpBegin, x.mpBegin + m, mpBegin);
            cArgInfo* tmp = 0;
            UninitCopyArgEH(&tmp, x.mpBegin + m, x.mpEnd, mpEnd, &x);
            mpEnd = mpBegin + n;
        } else {
            cArgInfo* q = MoveArgRange(x.mpBegin, x.mpEnd, mpBegin);
            FreeRange(q, mpEnd);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// ===========================================================================
// 0x0083a8b0  EA::ArgScript::cOptionsSpec::operator=
// ===========================================================================
// @ 0x0083a8b0
cOptionsSpec& cOptionsSpec::operator=(const cOptionsSpec& x) {
    if (this != &x)
        mName.assign(x.mName.mpBegin, x.mName.mpEnd);
    if (&mDescription != &x.mDescription)
        mDescription.assign(x.mDescription.mpBegin, x.mDescription.mpEnd);
    mArguments = x.mArguments;
    mFlagToSet = x.mFlagToSet;
    return *this;
}

// ===========================================================================
// 0x0083a900  eastl::copy_impl<...>::do_copy<cOptionsSpec*, cOptionsSpec*>
// ===========================================================================
// @ 0x0083a900
cOptionsSpec* __cdecl CopyOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* result) {
    if (first != last) {
        do {
            if (first != result)
                result->mName.assign(first->mName.mpBegin, first->mName.mpEnd);
            if (&first->mDescription != &result->mDescription)
                result->mDescription.assign(first->mDescription.mpBegin, first->mDescription.mpEnd);
            result->mArguments = first->mArguments;
            result->mFlagToSet = first->mFlagToSet;
            ++result, ++first;
        } while (first != last);
        return result;
    }
    return result;
}

// ===========================================================================
// 0x0083a970  eastl::copy_backward_impl<...>::do_copy<cOptionsSpec*, cOptionsSpec*>
// ===========================================================================
// @ 0x0083a970
cOptionsSpec* __cdecl CopyBackwardOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* resultEnd) {
    if (last != first) {
        do {
            last = (cOptionsSpec*)((char*)last - 0x38);
            resultEnd = (cOptionsSpec*)((char*)resultEnd - 0x38);
            if (last != resultEnd)
                resultEnd->mName.assign(last->mName.mpBegin, last->mName.mpEnd);
            if (&last->mDescription != &resultEnd->mDescription)
                resultEnd->mDescription.assign(last->mDescription.mpBegin, last->mDescription.mpEnd);
            resultEnd->mArguments = last->mArguments;
            resultEnd->mFlagToSet = last->mFlagToSet;
        } while (last != first);
        return resultEnd;
    }
    return resultEnd;
}
