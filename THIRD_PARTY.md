# Third-party components and derived artifacts

This project combines several kinds of material with different licensing. Read this
before redistributing.

## Project code — GPL-2.0
Everything authored for this project (the tools, the portable reimplementation under
`src/`, the tests, and the documentation) is licensed under the GNU General Public
License, version 2 only (GPL-2.0-only) — see [`LICENSE`](LICENSE).

## Upstream library sources used for byte-exact matches
Some functions in the binary are third-party code that we reproduce by compiling the
original upstream source with the matching toolchain. These sources are **not**
relicensed by this project; each keeps its own upstream license, and the resulting
matched addresses are recorded in `symbols/lib_names.txt` and `work/oss/*_matches.csv`.

| Component | Source | License |
|---|---|---|
| OpenSSL | openssl.org | Apache-2.0 |
| zlib | zlib.net | zlib |
| libpng | libpng.org | libpng |
| libjpeg (IJG) | ijg.org | IJG |
| Microsoft C runtime | MSVC 15.00 (VS2008 SP1) | Microsoft EULA |
| EA EAText / EAIO | EAWebKit 1.21.00 | EA WebKit license (3-clause BSD-style) |
| EA EAThread | github.com/BurnoutDecomp/EAThread (fork of electronicarts/EAThread) | EA BSD 3-clause |
| RenderWare 4 / EATech reconstructions (rw::audio::core, rw::core, EA::Thread, Snd, vp6) | github.com/BurnoutDecomp/b5-decomp (`vendor/renderware`, `src/vendor/renderware`, `src/SDKs/EATech`, `src/GameShared/GameClasses/RenderWare`) | EA-style BSD 3-clause, assumed (see below) |

The EA EAText/EAIO sources used for the `lib_eatext` matches are obtained from the
EAWebKit distribution and are built locally under `work/` (git-ignored); **no EA
source is redistributed in this repository**. If you intend to vendor them in-tree,
retain EA's copyright and license notice — that license is BSD-style, which is
compatible with combining it with GPL-2.0 code, but it is not itself GPL.

### Fetching them: `tools/ci/setup_oss.sh`
`sh tools/ci/setup_oss.sh` (also run by the Byte-match check) downloads the official releases into
`work/toolchain/downloads/oss`, checks their SHA-256, and unpacks them where the manifest rows expect them:

| Archive | SHA-256 | Unpacked to |
|---|---|---|
| https://www.ijg.org/files/jpegsrc.v6a.tar.gz | `0e963fdd29d5049f61f3dc137bdc9437473a0ad505dbcfc8925f0fcad46c5929` | `work/third_party/src/jpeg-6a` |
| https://www.openssl.org/source/old/0.9.x/openssl-0.9.8g.tar.gz | `0e26886845de95716c9f1b9b75c0e06e9d4075d2bdc9e11504eaa5f7ee901cf0` | `work/third_party/src/openssl-0.9.8g` |
| https://zlib.net/fossils/zlib-1.2.3.tar.gz | `1795c7d067a43174113fdf03447532f373e1c6c57c08d61d9e4e9be5e244b05e` | `work/third_party/src/zlib-1.2.3` |
| https://downloads.sourceforge.net/project/libpng/libpng12/older-releases/1.2.25/libpng-1.2.25.tar.gz | `295ba7b7744efe93fb4c34d4973cc1099055d9c379a1e9397209857e80611e18` | `work/third_party/src/libpng-1.2.25` |
| https://gpl.ea.com/EAWebKit-1.21.00.darkspore.zip (EA's GPL page for Darkspore; EAWebKit 1.21.00) | `a2f8ac0b7d2938d386389aec0a7b12d0c6eaffc2778ad90c88b87d04a60d1c77` | `work/ext/EAWebKitSupportPackages` |

It then recreates what the rows compile against, from the pristine sources and a few small files of our own under
`tools/ci/oss/` (no upstream source is committed):
- `work/third_party/build/jpeg-6a-inc/jconfig.h`: our `third_party/jpeg-6a/jconfig.h` (jconfig.vc; 6a ships none).
- `work/third_party/build/openssl-0.9.8g-d2110920`: `perl Configure VC-WIN32` with the options in
  `third_party/manifest.json`, `BN_LLONG` undefined, `make links` (`tools/third_party/build_faithful.py`).
