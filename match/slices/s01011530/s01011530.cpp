// Slice s01011530: 0x01011530..0x01012640 (12 functions).
//
//   0x01011530  eastl::partial_sort<AutoRefCount<cPlanetRecord>*, BioProtectorSort>   (497 B)
//   0x010117c0  partial_sort sibling over the AutoRefCount list                       (309 B)
//   0x01011a40  eastl::pop_heap<tGrobShockData>  (adjust_heap_grob + timer temp)      (266 B)
//   0x01011b50  SP::cSimulatorUniverse::~cSimulatorUniverse (rbtree/timer teardown)   (314 B)
//   0x01011cc0  eastl vector assignment (DoResize / copy_impl)                        (234 B)
//   0x01011db0  list serialiser (ConvertToString16 + wstring node walk)               (326 B)
//   0x01012030  eastl vector grow + range copy                                        (453 B)
//   0x01012330  eastl::make_heap<tGrobShockData, tGrobLess>                           (151 B)
//   0x010123d0  eastl::sort_heap<tGrobShockData, tGrobLess>                           ( 92 B)
//   0x01012450  SP::WarRaid::Start                                                    (225 B)
//   0x01012540  SP::GrobWarRaid::Start                                                (251 B)
//   0x01012640  SP::GrobTeaseRaid::Start                                              (229 B)
//
// Module is SporeApp Simulator/game code (VC9 SP1), not Havok.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types

// SP::cSPTimer sub-object (0x20 bytes), embedded in tGrobShockData at +0x08.
struct cSPTimer {
    void* mVtbl;        // +0x00  (0x01465d54 -> 0x01464450)
    int   mRefCount;    // +0x04
    int   mElapsedLo;   // +0x08
    int   mElapsedHi;   // +0x0c
    int   mBaseLo;      // +0x10
    int   mBaseHi;      // +0x14
    char  mRunning;     // +0x18
    char  mPad19[3];
    int   mGetMs;       // +0x1c

    void Dtor();        // 0x00b638b0  SP::cGonzagoTimer::~cGonzagoTimer
};

// SP::cSimulatorUniverse::tGrobShockData (0x28 bytes).
struct tGrobShockData {
    int      mField00;  // +0x00
    int      mField04;  // +0x04
    cSPTimer mTimer;    // +0x08

    tGrobShockData(const tGrobShockData& o)
    {
        mField00 = o.mField00;
        mField04 = o.mField04;
        mTimer.mVtbl = (void*)0x01465d54;
        mTimer.mRefCount = 0;
        mTimer.mElapsedLo = o.mTimer.mElapsedLo;
        mTimer.mElapsedHi = o.mTimer.mElapsedHi;
        mTimer.mBaseLo    = o.mTimer.mBaseLo;
        mTimer.mBaseHi    = o.mTimer.mBaseHi;
        mTimer.mRunning   = o.mTimer.mRunning;
        mTimer.mGetMs     = o.mTimer.mGetMs;
        mTimer.mVtbl = (void*)0x01464450;
    }

    // Copy-assignment copies the head dwords and the timer payload but leaves the
    // timer vtable/refcount alone (matches 0x01011a7d..0x01011aae).
    tGrobShockData& operator=(const tGrobShockData& o)
    {
        mField00 = o.mField00;
        mField04 = o.mField04;
        mTimer.mElapsedLo = o.mTimer.mElapsedLo;
        mTimer.mElapsedHi = o.mTimer.mElapsedHi;
        mTimer.mBaseLo    = o.mTimer.mBaseLo;
        mTimer.mBaseHi    = o.mTimer.mBaseHi;
        mTimer.mRunning   = o.mTimer.mRunning;
        mTimer.mGetMs     = o.mTimer.mGetMs;
        return *this;
    }
};

// eastl comparator functor used by the grob-shock heap helpers.
typedef bool (__cdecl *tGrobLess)(const tGrobShockData&, const tGrobShockData&);

// 0x01011900  SP::cSimulatorUniverse::adjust_heap_grob
//   adjust_heap(first, holeIndex, heapLength, topIndex, value, compare) -- the heap
//   value is passed by value (0x28 bytes) in the outgoing argument area.
void __cdecl adjust_heap_grob(tGrobShockData* first, int holeIndex, int heapLength,
                              int topIndex, tGrobShockData value, tGrobLess compare);

