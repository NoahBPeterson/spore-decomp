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

The EA EAText/EAIO sources used for the `lib_eatext` matches are obtained from the
EAWebKit distribution and are built locally under `work/` (git-ignored); **no EA
source is redistributed in this repository**. If you intend to vendor them in-tree,
retain EA's copyright and license notice — that license is BSD-style, which is
compatible with combining it with GPL-3.0 code, but it is not itself GPL.

A few game slices that call into EAText/EAIO/EA::Locale (s00880170, s00885ad0, s0088b250) compile
against the same EAWebKit headers through local include links; `tools/third_party/eawebkit_include_links.sh`
recreates them under `work/match/scratch_*_inc` once the support packages are unpacked in `work/ext/`.

## Binary-derived artifacts
The binary, its PDBs, and the game data are © Electronic Arts / Maxis and are **not**
distributed here. They live under `work/` (git-ignored) and are produced locally from
your own legally obtained copy of the game.

The reconstructed/annotated function sources under `match/` and the recovered symbol
lists under `symbols/` are derived from the original binary. They are published for
interoperability, research and preservation. They are derivative of the original work
and are **not** covered by this project's GPL grant; treat them accordingly.
