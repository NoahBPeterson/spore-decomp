// slice s009ccfe0 -- nSPCreatureAnim creature-static-data init and context-target
// frame queries (retail /O2 build of the dev module SPCreatureAnim/creature_spore.obj).
//
//   @ 0x009ccfe0  `anonymous namespace'::cParentIndexCommand::Execute
//   @ 0x009cd040  `anonymous namespace'::cBlockBlockCommand::Execute
//   @ 0x009cd110  nSPCreatureAnim::InitCreatureStaticDataFromBlocksFile
//   @ 0x009cd580  nSPCreatureAnim::FUN_009cd580  (context-target frame query, mode switch)
//   @ 0x009cd930  nSPCreatureAnim::FUN_009cd930  (context-target point accumulate)
//   @ 0x009cda70  nSPCreatureAnim::FUN_009cda70  (quaternion -> euler)
//   @ 0x009cdb20  nSPCreatureAnim::FUN_009cdb20  (biased pow clamp)
//   @ 0x009cdbe0  nSPCreatureAnim::FUN_009cdbe0  (hermite blend / clamp)
//   @ 0x009cdce0  nSPCreatureAnim::biasedSigmoid
//   @ 0x009cddc0  nSPCreatureAnim::FUN_009cddc0  (epsilon sign)
//
// Field offsets are the retail ones read from the disassembly (the dev PDB predates this build).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char uint8;
typedef unsigned int  uint32;
typedef unsigned long uint32ul;

namespace checkerlib {
class vector_3 { public: float x, y, z; };
class vector_4 { public: float x, y, z, w; };
}
using checkerlib::vector_3;
using checkerlib::vector_4;

// -------------------------------------------------------------------- external code
// Resolved from the `// 0x...` annotations by tools/difftest/resolve.py.
void  __cdecl FUN_009a9b70(const char* path, int cap, char* out, char** tail);   // 0x009a9b70
void* __cdecl FUN_0099c1a0(float* out, const float* q, const float* v);          // 0x0099c1a0 QuaternionVectorTransform
void* __cdecl FUN_0099c0b0(float* out, const float* a, const float* b);          // 0x0099c0b0
void* __cdecl FUN_0099c310(float* out, const float* q, const float* v);          // 0x0099c310
int   __cdecl nSPCreatureAnim_EvaluateContextTargetQuery(void* creature, int one, int key,
                                                         void* q, int z0, int z1);  // 0x009b2340
int   __cdecl nSPCreatureAnim_FinalizeCreature(void* creature);                  // 0x009c4a30
void  __cdecl FUN_009b3010(void* elem);                                          // 0x009b3010
void  __cdecl FUN_009cbdb0(char* instance);                                      // 0x009cbdb0
void  __cdecl FUN_009c1dc0(void* data, int bAll);                                // 0x009c1dc0 creature_static_data::Clear
float __cdecl FUN_009cdbe0(float, float, float, float, float);                   // 0x009cdbe0 (self)
double __cdecl lib_cblock_FUN_011e08f0(double, double);                          // 0x011e08f0 _CIpow  (this=ecx ignored)

// EA ArgScript runtime
void* __cdecl EA_ArgScript_CreateParser();                                       // 0x008408d0
void  __cdecl EA_ArgScript_cCommandBase_ctor(void* p);                           // 0x0083c800
void  __cdecl EA_ArgScript_AppPropsFields_ctor(void* p);                         // 0x0083cdd0
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
// eastl::map<unsigned long,unsigned long>::operator[]  -- __thiscall, key passed by address
struct ulong_map {
    unsigned long* __thiscall get(const unsigned long* key); // 0x00a2e060
};
void* __cdecl EA_RectT_assign(void* dst, const void* src);                       // 0x00572600 EA::RectT<float>::operator=
void* __cdecl map_node_free(void* node, void* key);                              // 0x009a9600
void  __cdecl operator_delete(void* p);                                          // 0x00f47380 ??3

