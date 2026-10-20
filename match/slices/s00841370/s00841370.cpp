// Slice s00841370 (batch gold2).
// EA::ArgScript parser / command / expression code from UTFSpore_Win32/Parser.obj: cParser and
// cExpression value parsing, the built-in commands (SetE, Namespace, Create, SCreate, ShowArguments,
// Trace, Help, ArrayCreate), the *Exists expression functions and the EASTL string helpers they use.
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
extern "C" void* __cdecl ByteCopy(void* dst, const void* src, unsigned n);          // 0x011e0744
extern "C" char* __cdecl slab_search(const char* first, const char* last,
                                     const char* pfirst, const char* plast);        // 0x00609d90
extern "C" int   __cdecl CompareBytes(const char* a, const char* b, unsigned n);    // 0x005f7870
bool __cdecl String8Equals(const void* a, const void* b);                            // 0x00554fb0 (operator==)

void __cdecl Sprintf(void* out, const char* fmt, ...);                              // 0x00840c20
void __cdecl Output(int* pOut, const char* fmt, ...);                               // 0x00841000
bool __cdecl Text_WildcardMatch(const char* pStr, const char* pPattern, bool bCase); // 0x0093d5d0

inline unsigned CharStrlen(const char* p)
{
    const char* pCurrent = p;
    const char* const pBase = p + 1;
    while (*pCurrent++) {}
    return (unsigned)(pCurrent - pBase);
}

// eastl::min returns a reference, so the compiler materialises both operands and selects an address.
template <typename T>
inline const T& eastl_min(const T& a, const T& b) { return (b < a) ? b : a; }

template <typename T>
inline const T& min_alt(const T& a, const T& b) { return (a < b) ? a : b; }

// 0x01667bac: shared empty-string storage (`?gEmptyString16@eastl@@3PA_WA`)
extern char gEmptyStr[2];

namespace eastl {
struct allocator_s0084_1370 { unsigned char pad[4]; };

struct string8_s0084_1370 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0084_1370 mAllocator;

    string8_s0084_1370() {
        mpBegin = gEmptyStr;
        mpEnd = gEmptyStr;
        mpCapacity = gEmptyStr + 1;
    }
    __forceinline string8_s0084_1370(const string8_s0084_1370& x) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        char* e = x.mpEnd;
        char* b = x.mpBegin;
        unsigned n = (unsigned)(e - b);
        RangeInitialize(n + 1);
        ByteCopy(mpBegin, b, n);
        mpEnd = mpBegin + (e - b);
        *mpEnd = 0;
    }
    ~string8_s0084_1370() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin);
    }
    void RangeInitialize(unsigned n);                            // 0x00475ab0
    void append(const char* first, const char* last);            // 0x00455d60
    void assign(const char* first, const char* last);            // 0x00454cb0
    int  compare(unsigned pos, unsigned n, const char* p) const; // 0x008417c0
    int  find(const char* p, unsigned pos) const;                // 0x00841d00
    void erase(unsigned position, unsigned n = 0xffffffffu);     // inline (used by PopNamespace)
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

// vector<T, sp_vector_allocator>: retail allocator is 8 bytes, so the object is 0x14.
template <typename T>
struct vec_s0084_1370 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned mAllocator[2];
    ~vec_s0084_1370() {
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) ::operator delete(mpBegin);
    }
};
}  // namespace eastl

using eastl::string8_s0084_1370;
using eastl::vec_s0084_1370;
typedef string8_s0084_1370 string8;

namespace EA {
namespace ArgScript {

struct cArguments_s0084_1370;
struct cExpression_s0084_1370;
struct cIParser_s0084_1370;
struct cState { unsigned mStateID; };
struct cIBlockCommand;
struct cIMetaCommand;

// ---- cICommand / cCommandBase / cMetaCommandBase / cBlockCommandBase ----
struct cICommand_s0084_1370 {
    virtual void Execute(cArguments_s0084_1370* pArgs);                 // +0x00
    virtual const char* Description(int helpType) const;                 // +0x04
    virtual void OnRegister(void* pParser, cState* pState);              // +0x08
    virtual int AddRef();                                                // +0x0c
    virtual int Release();                                               // +0x10
};

struct cCommandBase_s0084_1370 : cICommand_s0084_1370 {
    cIParser_s0084_1370* mParser;   // +0x04
    int mRefCount;          // +0x08

