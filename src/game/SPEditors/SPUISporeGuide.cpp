// src/game/SPEditors/SPUISporeGuide.cpp -- migrated from slice(s) s00674640, s00673c50, s00671840 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUISporeGuide.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUISporeGuidePage.h"
#include "SP/cSPUISearchBox.h"
#include "SP/cTribeTool.h"
#include <intrin.h>
#include "cSPUILayout.h"
#include <string.h>
#include "EA/ArgScript/cArguments.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"
#include <wchar.h>
#include "SP/cSPEditorModelValidity.h"

// ---- items of slice s00671840 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void (__thiscall *FnV1)(void*);
typedef void* (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnV0i)(void*, int);
void AddRefObj(void* p) { if (p) ((FnV1)((VObj*)p)->vt[0])(p); }
void ReleaseObj(void* p) { if (p) ((FnV1)((VObj*)p)->vt[1])(p); }
struct cSPUILayout_s0067_1840 {
  void Shutdown(int a);  // 0x00811ad0 (cSPUILayout::Shutdown)
  bool Init(void* arr, int a, unsigned key);  // 0x008120d0 (cSPUILayout::Init)
  void SetParentWin(void* w, int a, unsigned key);  // 0x008121b0 (cSPUILayout::SetParentWin)
  void SetReloadCallback(void* cb, void* self);  // 0x00810090 (cSPUILayout::SetReloadCallback)
  void* FindWindowByID(unsigned id, int rec);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void Dtor();   // 0x00811fe0 (equiv t3)
};
struct EString {
  void Assign(unsigned short* s);   // 0x005c3d90 (equiv t3)
  void Assign(unsigned short* a, unsigned short* b);
  void Detok8f40();
  long long Find(unsigned short* sub, int pos);
  EString* AssignFrom(EString* other);
};
void FUN_00996280(int a, int b, int c, int d);
bool FUN_009979f0(void* a, unsigned key);
struct FrameSet { void Ctor(int a); void Dtor(); void* GetFrame(void* key); void Clear(); void Release(); };
void CenterWindowInRect(void* obj);   // 0x00810000 (equiv t2)
void operator_delete_(void* p);
void SetScrollbarDrawable(void* frame, int a, void* drawable);
void FUN_00992dc0(int a, int b);
void* interface_cast(void* p); // 0x0081d780
void CStringDetokenizer_ProcessString(void* self, unsigned short* a, unsigned short* b);
void* g_1528cfc;
struct GuidePage {
  char pad[8];
  void* mFrameSet;      // +8
  char padC[0x60];
  void* mFrame;         // +0x6c
  bool Init(void* a);
  bool OnRelease();
};
struct Detokenizer {
  bool detokenize();
  void token_action_copy(void* a, unsigned short* b);
};
struct DetokSink {
  bool ProcessString(const unsigned short* a, void* b);   // 0x006b5bd0
  void Assign(void* begin, void* end);                    // 0x00423650
};
// ---- items of slice s00671840 end

// ---- items of slice s00673c50 begin (TODO(rewrite): local stubs, replace by canonical classes)
void DeleteObj(void* p);   // 0x00f47380
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
struct EStrVec {
    EStr* mpBegin;     // +0x00
    EStr* mpEnd;       // +0x04
    EStr* mpCapacity;  // +0x08
    char  padC[8];     // +0x0c
    void DoInsertValue(EStr* pos, const EStr* v);   // 0x00674440 (defined elsewhere)
    void DoInsertValueSkeleton(EStr* pos, const EStr* v);
    void  push_back(const EStr& v);
};
struct FillVec { unsigned* FillInsert(unsigned count, unsigned value); };
struct Detokenizer_s0067_3c50 {
    void Ctor();
};
// ---- items of slice s00673c50 end

