// Slice s00843650 (batch gold3).
// EA::ArgScript parser, part 2 (UTFSpore_Win32/Parser.obj): SubstituteVariables, CommandLookup,
// the macro-definition hashtable insert path, the fixed_vector inserts, the include commands,
// cIfCommand::Parse and cParser::ParseCommand.
// Built /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int uint32;

void* operator new(unsigned int n, const char* pName, int a, int b, const char* pFile, int line);
void operator delete(void* p) throw();
inline void* operator new(unsigned int, void*) throw() { return 0; }
inline void operator delete(void*, void*) throw() {}
extern "C" __declspec(dllimport) int  __cdecl isalpha(int);
extern "C" __declspec(dllimport) int  __cdecl isdigit(int);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) int  __cdecl _stat64i32(const char*, void*);

// 0x011e0744: out-of-line byte copy used by string8 and the vectors (returns dst).
extern "C" void* __cdecl CopyBytes(void* dst, const void* src, unsigned int n);
void* __cdecl EAAllocate(uint32 n, const char* pName, int a, int b,
                         const char* pFile, int line);                    // 0x00f473a0
void  __cdecl SP_cError(void* pBuf, const char* fmt, ...);                // 0x0052df30
__declspec(noreturn) void __cdecl ThrowException(void* pObj, void* pThrowInfo);   // 0x011e0912
void __cdecl MakeCaseInsensitiveChars(const char* pName, void* pTable);   // 0x00840cc0
void __cdecl Sprintf(void* out, const char* fmt, ...);                    // 0x00840c20
bool __cdecl StripCommentsAndWhiteSpace(char* pText, void* pOut, int* pDepth);  // 0x00840ec0

extern char gEmptyA[1];       // 0x01667bac: the shared empty string
extern char gEmptyB[1];       // 0x01667bad
extern char gThrowInfo;       // 0x014f9174

static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

inline unsigned CharStrlen(const char* p)
{
    const char* pBase = p + 1;
    while (*p++) {}
    return (unsigned)(p - pBase);
}

// ---------------------------------------------------------------------------------------------
// eastl containers
// ---------------------------------------------------------------------------------------------
namespace eastl {

struct allocator_s0084_3650 { unsigned char pad[4]; };

// basic_string<char, allocator> (0x10 bytes)
struct string8_s0084_3650 {
    char* mpBegin;                     // +0x00
    char* mpEnd;                       // +0x04
    char* mpCapacity;                  // +0x08
    allocator_s0084_3650 mAllocator;   // +0x0c

    string8_s0084_3650() { mpBegin = gEmptyA; mpEnd = gEmptyA; mpCapacity = gEmptyA + 1; }
    string8_s0084_3650(const char* p) {
        unsigned n = (unsigned)(CharStrlen(p));
        if (n + 1 > 1) {
            mpBegin = (char*)EAAllocate(n + 1, "ArgScript", 0, 0, kAllocFile, 0xd1);
            mpCapacity = mpBegin + n + 1;
        } else {
            mpBegin = gEmptyA;
            mpCapacity = gEmptyA + 1;
        }
        if (n) CopyBytes(mpBegin, p, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~string8_s0084_3650() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin);
    }
    string8_s0084_3650& append(const char* first, const char* last);   // 0x00455d60
    string8_s0084_3650& assign(const char* first, const char* last);   // 0x00454cb0
    int  compare(unsigned pos, unsigned n, const char* s) const;       // 0x008417c0
    int  find(const char* pStr, unsigned pos) const;                   // 0x00841d00
    void clearContents();                                              // 0x00478930
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

// element-wise string equality: 0x00554fb0 is eastl::operator==<char>(const string8*, const string8*)
bool operator==(const string8_s0084_3650& a, const string8_s0084_3650& b);
// 0x00555020: eastl::operator==<char>(const string8*, const char*)
bool operator==(const string8_s0084_3650& a, const char* pB);

// "vector<bool, fixed_vector_allocator<1,16,1,0,1>>": one byte per element, inline buffer at +0x18.
struct bool_vec_s0084_3650 {
    bool* mpBegin;      // +0x00
    bool* mpEnd;        // +0x04
    bool* mpCapacity;   // +0x08
    unsigned mPad0c;    // +0x0c
    bool* mpBuffer;     // +0x10
    unsigned mPad14;    // +0x14
    bool mStorage[16];  // +0x18