    cCommandBase_s0084_1370();                                           // 0x0083c800
    virtual ~cCommandBase_s0084_1370();                                  // 0x0083c750
    virtual void OnRegister(void* pParser, cState* pState);              // 0x0083c780
};

// Same layout as cCommandBase; its OnRegister lives at 0x0083c7f0.
struct cMetaCommandBase_s0084_1370 : cICommand_s0084_1370 {
    void* mParser;          // +0x04
    int mRefCount;          // +0x08

    virtual void OnRegister(void* pParser, cState* pState);              // 0x0083c7f0
};

// 0x30 bytes; OnRegister is still cCommandBase's (0x0083c780).
struct cBlockCommandBase_s0084_1370 : cCommandBase_s0084_1370 {
    unsigned char pad0c[0x30 - 0x0c];
};

struct cArguments_s0084_1370 {
    unsigned char pad[0x44];

    cArguments_s0084_1370();                                             // 0x00837ff0
    cArguments_s0084_1370(const char* pArgString);                       // 0x008386d0
    ~cArguments_s0084_1370();                                            // 0x00837fa0
    int NumArguments() const;                                            // 0x00837f30
    const char* operator[](int i) const;                                 // 0x00837f20
    const char* const* MainArguments(int start) const;                   // 0x00838320
    const char* const* MainArguments(int* pNum, int start, int count) const;  // 0x00838020
    bool HasFlag(const char* pFlag);                                     // 0x008380b0
};

struct cExpression_s0084_1370 {
    unsigned char pad[0x20];               // eastl::hash_map of functions

    void  EvalExpectCharThrow(const char*& p, char c);                   // 0x0083d240
    bool  EvalContinueChar(const char*& p, char c);                      // 0x0083d290
    void  EvalString(const char*& p, string8* pOut);                     // 0x0083dc00
    float EvalRealExpression(const char*& p);                            // 0x0083e470
    bool  operator==(const cExpression_s0084_1370& x) const { return true; }
};

// ---- hashtable node of mCommands: key string8, AutoRefCount<cICommand>, next ----
struct CommandNode_s0084_1370 {
    string8 key;            // +0x00
    void* mpCommand;        // +0x10 (AutoRefCount<cICommand>::mpObject)
    CommandNode_s0084_1370* mpNext;   // +0x14
};

struct CommandTable_s0084_1370 {
    int mPad2c;                              // +0x00 (table object lives at cParser+0x2c)
    CommandNode_s0084_1370** mpBucketArray;  // +0x04
    unsigned mnBucketCount;                  // +0x08
};

struct IntVec_s0084_1370 {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    unsigned mAllocator[2];
};

// ---- cIParser: retail vtable layout (one extra slot that the dev PDB does not know about sits
// right after InstantiateMacro, so everything from InstantiateMacroNoThrow on is 4 bytes higher).
struct cIParser_s0084_1370 {
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
    virtual void InstantiateMacro(const char* pName, cArguments_s0084_1370* pArgs);  // +0x44
    virtual void Slot48();                                               // +0x48
    virtual bool ParseFileNoThrow(const char* pPath);                    // +0x4c
    virtual bool ParseCommandNoThrow(const char* pCommand);              // +0x50
    virtual bool InstantiateMacroNoThrow(const char* pName, cArguments_s0084_1370* pArgs);  // +0x54
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
    virtual void ParseVector2(void* pOut, const char* pText) const;      // +0xa4
    virtual void ParseVector3(void* pOut, const char* pText) const;      // +0xa8
    virtual void ParseVector4(void* pOut, const char* pText) const;      // +0xac
    virtual void ParseRGB(void* pOut, const char* pText) const;          // +0xb0
    virtual void ParseRGBA(void* pOut, const char* pText) const;         // +0xb4
    virtual cExpression_s0084_1370& Expression();                        // +0xb8
    virtual void SetOutStream(void* pStream);                            // +0xbc
    virtual void SetTraceStream(void* pStream);                          // +0xc0
    virtual void* OutStream() const;                                     // +0xc4
    virtual void* TraceStream() const;                                   // +0xc8
};

// ---- cParser (retail offsets) ----
struct cParser_s0084_1370 : cIParser_s0084_1370 {
    unsigned char pad04[0x10 - 0x04];
    unsigned mFlags;                                     // +0x10
    unsigned char pad14[0x2c - 0x14];
    CommandTable_s0084_1370 mCommands;                   // +0x2c (bucket array +0x30, count +0x34)
    unsigned char pad38[0x4c - 0x38];
    cExpression_s0084_1370 mExpression;                  // +0x4c
    unsigned char pad6c[0xe0 - 0x6c];
    string8 mCurrentPath;                                // +0xe0
    int mCurrentLine;                                    // +0xf0
    string8 mLineLocation;                               // +0xf4
    unsigned char pad104[0x130 - 0x104];
    string8 mScope;                                      // +0x130
    IntVec_s0084_1370 mScopeOffsets;                     // +0x140

