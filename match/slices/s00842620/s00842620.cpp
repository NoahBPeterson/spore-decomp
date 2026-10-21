// Slice s00842620 (batch gold2).
// EA::ArgScript parser core from UTFSpore_Win32/Parser.obj: the cEnd/cPurge/cVersion commands,
// cIfCommand and the If meta command, cParser::ParseFile / ParseStream / Command / DefinitionExists
// and the scope/definition lookup helpers, plus the eastl::pair<string8,string8> destructor.
// Built /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int  uint32;
typedef unsigned char uint8;

// placement new (the CRT header is not available in this freestanding TU)
inline void* __cdecl operator new(unsigned int, void* p) { return p; }

// The CRT declares the global delete as nothrow; that is what lets MSVC omit the
// EH trylevel reset before an inlined destructor body.
void __cdecl operator delete(void*) throw();

// ---------------------------------------------------------------------------------------------
// external helpers (never defined here)
// ---------------------------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
extern "C" __declspec(dllimport) void* __cdecl fopen(const char* path, const char* mode);
extern "C" __declspec(dllimport) int   __cdecl feof(void* f);
extern "C" __declspec(dllimport) char* __cdecl fgets(char* buf, int n, void* f);
extern "C" __declspec(dllimport) int   __cdecl fclose(void* f);

// 0x011e0744: the out-of-line byte copy used by string8's range initialisation.
extern "C" void* __cdecl CopyBytes(void* dst, const void* src, unsigned n);

void __cdecl Sprintf(void* out, const char* fmt, ...);                    // 0x00840c20
void __cdecl SP_cError(void* pBuf, const char* fmt, ...);                 // 0x0052df30
__declspec(noreturn) void __cdecl ThrowException(void* pObj, void* pThrowInfo);  // 0x011e0912
void* __cdecl EAAllocate(uint32 n, const char* pName, int a, int b,
                         const char* pFile, int line);                    // 0x00f473a0
void __cdecl MakeCaseInsensitiveChars(const char* pName, void* pTable);   // 0x00840cc0
bool __cdecl WildcardMatch(const char* pStr, const char* pPat, bool bCase);  // 0x0093d5d0
unsigned __cdecl ReadLine(void* pStream, char* pBuf, unsigned n);         // 0x0093a8b0
void* __cdecl LogAppend(void* pDst, const char* pSrc);                    // 0x0061dea0

// 0x014f9174: the throw-info used by every SP cError throw in this object.
extern char gThrowInfo;
// 0x01667bac: the shared two-byte empty string (`?gEmptyString16@eastl@@3PA_WA`).
extern char gEmptyA[1];
extern char gEmptyB[1];
// 0x01401b70: the empty log fragment the LogAppend chain is seeded with.
extern char gEmptyLog[1];

inline unsigned CharStrlen(const char* p)
{
    const char* pBase = p + 1;
    while (*p++) {}
    return (unsigned)(p - pBase);
}

// eastl::min returns a reference, so the compiler materialises both operands and selects an address.
template <typename T>
inline const T& eastl_min(const T& a, const T& b) { return (b < a) ? b : a; }

// ---------------------------------------------------------------------------------------------
// eastl containers
// ---------------------------------------------------------------------------------------------
namespace eastl {

struct allocator_s0084_2620 { unsigned char pad[4]; };

// The packed-string base that basic_string derives from; Insert() is out of line at 0x0068c9e0.
struct PackStr_s0084_2620 {
    void Insert(char* pDst, const char* first, const char* last);
};

struct string8_s0084_2620 : PackStr_s0084_2620 {
    char* mpBegin;                  // +0x00
    char* mpEnd;                    // +0x04
    char* mpCapacity;               // +0x08
    allocator_s0084_2620 mAllocator;  // +0x0c