    void push_back(const bool* pValue);    // 0x00843bc0 (pos, value)
};

// vec<T, sp_vector_allocator>: 8-byte allocator, object is 0x14; heap blocks carry a size prefix.
// (0x00843ab0 is the void* instantiation used by cParser::mBlockCommandStack.)
struct VecPtr_s0084_3650 {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned mAllocator[2];

    void** DoInsertValue(void** pos, void** const* pValue);   // 0x00843ab0
};

template <typename T>
struct vec_s0084_3650 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned mAllocator[2];
};

// hashtable node: string8 key, the 8-byte mapped value, the cached hash and the chain link.
struct HashNode_s0084_3650 {
    string8_s0084_3650 key;         // +0x00
    void* mpValue;                  // +0x10
    void* mpValue2;                 // +0x14
    unsigned mPad18;                // +0x18
    unsigned mHash;                 // +0x1c
    HashNode_s0084_3650* mpNext;    // +0x20
};

struct FindResult_s0084_3650 {
    HashNode_s0084_3650* mpNode;        // +0x00
    HashNode_s0084_3650** mppBucket;    // +0x04

    FindResult_s0084_3650() {}
    FindResult_s0084_3650(const FindResult_s0084_3650& r)
        : mpNode(r.mpNode), mppBucket(r.mppBucket) {}
};

// insert()'s three-word result: node, bucket slot, and whether the node was created.
struct InsertResult_s0084_3650 {
    HashNode_s0084_3650* mpNode;        // +0x00
    HashNode_s0084_3650** mppBucket;    // +0x04
    bool mbInserted;                    // +0x08

    InsertResult_s0084_3650() {}
    InsertResult_s0084_3650(const InsertResult_s0084_3650& r)
        : mpNode(r.mpNode), mppBucket(r.mppBucket), mbInserted(r.mbInserted) {}
};

// The prime_rehash_policy result handed back by the growth helper (0x00921440).
struct RehashLocal_s0084_3650 {
    bool mbGrown;            // +0x00
    unsigned mnNewCount;     // +0x04
};

// Bucket table shared by every hashtable in this object: array at +0x04, count at +0x08.
struct HashTable_s0084_3650 {
    unsigned mPad00;                       // +0x00
    HashNode_s0084_3650** mpBucketArray;   // +0x04
    unsigned mnBucketCount;                // +0x08
    unsigned mnNodeCount;                  // +0x0c
    unsigned char mPad10[0x10];            // +0x10 (the allocator)

    FindResult_s0084_3650 find(const string8_s0084_3650* pKey) const;              // 0x007e2ea0
    InsertResult_s0084_3650 insert(const string8_s0084_3650* pKey,
                                   RehashLocal_s0084_3650* pRehash);               // 0x008439b0
};

// 0x00842830: construct a node for the key (malloc from the pool + copy the key).
void* __fastcall ConstructMacroNode(void* pTable, int, const string8_s0084_3650* pKey);
// 0x00921440: the rehash policy's grow helper.
void __fastcall GrowMacroTable(void* pAllocator, int, RehashLocal_s0084_3650* pOut,
                               unsigned nBucketCount, unsigned nNodeCount, int bOne);
// 0x00841e30: free the old bucket array after a rehash (this, count).
void __fastcall FreeMacroBuckets(void* pTable, int, unsigned nCount);

}  // namespace eastl

using eastl::string8_s0084_3650;
typedef string8_s0084_3650 string8;

