// @ 0x009a1ee0  nSPCreatureAnim::CreateAnimationBindRecords
// (name from the dev-build PDB: its local classes bind_record_helper / variant_helper and their
// members 0x0099c7b0 InitChannel, 0x009a0f10, 0x009a1c60, 0x009a1a60 are called from here only).
//
// Builds the animation_bind_data for one (animation, creature) pair:
//   1. two passes (pass 0 / pass 1 = normal / mirrored binding) over the animation channels; plain
//      channels get bind records through bind_record_helper, grouped channels (VariantGroup != 0)
//      go through variant_helper, which expands every combination into a variant bit;
//   2. records with no variant bit left are dropped; a pass that leaves some required (flag 4)
//      channel unbound is rolled back; if both passes fail the result is emptied (return false);
//   3. records are partitioned: creature-state records first, then root-body records, then the
//      records that target a secondary body; the targeted ones are split per variant bit and, per
//      variant, topologically ordered so that a body is evaluated after the bodies it targets.
//      Unkeyed / POS-less secondaries and dependency cycles only print a warning and set flag 2.
//
// The helpers are local-class members of the same TU in the original, so cl gave them custom
// register conventions (InitChannel: ESI/EDX, AddBindRecord: ECX/EAX, GenerateVariants: ESI,
// RemoveEdges: EAX/ECX, variant_helper ctor: EAX/EDI). They live in other slices and are declared
// here with plain conventions; the order and values of their arguments are the original's.
// Flags: /O2 /MD /Gy /TP /GS- (no /EHsc: the variant_helper local has a dtor but no EH frame;
// no /GS cookie despite the uint[255] stack buffer).

#include "types.h"

typedef unsigned int uint;

extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void* __cdecl _alloca(unsigned int);
#pragma intrinsic(memset, memcpy)
void operator_delete_array(void* p);                 // 0x00f47380 (operator delete[])

namespace nSPCreatureAnim {

// ---------------------------------------------------------------------------
// data
// ---------------------------------------------------------------------------
struct animation_body_bind_record                     // 0x10 bytes
{
    enum flags { CREATURE_STATE = 1, MIRROR_SAGITTAL = 2, ROOT_SCALE_HACK = 4, EVENTS_ONLY = 8,
                 TARGET_UNRESOLVED = 0x10, TARGET_POS = 0x20 };

    /* 00h */ uint64_t VariantMask;
    /* 08h */ uint KeyDataMask : 24;
              uint VariantGroup8 : 8;
    /* 0Ch */ uint8_t BodyIndex8;
    /* 0Dh */ uint8_t ChannelIndex8;
    /* 0Eh */ uint8_t TargetBodyIndex8;
    /* 0Fh */ uint8_t Flags;
};

template <typename T> inline void swap(T& a, T& b)
{
    T temp(a);
    a = b;
    b = temp;
}

template <typename T> inline const T& min(const T& a, const T& b)
{
    return (b < a) ? b : a;
}

// eastl::vector<animation_body_bind_record, eastl::sp_vector_allocator>
struct BindRecordVector
{
    typedef animation_body_bind_record value_type;

    value_type* mpBegin;
    value_type* mpEnd;
    value_type* mpCapacity;
    uint        mAllocator;

    uint size() const { return (uint)(mpEnd - mpBegin); }
    value_type& operator[](uint n) { return mpBegin[n]; }
    value_type& back() { return *(mpEnd - 1); }

    void resize(uint n);                                              // 0x00890490 (out of line)
    void DoInsertValues(value_type* pos, uint n, const value_type& v); // 0x0088fe00
    void DoInsertValue(value_type* pos, const value_type& v);          // 0x0092a100

    value_type* erase(value_type* first, value_type* last)
    {
        value_type* result = first;
        for (value_type* p = last; p != mpEnd; ++p, ++result)
            *result = *p;
        mpEnd -= (last - first);
        return first;
    }

    // resize as inlined here (the out-of-line copy is the 0x00890490 one)
    void resize_inline(uint n)
    {
        if (n > size())
            DoInsertValues(mpEnd, n - size(), value_type());
        else
            erase(mpBegin + n, mpEnd);
    }

    void push_back(const value_type& v)
    {
        if (mpEnd < mpCapacity)
        {
            value_type* p = mpEnd++;
            if (p)
                *p = v;
        }
        else
            DoInsertValue(mpEnd, v);
    }
};

// eastl::vector<unsigned long, eastl::sp_vector_allocator>
struct ULongVector
{
    uint* mpBegin;
    uint* mpEnd;
    uint* mpCapacity;
    uint  mAllocator;