    string8_s0084_2620() {
        mpBegin = gEmptyA;
        mpEnd = gEmptyA;
        mpCapacity = gEmptyA + 1;
    }
    string8_s0084_2620(const string8_s0084_2620& x);          // 0x0057cb10 (out of line)
    string8_s0084_2620(const char* p) {
        unsigned n = CharStrlen(p);
        RangeInitialize(n + 1);
        CopyBytes(mpBegin, p, n);
        mpEnd = mpBegin + n;
        mpEnd[0] = 0;
    }
    string8_s0084_2620(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first);
        RangeInitialize(n + 1);
        CopyBytes(mpBegin, first, n);
        mpEnd = mpBegin + n;
        mpEnd[0] = 0;
    }
    ~string8_s0084_2620() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin);
    }
    string8_s0084_2620& operator=(const string8_s0084_2620& x) {
        if (this != &x) assign(x.mpBegin, x.mpEnd);
        return *this;
    }

    // Inline allocator entry point (EASTL's allocator::allocate is folded in).
    void RangeInitialize(unsigned n) {
        if (n > 1) {
            mpBegin = (char*)EAAllocate(n, "ArgScript", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\"
                "Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            mpCapacity = mpBegin + n;
        } else {
            mpBegin = gEmptyA;
            mpCapacity = gEmptyA + 1;
        }
    }

    void assign(const char* first, const char* last);            // 0x00454cb0
    void append(const char* first, const char* last);            // 0x00455d60
    int  find_last_of(const char* p, unsigned pos) const;        // 0x0091bec0
    void erase(unsigned position, unsigned n);                   // 0x0061e200
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }

    // out of line so the 0x00842760 symbol is emitted
    string8_s0084_2620& insert(unsigned pos, const string8_s0084_2620& s);
};

// vec<T, sp_vector_allocator>: retail allocator is 8 bytes, so the object is 0x14.
template <typename T>
struct vec_s0084_2620 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned mAllocator[2];
};

// fixed_vector<T, N>: the vector plus its inline storage (pointer at +0x10, buffer at +0x18).
template <typename T, int N>
struct fixed_vec_s0084_2620 {
    T* mpBegin;          // +0x00
    T* mpEnd;            // +0x04
    T* mpCapacity;       // +0x08
    unsigned mPad0c;     // +0x0c
    T* mpBuffer;         // +0x10
    unsigned mPad14;     // +0x14
    T mBuffer[N];        // +0x18

    fixed_vec_s0084_2620() {
        mpBuffer = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mpBuffer + N;
    }
    ~fixed_vec_s0084_2620() {
        if (mpBegin && mpBegin != mpBuffer) ::operator delete(mpBegin);
    }
};

}  // namespace eastl

using eastl::string8_s0084_2620;
typedef string8_s0084_2620 string8;

// The hashtable lookups return a two-pointer result structure by value; the user-declared copy
// constructor keeps it non-POD so MSVC passes the hidden return pointer (matches retail).
struct FindResult_s0084_2620 {
    void* mpNode;    // +0x00
    void* mpExtra;   // +0x04

    FindResult_s0084_2620() {}
    FindResult_s0084_2620(const FindResult_s0084_2620& x) {
        mpNode = x.mpNode;
        mpExtra = x.mpExtra;
    }
};

namespace EA {
namespace ArgScript {

struct cArguments_s0084_2620;
struct cExpression_s0084_2620;
struct cIParser_s0084_2620;
struct cIMetaCommand;
struct cState { unsigned mStateID; };

// ---- cICommand / cCommandBase / cMetaCommandBase / cBlockCommandBase ----
struct cICommand_s0084_2620 {
    virtual void Execute(cArguments_s0084_2620* pArgs);                 // +0x00
    virtual const char* Description(int helpType) const;                 // +0x04
    virtual void OnRegister(void* pParser, cState* pState);              // +0x08
    virtual int AddRef();                                               // +0x0c
    virtual int Release();                                              // +0x10
    virtual void OnEndBlock(bool bEnd);                                  // +0x14
};

class cIBlockCommand { public:
    virtual void Execute(cArguments_s0084_2620* pArgs);                 // +0x00
    virtual const char* Description(int helpType) const;                 // +0x04
    virtual void OnRegister(void* pParser, cState* pState);              // +0x08
    virtual int AddRef();                                               // +0x0c
    virtual int Release();                                              // +0x10
    virtual void OnEndBlock(bool bEnd);                                  // +0x14
};

struct cCommandBase_s0084_2620 : cICommand_s0084_2620 {
    cIParser_s0084_2620* mParser;   // +0x04
    int mRefCount;                  // +0x08

