// Link-time callee contracts for cScenarioTutorials::cScenarioTutorials (0x00ef9d90), built through
// the /GL + link /LTCG lane (tools/matching/ltcg.py). The empty default-argument temporaries
// (HashFn/EqFn) only fold onto one frame byte when c2 sees the callee chain's facts at link time;
// with unresolved callees it keeps the conservative distinct-temp layout.
//
// Facts below are read from the original executable, not decompiled:
//  - StepSetBig::Construct (0x00ef86c0, ret 0x1c) and StepSetSmall::Construct (0x00ef8770) are
//    declared in _at_00ef0000.cpp but defined in other slices' translation units, so this companion
//    supplies their link-time facts: each reads only nBucketCount (cmp 2 / < 2) and the allocator
//    argument (dwords at +0x00 and +0x14); the five functor references are never read.
//  - The ctor and both StepSet ctors are called from outside this /GL set in the original
//    (cTutorialApp's TU; the StepSet ctors take this in ecx and ret 8): export them, or c2 gives
//    the in-set-only ones register ABIs and drops the (provably dead) functor arguments instead of
//    folding their temporaries.
//  - Stopwatch::Stopwatch (0x0093a560) and LimitStopwatch::SetTimeLimit (0x0093a480) live in the
//    EA framework module; stubs below model their native effects (both self-align their own frames,
//    so their callers do not need realignment) and are exported to keep their standard conventions.

// r36a09r scratch sink (volatile: keeps the stub's reads live without a game image)
extern "C" volatile unsigned g_r36a09r_ltcg_sink = 0;

namespace eastl { class fixed_hashtable_allocator; }
struct HashFn;                 // empty functors: mangling only needs the tags
struct ModRangeHashing;
struct RangedHash;
struct EqFn;
struct UseSelf;

struct StepSetBig
{
    void Construct(unsigned int n, const HashFn& h, const ModRangeHashing& h2, const RangedHash& rh,
                   const EqFn& e, const UseSelf& ek, const eastl::fixed_hashtable_allocator& a);
};
struct StepSetSmall
{
    void Construct(unsigned int n, const HashFn& h, const ModRangeHashing& h2, const RangedHash& rh,
                   const EqFn& e, const UseSelf& ek, const eastl::fixed_hashtable_allocator& a);
};

// target and in-set callees: standard thiscall (external callers in the original)
#pragma comment(linker, "/EXPORT:??0cScenarioTutorials@@QAE@XZ")
#pragma comment(linker, "/EXPORT:??0StepSetBig@@QAE@ABUHashFn@@ABUEqFn@@@Z")
#pragma comment(linker, "/EXPORT:??0StepSetSmall@@QAE@ABUHashFn@@ABUEqFn@@@Z")

__declspec(noinline) void StepSetBig::Construct(unsigned int n, const HashFn&, const ModRangeHashing&,
                                                const RangedHash&, const EqFn&, const UseSelf&,
                                                const eastl::fixed_hashtable_allocator& a)
{
    // 0x00ef86c0: reads n and allocator dwords +0x00/+0x14; h/h2/rh/e/ek never read
    const unsigned* pa = (const unsigned*)&a;
    g_r36a09r_ltcg_sink = n;
    g_r36a09r_ltcg_sink += pa[0];
    g_r36a09r_ltcg_sink += pa[5];
}

__declspec(noinline) void StepSetSmall::Construct(unsigned int n, const HashFn&, const ModRangeHashing&,
                                                  const RangedHash&, const EqFn&, const UseSelf&,
                                                  const eastl::fixed_hashtable_allocator& a)
{
    // 0x00ef8770: same read set as 0x00ef86c0 (bucket count, allocator +0x00/+0x14)
    const unsigned* pa = (const unsigned*)&a;
    g_r36a09r_ltcg_sink = n + 1;
    g_r36a09r_ltcg_sink += pa[0];
    g_r36a09r_ltcg_sink += pa[5];
}

// Stopwatch (0x0093a560): zeroes [this+0x00..0x10], stores a float constant at [this+0x14],
// calls its starter with the int argument, then (bool arg set) seeds via rdtsc.
extern "C" int r36a09r_stopwatch_start(int);        // 0x0093a1a0: stays unresolved (masked)
struct Stopwatch
{
    unsigned char raw[0x18];
    Stopwatch(int n, bool startNow);
};
__declspec(noinline) Stopwatch::Stopwatch(int n, bool startNow)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    for (int i = 0; i <= 4; ++i) *(unsigned*)&raw[4 * i] = 0;
    *(float*)&raw[0x14] = 1.0f;
    g_r36a09r_ltcg_sink += r36a09r_stopwatch_start(n);
    if (startNow) g_r36a09r_ltcg_sink += 1;
}

// LimitStopwatch::SetTimeLimit (0x0093a480, ret 8: unsigned + bool): reads the dword limit,
// runs it through x87 double math with local spills (that is what makes the native function
// align its OWN frame), writes [this+0x10..0x17].
struct LimitStopwatch
{
    unsigned char raw[0x18];
    void SetTimeLimit(unsigned v, bool startTimer);
};
__declspec(noinline) void LimitStopwatch::SetTimeLimit(unsigned v, bool startTimer)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    volatile double d = (double)v;
    volatile double q = d / 1000.0;
    *(unsigned*)&raw[0x10] = startTimer ? 1u : 0u;
    *(unsigned*)&raw[0x14] = v;
    g_r36a09r_ltcg_sink += (unsigned)q;
}