// ---- items of slice s00674640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWStr[];                              // 0x01667bac (shared empty eastl string)
#pragma intrinsic(strlen, wcscmp, wcslen)
struct TWStr {                       // eastl::basic_string<wchar_t, eastl::allocator>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCap;
    int      mAlloc;
    void append(const wchar_t* p);                    // 0x005c3d90
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
struct Detokenizer_s0067_4640 {
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
// ---- items of slice s00674640 end

// @ 0x00672480
bool GuidePage::Init(void* a)
{
  if (!a) return false;
  FUN_00996280(0x1002, 0x1006, 0x1003, 0x1024);
  if (!FUN_009979f0(a, 0x58c80f8)) return false;
  void* fr = ((FrameSet*)((char*)this + 8))->GetFrame(g_1528cfc);
  void* old = mFrame;
  if (fr != old) {
    if (fr) AddRefObj(fr);
    mFrame = fr;
    ReleaseObj(old);
  }
  char layout[0x18];
  CenterWindowInRect(layout);
  if (!mFrame) { ((cSPUILayout_s0067_1840*)layout)->Dtor(); return false; }
  if (!((cSPUILayout_s0067_1840*)layout)->Init((void*)0x1529058, 0, 0x5b598fa)) {
    ((cSPUILayout_s0067_1840*)layout)->Dtor();
    return false;
  }
  void* w = ((cSPUILayout_s0067_1840*)layout)->FindWindowByID( 0x4ab5e70, 1);
  if (w) {
    void* p2 = (void*)((FnV0i)((VObj*)w)->vt[3])(w, 0x2ef0c885);
    if (p2) {
      void* d = (void*)((FnV0)((VObj*)p2)->vt[0x60 / 4])(p2);
      void* dr = interface_cast(d);
      if (dr) {
        SetScrollbarDrawable(mFrame, 1, dr);
        FUN_00992dc0(1, 0);
      }
    }
  }
  ((cSPUILayout_s0067_1840*)layout)->Dtor();
  return true;
}

// @ 0x006725a0
bool GuidePage::OnRelease()
{
  ((FrameSet*)((char*)this + 8))->Clear();
  if (mFrame) {
    void* p = mFrame; mFrame = 0; ReleaseObj(p);
  }
  return true;
}

// @ 0x00672880
EString* EString::AssignFrom(EString* other)
{
  if (this != other) {
    unsigned short** a = (unsigned short**)this;
    if (a[0] != (unsigned short*)a[1]) { *a[0] = 0; a[1] = a[0]; }
    unsigned short** b = (unsigned short**)other;
    Assign(b[0], b[1]);
  }
  return this;
}

// @ 0x00672910
void* FUN_00672910(void* first, void* last, void* dst)
{
  if (first == last) return dst;
  do {
    if (dst != first) {
      unsigned short** d = (unsigned short**)dst;
      if (d[0] != (unsigned short*)d[1]) { *d[0] = 0; d[1] = d[0]; }
      unsigned short** f = (unsigned short**)first;
      ((EString*)dst)->Assign(f[0], f[1]);
    }
    first = (char*)first + 0x54;
    dst = (char*)dst + 0x54;
  } while (first != last);
  return dst;
}

// @ 0x006729d0
bool Detokenizer::detokenize()
{
  char* self = (char*)this;
  ((DetokSink*)this)->ProcessString(*(unsigned short**)(self + 0x84),
                                    *(void**)(self + 0x94));
  void* p94 = *(void**)(self + 0x94);
  if (p94 != self + 0x84)
    ((DetokSink*)(self + 0x84))->Assign(*(void**)p94, *(void**)((char*)p94 + 4));
  if (*(int*)(self + 0x60) != 1)
    return true;
  int off = 0;
  for (int i = 0;
       i < (int)(*(char**)(self + 0xa4) - *(char**)(self + 0xa0)) / 0x63c; ++i) {
    char* outer = *(char**)(self + 0xa0) + off;
    *(void**)(self + 0x98) = outer;
    for (int j = 0;
         j < (int)(*(char**)(outer + 0xb0) - *(char**)(outer + 0xac)) / 0x58; ++j) {
      char* inner = *(char**)(*(char**)(self + 0x98) + 0xac) + j * 0x58;
      *(void**)(self + 0x9c) = inner;
      ((void (__thiscall*)(void*, void*, void*))*(void**)(inner + 0x54))(
          self, *(void**)(self + 0x98), inner);
      void* q = *(void**)(self + 0x94);
      if (q != self + 0x84)
        ((DetokSink*)(self + 0x84))->Assign(*(void**)q, *(void**)((char*)q + 4));
    }
    off += 0x63c;
  }
  return true;
}

// @ 0x00672b50
void Detokenizer::token_action_copy(void* a, unsigned short* b)
{
  (void)a;
  unsigned short* local[3];
  local[0] = (unsigned short*)0x1667bac;
  local[1] = (unsigned short*)0x1667bac;
  local[2] = (unsigned short*)0x1667bae;
  CStringDetokenizer_ProcessString(this, b, local[0]);
  unsigned short* e = local[0];
  while (*e) ++e;
  ((EString*)*(void**)((char*)this + 0x94))->Assign((unsigned short*)local[0], e);
  if ((((unsigned)((char*)local[2] - (char*)local[0]) & 0xfffffffe) > 2) && local[0])
    operator_delete_(local[0]);
}

// @ 0x00673c50
void Detokenizer_s0067_3c50::Ctor()
{ }

// @ 0x00674170
void* FillN(unsigned short* first, unsigned n, unsigned short value)
{
    unsigned short* p = first;
    unsigned short* end = first + n;
    while (p < end) *p++ = value;
    return first;
}

// @ 0x006741b0
int FindRange(int* p, unsigned short* key)
{
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

// @ 0x00674230
unsigned* FillVec::FillInsert(unsigned count, unsigned value)
{
    unsigned* p = (unsigned*)this;
    unsigned* begin = (unsigned*)p[0];
    unsigned have = (p[1] - (unsigned)begin) >> 1;
    if (have < count) {
        unsigned* oldEnd = (unsigned*)((char*)begin + have * 2);
        for (unsigned* it = begin; it < oldEnd; ) {
            unsigned cnt = ((unsigned)((char*)oldEnd - (char*)it - 1) >> 1) + 1;
            unsigned i = cnt >> 1;
            while (i--) { *it++ = value & 0xffff | value << 0x10; }
            for (i = cnt & 1; i; --i) { *(unsigned short*)it = (unsigned short)value; it = (unsigned*)((char*)it + 2); }
        }
        FillN((unsigned short*)((char*)begin + have * 2), count - have, (unsigned short)value);
    } else {
        unsigned* mid = (unsigned*)((char*)begin + count * 2);
        for (unsigned* it = begin; it < mid; ) {
            unsigned cnt = ((unsigned)((char*)mid - (char*)it - 1) >> 1) + 1;
            unsigned i = cnt >> 1;
            while (i--) { *it++ = value & 0xffff | value << 0x10; }
            for (i = cnt & 1; i; --i) { *(unsigned short*)it = (unsigned short)value; it = (unsigned*)((char*)it + 2); }
        }
        void* src = (void*)p[1];
        void* dst = (void*)(p[0] + count * 2);
        if (dst != src) {
            memmove(dst, src, 2);
            p[1] = p[1] + (((char*)src - (char*)dst) >> 1) * -2;
        }
    }
    return p;
}

// @ 0x006742f0
EStr* MoveAssignBackward(EStr* first, EStr* last, EStr* dst)
{
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

// @ 0x00674340
EStr* UninitCopy(EStr* first, EStr* last, EStr* dst)
{
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

// @ 0x006743a0
EStr* DestroyValues(EStr* first, EStr* last, EStr* dst)
{
    while (first != last) {
        unsigned short* b = first->mpBegin;
        if ((((char*)first->mpCapacity - (char*)b) & ~1) > 2 && b && b != first->mpInline)
            DeleteObj(b);
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x006743f0
EStr* EStr::Construct(const unsigned short* src)
{
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

// @ 0x00674440
void EStrVec::DoInsertValueSkeleton(EStr* pos, const EStr* v)
{
    (void)pos; (void)v;
}

// @ 0x006745d0
void EStrVec::push_back(const EStr& v)
{
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

// @ 0x00674640
bool Detokenizer_s0067_4640::TranslateToken(const wchar_t* token, TWStr& out)
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

// @ 0x00674d30
void Detok2::Detokenize(const unsigned short* s, void* a2)
{
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

// @ 0x00674dc0
void sBuildXHTMLDocument(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x00675080
void SP::cSPUISporeGuidePage::LoadSporeGuidePage(unsigned int a)
{ (void)a; }
