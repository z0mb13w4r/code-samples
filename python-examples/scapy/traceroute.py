#!/usr/bin/python3
from scapy.all import traceroute
import socket

# destination
target = "8.8.8.8"

# try only once (retry=0)
ans, unans = traceroute([target], maxttl=30, dport=80, retry=0, verbose=0)

print(f"=== traceroute to {target} ===")
for snd, rcv in ans:
  hop = snd.ttl
  ip = rcv.src
  try:
    host = socket.gethostbyaddr(ip)[0]
  except socket.herror:
    host = "?"
  print(f"{hop:2d} {ip:15s} {host}")