// ---------------------------------------------------------------------------------------------
// EA::ArgScript
// ---------------------------------------------------------------------------------------------
namespace EA {
namespace ArgScript {

class cError { public:
    cError(const char* fmt, ...);   // 0x0052df30
    const char* mMessage;
    unsigned char pad[12];
};

struct cArguments_s0084_3650 {
    void SplitIntoArguments(const char* pText);   // 0x008383c0
    const char** MainArguments(int index);        // 0x00838320
    int NumArguments();                           // 0x00837f30
    const char* operator[](int index);            // 0x00837f20
    void Advance();                               // 0x00837ed0
    void FindUnprocessed();                       // 0x00837f40
    unsigned char pad[0x44];
};

struct cParser_s0084_3650;

// The parser interface as seen by the commands (slots used here: +0x38 and +0x94).
struct cIParser_s0084_3650 {
    virtual void s00();  virtual void s01();  virtual void s02();  virtual void s03();
    virtual void s04();  virtual void s05();  virtual void s06();  virtual void s07();
    virtual void s08();  virtual void s09();  virtual void s10();  virtual void s11();
    virtual void s12();  virtual void s13();
    virtual void RunFile(const char* pPath);      // +0x38
};
struct cIParser2_s0084_3650 {                      // the same object, its +0x94 slot
    virtual void s00();  virtual void s01();  virtual void s02();  virtual void s03();
    virtual void s04();  virtual void s05();  virtual void s06();  virtual void s07();
    virtual void s08();  virtual void s09();  virtual void s10();  virtual void s11();
    virtual void s12();  virtual void s13();  virtual void s14();  virtual void s15();
    virtual void s16();  virtual void s17();  virtual void s18();  virtual void s19();
    virtual void s20();  virtual void s21();  virtual void s22();  virtual void s23();
    virtual void s24();  virtual void s25();  virtual void s26();  virtual void s27();
    virtual void s28();  virtual void s29();  virtual void s30();  virtual void s31();
    virtual void s32();  virtual void s33();  virtual void s34();  virtual void s35();
    virtual void s36();
    virtual bool EvalCondition(const char* pExpr);  // +0x94
};

// The same object seen through its variable-lookup slot (+0x70).
struct cIParserExpr_s0084_3650 {
    virtual void s00();  virtual void s01();  virtual void s02();  virtual void s03();
    virtual void s04();  virtual void s05();  virtual void s06();  virtual void s07();
    virtual void s08();  virtual void s09();  virtual void s10();  virtual void s11();
    virtual void s12();  virtual void s13();  virtual void s14();  virtual void s15();
    virtual void s16();  virtual void s17();  virtual void s18();  virtual void s19();
    virtual void s20();  virtual void s21();  virtual void s22();  virtual void s23();
    virtual void s24();  virtual void s25();  virtual void s26();  virtual void s27();
    virtual const char* LookupVariable(const char* pName);   // +0x70
};

struct cICommand_s0084_3650 {
    virtual void Execute(cArguments_s0084_3650* pArgs);     // +0x00
    virtual void Description(int helpType);                 // +0x04
    virtual void OnRegister(void* pParser, void* pState);   // +0x08
    virtual int  AddRef();                                  // +0x0c
    virtual int  Release();                                 // +0x10
    virtual bool Parse(const string8_s0084_3650& line);     // +0x14
    virtual void EndMeta(bool bFlag);                       // +0x18
    virtual bool MatchName(const char* pName);              // +0x1c
};

// 8-byte entry pushed on cParser::mMetaCommandStack.
struct cMetaEntry_s0084_3650 {
    cICommand_s0084_3650* mCommand;         // +0x00
    const string8_s0084_3650* mpEndToken;   // +0x04
};

// vec<cMetaEntry, sp_vector_allocator>
struct cMetaStack_s0084_3650 {
    cMetaEntry_s0084_3650* mpBegin;      // +0x00
    cMetaEntry_s0084_3650* mpEnd;        // +0x04
    cMetaEntry_s0084_3650* mpCapacity;   // +0x08
    unsigned mAllocator[2];              // +0x0c
};

// The state object hanging off a command: its current-directory string sits at +0xd0.
struct cState_s0084_3650 {
    unsigned char mPad0[0xd0];
    string8_s0084_3650 mCurrentDir;    // +0xd0
};

// The cICommand layout with the fields these command classes share:
// vptr(+0) / parser(+4) / refcount(+8).
struct cCommandBase_s0084_3650 {
    virtual void Execute(cArguments_s0084_3650* pArgs);     // +0x00
    virtual void Description(int helpType);                 // +0x04
    virtual void OnRegister(void* pParser, void* pState);   // +0x08
    virtual int  AddRef();                                  // +0x0c
    virtual int  Release();                                 // +0x10
    virtual bool Parse(const string8_s0084_3650& line);     // +0x14
    virtual void EndMeta(bool bFlag);                       // +0x18
    virtual bool MatchName(const char* pName);              // +0x1c

    cIParser_s0084_3650* mParser;      // +0x04
    int mRefCount;                     // +0x08
};

// Commands that run a script file (state pointer at +0x0c).
struct cIncludeCommand_s0084_3650 : cCommandBase_s0084_3650 {
    cState_s0084_3650* mState;         // +0x0c