    enum tFlag { kFlagContinueAfterError = 0, kMaxFlags = 1 };

    void SetFlag(tFlag flag, bool value);                                // 0x00841490
    const char* LineLocationInfo();                                      // 0x008414d0
    float* ParseVector2(float* pOut, const char* pText);                 // 0x00841540
    float* ParseVector3(float* pOut, const char* pText);                 // 0x00841590
    float* ParseRGBA(float* pOut, const char* pText);                    // 0x00841610
    float* ParseRGB(float* pOut, const char* pText);                     // 0x008416b0
    void PopNamespace();                                                 // 0x00841c90
};

typedef cParser_s0084_1370 cParser;
typedef cIParser_s0084_1370 cIParser;

}  // namespace ArgScript
}  // namespace EA

// string8 helpers that live in this slice -------------------------------------------------------
namespace eastl {

// @ 0x008417c0
int string8_s0084_1370::compare(unsigned pos, unsigned n, const char* p) const
{
    const int n1 = (int)(mpEnd - mpBegin) - (int)pos;
    const int n2 = (int)CharStrlen(p);
    const int nMin = (int)min_alt((unsigned)n1, n);
    const int r = CompareBytes(mpBegin + pos, p, (unsigned)min_alt(n2, nMin));
    return (r != 0) ? r : (nMin < n2 ? -1 : (nMin > n2 ? 1 : 0));
}

// @ 0x00841d00
int string8_s0084_1370::find(const char* p, unsigned pos) const
{
    const unsigned plen = CharStrlen(p);
    char* const pBegin = mpBegin;
    char* const pEnd = mpEnd;
    if ((unsigned)(pEnd - pBegin) < plen + pos) return -1;
    const char* pFound = slab_search(pBegin + pos, pEnd, p, p + plen);
    if (pFound != pEnd || plen == 0) return (int)(pFound - pBegin);
    return -1;
}

// inlined by PopNamespace
inline void string8_s0084_1370::erase(unsigned position, unsigned n)
{
    unsigned count = min_alt(size() - position, n);
    char* pDest = mpBegin + position;
    char* pSrc = pDest + count;
    if (pDest != pSrc) {
        memmove(pDest, pSrc, (unsigned)(mpEnd - pSrc) + 1);
        mpEnd = pDest + (mpEnd - pSrc);
    }
}

}  // namespace eastl

using EA::ArgScript::cArguments_s0084_1370;
using EA::ArgScript::cParser;
using EA::ArgScript::cState;
typedef cArguments_s0084_1370 cArguments;

// ---------------------------------------------------------------------------------------------
// anonymous-namespace command classes
// ---------------------------------------------------------------------------------------------
namespace {

// ---- cCommandStateT<cParser, cMetaCommandBase>: command + the parser it was registered for ----
struct cCommandStateMeta_s0084_1370 : EA::ArgScript::cMetaCommandBase_s0084_1370 {
    cParser* mState;        // +0x0c
    void OnRegister(void* pParser, cState* pState);      // 0x00841410
};

// ---- cCommandStateT<cParser, cBlockCommandBase> ----
struct cCommandStateBlock_s0084_1370 : EA::ArgScript::cBlockCommandBase_s0084_1370 {
    cParser* mState;        // +0x30
    void OnRegister(void* pParser, cState* pState);      // 0x00841440
};

// ---- plain commands built on cCommandBase: output stream at +0x04 ----
struct cOutputCommand_s0084_1370 {
    int mPad00;
    int* mOut;              // +0x04
};

struct cEvalCommand_s0084_1370 {
    int mPad00;
    cParser* mParser;       // +0x04
    void Execute(cArguments* pArgs);                     // 0x008418b0
};

struct cSetECommand_s0084_1370 : EA::ArgScript::cCommandBase_s0084_1370 {
    int mPad0c;                 // +0x0c
    cArguments mArguments;      // +0x10