extern "C" __declspec(dllimport) void* __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) char* __cdecl fgets(char*, int, void*);
extern "C" __declspec(dllimport) int   __cdecl fclose(void*);
extern "C" __declspec(dllimport) char* __cdecl strrchr(const char*, int);
extern "C" __declspec(dllimport) char* __cdecl strstr(const char*, const char*);
extern "C" __declspec(dllimport) int   __cdecl sprintf(char*, const char*, ...);
extern "C" __declspec(dllimport) int   __cdecl fprintf(void*, const char*, ...);
extern "C" __declspec(dllimport) void* __cdecl __iob_func(void);

extern float DAT_01485720;   // 1.0f
extern float DAT_013eb1bc;   // -1.0f
extern float DAT_014479b0;   // 1e-06f
extern float DAT_01485378;   // 0.0f
extern float DAT_0147b9f0;   // 6.0f
extern float DAT_014007f4;   // 15.0f
extern float DAT_01473c70;   // 10.0f
extern float DAT_01471064;   // 0.5f
extern double DAT_013f1298;  // 0.5 (loaded with fld qword)
extern unsigned long g_01550fe4;   // "crncmd" name entry
extern unsigned long g_01550fec;   // "isplant" name entry
extern unsigned long g_01550fcc;   // "cal3DRootBlockIndex" name entry
extern unsigned long g_01550ff0;   // "numBlocks" name entry
extern unsigned long g_01550fc4;   // "block" name entry
extern void* g_vtbl_crncmd;        // 0x014474f8
extern void* g_vtbl_isplant;       // 0x0144745c
extern void* g_vtbl_calrtblki;     // 0x01447474
extern void* g_vtbl_numblk;        // 0x0144748c
extern void* g_vtbl_blkblk;        // 0x014474a4

namespace nSPCreatureAnim {

struct creature_body_static_data;             // retail size 0x468
struct creature_body_instance_data;           // retail size 0x2bc

// ArgScript arguments block; MainArguments is a __thiscall returning the arg array.
struct cArguments {
    unsigned long* __thiscall MainArguments(int n);          // 0x00838320
};

// The parser interface: only the vtable slot at +0x9c (GetBlockCount) is used.
struct cIParser {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38();
    virtual unsigned long GetBlockCount(unsigned long id);    // vtable +0x9c
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44();
};

// creature_static_data: only the fields this slice touches (the real object is larger).
// Pertinent retail offsets: name @0x208, body vector @0x384/0x388/0x38c,
// count @0x3c8, an extra flag @0x3f0.
struct creature_static_data {
    char  pad_000[0x208];
    char  name[0x104];                  // 0x208 (wide chars)
    char  pad_30c[0x384 - 0x30c];
    creature_body_static_data* bodies_begin;   // 0x384
    creature_body_static_data* bodies_end;     // 0x388
    creature_body_static_data* bodies_cap;     // 0x38c
    char  pad_390[0x3c8 - 0x390];
    int   count_3c8;                    // 0x3c8
    char  pad_3cc[0x3f0 - 0x3cc];
    int   flag_3f0;                     // 0x3f0
};

// The two ArgScript command objects (both are polymorphic; only Execute is defined).
struct cParentIndexCommand {
    cIParser* parser;                   // +4
    char      pad_08[4];
    char*     state;                    // +0xc
    virtual void Execute(cArguments& args);          // 0x009ccfe0
};

struct cBlockBlockCommand {
    cIParser* parser;                   // +4
    char      pad_08[0x30 - 0x08];
    char*     state;                    // +0x30
    virtual void Execute(cArguments& args);          // 0x009cd040
};

// stub for the __thiscall body-reset helper called at 0x009b3180 (ecx = body)
struct body_clear_t {
    void __thiscall Clear0();                        // 0x009b3180
};

}  // namespace nSPCreatureAnim