    cCommandBase_s0084_2620();                                           // 0x0083c800
    virtual ~cCommandBase_s0084_2620();                                  // 0x0083c750
};

// Same layout as cCommandBase; its ctor is at 0x0083c840.
struct cMetaCommandBase_s0084_2620 : cICommand_s0084_2620 {
    void* mParser;          // +0x04
    int mRefCount;          // +0x08

    cMetaCommandBase_s0084_2620();                                       // 0x0083c840
    virtual ~cMetaCommandBase_s0084_2620();                              // 0x0083c7c0
};

struct cArguments_s0084_2620 {
    unsigned char pad[0x44];

    cArguments_s0084_2620();                                             // 0x00837ff0
    ~cArguments_s0084_2620();                                            // 0x00837fa0
    const char* const* MainArguments(int start) const;                   // 0x00838320
    bool HasFlag(const char* pFlag);                                     // 0x008380b0
};

struct cExpression_s0084_2620 {
    unsigned char pad[0x20];

    void EvalExpectCharThrow(const char*& p, char c);                    // 0x0083d240
    void EvalString(const char*& p, string8* pOut);                      // 0x0083dc00
};

// ---- hashtable nodes ----
struct CmdNode_s0084_2620 {                      // value is a pointer at +0x10
    string8 key;                                 // +0x00
    void* mpValue;                               // +0x10
    CmdNode_s0084_2620* mpNext;                  // +0x14
};

struct StrNode_s0084_2620 {                      // value is a string8 at +0x10
    string8 key;                                 // +0x00
    string8 value;                               // +0x10
    StrNode_s0084_2620* mpNext;                  // +0x20
};

struct CmdTable_s0084_2620 {
    int mPad;                                    // +0x00
    CmdNode_s0084_2620** mpBucketArray;          // +0x04
    unsigned mnBucketCount;                      // +0x08
    unsigned char pad0c[0x20 - 0x0c];            // +0x0c
    FindResult_s0084_2620 find(const void* pKey) const;   // 0x007e2ea0
};

struct StrTable_s0084_2620 {
    int mPad;                                    // +0x00
    StrNode_s0084_2620** mpBucketArray;          // +0x04
    unsigned mnBucketCount;                      // +0x08
    unsigned char pad0c[0x20 - 0x0c];            // +0x0c
    FindResult_s0084_2620 find(const void* pKey) const;   // 0x00842790
};

struct IntVec_s0084_2620 {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    unsigned mAllocator[2];
};

// 8-byte stack element used by cParser's meta-command stack.
struct MetaEntry_s0084_2620 { void* mpCommand; void* mpName; };

// ---- an object with one virtual taking a name, reachable from cParser+0xcc ----
struct cIncludeHandler_s0084_2620 {
    virtual void* Resolve(const char* pName);    // +0x00
};

// ---- cIParser: retail vtable layout (block command base just past OnRegister) ----
struct cIParser_s0084_2620 {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual bool Init();                                                 // +0x08
    virtual bool Shutdown();                                             // +0x0c
    virtual void SetState(cState* pState);                               // +0x10
    virtual void RegisterCommand(const char* pName, void* pCommand);     // +0x14
    virtual bool UnregisterCommand(void* pCommand);                      // +0x18
    virtual bool UnregisterCommand(const char* pName);                   // +0x1c
    virtual void* Command(const char* pName) const;                      // +0x20
    virtual void SetFlag(int flag, bool value);                          // +0x24
    virtual void SetMinMaxVersion(int nMin, int nMax);                   // +0x28
    virtual int Version() const;                                         // +0x2c
    virtual void ParseBegin();                                           // +0x30
    virtual int ParseEnd(bool bUnwind);                                  // +0x34
    virtual void ParseFile(const char* pPath);                           // +0x38
    virtual void ParseStream(void* pStream);                             // +0x3c
    virtual void ParseCommand(const char* pCommand);                     // +0x40
    virtual void InstantiateMacro(const char* pName, cArguments_s0084_2620* pArgs);  // +0x44
    virtual void Slot48();                                               // +0x48
    virtual bool ParseFileNoThrow(const char* pPath);                    // +0x4c
    virtual bool ParseCommandNoThrow(const char* pCommand);              // +0x50
    virtual bool InstantiateMacroNoThrow(const char* pName, cArguments_s0084_2620* pArgs);  // +0x54
    virtual const char* LastErrorString() const;                         // +0x58
    virtual const char* LineLocationInfo();                              // +0x5c
    virtual void GetLineLocationInfo(string8* pInfo, int* pLine) const;  // +0x60
    virtual bool CommandExists(const char* pName) const;                 // +0x64
    virtual bool DefinitionExists(const char* pName) const;              // +0x68
    virtual void SetVariable(const char* pName, const char* pValue);     // +0x6c
    virtual const char* Variable(const char* pName) const;               // +0x70
    virtual void SetGlobalVariable(const char* pName, const char* pValue);  // +0x74
    virtual void SetGlobalVariableSet(void* pSet);                       // +0x78
    virtual void PushNamespace(const char* pName);                       // +0x7c
    virtual void PopNamespace();                                         // +0x80
    virtual void PurgeNamespace(const char* pName);                      // +0x84
    virtual const char* CurrentScope() const;                            // +0x88
    virtual void StartBlock(cIBlockCommand* pCommand);                   // +0x8c
    virtual void StartMetaBlock(cIMetaCommand* pCommand, const char* pEndName);  // +0x90
    virtual bool ParseBool(const char* pText) const;                     // +0x94
    virtual float ParseFloat(const char* pText) const;                   // +0x98
    virtual int ParseInt(const char* pText) const;                       // +0x9c
    virtual unsigned ParseUint(const char* pText) const;                 // +0xa0
    virtual cExpression_s0084_2620& Expression();                        // +0xb8
};

// ---- cParser (retail offsets) ----
struct cParser_s0084_2620 : cIParser_s0084_2620 {
    unsigned char pad04[0x10 - 0x04];
    unsigned mFlags;                                     // +0x10
    void* mLogTarget;                                    // +0x14
    unsigned char pad18[0x1c - 0x18];
    int mMinVersion;                                     // +0x1c
    int mMaxVersion;                                     // +0x20
    int mCurrentVersion;                                 // +0x24
    unsigned char pad28[0x2c - 0x28];
    CmdTable_s0084_2620 mCommands;                       // +0x2c (bucket array +0x30, count +0x34)
    unsigned char pad38[0x6c - 0x4c];
    CmdTable_s0084_2620 mTable6c;                        // +0x6c (bucket array +0x70, count +0x74)
    StrTable_s0084_2620 mTable8c;                        // +0x8c (bucket array +0x90, count +0x94)
    StrTable_s0084_2620 mTableAc;                        // +0xac (bucket array +0xb0, count +0xb4)
    cIncludeHandler_s0084_2620* mIncludeHandler;         // +0xcc
    string8 mIncludeBaseDir;                             // +0xd0
    string8 mCurrentPath;                                // +0xe0
    int mCurrentLine;                                    // +0xf0
    unsigned char padf4[0x108 - 0xf4];
    eastl::vec_s0084_2620<void*> mBlockCommandStack;     // +0x108 (4-byte elements)
    eastl::vec_s0084_2620<MetaEntry_s0084_2620> mMetaCommandStack;  // +0x11c (8-byte elements)
    string8 mScope;                                      // +0x130
    IntVec_s0084_2620 mScopeOffsets;                     // +0x140
    string8 mLastErrorString;                            // +0x154
    unsigned char mErrorFlag;                            // +0x164
    unsigned char pad165[0x1b0 - 0x165];
    char mCaseInsensitive[0x40];                         // +0x1b0

