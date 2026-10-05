#!/usr/bin/env python3
"""Start an opencode session on the background service (so permission requests reach the broker) and send it a prompt.

usage: opencode_launch.py <provider/model> <title> <prompt file>
Prints the new session id. `opencode run` without --auto rejects permission requests when non-interactive, so
brokered sessions are created through the HTTP API instead.
"""
import base64, json, os, re, subprocess, sys, urllib.parse, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
model, title, pfile = sys.argv[1:4]
prov, mid = model.split("/", 1)
url = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"], capture_output=True, text=True).stdout).group(0)
pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
H = {"Authorization": "Basic " + base64.b64encode(("opencode:" + pw).encode()).decode(), "content-type": "application/json"}
LOC = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)


def post(path, body):
    req = urllib.request.Request(url + path + "?" + LOC, data=json.dumps(body).encode(), headers=H, method="POST")
    with urllib.request.urlopen(req, timeout=60) as r:
        return json.loads(r.read() or b"{}")


s = post("/api/session", {"title": title, "location": {"directory": ROOT}, "model": {"providerID": prov, "id": mid}})
sid = s.get("id") or s.get("data", {}).get("id")
post("/api/session/%s/prompt" % sid, {"text": open(pfile).read(),
                                       "model": {"providerID": prov, "id": mid}})
print(sid)
