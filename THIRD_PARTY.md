# Third-party components and derived artifacts

This project combines several kinds of material with different licensing. Read this
before redistributing.

## Project code — GPL-3.0
Everything authored for this project (the tools, the portable reimplementation under
`src/`, the tests, and the documentation) is licensed under the GNU General Public
License v3.0 — see [`LICENSE`](LICENSE).

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
compatible with combining it with GPL-3.0 code, but it is not itself GPL.

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