    void  ParseFile(const char* pPath);                  // 0x00842c60
    void  ParseStream(void* pStream);                    // 0x00842f50
    void* Command(const char* pName) const;              // 0x00842c10
    bool  DefinitionExists(const char* pName) const;     // 0x00843280
    bool  HasName6c(const char* pName) const;            // 0x008432d0
    void  GetLineLocationInfo(string8* pInfo, int* pLine) const;   // 0x00843240
    const char* LookupName(const char* pName) const;     // 0x00843320
};

typedef cParser_s0084_2620 cParser;
typedef cIParser_s0084_2620 cIParser;
typedef cArguments_s0084_2620 cArguments;
typedef cExpression_s0084_2620 cExpression;

}  // namespace ArgScript
}  // namespace EA

using EA::ArgScript::cArguments;
using EA::ArgScript::cExpression;
using EA::ArgScript::cParser;
using EA::ArgScript::cIBlockCommand;

// ---------------------------------------------------------------------------------------------
// anonymous-namespace command classes
// ---------------------------------------------------------------------------------------------
namespace {

// ---- cMatchFunction: value-matching expression function ----
struct cMatchFunction_s0084_2620 {
    int mPad00;
    int mPad04;

    int  EvalInt(const char** p, cExpression* pExpr);    // 0x00842620
    void EvalReal();                                     // 0x00842a90
};

// ---- cEndCommand ----
struct cEndCommand_s0084_2620 : EA::ArgScript::cMetaCommandBase_s0084_2620 {
    cParser* mState;                                     // +0x0c
    void Execute(cArguments* pArgs);                     // 0x00842910
};

// ---- cPurgeCommand ----
struct cPurgeCommand_s0084_2620 : EA::ArgScript::cCommandBase_s0084_2620 {
    void Execute(cArguments* pArgs);                     // 0x00842980
};

// ---- cVersionCommand ----
struct cVersionCommand_s0084_2620 : EA::ArgScript::cCommandBase_s0084_2620 {
    cParser* mState;                                     // +0x0c
    void Execute(cArguments* pArgs);                     // 0x00842a00
};

// ---- ArgScript::If (0x90): two fixed vectors plus a cArguments ----
struct If_s0084_2620 : EA::ArgScript::cMetaCommandBase_s0084_2620 {
    int mPad0c;                                              // +0x0c
    eastl::fixed_vec_s0084_2620<char, 16> mVec1;             // +0x10
    eastl::fixed_vec_s0084_2620<char, 16> mVec2;             // +0x38
    cArguments mArgs;                                        // +0x60

