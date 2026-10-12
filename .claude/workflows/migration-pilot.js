export const meta = {
  name: 'migration-pilot',
  description: 'Migrate the DBPF + property-list pilot from slices into src/game/ with rewrite.py, verify byte-exactness, boot the hybrid',
  whenToUse: 'Phase B step 3-4 of docs/migration.md; the exact procedure is docs/migration-runbook.md',
  phases: [
    { title: 'Tool + first slice', detail: 'build tools/migrate/rewrite.py and land s008d81d0 (21/21 MATCH)' },
    { title: 'Pilot slices', detail: 'the other 32 slices, one agent per target module, slices in order' },
    { title: 'Module build', detail: 'seven TUs compile, run_all green on the union, census one body per class' },
    { title: 'Gate', detail: 'hybrid with the module hooks boots twice' },
  ],
}

// Every agent reads the runbook; the prompt only says which section is its job.
const COMMON = `
Repo: /Users/noahpeterson/Documents/Projects/spore-decomp (branch main). Before anything else read
docs/migration-runbook.md in full (the exact procedure, verified facts, and the worked example) and
docs/migration.md (design and measurements). Obey runbook section 0: never commit, nothing in the
background, rg not grep, scratch files under the scratchpad directory
/private/tmp/claude-501/-Users-noahpeterson-Documents-Projects-spore-decomp/migration-pilot/<your-label>/
(create it), one compile loop at a time, do not edit match/slices/** or generated headers.
Your final text is returned as data to the workflow, not to a human: report facts, numbers you
read yourself, file paths, and the rules you added, in the schema you are given.
`

const RESULT = {
  type: 'object',
  properties: {
    ok: { type: 'boolean' },
    summary: { type: 'string' },
    matches: { type: 'string', description: 'run_all result: "N/M MATCH" per manifest, with the DIFF rows if any' },
    verdicts: { type: 'string', description: 'equiv verdict before -> after per nonmatching row, regressions called out' },
    files: { type: 'array', items: { type: 'string' } },
    rules_added: { type: 'array', items: { type: 'string' }, description: 'rename/thunk/extern rules you had to add to rewrite.py or the renames file' },
    header_fixes: { type: 'array', items: { type: 'string' }, description: 'overrides, leaf-table or generator changes you made, each with its evidence' },
    blockers: { type: 'string' },
  },
  required: ['ok', 'summary', 'matches', 'verdicts', 'files', 'rules_added', 'header_fixes', 'blockers'],
}

// ---- Phase 1: the tool and the first slice ------------------------------------------------
phase('Tool + first slice')
const first = await agent(COMMON + `
Your job is runbook section 3 (build tools/migrate/rewrite.py) and section 4 step 1 (land slice
s008d81d0 as src/game/UTFSpore_Win32/DatabasePackedFile.cpp with its manifests). Acceptance:
python3 tools/matching/run_all.py --manifest src/game/UTFSpore_Win32/DatabasePackedFile/manifest.txt -v
reports 21/21 MATCH, and the 12 nonmatching rows keep their verdict class (runbook section 2).
Use the worked example in section 3 as the test of your rename, thunk and extern rules; whatever
you had to do by hand for this slice must become a rule in the tool or an entry in
work/migrate/renames_s008d81d0.json before you finish. If a DIFF comes from a header, fix the
header's source (override / leaf table / hand template header), regenerate with
python3 tools/migrate/headers.py --module DatabasePackedFile, and record the evidence. Do not
change a function body's logic to make bytes match. Stop and report ok=false with the exact
blocker if you cannot get every row to MATCH after a serious attempt; a precise diagnosis of the
first DIFF (which instruction, which header member or slot) is more useful than a workaround.
`, { label: 'rewrite:s008d81d0', phase: 'Tool + first slice', model: 'sonnet', effort: 'high', schema: RESULT })

if (!first || !first.ok) {
  log('first slice did not land; stopping before the fan-out')
  return { first }
}