// eastl::pop_heap<tGrobShockData*, tGrobLess>  (kept out-of-line: 0x010123d0 has a real
// call to it, matching the original build).
void __declspec(noinline) __cdecl FUN_01011a40(tGrobShockData* first, tGrobShockData* last,
                                               tGrobLess compare);

// ---------------------------------------------------------------------------
// helpers used by the partial_sort / vector / serialiser reconstructions
// ---------------------------------------------------------------------------
struct cCivData     { float* GetCities(); };            // 0x005c65e0 (thiscall)
struct cPlanetRecord{ cCivData* GetCivData(); };        // 0x00b8de30 (thiscall)
struct cRefObj {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
};

// 0x01011530 instantiation (comparator passed by value as three floats).
void __cdecl FUN_01010c70(void** first, void** middle, float cx, float cy, float cz);   // make_heap
void __cdecl FUN_0100ffc0(void** first, int hole, int len, int top, void* value,
                          float cx, float cy, float cz);                               // adjust_heap
void __cdecl FUN_01010ce0(void** first, void** middle, float cx, float cy, float cz);   // sort_heap

// 0x010117c0 instantiation (out-of-line comparator object).
void __cdecl FUN_01010d50(void** first, void** middle, float cx, float cy, float cz);   // make_heap
struct cBioSort2 { bool Less(void* a, void* b); };                                      // 0x0100dc20
void __cdecl FUN_01010190(void** first, int hole, int len, int top, void* value,
                          float cx, float cy, float cz);                               // adjust_heap
void __cdecl FUN_01010dc0(void** first, void** middle, float cx, float cy, float cz);   // sort_heap

// eastl vector range-insert helpers.
void* __cdecl FUN_00ac97a0(void* dst, void* first, void* last);        // 0x00ac97a0
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void    __cdecl operator_delete_(void* p);                             // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);         // 0x011e0744

// eastl::wstring + XML writer used by the shock-list serialiser.
struct cWString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    void RangeInitialize(int n);            // 0x00579a90
    void CopyCtor(const cWString* src);     // 0x0056e2d0
};
cWString* __cdecl ConvertToString16(cWString* out, const wchar_t* s, int len);   // 0x0093c5a0
struct cXmlWriter {
    virtual void BeginBlock(const wchar_t* name);   // +0x00
    virtual void EndBlock(const wchar_t* name);     // +0x04
};
char __cdecl FUN_00ac8050(void* writer, int a, void* elem);          // 0x00ac8050

// shock list {begin, end} over 0x28-byte tGrobShockData elements.
struct cShockList {
    tGrobShockData* mpBegin;    // +0x00
    tGrobShockData* mpEnd;      // +0x04
};


// ---------------------------------------------------------------- 0x01011530

// eastl::partial_sort<AutoRefCount<cPlanetRecord>*, BioProtectorSort>
//
//   make_heap(first, middle, comp);
//   for (it = middle; it < last; ++it) {
//       pa = (*it)->GetCivData()->GetCities();       // evaluated first (2nd arg)
//       pb = (*first)->GetCivData()->GetCities();
//       if (dist2(pb - comp) > dist2(pa - comp)) {   // comp(*first, *it)
//           value = *it;                             // AutoRefCount copy ctor (AddRef)
//           *it = *first;                            // AutoRefCount assignment
//           adjust_heap(first, 0, middle - first, 0, value, comp);
//           value->Release();                        // ~value
//       }
//   }
//   sort_heap(first, middle, comp);
//
// The comparator (BioProtectorSort) is a 12-byte functor holding the reference
// position; MSVC passes it by value in the outgoing argument area, so the source
// models it as three floats.
//
// @ 0x01011530
void __cdecl FUN_01011530(void** first, void** middle, void** last,
                          float cx, float cy, float cz)
{
    FUN_01010c70(first, middle, cx, cy, cz);

    for (void** it = middle; it < last; ++it) {
        float* pa = ((cPlanetRecord*)*it)->GetCivData()->GetCities();
        float ax = pa[0] - cx;
        float ay = pa[1] - cy;
        float az = pa[2] - cz;
        float d2a = ax * ax + ay * ay + az * az;

        float* pb = ((cPlanetRecord*)*first)->GetCivData()->GetCities();
        float bx = pb[0] - cx;
        float by = pb[1] - cy;
        float bz = pb[2] - cz;
        float d2b = bx * bx + by * by + bz * bz;

        if (d2b > d2a) {
            cRefObj* value = (cRefObj*)*it;          // AutoRefCount copy ctor
            if (value)
                value->AddRef();
            cRefObj* top = (cRefObj*)*first;         // AutoRefCount assignment
            if (top != value) {
                if (top)
                    top->AddRef();
                *it = (void*)top;
                if (value)
                    value->Release();
            }
            FUN_0100ffc0(first, 0, (int)(middle - first), 0, value, cx, cy, cz);
            if (value)
                value->Release();
        }
    }

    FUN_01010ce0(first, middle, cx, cy, cz);
}