    If_s0084_2620();                                         // 0x00842ac0
    ~If_s0084_2620();                                        // 0x00842b70
    virtual void Execute(cArguments* pArgs);
    virtual void OnEndParse(bool bEnd);                      // 0x00842b50
};

// ---- eastl::pair<string8 const, string8> ----
struct StringStringPair_s0084_2620 {
    const string8 first;     // +0x00
    string8 second;          // +0x10

    ~StringStringPair_s0084_2620();                          // 0x00842720
};

// The "stream" object passed to ParseStream (an IOStream with a virtual interface).
struct IOStream_s0084_2620 {
    virtual int  AddRef();                          // +0x00
    virtual int  Release();                         // +0x04
    virtual void Slot08();                          // +0x08
    virtual void Slot0c();                          // +0x0c
    virtual bool IsValid();                         // +0x10
    virtual bool IsEOF();                           // +0x14
    virtual void Slot18();                          // +0x18
    virtual void Slot1c();                          // +0x1c
    virtual void Slot20();                          // +0x20
    virtual void Slot24();                          // +0x24
    virtual void Slot28();                          // +0x28
    virtual bool HasData();                         // +0x2c
};

// strip the file name off a path, leaving the directory (with trailing separator).
// @ 0x008428b0
void FindParentDir(const char* pPath, string8* pOut)
{
    pOut->assign(pPath, pPath + CharStrlen(pPath));
    int pos = pOut->find_last_of("/\\", 0xffffffffu);
    if (pos != -1)
        pOut->erase((unsigned)(pos + 1), 0xffffffffu);
    else
        pOut->assign(gEmptyA, gEmptyB);
}

}  // namespace

