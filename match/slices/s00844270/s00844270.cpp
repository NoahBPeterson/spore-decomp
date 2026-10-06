// Slice s00844270: EA::ArgScript parser internals (macros, if/define commands).
// Built /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

typedef unsigned int size_t_;
void* operator new(size_t_ n, const char* name, int flags, unsigned dbg, const char* file, int line);
void operator delete(void* p) throw();
inline void* operator new(size_t_, void* p) { return p; }
inline void operator delete(void*, void*) throw() {}
extern "C" int __cdecl isalpha(int);
extern "C" int __cdecl isdigit(int);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
extern char gEmptyStr[2];   // 0x01667bac: shared empty-string storage

inline unsigned CharStrlen(const char* p) {
    const char* pCurrent = p;
    while (*pCurrent++) {}
    return (unsigned)(pCurrent - p - 1);
}

static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

namespace eastl {
struct allocator { unsigned char pad[4]; };

// basic_string<char, allocator> (0x10)
struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    __forceinline string8(const char* b, const char* e) {
        unsigned n = e - b;
        unsigned cap = n + 1;
        char* d; char* c;
        if (cap > 1) {
            d = (char*)operator new(cap, "ArgScript", 0, 0, kAllocFile, 0xd1);
            c = d + cap;
        } else {
            d = gEmptyStr; c = gEmptyStr + 1;
        }
        mpBegin = d; mpCapacity = c;
        memcpy(d, b, n);
        mpEnd = d + n;
        *mpEnd = 0;
    }
    void RangeInitialize(unsigned n);                       // 0x00475ab0
    __forceinline string8(const string8& x) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        const char* e = x.mpEnd;
        const char* b = x.mpBegin;
        unsigned n = e - b;
        RangeInitialize(n + 1);
        char* d = mpBegin;
        memcpy(d, b, n);
        d = d + (e - b);
        mpEnd = d;
        *d = 0;
    }
    string8() { mpBegin = gEmptyStr; mpEnd = gEmptyStr; mpCapacity = gEmptyStr + 1; }
    ~string8() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete(mpBegin); }
    string8& append(const char* first, const char* last);   // 0x00455d60
    string8& assign(const char* first, const char* last);   // 0x00454cb0
    void push_back(char c);                                 // 0x005306c0
    int  compare(unsigned pos, unsigned n, const char* s);  // 0x008417c0
    unsigned find(char c, unsigned pos) const;              // 0x00607580
    unsigned size() const { return mpEnd - mpBegin; }
};

template <typename T>
struct vec {
    vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(T* pos, const T& v);   // out-of-line grow path
    void push_back(const T& v) {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;
    unsigned mExtra;   // retail sp_vector_allocator is 8 bytes
};
}  // namespace eastl

using eastl::string8;

namespace EA { namespace ArgScript {
struct cArguments {
    int NumArguments();                      // 0x00837f30
    const char* operator[](int i);           // 0x00837f20
    const char** MainArguments(int i);       // 0x00838320
    cArguments();                            // 0x00837ff0
    void SplitIntoArguments(const char* s);  // 0x008383c0
    unsigned char pad[0x44];
};

struct cError {
    cError(const char* fmt, ...);            // 0x0052df30
    const char* mMessage;
    unsigned char pad[12];
};

void MakeCaseInsensitive(const char* s, string8* out);   // 0x00840cc0 (cdecl)

struct cMacroLine { int offset; int line; };

// retail layout (0x94 bytes)
struct cMacroDefinition {
    int mRefCount;                    // +0x00
    string8 mName;                    // +0x04
    cArguments mParams;               // +0x14
    eastl::vec<char> mMacroText;      // +0x58
    eastl::vec<cMacroLine> mMacroBody;// +0x6c
    string8 mPath;                    // +0x80
    int mStartLine;                   // +0x90

