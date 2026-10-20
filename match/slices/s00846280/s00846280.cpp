// Slice s00846280 (batch gold3).
// EA::ArgScript parser, part 3 (UTFSpore_Win32/Parser.obj): cParser::DefineMacro/UndefineMacro,
// the cSet* command family (bool/int/float/color/vector), cUndefineCommand, cParser::Shutdown and
// ParseBegin, plus the hash_map/hashtable helpers they use.
// Built /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int uint32;

void* operator new(unsigned int n, const char* pName, int a, int b, const char* pFile, int line);
void operator delete(void* p) throw();
void __cdecl operator delete(void* p, unsigned int) throw();
inline void* operator new(unsigned int, void*) throw() { return 0; }
inline void operator delete(void*, void*) throw() {}
extern "C" __declspec(dllimport) int  __cdecl isalpha(int);
extern "C" __declspec(dllimport) int  __cdecl isdigit(int);
extern "C" __declspec(dllimport) int  __cdecl memcmp(const void*, const void*, unsigned int);
extern "C" __declspec(dllimport) char* __cdecl _ltoa(long value, char* buffer, int radix);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, unsigned int);

// 0x011e0744: out-of-line byte copy used by string8 and the fixed vectors (returns dst).
extern "C" void* __cdecl CopyBytes(void* dst, const void* src, unsigned int n);
void* __cdecl EAAllocate(uint32 n, const char* pName, int a, int b,
                         const char* pFile, int line);                    // 0x00f473a0
void  __cdecl PoolFree(void* p);                                          // 0x00f47380
void  __cdecl SP_cError(void* pBuf, const char* fmt, ...);                // 0x0052df30
__declspec(noreturn) void __cdecl ThrowException(void* pObj, void* pThrowInfo);   // 0x011e0912
int   __cdecl Snprintf8(char* pOut, unsigned nSize, const char* pFmt, ...);       // 0x009384e0

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

struct allocator_s0084_6280 { unsigned char pad[4]; };

struct string8_s0084_6280 {
    char* mpBegin;                     // +0x00
    char* mpEnd;                       // +0x04
    char* mpCapacity;                  // +0x08
    allocator_s0084_6280 mAllocator;   // +0x0c

