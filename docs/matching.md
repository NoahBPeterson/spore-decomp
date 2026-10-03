# Byte-exact matching (stage 2)

## Toolchain
- `tools/matching/cl.sh` runs **cl 15.00.30729.01 (VS2008 SP1, x86)** under wine, taken from
  Microsoft's `VCForPython27.msi` (SHA-1 `7800d037ba962f288f9b952001106d35ef57befe`, verified)
  and kept in `work/toolchain/` (git-ignored; never commit Microsoft binaries).
- RTM vs SP1 is still open. The Rich header was destroyed by SteamStub, and the manifest's
  9.0.21022.8 CRT binding is SP1's default too. So far every function matches with SP1.
  If residual mismatches appear, test them with a VS2008 RTM cl (15.00.21022.08).

## Workflow
1. `tools/matching/disasm.py work/SporeApp.analysis.bin <va>` prints the original instructions.
2. Write candidate spellings into a scratch file, then run
   `tools/matching/try_variants.py <scratch.cpp> <va>`, which ranks every function by diff bytes.
3. Move the winner into `match/<subsystem>/*.cpp`, add it to `match/manifest.txt`, and run
   `tools/matching/run_all.py`. That recompiles and re-verifies the whole set, so it stays green.
4. `tools/matching/cmpobj.py` is the verifier. It masks relocations on our side (COFF
   DIR32/REL32/...) and on the original's side (.reloc absolute addresses).

## Recovered build settings (evidence-based, per module)
| Setting | Evidence |
|---|---|
| `/O2` with frame-pointer omission | `/Oy-` breaks every match so far; `/O1` and `/Os` diverge |
| `/MD` (dynamic CRT) | CRT calls go through the IAT (`mov ebp,[__imp_towlower]; call ebp`) |
| C++ (`/TP`), `/EHsc` | mangled class methods, EH tables elsewhere |
| Mixed optimization | some modules look `/Od` (e.g. hash table near 0x0050E850): to verify |

## Codegen levers learned on this binary
- **Byte swaps use the intrinsics** `_byteswap_ushort` / `_byteswap_ulong`. A shift/or swap
  becomes `rol`, and a byte-wise memory swap spills to the stack.
- **`return true;` / `return false;`** yield `mov al,1` / `xor al,al`. Returning a comparison
  yields full-width `mov eax,1` / `xor eax,eax`.
- **Loop shape matters.** `while (n--) h = f(*s++);` matched; `for (; n; --n)` did not
  (register assignment and `dec`/`sub` choice differ).
- 16-bit ops with constants preloaded into registers come from intrinsic results being
  compared as `unsigned short`.

## Tally
`run_all.py` prints it. Currently **4 / 4 attempted byte-exact**, out of ~96,420 functions.
