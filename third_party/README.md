# Third-party libraries

These are statically linked into SporeApp.exe. They're excluded from the decompilation percentages because we
build them from upstream source instead of decompiling them. Versions come from strings in the binary.
1,704 of their functions (distinct addresses in the original image) are proven byte-identical to objects built
from these versions with VS2008 SP1 (`third_party/baseline_matches.csv`; was 1,149 before the build was scripted).

| Library | Version | Evidence | License |
|---|---|---|---|
| OpenSSL | 0.9.8g (19 Oct 2007) | "... part of OpenSSL 0.9.8g 19 Oct 2007" | OpenSSL/SSLeay |
| zlib | 1.2.3 | "deflate 1.2.3 Copyright 1995-2005" | zlib |
| libpng | 1.2.25 | "1.2.25" | libpng |
| libjpeg (IJG) | **6a** (7 Feb 1996) | string "6a  7-Feb-96" and "Copyright (C) 1996, Thomas G. Lane". An earlier version of this file said 6b; that was wrong. | IJG |

## Status: reproducible vendoring

Everything lives in `third_party/manifest.json` (URLs, SHA-256, license, per-library cl flags, OpenSSL Configure
options) and `tools/third_party/` (run from the repo root, with `.venv/bin/python`; needs `perl` and `make` for OpenSSL):

    tools/third_party/fetch.py            # download or reuse tarballs (work/oss is a seed), verify SHA-256, extract to work/third_party/src
    tools/third_party/build_faithful.py   # cl 15.00.30729 via wine (tools/matching/cl.sh) -> work/third_party/obj/<lib>/ and lib/<lib>.lib (lib.exe)
    tools/third_party/verify.py           # CI check: libresolve vs work/SporeApp.analysis.bin, exit 1 if any baseline function stops matching
    tools/third_party/cblock_resolve.py   # classify the 748 lib_cblock functions -> third_party/cblock_resolution.csv

A clean run (fetch from the seed, build everything, verify) takes about 4 minutes on 10 cores. Fetch also works from
the network (all four URLs tested) and fails closed on a hash mismatch.

Per-library flags recovered by byte-matching (all of them were needed; each one was proven by a jump in matches):

| Library | Flags | Result (unique original functions matched) |
|---|---|---|
| all | `/O2 /arch:SSE /MD /Gy /TC`. `/arch:SSE` is the "P6 instructions" switch: it makes cl emit `cmovcc` and `fcomip`; without it every function using `min/max` or a float compare differs. `/arch:SSE2`, `/O1`, `/Ox`, `/Oy-`, `/Os`, `/Od` do not help | |
| zlib 1.2.3 | the above, 12 source files | 33 (was 29) |
| libpng 1.2.25 | the above, `/I zlib`, `png*.c` | 117 (was 113) |
| libjpeg 6a | the above with a **custom `jconfig.h`** (`third_party/jpeg-6a/jconfig.h`: jconfig.vc with `boolean` left as the default `int`, not `unsigned char`). 6a ships no jconfig.vc. Only 29 functions matched with `unsigned char`, 125 with `int` | 134 (was 31) |
| OpenSSL 0.9.8g | `perl Configure VC-WIN32 no-asm no-err no-ocsp no-idea no-bf no-ssl2`, then `BN_LLONG` undefined in `opensslconf.h`, plus `-DOPENSSL_THREADS -DDSO_WIN32 -DOPENSSL_SYSNAME_WIN32 -DWIN32_LEAN_AND_MEAN -DL_ENDIAN -D_CRT_SECURE_NO_DEPRECATE` | 1,385 (was 941) |

How each OpenSSL option was identified: `no-err` (`OPENSSL_NO_ERR`): every `ERR_put_error` call has file=NULL, line=0
(this alone accounted for about 350 of the 748 cblock functions); `no-ocsp`: `STANDARD_EXTENSION_COUNT` is 29, not 37;
`no-idea`/`no-bf`: `SSL3_NUM_CIPHERS` is 65 and `OpenSSL_add_all_ciphers` registers no IDEA or Blowfish; `no-ssl2`:
`ssl23_get_server_method` has no SSL2 branch; `BN_LLONG` undefined: `PQ_64BIT` is a `BIGNUM` in the 2008 dev-build PDB
(`tools/pdb_type.py ssl3_record_st`), which moves `SSL3_STATE.tmp` by 16 bytes. The `no-asm` flag is an assumption: it is
consistent with every match so far, but not independently proven (asm routines such as bn_mul_add_words would show up as unmatched). Not recovered: whether
`enable-tlsext` was off (tried; matches got worse, so it stays default-off).