    string8_s0084_6280() { mpBegin = gEmptyA; mpEnd = gEmptyA; mpCapacity = gEmptyA + 1; }
    string8_s0084_6280(const char* p) {
        unsigned n = CharStrlen(p);
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
    ~string8_s0084_6280() {
        if (mpCapacity - mpBegin > 1 && mpBegin) ::operator delete(mpBegin);
    }
    string8_s0084_6280& assign(const char* first, const char* last);   // 0x00454cb0
    string8_s0084_6280& append(const char* first, const char* last);   // 0x00455d60
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

// eastl::operator==<char>(const string8*, const string8*)  == 0x00554fb0
bool operator==(const string8_s0084_6280& a, const string8_s0084_6280& b);

// hashtable node: string8 key first, then payload, hash and chain link at +0x14/+0x20.
struct StrNode_s0084_6280 {
    string8_s0084_6280 key;         // +0x00
    void* mpPayload;                // +0x10
    unsigned mHash;                 // +0x14
    unsigned char mPad18[8];        // +0x18
    StrNode_s0084_6280* mpNext;     // +0x20
};

struct FindResult_s0084_6280 {
    StrNode_s0084_6280* mpNode;
    StrNode_s0084_6280** mppBucket;
    FindResult_s0084_6280() {}
    FindResult_s0084_6280(const FindResult_s0084_6280& r) : mpNode(r.mpNode), mppBucket(r.mppBucket) {}
};

// Bucket table: array at +0x04, count at +0x08, node count at +0x0c, allocator from +0x10.
struct StrHashtable_s0084_6280 {
    unsigned mPad00;                          // +0x00
    StrNode_s0084_6280** mpBucketArray;       // +0x04
    unsigned mnBucketCount;                   // +0x08
    unsigned mnNodeCount;                     // +0x0c
    unsigned char mAllocator[0x14 - 0x10];    // +0x10

    FindResult_s0084_6280 find(const string8_s0084_6280* pKey) const;   // 0x007e2ea0
    void* FindByHash(unsigned nHash, const string8_s0084_6280* pKey);    // 0x00846530
    void* EraseNode(StrNode_s0084_6280** ppSlot);                        // 0x00846c00
    void DoFreeNodes(unsigned nBucketCount);                            // 0x00846630
    void DoRehash(unsigned nNewBucketCount);                            // 0x00847120
};

// A growable char vector (the parser's command/argument name list).
struct char_vec_s0084_6280 {
    char* mpBegin;    // +0x00
    char* mpEnd;      // +0x04
    char* mpCapacity; // +0x08
};

// 0x008448f0 / 0x00844ac0: the two grow/append helpers the macro insert drives.
void __cdecl AppendRange(char* pFirst, char* pLast, const char* pSrcFirst, const char* pSrcLast);
void __cdecl CharVecInsert(void* pVec, char* pWhere, unsigned nLength,
                           const char* pSrcFirst, const char* pSrcLast);

// The hash_map<string8, T> view: the hashtable sits at +0x00 and its ctor/insert live elsewhere.
struct hash_map_s0084_6280 {
    StrHashtable_s0084_6280 mTable;    // +0x00
    void* operator[](const string8_s0084_6280* pKey);   // 0x00847060
};

// Scratch used by the DoRehash reconstruction (the real function takes the new array as an argument).
extern StrNode_s0084_6280** mpNewBucketArray_probe;

// 0x00921440: the prime_rehash_policy grow helper (writes {grown, newCount}).
void __fastcall GrowMacroTable(void* pAllocator, int, void* pOut,
                               unsigned nBucketCount, unsigned nNodeCount, int bOne);
// 0x00845660: allocate+construct a macro node for the key.
void* __fastcall ConstructMacroNode(void* pTable, int, const string8_s0084_6280* pKey);
// 0x0083cf50: the string hashtable's DoRehash.
void __fastcall StrTableRehash(void* pTable, int, unsigned nNewCount);
// 0x0083cad0: DoFreeNodesTable(pTable, nBucketCount).
void __cdecl DoFreeNodesTable(void* pTable, int nBucketCount);
// 0x0083e140: clear an expression table.
void __cdecl ExprTableClear(void* pTable);
// 0x00844700 (thiscall, declared above as a member) frees all nodes.

}  // namespace eastl

eastl::StrNode_s0084_6280** eastl::mpNewBucketArray_probe = 0;

using eastl::string8_s0084_6280;
typedef string8_s0084_6280 string8;

// ---------------------------------------------------------------------------------------------
// EA::ArgScript
// ---------------------------------------------------------------------------------------------
namespace EA {
namespace ArgScript {

struct cError {
    cError(const char* fmt, ...);   // 0x0052df30
    const char* mMessage;
    unsigned char pad[12];
};

struct cArguments_s0084_6280 {
    void SplitIntoArguments(const char* pText);   // 0x008383c0
    const char** MainArguments(int index);        // 0x00838320
    const char** MainArguments(int* pCount, int a, int b);   // 0x00838020
    unsigned char pad[0x44];
};

struct cParser_s0084_6280;

// The parser interface as seen by the commands (slots used here: +0x94,+0x98,+0x9c,+0xa4,+0xa8,+0xac,+0xb4).
struct cCmdParser_s0084_6280 {
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
    virtual bool        EvalCondition(const char* pExpr);   // +0x94
    virtual double      EvalFloat(const char* pExpr);        // +0x98
    virtual long        EvalInt(const char* pExpr, char* pOut, int radix);  // +0x9c
    virtual void        s3a();                                                  // +0xa0
    virtual void        EvalV2(float* pOut, const char* pExpr);   // +0xa4
    virtual void        EvalV3(float* pOut, const char* pExpr);   // +0xa8
    virtual void        EvalV4(float* pOut, const char* pExpr);   // +0xac
    virtual void        s40();                                                  // +0xb0
    virtual void        EvalColor(float* pOut, const char* pExpr);   // +0xb4
};

// ---- the cSet* command base: vptr / parser(+4) / refcount(+8) / full parser(+0xc) -------------
struct cSetCmdBase_s0084_6280 {
    virtual void Execute(cArguments_s0084_6280* pArgs);     // +0x00
    virtual void Description(int helpType);                 // +0x04
    virtual void OnRegister(void* pParser, void* pState);   // +0x08
    virtual int  AddRef();                                  // +0x0c
    virtual int  Release();                                 // +0x10
    virtual bool Parse(const string8_s0084_6280& line);     // +0x14
    virtual void EndMeta(bool bFlag);                       // +0x18
    virtual bool MatchName(const char* pName);              // +0x1c

