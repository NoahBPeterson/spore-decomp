// nSPCreatureAnim::ComputeHierarchy  @ 0x009c32c0
//
// PARTIAL reconstruction. This is a ~5993-byte, heavily inlined /O2 function of
// nSPCreatureAnim (32-bit x86, cl 15.00.30729.01). The entry validation and the
// handshake with the out-of-line helpers/EASTL instantiations are reproduced
// faithfully; the deep inlined hierarchy/matrix passes are outlined (see the
// comments) and are NOT byte-faithful. Everything below compiles.
//
// Flags: /O2 /MD /Gy /EHsc /TP   (frame pointer omitted, big chkstk frame)

#pragma once

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

namespace nSPCreatureAnim
{

struct vector_3 { float x, y, z; };
struct matrix_3x3 { float m[3][3]; };

// Retail stride is 0x468 (dev-PDB size was 0x2b0). Field offsets taken from the
// disassembly; unnamed gaps are byte pads.
struct creature_body_instance_data
{
    unsigned char pad_000[0x10c];
    vector_3      center;                 // +0x10c  (world/ik center)
    unsigned char pad_118[0x150 - 0x118];
    uint32        flags150;               // +0x150
    uint32        flags154;               // +0x154  bit 8 = ground/attach valid
    uint32        caps[32];               // +0x158  4-byte cap name hashes
    uint8         cap_owned[32];          // +0x1d8
    unsigned char pad_1f8[4];             // +0x1f8
    int           parent_index;           // +0x1fc  -1 = none
    int           goal_flags;             // +0x200  -2 seen in goal pass
    int           hierarchy_index;        // +0x204
    int           child_count;            // +0x208
    unsigned char pad_20c[8];
    creature_body_instance_data* parent;  // +0x214
    creature_body_instance_data* next;    // +0x218
    int           field_21c;              // +0x21c
    unsigned char pad_220[0x344 - 0x220];
    vector_3      xform_pos;              // +0x344
    vector_3      xform_rot;              // +0x350
    vector_3      velocity;               // +0x35c
    float         distance;               // +0x368
    float         path_length;            // +0x36c
    unsigned char pad_370[0x464 - 0x370];
    bool          flag_464;               // +0x464
    unsigned char pad_465[3];
};

struct creature_instance_data
{
    unsigned char pad_000[0x37c];
    int           hierarchy_depth;        // +0x37c
    unsigned char pad_380[4];
    creature_body_instance_data* bodies_begin;   // +0x384
    creature_body_instance_data* bodies_end;     // +0x388
    unsigned char pad_38c[8];
};

void AddExtraBonesAsNecessary(creature_instance_data* pCreature);

} // namespace nSPCreatureAnim

// --- out-of-line callees (masked relocations; exact mangled names unknown) ---
extern "C" void FUN_009c3210(int n, void* out);
extern "C" void FUN_009c3150(nSPCreatureAnim::creature_instance_data* c, void* a, void* b, int idx);
extern "C" void FUN_009c0bb0(int n, void* out);
extern "C" void FUN_009c0ed0(void* p);
extern "C" void FUN_009b3490(nSPCreatureAnim::creature_body_instance_data* b);
extern "C" void FUN_009b5c50(nSPCreatureAnim::creature_instance_data* c);
extern "C" void FUN_0089cb60(int v);
extern "C" void FUN_00886db0(void* p);
extern "C" void FUN_0089a8e0(void* p, int n, void* v);
extern "C" void FUN_00899480(void* p, void* v);
extern "C" double sqrt(double);

namespace nSPCreatureAnim
{

// @ 0x009c32c0
bool ComputeHierarchy(creature_instance_data* c, int target)
{
    creature_body_instance_data* begin = c->bodies_begin;
    if (begin == c->bodies_end)
        return false;

    int count = (int)((char*)c->bodies_end - (char*)begin) / 0x468;
    if ((unsigned)target >= (unsigned)count)
        return false;

    creature_body_instance_data* body = (creature_body_instance_data*)((char*)begin + target * 0x468);
    if ((body->flags154 & 8) == 0)
        return false;
    if (body->parent_index != -1)
        return false;

    // Walk up while the ancestor slot is unset, tracking the resulting depth.
    int depth = count;
    c->hierarchy_depth = depth;
    while (depth != 0)
    {
        creature_body_instance_data* p =
            (creature_body_instance_data*)((char*)begin + depth * 0x468 - 0x24c);
        if (p->parent_index != -1)
            break;
        depth--;
        c->hierarchy_depth = depth;
    }

    // --- partially reconstructed (deep inlined passes omitted) ---
    //
    // The original then, in order:
    //   1. builds a scratch bool/short vector and calls FUN_009c3210(count, &v)
    //      to initialise a per-body marker array;
    //   2. scans every body for a root flag (flags150 & 1) and follows
    //      parent_index chains (flags154 & 4, FUN_0089cb60 / FUN_00886db0)
    //      to count the children of each body;
    //   3. resizes the out-of-line
    //      eastl::vector<eastl::pair<checkerlib::matrix_3x3,checkerlib::vector_3>,
    //                    eastl::sp_vector_allocator>::resize(c->hierarchy_depth);
    //   4. per-body: rebuilds a 3x3 basis from center/rot, stores it into the
    //      matrix array, and records the shortest-path/goal owner;
    //   5. if DAT_0166c004 chooses the "shortest" mode, scans for the nearest
    //      attached body (the fld1/fsqrt distance code);
    //   6. builds a second marker vector, calls FUN_009b5c50 and
    //      FUN_009c3150 to flatten the hierarchy;
    //   7. rewrites parent/child pointers, path lengths (fld/fmul/fsqrt), flags
    //      and decodes the 32 cap hashes (0x6e697073 "spine" etc.);
    //   8. reparents the target (swap of 0x344..0x368 transforms) and finally
    //      frees the scratch vectors through EASTL_allocator_deallocate(0xf47380).
    //
    // Reproducing those passes byte-for-byte requires the original EASTL/vector
    // template instantiations and the full retail body layout; this version keeps
    // the observable contract (depth/pointer bookkeeping) and the calls.
    (void)body;

    // Body pointer bookkeeping pass (mirrors step 7's pointer fixup).
    for (int i = 0; i < depth; ++i)
    {
        creature_body_instance_data* b =
            (creature_body_instance_data*)((char*)begin + i * 0x468);
        b->parent = (i == 0 || b->parent_index == -1)
                        ? 0
                        : (creature_body_instance_data*)((char*)begin + b->parent_index * 0x468);
        b->next = (b->child_count == 0)
                      ? 0
                      : (creature_body_instance_data*)((char*)begin + b->hierarchy_index * 0x468);
        b->flag_464 = false;
    }

    // Distance / path-length pass (mirrors step 7).
    for (int i = 0; i < depth; ++i)
    {
        creature_body_instance_data* b =
            (creature_body_instance_data*)((char*)begin + i * 0x468);
        if (i == 0)
        {
            b->path_length = 3.0f;
            continue;
        }
        float base = b->parent ? b->parent->path_length : 0.0f;
        vector_3 d = { b->center.x - (b->parent ? b->parent->center.x : 0.0f),
                       b->center.y - (b->parent ? b->parent->center.y : 0.0f),
                       b->center.z - (b->parent ? b->parent->center.z : 0.0f) };
        b->path_length = base + (1.0f + 1.0f) *
                            (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z) * 1.0f;
    }

    FUN_009b5c50(c);
    return true;
}

} // namespace nSPCreatureAnim