// ---------------------------------------------------------------- 0x010117c0

// eastl::partial_sort sibling.  Same shape as 0x01011530 but the comparator is an
// out-of-line thiscall member of the 12-byte functor stored in the caller's frame:
//
//   if (comp.Less(*it, *first)) { value = *it; *it = *first; adjust_heap(...); }
//
// @ 0x010117c0
void __cdecl FUN_010117c0(void** first, void** middle, void** last,
                          float cx, float cy, float cz)
{
    FUN_01010d50(first, middle, cx, cy, cz);

    for (void** it = middle; it < last; ++it) {
        if (((cBioSort2*)&cx)->Less(*it, *first)) {
            cRefObj* value = (cRefObj*)*it;          // AutoRefCount copy ctor
            if (value)
                value->AddRef();
            cRefObj* top = (cRefObj*)*first;         // AutoRefCount assignment
            if (top != value) {
                if (top)
                    top->AddRef();
                *it = (void*)top;
                if (value)
                    value->Release();
            }
            FUN_01010190(first, 0, (int)(middle - first), 0, value, cx, cy, cz);
            if (value)
                value->Release();
        }
    }

    FUN_01010dc0(first, middle, cx, cy, cz);
}

// ---------------------------------------------------------------- 0x01011a40

// eastl::pop_heap<tGrobShockData*, tGrobLess>
//
//   value = *(last - 1);
//   *(last - 1) = *first;
//   adjust_heap_grob(first, 0, (last - first) - 1, 0, value, compare);
//   ~value;
//
// @ 0x01011a40
void __cdecl FUN_01011a40(tGrobShockData* first, tGrobShockData* last, tGrobLess compare)
{
    tGrobShockData value(last[-1]);
    last[-1] = *first;
    adjust_heap_grob(first, 0, (int)(last - first) - 1, 0, value, compare);
    value.mTimer.Dtor();
}

// ---------------------------------------------------------------- 0x01011b50

// SP::cSimulatorUniverse  (the object is ~0x1a8 bytes; only the members the
// destructor touches are named).
struct cRBTree {                          // 0x009a9600 DoNukeSubtree
    void* mpHead[3];                      // +0x00
    void* mpRoot;                         // +0x0c
    void  DoNukeSubtree(void* node);
    void  DoNuke() { DoNukeSubtree(mpRoot); }
};

struct cSimTimerVec {                     // 0x00b95240 (thiscall, 2 stack args)
    void* mpBegin;                        // +0x00
    void* mpEnd;                          // +0x04
    void* mpCap;                          // +0x08
    void  Destroy(void* begin, void* end);
};