// ---- Phase 2: the remaining pilot slices, grouped by target module ----------------------------
phase('Pilot slices')
const GROUPS = {
  type: 'object',
  properties: {
    modules: { type: 'array', items: { type: 'object', properties: {
      module: { type: 'string' }, slices: { type: 'array', items: { type: 'string' } },
      functions: { type: 'number' } }, required: ['module', 'slices', 'functions'] } },
    outside_pilot: { type: 'string' },
  },
  required: ['modules', 'outside_pilot'],
}
const groups = await agent(COMMON + `
Compute the pilot's remaining work list (runbook section 1): for each of the seven pilot object
files (python3 tools/migrate/modmap.py --quiet --module DatabasePackedFile and --module
SPProperty list the functions), find the slices that hold its functions (the slice directory
whose <id>.cpp contains "// @ 0x<va>"), excluding s008d81d0 which is done. Order each module's
slice list by the lowest function VA. Also report, as text, the functions those slices hold for
objects OUTSIDE the pilot (they stay in their slices). Read-only task: write nothing in the repo.
`, { label: 'scout:groups', phase: 'Pilot slices', model: 'sonnet', schema: GROUPS })

const perModule = await parallel((groups ? groups.modules : []).filter(g => g.slices.length).map(g => () =>
  agent(COMMON + `
Your job is runbook section 4 step 2 for the module ${g.module}: migrate its slices IN THIS ORDER,
one after another (they append to the same TU): ${g.slices.join(', ')}. For each slice run
python3 tools/migrate/rewrite.py <slice> (plan), review work/migrate/renames_<slice>.json, then
--apply, then run_all on the module manifest; the acceptance per slice is every manifest row
MATCH and no verdict regression on the nonmatching rows. The tool and the rules from the first
slice are in place (its report: ${JSON.stringify((first.rules_added || []).slice(0, 20))}); add
rules, never one-off edits. Functions the slice holds for other modules stay in the slice: list
them. If a slice cannot land, leave its functions in the slice, record why in blockers, and go on
to the next slice; do not leave the module TU in a state that fails to compile. Report per slice.
`, { label: 'module:' + g.module.split('/').pop(), phase: 'Pilot slices', model: 'sonnet', effort: 'high', schema: RESULT })))

// ---- Phase 3: the module builds as one unit -------------------------------------------------
phase('Module build')
const build = await agent(COMMON + `
Runbook section 4 step 3. Results so far: ${JSON.stringify(perModule.filter(Boolean).map(r => r.summary))}.
Compile all seven pilot TUs under src/game/ with their manifest flags, run
python3 tools/matching/run_all.py on each module manifest (one at a time) and report the union;
run python3 tools/matching/layout_census.py pointed at src/game/include (read its usage; if it
only reads match/slices, add an --include-root option) and report whether the pilot's classes have
one body each. Fix only what is a build/bookkeeping problem; anything that needs a header change
goes into blockers with evidence.
`, { label: 'module-build', phase: 'Module build', model: 'sonnet', schema: RESULT })

// ---- Phase 4: the hybrid gate (serial: one build/boot at a time on this machine) --------------
phase('Gate')
const gate = await agent(COMMON + `
Runbook section 4 step 4. Read docs/hybrid.md first (build.py, boottest.sh, the scene metric, the
fault-address-first rule). Extend tools/hybrid/build.py with --hook-manifest <nonmatching.txt> if
it is not there (rows give va, source TU, symbol; reuse the existing splicer path that consumes
COFF objects through equiv.prepare), build one hybrid with the pilot modules' equivalent
functions hooked in, and run tools/hybrid/boottest.sh twice with SCENE_MIN=6. Exactly one build and
one boot at a time; make sure no game window is left open when you finish (pkill the SporeApp
process the script started). If the boot fails, diagnose from the fault address with only the
pilot hooks as suspects; one bisect at most, no human-in-the-loop. Report the boot results and the
hook count.
`, { label: 'gate', phase: 'Gate', model: 'sonnet', effort: 'high', schema: RESULT })

return { first, groups, perModule, build, gate }