    void ExecuteBody(cArguments_s0084_3650* pArgs);      // 0x00843cc0
};

struct cIncludeIfExistsCommand_s0084_3650 : cCommandBase_s0084_3650 {
    cState_s0084_3650* mState;         // +0x0c

    void ExecuteBody(cArguments_s0084_3650* pArgs);      // 0x00843e50
};

// The if meta-command: two byte-flag vectors then the condition arguments.
struct cIfCommand_s0084_3650 : cCommandBase_s0084_3650 {
    cParser_s0084_3650* mFullParser;           // +0x0c
    eastl::bool_vec_s0084_3650 mTakenVector;   // +0x10 (mpEnd at +0x14)
    eastl::bool_vec_s0084_3650 mCondVector;    // +0x38 (mpEnd at +0x3c)
    cArguments_s0084_3650 mArgs;               // +0x60

    bool ParseBody(const string8_s0084_3650& line);   // 0x00843ff0
};

struct CmdNode_s0084_3650 {
    unsigned char mPad0[0x10];
    void* mpValue;                     // +0x10
};

// mCommands: bucket array at +0x04, bucket count at +0x08, keyed on a case-insensitive string.
struct CmdTable_s0084_3650 {
    unsigned mPad00;                          // +0x00
    CmdNode_s0084_3650** mpBucketArray;       // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned char mPad0c[0x20 - 0x0c];        // +0x0c

    eastl::FindResult_s0084_3650 find(const string8_s0084_3650* pKey) const;   // 0x007e2ea0
};

}  // namespace ArgScript
}  // namespace EA

typedef EA::ArgScript::cICommand_s0084_3650       cICommand;
typedef EA::ArgScript::cArguments_s0084_3650      cArguments;
typedef EA::ArgScript::cState_s0084_3650          cState;

// The parser proper (retail offsets; only the members touched here are named).
struct EA::ArgScript::cParser_s0084_3650 {
    virtual void v00();                                     // vptr at +0x00
    unsigned char mPad0004[0x100];
    int mBlockCommentDepth;                                 // +0x104
    eastl::vec_s0084_3650<void*> mBlockCommandStack;        // +0x108
    EA::ArgScript::cMetaStack_s0084_3650 mMetaCommandStack; // +0x11c
    string8_s0084_3650 mScope;                              // +0x130
    eastl::vec_s0084_3650<int> mScopeOffsets;               // +0x140
    string8_s0084_3650 mLastError;                          // +0x154
    unsigned mPad164;                                       // +0x164
    int mNesting;                                           // +0x168
    cArguments mArgs;                                       // +0x16c
    char mLCNameStorage[0x1c];                              // +0x1b0 (case-insensitive command name)

    void SubstituteVariables(string8_s0084_3650* pLine, int bFlag);   // 0x00843650
    cICommand_s0084_3650* CommandLookup(const char* pName);           // 0x00843920
    void ParseCommand(const char* pText);                             // 0x008440d0
};

// The hash table the parser builds from its case-insensitive member name (offset +0x2c).
inline EA::ArgScript::CmdTable_s0084_3650* CmdTableOf(void* p)
{
    return (EA::ArgScript::CmdTable_s0084_3650*)((char*)p + 0x2c);
}