// ---------------------------------------------------------------------------------------------
// 0x00842620..0x00842a90: expression functions
// ---------------------------------------------------------------------------------------------

// @ 0x00842620
int cMatchFunction_s0084_2620::EvalInt(const char** p, cExpression* pExpr)
{
    string8 a;
    string8 b;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &a);
    pExpr->EvalExpectCharThrow(*p, ',');
    pExpr->EvalString(*p, &b);
    pExpr->EvalExpectCharThrow(*p, ')');
    bool bMatch = WildcardMatch(a.mpBegin, b.mpBegin, false);
    return bMatch != false;
}

// @ 0x00842a90
void cMatchFunction_s0084_2620::EvalReal()
{
    char buf[16];
    SP_cError(buf, "boolean function");
    ThrowException(buf, &gThrowInfo);
}

// ---------------------------------------------------------------------------------------------
// 0x00842720..0x008428b0: pair / string helpers
// ---------------------------------------------------------------------------------------------

// @ 0x00842720
StringStringPair_s0084_2620::~StringStringPair_s0084_2620()
{
}

// @ 0x00842760
string8_s0084_2620& string8_s0084_2620::insert(unsigned pos, const string8_s0084_2620& s)
{
    Insert(mpBegin + pos, s.mpBegin, s.mpEnd);
    return *this;
}

// ---------------------------------------------------------------------------------------------
// 0x00842910..0x00842a00: built-in commands
// ---------------------------------------------------------------------------------------------

// @ 0x00842910
void cEndCommand_s0084_2620::Execute(cArguments* pArgs)
{
    pArgs->MainArguments(0);
    eastl::vec_s0084_2620<void*>& stack = mState->mBlockCommandStack;
    if (stack.mpBegin == stack.mpEnd) {
        char buf[16];
        SP_cError(buf, "Not inside a block");
        ThrowException(buf, &gThrowInfo);
    }
    void** ppEnd = mState->mBlockCommandStack.mpEnd;
    cIBlockCommand* pBlock = (cIBlockCommand*)*(ppEnd - 1);
    mState->mBlockCommandStack.mpEnd += -1;
    return pBlock->OnEndBlock(false);
}

// @ 0x00842980
void cPurgeCommand_s0084_2620::Execute(cArguments* pArgs)
{
    cParser* pParser = (cParser*)mParser;
    const char* pName = *pArgs->MainArguments(1);
    const char* p = pName;
    unsigned len = CharStrlen(p);
    if (len > 1 && pName[len - 1] == ':') {
        pParser->PurgeNamespace(pName);
    } else {
        char buf[16];
        SP_cError(buf, "Bad scope '%s' specified", pName);
        ThrowException(buf, &gThrowInfo);
    }
}

