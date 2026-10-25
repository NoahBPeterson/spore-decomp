// Slice s00674640 - XHTML detokenizer, Spore guide page loader, achievement-test cheat
// helpers, and a cVar-list serializer.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"

struct VObj { void** vt; };
typedef void   (__thiscall *FnV0)(void*);
typedef void   (__thiscall *FnV1)(void*);
typedef void   (__thiscall *FnV1i)(void*, int);
typedef void   (__thiscall *FnV2ip)(void*, int, void*);
typedef void   (__thiscall *FnV3pii)(void*, void*, int, int);
typedef void   (__thiscall *FnV3ipi)(void*, void*, int, void*);
typedef void*  (__thiscall *FnVp0)(void*);
typedef int    (__thiscall *FnVi0)(void*);
typedef bool   (__thiscall *FnVb2ip)(void*, void*, int);
typedef void   (__thiscall *FnV2pp)(void*, void*, void*);
typedef void   (__thiscall *FnV1p)(void*, void*);

void DeleteObj(void* p);   // 0x00f47380

// ---- external callees -------------------------------------------------
void* __cdecl PropertyManager();          // 0x0067de30
void* __cdecl GetMessagingServer();       // 0x00883860
void* __cdecl GetCheatManager();          // 0x0067de20
void  __cdecl FUN_0067cbe0(int a);
void  __cdecl FUN_005fe1d0();
void* __cdecl GetSaveArea(int a);         // 0x006b1f90
void* __cdecl ZoneObjNew(unsigned n, const char* name, int a, int b, int c, int d); // 0x00926020
void* __cdecl ObjectDbCtor(void* db, void* save);  // 0x0069fa60
void  __cdecl FUN_0069e210(void* p);
char  __cdecl FUN_0069e260(void* p, void* key, int a);
void  __cdecl FUN_0069d860(void* p);
void  __cdecl FUN_0069d8e0(void* p);
extern void* g_achievement_test_str;      // [0x0152906c]

// ---- 0x00674640 : cBuildXHTMLDetokenizer::TranslateToken -------------
// Translates one markup token (a name from a guide page) into text appended to `out`.
#include <string.h>
#include <wchar.h>
#pragma intrinsic(strlen, wcscmp, wcslen)

struct TWStr {                       // eastl::basic_string<wchar_t, eastl::allocator>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCap;
    int      mAlloc;
    void append(const wchar_t* p);                    // 0x005c3d90
    void append(const wchar_t* b, const wchar_t* e);  // 0x00672750 (insert range)
    void operator_assign(const TWStr* o);             // 0x0057cb60 (operator=)
    void assign(const wchar_t* b, const wchar_t* e);  // 0x00423650
    void resize(unsigned n);                          // 0x00429520
    void appendPtr(const wchar_t* p);                 // 0x00599bb0 (operator+=)
    void assign_n(unsigned n, wchar_t c);             // 0x00674230 (fill assign)
    void append_n(unsigned n, wchar_t c);             // 0x0042d2e0
};
struct TWStrLocal : TWStr {
    ~TWStrLocal() { if ((((char*)mpCap - (char*)mpBegin) & ~1) > 2 && mpBegin) DeleteObj(mpBegin); }
};
struct TCStr {                       // narrow string, begin/end/cap
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    ~TCStr() { if ((mpCap - mpBegin) > 1 && mpBegin) DeleteObj(mpBegin); }
};
struct TFStr32 {                     // eastl::fixed_string<wchar_t,32,1>, 0x54 bytes
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCap;
    int      mAlloc;
    wchar_t* mpInline;
    wchar_t  mBuf[32];
    void Construct(const wchar_t* s);                 // 0x006743f0
    void AssignCStr(const wchar_t* s);                // 0x008369e0
};
struct TFStrLocal : TFStr32 {
    ~TFStrLocal() { if ((((char*)mpCap - (char*)mpBegin) & ~1) > 2 && mpBegin && mpBegin != mpInline) DeleteObj(mpBegin); }
};
struct TVar;
struct TVarVec {                     // fixed_vector of TVar (begin/end/cap)
    TVar* mpBegin;
    TVar* mpEnd;
    TVar* mpCap;
    int   mAlloc;
    void DoInsertValue(TVar* pos, const TVar* v);     // 0x00673b00
};
struct TFStrVec {                    // fixed_vector<TFStr32,8,1> at TVar+0x384
    char hdr[0x18];
    void push_back(const TFStr32* s);                 // 0x006745d0
};
struct TActionVec {                  // fixed_vector<cAction,8,1> at TVar+0xac
    char hdr[0x18];
    void assign(const TActionVec* o);                 // 0x00673810
};
struct TVar {                        // cBuildXHTMLDetokenizer::cVar, 0x63c bytes
    int        id;                   // +0x00
    TFStr32    value;                // +0x04
    TFStr32    text;                 // +0x58
    TActionVec actions;              // +0xac
    char       actBuf[0x2c0];
    TFStrVec   params;               // +0x384
    char       parBuf[0x2a0];
    TVar* Init();                    // 0x006732e0 (default ctor, returns this)
    void CopyConstruct(const TVar* o);   // 0x00673870
    void Destroy();                  // 0x00673360
};