    cSetECommand_s0084_1370();                           // 0x00841900
};

struct cNamespaceCommand_s0084_1370 : EA::ArgScript::cBlockCommandBase_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x008419d0
    void OnEndBlock(bool bEnd);                          // 0x00841a10
};

struct cCreateCommand_s0084_1370 : cCommandStateMeta_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841a50
};

struct cSCreateCommand_s0084_1370 : cCommandStateMeta_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841ae0
};

struct cShowArgumentsCommand_s0084_1370 : cOutputCommand_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841b70
};

struct cTraceCommand_s0084_1370 : cOutputCommand_s0084_1370 {
    void Execute(cArguments* pArgs);                     // 0x00841bf0
};

struct cHelpCommand_s0084_1370 : cOutputCommand_s0084_1370 {
    int mPad08;             // +0x08
    cParser* mState;        // +0x0c
    void Execute(cArguments* pArgs);                     // 0x00842080
};

struct cArrayCreateCommand_s0084_1370 {
    int mPad00;
    cParser* mParser;       // +0x04
    void Execute(cArguments* pArgs);                     // 0x00842230
};

struct ExistFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser* mParser;       // +0x08
};

struct cVariableExistsFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser* mParser;       // +0x08
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x00842310
};

struct cDefinitionExistsFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser* mParser;       // +0x08
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x008423c0
};

struct cCommandExistsFunction_s0084_1370 {
    int mPad00;
    int mPad04;
    cParser* mParser;       // +0x08
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x00842470
};

struct cEqFunction_s0084_1370 {
    int mPad00;
    int mRefCount;          // +0x04
    int EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr);  // 0x00842520
};

// ---- pair<string8, string8> (0x20) used by the variable table ----
struct StringPair_s0084_1370 {
    string8 first;          // +0x00
    string8 second;         // +0x10

    StringPair_s0084_1370(const string8& a, const string8& b);   // 0x00841d60
    StringPair_s0084_1370(const StringPair_s0084_1370& x);       // 0x00841f00
};

// ---- cMacroDefinition (0x90): name string8, argument spec, two vectors, body text ----
struct cMacroDefinition_s0084_1370 {
    int mRefCount;                      // +0x00
    string8 mName;                      // +0x04
    cArguments mArgs;                   // +0x14
    vec_s0084_1370<int> mArgNames;      // +0x58
    vec_s0084_1370<int> mArgDefaults;   // +0x6c
    string8 mBody;                      // +0x80

    ~cMacroDefinition_s0084_1370();     // 0x00841fd0
};

}  // namespace

// ---------------------------------------------------------------------------------------------
// 0x00841370..0x008417c0: parser helpers
// ---------------------------------------------------------------------------------------------

// @ 0x00841370
bool __fastcall cParser_InstantiateMacroNoThrow(int* self, int, const char* pName, cArguments* pArgs)
{
    try {
        ((void(__thiscall*)(int*, const char*, cArguments*))(*(void***)self)[0x44 / 4])(self, pName, pArgs);
    } catch (...) {
        return false;
    }
    return true;
}

// @ 0x00841410
void cCommandStateMeta_s0084_1370::OnRegister(void* pParser, cState* pState)
{
    mState = pState ? (cParser*)((char*)pState - 4) : 0;
    EA::ArgScript::cMetaCommandBase_s0084_1370::OnRegister(pParser, pState);
}

// @ 0x00841440
void cCommandStateBlock_s0084_1370::OnRegister(void* pParser, cState* pState)
{
    mState = pState ? (cParser*)((char*)pState - 4) : 0;
    EA::ArgScript::cCommandBase_s0084_1370::OnRegister(pParser, pState);
}

// @ 0x00841490
void cParser::SetFlag(tFlag flag, bool value)
{
    if ((unsigned)flag >= (unsigned)kMaxFlags) return;
    if (value) mFlags |= 1u << (flag & 0x1f);
    else mFlags &= ~(1u << (flag & 0x1f));
}

// @ 0x008414d0
const char* cParser::LineLocationInfo()
{
    Sprintf(&mLineLocation, "%s:%d", mCurrentPath.mpBegin, mCurrentLine);
    return mLineLocation.mpBegin;
}