    cMacroDefinition();               // 0x00844860
    ~cMacroDefinition();              // 0x00841fd0
};

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& r) {
        mpObject = r.mpObject;
        if (mpObject) ++mpObject->mRefCount;
    }
    void Release() {
        T* p = mpObject;
        if (p) {
            if (p->mRefCount == 1) { p->~T(); operator delete(p); }
            else --p->mRefCount;
        }
    }
    ~AutoRefCount() { Release(); }
};

struct cICommand {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void EndBlock(bool b);   // +0x14
    virtual void EndMeta(bool b);    // +0x18
};
struct cIParser {
    virtual void v0();
};
}}  // namespace EA::ArgScript

using namespace EA::ArgScript;

// vector<bool, fixed_vector_allocator<1,16,1,0,1>> as used here: byte elements.
struct BoolVec {
    bool* mpBegin;
    bool* mpEnd;
    bool* mpCapacity;
    void DoInsertValue(bool* pos, const bool* v);   // 0x00843bc0
    void push_back(bool v) {
        bool* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(p, &v);
        }
    }
};

// ---------------------------------------------------------------------------
// SubstituteParameters (0x00844270)
// ---------------------------------------------------------------------------
namespace {
void SubstituteParameters(cArguments* params, cArguments* values, string8* text)
{
    unsigned size = text->size();
    if (size == 0) return;
    // find first '&'
    const char* p = text->mpBegin;
    while (p != text->mpEnd && *p != '&') ++p;
    if (p == text->mpEnd) return;
    unsigned amp = p - text->mpBegin;
    if (amp == (unsigned)-1) return;

    string8 result;
    unsigned start = 0;
    do {
        unsigned total = text->size() - start;
        unsigned len = amp - start;
        const char* b = text->mpBegin;
        result.append(b + start, b + start + (total < len ? total : len));
        if (amp == (unsigned)-1) break;
        ++amp;
        bool brace = text->mpBegin[amp] == '{';
        if (brace) ++amp;
        if (amp >= text->size()) throw cError("missing parameter name");
        unsigned char c = text->mpBegin[amp];
        if (!(isalpha(c) || isdigit(c) || c == '_') || isdigit((unsigned char)text->mpBegin[amp]))
            throw cError("bad parameter name");
        start = amp + 1;
        while (start < text->size()) {
            unsigned char d = text->mpBegin[start];
            if (!(isalpha(d) || isdigit(d) || d == '_')) break;
            ++start;
        }
        if (brace && (start >= text->size() || text->mpBegin[start] != '}'))
            throw cError("missing '}'");
        int i = 0;
        if (params->NumArguments() > 0) {
            unsigned nameLen = start - amp;
            do {
                if (text->compare(amp, nameLen, (*params)[i]) == 0) {
                    if (!brace) result.push_back('(');
                    const char* v = (*values)[i];
                    const char* e = v + CharStrlen(v);
                    result.append(v, e);
                    if (!brace) result.push_back(')');
                    break;
                }
                ++i;
            } while (i < params->NumArguments());
        }
        if (i == params->NumArguments()) {
            string8 msg;
            msg.append("Unknown parameter: ", "Unknown parameter: " + 19);
            unsigned total = text->size() - amp;
            unsigned len = start - amp;
            msg.append(text->mpBegin + amp, text->mpBegin + amp + (total < len ? total : len));
            throw cError(msg.mpBegin);
        }
        if (brace) ++start;
        amp = text->find('&', start);
    } while (start < text->size());

    if (&result != text) text->assign(result.mpBegin, result.mpEnd);
}
}  // namespace

// ---------------------------------------------------------------------------
// eastl::pair<const string, AutoRefCount<cMacroDefinition>> dtor (0x00844680)
// ---------------------------------------------------------------------------
struct MacroPair {
    string8 first;
    AutoRefCount<cMacroDefinition> second;
    MacroPair(const string8& k, const AutoRefCount<cMacroDefinition>& v) : first(k), second(v) {}   // 0x00844a00
    MacroPair(const MacroPair& o) : first(o.first), second(o.second) {}                            // 0x00844a60
    ~MacroPair() {}
};
// @ 0x00844680
void __fastcall MacroPair_dtor(MacroPair* p) { p->~MacroPair(); }