class TArgs {                        // EA::ArgScript::cArguments, 0x38 bytes
public:
    char mData[0x40];
    TArgs(const char* text);                                                  // 0x008386d0
    void GatherUnprocessed(void* outList);                                    // 0x00838350
    const char** OptionArguments(const char* name, int* pCount, int a, int b);   // 0x00838130
    ~TArgs();                                                                 // 0x00837fa0
};
struct TArgList {                    // eastl::vector<const char*, sp_vector_allocator>
    const char** mpBegin;
    const char** mpEnd;
    const char** mpCap;
    int          mAlloc;
    ~TArgList() { if (mpBegin && ((int*)mpBegin)[-1]) DeleteObj(mpBegin); }
};
extern wchar_t gEmptyWStr[];                              // 0x01667bac (shared empty eastl string)
struct TPropList { bool GetDescription(unsigned id); };   // 0x006a25a0
extern TPropList* g_pAppProperties;                       // [0x015fd918]
struct TString {                     // SP::cString, 0x1c bytes
    unsigned mData[7];
    TString();                                            // 0x006b5060
    ~TString();                                           // 0x006b5240
    bool Load(unsigned table, unsigned inst, const wchar_t* def);   // 0x006b54b0
    const wchar_t* GetText();                             // 0x006b55c0
};
int  __cdecl Sprintf16T(wchar_t* dst, const wchar_t* fmt, ...);               // 0x009399c0
void __cdecl GetDataPathT(unsigned id, TWStr* out, int flag);                 // 0x00688830
TWStr* __cdecl ConvertToString16T(TWStr* out, const char* s, int n);          // 0x0093c5a0
TCStr* __cdecl ConvertToString8T(TCStr* out, const TWStr* s);                 // 0x0093c570
unsigned __cdecl FNV1_String8T(const char* s, unsigned basis, int flag);      // 0x00932e80

inline void AssignLit(TWStr& s, const wchar_t* lit) { const wchar_t* p = lit; while (*p) ++p; s.assign(lit, lit + (p - lit)); }

struct Detokenizer {
    char    pad0[0x60];
    int     mState;            // +0x60
    char    pad64[0x10];
    TWStr   str74;             // +0x74
    TWStr   str84;             // +0x84
    char    pad94[4];
    TVar*   mpCurVar;          // +0x98
    TVar*   mpCurAux;          // +0x9c
    TVarVec vars;              // +0xa0
    char    padB0[0x6478 - 0xb0];
    TVar*   mpDefsBegin;       // +0x6478
    TVar*   mpDefsEnd;         // +0x647c