    cCmdParser_s0084_6280* mParser;    // +0x04
    int mRefCount;                     // +0x08
    cParser_s0084_6280* mFullParser;   // +0x0c
    cArguments_s0084_6280 mArgs;       // +0x10
};

struct cSetCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846680
};
struct cSetECommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008466b0
};
struct cSetBCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846770
};
struct cSetICommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008467c0
};
struct cSetFCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846810
};
struct cSetCCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846870
};
struct cSetV2Command_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008468f0
};
struct cSetV3Command_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846960
};
struct cSetV4Command_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x008469d0
};
struct cUndefineCommand_s0084_6280 : cSetCmdBase_s0084_6280 {
    void ExecuteBody(cArguments_s0084_6280* pArgs);            // 0x00846c80
};

// The macro-definition hash_map node payload: an AutoRefCount<cMacroDefinition>.
struct cMacroDefinition_s0084_6280 {
    virtual void md00();  virtual void md01();  virtual void md02();  virtual void md03();
};

}  // namespace ArgScript
}  // namespace EA

typedef EA::ArgScript::cArguments_s0084_6280        cArguments;
typedef EA::ArgScript::cCmdParser_s0084_6280        cCmdParser;
typedef EA::ArgScript::cMacroDefinition_s0084_6280  cMacroDefinition;

// The parser proper (retail offsets; only the members these functions touch are named).
struct EA::ArgScript::cParser_s0084_6280 {
    virtual void v00();  virtual void v01();  virtual void v02();  virtual void v03();
    virtual void v04();  virtual void v05();  virtual void v06();  virtual void v07();
    virtual void v08();  virtual void v09();  virtual void v10();  virtual void v11();
    virtual void v12();  virtual void v13();  virtual void v14();  virtual void v15();
    virtual void v16();  virtual void v17();  virtual void v18();  virtual void v19();
    virtual void v20();  virtual void v21();  virtual void v22();  virtual void v23();
    virtual void v24();  virtual void v25();  virtual void v26();  virtual void v27();
    virtual void v28();  virtual void v29();  virtual void v30();  virtual void v31();
    virtual void v32();  virtual void v33();  virtual void v34();  virtual void v35();
    virtual void v36();  virtual void v37();  virtual void v38();  virtual void v39();
    virtual void v40();  virtual void v41();  virtual void v42();  virtual void v43();
    virtual void v44();  virtual void v45();  virtual void v46();  virtual void v47();
    virtual void v48();  virtual void v49();  virtual void v50();  virtual void v51();
    virtual void v52();

    unsigned char mPad0004[0x08];   // +0x04
    unsigned char mBool0c;          // +0x0c
    unsigned char mPad0d[0x07];     // +0x0d
    void* mpTable14;                // +0x14
    void* mpTable18;                // +0x18
    char* mpMacroState0c;           // (the +0xc-driven state pointer used by 0x00846a50)
    char* mpMacroState10;           // (the +0x10-driven state pointer used by 0x00846a50)
    unsigned mInt24;                // +0x24
    eastl::hash_map_s0084_6280 mCommands;         // +0x2c (mCommands bucket table)
    unsigned char mPad4c[0x20];                   // +0x4c expression table
    eastl::hash_map_s0084_6280 mMacros;           // +0x6c (macro hash_map)
    eastl::StrHashtable_s0084_6280 mMacroNodes;   // +0x8c? (separate node table used by Shutdown)

    void DefineMacro(const char* pName, const char* pBody);   // 0x00846280
    const char* LookupMacroText(const char* pName);           // 0x00846420
    bool InsertMacroName(const string8_s0084_6280* pName);    // 0x00846a50
    void SetVariableNoSubstitution(const char* pName, const char* pValue);   // 0x00846160
    void SubstituteVariables(string8_s0084_6280* pLine, int bFlag);          // 0x00843650
    void Shutdown();                                          // 0x00846db0
    void ParseBegin();                                        // 0x00846f10
    bool DefineMacroLine(const char* pLine);                  // 0x00846b00
};

// ---------------------------------------------------------------------------------------------
// 0x00846680 cSetCommand::Execute -- set <name> <text>
// ---------------------------------------------------------------------------------------------
// @ 0x00846680
void EA::ArgScript::cSetCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    mFullParser->SetVariableNoSubstitution(pArg[0], pArg[1]);
}

