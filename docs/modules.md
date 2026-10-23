# Modules: what the code of SporeApp.exe is made of

This page explains the top-level directories ("modules") that the retail executable's code comes from, what each one
does, how big it is, and how far the decompilation has got in each. It is written for choosing what to work on next.

## Terms

- **Object file (`.obj`)**: one compiled source file. The 2008 development build's PDB (`work/devbuild`) names every
  object file it was linked from, with its directory, e.g. `SPGonzago/SPCellGame.obj` (industry term).
- **Module** (this project's term): the top-level directory of an object file's path, e.g. `SPGonzago`. The names are
  EA's own directory names from the dev build, not names we chose.
- **Module map** (project term): `work/migrate/modmap.json`, which assigns each retail function address to the
  object file it most likely came from. `how` says how it was assigned: `anchor` (a function the dev PDB names and
  we found in retail), `interp` (sits between two anchors of the same object), `vtable-vote` (its class's other virtual
  functions belong to that object), and so on; `confidence` goes with it.
- **Slice** (project term): a range of retail addresses under `match/slices/<id>/`, the unit the DeepSeek waves work
  on. A slice can hold functions from several object files.

## The modules

Sizes and progress below come from the module map joined with every bookkeeping source (2026-10-23):
`manifest.txt` files under `match/slices/` and `src/game/`, `match/manifest.txt`, the pattern-generated manifests in
`match/synth/` and `match/clones.txt` (byte-exact), `nonmatching.txt` (complete, not byte-exact) and `partial.txt`
(incomplete). "Synth" is the part of the byte-exact count that `tools/matching/synth.py` generated from code shapes
(an `AddRef`, a three-store constructor, and so on): byte-exact, but compiled under placeholder class names such as
`C_00768530` until migration gives them real ones. "No row" means no bookkeeping source mentions the function yet.
What each module does is inferred from its object-file names and the dev PDB's class names.

| Module | Functions | Code | Objects | Byte-exact | of which synth | Complete, not exact | Partial | No row |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| SPGonzago | 13,090 | 3.14 MB | 274 | 5,525 | 4,903 | 935 | 359 | 6,271 |
| UTFSpore_Win32 | 5,269 | 1.12 MB | 240 | 2,639 | 942 | 1,816 | 235 | 579 |
| SPEditors | 3,368 | 0.89 MB | 118 | 2,261 | 994 | 776 | 331 | 0 |
| SPEngine | 3,353 | 0.89 MB | 100 | 1,519 | 748 | 1,271 | 490 | 73 |
| SPBake | 1,060 | 0.65 MB | 34 | 534 | 84 | 392 | 134 | 0 |
| SPCreatureAnim | 712 | 0.30 MB | 15 | 262 | 121 | 304 | 29 | 117 |
| SPAudio | 1,533 | 0.29 MB | 70 | 708 | 216 | 618 | 31 | 176 |
| SPTerrain | 507 | 0.25 MB | 20 | 188 | 83 | 191 | 31 | 97 |
| Spui | 1,238 | 0.22 MB | 31 | 737 | 416 | 373 | 128 | 0 |
| Swarm | 335 | 0.12 MB | 18 | 139 | 63 | 133 | 8 | 55 |
| Native Release (RenderWare 4) | 429 | 0.07 MB | 48 | 133 | 62 | 211 | 30 | 55 |
| EA sound library (`cmn`, `plugins`, `mix`, `decoders`, `ealayer30`, `ealayer31`) | 187 | 0.06 MB | 51 | 32 | 10 | 137 | 4 | 14 |
| SPMovie | 190 | 0.03 MB | 16 | 94 | 44 | 54 | 18 | 24 |
| SporeApp | 15 | 0.01 MB | 1 | 6 | 4 | 7 | 2 | 0 |
| dll_obj (CRT helpers) | 9 | <0.01 MB | 7 | 1 | 0 | 0 | 0 | 8 |

Code sizes are the module map's function sizes. `tools/module_progress.py` prints this table; `--batch <name>`
shows how much of each module's unrecorded code a batch offers.

### SPGonzago: the game itself

The gameplay layer for every stage, the largest module by far (about 40% of the game code, `docs/PLAN.md`). The name
is EA's directory name for this project in the dev build (`SPGonzagoSystem.obj` is its top-level system); the origin
of "Gonzago" is not recorded anywhere we have. Its largest object files, by function count:

- Cell stage: `SPCellGame` (done: all 63 of its slices are recorded, batch spcg1).
- Creature stage: `SPCreatureBase`, `SPAnimalBehaviorTrees`.
- Tribe stage: `SPTribe`, `SPTribeBehaviorTrees`, `SPTribeModeStrategy`, `SPCitizenBehaviorTree`.
- Civilization stage: `SPVehicle`, `SPWeapons`.
- Space stage: `SPPlanet`, `SPGalaxyGameEntry`, `SPUISpace`, `SPToolStrategies`.
- Shared: `SPGonzagoSystem`, `SPGonzagoPhysics`, `SPDramaManager`, `SPCinematicActions`, `SPUIPosse` (the
  player's group of followers).

It is the least finished module: 6,271 of its 13,090 functions have no row, and most of its 5,525 byte-exact
functions are pattern-generated (synth) ones still under placeholder names. Of the 6,271, batch gold6 (2026-10-23)
covers 4,958; 994 sit in slices that an earlier wave created but never recorded, and 328 in slices that were put in a
batch but never created; a few dozen more have a `// @` marker in some source but no row.

### UTFSpore_Win32: EA's application framework

The engine-independent framework the game is built on: the resource system (`DatabasePackedFile`, the DBPF package
format), the windowing and UI toolkit (`Window`, `Button`, `TreeView`, `TextEdit`, `Grid`), CSS and XML parsing
(`CSSParser`, `xmltok`, the latter from expat), fonts and text layout (`fnt`, and the `EAText*` objects), logging
(`ealog_imp`) and networking (`Socket_imp`). It is the most finished large module and was the migration pilot's area.

### SPEditors: the editors and sharing

The editor modes and everything around them: `SPAppModeEditorBase`, play mode (`SPPlayMode`,
`SPPlayModePhotoBrowser`), the asset browser, the "Pollinator" system that uploads and downloads player creations
(`SPPollinator`, `SPPollinatorTransactions`), the object template database, authentication and settings.

### SPEngine: graphics and core game services

Rendering and the game's core services: model, material, lighting, thumbnail and effects managers
(`SPGraphics*`), mesh joining, the property manager (`.prop` files), the object database and configuration.

### SPBake: building editor models

Turns what the player made in an editor into game assets: editor blocks and manipulation, the baker, the species
manager, skin painting, validity checks and export.

### SPCreatureAnim: creature animation

Procedural animation for player-made creatures: gaits, inverse kinematics (`ik_solver`), the creature mesh, animation
events and blending.

### SPAudio and the EA sound library

`SPAudio` is the game's audio system (sound objects, emitters, resource configuration) plus `eapd*`, EA's audio
data-flow engine (graph, canvas, connective, system). The small modules `cmn`, `plugins`, `mix`, `decoders`,
`ealayer30` and `ealayer31` are EA's sound library (mixer, voices, effects plugins, the EALayer3 codec).

### SPTerrain: planets

The planet sphere, terrain editing, weather, and effects distributed over the surface.

### Spui: the game's UI layer

Game-side UI on top of the framework's toolkit: behaviours, layouts, popup and pie menus, the cursor manager, input
method (IME) support and UI serialization.

### Swarm: effects

The visual effects system: particles, effects descriptions and parser, decals, lights and camera shake.

### Native Release: RenderWare 4

EA's RenderWare 4 core (`rw*.obj`: arenas, streams, the PC graphics driver). It was linked with link-time code
generation, so its calling functions cannot be byte-exact; the target there is equivalence (`docs/matching.md`).

### Smaller modules

- **SPMovie**: video capture and playback (AVI and JPEG encoders, YUV conversion, the movie player).
- **SporeApp**: the executable's own entry object.
- **dll_obj**: C runtime helpers (`chkstk`, `ftol2`, `lldiv`, vector constructor/destructor iterators).

### Not in the module map

Havok 3.1 physics (about 1.1 MB, `docs/PLAN.md`) and the third-party libraries linked into the executable are not
in the table. The third-party functions found so far are listed in `symbols/lib_names.txt` (OpenSSL, zlib, libpng,
libjpeg, CRT, EAThread, EAText and others) and are excluded from the progress figures in `docs/STATUS.md`.

## What the waves leave out, and why

The scripts that build DeepSeek batches (`work/claude/make_wave.py` and the gold batch builders) skip three groups:

- **SPCellGame**: already done by batch spcg1 (October 14; committed 2026-10-23).
- **EAText**: EA's text library. Its real source is vendored under `work/ext/EAWebKitSupportPackages`, and
  `docs/STATUS.md` counts its functions as third-party.
- **Third-party library functions** listed in `symbols/lib_names.txt`.

Until 2026-10-23 the filter also matched any module containing the text "SPGonzago", which kept the whole of
SPGonzago, not only `SPGonzago/SPCellGame.obj`, out of every wave since the migration rounds. It now matches
SPCellGame and EAText only, and gold6 is the first wave to offer the rest of SPGonzago.