    TVar* FindVar(TVarVec* v, const wchar_t* key);   // 0x006741b0
    bool  TranslateToken(const wchar_t* token, TWStr& out);
};
// @ 0x00674640
bool Detokenizer::TranslateToken(const wchar_t* token, TWStr& out)
{
    if (wcscmp(token, L"br") == 0) {
        AssignLit(out, L"<br/>");
        return true;
    }
    if (wcscmp(token, L"p") == 0) {
        AssignLit(out, L"<p/>");
        return true;
    }
    if (wcscmp(token, L"save_path") == 0) {
        if (g_pAppProperties->GetDescription(0x61b67b6)) {
            TString s;
            wchar_t buf[260];
            s.Load(0x19f76d11, 0x5ca8d97, L"My Spore Creations");
            Sprintf16T(buf, L"%s", s.GetText());
            out.append(buf);
        } else {
            TWStrLocal path;
            path.mpBegin = gEmptyWStr;
            path.mpEnd = gEmptyWStr;
            path.mpCap = gEmptyWStr + 1;
            GetDataPathT(0xa0214b, &path, 0);
            out.append(path.mpBegin);
        }
        return true;
    }
    if (wcscmp(token, L"mac_save_append") == 0) {
        if (g_pAppProperties->GetDescription(0x61b67b6)) {
            TString s;
            wchar_t buf[260];
            s.Load(0x19f76d11, 0x61b68c1, L"***");
            Sprintf16T(buf, L" %s", s.GetText());
            out.append(buf);
        } else {
            out.append(L"");
        }
        return true;
    }

    if (mState == 0) {
        const wchar_t* colon = wcschr(token, L':');
        if (colon && wcsncmp(token, L"guide", colon - token) != 0)
            token = colon + 1;
        str74.append(token);
        TCStr narrow;
        ConvertToString8T(&narrow, &str74);
        TArgs args(narrow.mpBegin);
        TArgList list;
        list.mpBegin = 0; list.mpEnd = 0; list.mpCap = 0;
        args.GatherUnprocessed(&list);
        for (unsigned idx = 0; idx < (unsigned)(list.mpEnd - list.mpBegin); ++idx) {
            TVar tmp;
            TVar* t = tmp.Init();
            if (vars.mpEnd < vars.mpCap) {
                TVar* e = vars.mpEnd;
                vars.mpEnd = e + 1;
                if (e)
                    e->CopyConstruct(t);
            } else {
                vars.DoInsertValue(vars.mpEnd, t);
            }
            tmp.Destroy();
            TVar* v = vars.mpEnd - 1;
            v->id = FNV1_String8T(list.mpBegin[idx], 0x811c9dc5, 1);
            int count;
            const char** vals = args.OptionArguments(list.mpBegin[idx], &count, 0, 0x7fffffff);
            for (int j = 0; j < count; ++j) {
                if (j == 0) {
                    TWStrLocal w;
                    const char* s = vals[0];
                    v->value.AssignCStr(ConvertToString16T(&w, s, (int)strlen(s))->mpBegin);
                } else {
                    TWStrLocal w;
                    const char* s = vals[j];
                    TFStrLocal fs;
                    fs.Construct(ConvertToString16T(&w, s, (int)strlen(s))->mpBegin);
                    v->params.push_back(&fs);
                }
            }
            for (TVar* d = mpDefsBegin; d != mpDefsEnd; d = (TVar*)((char*)d + 0x63c)) {
                if (d->id == v->id) {
                    v->actions.assign(&d->actions);
                    break;
                }
            }
        }
        out.resize(0);
        mpCurAux = 0;
        mpCurVar = 0;
        mState = 1;
        return true;
    }
    if (mState == 1 && mpCurVar && mpCurAux) {
        if (wcscmp(token, L"text") == 0) {
            out.operator_assign(&str84);
            return true;
        }
        if (wcscmp(token, L"value") == 0) {
            if (mpCurVar->value.mpBegin != mpCurVar->value.mpEnd) {   // not empty
                out.append(mpCurVar->value.mpBegin);
                return true;
            }
        } else if (FindVar(&vars, token) == mpCurVar) {
            out.append(mpCurVar->text.mpBegin);
            return true;
        }
    }
    out.assign_n(1, L'~');
    out.appendPtr(token);
    out.append_n(1, L'~');
    return true;
}