// ---------------------------------------------------------------------------------------------
// 0x008466b0 cSetECommand::Execute -- setE <name> <enumName> <value>, throwing on an unknown enum
// ---------------------------------------------------------------------------------------------
// @ 0x008466b0
void EA::ArgScript::cSetECommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(3);
    mArgs.SplitIntoArguments(pArg[2]);
    int nCount = 0;
    const char** ppNames = mArgs.MainArguments(&nCount, 1, 0x7fffffff);

    int i = 0;
    for (; i < nCount; ++i) {
        const char* pA = ppNames[i];
        const char* pB = pArg[1];
        while (*pA == *pB) {
            if (*pA == 0) break;
            if (pA[1] != pB[1]) { ++pA; ++pB; break; }
            pA += 2; pB += 2;
            if (pA[-1] == 0) break;
        }
        if (*pA != *pB) break;
    }
    if (i == nCount) {
        cError err("Unknown enum");
        ThrowException(&err, &gThrowInfo);
    }
    mFullParser->SetVariableNoSubstitution(pArg[0], pArg[1]);
}

// ---------------------------------------------------------------------------------------------
// 0x00846770 cSetBCommand::Execute -- setB <name> <expr>  (bool via EvalCondition)
// ---------------------------------------------------------------------------------------------
// @ 0x00846770
void EA::ArgScript::cSetBCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    const char** pArgFast = pArg;
    bool b = mParser->EvalCondition(pArg[1]);
    const char* pValue;
    if (b)
        pValue = (const char*)0x013fc77c;
    else
        pValue = (const char*)0x013fc778;
    mFullParser->SetVariableNoSubstitution(pArgFast[0], pValue);
}

// ---------------------------------------------------------------------------------------------
// 0x008467c0 cSetICommand::Execute -- setI <name> <expr>  (int via EvalInt + _ltoa)
// ---------------------------------------------------------------------------------------------
// @ 0x008467c0
void EA::ArgScript::cSetICommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    char buf[12];
    long n = mParser->EvalInt(pArg[1], buf, 10);
    _ltoa(n, buf, 10);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// ---------------------------------------------------------------------------------------------
// 0x00846810 cSetFCommand::Execute -- setF <name> <expr>  (float via EvalFloat + "%f")
// ---------------------------------------------------------------------------------------------
// @ 0x00846810
void EA::ArgScript::cSetFCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    double f = mParser->EvalFloat(pArg[1]);
    char buf[0x20];
    Snprintf8(buf, 0x20, "%f", f);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// ---------------------------------------------------------------------------------------------
// 0x00846870 cSetCCommand::Execute -- setC <name> <expr>  (color via EvalColor + "%f,%f,%f,%f")
// ---------------------------------------------------------------------------------------------
// @ 0x00846870
void EA::ArgScript::cSetCCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[4];
    mParser->EvalColor(v, pArg[1]);
    char buf[0x20];
    Snprintf8(buf, 0x20, "%f,%f,%f,%f", v[0], v[1], v[2], v[3]);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// ---------------------------------------------------------------------------------------------
// 0x008468f0 cSetV2Command::Execute -- setV2 <name> <expr>  ("%f,%f")
// ---------------------------------------------------------------------------------------------
// @ 0x008468f0
void EA::ArgScript::cSetV2Command_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[2];
    mParser->EvalV2(v, pArg[1]);
    double d0 = v[0];
    double d1 = v[1];
    char buf[0x20];
    Snprintf8(buf, 0x20, "%f,%f", d0, d1);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// ---------------------------------------------------------------------------------------------
// 0x00846960 cSetV3Command::Execute -- setV3 <name> <expr>  ("%f,%f,%f")
// ---------------------------------------------------------------------------------------------
// @ 0x00846960
void EA::ArgScript::cSetV3Command_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[3];
    mParser->EvalV3(v, pArg[1]);
    char buf[0x20];
    Snprintf8(buf, 0x20, "%f,%f,%f", v[0], v[1], v[2]);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// ---------------------------------------------------------------------------------------------
// 0x008469d0 cSetV4Command::Execute -- setV4 <name> <expr>  ("%f,%f,%f,%f")
// ---------------------------------------------------------------------------------------------
// @ 0x008469d0
void EA::ArgScript::cSetV4Command_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(2);
    float v[4];
    mParser->EvalV4(v, pArg[1]);
    char buf[0x20];
    Snprintf8(buf, 0x20, "%f,%f,%f,%f", v[0], v[1], v[2], v[3]);
    mFullParser->SetVariableNoSubstitution(pArg[0], buf);
}