struct cSimUniverse {
    void*  mpVtbl;              // +0x000
    int    mPad004;             // +0x004
    void*  mpVtbl08;            // +0x008
    int    mPad00c;             // +0x00c
    void*  mpRef10;             // +0x010  ref-counted object (Release = slot 1)
    int    mPad014;             // +0x014
    cRBTree mTree18;            // +0x018
    int    mPad028[3];          // +0x028
    void*  mpVtbl034;           // +0x034
    void*  mpVtbl038;           // +0x038
    int    mPad03c;             // +0x03c
    void*  mpVtbl040;           // +0x040
    int    mPad044[3];          // +0x044
    void*  mpVtbl050;           // +0x050
    int    mPad054;             // +0x054
    void*  mpVtbl058;           // +0x058
    int    mPad05c[3];          // +0x05c
    void*  mpVtbl068;           // +0x068
    int    mPad06c;             // +0x06c
    void*  mpVtbl070;           // +0x070
    int    mPad074[3];          // +0x074
    void*  mpVtbl080;           // +0x080
    int    mPad084;             // +0x084
    void*  mpVtbl088;           // +0x088
    int    mPad08c[3];          // +0x08c
    void*  mpVtbl098;           // +0x098
    int    mPad09c;             // +0x09c
    void*  mpVtbl0a0;           // +0x0a0
    int    mPad0a4[3];          // +0x0a4
    void*  mpVtbl0b0;           // +0x0b0
    void*  mpVtbl0b4;           // +0x0b4
    int    mPad0b8[5];          // +0x0b8
    void*  mpVtbl0cc;           // +0x0cc
    void*  mpVtbl0d0;           // +0x0d0
    int    mPad0d4;             // +0x0d4
    void*  mpVtbl0d8;           // +0x0d8
    void*  mpVtbl0dc;           // +0x0dc
    int    mPad0e0;             // +0x0e0
    void*  mpVtbl0e4;           // +0x0e4
    void*  mpVtbl0e8;           // +0x0e8
    int    mPad0ec[2];          // +0x0ec
    void*  mpVtbl0f4;           // +0x0f4
    cSimTimerVec mTimerVec;     // +0x0f8
    int    mPad104[9];          // +0x104
    tGrobShockData* mpTimersBegin;  // +0x128
    tGrobShockData* mpTimersEnd;    // +0x12c
    int    mPad130[19];         // +0x130
    cRBTree mTree17c;           // +0x17c
    int    mPad18c[3];          // +0x18c
    cRBTree mTree198;           // +0x198

    void Destroy();             // 0x01011b50  ~SP::cSimulatorUniverse
};

extern void* gSimUniverse;      // 0x016dc798

// @ 0x01011b50
void cSimUniverse::Destroy()
{
    mpVtbl   = (void*)0x01495748;       // ??_7cSimulatorUniverse@@6B@
    mpVtbl08 = (void*)0x01495724;       // cISerializableObject sub-vtable
    gSimUniverse = 0;

    mTree198.DoNuke();
    mTree17c.DoNuke();

    tGrobShockData* timerEnd = mpTimersEnd;
    for (tGrobShockData* p = mpTimersBegin; p < timerEnd; ++p)
        p->mTimer.Dtor();

    if (mpTimersBegin != 0 && ((int*)mpTimersBegin)[-1] != 0)
        operator_delete_(mpTimersBegin);

    mTimerVec.Destroy(mTimerVec.mpBegin, mTimerVec.mpEnd);
    if (mTimerVec.mpBegin)
        operator_delete_(mTimerVec.mpBegin);

    void* const vtblB = (void*)0x01403934;
    void* const vtblA = (void*)0x01495584;

    mpVtbl0f4 = vtblA;
    mpVtbl0e4 = vtblA;
    mpVtbl0d8 = vtblA;
    mpVtbl0cc = vtblA;
    mpVtbl0b0 = vtblA;
    mpVtbl098 = vtblA;
    mpVtbl080 = vtblA;
    mpVtbl068 = vtblA;
    mpVtbl050 = vtblA;
    mpVtbl038 = vtblA;

    mpVtbl0e8 = vtblB;
    mpVtbl0dc = vtblB;
    mpVtbl0d0 = vtblB;
    mpVtbl0b4 = vtblB;
    mpVtbl0a0 = vtblB;
    mpVtbl088 = vtblB;
    mpVtbl070 = vtblB;
    mpVtbl058 = vtblB;
    mpVtbl040 = vtblB;
    mpVtbl034 = vtblB;

    mTree18.DoNuke();

    cRefObj* ref = (cRefObj*)mpRef10;
    if (ref)
        ref->Release();

    mpVtbl   = (void*)0x013ec458;       // vtbl SP::Simulator::cContentValidationSummarizer
    mpVtbl08 = (void*)0x013eb938;       // vtbl EA::Trace::ITracerBase
}

