# cheaperinference prompt-cache: measurement and fix

## Why this exists
The `gold0` wave cost ~5× the earlier `bfs*` waves and yielded less byte-exact
output. Root cause: **prefix-cache misses**. `gold0`'s sessions grew huge contexts
(up to ~600k tokens) and the provider's prompt cache stopped hitting, so the whole
context was re-billed at the cache-**miss** rate (50× the read rate on this plan).

## The real measurement (not per-request guesswork)
```
GET https://api.cheaperinference.com/v1/usage/daily        # Authorization: Bearer <ci key>
```
Returns workspace aggregates and `daily_spend[]` with `cache_hit_pct`,
`cache_reported_request_count`, `prompt_tokens`, `cached_tokens`, `spend_usd`.

Observed (2026-10-09):

| date | requests | prompt M | cached M | cache_hit_pct | spend |
|---|--:|--:|--:|--:|--:|
| 2026-10-05 | 24,710 | 5,220 | 5,141 | **98.5%** | $32.52 |
| 2026-10-06 | 9,313 | 1,993 | 1,941 | 97.5% | $17.67 |
| 2026-10-08 | 3,631 | 721 | 716 | **99.3%** | $4.07 |
| **2026-10-09 (gold0)** | 2,467 | 653 | 570 | **87.3%** | $7.80 |

So `gold0` ran at 87.3% cache-hit vs 97.5–99.3% on the clean days — an isolated
regression, confirmed by the provider's own accounting.

## Fix applied — routing-affinity headers
`cheaperinference` requests now send, per provider config in `.opencode/opencode.json`:

```jsonc
"options": {
  "baseURL": "https://api.cheaperinference.com/v1",
  "headers": {
    "x-ci-prompt-cache": "on",
    "x-ci-prompt-cache-session": "spore-decomp"
  }
}
```

Resolved config (verified via `GET /api/config`):

```
providers.cheaperinference.headers = {"x-ci-prompt-cache":"on","x-ci-prompt-cache-session":"spore-decomp"}
```

The intent is **routing affinity**: keep every turn of a conversation on the backend
that already holds its prefix, so the cache stays warm instead of missing on a cold
node.

### Resolved: per-session cache namespaces (2026-10-10)
The `x-ci-prompt-cache-session` value is the prompt cache's **namespace key**, not a node
affinity hint (opencode's automatic `x-session-affinity` header was tested and has **no**
effect: 5 hit/3 miss with it unchanged, identically 5/3 with it changed). With one fixed
value every concurrent worker shares one namespace; at a wave-sized working set the large
contexts evict each other, which is the observed ~7% of requests that re-read the whole
context.

Reproduced directly against the API at the real working set (30 prompts x ~70k tokens,
~2.1M total), priming each then re-probing:

| trial | session header | prefixes retained |
|---|---|---|
| 30 contexts, **one shared** header | `spore-shared` | **0 / 7** |
| 30 contexts, **distinct** header per context | `spore-node-*` | **7 / 7** |
| alternating repeats (fresh tags) | distinct vs shared | distinct 11/16 vs shared 3/16 |

opencode cannot interpolate a session id into a static config header, and **provider-level
headers override per-model ones** (a model-level `x-ci-prompt-cache: off` probe did not
disable caching while the provider set `on`), so the session header must live *per model*
and not at provider level.

### Fix implemented
- `tools/opencode_cache_ns.py [N]` (default 32) rewrites `.opencode/opencode.json` to expose
  N model aliases (`deepseek-v4.1-flash-c00..c31`) under `cheaperinference`. Each alias has
  `"id": "deepseek-v4.1-flash"` (maps back to the real API model) and its own per-model
  `x-ci-prompt-cache-session: spore-decomp-cNN`. Provider-level headers keep only
  `x-ci-prompt-cache: on`.
- `tools/opencode_sup.py`: with a group's `"cache_ns": N`, range k runs on alias `k % N`
  (all prompts, `unhang`, `nudge`, `switch`). `opencode_sup.py <group> ns [N]` sets it.
- `work/opencode/new_group.py` defaults new cheaperinference groups to `cache_ns=32`.
- `tools/opencode_fallback.py` clears `cache_ns` when it moves a group to OpenRouter
  (the cheaperinference-only aliases do not exist there).

### Verification (end-to-end through opencode)
First request of a fresh session, one completion each:

| model | first-req input | cache_read | cached |
|---|--:|--:|--:|
| base `deepseek-v4.1-flash` | 141 | 8,320 | **98%** (warm shared ns) |
| alias `deepseek-v4.1-flash-c07` | 8,346 | 128 | **2%** (cold, own ns) |
| alias `deepseek-v4.1-flash-c08` | 8,346 | 128 | **2%** (cold, own ns) |

The aliases are cold while the base is warm → the per-model `x-ci-prompt-cache-session`
header **is delivered**, so each session now gets a disjoint namespace.

### Expected cost
The one-off cost is a cold first request per session (the shared system prompt is no longer
cross-session shared): ~8k tokens x N sessions (~$0.02 for 30). That trades against the
mid-epoch full re-reads, which were the dominant miss cost (~$4.4 of gold1's $10.4).

### Still to confirm
Run a full wave on aliases, then check `/v1/usage/daily` `cache_hit_pct` (target ≥ 97 on
the wave day) and per-group cost from `tools/progress.py --groups`. The provider's cache is
noisy (an ~8% stochastic full-miss rate persisted even in a tight sequential loop with a
stable header), so expect improvement, not perfection. Keep per-session context bounded
(~120–150k): miss *cost* scales with context size even when the rate is fixed.

## exact-cache (provider option)
The provider offers an "exact-cache" that skips upstream generation on eligible hits.
Assessment: low risk for this workload (deterministic codegen; opencode already retries
timed-out requests, which would become free), but **it does not address prefix-cache
misses** — those are about prompt *caching*, not exact response reuse. Treat it as a
secondary win and measure with `/v1/usage/daily` before/after.

## How to re-check after the next wave
```sh
curl -s -H "Authorization: Bearer $CI_KEY" https://api.cheaperinference.com/v1/usage/daily \
  | jq '{cache_hit_pct, cache_reported_request_count, spend_usd,
         today: (.daily_spend | map(select(.request_count>0)) | last)}'
```
Target: hit% back to ≥97 on the wave day. Also keep per-session context bounded
(~120–150k) — miss *cost* scales with context size, so smaller sessions help even if
affinity fixes the miss *rate*.