// ---- 0x00674d30 : Detokenize ----------------------------------------
struct EString16 {
    void* mpBegin;    // +0
    void* mpEnd;      // +4
    void* mpCapacity; // +8
    void* mAlloc;     // +0xc
    void  Resize(int n);                               // 0x00429520
    void  Assign(unsigned short* b, unsigned short* e); // 0x00423650
};
struct CVarVec {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    void  erase(void* first, void* last);              // 0x00673a90
};
struct Detok2 {
    char pad0[0x60];
    int  m60;             // +0x60
    char pad64[0x10];     // +0x64..0x74
    EString16 str74;      // +0x74
    EString16 str84;      // +0x84
    void* mp94;           // +0x94
    char pad98[8];        // +0x98..0xa0
    CVarVec vecA0;        // +0xa0
    void detokenize();    // 0x006729d0

    void Detokenize(const unsigned short* s, void* a2);
};
// @ 0x00674d30
void Detok2::Detokenize(const unsigned short* s, void* a2) {
    mp94 = 0;
    str84.Resize(0);
    str74.Resize(0);
    vecA0.erase(vecA0.mpBegin, vecA0.mpEnd);
    m60 = 0;
    const unsigned short* p = s;
    while (*p) ++p;
    str84.Assign((unsigned short*)s, (unsigned short*)(s + (p - s)));
    mp94 = a2;
    detokenize();
}

// ---- 0x00674dc0 : sBuildXHTMLDocument --------------------------------
struct ResKey {
    unsigned mInstance;   // +0
    unsigned mType;       // +4
    unsigned mGroup;      // +8
};

typedef char  (__thiscall *FnGetProperty)(void*, unsigned, unsigned, void**);
typedef char  (__thiscall *FnGetResource)(void*, ResKey*, void**, int, int, int, int);
typedef void* (__thiscall *FnFindObject)(void*, unsigned);
typedef char  (__thiscall *FnNextEntry)(void*, void*, void**, void**);
typedef void  (__thiscall *FnReleaseObject)(void*);

void* __cdecl GetResourceManager();                                       // 0x008de1a0
bool  __cdecl GetPropertyAsString16(void* list, unsigned id, void* out);  // 0x006a1400
void  __cdecl PackDataIntoURIString(TWStr* out, const wchar_t* data, int nbytes,
                                    const wchar_t* mime, int a, int b);   // 0x00837360

// intrusive ref-counted pointer local, same shape as the engine's AutoRefCount
struct AutoRef {
    void* mpObject;   // +0
    AutoRef() {}
    ~AutoRef() { if (mpObject) ((FnReleaseObject)((VObj*)mpObject)->vt[1])(mpObject); }
    void** AsPointer() {
        if (mpObject) {
            void* p = mpObject;
            mpObject = 0;
            ((FnReleaseObject)((VObj*)p)->vt[1])(p);
        }
        return &mpObject;
    }
};

struct ResIter {                 // resource enumeration cursor, 8 bytes
    unsigned mData[2];
    void Ctor();                 // 0x00b90720
};

struct BuildDetokenizer {        // cBuildXHTMLDetokenizer, 0xc850 bytes
    unsigned mData[0xc850 / 4];
    void Ctor(void* props);                              // 0x00673c50
    void Dtor();                                        // 0x00673710
    void Detokenize(const unsigned short* s, void* a2);  // 0x00674d30
};