// ---------------------------------------------------------------- 0x01011cc0

// eastl vector (EA::AutoRefCount<EA::Trace::ILogReporter>) operator=.
struct VecAutoRef {
    void** mpBegin;   // +0x00
    void** mpEnd;     // +0x04
    void** mpCap;     // +0x08

    void** DoResize(unsigned n, void** begin, void** end);   // 0x00b95280
    void   FreeOld(void** begin, void** end);                // 0x00b007f0
    VecAutoRef* Assign(const VecAutoRef& o);                 // 0x011cc0
};

void** __cdecl copy_impl_do_copy(void** first, void** last, void** dst);   // 0x006782c0
void*  __cdecl move_range_range(const void* dst, void** first, void** last, void** dlast, void* src); // 0x00829110
void   __cdecl operator_delete_(void* p);                                  // 0x00f47380

// @ 0x01011cc0
VecAutoRef* VecAutoRef::Assign(const VecAutoRef& o)
{
    if (&o == this)
        return this;
    unsigned n = (unsigned)(o.mpEnd - o.mpBegin);
    if ((unsigned)(mpCap - mpBegin) < n) {
        void** p = DoResize(n, o.mpBegin, o.mpEnd);
        FreeOld(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete_(mpBegin);
        mpCap  = p + n;
        mpEnd  = p + n;
        mpBegin = p;
        return this;
    }
    unsigned have = (unsigned)(mpEnd - mpBegin);
    if (have < n) {
        copy_impl_do_copy(o.mpBegin, o.mpBegin + have, mpBegin);
        move_range_range(&o, o.mpBegin + (mpEnd - mpBegin), o.mpEnd, mpEnd, 0);
        mpEnd = mpBegin + n;
        return this;
    }
    void* p = copy_impl_do_copy(o.mpBegin, o.mpEnd, mpBegin);
    FreeOld((void**)p, mpEnd);
    mpEnd = mpBegin + n;
    return this;
}

// ---------------------------------------------------------------- 0x01011db0

// SP::cSimulatorUniverse shock-list serialiser.
//
//   if (list.empty()) return true;
//   wstring name16 = name ? ConvertToString16(name, -1) : wstring();
//   text = name16.empty() ? L"list" : name16.c_str();
//   writer->BeginBlock(text);
//   for (e : list) if (ok) ok = ToXml(writer, 0, e);
//   writer->EndBlock(text);
//
// The two conditional temporaries of the wstring initialiser are each freed
// through operator_delete_ when their capacity check says they are heap blocks.
//
// @ 0x01011db0
char __cdecl FUN_01011db0(cXmlWriter* writer, const wchar_t* name, cShockList* list)
{
    char ok = 1;

    if (list->mpBegin == list->mpEnd)
        return ok;

    cWString text;
    if (name == 0) {
        cWString empty;
        empty.mpBegin = 0;
        empty.mpEnd   = 0;
        empty.mpCap   = 0;
        empty.RangeInitialize(0);
        text.CopyCtor(&empty);
        if (((int)((char*)empty.mpCap - (char*)empty.mpBegin) & 0xfffffffe) > 2 && empty.mpBegin != 0)
            operator_delete_(empty.mpBegin);
    } else {
        cWString conv;
        ConvertToString16(&conv, name, -1);
        text.CopyCtor(&conv);
        if (((int)((char*)conv.mpCap - (char*)conv.mpBegin) & 0xfffffffe) > 2 && conv.mpBegin != 0)
            operator_delete_(conv.mpBegin);
    }

    const wchar_t* block = (text.mpBegin == text.mpEnd) ? L"list" : text.mpBegin;

    writer->BeginBlock(block);
    for (tGrobShockData* it = list->mpBegin; it != list->mpEnd; ++it) {
        if (ok)
            ok = FUN_00ac8050(writer, 0, it);
    }
    writer->EndBlock(block);

    if (((int)((char*)text.mpCap - (char*)text.mpBegin) & 0xfffffffe) > 2 && text.mpBegin != 0)
        operator_delete_(text.mpBegin);

    return ok;
}

// ---------------------------------------------------------------- 0x01012030

// The vector itself: begin/end/cap at +0/+4/+8.
struct cInsertVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCap;        // +0x08

    void Insert(void* pos, void* first, void* last, int allocator);   // 0x01012030
};