- `EATextOpenType.cpp` patched with `tools/ci/oss/EATextOpenType.patch` (byte swaps through `_byteswap_ushort` /
  `_byteswap_ulong`, as the retail build compiled them; the file's CRLF line ends become LF).
- `work/match/scratch_*_inc`, the include directories manifest rows name as `/Iscratch_*_inc`: the EAWebKit links
  below, our minimal EAThread headers (`tools/ci/oss/eathread/`), and copies of the configured OpenSSL headers (some
  with `OPENSSL_EXPORT_VAR_AS_FUNCTION` undefined, as the retail build had it).

A few game slices that call into EAText/EAIO/EA::Locale (s00880170, s00885ad0, s0088b250) compile
against the same EAWebKit headers through local include links; `tools/third_party/eawebkit_include_links.sh`
recreates them under `work/match/scratch_*_inc` once the support packages are unpacked in `work/ext/`.

### EAThread and the BurnoutDecomp RenderWare/EATech reconstructions
`lib_eathread` and `lib_b5rw` entries in `symbols/lib_names.txt` are functions that compile
byte-exact with cl 15.00.30729 from:
- **EAThread**, EA's open-source threading library (BSD 3-clause, copyright Electronic Arts), via the
  BurnoutDecomp fork: `git clone https://github.com/BurnoutDecomp/EAThread work/ext/gh_EAThread`.
- **BurnoutDecomp's reconstructions** of RenderWare 4 (mostly RenderWare Audio, `rw::audio::core`) and
  of the EATech SDK, decompiled from Burnout Paradise: `git clone --filter=blob:none --sparse -b dev
  https://github.com/BurnoutDecomp/b5-decomp work/ext/gh_b5`, then `git -C work/ext/gh_b5 sparse-checkout
  set vendor/renderware src/SDKs/EATech src/vendor/renderware src/GameShared/GameClasses/Sound/Playback
  vendor/PPMalloc` and `sparse-checkout add --skip-checks src/types.hpp`; the `b5more` target also needs
  `sparse-checkout add src/GameShared/GameClasses/RenderWare src/GameShared/GameClasses/Core
  src/GameShared/GameClasses/Development/Log src/GameShared/GameClasses/Graphics
  src/GameShared/GameClasses/System/Resource src/SDKs/RenderEngineClub src/SDKs/Packages/Apt
  src/pc/gcm/renderengine` (headers). The b5-decomp repository
  carries no license notice; we treat it under the same EA-style BSD 3-clause terms as the EA libraries
  above, on the assumption that the notice is simply missing.

`tools/third_party/build_ea_libs.py {eathread,b5rw} --emit` builds both against the ~2010 EABase and
coreallocator from the EAWebKit bundle (through `tools/third_party/compat`, our own shims for newer
EABase macros and C++11 headers), applies a few VS2008 compatibility edits to copies under `work/oss`,
matches the objects against the image (libmatch + libresolve), and appends the unique placements.
`build_ea_libs.py b5more --emit` does the same, under the same `lib_b5rw` tag, for the rest of
b5-decomp's PC code: `src/vendor/renderware` (collision, physics), `src/SDKs/EATech` (Apt, eajobs,
rwcollision, rwmovie, and the sources under `include/`: Apt, NFSMix, Nicotine, rw, snd) and
`src/GameShared/GameClasses/RenderWare` (without the PS3/x360 subdirectories). It rewrites their
C++11/17 syntax for VS2008 on copies under `work/oss/b5more_src`, and before appending it drops generic
bodies (deleting destructors, STL helpers, EH funclets), Apt and Criterion `Cgs*` code (absent from
Spore) and addresses already named by the PDB or a slice, then re-checks each entry with `cmpobj.py`. No
upstream source is committed; if you vendor it in-tree, keep the copyright and license notices.

## Binary-derived artifacts
The binary, its PDBs, and the game data are © Electronic Arts / Maxis and are **not**
distributed here. They live under `work/` (git-ignored) and are produced locally from
your own legally obtained copy of the game.

The reconstructed/annotated function sources under `match/` and the recovered symbol
lists under `symbols/` are derived from the original binary. They are published for
interoperability, research and preservation. They are derivative of the original work
and are **not** covered by this project's GPL grant; treat them accordingly.