// ---------------------------------------------------------------------------------------------
// 0x00843650 cParser::SubstituteVariables -- expand $var / ${var} references in place
// ---------------------------------------------------------------------------------------------
// @ 0x00843650
void EA::ArgScript::cParser_s0084_3650::SubstituteVariables(string8_s0084_3650* pLine, int bFlag)
{
    char* pText = pLine->mpBegin;
    unsigned total = (unsigned)(pLine->mpEnd - pText);
    if (total == 0)
        return;

    char* pDollar = pText;
    char* const pEnd = pText + total;
    while (pDollar != pEnd && *pDollar != '$')
        ++pDollar;
    unsigned start = (unsigned)(pDollar - pText);
    if (start == total)
        return;

    if (total > 0x7ff) {
        cError err("buffer overflow");
        ThrowException(&err, &gThrowInfo);
    }

    char buf[2048];
    CopyBytes(buf, pText, total + 1);
    pLine->clearContents();

    unsigned idx = 0;
    while (idx < total) {
        pLine->append(buf + idx, buf + idx + (start - idx));
        if (start == total)
            return;

        unsigned j = start + 1;
        bool bBrace = buf[j] == '{';
        if (bBrace)
            ++j;
        if (j >= total) {
            cError err("missing variable name");
            ThrowException(&err, &gThrowInfo);
        }
        char ch = buf[j];
        if (!(isalpha((int)ch) || isdigit((int)ch) || ch == '_' || ch == ':') ||
            isdigit((int)buf[j])) {
            cError err("bad variable name");
            ThrowException(&err, &gThrowInfo);
        }
        unsigned k = j + 1;
        while (k < total) {
            char d = buf[k];
            if (!(isalpha((int)d) || isdigit((int)d) || d == '_' || d == ':'))
                break;
            ++k;
        }
        if (bBrace && (k >= total || buf[k] != '}')) {
            cError err("missing '}'");
            ThrowException(&err, &gThrowInfo);
        }

        char saved = buf[k];
        buf[k] = 0;
        const char* pValue = ((cIParserExpr_s0084_3650*)this)->LookupVariable(buf + j);
        if (pValue == 0) {
            cError err("Unknown variable: '%s'", buf + j);
            ThrowException(&err, &gThrowInfo);
        }
        buf[k] = saved;

        if (!bBrace && bFlag != 0)
            pLine->append(gEmptyB, gEmptyB + 1);
        pLine->append(pValue, pValue + CharStrlen(pValue));
        if (bBrace)
            k = k + 1;
        else if (bFlag != 0)
            pLine->append(gEmptyA, gEmptyA + 1);

        char* pNext = buf + k;
        while (pNext != buf + total && *pNext != '$')
            ++pNext;
        start = (unsigned)(pNext - buf);
        if (k >= total)
            return;
        idx = k;
    }
}


// @ 0x00843bc0
void eastl::bool_vec_s0084_3650::push_back(const bool* pValue)
{
    bool* pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        const bool* pSource = pValue;
        if (pValue >= pEnd && pValue < mpCapacity)
            ++pSource;
        if (pEnd != 0)
            *pEnd = pEnd[-1];
        bool* pDst = pEnd - ((mpEnd - 1) - pEnd) - 1;
        ::memmove(pDst, pEnd, (unsigned)((mpEnd - 1) - pEnd));
        *pEnd = *pSource;
        ++mpEnd;
        return;
    }

    unsigned nPrev = (unsigned)(pEnd - mpBegin);
    unsigned nNew = nPrev != 0 ? nPrev * 2 : 1;
    bool* pNew = nNew != 0
        ? (bool*)EAAllocate(nNew, "ArgScript", 0, 0, kAllocFile, 0xd1)
        : 0;
    bool* pMid = pNew;
    if (pNew) {
        CopyBytes(pNew, mpBegin, (unsigned)(pValue - mpBegin));
        pMid = pNew + (pValue - mpBegin);
        *pMid = *pValue;
    }
    bool* pNewEnd = (bool*)CopyBytes(pMid + 1, pValue, (unsigned)(mpEnd - pValue));
    pNewEnd += (mpEnd - pValue);
    if (mpBegin != 0 && mpBegin != mpBuffer)
        ::operator delete(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCapacity = pNew + nNew;
}

// ---------------------------------------------------------------------------------------------
// 0x00843ab0 vec<cICommand*, sp_vector_allocator>::DoInsertValue
// ---------------------------------------------------------------------------------------------
// @ 0x00843ab0
void** eastl::VecPtr_s0084_3650::DoInsertValue(void** pos, void** const* pValue)
{
    void** pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        void** pSource = *pValue;
        if (*pValue >= pEnd && *pValue < mpCapacity)
            pSource = *pValue + 1;
        if (pEnd != 0)
            *pEnd = pEnd[-1];
        void** pDst = pEnd - 1;
        pDst = pDst - pDst + pos;
        unsigned n = (unsigned)((char*)(pEnd - 1) - (char*)pos);
        ::memmove(pDst, pos, n);
        *pos = *pSource;
        ++mpEnd;
        return pos;
    }

    unsigned nPrev = (unsigned)(pEnd - mpBegin);
    unsigned nNew;
    if (nPrev != 0) {
        nNew = nPrev * 2;
    } else {
        nNew = 1;
    }
    void** pNew = nNew != 0
        ? (void**)EAAllocate(nNew * 4, "ArgScript", 0, 0, kAllocFile, 0xd1)
        : 0;
    void** pMid = pNew;
    if (pNew) {
        CopyBytes(pNew, mpBegin, (unsigned)((char*)*pValue - (char*)mpBegin));
        pMid = pNew + (*pValue - mpBegin);
        *pMid = *pValue;
    }
    void** pNewEnd = (void**)CopyBytes(pMid + 1, *pValue, (unsigned)((char*)mpEnd - (char*)*pValue));
    pNewEnd += (mpEnd - *pValue);
    if (mpBegin != 0 && mpBegin[-1] != 0)
        ::operator delete(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCapacity = pNew + nNew;
    return pNew;
}

