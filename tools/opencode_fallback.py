#!/usr/bin/env python3
"""Move cheaperinference groups to OpenRouter once (and only once) cheaperinference credits are exhausted.

usage: opencode_fallback.py [poll seconds, default 120]
Every poll, scans the latest messages of every session in groups whose provider is cheaperinference for a failure
mentioning credits/balance/payment (HTTP 402 and friends). On a hit it confirms with a 1-token request to the
cheaperinference API; only if that also fails with a credit error does it rewrite those group files to
openrouter/deepseek/deepseek-v4.1-flash and run `opencode_sup.py <group> switch`. Other errors are logged only.
Log: work/opencode/fallback.log
"""
import base64, glob, json, os, re, subprocess, sys, time, urllib.error, urllib.parse, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)
POLL = int(sys.argv[1]) if len(sys.argv) > 1 else 120
CREDIT = re.compile(r"credit|balance|insufficient|payment|402|quota|top.?up|billing", re.I)
TARGET = {"provider": "openrouter", "model": "deepseek/deepseek-v4.1-flash"}


def log(*a):
    open(W("work/opencode/fallback.log"), "a").write(time.strftime("%H:%M:%S ") + " ".join(map(str, a)) + "\n")


def service():
    for _ in range(10):
        m = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"], capture_output=True,
                                                         text=True).stdout)
        if m:
            break
        time.sleep(1)
    url = m.group(0)
    pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
    return url, {"Authorization": "Basic " + base64.b64encode(("opencode:" + pw).encode()).decode()}


def get(path):
    url, h = service()
    loc = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)
    with urllib.request.urlopen(urllib.request.Request(url + path + ("&" if "?" in path else "?") + loc, headers=h),
                                timeout=60) as r:
        return json.loads(r.read() or b"{}")


def ci_key():
    for l in open(os.path.expanduser("~/Documents/Secrets.txt")):
        m = re.search(r"ci_live_\w+", l)
        if m:
            return m.group(0)


def confirm():
    """True only if cheaperinference itself refuses a 1-token request for a credit reason."""
    req = urllib.request.Request("https://api.cheaperinference.com/v1/chat/completions", method="POST",
                                 headers={"Authorization": "Bearer " + ci_key(), "content-type": "application/json"},
                                 data=json.dumps({"model": "deepseek-v4.1-flash", "max_tokens": 1,
                                                  "messages": [{"role": "user", "content": "ok"}]}).encode())
    try:
        urllib.request.urlopen(req, timeout=60).read()
        return False, "probe ok"
    except urllib.error.HTTPError as e:
        body = e.read().decode(errors="replace")[:300]
        return (e.code == 402 or bool(CREDIT.search(body))), "probe HTTP %d %s" % (e.code, body)
    except Exception as e:
        return False, "probe error %s" % e


while True:
    try:
        groups = [f for f in glob.glob(W("work/opencode/groups/*.json"))
                  if json.load(open(f)).get("provider") == "cheaperinference"]
        if not groups:
            log("no cheaperinference groups left; exiting")
            break
        hit = None
        for f in groups:
            for sid in json.load(open(f)).get("sessions", {}).values():
                for m in get("/api/session/%s/message?limit=3" % sid).get("data", []):
                    t = json.dumps({k: v for k, v in m.items() if k in ("error", "outcome", "content")})
                    if ("error" in m or m.get("outcome") == "failed") and CREDIT.search(t):
                        hit = (os.path.basename(f), sid, t[:200])
        if hit:
            ok, why = confirm()
            log("suspected credit failure", hit, "->", why)
            if ok:
                for f in groups:
                    g = json.load(open(f))
                    g.update(TARGET)
                    g.pop("cache_ns", None)  # cheaperinference-only aliases don't exist on OpenRouter
                    json.dump(g, open(f, "w"), indent=1)
                    name = os.path.basename(f)[:-5]
                    out = subprocess.run([sys.executable, W("tools/opencode_sup.py"), name, "switch"],
                                         capture_output=True, text=True)
                    log("switched", name, "to openrouter:", out.stdout.count("ok"), "sessions", out.stderr[-200:])
                break
    except Exception as e:
        log("poll error", e)
    time.sleep(POLL)
