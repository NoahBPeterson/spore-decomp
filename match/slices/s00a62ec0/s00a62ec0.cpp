// Slice s00a62ec0 - EA::Audio::Eapd (EA's embedded Pure Data):
//   * the "x_input" / "x_thisinstance" PD wrapper family (new/create/setup/pause/busy),
//   * the symbol-table parse helper used by those classes,
//   * the EASTL rbtree / multimap node helpers the EAPd map objects are built on,
//   * the "EAPd/map", "EAPd/AssetManager", "EAPd/BinaryMap" and "EAPd/ReleaseMap"
//     constructor / destructor pair.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00a62ec0.h"

namespace EA { namespace Audio { namespace Eapd {

extern "C" void* __cdecl memcpy_f(void*, const void*, unsigned);
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

t_class*  gpInputClass;         // 0x0167585c
t_class*  gpInstanceClass;      // 0x01675860
PgSymbol  gEventSymbol;         // 0x01675864
PgSymbol  gFieldSymbol;         // 0x0167586c
PgSymbol  gEmptySymbol;         // 0x01675874
PgSymbol  gGrandSymbol;         // 0x0167587c
PgSymbol  gGrpSymbol;           // 0x01675884
PgSymbol  gSymbolSymbol;        // 0x01675894
PgSymbol  gBangSymbol;          // 0x016758b4
PgSymbol  gFloatSymbol;         // 0x016758c4
PgSymbol  gBangSym2;            // 0x016758b8
PgSymbol  gFloatSym2;           // 0x016758c8
PgSymbol  gSymbolSym2;          // 0x01675898
uint32_t  gFieldKind;           // 0x015544ac

// ---------------------------------------------------------------------------
// @ 0x00a62ec0  EA::Audio::Eapd::x_input_new
//   custom ABI: `iface` arrives in edi, `sym`/`sym2`/`p4`/`p5` on the stack.
// ---------------------------------------------------------------------------
void* __stdcall x_input_new_reg(void* iface, PgSymbol sym, PgSymbol sym2, void* p4, void* p5)
{
    XInput* x = (XInput*)pd_new(gpInputClass);
    if (x) {
        x->mpOutlet = outlet_new(x, sym, sym2);
        x->mpParam1 = p4;
        x->mpParam2 = p5;
        x->mpParam3 = iface;
        x->mbPaused = 0;
        x->mpIface = iface;
        if (!((bool (__thiscall*)(void*, XInput*))(*(void***)iface)[6])(iface, x)) {
            pd_free(x);
            return 0;
        }
    }
    return x;
}

// ---------------------------------------------------------------------------
// @ 0x00a62f30  EA::Audio::Eapd::input_bang
// ---------------------------------------------------------------------------
void input_bang(XInput* x)
{
    ((void (__thiscall*)(void*, XInput*))(*(void***)x->mpIface)[7])(x->mpIface, x);
}

// ---------------------------------------------------------------------------
// @ 0x00a62f80  EA::Audio::Eapd::input_new_symbol
// ---------------------------------------------------------------------------
void* input_new_symbol(void* a, void* b)
{
    void* inst = canvas_getcurrentinstance();
    void* iface = InstanceCreate(inst, 1, gSymbolSymbol, gSymbolSym2, a, b);
    return x_input_new_reg(iface, gSymbolSymbol, gSymbolSym2, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00a62fc0  EA::Audio::Eapd::input_new_bang_local
// ---------------------------------------------------------------------------
void* input_new_bang_local(void* a, void* b)
{
    void* inst = canvas_getcurrentinstance();
    void* iface = InstanceCreate(inst, 2, gBangSymbol, gBangSym2, a, b);
    return x_input_new_reg(iface, gBangSymbol, gBangSym2, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00a62f40  EA::Audio::Eapd::input_new_float_local
// ---------------------------------------------------------------------------
void* input_new_float_local(void* a, void* b)
{
    void* inst = canvas_getcurrentinstance();
    void* iface = InstanceCreate(inst, 0, gFloatSymbol, gFloatSym2, a, b);
    return x_input_new_reg(iface, gFloatSymbol, gFloatSym2, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00a63000  EA::Audio::Eapd::input_new_globalfloat
// ---------------------------------------------------------------------------
void* input_new_globalfloat(void* a, void* b)
{
    void* iface = InputCreate(0, gFloatSymbol, gFloatSym2, a, b);
    return x_input_new_reg(iface, gFloatSymbol, gFloatSym2, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00a63030  EA::Audio::Eapd::input_new_globalsymbol
// ---------------------------------------------------------------------------
void* input_new_globalsymbol(void* a, void* b)
{
    void* iface = InputCreate(1, gSymbolSymbol, gSymbolSym2, a, b);
    return x_input_new_reg(iface, gSymbolSymbol, gSymbolSym2, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00a63060  EA::Audio::Eapd::input_new_globalevent
// ---------------------------------------------------------------------------
void* input_new_globalevent(void* a, void* b)
{
    void* iface = InputCreate(2, gBangSymbol, gBangSym2, a, b);
    return x_input_new_reg(iface, gBangSymbol, gBangSym2, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00a63090  EA::Audio::Eapd::pause_float
// ---------------------------------------------------------------------------
void pause_float(XInput* x, float f)
{
    int b = (f != 0.0f);
    x->mbPaused = (uint8_t)b;
}

// ---------------------------------------------------------------------------
// @ 0x00a630c0  EA::Audio::Eapd::x_input_setup
// ---------------------------------------------------------------------------
bool x_input_setup()
{
    PgSymbol s;
    bool ok;

    gpInputClass = class_new7(*gensym(&s, "input"), 0x44, 0, (void*)input_bang, 8, 9, 0);
    ok = gpInputClass != 0;
    ok &= class_addcreator((void*)input_new_bang_local,     *gensym(&s, "event"), 2, 0);
    ok &= class_addcreator((void*)input_new_float_local,    *gensym(&s, "floatparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_float_local,    *gensym(&s, "fparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_symbol,         *gensym(&s, "symbolparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_symbol,         *gensym(&s, "sparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalevent,    *gensym(&s, "globalevent"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalevent,    *gensym(&s, "gevent"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalfloat,    *gensym(&s, "globalfloatparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalfloat,    *gensym(&s, "gfparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalsymbol,   *gensym(&s, "globalsymbolparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalsymbol,   *gensym(&s, "gsparam"), 2, 0);
    ok &= class_addmethod1(gpInputClass, (void*)pause_float, *gensym(&s, "pause"), 1, 0);
    return ok;
}

// ---------------------------------------------------------------------------
// @ 0x00a632e0  EA::Audio::Eapd::instance_new
// ---------------------------------------------------------------------------
void* instance_new()
{
    XThisInstance* x = (XThisInstance*)pd_new(gpInstanceClass);
    if (x)
        x->mpInstance = canvas_getcurrentinstance();
    return x;
}

// ---------------------------------------------------------------------------
// @ 0x00a63310  EA::Audio::Eapd::busy_float
// ---------------------------------------------------------------------------
void busy_float(XThisInstance* x, float f)
{
    ((ParamSink*)x->mpInstance)->SetParam(f != 0.0f);
}

// ---------------------------------------------------------------------------
// @ 0x00a63350  EA::Audio::Eapd::x_thisinstance_setup
// ---------------------------------------------------------------------------
bool x_thisinstance_setup()
{
    PgSymbol s;
    bool ok;

    gpInstanceClass = class_new7(*gensym(&s, "thisinstance"), 0x2c, (void*)instance_new, 0, 0, 0, 0);
    ok = gpInstanceClass != 0;
    ok &= class_addmethod1(gpInstanceClass, (void*)busy_float, *gensym(&s, "busy"), 1, 0);
    return ok;
}

// ---------------------------------------------------------------------------
// @ 0x00a633e0  EA::Audio::Eapd::XThisInstance::StoreFlag
// ---------------------------------------------------------------------------
bool XThisInstance::StoreFlag(uint8_t flag)
{
    PgSymbol s;
    mbInstanceFlag = flag;
    gEventSymbol = *gensym(&s, "--current--");
    gGrpSymbol   = *gensym(&s, "grp");
    gGrandSymbol = *gensym(&s, "snr");
    gFieldSymbol = *gensym(&s, "sns");
    gEmptySymbol = gSymbolSymbol;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a634a0  EA::Audio::Eapd::InputParseSymbols
// ---------------------------------------------------------------------------
bool __fastcall InputParseSymbols(int kind, char** cursor, char* end, char** out1,
                                  PgSymbol* out2, int* out3, int* out4)
{
    char buf[0x18];
    char* text;
    if (kind == (int)gFieldKind) {
        memcpy_f(buf, *cursor, 0x19);
        *strchr_f(buf, 0x20) = 0;
        *cursor += 0x19;
        text = buf;
    } else if (kind == 2) {
        if (*cursor == end)
            return false;
        while (**cursor != 0) {
            ++*cursor;
            if (*cursor == end)
                break;
        }
        if (*cursor == end)
            return false;
        ++*cursor;
        text = *cursor;
    } else if (kind == 3) {
        text = *cursor + 4 + *(int*)*cursor;
        *cursor = text;
    } else {
        return false;
    }
    if (text == 0)
        return false;
    *gensym((PgSymbol*)buf, text);
    if (out1)
        *out1 = *(char**)((char*)buf + 4);
    *out2 = *gensym((PgSymbol*)buf, 0);
    if (kind == 3) {
        *out2 = *gensym((PgSymbol*)buf, *cursor);
        *cursor += 4;
    } else {
        *out2 = gSymbolSymbol;
    }
    *out3 = *(int*)*cursor;
    *cursor += 4;
    *out4 = (int)*cursor;
    *cursor += *out3;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a635d0  EA::Audio::Eapd::GetGroupSymbol
// ---------------------------------------------------------------------------
PgSymbol* GetGroupSymbol(PgSymbol* out)
{
    uint32_t    emptyH = gEmptySymbol.mHash;
    uint32_t    fieldH = gFieldSymbol.mHash;
    const char* emptyN = gEmptySymbol.mpName;
    out->mHash = emptyH;
    out->mpName = emptyN;
    if (emptyH != fieldH) {
        out->mHash = fieldH;
        out->mpName = gFieldSymbol.mpName;
        gFieldSymbol.mHash = emptyH;
        gFieldSymbol.mpName = emptyN;
        return out;
    }
    void* canvas = canvas_getcurrent();
    if (canvas != 0) {
        PgSymbol tmp;
        PgSymbol* r = (PgSymbol*)canvas_realizedollar2(&tmp, canvas);
        out->mHash = r->mHash;
        out->mpName = r->mpName;
    }
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a63640  EA::Audio::Eapd::EapdMapBase::DestroyAll
// ---------------------------------------------------------------------------
void EapdMapBase::DestroyAll(void* node)
{
    if (node == 0)
        return;
    void* next;
    do {
        DestroyAll(*(void**)node);
        next = *(void**)((char*)node + 4);
        void* alloc = (char*)this + 0x18;
        ((void (__thiscall*)(void*, void*))(*(void***)alloc)[3])(alloc, node);
        node = next;
    } while (next != 0);
}

// ---------------------------------------------------------------------------
// @ 0x00a63680  EA::Audio::Eapd::EapdMapBase::HasKeyEvent
// ---------------------------------------------------------------------------
bool EapdMapBase::HasKeyEvent(uint32_t key)
{
    void* found;
    void* n = ((RbTreeView*)((char*)this + 0x34))->find(&found, &key);
    return (char*)this + 0x38 == *(void**)n;
}

// ---------------------------------------------------------------------------
// @ 0x00a636b0  EA::Audio::Eapd::EapdMapBase::HasKeyField
// ---------------------------------------------------------------------------
bool EapdMapBase::HasKeyField(uint32_t key, int arg)
{
    void* found;
    void* n = ((RbTreeView*)((char*)this + 0x10))->find(&found, &key);
    (void)arg;
    return (char*)this + 0x14 != *(void**)n;
}

// ---------------------------------------------------------------------------
// @ 0x00a636e0  EA::Audio::Eapd::EapdMapBase::Insert28
// ---------------------------------------------------------------------------
void* EapdMapBase::Insert28(void** out, void* hint, uint32_t* key, char isEnd)
{
    int side;
    if (isEnd == 0 && hint != (char*)this + 4 && *key >= *(uint32_t*)((char*)hint + 0x10))
        side = 1;
    else
        side = 0;
    void* alloc = (char*)this + 0x18;
    void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x28);
    if ((char*)node + 0x10 != 0) {
        uint32_t* d = (uint32_t*)((char*)node + 0x10);
        d[0] = key[0]; d[1] = key[1]; d[2] = key[2];
        d[3] = key[3]; d[4] = key[4]; d[5] = key[5];
    }
    RBTreeInsert(node, hint, (char*)this + 4, side);
    void** o = out;
    ++*(int*)((char*)this + 0x14);
    *o = node;
    return o;
}

// ---------------------------------------------------------------------------
// @ 0x00a63770  EA::Audio::Eapd::EapdMapBase::Insert1c
// ---------------------------------------------------------------------------
void EapdMapBase::Insert1c(uint32_t* val, void* hint, uint32_t* key, char isEnd)
{
    int side;
    if (isEnd == 0 && hint != (char*)this + 4 && *key >= *(uint32_t*)((char*)hint + 0x10))
        side = 1;
    else
        side = 0;
    void* alloc = (char*)this + 0x18;
    void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x1c);
    if ((char*)node + 0x10 != 0) {
        uint32_t* d = (uint32_t*)((char*)node + 0x10);
        d[0] = key[0]; d[1] = key[1]; d[2] = key[2];
    }
    RBTreeInsert(node, hint, (char*)this + 4, side);
    uint32_t* v = val;
    ++*(int*)((char*)this + 0x14);
    *v = (uint32_t)node;
}

// ---------------------------------------------------------------------------
// @ 0x00a637f0  EA::Audio::Eapd::EapdMapBase::Insert18
// ---------------------------------------------------------------------------
void EapdMapBase::Insert18(uint32_t* val, void* hint, uint32_t* key, char isEnd)
{
    int side;
    if (isEnd == 0 && hint != (char*)this + 4 && *key >= *(uint32_t*)((char*)hint + 0x10))
        side = 1;
    else
        side = 0;
    void* alloc = (char*)this + 0x18;
    void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x18);
    if ((char*)node + 0x10 != 0) {
        uint32_t* d = (uint32_t*)((char*)node + 0x10);
        d[0] = key[0]; d[1] = key[1];
    }
    RBTreeInsert(node, hint, (char*)this + 4, side);
    ++*(int*)((char*)this + 0x14);
    *val = (uint32_t)node;
}

// ---------------------------------------------------------------------------
// @ 0x00a63860  EA::Audio::Eapd::EapdMapBase::EraseEvent
// ---------------------------------------------------------------------------
bool EapdMapBase::EraseEvent(uint32_t key, PgSymbol* out)
{
    bool ret = false;
    void* found;
    ((RbTreeView*)((char*)this + 0x34))->find(&found, &key);
    if ((char*)this + 0x38 != found) {
        uint32_t* ev = *(uint32_t**)((char*)found + 0x14);
        if (out) {
            out->mHash = ev[2];
            out->mpName = (const char*)ev[3];
        }
        void* f2;
        ((RbTreeView*)((char*)this + 0x10))->find(&f2, ev + 2);
        if ((char*)this + 0x14 != f2) {
            --*(int*)((char*)this + 0x24);
            (void)RBTreeIncrement(f2);
            RBTreeErase(f2, (char*)this + 0x14);
            void* alloc = (char*)this + 0x28;
            ((void (__thiscall*)(void*, void*))(*(void***)alloc)[3])(alloc, f2);
        }
        ((void (__thiscall*)(void*, uint32_t))(*(void***)this)[4])(this, key);
        ret = true;
    }
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x00a63900  EA::Audio::Eapd::EapdMapBase::FindEventSample
// ---------------------------------------------------------------------------
bool EapdMapBase::FindEventSample(uint32_t a0, uint32_t key, int sym2, uint32_t a4, uint32_t a5,
                                  uint32_t evKey, uint32_t* out1, uint32_t* out2)
{
    if (evKey == gEventSymbol.mHash && key == gSymbolSymbol.mHash) {
        key = a4;
        sym2 = (int)a5;
    }
    void* found;
    ((RbTreeView*)((char*)this + 0x10))->find(&found, &key);
    if ((char*)this + 0x14 == found)
        return false;
    uint32_t* node = *(uint32_t**)((char*)found + 0x18);
    void* range[2];
    ((RbMapView*)((char*)node + 0x10))->equal_range(range, &sym2);
    uint32_t* it = (uint32_t*)range[0];
    uint32_t* end = (uint32_t*)range[1];
    if (it == end)
        return false;
    while (it[6] != evKey) {
        it = (uint32_t*)RBTreeIncrement(it);
        if (it == end)
            return false;
    }
    *out1 = it[9];
    *out2 = it[8];
    ++*node;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a63a50  EA::Audio::Eapd::EapdMapBase::FindOrInsert18
// ---------------------------------------------------------------------------
void* EapdMapBase::FindOrInsert18(void** out, uint32_t* key)
{
    char* head = (char*)this + 4;
    char* parent = head;
    char cmp = 1;
    uint32_t* cur = *(uint32_t**)((char*)this + 0xc);
    if (cur) {
        do {
            parent = (char*)cur;
            cmp = (*key < cur[4]);
            cur = cmp ? *(uint32_t**)((char*)cur + 4) : *(uint32_t**)cur;
        } while (cur);
    }
    char* hint = parent;
    if (cmp) {
        if (parent == *(char**)((char*)this + 8)) {
            Insert18((uint32_t*)out, hint, key, 0);
            return out;
        }
        hint = (char*)RBTreeDecrement(parent);
    }
    if (*(uint32_t*)(hint + 0x10) < *key) {
        int side = !(parent == head || *key < *(uint32_t*)(parent + 0x10));
        void* alloc = *(void**)((char*)this + 0x18);
        void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x18);
        if ((char*)node + 0x10 != 0) {
            uint32_t* d = (uint32_t*)((char*)node + 0x10);
            d[0] = key[0]; d[1] = key[1];
        }
        RBTreeInsert(node, parent, head, side);
        ++*(int*)((char*)this + 0x14);
        *(void**)out = node;
        ((uint8_t*)out)[4] = 1;
        return out;
    }
    *(char**)out = hint;
    ((uint8_t*)out)[4] = 0;
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a63b40  EA::Audio::Eapd::EapdMapBase::~EapdMapBase
// ---------------------------------------------------------------------------
EapdMapBase::~EapdMapBase()
{
    DestroyAll(*(void**)((char*)this + 0xc));
    *(void**)((char*)this + 0x18) = (void*)0x1403934;
}

// ---------------------------------------------------------------------------
// @ 0x00a63b90  EA::Audio::Eapd::EapdMapBase::ClearAll
// ---------------------------------------------------------------------------
bool EapdMapBase::ClearAll()
{
    bool ok = true;
    while (*(void**)((char*)this + 0x24) != 0)
        EraseEvent(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)((char*)this + 0x18) + 0x18) + 4), 0);
    if (*(void**)((char*)this + 0x48) != 0) {
        ok = false;
        do {
            uint32_t* p = (uint32_t*)(*(uint32_t*)(*(uint32_t*)((char*)this + 0x3c) + 0x14));
            *p = 1;
            ((void (__thiscall*)(void*, uint32_t))(*(void***)this)[4])(this, p[1]);
        } while (*(void**)((char*)this + 0x48) != 0);
    }
    return ok;
}

// ---------------------------------------------------------------------------
// @ 0x00a63bf0  EA::Audio::Eapd::EapdMapBase::FindOrInsert28
// ---------------------------------------------------------------------------
void* EapdMapBase::FindOrInsert28(void** out, uint32_t* key)
{
    char* parent = (char*)this + 4;
    uint32_t* cur = *(uint32_t**)((char*)this + 0xc);
    if (cur) {
        do {
            parent = (char*)cur;
            cur = (*key < cur[4]) ? *(uint32_t**)((char*)cur + 4) : *(uint32_t**)cur;
        } while (cur);
    }
    Insert28(out, parent, key, 0);
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a63c30  EA::Audio::Eapd::EapdMapBase::Init
// ---------------------------------------------------------------------------
void* EapdMapBase::Init(void* allocator, void* a3, void* a4, void* a5)
{
    mpAllocVtbl = a3;
    mpAllocator = a4;
    mpName = (const char*)a5;
    void* vtbl = *(void**)((char*)allocator + 4);
    *(void**)((char*)this) = 0;
    *(uint8_t*)((char*)this + 0x10) = 0;
    *(void**)((char*)this + 0x18) = 0;
    *(void**)((char*)this + 0x1c) = 0;
    void* sentinel = (char*)this + 0x14;
    *(void**)((char*)this + 0x20) = 0;
    mpOwner2c = vtbl;
    mpVtbl28 = (void*)0x1454fac;
    mpKind30 = "EAPd/map";
    *(void**)((char*)this + 0x14) = sentinel;
    *(void**)((char*)this + 0x18) = sentinel;
    *(void**)((char*)this + 0x1c) = 0;
    *(uint8_t*)((char*)this + 0x20) = 0;
    *(void**)((char*)this + 0x24) = 0;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00a63c90  EA::Audio::Eapd::EapdAssetManager::Init
// ---------------------------------------------------------------------------
void* EapdAssetManager::Init(void* allocator)
{
    void* vtbl = *(void**)((char*)allocator + 4);
    mpvtable = (void*)0x1455618;
    mpAllocVtbl = (void*)0x1454fac;
    mpAllocator = vtbl;
    mpName = "EAPd/AssetManager";
    void* bmSentinel = (char*)this + 0x14;
    *(uint8_t*)((char*)this + 0x10) = 0;
    *(void**)((char*)this + 0x18) = 0;
    *(void**)((char*)this + 0x1c) = 0;
    *(void**)((char*)this + 0x20) = 0;
    mpOwner2c = vtbl;
    mpVtbl28 = (void*)0x1454fac;
    mpKind30 = "EAPd/BinaryMap";
    *(void**)((char*)this + 0x14) = bmSentinel;
    *(void**)((char*)this + 0x18) = bmSentinel;
    *(void**)((char*)this + 0x1c) = 0;
    *(uint8_t*)((char*)this + 0x20) = 0;
    *(void**)((char*)this + 0x24) = 0;
    void* bmVtbl2 = *(void**)((char*)allocator + 4);
    *(void**)((char*)this + 0x3c) = 0;
    *(void**)((char*)this + 0x40) = 0;
    *(void**)((char*)this + 0x44) = 0;
    void* rmSentinel = (char*)this + 0x38;
    *(void**)((char*)this + 0x50) = bmVtbl2;
    *(void**)((char*)this + 0x4c) = (void*)0x1454fac;
    *(void**)((char*)this + 0x54) = (void*)"EAPd/ReleaseMap";
    *(void**)((char*)this + 0x38) = rmSentinel;
    *(void**)((char*)this + 0x3c) = rmSentinel;
    *(void**)((char*)this + 0x40) = 0;
    *(uint8_t*)((char*)this + 0x44) = 0;
    *(void**)((char*)this + 0x48) = 0;
    *(void**)((char*)this + 0x58) = 0;
    *(uint8_t*)((char*)this + 0x5c) = 0;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00a63d20  EA::Audio::Eapd::EapdAssetManager::~EapdAssetManager
// ---------------------------------------------------------------------------
EapdAssetManager::~EapdAssetManager()
{
    mpvtable = (void*)0x1455618;
    ((EapdMapBase*)((char*)this + 0x20))->DestroyAll(*(void**)((char*)this + 0x40));
    *(void**)((char*)this + 0x4c) = (void*)0x1403934;
    ((EapdMapBase*)this)->DestroyAll(*(void**)((char*)this + 0x1c));
    *(void**)((char*)this + 0x2c) = (void*)0x1403934;
    mpAllocVtbl = (void*)0x1403934;
}

}}}