// ---------------------------------------------------------------------------
// hashtable<string, pair<const string, string>>::DoFreeNodes (0x00844700)
// ---------------------------------------------------------------------------
struct StrNode {
    string8 key;
    string8 value;
    StrNode* mpNext;
};
struct StrHashtable {
    void DoFreeNodes(StrNode** pNodeArray, unsigned n);
};
// @ 0x00844700
void StrHashtable::DoFreeNodes(StrNode** pNodeArray, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        StrNode* pNode = pNodeArray[i];
        while (pNode) {
            StrNode* pTemp = pNode;
            pNode = pNode->mpNext;
            pTemp->~StrNode();
            operator delete(pTemp);
        }
        pNodeArray[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// Commands
// ---------------------------------------------------------------------------
struct cParserIface {
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
    virtual void ParseLine(const char* line);   // +0x40
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void ExpectEnd(void* cmd, const char* endName);   // +0x90
    virtual bool EvalCondition(const char* expr);   // +0x94
};

struct cMetaCommandBase {
    virtual void m0();
    cParserIface* mParser;   // +4
    int mRefCount;           // +8
    virtual ~cMetaCommandBase();     // 0x0083c7c0
};

// cParser (retail offsets)
struct cParser : cParserIface {
    unsigned char pad0[0x6c - 4];
    unsigned char mMacroDefinitions[0x20];   // +0x6c hashtable (bucketArray +0x70, bucketCount +0x74)
    unsigned char pad1[0xe0 - 0x8c];
    string8 mCurrentPath;                    // +0xe0
    int mCurrentLine;                        // +0xf0
    unsigned char pad2[0x104 - 0xf4];
    int mBlockCommentDepth;                      // +0x104
    eastl::vec<cICommand*> mBlockCommandStack;   // +0x108
    struct cMetaEntry {
        cICommand* mCommand; int mLine;
        cMetaEntry(cICommand* c, int l) : mCommand(c), mLine(l) {}
        cMetaEntry(const cMetaEntry& o) : mCommand(o.mCommand), mLine(o.mLine) {}
    };
    eastl::vec<cMetaEntry> mMetaCommandStack;    // +0x11c
    string8 mScope;                              // +0x130
    eastl::vec<int> mScopeOffsets;               // +0x140
    unsigned char pad5[0x1b0 - 0x150];
    string8 mLCName;                             // +0x1b0

    int ParseEnd(bool bUnwind);                  // 0x00844ec0
    void InstantiateMacro(const char* name, cArguments* args);   // 0x00844fb0
    void PushScope(const char* name);            // 0x00845260
    void PushMeta(cICommand* c, int line);       // 0x00845320
};

struct MacroNode {
    string8 key;
    AutoRefCount<cMacroDefinition> value;
    MacroNode* mpNext;
};
struct MacroIter { MacroNode* node; MacroNode** bucket; };
struct MacroTable {
    unsigned char pad[4];
    MacroNode** mpBucketArray;   // +4
    unsigned mnBucketCount;      // +8
    MacroIter find(const string8& key);   // 0x007e2ea0
};
inline MacroTable* MacroTableOf(cParser* p) { return (MacroTable*)((char*)p + 0x6c); }

namespace {
struct cIfCommand : cMetaCommandBase {
    unsigned char pad[0x10 - 0xc];
    BoolVec mConditions;      // +0x10
    unsigned char pad2[0x38 - 0x1c];
    BoolVec mTaken;           // +0x38
    // @ 0x00844780
    virtual void Execute(cArguments& args);
};
void cIfCommand::Execute(cArguments& args)
{
    mParser->ExpectEnd(this, "endif");
    bool value = mParser->EvalCondition(*args.MainArguments(1));
    bool parentActive = mConditions.mpBegin == mConditions.mpEnd || mConditions.mpEnd[-1] != 0;
    mConditions.push_back(value && parentActive);
    mTaken.push_back(value || !parentActive);
}
}

// @ 0x00844860
cMacroDefinition::cMacroDefinition()
{
    mRefCount = 0;
    mStartLine = -1;
}

// @ 0x00844a00
MacroPair* __fastcall MacroPair_ctor_kv(MacroPair* mem, int, const string8& k, const AutoRefCount<cMacroDefinition>& v)
{
    return new (mem) MacroPair(k, v);
}
// @ 0x00844a60
MacroPair* __fastcall MacroPair_ctor_copy(MacroPair* mem, int, const MacroPair& o)
{
    return new (mem) MacroPair(o);
}

// @ 0x00844ac0: basic_string::insert(pos, first, last) (range)
namespace eastl {
struct false_type_ { false_type_() {} };
struct string_insert {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void insert(char* p, const char* first, const char* last, const struct false_type_&);
};
void string_insert::insert(char* p, const char* first, const char* last, const false_type_&)
{
    if (first == last) return;
    unsigned n = last - first;
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        unsigned nElementsAfter = mpEnd - p;
        char* pOldEnd = mpEnd;
        if (nElementsAfter > n) {
            char* pMoveSrc = pOldEnd - n;
            memcpy(pOldEnd, pMoveSrc, n);          // uninitialized_copy tail
            mpEnd += n;
            memmove(p + n, p, pMoveSrc - p);
            memmove(p, first, n);
        } else {
            const char* pMid = first + nElementsAfter;
            memcpy(pOldEnd, pMid, last - pMid);
            mpEnd += n - nElementsAfter;
            memcpy(mpEnd, p, nElementsAfter);
            mpEnd += nElementsAfter;
            memmove(p, first, pMid - first);
        }
    } else {
        unsigned nPrevSize = mpEnd - mpBegin;
        unsigned nNewCap = nPrevSize ? nPrevSize * 2 : 1;
        if (nNewCap < nPrevSize + n) nNewCap = nPrevSize + n;
        char* pNew = nNewCap ? (char*)operator new(nNewCap, "ArgScript", 0, 0, kAllocFile, 0xd1) : 0;
        unsigned nBefore = p - mpBegin;
        char* q = pNew;
        memcpy(q, mpBegin, nBefore);
        q += nBefore;
        memcpy(q, first, n);
        q += n;
        unsigned nAfter = mpEnd - p;
        memcpy(q, p, nAfter);
        q += nAfter;
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin);
        mpBegin = pNew;
        mpEnd = q;
        mpCapacity = pNew + nNewCap;
    }
}
}