// =====================================================================
// 0x009ccfe0  cParentIndexCommand::Execute   (this+4 = parser, this+0xc = state)
// =====================================================================
// @ 0x009ccfe0
void nSPCreatureAnim::cParentIndexCommand::Execute(cArguments& args)
{
    unsigned long* av = args.MainArguments(1);
    int v = (int)parser->GetBlockCount(*av);
    if (v == -1) {
        *(int*)(*(int*)(state + 0x40) + 0x1fc) = -1;
        return;
    }
    unsigned long key = (unsigned long)v;
    unsigned long* r = ((ulong_map*)(state + 0x48))->get(&key);
    *(int*)(*(int*)(state + 0x40) + 0x1fc) = (int)*r;
}

// =====================================================================
// 0x009cd040  cBlockBlockCommand::Execute   (this+4 = parser, this+0x30 = state)
// =====================================================================
// @ 0x009cd040
void nSPCreatureAnim::cBlockBlockCommand::Execute(cArguments& args)
{
    unsigned long* av = args.MainArguments(1);
    *(int*)(state + 8) = 0;
    *(int*)(state + 0x40) = *(int*)(state + 4) * 0x468
                          + *(int*)(*(int*)(state + 0x44) + 0x384);
    ((body_clear_t*)*(void**)(state + 0x40))->Clear0();
    *(int*)(*(int*)(state + 0x40) + 0x108) = 0x40626000;
    *(int*)(*(int*)(state + 0x40) + 0x104) = -1;
    *(int*)(*(int*)(state + 0x40) + 0x1f8) = *(int*)(state + 4);
    *(int*)(*(int*)(state + 0x40) + 0x200) = -2;
    unsigned long v = parser->GetBlockCount(*av);
    *(unsigned long*)(*(int*)(state + 0x40) + 0x21c) = v;
    char* cur = *(char**)(state + 0x40);
    unsigned long* r = ((ulong_map*)(state + 0x48))->get((unsigned long*)(cur + 0x21c));
    *r = *(unsigned long*)(cur + 0x1f8);
    (*(void(__thiscall**)(cIParser*, void*))(*(char**)parser + 0x8c))(parser, this);
}

// =====================================================================
// 0x009cd110  InitCreatureStaticDataFromBlocksFile
// =====================================================================
namespace {
struct block_mgr {                                   // the local scope object on the stack
    char  pad_000[0x10];
    int   f_010;                    // 0x010
    char* f_014;                    // 0x014
    void* f_018;                    // 0x018
    char  pad_01c[0x38 - 0x1c];
    void* f_038;                    // 0x038 (block-list head)
};
struct cfg_block {                                   // local_600-ish (a sub-object)
    char  pad_000[0x14];
    void* f_014;                    // 0x014 (some ptr)
};
}