// @ 0x00842a00
void cVersionCommand_s0084_2620::Execute(cArguments* pArgs)
{
    const char* pVer = *pArgs->MainArguments(1);
    cParser* pParser = (cParser*)mParser;
    int version = pParser->ParseInt(pVer);
    mState->mCurrentVersion = version;
    if (version < mState->mMinVersion) {
        char buf[16];
        SP_cError(buf,
                  "Script version no longer supported: have %d, need at least %d",
                  version, mState->mMinVersion);
        ThrowException(buf, &gThrowInfo);
    }
    if (version > mState->mMaxVersion) {
        char buf[16];
        SP_cError(buf,
                  "Script version more recent than code: have %d, can only handle up to %d",
                  version, mState->mMaxVersion);
        ThrowException(buf, &gThrowInfo);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00842ac0..0x00842b70: the If meta command
// ---------------------------------------------------------------------------------------------

// @ 0x00842ac0
If_s0084_2620::If_s0084_2620()
{
}

// @ 0x00842b50
void If_s0084_2620::OnEndParse(bool bEnd)
{
    if (mVec1.mpEnd != mVec1.mpBegin) {
        mVec1.mpEnd -= 1;
        mVec2.mpEnd -= 1;
    }
}

// 0x00842b70 (If_s0084_2620::~If_s0084_2620) is compiler generated (only its vfptr store is absent
// from the original, and it has no out-of-line definition to hang a marker on).

// ---------------------------------------------------------------------------------------------
// 0x00842c10..0x00843280: cParser lookups
// ---------------------------------------------------------------------------------------------

// @ 0x00842c10
void* cParser::Command(const char* pName) const
{
    MakeCaseInsensitiveChars(pName, (void*)mCaseInsensitive);
    const CmdTable_s0084_2620& cmds = mCommands;
    FindResult_s0084_2620 r = cmds.find(mCaseInsensitive);
    if (r.mpNode != cmds.mpBucketArray[cmds.mnBucketCount])
        return ((CmdNode_s0084_2620*)r.mpNode)->mpValue;
    return 0;
}

// @ 0x00842c60
void cParser::ParseFile(const char* pPath)
{
    void* f = fopen(pPath, "r");
    if (!f) {
        Sprintf(&mLastErrorString, "File not found: '%s'", pPath);
        char buf[16];
        SP_cError(buf, mLastErrorString.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
    string8 savedBaseDir(mIncludeBaseDir);
    FindParentDir(pPath, &mIncludeBaseDir);
    const int blockCount = (int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin);
    const int metaCount  = (int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin);
    int line = 1;
    for (;;) {
        if (feof(f))
            break;
        char buf[0x800];
        buf[0] = 0;
        fgets(buf, 0x800, f);
        try {
            mCurrentPath.assign(pPath, pPath + CharStrlen(pPath));
            mCurrentLine = line;
            ParseCommand(buf);
        } catch (...) {
            if (!mErrorFlag) {
                string8 msg;
                Sprintf(&msg, "%s(%d): error: ", pPath, line);
                mLastErrorString.insert(0, msg);
            }
            if (!(mFlags & 1)) {
                mErrorFlag = 1;
                fclose(f);
                char buf2[16];
                SP_cError(buf2, mLastErrorString.mpBegin);
                ThrowException(buf2, &gThrowInfo);
            }
            if (mLogTarget) {
                LogAppend(LogAppend(LogAppend(mLogTarget, gEmptyLog),
                                    mLastErrorString.mpBegin), gEmptyLog);
            }
        }
        line++;
    }
    fclose(f);
    if ((int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin) != blockCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced block command in '%s': too many or two few 'end's.\n", pPath);
        ThrowException(buf, &gThrowInfo);
    }
    if ((int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin) != metaCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced meta command in '%s': look for missing close tag "
                       "(e.g. endif/enddef)\n", pPath);
        ThrowException(buf, &gThrowInfo);
    }
    mIncludeBaseDir = savedBaseDir;
}

// @ 0x00842f50
void cParser::ParseStream(void* pStream)
{
    IOStream_s0084_2620* p = (IOStream_s0084_2620*)pStream;
    if (!p || !p->IsValid()) {
        mLastErrorString.assign("Bad input stream", "Bad input stream" + 17);
        char buf[16];
        SP_cError(buf, mLastErrorString.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
    string8 stream("stream");
    const int blockCount = (int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin);
    const int metaCount  = (int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin);
    int line = 1;
    for (;;) {
        if (p->IsEOF())
            break;
        if (!p->HasData())
            break;
        char buf[0x800];
        buf[0] = 0;
        ReadLine(p, buf, 0x800);
        try {
            mCurrentPath.assign(stream.mpBegin, stream.mpEnd);
            mCurrentLine = line;
            ParseCommand(buf);
        } catch (...) {
            if (!mErrorFlag) {
                string8 msg;
                Sprintf(&msg, "%s(%d): error: ", stream.mpBegin, line);
                mLastErrorString.insert(0, msg);
            }
            if (!(mFlags & 1)) {
                mErrorFlag = 1;
                char buf2[16];
                SP_cError(buf2, mLastErrorString.mpBegin);
                ThrowException(buf2, &gThrowInfo);
            }
            if (mLogTarget) {
                LogAppend(LogAppend(LogAppend(mLogTarget, gEmptyLog),
                                    mLastErrorString.mpBegin), gEmptyLog);
            }
        }
        line++;
    }
    if ((int)(mBlockCommandStack.mpEnd - mBlockCommandStack.mpBegin) != blockCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced block command in '%s': too many or two few 'end's.\n",
                  stream.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
    if ((int)(mMetaCommandStack.mpEnd - mMetaCommandStack.mpBegin) != metaCount) {
        char buf[16];
        SP_cError(buf, "Unbalanced meta command in '%s': look for missing close tag "
                       "(e.g. endif/enddef)\n", stream.mpBegin);
        ThrowException(buf, &gThrowInfo);
    }
}

// @ 0x00843240
void cParser::GetLineLocationInfo(string8* pInfo, int* pLine) const
{
    if (pInfo && &mCurrentPath != pInfo)
        pInfo->assign(mCurrentPath.mpBegin, mCurrentPath.mpEnd);
    if (pLine)
        *pLine = mCurrentLine;
}

// @ 0x00843280
bool cParser::DefinitionExists(const char* pName) const
{
    MakeCaseInsensitiveChars(pName, (void*)mCaseInsensitive);
    FindResult_s0084_2620 r = mCommands.find(mCaseInsensitive);
    CmdNode_s0084_2620* pEnd = mCommands.mpBucketArray[mCommands.mnBucketCount];
    return r.mpNode != pEnd;
}

// @ 0x008432d0
bool cParser::HasName6c(const char* pName) const
{
    MakeCaseInsensitiveChars(pName, (void*)mCaseInsensitive);
    FindResult_s0084_2620 r = mTable6c.find(mCaseInsensitive);
    CmdNode_s0084_2620* pEnd = mTable6c.mpBucketArray[mTable6c.mnBucketCount];
    return r.mpNode != pEnd;
}

// @ 0x00843320
const char* cParser::LookupName(const char* pName) const
{
    const char* pResult = 0;
    bool bFound = false;

    if (*pName == ':') {
        string8 name(pName + 1, pName + 1 + CharStrlen(pName + 1));
        FindResult_s0084_2620 r = mTable8c.find(name.mpBegin);
        if (r.mpNode != mTable8c.mpBucketArray[mTable8c.mnBucketCount]) {
            pResult = *(const char**)((char*)r.mpNode + 0x10);
            bFound = true;
        }
    } else {
        const unsigned len = CharStrlen(pName);
        string8 name(mScope);
        name.append(pName, pName + len);
        FindResult_s0084_2620 r = mTable8c.find(name.mpBegin);
        int i = (int)(mScopeOffsets.mpEnd - mScopeOffsets.mpBegin) - 1;
        while (r.mpNode == mTable8c.mpBucketArray[mTable8c.mnBucketCount] && i >= 0) {
            unsigned off = (unsigned)mScopeOffsets.mpBegin[i];
            unsigned sz  = (unsigned)(mScope.mpEnd - mScope.mpBegin);
            unsigned n   = eastl_min(off, sz);
            name.assign(mScope.mpBegin, mScope.mpBegin + n);
            name.append(pName, pName + len);
            r = mTable8c.find(name.mpBegin);
            i--;
        }
        if (r.mpNode != mTable8c.mpBucketArray[mTable8c.mnBucketCount]) {
            pResult = *(const char**)((char*)r.mpNode + 0x10);
            bFound = true;
        }
    }

    if (!bFound) {
        string8 bare(pName, pName + CharStrlen(pName));
        FindResult_s0084_2620 r = mTableAc.find(bare.mpBegin);
        if (r.mpNode != mTableAc.mpBucketArray[mTableAc.mnBucketCount]) {
            return *(const char**)((char*)r.mpNode + 0x10);
        }
    } else {
        return pResult;
    }

    if (mIncludeHandler) {
        void* pv = mIncludeHandler->Resolve(pName);
        if (pv)
            return (const char*)pv;
    }
    return 0;
}