// eastl vector (4-byte EA::AutoRefCount elements) range-insert.
//
//   VecInsert(v, pos, first, last, allocator):
//     n = last - first;
//     if (n <= capacity - size) {
//         tail = end - pos;
//         if (n < tail) {
//             uninitialized_copy(end - n, end, end);      // ref-counted, raw dst
//             end += n;
//             move_backward(pos, end - n, end);
//             copy(first, last, pos);
//         } else {
//             uninitialized_copy(first + tail, last, end);
//             end += n - tail;
//             uninitialized_copy(pos, oldEnd, end);
//             end += tail;
//             move_backward(first, first + tail, pos + tail);
//         }
//     } else {
//         newCap = max(2 * size, n + size);  (1 if size == 0)
//         buf = operator_new(newCap * 4, "Simulator", ..., 0xd1);
//         memcpy(buf, begin, pos - begin);
//         dst = uninitialized_copy(first, last, buf + (pos - begin));
//         memcpy(dst, pos, oldEnd - pos);
//         free(begin);
//         begin = buf; end = dst + (oldEnd - pos); cap = buf + newCap * 4;
//     }
//
// 0x00829110 is eastl's ref-counted uninitialized copy with a write-back
// destination cursor; 0x00ac97a0 is the ref-counted move_backward;
// 0x006782c0 is the ref-counted copy.
//
// @ 0x01012030
void cInsertVec::Insert(void* pos, void* first, void* last, int unused)
{
    if (first == last)
        return;

    int n       = (int)((char*)last - (char*)first) >> 2;
    int capLeft = (int)((char*)mpCap - (char*)mpEnd) >> 2;

    if (n > capLeft) {
        // ---- reallocate and insert
        int size   = (int)((char*)mpEnd - (char*)mpBegin) >> 2;
        int newCap = size + size;
        if (size == 0)
            newCap = 1;
        if (newCap <= n + size)
            newCap = n + size;

        void* buf = 0;
        if (newCap != 0)
            buf = operator_new(newCap * 4, "Simulator", 0, 0, (const char*)0x013ebb38, 0xd1);

        void* endOld   = mpEnd;
        int   posBytes = (int)((char*)pos - (char*)mpBegin);
        memcpy(buf, mpBegin, posBytes);

        void* dst = (char*)buf + posBytes;
        move_range_range(&dst, (void**)first, (void**)last, (void**)dst, first);
        memcpy(dst, pos, (char*)endOld - (char*)pos);
        void* newEnd = (char*)dst + ((char*)endOld - (char*)pos);

        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete_(mpBegin);

        mpBegin = buf;
        mpEnd   = newEnd;
        mpCap   = (char*)buf + newCap * 4;
        return;
    }

    void* endOld = mpEnd;
    int   tail   = (int)((char*)endOld - (char*)pos) >> 2;

    if (n < tail) {
        // ---- the tail already has room: shift it back by n, overwrite pos
        int   nBytes = n * 4;
        void* src    = (char*)endOld - nBytes;
        void* cursor = 0;
        move_range_range(&cursor, (void**)src, (void**)endOld, (void**)endOld, first);
        mpEnd = (char*)endOld + nBytes;
        FUN_00ac97a0(pos, src, endOld);
        copy_impl_do_copy((void**)first, (void**)last, (void**)pos);
        return;
    }

    // ---- n >= tail: spill the tail past the new range, then fill in front
    int   tailBytes = tail * 4;
    void* dstA      = (char*)first + tailBytes;
    void* cursorA   = 0;
    move_range_range(&cursorA, (void**)dstA, (void**)last, (void**)endOld, first);
    mpEnd = (char*)endOld + (n - tail) * 4;

    void* endNew  = mpEnd;
    void* cursorB = 0;
    move_range_range(&cursorB, (void**)pos, (void**)endOld, (void**)endNew, first);
    mpEnd = (char*)endNew + tailBytes;

    FUN_00ac97a0(first, dstA, (char*)pos + tailBytes);
}

