// Slice s01022fd0: SP::nSpaceCheats cheat-console commands and the eastl pointer-container
// helpers used by the cSPUILayoutManager rbtree map.
// Targets: 01022FD0 cCommandMission::VerifyMission
//          01023030 eastl::vector<vector<int>>::~vector
//          01023180 FUN_01023180  rbtree-map range node destroy (returns advanced out)
//          010231E0 FUN_010231E0  rbtree-map range node destroy
//          01023270 FUN_01023270  partition (comparator-based)
//          010232F0 FUN_010232F0  insert/erase wrapper
//          010234A0 cCommandToolCheat::Execute (the "tool" cheat console command)
//          01023BE0 FUN_01023BE0
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s01022fd0.h"

using namespace EA::ArgScript;

namespace SP {
namespace nSpaceCheats {

struct LayoutNode;
// The intrusive rbtree node stored at LayoutNode::mpNode.
struct RbNode {
    void* mpKey;                                                // 0x000
    RbNode* mpNext;                                             // 0x004
};

struct LayoutNode {
    uint32_t pad00[3];                                          // 0x000..0x00c
    void*    mpNode;                                            // 0x00c
    uint32_t pad10[3];                                          // 0x010..0x01c
    void DoNukeSubtree(void* key);                              // 0x009A9600
};

// The 0x14-byte element of eastl::vector<eastl::vector<int>>: a vector<int> with an inline
// eastl sp allocator header (int at -4 marks "not the shared empty buffer").
struct IntVectorElem {
    int* mpBegin;                                               // 0x000 (points past a 4-byte header)
    int* mpEnd;                                                 // 0x004
    int* mpCapacity;                                            // 0x008
    void* mpAllocator;                                          // 0x00c
    uint32_t pad10;                                             // 0x010
};

void FUN_00b2af00(void* a, void* b);                            // 0x00B2AF00 (swap helper)
void FUN_01010c20(int** a, int** b, int (*cmp)(void*, void*));  // 0x01010C20
void FUN_0100fee0(int** a, int b, int c, int d);                // 0x0100FEE0
void FUN_01023070(int** a, int** b, int (*cmp)(void*, void*));  // 0x01023070

// ===========================================================================
// 0x01022fd0  VerifyMission: linear-scan of the game-noun list for a pointer
// ===========================================================================
// @ 0x01022fd0
void* cCommandMission::VerifyMission(uint32_t id)
{
    int** list = (int**)NounManager()->GetAllNouns();
    int*  node = *list;
    int*  cur  = node ? (int*)((char*)node - 0xc) : 0;
    int*  end  = (int*)((char*)list - 0xc);
    if (cur == end)
        return 0;
    for (;;) {
        if (cur == (int*)id && id != 0)
            break;
        int* next = (int*)cur[3];
        cur = next ? (int*)((char*)next - 0xc) : 0;
        if (cur == end)
            return 0;
    }
    int** vtbl = *(int***)cur;
    void* (__thiscall *fn)(void*, void*) = (void* (__thiscall *)(void*, void*))vtbl[3];
    return fn(cur, (void*)0x2aa5ada);
}

// ===========================================================================
// 0x01023030  eastl::vector<eastl::vector<int>>::~vector  (destroy [begin,end))
// ===========================================================================
// @ 0x01023030
void __stdcall vector_dtor_IntVector(IntVectorElem* begin, IntVectorElem* end)
{
    for (; begin < end; ++begin) {
        int* p = begin->mpBegin;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            operator delete[](p);
    }
}

// ===========================================================================
// 0x01023180  destroy every map node in [begin,end), returning the advanced copy
// ===========================================================================
// @ 0x01023180
LayoutNode* __stdcall FUN_01023180(LayoutNode* begin, LayoutNode* end, LayoutNode* out)
{
    if (begin == end)
        return out;
    do {
        RbNode* node = (RbNode*)begin->mpNode;
        while (node != 0) {
            begin->DoNukeSubtree(node->mpKey);
            RbNode* next = node->mpNext;
            operator delete[](node);
            node = next;
        }
        begin += 1;
        out += 1;
    } while (begin != end);
    return out;
}

// ===========================================================================
// 0x010231e0  destroy every map node in [begin,end)
// ===========================================================================
// @ 0x010231e0
void __stdcall FUN_010231e0(LayoutNode* begin, LayoutNode* end)
{
    for (; begin < end; begin += 1) {
        RbNode* node = (RbNode*)begin->mpNode;
        while (node != 0) {
            begin->DoNukeSubtree(node->mpKey);
            RbNode* next = node->mpNext;
            operator delete[](node);
            node = next;
        }
    }
}

// ===========================================================================
// 0x01023270  comparator-based partition, returns the partition boundary
// ===========================================================================
// @ 0x01023270
void* FUN_01023270(void** begin, void** end, int* ctx, int (*cmp)(void*, void*))
{
    while (true) {
        while (cmp(*begin, ctx) != 0)
            ++begin;
        while (cmp(ctx, end[-1]) != 0)
            --end;
        if (end <= begin)
            break;
        FUN_00b2af00(begin, end);
        ++begin;
    }
    if (ctx != 0)
        (*(void(**)(void*))((char*)*ctx + 4))(ctx);
    return begin;
}

// ===========================================================================
// 0x010232f0  insert/erase wrapper over the map's flat vector
// ===========================================================================
// @ 0x010232f0
void __cdecl FUN_010232f0(int** begin, int** end, int** src, int (*cmp)(void*, void*))
{
    (void)src;
    FUN_01010c20(begin, end, cmp);
    for (int** p = end; p < (int**)src; ++p) {
        if (cmp(*p, *begin) != 0) {
            int* old = *p;
            if (old != 0)
                (*(void(**)(void*))old)(old);
            int* a = *begin;
            if (old != a) {
                if (a != 0)
                    (*(void(**)(void*))a)(a);
                *p = a;
                if (old != 0)
                    (*(void(**)(void*, void*))((char*)*old + 4))(old, cmp);
            }
            if (old != 0)
                (*(void(**)(void*))old)(old);
            FUN_0100fee0(begin, 0, (int)((char*)end - (char*)begin) >> 2, 0);
            if (old != 0)
                (*(void(**)(void*))((char*)*old + 4))(old);
        }
    }
    unsigned n = (unsigned)((char*)end - (char*)begin) - 4;
    for (; 4 < (int)(n & 0xfffffffc); n -= 4) {
        FUN_01023070(begin, end, cmp);
        --end;
    }
}

// ===========================================================================
// 0x01023be0  cCommandAri::Execute  (the "ari" cheat console command)
//   flags: preroll | demo | monolith | ctmg | war
// ===========================================================================
// @ 0x01023be0
void cCommandAri::Execute(EA::ArgScript::cArguments* args)
{
    if (args->HasFlag("preroll")) {
        FUN_01034b90(FUN_00b3d470(FUN_01021230()));
        return;
    }
    if (args->HasFlag("demo")) {
        FUN_01021300();
        return;
    }
    if (args->HasFlag("monolith")) {
        FUN_01021300();
        return;
    }
    if (args->HasFlag("ctmg")) {
        FUN_01021300();
        return;
    }
    if (args->HasFlag("war")) {
        void* empire = FUN_01021300();
        void* game = SpaceGameGet();
        char* p = (char*)game;
        int* vec = (int*)(p + 0x30);
        int count = (vec[1] - vec[0]) / 4;
        for (int i = 0; i < count; ++i) {
            void* avatar = cGameNounManager_GetAvatar(NounManager(), vec[i]);
            void* other = (void*)StarManager();
            (void)other; (void)avatar; (void)empire;
        }
        return;
    }
}

// ===========================================================================
// 0x010234a0  cCommandToolCheat::Execute  (the "tool" cheat console command)
// ===========================================================================
// @ 0x010234a0
void cCommandToolCheat::Execute(EA::ArgScript::cArguments* args)
{
    int numArgs = args->NumArguments();
    if (numArgs == 4) {
        Output(mpFormatParser, "%s\n", args->operator[](1));
    } else if (numArgs == 3) {
        Output(mpFormatParser, "%s\n", args->operator[](1));
    } else if (numArgs == 2) {
        Output(mpFormatParser, "%s\n", args->operator[](1));
    }
}

} // namespace nSpaceCheats
} // namespace SP