    ~ULongVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete_array(mpBegin);
    }
};

struct animation_channel_static_data
{
    char     pad0[0x8c];
    uint     Context[8];        // +0x8c  context passed to the target lookups
    uint16_t Flags;             // +0xac  1 = bindable, 4 = required
    uint8_t  BodyIndex;         // +0xae
    uint8_t  VariantGroup;      // +0xaf
};

struct animation_static_data
{
    char  pad0[0x144];
    uint  NumChannels;                                // +0x144
    animation_channel_static_data** ChannelPointers;  // +0x148
    uint  NumFixups;                                  // +0x14c
    uint  FixupTableOffsetBytes;                      // +0x150
    uint  BranchPredicatesMask;                       // +0x154
    uint  BranchPredicatesMatch;                      // +0x158
};

struct creature_body_static_data { uint8_t data[0x468]; };

struct creature_static_data
{
    char pad0[0x384];
    creature_body_static_data* BodiesBegin;           // +0x384
    creature_body_static_data* BodiesEnd;             // +0x388
};

struct animation_bind_data
{
    /* 00h */ uint64_t ChannelMask;          // channels that produced at least one record
    /* 08h */ uint64_t KeyedChannelMask;     // ... with key data
    /* 10h */ uint     Flags;                // 1 = has secondary targets, 2 = needs smoothing
    /* 14h */ uint     NumVariants;
    /* 18h */ uint     NumVariantGroups;
    /* 1Ch */ BindRecordVector Records;
};

// `CreateAnimationBindRecords'::`7'::bind_record_helper  (0xd1c bytes in retail)
struct bind_record_helper
{
    /* 000h */ animation_static_data* animation;
    /* 004h */ creature_static_data*  creature;
    /* 008h */ BindRecordVector*      records;
    /* 00Ch */ uint    num_creature_state_records;
    /* 010h */ uint    num_root_records;
    /* 014h */ uint    num_targeted_records;
    /* 018h */ uint8_t BodyGroups[255][9];
    /* 910h */ animation_channel_static_data* channel;
    /* 914h */ uint    target_selected_bidxs[255];
    /* D10h */ uint    num_target_selected_bidxs;
    /* D14h */ int     default_target;
    /* D18h */ bool    target_symmetric;
};

// `CreateAnimationBindRecords'::`8'::variant_helper  (0xc24 bytes in retail)
struct variant_helper
{
    struct group_channel_marker { uint first_channel_idx; uint required; };
    struct variant_set
    {
        uint group, bidx, selection_idx, num_bound, required;
        ULongVector bidxs;
        uint pad;
    };

    /* 000h */ group_channel_marker group_channel_markers[64];
    /* 200h */ uint variant_idx;
    /* 204h */ uint num_groups;
    /* 208h */ BindRecordVector* records;
    /* 20Ch */ uint begin_base_bind_record;
    /* 210h */ uint end_base_bind_record;
    /* 214h */ bind_record_helper* BindHelper;
    /* 218h */ variant_set variant_sets[64];
    /* C18h */ uint num_variant_sets;
    /* C1Ch */ animation_static_data* animation;
    /* C20h */ creature_static_data* creature;

    variant_helper(bind_record_helper* helper);       // 0x0099f8b0 (EAX = this, EDI = helper)
};

// work context of the dependency sort (0x0099c910 takes it in EAX)
struct dependency_sort
{
    uint*    counts;        // per body: number of bodies it still waits for
    uint8_t* ready;         // stack of bodies whose count dropped to zero
    uint*    num_edges;
    uint8_t* edges;         // numBodies x numBodies, 0xff-terminated rows
    uint     stride;
    uint*    num_ready;
};

// helpers (other slices)
bool CheckBranchPredicates(creature_static_data* creature, uint mask, uint match);   // 0x0099c710
void InitChannel(bind_record_helper* helper, uint channel, uint pass);               // 0x0099c7b0
uint FindTargetBodies(uint* out, uint max, creature_static_data* creature, void* context,
                      uint pass, uint symmetric);                                     // 0x009b2340
void AddBindRecord(bind_record_helper* helper, uint idx, uint bidx, uint channel, uint group,
                   uint64_t variantMask, uint pass);                                  // 0x009a0f10