// ---------------------------------------------------------------- 0x01012330

// eastl::make_heap<tGrobShockData*, tGrobLess>
//
//   length = last - first;
//   if (length > 1) {
//       n = (length - 2) / 2 + 1;
//       do { --n; adjust_heap_grob(first, n, length, n, first[n], compare); } while (n);
//   }
//
// @ 0x01012330
void __cdecl FUN_01012330(tGrobShockData* first, tGrobShockData* last, tGrobLess compare)
{
    int length = (int)(last - first);
    if (length > 1) {
        int n = (length - 2) / 2 + 1;
        do {
            --n;
            adjust_heap_grob(first, n, length, n, first[n], compare);
        } while (n != 0);
    }
}

// ---------------------------------------------------------------- 0x010123d0

// eastl::sort_heap<tGrobShockData*, tGrobLess>
//
//   while (last - first > 1) { pop_heap(first, last, compare); --last; }
//
// @ 0x010123d0
void __cdecl FUN_010123d0(tGrobShockData* first, tGrobShockData* last, tGrobLess compare)
{
    while (last - first > 1) {
        FUN_01011a40(first, last, compare);
        --last;
    }
}

// ---------------------------------------------------------------- mission objects

struct cEmpire {
    int GetRandomEnemy(int flag);                     // 0x00c31a90
};

struct cStarManager {
    void* GetEmpireByID(void* key);                   // 0x00ba9370
    void* FUN_ba93b0();                               // 0x00ba93b0
};

struct cSPMissionManager {
    void* CreateMissionFromID(int id, int a, void* b, int c);   // 0x00fec590
};

struct cMission {
    virtual void  v0();                               // +0x00
    virtual void  v1();                               // +0x04
    virtual void  v2();                               // +0x08
    virtual void* GetEvent(int id);                   // +0x0c
    virtual void  d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void  d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void  d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void  d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void  d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void  d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void  d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void  d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void  d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void  d40();
    virtual void* vA4(int id, void* self, int a, int b);  // +0x0a4
};

struct cRaidEvent {
    int  GenerateBomberCount();                       // 0x00c5b530
    void SetTarget(int target);                       // 0x00c5b370
    void FUN_c47180(int a);                           // 0x00c47180
    void FUN_c5b390(int a);                           // 0x00c5b390
    void Accept();                                    // 0x00c485b0
};

struct cNounMgr {
    void* FUN_b8de30();                               // 0x00b8de30
    void* FUN_b1fdb0();                               // 0x00b1fdb0
};

struct cSimCtx {
    void FUN_e1c7f0(void** p);                        // 0x00e1c7f0
};

struct cStarRecordRef {
    void* GetCommContext(int id);                     // 0x00ce6950
};

struct cThunk {
    void* FUN_aeb7a0(void* a, void* b);               // 0x00aeb7a0
};

void* __cdecl GetPlayerEmpire();       // 0x01021300
void* __cdecl GetMissionManager();     // 0x00feb9f0
void* __cdecl StarManager();           // 0x00b3d2a0
void* __cdecl CommManager();           // 0x00b3d4a0

// ---------------------------------------------------------------- 0x01012450

struct cWarRaid {
    int Start(int arg1, void* arg2);      // 0x01012450  (ret 8)
};