static __inline unsigned WStrLen(const wchar_t* s) {   // inlined scan used by the appends
    const wchar_t* p = s;
    while (*p) ++p;
    return (unsigned)(p - s);
}

struct StrSlot : TWStr {          // engine EString with its explicit range destructor
    void Destroy() {
        if ((((char*)mpCap - (char*)mpBegin) & ~1) > 2 && mpBegin)
            DeleteObj(mpBegin);
    }
};
struct BuildLocals {              // frame block: cursor, three decoded strings, resource key
    ResIter it;     // +0x00
    StrSlot head;   // +0x08
    StrSlot body;   // +0x18
    StrSlot tail;   // +0x28
    ResKey  key;    // +0x38
};

// @ 0x00674dc0
bool __cdecl sBuildXHTMLDocument(unsigned instance, TWStr* out)
{
    out->resize(0);

    AutoRef props;
    props.mpObject = 0;
    void* pm = PropertyManager();
    ((FnGetProperty)((VObj*)pm)->vt[0x2c / 4])(pm, 0x3bc56e83, 0x41bbeb9, props.AsPointer());

    AutoRef res;
    void* k;
    void* v;

    BuildLocals loc;
    loc.key.mInstance = instance;
    loc.key.mType = 0x2fac0b6;
    loc.key.mGroup = 0x2fabf01;
    res.mpObject = 0;

    void* rm = GetResourceManager();
    ((FnGetResource)((VObj*)rm)->vt[0xc / 4])(rm, &loc.key, res.AsPointer(), 0, 0, 0, 0);

    void* obj = 0;
    if (res.mpObject)
        obj = ((FnFindObject)((VObj*)res.mpObject)->vt[0xc / 4])(res.mpObject, 0x30410fc);
    if (!obj)
        return false;

    BuildDetokenizer detok;
    detok.Ctor(props.mpObject);

    loc.body.mpBegin = gEmptyWStr;
    loc.body.mpEnd = gEmptyWStr;
    loc.body.mpCap = gEmptyWStr + 1;
    loc.head.mpBegin = gEmptyWStr;
    loc.head.mpEnd = gEmptyWStr;
    loc.head.mpCap = gEmptyWStr + 1;

    GetPropertyAsString16(props.mpObject, 0x14d9cf40, &loc.head);
    out->append(loc.head.mpBegin, loc.head.mpBegin + WStrLen(loc.head.mpBegin));

    loc.it.Ctor();
    k = 0;
    v = 0;
    while (((FnNextEntry)((VObj*)obj)->vt[0x1c / 4])(obj, &loc.it, &k, &v)) {
        detok.Detokenize((const unsigned short*)k, &loc.body);
        out->append(loc.body.mpBegin, loc.body.mpBegin + WStrLen(loc.body.mpBegin));
    }

    loc.tail.mpBegin = gEmptyWStr;
    loc.tail.mpEnd = gEmptyWStr;
    loc.tail.mpCap = gEmptyWStr + 1;
    GetPropertyAsString16(props.mpObject, 0x1f92fc44, &loc.tail);
    out->append(loc.tail.mpBegin, loc.tail.mpBegin + WStrLen(loc.tail.mpBegin));

    loc.tail.Destroy();
    loc.head.Destroy();
    loc.body.Destroy();
    detok.Dtor();
    return true;
}
// ---- 0x00675080 : cSPUISporeGuidePage::LoadSporeGuidePage ------------
struct TFStr1024 : TWStr {        // eastl::fixed_string<wchar_t,1024,1>, 0x814 bytes
    wchar_t* mpInline;            // +0x10
    wchar_t  mBuf[1024];          // +0x14
    TFStr1024() {
        mpInline = mBuf;
        mpEnd = mBuf;
        mpBegin = mBuf;
        mpCap = mBuf + 1024;
        mBuf[0] = 0;
    }
    ~TFStr1024() {
        if ((((char*)mpCap - (char*)mpBegin) & ~1) > 2 && mpBegin && mpBegin != mpInline)
            DeleteObj(mpBegin);
    }
};

