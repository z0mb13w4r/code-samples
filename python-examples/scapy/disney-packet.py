#!/usr/bin/python3
from scapy.all import *

class Disney(Packet):
  name = "DisneyPacket"
  fields_desc = [
    ShortField("mickey", 5),
    XByteField("minnie", 3),
    XLongField("daisy", 8),
    IntEnumField("donald", 1, {1: "happy", 2: "cool", 3: "angry"}),
    ByteEnumField("pluto", 3, {1: "barks", 2: "whines", 3: "growls", 4: "howls"}),
    XIntField("goofy", 11),
    BitField("aurora", 2, 3),
    BitField("ariel", 1, 5)
  ]

d = Disney(mickey=1)
ls(d)
d.show()
print(raw(d))