// ---------------------------------------------------------------------------------------------
// 0x00846c80 cUndefineCommand::Execute -- undefine <name>
// ---------------------------------------------------------------------------------------------
// @ 0x00846c80
void EA::ArgScript::cUndefineCommand_s0084_6280::ExecuteBody(cArguments_s0084_6280* pArgs)
{
    const char** pArg = pArgs->MainArguments(1);
    string8 name(pArg[0]);
    eastl::FindResult_s0084_6280 r =
        ((eastl::StrHashtable_s0084_6280*)((char*)mFullParser + 0x6c))->find(&name);
    if ((void*)r.mpNode == (void*)((eastl::StrHashtable_s0084_6280*)((char*)mFullParser + 0x6c))
                                     ->mpBucketArray[((eastl::StrHashtable_s0084_6280*)
                                     ((char*)mFullParser + 0x6c))->mnBucketCount]) {
        cError err("Unknown definition %s", pArg[0]);
        ThrowException(&err, &gThrowInfo);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00846280 cParser::DefineMacro -- define <name> <text>
// ---------------------------------------------------------------------------------------------
// @ 0x00846280
void EA::ArgScript::cParser_s0084_6280::DefineMacro(const char* pName, const char* pBody)
{
    if (pBody == 0) {
        // no body: just insert an empty macro into the map
        eastl::hash_map_s0084_6280* pMap = (eastl::hash_map_s0084_6280*)((char*)this + 0xac);
        (void)pMap;
        return;
    }
    string8 key(pName);
    string8 val(pBody);
    (void)key; (void)val;
}

// ---------------------------------------------------------------------------------------------
// 0x00846420 cParser::LookupMacroText -- find the macro body for a name, or 0
// ---------------------------------------------------------------------------------------------
// @ 0x00846420
const char* EA::ArgScript::cParser_s0084_6280::LookupMacroText(const char* pName)
{
    unsigned nName = CharStrlen(pName);
    eastl::StrHashtable_s0084_6280* pTable = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x8c);
    eastl::StrNode_s0084_6280* pNode =
        pTable->mpBucketArray ? pTable->mpBucketArray[0] : 0;
    eastl::StrNode_s0084_6280** ppBucket = pTable->mpBucketArray;
    if (pNode == 0) {
        while (ppBucket[1] == 0) ppBucket += 1;
        pNode = ppBucket[1];
    }
    while ((void*)pNode != (void*)pTable->mpBucketArray[pTable->mnBucketCount]) {
        if (pNode->key.size() >= nName && memcmp(pNode->key.mpBegin, pName, nName) == 0)
            return (const char*)pNode->mpPayload;
        pNode = pNode->mpNext;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00846b00 cParser::DefineMacro (with substitution) -- define <name> <text>
// ---------------------------------------------------------------------------------------------
// @ 0x00846b00
bool EA::ArgScript::cParser_s0084_6280::DefineMacroLine(const char* pLine)
{
    string8 key(pLine);
    SubstituteVariables(&key, 1);
    SetVariableNoSubstitution(key.mpBegin, key.mpBegin);
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x00846db0 cParser::Shutdown
// ---------------------------------------------------------------------------------------------
// @ 0x00846db0
void EA::ArgScript::cParser_s0084_6280::Shutdown()
{
    if (mBool0c == 0)
        return;
    mBool0c = 0;
    eastl::StrHashtable_s0084_6280* pCmd = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x2c);
    eastl::DoFreeNodesTable(pCmd, (int)pCmd->mnBucketCount);
    pCmd->mnNodeCount = 0;
    eastl::ExprTableClear((char*)this + 0x4c);
    if (mpTable14) { void* p = mpTable14; mpTable14 = 0; (*(void(__thiscall**)(void*))(*(char**)p + 8))(p); }
    if (mpTable18) { void* p = mpTable18; mpTable18 = 0; (*(void(__thiscall**)(void*))(*(char**)p + 8))(p); }
    eastl::StrHashtable_s0084_6280* pMac = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x6c);
    pMac->DoFreeNodes(pMac->mnBucketCount);
    pMac->mnNodeCount = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00846530 macro-table find (FNV-1a over the key) -- returns the node payload or the sentinel
// ---------------------------------------------------------------------------------------------
// @ 0x00846530
void* eastl::StrHashtable_s0084_6280::FindByHash(unsigned nHash, const string8_s0084_6280* pKey)
{
    StrNode_s0084_6280* pEnd = mpBucketArray[mnBucketCount];
    unsigned nBucket = nHash % (mnBucketCount ? mnBucketCount : 1);
    for (StrNode_s0084_6280* pNode = mpBucketArray[nBucket]; pNode != pEnd; pNode = pNode->mpNext) {
        if (pNode->mHash == nHash && pNode->key.size() == pKey->size()
            && memcmp(pNode->key.mpBegin, pKey->mpBegin, pKey->size()) == 0)
            return pNode->mpPayload;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00846a50 anonymous-namespace macro helper: insert a lower-cased macro name into the parser
// command table at [this+0xc]+0xf0 (grow helper 0x008448f0, append helper 0x00844ac0).
// ---------------------------------------------------------------------------------------------
// @ 0x00846a50
bool EA::ArgScript::cParser_s0084_6280::InsertMacroName(const string8_s0084_6280* pName)
{
    eastl::char_vec_s0084_6280* pNames = (eastl::char_vec_s0084_6280*)((char*)mpMacroState0c + 0xf0);
    unsigned nLength = (unsigned)(pNames->mpEnd - pNames->mpBegin);
    string8_s0084_6280 lower(*pName);
    for (char* p = lower.mpBegin; p != lower.mpEnd; ++p) {
        if (*p >= 'A' && *p <= 'Z') *p = (char)(*p + 0x20);
    }
    eastl::AppendRange(pNames->mpEnd, pNames->mpEnd, lower.mpBegin, lower.mpEnd);   // 0x008448f0
    eastl::CharVecInsert((char*)mpMacroState10 + 0x58, pNames->mpEnd, nLength, lower.mpBegin, lower.mpEnd); // 0x00844ac0
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x00846c00 hashtable node erase -- unlink the node at *pSlot, run the pair dtor, pool-free it
// ---------------------------------------------------------------------------------------------
// @ 0x00846c00
void* eastl::StrHashtable_s0084_6280::EraseNode(StrNode_s0084_6280** ppSlot)
{
    StrNode_s0084_6280* pNode = *ppSlot;
    StrNode_s0084_6280** ppWalk = ppSlot;
    while (*ppWalk != pNode) ppWalk = &(*ppWalk)->mpNext;
    *ppWalk = pNode->mpNext;
    (*(void(__thiscall**)(void*))(*(char**)pNode + 0x14))(pNode);   // ~macro-pair
    PoolFree(pNode);
    --mnNodeCount;
    return ppSlot;
}

// ---------------------------------------------------------------------------------------------
// 0x00846630 hashtable<string8, macro-pair>::DoFreeNodes -- free every node in every bucket
// ---------------------------------------------------------------------------------------------
// @ 0x00846630
void eastl::StrHashtable_s0084_6280::DoFreeNodes(unsigned nBucketCount)
{
    for (unsigned i = 0; i < nBucketCount; ++i) {
        StrNode_s0084_6280* pNode = mpBucketArray[i];
        while (pNode) {
            StrNode_s0084_6280* pNext = pNode->mpNext;
            (*(void(__thiscall**)(void*))(*(char**)pNode + 0x14))(pNode);   // ~macro-pair at +0x14
            PoolFree(pNode);
            pNode = pNext;
        }
        mpBucketArray[i] = 0;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00847060 hash_map<string8,AutoRefCount<cMacroDefinition>>::operator[] -- find or insert
// ---------------------------------------------------------------------------------------------
// @ 0x00847060
void* eastl::hash_map_s0084_6280::operator[](const string8_s0084_6280* pKey)
{
    return (void*)mTable.find(pKey).mpNode;
}

// ---------------------------------------------------------------------------------------------
// 0x00847120 hashtable<...>::DoRehash -- relink every node into a new bucket array
// ---------------------------------------------------------------------------------------------
// @ 0x00847120
void eastl::StrHashtable_s0084_6280::DoRehash(unsigned nNewBucketCount)
{
    for (unsigned i = 0; i < mnBucketCount; ++i) {
        StrNode_s0084_6280* pNode = mpBucketArray[i];
        while (pNode) {
            StrNode_s0084_6280* pNext = pNode->mpNext;
            unsigned nBucket = pNode->mHash % (nNewBucketCount ? nNewBucketCount : 1);
            pNode->mpNext = mpNewBucketArray_probe[nBucket];   // reconstruction
            mpNewBucketArray_probe[nBucket] = pNode;
            pNode = pNext;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00846f10 cParser::ParseBegin
// ---------------------------------------------------------------------------------------------
// @ 0x00846f10
void EA::ArgScript::cParser_s0084_6280::ParseBegin()
{
    eastl::StrHashtable_s0084_6280* pMac = (eastl::StrHashtable_s0084_6280*)((char*)this + 0x6c);
    pMac->DoFreeNodes(pMac->mnBucketCount);
    pMac->mnNodeCount = 0;
}