// @ 0x01012450
int cWarRaid::Start(int arg1, void* arg2)
{
    int enemy = ((cEmpire*)GetPlayerEmpire())->GetRandomEnemy(1);
    if (enemy == 0)
        return 0;
    cSPMissionManager* mm = (cSPMissionManager*)GetMissionManager();
    if (arg1 == 0)
        return 0;

    void* avatar = ((cNounMgr*)arg1)->FUN_b8de30();
    void* av2    = ((cNounMgr*)avatar)->FUN_b1fdb0();
    void* civ    = ((cStarManager*)StarManager())->GetEmpireByID(av2);

    void* mission = mm->CreateMissionFromID(0x77184bae, arg1, civ, 0);
    if (mission == 0)
        return 0;

    void* raid = ((cMission*)mission)->GetEvent(0x3960c0a);
    if (raid == 0)
        return 0;

    int count = ((cRaidEvent*)raid)->GenerateBomberCount();
    ((cRaidEvent*)raid)->SetTarget(enemy);
    ((cRaidEvent*)raid)->FUN_c47180(arg1);
    ((cRaidEvent*)raid)->FUN_c5b390(count);
    ((cRaidEvent*)raid)->Accept();

    void* tmp = mission;
    ((cMission*)mission)->v0();
    ((cSimCtx*)arg2)->FUN_e1c7f0(&tmp);
    if (tmp)
        ((cMission*)tmp)->v1();
    return 1;
}

// ---------------------------------------------------------------- 0x01012540

struct cGrobWarRaid {
    int Start(int arg1, int arg2);        // 0x01012540  (ret 8)
};

// @ 0x01012540
int cGrobWarRaid::Start(int arg1, int arg2)
{
    if (arg1 == 0)
        return 0;
    void* empire = GetPlayerEmpire();
    void* x      = ((cStarManager*)StarManager())->FUN_ba93b0();
    void* mm = GetMissionManager();
    if (mm == 0)
        return 0;

    void* mission = ((cSPMissionManager*)mm)->CreateMissionFromID(0x25089345, arg1, empire, 0);
    if (mission == 0)
        return 0;

    void* raid = ((cMission*)mission)->GetEvent(0x3960c0a);
    if (raid == 0)
        return 0;

    ((cRaidEvent*)raid)->SetTarget((int)x);
    ((cRaidEvent*)raid)->FUN_c47180(arg1);
    int count = ((cRaidEvent*)raid)->GenerateBomberCount();
    ((cRaidEvent*)raid)->FUN_c5b390(count);
    ((cRaidEvent*)raid)->Accept();

    void* a = ((cMission*)mission)->vA4(0x8b756f4b, mission, 0, 0);
    void* b = ((cStarRecordRef*)arg1)->GetCommContext((int)a);
    ((cThunk*)CommManager())->FUN_aeb7a0(b, *(void**)((char*)empire + 0x84));

    void* tmp = mission;
    ((cMission*)mission)->v0();
    ((cSimCtx*)arg2)->FUN_e1c7f0(&tmp);
    if (tmp)
        ((cMission*)tmp)->v1();
    return 1;
}

// ---------------------------------------------------------------- 0x01012640

struct cGrobTeaseRaid {
    int Start(int arg1, int arg2);        // 0x01012640  (ret 8)
};

// @ 0x01012640
int cGrobTeaseRaid::Start(int arg1, int arg2)
{
    if (arg1 == 0)
        return 0;
    GetPlayerEmpire();
    void* x   = ((cStarManager*)StarManager())->FUN_ba93b0();
    void* av2 = ((cNounMgr*)((cNounMgr*)arg1)->FUN_b8de30())->FUN_b1fdb0();
    void* esi = ((cStarManager*)StarManager())->GetEmpireByID(av2);
    if (esi == 0)
        return 0;
    void* mm = GetMissionManager();
    if (mm == 0)
        return 0;

    void* mission = ((cSPMissionManager*)mm)->CreateMissionFromID(0x56afe39d, arg1, esi, 0);
    if (mission == 0)
        return 0;

    void* raid = ((cMission*)mission)->GetEvent(0x3960c0a);
    if (raid == 0)
        return 0;

    ((cRaidEvent*)raid)->SetTarget((int)x);
    ((cRaidEvent*)raid)->FUN_c47180(arg1);
    int count = ((cRaidEvent*)raid)->GenerateBomberCount();
    ((cRaidEvent*)raid)->FUN_c5b390(count);
    ((cRaidEvent*)raid)->Accept();

    void* tmp = mission;
    ((cMission*)mission)->v0();
    ((cSimCtx*)arg2)->FUN_e1c7f0(&tmp);
    if (tmp)
        ((cMission*)tmp)->v1();
    return 1;
}