struct GuideFrame {
    void SetScrollPosition(float* pos);   // 0x00993490
};
struct GuideFrameSet {
    char mData[0x64];
    bool HandleLocationChange(void* frame, const wchar_t* uri, int a, int b);  // 0x00997730
};
struct GuidePage {
    char         pad0[8];
    GuideFrameSet mFrameSet;   // +8
    GuideFrame*  mpFrame;      // +0x6c
    void LoadSporeGuidePage(unsigned instance);
};

// @ 0x00675080
void GuidePage::LoadSporeGuidePage(unsigned instance)
{
    if (!mpFrame)
        return;
    TFStr1024 html;
    if (sBuildXHTMLDocument(instance, &html)) {
        TWStrLocal uri;
        int nbytes = (int)wcslen(html.mpBegin) * 2;
        PackDataIntoURIString(&uri, html.mpBegin, nbytes, L"text/html", 0x10, 0);
        void* frame = mpFrame ? (void*)((char*)mpFrame + 4) : 0;
        mFrameSet.HandleLocationChange(frame, uri.mpBegin, 0, 0);
    }
    {
        float pos[2] = {0.0f, 0.0f};
        mpFrame->SetScrollPosition(pos);
    }
}

// ---- 0x006751a0 ------------------------------------------------------
// @ 0x006751a0
void __stdcall FUN_006751a0(void* a, void* b) {
    void* pm = PropertyManager();
    ((FnV3ipi)((VObj*)pm)->vt[0x2c / 4])(pm, a, 0x5befd27, b);
}

// ---- 0x006751c0 ------------------------------------------------------
// @ 0x006751c0
bool __stdcall FUN_006751c0(unsigned* p) {
    switch ((*p >> 8) & 7) {
    case 0: return p[1] >= p[2];
    case 1: return p[1] > p[2];
    case 2: return p[1] == p[2];
    case 3: return p[1] < p[2];
    case 4: return p[1] <= p[2];
    case 5: return p[1] != p[2];
    default: return false;
    }
}

// ---- 0x00675260 : cVar-list serialization (complete, non-matching) ---
extern void EA_IO_WriteUint32(void* w, void* p, int n, int a); // 0x0093aa70

void WriteIntVal(int* io, int v) {
    int* o = (int*)((FnVp0)((VObj*)io)->vt[0x20 / 4])(io);
    void* w = (void*)((FnVp0)((VObj*)o)->vt[0x18 / 4])(o);
    EA_IO_WriteUint32(w, &v, 1, 0);
}
struct cVarListSerializer {
    char data[0x18];
    cVarListSerializer(void* owner, void* key, int id);  // 0x00692f90
    void Serialize(int* io);                             // 0x00692900
};
struct CVarList {
    char pad[0xc];
    int* mpBegin;  // +0xc
    int* mpEnd;    // +0x10
    void Serialize(int* io);
};
extern char g_1529330;   // [0x01529330]
// @ 0x00675260
void CVarList::Serialize(int* io) {
    WriteIntVal(io, 1);
    WriteIntVal(io, (mpEnd - mpBegin) >> 4);
    for (int* p = mpBegin; p != mpEnd; p += 4) {
        WriteIntVal(io, p[0]);
        WriteIntVal(io, p[2]);
    }
    cVarListSerializer s((void*)this, &g_1529330, 0x1a80d26);
    s.Serialize(io);
}

// ---- 0x00675370 ------------------------------------------------------
// @ 0x00675370
int __fastcall FUN_00675370(char* p) {
    if (p[0x24] == 0) return *(int*)(p + 8) + 0x3c;
    return (int)(p + 0x28);
}