// @ 0x009cd110
int __cdecl FUN_009cd110(nSPCreatureAnim::creature_static_data* param_1, const char* param_2)
{
    char local_679 = 0;
    void* fp;
    char local_610[16];
    char local_600[0x1c8];
    char acStack_438[1036];
    char local_674[0x400];
    void* local_628;
    void* local_620 = 0;
    int   local_61c = 0;
    int   local_618 = 0;

    fp = fopen(param_2, "r");
    if (fp == 0)
        return 0;
    fgets(local_610, 0xd, fp);
    fclose(fp);
    FUN_009c1dc0(param_1, 0);

    {
        char* s = (char*)param_2;
        char* d = param_1->name;
        char c;
        do { c = *s; d[(int)(s - (char*)param_2)] = c; ++s; } while (c != 0);
    }
    {
        char* tail;
        FUN_009a9b70(param_2, 0x200, local_600, &tail);
        char* dot = strrchr(tail, '.');
        *dot = 0;
        char* d = param_1->name;
        while (tail != dot + 1) {
            *(short*)d = (short)*tail++;
            d += 2;
        }
    }

    // build the block manager object
    char* base = local_674;
    *(void**)(base + 0x00) = base;
    *(int*) (base + 0x0c) = 0x1ff0ee3;
    *(int*) (base + 0x10) = 0;
    *(int*) (base + 0x14) = 0;
    for (int i = 0; i < 12; ++i) *(int*)(base + 0x20 + i * 4) = 0;  // zero 12-float block
    *(void**)(base + 0x58) = param_1;
    *(void**)(base + 0x48) = base;              // local_624 = local_628
    *(void**)(base + 0x4c) = 0;                 // local_620
    *(int*) (base + 0x50) = 0;                  // local_61c
    *(int*) (base + 0x54) = 0;                  // local_618

    if (strstr(local_610, "group blocks") == 0) {
        void* parser = EA_ArgScript_CreateParser();
        if (parser != 0)
            (*(void(__cdecl**)(void*))(*(char**)parser))(parser);
        (*(void(__cdecl**)(void*))(*(char**)parser + 8))(parser);
        (*(void(__cdecl**)(void*, void*))(*(char**)parser + 0x10))(parser, base + 0x0c);
        (*(void(__cdecl**)(void*, int, int))(*(char**)parser + 0x28))(parser, 4, 5);

        void* cmd;
        cmd = EAAllocate(0x10, "Anim/crncmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_crncmd; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fe4, cmd);

        cmd = EAAllocate(0x10, "Anim/isplantcmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_isplant; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fec, cmd);

        cmd = EAAllocate(0x10, "Anim/calrtblkicmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_calrtblki; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fcc, cmd);

        cmd = EAAllocate(0x10, "Anim/numblkcmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_cCommandBase_ctor(cmd); *(void**)cmd = g_vtbl_numblk; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550ff0, cmd);

        cmd = EAAllocate(0x34, "Anim/blkblkcmd", 0, 0, 0, 0);
        if (cmd == 0) cmd = 0;
        else { EA_ArgScript_AppPropsFields_ctor(cmd); *(void**)cmd = g_vtbl_blkblk; }
        (*(void(__cdecl**)(void*, unsigned long, void*))(*(char**)parser + 0x14))
            (parser, g_01550fc4, cmd);

        (*(void(__cdecl**)(void*))(*(char**)parser + 0x30))(parser);
        char ok = (*(char(__cdecl**)(void*, void*))(*(char**)parser + 0x48))(parser, local_674);
        local_679 = ok;
        if (ok == 0) {
            char* msg = (*(char*(__cdecl**)(void*))(*(char**)parser + 0x58))(parser);
            sprintf(acStack_438, "error occurred: '%s'\n", msg);
            fprintf((char*)__iob_func() + 0x40, "%s", acStack_438);
        }
        (*(void(__cdecl**)(void*, int))(*(char**)parser + 0x34))(parser, ok == 0);
        (*(void(__cdecl**)(void*))(*(char**)parser + 0xc))(parser);
        if (parser != 0)
            (*(void(__cdecl**)(void*))(*(char**)parser + 4))(parser);

        int bodyBytes = (int)((char*)param_1->bodies_end - (char*)param_1->bodies_begin);
        int n = bodyBytes / 0x468;
        if (n != 0) {
            int off = 0;
            do {
                int* p = (int*)((char*)param_1->bodies_begin + off + 0x200);
                if (*p != -2 && *p != -1) {
                    unsigned long* r = ((ulong_map*)base)->get((unsigned long*)p);
                    *p = (int)*r;
                }
                off += 0x468;
            } while (--n != 0);
            ok = 0;
            local_679 = ok;
        }
        if (ok != 0) {
            int bodyBytes2 = (int)((char*)param_1->bodies_end - (char*)param_1->bodies_begin);
            int n2 = bodyBytes2 / 0x468;
            if (n2 != 0) {
                int off2 = 0;
                do {
                    FUN_009b3010((char*)param_1->bodies_begin + off2 + 0x150);
                    if ((*(unsigned char*)((char*)param_1->bodies_begin + off2 + 0x154) & 4) != 0)
                        ++param_1->count_3c8;
                    off2 += 0x468;
                } while (--n2 != 0);
            }
            if (param_1->count_3c8 == 0 && param_1->flag_3f0 == 0)
                FUN_009cbdb0((char*)param_1);
            local_679 = (char)nSPCreatureAnim_FinalizeCreature(param_1);
        }
    }
    {
        void* node = local_620;
        while (node != 0) {
            map_node_free(node, (void*)base);
            void* next = *(void**)((char*)node + 4);
            operator_delete(node);
            node = next;
        }
    }
    return local_679;
}

// =====================================================================
// 0x009cd580  FUN_009cd580  (context-target frame query, mode switch)
// =====================================================================
// @ 0x009cd580
void __cdecl FUN_009cd580(char* self, float* out_pos, void* out_rect, int use_rot)
{
    float local_50;
    float local_4c;
    float local_48;
    float local_44[3];
    float local_38[3];
    float local_2c[3];
    float local_20[4];
    float local_10[4];
    int mode = *(int*)(self + 0x274);

    if (mode == 0) {
        if (out_pos != 0) {
            float* p = (float*)FUN_0099c1a0(local_2c, (float*)(self + 0x3c),
                                            (float*)(self + 0x278));
            out_pos[2] = *(float*)(self + 0x20) + p[2];
            out_pos[1] = *(float*)(self + 0x1c) + p[1];
            out_pos[0] = *(float*)(self + 0x18) + p[0];
        }
        if (out_rect != 0) {
            float q0 = *(float*)(self + 0x3c);
            float q120 = *(float*)(self + 0x290);
            float q1 = *(float*)(self + 0x284);
            float f40 = *(float*)(self + 0x40);
            float q2 = *(float*)(self + 0x28c);
            float f44a = *(float*)(self + 0x44);
            float q3 = *(float*)(self + 0x288);
            float f48a = *(float*)(self + 0x48);
            float f44b = *(float*)(self + 0x44);
            float q1b = *(float*)(self + 0x284);
            float q3b = *(float*)(self + 0x288);
            float f48b = *(float*)(self + 0x48);
            float f48c = *(float*)(self + 0x48);
            float q1c = *(float*)(self + 0x284);
            float q3c = *(float*)(self + 0x288);
            float f44c = *(float*)(self + 0x44);
            ((float*)out_rect)[0] = ((q0 * q120 + q1 * f48a) - f44a * q3) + f40 * q2;
            ((float*)out_rect)[1] = ((f40 * q120 + f44b * q1b) + q3b * f48b) - q2 * q0;
            ((float*)out_rect)[2] = ((f44c * q120 - f40 * q1c) + q3c * q0) + q2 * f48c;
            ((float*)out_rect)[3] = ((q120 * f48c - q0 * q1c) - f40 * q3c) - q2 * f44c;
        }
        return;
    }
    if (mode == 1) {
        if (out_pos != 0) {
            out_pos[0] = *(float*)(self + 0x278);
            out_pos[1] = *(float*)(self + 0x27c);
            out_pos[2] = *(float*)(self + 0x280);
        }
        if (out_rect != 0) {
            ((float*)out_rect)[0] = *(float*)(self + 0x284);
            ((float*)out_rect)[1] = *(float*)(self + 0x288);
            ((float*)out_rect)[2] = *(float*)(self + 0x28c);
            ((float*)out_rect)[3] = *(float*)(self + 0x290);
        }
        return;
    }
    if (mode != 2 || *(int*)(self + 0x294) == 0 || **(int**)(self + 0x294) == 0
        || nSPCreatureAnim_EvaluateContextTargetQuery(&self, 1, **(int**)(self + 0x294),
                                                      self + 0x298, 0, 0) == 0) {
        if (out_pos != 0) {
            out_pos[0] = 0.0f; out_pos[1] = 0.0f; out_pos[2] = 0.0f;
        }
        if (out_rect != 0) {
            ((float*)out_rect)[0] = 0.0f;
            ((float*)out_rect)[1] = 0.0f;
            ((float*)out_rect)[2] = 0.0f;
            ((float*)out_rect)[3] = 1.0f;
        }
        return;
    }
    {
        int* tgt = *(int**)(self + 0x294);
        float* body = (float*)((char*)tgt + *(int*)(self + 0x60) * 0x2bc + 0x2e4);
        if (out_pos != 0) {
            if (use_rot == 0) {
                float* p = (float*)FUN_0099c1a0(local_38, (float*)(tgt + 0xf),
                                                body + 4);
                out_pos[0] = p[0] + (float)tgt[6];
                out_pos[1] = (float)tgt[7] + p[1];
                out_pos[2] = (float)tgt[8] + p[2];
            }
            else {
                float* q = *(float**)(body);
                local_48 = (float)tgt[0x1c];
                local_50 = q[0x10c] * local_48;
                local_4c = q[0x110] * local_48;
                local_48 = q[0x114] * local_48;
                float* p = (float*)FUN_0099c1a0(local_44, (float*)(tgt + 0xf), &local_50);
                out_pos[0] = p[0] + (float)tgt[6];
                out_pos[1] = p[1] + (float)tgt[7];
                out_pos[2] = p[2] + (float)tgt[8];
            }
        }
        if (out_rect != 0) {
            float* src;
            float* dst;
            if (use_rot == 0) { src = body + 0x40 / 4; dst = local_10; }
            else { src = (float*)(*(int*)body + 0x118); dst = local_20; }
            void* r = FUN_0099c0b0(dst, (float*)(tgt + 0xf), src);
            EA_RectT_assign(out_rect, r);
        }
    }
}

// =====================================================================
// 0x009cd930  FUN_009cd930  (context-target point accumulate)
// =====================================================================
// @ 0x009cd930
void __cdecl FUN_009cd930(char* self, float* pos)
{
    float local_18;
    float local_14;
    float local_10;
    float local_c[3];

    if (*(int*)(self + 0x274) != 2)
        return;
    int* tgt = *(int**)(self + 0x294);
    if (tgt == 0 || *tgt == 0)
        return;
    if (nSPCreatureAnim_EvaluateContextTargetQuery(&self, 1, *tgt, self + 0x298, 0, 0) == 0)
        return;
    local_18 = pos[0] - (float)tgt[6];
    int* body = (int*)(self + *(int*)(self + 0x60) * 0x2bc + 0x2e4);
    local_14 = pos[1] - (float)tgt[7];
    local_10 = pos[2] - (float)tgt[8];
    float* p = (float*)FUN_0099c310(local_c, (float*)(tgt + 0xf), &local_18);
    *(float*)((char*)body + 0x58) = *(float*)((char*)body + 0x58) + p[0];
    *(float*)((char*)body + 0x5c) = p[1] + *(float*)((char*)body + 0x5c);
    *(float*)((char*)body + 0x60) = p[2] + *(float*)((char*)body + 0x60);
    *(float*)((char*)body + 0x64) = *(float*)((char*)body + 0x64) + DAT_01485720;
    int* inst = *(int**)(body);
    int* src = (int*)((char*)inst + 0x118);
    ((float*)((char*)body + 0x68))[0] = ((float*)src)[0];
    ((float*)((char*)body + 0x6c))[0] = ((float*)src)[1];
    ((float*)((char*)body + 0x70))[0] = ((float*)src)[2];
    ((float*)((char*)body + 0x74))[0] = ((float*)src)[3];
    *(float*)((char*)body + 0x78) = DAT_01485720;
    int idx = *(int*)((char*)inst + 0x1f8);
    int eax = idx * 2;
    unsigned char* pb = (unsigned char*)(*(int*)((char*)body + 4) + (eax >> 3) + 0x1b8);
    unsigned char bit = (unsigned char)(1 << (eax & 7));
    *pb |= bit;
}

// =====================================================================
// 0x009cda70  FUN_009cda70  (quaternion -> euler)
// =====================================================================
// @ 0x009cda70
float* __cdecl FUN_009cda70(float* out, const float* m)
{
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[0] = 0.0f;
    float fq = -m[6];
    float fVar2 = (float)sqrt((float)(1.0f - (float)(fq * fq)));
    out[1] = (float)atan2((double)fq, (double)fVar2);
    if (fq != 1.0f && fq != -1.0f) {
        float r = 1.0f / fVar2;
        out[0] = (float)atan2((double)(m[7] * r), (double)(m[8] * r));
        out[2] = (float)atan2((double)(m[3] * r), (double)(r * m[0]));
        return out;
    }
    out[0] = (float)atan2((double)(-m[5]), (double)(m[4]));
    out[2] = (float)atan2(0.0, 1.0);
    return out;
}

// =====================================================================
// 0x009cdb20  FUN_009cdb20  (biased pow clamp) -- x87, uses _CIpow
// =====================================================================
// @ 0x009cdb20
// Best-effort reconstruction: the x87 argument order of the two _CIpow calls
// (0x011e08f0, constant 2.0 at 0x013f1298) could not be pinned down from the
// disassembly, so the pow branch below is approximate (see partial.txt).
float __cdecl FUN_009cdb20(float a, float b)
{
    float res;
    if ((float)fabs((double)b) < 1.0f) {
        res = a * (a * b - b + 1.0f);
    }
    else if (0.0f <= b) {
        res = (float)pow(pow(2.0, (double)b), (double)a);
    }
    else {
        float d = (float)fabs((double)b) - a;
        res = 1.0f - (float)pow(pow((double)b, 2.0), (double)d);
    }
    if (res <= 0.0f)
        return 0.0f;
    if (1.0f < res)
        return 1.0f;
    return res;
}

// =====================================================================
// 0x009cdbe0  FUN_009cdbe0  (hermite blend / clamp)
// =====================================================================
// @ 0x009cdbe0
float __cdecl FUN_009cdbe0(float param_1, float param_2, float param_3,
                           float param_4, float param_5)
{
    float range  = param_3 - param_2;
    float range2 = param_5 - param_4;
    if (param_1 <= param_2) param_1 = param_2;
    if (param_1 > param_3) param_1 = param_3;
    param_1 = (float)fabs((double)((param_1 - param_2) / range));
    float res = param_4;
    // 0x9cdc5a: fcompi |t| (st0) vs |range2*1e-06| (st1); jbe skips the hermite blend
    if (param_1 > (float)fabs((double)(range2 * 1e-06f)))
        res = (((((param_1 * 6.0f - 15.0f) * param_1 + 10.0f) * param_1) * param_1)
               * param_1) * range2 + param_4;
    if (range2 > 0.0f) {
        if (!(res > param_4)) res = param_4;
        if (res > param_5) res = param_5;
    }
    else {
        if (!(res > param_5)) res = param_5;
        if (res > param_4) res = param_4;
    }
    return res;
}

// =====================================================================
// 0x009cdce0  biasedSigmoid
// =====================================================================
// @ 0x009cdce0
float __cdecl FUN_009cdce0(float param_1, float param_2, float param_3,
                           float param_4, float param_5, float param_6)
{
    float fVar1 = param_3 - param_2;
    if ((float)fabs((double)fVar1) <= 1e-06f)
        return (param_4 + param_5) * 0.5f;
    float fVar4 = (param_1 - param_2) / fVar1;
    float fVar2 = 0.0f;
    if (fVar4 <= 0.0f || (fVar2 = 1.0f, 1.0f < fVar4)) {
        fVar4 = fVar2;
    }
    float res;
    if (fVar4 < 1e-06f) {
        res = param_2;
    }
    else {
        res = (float)pow((double)fVar4, (double)param_6) * fVar1 + param_2;
    }
    return FUN_009cdbe0(res, param_2, param_3, param_4, param_5);
}

// =====================================================================
// 0x009cddc0  FUN_009cddc0  (epsilon sign)
// =====================================================================
// A register-convention static helper: its caller holds `v` in xmm1 and reads
// the result from xmm0 (see codegen.md 6.3). Keep it static and give it a
// same-TU stand-in caller so cl reproduces the convention.
// @ 0x009cddc0
static float FUN_009cddc0(float /*unused*/, float v)
{
    if (DAT_014479b0 > v)
        return -1.0f;
    if (v > DAT_014479b0)
        return 1.0f;
    return 0.0f;
}

float __cdecl probe_sign_009cddc0(float a, float b)
{
    return a + FUN_009cddc0(a, b);
}
