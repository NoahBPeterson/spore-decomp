# Auditing the worker agents

The matching waves hand slices of the binary to many cheap, free-form opencode sessions. A session
may write any C++ and any bookkeeping, so the *audit* is the deterministic layer that decides whether
its output counts. This page is the index of those checks; each is documented in depth elsewhere
(see [Where this is already documented](#where-this-is-already-documented)).

## The contract

For each slice `<id>`, an agent must produce:

| file | meaning | row format |
|---|---|---|
| `match/slices/<id>/<id>.cpp` | compilable source for **every** function; markers `// @ 0x<VA>` where used | — |
| `match/slices/<id>/manifest.txt` | **byte-exact** functions | `<source> <symbol> <va> [cl flags]` |
| `match/slices/<id>/nonmatching.txt` | complete, **behaviourally equivalent, not byte-exact** | `<va> <diff> <reason>` (reason carries flags + difftest verdict) |
| `match/slices/<id>/partial.txt` | **incomplete / approximate** | `<va> …` |

Every VA the batch assigns to the slice must be in **exactly one** of the three files.

## Why an audit is needed (the hole it closes)

`run_all.py` reads only `manifest.txt`; `equiv.py`/`batch.py` read only `nonmatching.txt`; and
`verify_group.py` only checks that the rows *in the manifest* are byte-exact. So **a VA in none of
the three files is invisible to byte-exact verification AND to the equivalence backlog — and the
group still commits.** The categorisation audit exists to close that hole. It also catches a VA listed
in two files (ambiguous verdict, double-counted by `progress.py`) and manifests that over-claim
byte-exactness.

## The gates

| # | Gate | Tool / how to run | Passes when | Failure means |
|---|---|---|---|---|
| 1 | **Bookkeeping completeness** | `.venv/bin/python tools/categorize_audit.py --batch <batch>` (`--all`, `--gate`, `-v`) | every target VA in exactly one file; source markers all categorised | `TARGET-UNCATEGORISED` = invisible to both pipelines; `IN-MULTIPLE-FILES` = ambiguous/double-counted |
| 2 | **Byte-exact** | `.venv/bin/python tools/matching/run_all.py --manifest match/slices/<id>/manifest.txt [-v]` | `N / N functions byte-exact` | a manifest row that isn't byte-exact, or a compile/symbol error. Only one `run_all` at a time (`work/run_all.lock`). |
| 2b | **Byte-exact, whole group** | `sh tools/opencode_verify_group.sh <batch>` (add `--skip-audit` to skip gate 1) | every slice `N / N` **and** gate 1 clean | any slice mismatch, or an untracked target VA |
| 2c | **Group commit path** | `.venv/bin/python work/opencode/verify_group.py <group>` (git-ignored; run_all + gate 1, then `git commit`) | same as 2b | refuses to commit |
| 3 | **No assembly transcription** | `.venv/bin/python tools/matching/asm_audit.py [slice …]` | no manifest entry uses `_emit`, `__declspec(naked)`, or >3 `__asm` blocks | an entry needs a human look; transcribed bodies are disallowed |
| 4 | **Behavioural equivalence** | `.venv/bin/python tools/difftest/equiv.py <slice> [va …]`; strict backlog `sh work/opencode/run_backlog.sh [K] equivalents` | `PASS` (or `WEAK`: no mismatch, under-covered) | `FAIL` = a real behaviour bug; `UNSUPPORTED` = unresolved ref / compile / no coverage (documented, not silent) |
| 5 | **Partial diagnostics** | `sh work/opencode/run_backlog.sh [K] partials` | — | diagnostics only, **not** verification; catches crashes/compiles |
| 6 | **Coverage / status** | `.venv/bin/python tools/status.py` (writes `docs/STATUS.md`); `.venv/bin/python tools/progress.py [--groups]` | — | tier counts: byte-exact / equivalent / partial / no-source |
| 7 | **Wave health** (sessions, cost, cache) | `.venv/bin/python tools/opencode_sup.py <group> status`; `.venv/bin/python tools/opencode_drain.py <group>`; broker `tools/opencode_broker.py` | all ranges accounted, no stuck sessions | idle-unfinished ranges get re-prompted; hung calls interrupted |

### Gate 1 in commit-gate mode

`--gate` (used by gates 2b/2c) fails only on the two findings that lose or misverify work —
`TARGET-UNCATEGORISED` and `IN-MULTIPLE-FILES` — and demotes `WRITTEN-NOT-CATEGORISED` (a source
marker not listed anywhere) to a warning, so helper functions don't block a group. Without `--gate`,
`WRITTEN-NOT-CATEGORISED` is also an error (useful for a whole-repo sweep: `--all`).

### Gate 4: in-wave check vs the strict backlog

The wave prompt's per-slice "equivalence gate" is a **single** `equiv.py` run at default inputs whose
verdict is recorded as prose in `nonmatching.txt`. The **strict backlog** (`run_backlog.sh equivalents`,
i.e. `batch.py --require-all --inputs 1200 --time-limit 150`) is the machine-checked verification and
is resumable/atomic: `sh work/opencode/run_backlog.sh status equivalents` shows progress, and a kill
loses nothing. Treat the in-wave verdict as a smoke test, the backlog as the record.

## Audit trail (ledgers, git-ignored)

- `work/opencode/decisions.jsonl` — every permission decision the broker made (append-only).
- `work/opencode/attempts.jsonl` — per-attempt ledger, keys `{t, slice, va, verdict, seconds,
  coverage, all, valid, inputs, orig_size, wave, model}` (append-only JSONL; never in git).
- `work/difftest/*_shard*.json` (+ `_summary.md`) — equivalence results, written atomically.
- `work/verify_results.json` — the last `run_all.py` result per VA.
- `work/opencode/groups/<group>.json` — range → session id, provider/model, `cache_ns`.

## Where this is already documented

- **`docs/matching.md`** — the agent playbook: toolchain provenance (which compiler built which code),
  the byte-exact workflow (`chk.py` per round, `cmpdis.py` for near-miss diffs, `run_all.py` to
  verify a manifest), the `/Od` frame layout, and the "Batch-2 lessons".
- **`docs/equivalence.md`** — the differential harness: what `equiv.py` observes, the
  `PASS`/`WEAK`/`FAIL`/`UNSUPPORTED` verdicts, inputs, coverage, and the self-tests.
- **`docs/STATUS.md`** — generated tier coverage (byte-exact / equivalent / partial / no source).
- **`docs/Papercuts.md`** — recurring agent mistakes and gotchas (the largest running list of
  failure modes worth auditing for).
- **`docs/tickets.md`** — the `UNSUPPORTED` backlog.
- **`docs/cheaperinference-cache.md`** — measuring the wave's cache hit rate and per-session
  prompt-cache namespaces (a cost/latency audit of the fleet).
- **`docs/PLAN.md`** — the overall staged plan and ground rules.
