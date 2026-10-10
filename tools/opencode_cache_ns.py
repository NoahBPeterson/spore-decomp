#!/usr/bin/env python3
"""Give each opencode worker session its own cheaperinference prompt-cache namespace.

Why: cheaperinference keys its prompt cache (partly) on the `x-ci-prompt-cache-session`
header. opencode cannot interpolate a session id into a custom header, so with a single
fixed value every concurrent worker shares one cache namespace and, at our working set
(~30 sessions x ~100k tokens), entries evict each other -> the ~7% of requests that
re-read the whole context (the dominant cache-miss cost of a wave).

Fix: expose N model aliases under the cheaperinference provider. Each alias maps to the
real API model via the model `id` override and differs only in the per-model
`x-ci-prompt-cache-session` header. The supervisor (tools/opencode_sup.py) assigns alias
k % N to range k, so concurrent sessions land in disjoint namespaces.

The session header is deliberately NOT set at provider level: provider-level headers can
override per-model ones, which would make every alias share one namespace (a no-op).

usage: opencode_cache_ns.py [N]        # default 32; rewrites .opencode/opencode.json
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CFG = os.path.join(ROOT, ".opencode", "opencode.json")
PROVIDER = "cheaperinference"
BASE = "deepseek-v4.1-flash"
NS_PREFIX = "spore-decomp"
STALE = {BASE + "-off", BASE + "-authprobe"}  # probe aliases from development


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 32
    cfg = json.load(open(CFG))
    prov = cfg.setdefault("provider", {}).setdefault(PROVIDER, {})
    hdr = prov.setdefault("options", {}).setdefault("headers", {})
    hdr["x-ci-prompt-cache"] = "on"
    hdr.pop("x-ci-prompt-cache-session", None)  # must live per-model or it wins over aliases
    models = prov.setdefault("models", {})
    if BASE not in models:
        sys.exit("no %s model under provider %s" % (BASE, PROVIDER))
    base = models[BASE]
    bh = base.setdefault("headers", {})
    bh["x-ci-prompt-cache"] = "on"
    bh["x-ci-prompt-cache-session"] = NS_PREFIX
    for k in list(models):  # drop stale/generated aliases, regenerate cleanly
        if k in STALE or (k.startswith(BASE + "-c") and k[len(BASE) + 2:].isdigit()):
            del models[k]
    for i in range(n):
        models["%s-c%02d" % (BASE, i)] = {
            "name": "%s cache-ns %02d (%s)" % (base.get("name", BASE), i, PROVIDER),
            "id": BASE,  # real API model id; the alias key is only a local cache namespace
            "limit": base["limit"],
            "cost": base["cost"],
            "headers": {"x-ci-prompt-cache": "on",
                        "x-ci-prompt-cache-session": "%s-c%02d" % (NS_PREFIX, i)},
        }
    json.dump(cfg, open(CFG, "w"), indent=1)
    print("wrote %d cache namespaces: %s-c00 .. %s-c%02d (base %s keeps '%s')"
          % (n, BASE, BASE, n - 1, BASE, NS_PREFIX))


if __name__ == "__main__":
    main()