// @ 0x00841540
float* cParser::ParseVector2(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ','))
        pOut[1] = pExpr->EvalRealExpression(pText);
    else
        pOut[1] = pOut[0];
    return pOut;
}

// @ 0x00841590
float* cParser::ParseVector3(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ',')) {
        pOut[1] = pExpr->EvalRealExpression(pText);
        pExpr->EvalExpectCharThrow(pText, ',');
        pOut[2] = pExpr->EvalRealExpression(pText);
    } else {
        pOut[1] = pOut[0];
        pOut[2] = pOut[0];
    }
    return pOut;
}

// @ 0x00841610
float* cParser::ParseRGBA(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ',')) {
        pOut[1] = pExpr->EvalRealExpression(pText);
        pExpr->EvalExpectCharThrow(pText, ',');
        pOut[2] = pExpr->EvalRealExpression(pText);
        pExpr->EvalExpectCharThrow(pText, ',');
        pOut[3] = pExpr->EvalRealExpression(pText);
    } else {
        pOut[1] = pOut[0];
        pOut[2] = pOut[0];
        pOut[3] = pOut[0];
    }
    return pOut;
}

// @ 0x008416b0
float* cParser::ParseRGB(float* pOut, const char* pText)
{
    EA::ArgScript::cExpression_s0084_1370* pExpr = &mExpression;
    pOut[0] = pExpr->EvalRealExpression(pText);
    pExpr->EvalExpectCharThrow(pText, ',');
    pOut[1] = pExpr->EvalRealExpression(pText);
    pExpr->EvalExpectCharThrow(pText, ',');
    pOut[2] = pExpr->EvalRealExpression(pText);
    if (pExpr->EvalContinueChar(pText, ','))
        pOut[3] = pExpr->EvalRealExpression(pText);
    else
        pOut[3] = 1.0f;
    return pOut;
}

// ---------------------------------------------------------------------------------------------
// 0x008418b0..0x00841c30: built-in commands
// ---------------------------------------------------------------------------------------------

// @ 0x008418b0
void cEvalCommand_s0084_1370::Execute(cArguments* pArgs)
{
    mParser->ParseCommand(*pArgs->MainArguments(1));
}

// @ 0x00841900
cSetECommand_s0084_1370::cSetECommand_s0084_1370()
{
}

// @ 0x008419d0
void cNamespaceCommand_s0084_1370::Execute(cArguments* pArgs)
{
    mParser->StartBlock((EA::ArgScript::cIBlockCommand*)this);
    mParser->PushNamespace(*pArgs->MainArguments(1));
}

// @ 0x00841a10
void cNamespaceCommand_s0084_1370::OnEndBlock(bool bEnd)
{
    mParser->PopNamespace();
}

// @ 0x00841a50
void cCreateCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* const* pMain = pArgs->MainArguments(2);
    cArguments args(pMain[1]);
    mState->InstantiateMacro(pMain[0], &args);
}

// @ 0x00841ae0
void cSCreateCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* const* pMain = pArgs->MainArguments(2);
    cArguments args(pMain[1]);
    mState->InstantiateMacroNoThrow(pMain[0], &args);
}

// @ 0x00841b70
void cShowArgumentsCommand_s0084_1370::Execute(cArguments* pArgs)
{
    Output(mOut, "Arguments:\n");
    for (int i = 0; i < pArgs->NumArguments(); ++i)
        Output(mOut, "%d: %s\n", i, (*pArgs)[i]);
}

// @ 0x00841bf0
void cTraceCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* pArg = *pArgs->MainArguments(1);
    Output(mOut, "%s\n", pArg);
}

// @ 0x00841c30 is the compiler-generated scalar deleting destructor (??_G) for
// cSetECommand_s0084_1370; it is emitted automatically for the implicit virtual destructor.

// ---------------------------------------------------------------------------------------------
// 0x00841c90..0x00842080: namespaces, macro table, help
// ---------------------------------------------------------------------------------------------

// @ 0x00841c90
void cParser::PopNamespace()
{
    mScope.erase(mScopeOffsets.mpEnd[-1]);
    mScopeOffsets.mpEnd -= 1;
}

// @ 0x00841d60
StringPair_s0084_1370::StringPair_s0084_1370(const string8& a, const string8& b)
    : first(a), second(b)
{
}

