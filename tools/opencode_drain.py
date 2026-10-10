#!/usr/bin/env python3
"""Watch a brokered opencode wave to completion: re-prompt idle-but-unfinished sessions and
interrupt sessions whose current model call has hung.

usage: opencode_drain.py <group> [--interval S=60] [--cooldown S=300] [--hang S=900] [--once]

Each pass:
  * a range is DONE when its manifest+nonmatching+partial count >= its function count;
  * a range that is idle, unfinished, has no pending permission request, and whose last assistant
    message is older than --cooldown is re-prompted (nudge) on its per-session alias model;
  * a range that is active but whose open model call has run longer than --hang is interrupted and
    re-prompted.
Exits 0 ("DRAIN_COMPLETE") once every range is done. Safe to kill and restart: it holds no state on
disk beyond appending to work/opencode/drain_<group>.log.
"""
import argparse, base64, json, os, re, subprocess, sys, time, urllib.error, urllib.parse, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)


def svc():
    for _ in range(10):
        m = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"], capture_output=True,
                                                         text=True).stdout)
        if m:
            return m.group(0)
        time.sleep(1)
    sys.exit("opencode service not reachable")


url = svc()
_pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
H = {"Authorization": "Basic " + base64.b64encode(("opencode:" + _pw).encode()).decode(),
     "content-type": "application/json"}
LOC = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)


def api(method, path, body=None):
    req = urllib.request.Request(url + path + ("&" if "?" in path else "?") + LOC, method=method, headers=H,
                                 data=json.dumps(body).encode() if body is not None else None)
    try:
        with urllib.request.urlopen(req, timeout=60) as r:
            return json.loads(r.read() or b"{}")
    except urllib.error.HTTPError as e:
        return {"error": e.code, "body": e.read().decode()[:200]}


ap = argparse.ArgumentParser()
ap.add_argument("group")
ap.add_argument("--interval", type=int, default=60)
ap.add_argument("--cooldown", type=int, default=300, help="min seconds idle before re-nudging a range")
ap.add_argument("--hang", type=int, default=900, help="seconds an open model call may run before interrupt")
ap.add_argument("--once", action="store_true")
a = ap.parse_args()

GF = W("work/opencode/groups", a.group + ".json")
G = json.load(open(GF))
SESS = G.get("sessions", {})
BATCH = json.load(open(W("work/batches", G["batch"] + ".json")))
LOG = W("work/opencode", "drain_%s.log" % a.group)


def log(msg):
    line = "%s %s" % (time.strftime("%H:%M:%S"), msg)
    print(line, flush=True)
    open(LOG, "a").write(line + "\n")


def model_of(k):
    mid = G["model"]
    if G.get("cache_ns") and G.get("provider") == "cheaperinference":
        mid = "%s-c%02d" % (mid, int(k) % int(G["cache_ns"]))
    return {"providerID": G["provider"], "id": mid}


def progress(k):
    lo, hi = G["ranges"][k]
    tot = done = 0
    for i in range(lo, hi + 1):
        sid = BATCH[i]["id"]
        tot += len(BATCH[i]["vas"])
        for f in ("manifest.txt", "nonmatching.txt", "partial.txt"):
            p = W("match/slices", sid, f)
            if not os.path.exists(p):
                continue
            done += sum(1 for l in open(p) if re.match(r"\s*(?:0x)?[0-9a-fA-F]{6,8}\b", l)) if f != "manifest.txt" \
                else sum(1 for l in open(p) if l.strip() and not l.lstrip().startswith("#"))
    return tot, done


def pending(sid):
    r = api("GET", "/api/session/%s/permission" % sid)
    if "error" in r:
        return False
    return bool(r.get("data"))


def last_assistant(sid):
    m = api("GET", "/api/session/%s/message?limit=3" % sid).get("data", [])
    for x in m:
        if x.get("type") == "assistant" or x.get("role") == "assistant":
            return x
    return None


nudged_at = {}   # sid -> (monotonic time, done-count when nudged)
loops = 0
while True:
    loops += 1
    now = time.time()
    active = api("GET", "/api/session/active").get("data", {})
    if isinstance(active, list):
        active = {s.get("id", s) if isinstance(s, dict) else s: 1 for s in active}
    finished = busy = 0
    for k in range(len(G["ranges"])):
        sid = SESS.get(str(k))
        if not sid:
            continue
        tot, done = progress(k)
        if done >= tot:
            finished += 1
            continue
        if pending(sid):
            busy += 1
            continue
        last = last_assistant(sid)
        t = (last or {}).get("time", {})
        created = (t.get("created") or 0) / 1000
        completed = (t.get("completed") or 0) / 1000
        is_active = sid in active
        if is_active:
            if created and not completed and now - created > a.hang:
                log("unhang r%d %s (open %.0fs)" % (k, sid, now - created))
                api("POST", "/api/session/%s/interrupt" % sid, {})
                api("POST", "/api/session/%s/prompt" % sid, {"text": "Your previous model call hung and was "
                    "interrupted. Continue your task from the files already written in your slices.",
                    "model": model_of(k)})
                nudged_at[sid] = (now, done)
            else:
                busy += 1
            continue
        # idle and unfinished
        since = now - (completed or created or 0)
        prev = nudged_at.get(sid)
        if prev and prev[1] == done and now - prev[0] < a.cooldown:
            continue
        if since < a.cooldown:
            continue
        log("nudge r%d %s (done %d/%d, idle %.0fs)" % (k, sid, done, tot, since))
        api("POST", "/api/session/%s/model" % sid, {"model": model_of(k)})
        r = api("POST", "/api/session/%s/prompt" % sid, {"text": "Continue your task: check the files already "
            "written in your slices and finish the remaining slices, then give the final one-line-per-slice summary.",
            "model": model_of(k)})
        if "error" in r:
            log("  nudge failed r%d: %s" % (k, r))
        nudged_at[sid] = (now, done)
    log("pass %d: %d/%d ranges done, %d busy/working" % (loops, finished, len(G["ranges"]), busy))
    if finished == len(G["ranges"]):
        log("DRAIN_COMPLETE")
        sys.exit(0)
    if a.once:
        sys.exit(0)
    time.sleep(a.interval)