// ---------------------------------------------------------------------------
// cDefineCommand
// ---------------------------------------------------------------------------
namespace {
struct cDefineCommand : cMetaCommandBase {
    cParser* mFullParser;                      // +0xc
    AutoRefCount<cMacroDefinition> mpMacro;    // +0x10
    // @ 0x00844c40
    virtual void Execute(cArguments& args);
    // @ 0x00844e50: destructor body
};

void cDefineCommand::Execute(cArguments& args)
{
    const char** a = args.MainArguments(2);
    const char* name = a[0];
    const char* nameEnd = name + CharStrlen(name);
    MacroIter it;
    {
        string8 key(name, nameEnd);
        it = MacroTableOf(mFullParser)->find(key);
    }
    MacroTable* t = MacroTableOf(mFullParser);
    if (it.node != (MacroNode*)t->mpBucketArray[t->mnBucketCount])
        throw cError("Already defined");
    mParser->ExpectEnd(this, "enddef");
    cMacroDefinition* m = new ("ArgScript", 0, 0, 0, 0) cMacroDefinition;
    cMacroDefinition* old = mpMacro.mpObject;
    if (m != old) {
        if (m) ++m->mRefCount;
        mpMacro.mpObject = m;
        if (old) {
            if (old->mRefCount == 1) { old->~cMacroDefinition(); operator delete(old); }
            else --old->mRefCount;
        }
    }
    const char* s = a[0];
    const char* e = s + CharStrlen(s);
    mpMacro.mpObject->mName.assign(s, e);
    mpMacro.mpObject->mParams.SplitIntoArguments(a[1]);
    string8* cur = &mFullParser->mCurrentPath;
    if (cur != &mpMacro.mpObject->mPath)
        mpMacro.mpObject->mPath.assign(cur->mpBegin, cur->mpEnd);
    mpMacro.mpObject->mStartLine = mFullParser->mCurrentLine;
}
// @ 0x00844e50
void __fastcall cDefineCommand_dtor(cDefineCommand* p) { p->cDefineCommand::~cDefineCommand(); }
}  // namespace

