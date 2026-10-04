# Third-party libraries

These are statically linked into SporeApp.exe. They're excluded from the decompilation percentages because we
build them from upstream source instead of decompiling them. Versions come from strings in the binary.
1,298 of their functions are proven byte-identical to objects built from these versions with VS2008
(`work/oss/lib_matches.csv`, via tools/matching/libmatch.py).

| Library | Version | Evidence | License |
|---|---|---|---|
| OpenSSL | 0.9.8g (19 Oct 2007) | "... part of OpenSSL 0.9.8g 19 Oct 2007" | OpenSSL/SSLeay |
| zlib | 1.2.3 | "deflate 1.2.3 Copyright 1995-2005" | zlib |
| libpng | 1.2.25 | "1.2.25" | libpng |
| libjpeg (IJG) | 6b | byte-matched objects (some functions built with /O1, /Ox, /Oy-) | IJG |

Status: the build is not yet scripted in the repo (it was done ad hoc in work/oss). To do: a fetch script
(upstream URL plus SHA-256), per-library cl flags, CMake targets, and a CI check that every library function
of the original exe has an identical function in our build. Also, 748 functions in the contiguous C-library
block (0x1176a90-0x11e2000) are excluded by link order but not yet byte-matched.

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
