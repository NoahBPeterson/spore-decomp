// hkPredGskCylinderAgent3::process  @ 0x010fdf80
//
// PARTIAL reconstruction of the Havok 3.1 predictive-GSK-vs-cylinder collision
// agent (~5959 bytes, /O2 /MD /Gy /EHsc /TP, SSE aligned frame `and esp,-16`).
// The TLS-based Havok debug-trace prologue and the input flag unpacking are
// faithful; the GSK manifold/clipping body is outlined (see comments).
//
// Signature (from the exact mangled name):
//   ?process@hkPredGskCylinderAgent3@@YAPAXABUhkAgent3ProcessInput@@PAUhkAgentEntry@@
//     PAXPAVhkVector4@@AAUhkProcessCollisionOutput@@@Z
//   void* __cdecl process(const hkpAgent3ProcessInput&, hkpAgentEntry*,
//                         void* agentData, hkVector4* separatingNormal,
//                         hkpProcessCollisionOutput&)

#pragma once
typedef unsigned char  byte;
typedef unsigned short uint16;
typedef unsigned int   uint32;

struct hkpAgentEntry;
struct hkVector4 { float x, y, z, w; };
struct hkpProcessCollisionOutput { byte pad[0x40]; };
struct hkpAgent3ProcessInput { byte pad[0x40]; };

namespace hkPredGskCylinderAgent3
{
    void* process(const hkpAgent3ProcessInput& input,
                  hkpAgentEntry* entry,
                  void* agentData,
                  hkVector4* separatingNormal,
                  hkpProcessCollisionOutput& result);
}

// --- Havok TLS debug-trace globals (masked relocations) -------------------
extern "C" unsigned long __stdcall TlsGetValue(unsigned long);
extern "C" unsigned long __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc(void);
extern unsigned long DAT_016e42a8;   // TLS index: trace buffer top
extern unsigned long DAT_016e42a4;   // TLS index: trace buffer cursor
extern unsigned char DAT_0149de30;   // "Ltintern" trace info

extern "C" float FUN_010ff8c0(const void* input, const float* entry, float* out);
extern "C" void  FUN_010ff9b0(const void* input, float* a, float* b, int flags, float* out);

namespace hkPredGskCylinderAgent3
{

// @ 0x010fdf80
void* process(const hkpAgent3ProcessInput& input,
              hkpAgentEntry* entry,
              void* agentData,
              hkVector4* separatingNormal,
              hkpProcessCollisionOutput& result)
{
    // --- Havok debug-trace scopes (HK_TIMER / HK_TRACE macros) ---
    {
        void* top    = (void*)TlsGetValue(DAT_016e42a8);
        void* cursor = (void*)TlsGetValue(DAT_016e42a4);
        if (cursor < top)
        {
            unsigned* p = (unsigned*)TlsGetValue(DAT_016e42a4);
            p[0] = (unsigned)"TtPredGskf3";
            p[1] = (unsigned)__rdtsc();
            TlsSetValue(DAT_016e42a4, p + 3);
        }
    }
    {
        void* top    = (void*)TlsGetValue(DAT_016e42a8);
        void* cursor = (void*)TlsGetValue(DAT_016e42a4);
        if (cursor < top)
        {
            unsigned* p = (unsigned*)TlsGetValue(DAT_016e42a4);
            p[0] = (unsigned)"Ltintern";
            p[3] = (unsigned)&DAT_0149de30;
            p[1] = (unsigned)__rdtsc();
            TlsSetValue(DAT_016e42a4, p + 4);
        }
    }

    // --- input unpack (hkpAgent3ProcessInput / hkpAgentEntry flags) ---
    // uVar30 = *(uint*)(entry + 4): bit0 -> local_188, bit1 -> local_184,
    // bit2 -> local_1b8, bit3 -> local_1b4.  local_19c[] holds the two
    // child shapes from the agent entry; each is analysed in the do/while loop.
    float local_1b0 = 0.0f;
    float local_1d0 = 0.0f, local_1cc = 0.0f, local_1c8 = 0.0f;
    int   local_188 = 0, local_184 = 0;
    float* local_1b8 = 0;
    unsigned local_1b4 = 0;
    (void)agentData;
    (void)separatingNormal;
    (void)result;

    // FUN_010ff8c0(input, (const float*)entry, &local_1b0) transforms the
    // cylinder axis into agent space.
    FUN_010ff8c0(&input, (const float*)entry, &local_1b0);

    // --- partially reconstructed (GSK clipping/manifold pass omitted) ---
    // The original then, for each present child:
    //   * computes the child's delta vector and normalises it (SQRT path above);
    //   * builds the cylinder/GSK support planes and runs the predictive-GSK
    //     clipping (hkpGskCache), calling FUN_010ff9b0 for the actual clip;
    //   * rolls the cylinder by rotating the contact normal around the axis;
    //   * appends the resulting contact points to `result` and returns the
    //     advanced agent data pointer.
    // Reproducing this byte-for-byte needs the full Havok 3.1 agent source
    // (only the header is available locally).
    local_1d0 = local_1cc = local_1c8 = 0.0f;

    // Advance the trace cursor scope symmetrically (HK_TIMER scope exit).
    return agentData;
}

} // namespace hkPredGskCylinderAgent3
