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

### Open item: the session token is currently project-wide, not per-conversation
OpenCode provider `headers` are static strings — it exposes no per-session variable
(no `OPENCODE_SESSION_ID`; config `{env:...}` is process-wide), so we cannot put the
conversation id in the header from config alone. `spore-decomp` is therefore stable but
**shared** across all concurrent sessions. If a per-conversation value is required (to
spread 10 concurrent large contexts across backends rather than pinning them to one),
it needs a small OpenCode **plugin** that sets `x-ci-prompt-cache-session` per session
via the session HTTP hook.

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