// ---------------------------------------------------------------------------------------------
// 0x008439b0 macro-definition hashtable: find-or-insert keyed on the case-insensitive name
// ---------------------------------------------------------------------------------------------
// @ 0x008439b0
eastl::InsertResult_s0084_3650
eastl::HashTable_s0084_3650::insert(const string8_s0084_3650* pKey,
                                    eastl::RehashLocal_s0084_3650* pRehash)
{
    unsigned hash = 0x811c9dc5;
    const unsigned char* p = (const unsigned char*)pKey->mpBegin;
    for (unsigned char c = *p; c != 0; c = *++p)
        hash = (hash * 0x1000193) ^ c;

    unsigned bucket = hash % mnBucketCount;
    HashNode_s0084_3650** ppBucket = mpBucketArray + bucket;
    HashNode_s0084_3650* pNode = *ppBucket;
    for (; pNode != 0; pNode = pNode->mpNext) {
        if (operator==(*pKey, pNode->key))
            return InsertResult_s0084_3650();
    }

    pRehash->mbGrown = false;
    unsigned nNewCount = 0;
    GrowMacroTable((char*)this + 0x10, 0, pRehash, mnBucketCount, mnNodeCount, 1);
    nNewCount = pRehash->mnNewCount;
    HashNode_s0084_3650* pNew = (HashNode_s0084_3650*)ConstructMacroNode(this, 0, pKey);
    if (pRehash->mbGrown)
        FreeMacroBuckets(this, 0, pRehash->mnNewCount);

    InsertResult_s0084_3650 result;
    result.mpNode = pNew;
    result.mppBucket = 0;
    (void)nNewCount;
    pNew->mpNext = mpBucketArray[bucket];
    mpBucketArray[bucket] = pNew;
    ++mnNodeCount;
    result.mppBucket = mpBucketArray + bucket;
    result.mbInserted = true;
    return result;
}