Note on the old "/O1, /Ox, /Oy-" claim for libjpeg: re-tested, none of those variants matches any function that
plain `/O2` does not; the claim was an artifact of the unscripted session and has been dropped.

### The 748 `lib_cblock` functions (0x1176a90-0x11e2000)

Resolved by `cblock_resolve.py` into `third_party/cblock_resolution.csv` (`va,lib,function,status,evidence`;
`symbols/lib_names.txt` is NOT edited, the orchestrator can apply the renames):
- 465 `exact-unique`: byte-identical to exactly one library function (named).
- 118 `exact-ambiguous`: byte-identical, but several library functions share the same body (aliases, tiny wrappers); all candidates are listed.
- 58 `exact-by-data`: tiny `mov eax, <static>; ret` getters named from the NID in the struct they return (`EVP_aes_128_cbc` etc.) and `X_new`/`X_free` ASN1 item wrappers named from the `ASN1_ITEM.sname`.
- 8 `thunk`: `jmp` stubs to an identified function. Nothing in the block looked like game code: of the identified functions all are OpenSSL except 3 static-CRT ones (the block's tail overlaps the CRT start).
- 34 `near` and 65 `unresolved`. The `near` ones are the right OpenSSL function by instruction-sequence similarity (0.9+), but not byte-identical. Several take their arguments in registers (`push edx` instead of `push esi` across a call), which means the original compiled those modules with whole-program optimization (`/GL`); our `/GL` output is not a plain COFF object, so libmatch cannot compare it. The `unresolved` ones are tiny getters (ssl method tables, ex_data class getters, 5 to 14 byte stubs) whose name is not decidable from bytes alone.

### What is not reproducible (honest gaps)

- About 99 cblock functions, as above (near-matches with likely `/GL` or another per-module flag difference, and undecidable tiny getters).
- The exact original build lines and whether the real build used per-file flags are unknown; the manifest has an empty `per_file` map ready for them.
- OpenSSL `crypto/buildinf.h` / `cversion.c` (the "compiler: cl ..." string) is not built: Configure's makefile-based buildinf does not apply to VC-WIN32.
- CRT objects (`crt_msvcrt`, `crt_msvcprt`, extracted from the toolchain `.lib` files in work/oss) are only used as an informational check in verify.py, not rebuilt.
- `.lib` files are produced, but nothing in the repo links them yet. `third_party/CMakeLists.txt` is a sketch (not added to the top-level build): portable builds use the system zlib/libpng/libjpeg(-turbo) and optionally OpenSSL; `-DSPORE_THIRD_PARTY_FAITHFUL=ON` imports the pinned `.lib` files and ships OpenSSL 0.9.8g per the decision below.

## OpenSSL 0.9.8g: shipped on purpose, with known risk

Decision (2026-10-04): ship the original 0.9.8g for fidelity, and note the risk here. Spore uses TLS as a client
only, for the Pollinator login to Spore's servers (EA account email and password,
`/pollinator/public-interface/login`) and for the long-dead YouTube ClientLogin upload API.

Worst case, all of it requires a man-in-the-middle (hostile Wi-Fi, a compromised router, DNS spoofing) or a
malicious server impersonating Spore's:
- **Credential theft or traffic tampering:** CCS injection (CVE-2014-0224) lets a MITM decrypt and modify
  the session. Old protocol and cipher support (no TLS 1.2; RC4, export and DES suites, FREAK
  CVE-2015-0204, renegotiation CVE-2009-3555) lets an attacker downgrade it. Most realistic outcome: the
  player's EA account password is exposed.
- **Code execution in the game process (theoretical):** ASN.1 and certificate parsing memory-corruption bugs
  in the 0.9.8 line (e.g. CVE-2012-2110) are reachable from a hostile server's certificate. That could run
  code with the player's user privileges.
- **Not affected:** Heartbleed (1.0.1 only). Spore is never a TLS server.
- **Practical side effect:** servers that require TLS 1.2+ will refuse the handshake.

Mitigation to consider later: a build option to use a modern OpenSSL (3.x) behind a small adapter for the
handful of 0.9.8 APIs the game calls.