// ---------------------------------------------------------------------------
// cParser methods
// ---------------------------------------------------------------------------
// @ 0x00844ec0
int cParser::ParseEnd(bool bUnwind)
{
    if (bUnwind) {
        while (mMetaCommandStack.mpBegin != mMetaCommandStack.mpEnd) {
            mMetaCommandStack.mpEnd[-1].mCommand->EndMeta(bUnwind);
            mMetaCommandStack.mpEnd -= 1;
        }
        while (mBlockCommandStack.mpBegin != mBlockCommandStack.mpEnd) {
            mBlockCommandStack.mpEnd[-1]->EndBlock(bUnwind);
            mBlockCommandStack.mpEnd -= 1;
        }
    }
    if (mScope.mpBegin != mScope.mpEnd) {
        *mScope.mpBegin = 0;
        mScope.mpEnd = mScope.mpBegin;
    }
    int* last = mScopeOffsets.mpEnd;
    int* first = mScopeOffsets.mpBegin;
    memcpy(first, last, (char*)mScopeOffsets.mpEnd - (char*)last);
    mScopeOffsets.mpEnd += -(last - first);
    int r = *(int*)((char*)this + 0x168);   // value left in eax by the original (mArgs storage field)
    mBlockCommentDepth = 0;
    return r;
}

// @ 0x00844fb0
void cParser::InstantiateMacro(const char* name, cArguments* args)
{
    MakeCaseInsensitive(name, &mLCName);
    const char* nameEnd = name + CharStrlen(name);
    MacroTable* t = MacroTableOf(this);
    MacroIter it;
    {
        string8 key(name, nameEnd);
        it = t->find(key);
    }
    if (it.node == (MacroNode*)t->mpBucketArray[t->mnBucketCount])
        throw cError("Unknown definition: '%s'", name);
    cMacroDefinition* m = it.node->value.mpObject;
    if (m->mParams.NumArguments() != args->NumArguments())
        throw cError("Wrong number of arguments");
    string8 line;
    cMacroLine* end = m->mMacroBody.mpEnd;
    for (cMacroLine* p = m->mMacroBody.mpBegin; p != end; ++p) {
        int lineNo = p->line;
        int relLine = lineNo - m->mStartLine;
        const char* s = m->mMacroText.mpBegin + p->offset;
        const char* e = s + CharStrlen(s);
        line.assign(s, e);
        SubstituteParameters(&m->mParams, args, &line);
        if (m->mStartLine) {
            if (&m->mPath != &mCurrentPath)
                mCurrentPath.assign(m->mPath.mpBegin, m->mPath.mpEnd);
            mCurrentLine = lineNo;
        }
        try {
            ParseLine(line.mpBegin);
        } catch (cError& err) {
            if (m->mStartLine)
                throw cError("\n%s(%d): %s\n      in definition '%s', line %d",
                             m->mPath.mpBegin, lineNo, err.mMessage, name, relLine);
            throw cError("%s\n  in definition '%s', line %d", err.mMessage, name, relLine);
        }
    }
}

// @ 0x00845260: push a scope name onto the scope string
void cParser::PushScope(const char* name)
{
    int offset = mScope.mpEnd - mScope.mpBegin;
    mScopeOffsets.push_back(offset);
    const char* e = name + CharStrlen(name);
    mScope.append(name, e);
    mScope.append(":", ":" + 1);
}

// @ 0x00845320
void cParser::PushMeta(cICommand* c, int line)
{
    mMetaCommandStack.push_back(cMetaEntry(c, line));
}