// @ 0x00841f00
StringPair_s0084_1370::StringPair_s0084_1370(const StringPair_s0084_1370& x)
    : first(x.first), second(x.second)
{
}

// @ 0x00841fd0
cMacroDefinition_s0084_1370::~cMacroDefinition_s0084_1370()
{
}

// @ 0x00842080
void cHelpCommand_s0084_1370::Execute(cArguments* pArgs)
{
    int numMain;
    const char* const* pMain = pArgs->MainArguments(&numMain, 0, 1);
    const char* pPattern = "*";
    if (numMain > 0) pPattern = pMain[0];

    EA::ArgScript::CommandNode_s0084_1370** pBucket = mState->mCommands.mpBucketArray;
    EA::ArgScript::CommandNode_s0084_1370* pNode = *pBucket;
    int numMatches = 0;
    if (!pNode) {
        ++pBucket;
        while (!*pBucket) ++pBucket;
        pNode = *pBucket;
    }
    if (pNode != mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]) {
        do {
            if (Text_WildcardMatch(pNode->key.mpBegin, pPattern, false)) ++numMatches;
            pNode = pNode->mpNext;
            if (!pNode) {
                do {
                    ++pBucket;
                    pNode = *pBucket;
                } while (!pNode);
            }
        } while (pNode != mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]);

        if (numMatches > 0) {
            int helpType = 0;
            if (numMatches == 1) helpType = 1;
            if (pArgs->HasFlag("full")) helpType = 1;
            if (pArgs->HasFlag("html")) helpType = 2;

            pBucket = mState->mCommands.mpBucketArray;
            pNode = *pBucket;
            if (!pNode) {
                ++pBucket;
                while (!*pBucket) ++pBucket;
                pNode = *pBucket;
            }
            if (pNode == mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]) return;
            do {
                if (Text_WildcardMatch(pNode->key.mpBegin, pPattern, false)) {
                    EA::ArgScript::cICommand_s0084_1370* pCommand =
                        (EA::ArgScript::cICommand_s0084_1370*)pNode->mpCommand;
                    const char* pDescription = pCommand->Description(helpType);
                    if (!pDescription) pDescription = "no description";
                    Output(mOut, "%-20s: %s\n", pNode->key.mpBegin, pDescription);
                }
                pNode = pNode->mpNext;
                if (!pNode) {
                    do {
                        ++pBucket;
                        pNode = *pBucket;
                    } while (!pNode);
                }
            } while (pNode != mState->mCommands.mpBucketArray[mState->mCommands.mnBucketCount]);
            return;
        }
    }
    Output(mOut, "No matches! You may want to include wildcards. (*, ?, etc.)\n");
}

// ---------------------------------------------------------------------------------------------
// 0x00842230..0x00842520: array create command and expression functions
// ---------------------------------------------------------------------------------------------

// @ 0x00842230
void cArrayCreateCommand_s0084_1370::Execute(cArguments* pArgs)
{
    const char* const* pMain = pArgs->MainArguments(2);
    int numArrays = mParser->ParseInt(pMain[1]);
    for (int i = 0; i < numArrays; ++i) {
        string8 name;
        Sprintf(&name, "%s %s(%d %d)", "create", pMain[0], i, numArrays);
        mParser->ParseCommand(name.mpBegin);
    }
}

// @ 0x00842310
int cVariableExistsFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 name;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &name);
    pExpr->EvalExpectCharThrow(*p, ')');
    return mParser->Variable(name.mpBegin) != 0;
}

// @ 0x008423c0
int cDefinitionExistsFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 name;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &name);
    pExpr->EvalExpectCharThrow(*p, ')');
    return mParser->DefinitionExists(name.mpBegin) != 0;
}

// @ 0x00842470
int cCommandExistsFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 name;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &name);
    pExpr->EvalExpectCharThrow(*p, ')');
    return mParser->CommandExists(name.mpBegin) != 0;
}

// @ 0x00842520
int cEqFunction_s0084_1370::EvalInt(const char** p, EA::ArgScript::cExpression_s0084_1370* pExpr)
{
    string8 a;
    string8 b;
    pExpr->EvalExpectCharThrow(*p, '(');
    pExpr->EvalString(*p, &a);
    pExpr->EvalExpectCharThrow(*p, ',');
    pExpr->EvalString(*p, &b);
    pExpr->EvalExpectCharThrow(*p, ')');
    return String8Equals(&a, &b) != 0;
}