// ---------------------------------------------------------------------------------------------
// 0x00843920 cParser::CommandLookup
// ---------------------------------------------------------------------------------------------
// @ 0x00843920
cICommand* EA::ArgScript::cParser_s0084_3650::CommandLookup(const char* pName)
{
    char* pLCName = mLCNameStorage;
    MakeCaseInsensitiveChars(pName, pLCName);
    int i = (int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin) - 1;
    for (; i >= 0; --i) {
        cICommand* pCmd = (cICommand*)mBlockCommandStack.mpBegin[i];
        if (pCmd->MatchName(pLCName))
            return pCmd;
    }
    EA::ArgScript::CmdTable_s0084_3650* pTable = CmdTableOf(this);
    eastl::FindResult_s0084_3650 r = pTable->find((string8*)pLCName);
    if ((void*)r.mpNode != (void*)pTable->mpBucketArray[pTable->mnBucketCount])
        return (cICommand*)((EA::ArgScript::CmdNode_s0084_3650*)r.mpNode)->mpValue;
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00843cc0 include-style command: resolve the path, then ask the parser to run it
// ---------------------------------------------------------------------------------------------
// @ 0x00843cc0
void EA::ArgScript::cIncludeCommand_s0084_3650::ExecuteBody(cArguments_s0084_3650* pArgs)
{
    const char* const* pName = pArgs->MainArguments(1);
    string8 fileName(*pName);

    bool bRelative;
    if (fileName.size() >= 2 && fileName.mpBegin[1] == ':' && isalpha(fileName.mpBegin[0]))
        bRelative = false;
    else
        bRelative = fileName.find("\\", 0) != 0;

    if (bRelative)
        fileName.assign(mState->mCurrentDir.mpBegin, mState->mCurrentDir.mpEnd);

    fileName.append(*pName, *pName + CharStrlen(*pName));
    ((cIParser_s0084_3650*)mParser)->RunFile(fileName.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// 0x00843e50 include-if-exists command: as above, but only when stat() succeeds
// ---------------------------------------------------------------------------------------------
// @ 0x00843e50
void EA::ArgScript::cIncludeIfExistsCommand_s0084_3650::ExecuteBody(cArguments_s0084_3650* pArgs)
{
    const char* const* pName = pArgs->MainArguments(1);
    string8 fileName(*pName);

    bool bRelative;
    if (fileName.size() >= 2 && fileName.mpBegin[1] == ':' && isalpha(fileName.mpBegin[0]))
        bRelative = false;
    else
        bRelative = fileName.find("\\", 0) != 0;

    if (bRelative)
        fileName.assign(mState->mCurrentDir.mpBegin, mState->mCurrentDir.mpEnd);

    fileName.append(*pName, *pName + CharStrlen(*pName));
    char statBuf[0x30];
    if (_stat64i32(fileName.mpBegin, statBuf) == 0)
        ((cIParser_s0084_3650*)mParser)->RunFile(fileName.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// 0x00843ff0 cIfCommand::Parse -- consume an else/elseif continuation line
// ---------------------------------------------------------------------------------------------
// @ 0x00843ff0
bool EA::ArgScript::cIfCommand_s0084_3650::ParseBody(const string8_s0084_3650& line)
{
    if (line.compare(0, 2, "if") == 0)
        return false;

    if (eastl::operator==(line, "else")) {
        if (mCondVector.mpEnd[-1] == 0) {
            mTakenVector.mpEnd[-1] = 1;
            mCondVector.mpEnd[-1] = 1;
            return true;
        }
        mTakenVector.mpEnd[-1] = 0;
        return true;
    }

    if (line.compare(0, 6, "elseif") == 0) {
        if (mTakenVector.mpEnd[-1] != 0) {
            mTakenVector.mpEnd[-1] = 0;
            return true;
        }
        mFullParser->SubstituteVariables((string8_s0084_3650*)&line, 1);
        mArgs.SplitIntoArguments(line.mpBegin);
        mArgs.Advance();
        char bResult = (char)((cIParser2_s0084_3650*)mParser)->EvalCondition(*mArgs.MainArguments(1));
        mTakenVector.mpEnd[-1] = bResult;
        mCondVector.mpEnd[-1] = bResult;
        return true;
    }

    return mTakenVector.mpEnd[-1] == 0;
}

// ---------------------------------------------------------------------------------------------
// 0x008440d0 cParser::ParseCommand
// ---------------------------------------------------------------------------------------------
// @ 0x008440d0
void EA::ArgScript::cParser_s0084_3650::ParseCommand(const char* pText)
{
    ++mNesting;
    string8 line;
    try {
        if (StripCommentsAndWhiteSpace((char*)pText, &line, &mBlockCommentDepth)) {
            if (mMetaCommandStack.mpBegin != mMetaCommandStack.mpEnd) {
                EA::ArgScript::cMetaEntry_s0084_3650* pEntry = mMetaCommandStack.mpEnd - 1;
                if (line.compare(0, pEntry->mpEndToken->size(), pEntry->mpEndToken->mpBegin) == 0) {
                    pEntry->mCommand->EndMeta(false);
                    mMetaCommandStack.mpEnd -= 1;
                } else if (!pEntry->mCommand->Parse(line)) {
                    goto parse;
                }
            } else {
            parse:
                SubstituteVariables(&line, 1);
                mArgs.SplitIntoArguments(line.mpBegin);
                if (mArgs.NumArguments() != 0) {
                    cICommand* pCmd = CommandLookup(mArgs[0]);
                    if (pCmd == 0) {
                        cError err("Unknown command");
                        ThrowException(&err, &gThrowInfo);
                    }
                    mArgs.Advance();
                    pCmd->Execute(&mArgs);
                    mArgs.FindUnprocessed();
                }
            }
        }
    } catch (cError& err) {
        Sprintf(&mLastError, "%s: %s", err.mMessage, line.mpBegin);
        cError rethrow(mLastError.mpBegin);
        ThrowException(&rethrow, &gThrowInfo);
    }
}