// ---- 0x006753a0 ------------------------------------------------------
// @ 0x006753a0
void __fastcall FUN_006753a0(char* p) {
    void* srv = GetMessagingServer();
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, p, 0x212d3e7, -0x270f);
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, p, 0x238de9c, -0x270f);
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, p, 0x4bef1e3, -0x270f);
    void* cm = GetCheatManager();
    ((FnV1i)((VObj*)cm)->vt[0x1c / 4])(cm, (int)g_achievement_test_str);
    void* a = *(void**)(p + 8);
    if (a) {
        *(void**)(p + 8) = 0;
        ((FnV1)((VObj*)a)->vt[1])(a);
    }
    if (*(void**)(p + 4)) {
        FUN_0067cbe0(0);
        FUN_005fe1d0();
        void* b = *(void**)(p + 4);
        if (b) {
            *(void**)(p + 4) = 0;
            ((FnV1)((VObj*)b)->vt[2])(b);
        }
    }
}

// ---- 0x00675440 : deserialize cVar list (complete, non-matching) -----
struct SerObj {
    char pad[0xc];
    char* mpBegin;  // +0xc
    char* mpEnd;    // +0x10
    unsigned Read(int* io);
};
// @ 0x00675440
unsigned SerObj::Read(int* io) {
    char ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, (void*)0x14010d4, 4);
    char* i = mpBegin;
    char* e = mpEnd;
    while (ok && i != e) {
        ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, i, 4);
        if (ok) {
            ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, i + 8, 4);
            if (ok) ok = 1; else ok = 0;
        } else ok = 0;
        i += 0x10;
    }
    int local = -1;
    if (ok) {
        ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, &local, 4);
        if (ok) return 1;
    }
    return 0;
}

// ---- 0x006754d0 : load object database (complete, non-matching) ------
struct HeldBase {               // holder interface sub-object
    void* mpVt;                 // +0
    void* mpObject;             // +4
    void* mpDb;                 // +8
    bool  mbFlag;               // +0xc
    char  pad[3];
    bool Bind(void* db, void* key, int flag);   // 0x0069e260
    bool Reset();                               // 0x0069d8e0
};
struct ValidationHolder {       // cContentValidationSummarizer + HeldBase
    void*   mpVt0;              // +0
    void*   mpPad4;             // +4
    HeldBase base;              // +8
    void Ctor();                // 0x0069e210
    void Dtor();                // 0x0069d860
};
struct ObjectDatabase {
    void** vt;
    void* Ctor(void* save);     // 0x0069fa60
};
struct AchievementLoader {
    char  pad0[8];
    void* mp8;                  // +8
};
extern char g_1529498;          // [0x01529498]

// @ 0x006754d0
char __fastcall FUN_006754d0(char* p) {
    AchievementLoader* self = (AchievementLoader*)p;
    void* save = GetSaveArea(0x11ac19c);
    void* db = ZoneObjNew(0x24, "Simulator", 0, 0, 0, 0);
    db = db ? ((ObjectDatabase*)db)->Ctor(save) : 0;
    if (db)
        ((FnV0)((VObj*)db)->vt[0])(db);
    ValidationHolder holder;
    holder.Ctor();
    if (!holder.base.Bind(db, &g_1529498, 1)) {
        holder.Dtor();
        if (db) ((FnV1)((VObj*)db)->vt[1])(db);
        return 0;
    }
    void* src = self->mp8;
    ((FnV1p)((VObj*)src)->vt[0x10 / 4])(src, &holder.base);
    holder.base.Reset();
    holder.Dtor();
    if (db) ((FnV1)((VObj*)db)->vt[1])(db);
    return 1;
}

// ---- 0x00675590 ------------------------------------------------------
// @ 0x00675590
void __fastcall FUN_00675590(char* p) {
    char* i = *(char**)(p + 0xc);
    char* e = *(char**)(p + 0x10);
    while (i != e) {
        if (i[4] & 2) *(int*)(i + 8) = 0;
        i += 0x10;
    }
    p[0x24] = 0;
}