bool PrepareVariantSets(variant_helper* helper, uint pass);                          // 0x009a1c60
uint GenerateVariants(variant_helper* helper, uint pass);                            // 0x009a1a60
void RemoveEdges(dependency_sort* sort, uint8_t* row, uint8_t body);                 // 0x0099c910
void AnimWarning(const char* fmt, ...);                                              // 0x00c2e4e0

// ---------------------------------------------------------------------------
// @ 0x009a1ee0
// ---------------------------------------------------------------------------
bool CreateAnimationBindRecords(animation_static_data* animation, creature_static_data* creature,
                                animation_bind_data* bind)
{
    typedef animation_body_bind_record record;

    bind->Flags = 0;
    bind->Records.resize(0);
    bind->NumVariants = 0;
    bind->NumVariantGroups = 0;
    bind->ChannelMask = 0;
    bind->KeyedChannelMask = 0;

    if (creature == 0 ||
        !CheckBranchPredicates(creature, animation->BranchPredicatesMask, animation->BranchPredicatesMatch))
        return false;

    BindRecordVector& records = bind->Records;
    uint bidxs[255];

    bind_record_helper helper;
    helper.animation = animation;
    helper.creature = creature;
    helper.records = &records;
    helper.num_creature_state_records = 0;
    helper.num_root_records = 0;
    helper.num_targeted_records = 0;

    variant_helper variants(&helper);
    const char* msg;

    uint variantIdx = 0;
    bool passFailed[2];
    passFailed[0] = false;
    passFailed[1] = false;

    for (uint pass = 0; pass < 2; ++pass)
    {
        uint beginIdx = records.size();
        uint64_t requiredMask = 0;
        uint savedVariantIdx = variantIdx;

        memset(helper.BodyGroups, 0xff, sizeof(helper.BodyGroups));
        variants.group_channel_markers[0].first_channel_idx = 0xffffffff;
        variants.group_channel_markers[0].required = 0;
        // spread marker 0 over the other 63 (forward overlapping copy: rep movsd)
        memcpy(&variants.group_channel_markers[1], &variants.group_channel_markers[0],
               sizeof(variants.group_channel_markers) - sizeof(variants.group_channel_markers[0]));
        variants.num_groups = 0;
        variants.num_variant_sets = 0;

        uint numChannels = animation->NumChannels;
        for (uint i = 0; i < numChannels; ++i)
        {
            animation_channel_static_data* channel = animation->ChannelPointers[i];
            uint flags = channel->Flags;
            if ((flags & 1) == 0)
                continue;

            uint required = flags & 4;
            if (required)
                requiredMask |= (uint64_t)1 << i;

            uint8_t group = channel->VariantGroup;
            if (group != 0)
            {
                uint g = group;
                uint maxGroup = 63;
                uint idx = min(g, maxGroup);
                if (variants.group_channel_markers[idx].first_channel_idx == 0xffffffff)
                {
                    variants.num_variant_sets += 1;
                    variants.num_groups += 1;
                    variants.group_channel_markers[idx].first_channel_idx = i;
                }
                variants.group_channel_markers[idx].required |= required;
            }
            else
            {
                InitChannel(&helper, i, pass);
                uint n = FindTargetBodies(bidxs, 0xff, creature, channel->Context, pass, 0);
                if (n != 0)
                {
                    for (uint k = 0; k < n; ++k)
                        AddBindRecord(&helper, k, bidxs[k], i, 0, ~(uint64_t)0, pass);
                }
            }
        }

        uint endIdx = records.size();
        if (variants.num_groups != 0)
        {
            variants.begin_base_bind_record = beginIdx;
            variants.end_base_bind_record = endIdx;
            variants.variant_idx = variantIdx;
            uint generated = 0;
            if (PrepareVariantSets(&variants, pass))
                generated = GenerateVariants(&variants, pass);
            uint64_t keep = ~(((uint64_t)1 << variantIdx) - 1);
            variantIdx += generated;
            keep &= ((uint64_t)1 << variantIdx) - 1;
            for (uint k = beginIdx; k < endIdx; ++k)
                records[k].VariantMask &= keep;
        }
        else
        {
            uint64_t bit = (uint64_t)1 << variantIdx;
            for (uint k = beginIdx; k < endIdx; ++k)
                records[k].VariantMask = bit;
            ++variantIdx;
        }

        // drop the records that lost every variant bit
        uint n = records.size();
        uint64_t usedMask = 0;
        for (uint k = beginIdx; k < n; )
        {
            record& r = records[k];
            if (r.VariantMask == 0)
            {
                if (r.Flags & record::CREATURE_STATE)
                    helper.num_creature_state_records -= 1;
                else if (r.BodyIndex8 == 0)
                    helper.num_root_records -= 1;
                if (r.TargetBodyIndex8 != 0xff)
                    helper.num_targeted_records -= 1;
                r = records[n - 1];
                --n;
            }
            else
            {
                uint64_t bit = (uint64_t)1 << r.ChannelIndex8;
                bind->ChannelMask |= bit;
                usedMask |= bit;
                if (records[k].KeyDataMask != 0)
                    bind->KeyedChannelMask |= bit;
                ++k;
            }
        }
        records.resize_inline(n);

        if ((usedMask & requiredMask) != requiredMask)
        {
            // a required channel could not be bound: roll this pass back
            records.erase(records.mpBegin + beginIdx, records.mpBegin + n);
            passFailed[pass] = true;
            variantIdx = savedVariantIdx;
        }
    }

    if (passFailed[0] && passFailed[1])
    {
        bind->Records.resize(0);
        bind->NumVariants = 0;
        bind->ChannelMask = 0;
        bind->KeyedChannelMask = 0;
        return false;
    }

    uint numRecords = records.size();
    bind->NumVariants = numRecords ? variantIdx : 1;
    bind->NumVariantGroups = variants.num_groups + 1;

    // creature-state records first ...
    uint numState = helper.num_creature_state_records;
    uint j = numState;
    for (uint k = 0; k < numState; ++k)
    {
        if ((records[k].Flags & record::CREATURE_STATE) == 0)
        {
            for (; j < numRecords; ++j)
            {
                if (records[j].Flags & record::CREATURE_STATE)
                {
                    swap(records[k], records[j]);
                    break;
                }
            }
        }
    }

    // ... then the root-body records ...
    uint rootEnd = helper.num_root_records + numState;
    j = rootEnd;
    for (uint k = numState; k < rootEnd; ++k)
    {
        if (records[k].BodyIndex8 != 0)
        {
            for (; j < numRecords; ++j)
            {
                if (records[j].BodyIndex8 == 0)
                {
                    swap(records[k], records[j]);
                    break;
                }
            }
        }
    }

    if (helper.num_targeted_records != 0)
    {
        bind->Flags |= 1;
        uint numBodies = (uint)(creature->BodiesEnd - creature->BodiesBegin);

        // per body: 1 = has records, 2 = is a target, 4 = has POS keys, 8 = has a target
        uint8_t* bodyFlags = (uint8_t*)_alloca(numBodies);
        memset(bodyFlags, 0, numBodies);

        for (uint k = rootEnd; k < numRecords; ++k)
        {
            record& r = records[k];
            uint8_t& f = bodyFlags[r.BodyIndex8];
            f |= 1;
            if (r.Flags & record::TARGET_POS)
                f |= 4;
            uint8_t target = r.TargetBodyIndex8;
            if (target < numBodies)
            {
                if (r.Flags & record::TARGET_UNRESOLVED)
                {
                    // resolve the target channel to the body bound to it in the same variant
                    r.TargetBodyIndex8 = 0xff;
                    for (uint m = 0; m < numRecords; ++m)
                    {
                        record& o = records[m];
                        if (o.ChannelIndex8 == target && (r.VariantMask & o.VariantMask) == r.VariantMask)
                        {
                            r.TargetBodyIndex8 = o.BodyIndex8;
                            break;
                        }
                    }
                    r.Flags &= ~record::TARGET_UNRESOLVED;
                }
                if (r.TargetBodyIndex8 < numBodies)
                {
                    f |= 8;
                    bodyFlags[r.TargetBodyIndex8] |= 2;
                }
            }
        }

        bool anyTargeting = false;
        for (uint b = 0; b < numBodies; ++b)
        {
            uint8_t f = bodyFlags[b];
            if (f == 2)
            {
                msg = "This animation has channels that target a secondary that isn't keyed, will use smoothing to decouple.\n";
                goto warn;
            }
            if (f & 1)
            {
                if ((f & 6) == 2)
                {
                    msg = "This animation has channels that target a secondary that doesn't have POS key data, will use smoothing to decouple.\n";
                    goto warn;
                }
                if ((f & 8) == 0)
                    anyTargeting = true;
            }
        }
        if (!anyTargeting)
            goto cycle;

        {
            // records of targeting bodies go last
            int lo = (int)rootEnd - 1;
            int hi = (int)numRecords;
            for (;;)
            {
                do { ++lo; } while ((bodyFlags[records[lo].BodyIndex8] & 8) == 0);
                do { --hi; } while ((bodyFlags[records[hi].BodyIndex8] & 8) != 0);
                if (lo >= hi)
                    break;
                swap(records[lo], records[hi]);
            }
            uint firstTargeting = hi + 1;

            // split the targeting records per variant bit
            uint64_t allVariants = 0;
            for (uint k = firstTargeting; k < numRecords; ++k)
            {
                record* r = &records[k];
                uint64_t v = r->VariantMask;
                allVariants |= v;
                uint64_t rest = v & (v - 1);
                r->VariantMask = rest ^ v;
                while (rest != 0)
                {
                    uint64_t next = rest & (rest - 1);
                    uint64_t bit = next ^ rest;
                    records.push_back(*r);
                    records.back().VariantMask = bit;
                    rest = next;
                }
            }

            uint numSplit = records.size();
            uint numBodies2 = numBodies * numBodies;
            uint8_t* edges = (uint8_t*)_alloca(numBodies2);
            uint* counts = (uint*)_alloca(numBodies * 4);
            uint8_t* ready = (uint8_t*)_alloca(numBodies);
            uint8_t* order = (uint8_t*)_alloca(numBodies);
            uint first = firstTargeting;

            while (allVariants != 0)
            {
                uint64_t restVariants = allVariants & (allVariants - 1);
                uint64_t bit = restVariants ^ allVariants;

                memset(edges, 0xff, numBodies2);
                memset(counts, 0, numBodies * 4);
                uint numReady = 0;
                int numOrdered = 0;
                uint numEdges = 0;

                // edge target -> source for every targeting record of this variant
                for (uint k = first; k < numSplit; ++k)
                {
                    record& r = records[k];
                    if ((r.VariantMask & bit) != 0 && r.TargetBodyIndex8 != 0xff)
                    {
                        uint8_t* row = &edges[r.TargetBodyIndex8 * numBodies];
                        uint8_t body = r.BodyIndex8;
                        uint m = 0;
                        do
                        {
                            uint8_t e = row[m];
                            if (e == body)
                                break;
                            if (e == 0xff)
                            {
                                row[m] = r.BodyIndex8;
                                counts[r.BodyIndex8] += 1;
                                numEdges += 1;
                                break;
                            }
                        } while (++m < numBodies);
                    }
                }

                dependency_sort sort;
                sort.counts = counts;
                sort.ready = ready;
                sort.num_edges = &numEdges;
                sort.edges = edges;
                sort.stride = numBodies;
                sort.num_ready = &numReady;

                // bodies that target nothing in this variant are ready
                for (int k = (int)rootEnd; k < (int)firstTargeting; ++k)
                {
                    record& r = records[k];
                    if ((r.VariantMask & bit) != 0)
                    {
                        uint8_t body = r.BodyIndex8;
                        RemoveEdges(&sort, &edges[body * numBodies], body);
                    }
                }
                while (numReady != 0)
                {
                    --numReady;
                    uint8_t body = ready[numReady];
                    order[numOrdered++] = body;
                    RemoveEdges(&sort, &edges[body * numBodies], body);
                }
                if (numEdges != 0)
                    goto cycle;

                // this variant's records first
                uint split;
                if (restVariants != 0)
                {
                    int a = (int)first - 1;
                    int b = (int)numSplit;
                    for (;;)
                    {
                        do { ++a; } while ((records[a].VariantMask & bit) != 0);
                        do { --b; } while ((records[b].VariantMask & bit) == 0);
                        if (a >= b)
                            break;
                        swap(records[a], records[b]);
                    }
                    split = a;
                }
                else
                    split = numSplit;

                // and in dependency order
                int a = (int)first;
                for (int t = 0; t < numOrdered - 1; ++t)
                {
                    uint8_t body = order[t];
                    --a;
                    int b = (int)split;
                    for (;;)
                    {
                        do { ++a; } while (records[a].BodyIndex8 == body);
                        do { --b; } while (records[b].BodyIndex8 != body);
                        if (a >= b)
                            break;
                        swap(records[a], records[b]);
                    }
                }

                first = split;
                allVariants = restVariants;
            }
        }
    }
    goto done;

cycle:
    msg = "This animation has a secondary depedency cycles, will use smoothing to decouple.\n";
warn:
    AnimWarning(msg);
    bind->Flags |= 2;
done:
    return true;
}

}  // namespace nSPCreatureAnim
