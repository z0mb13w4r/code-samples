-- declare protocol
simple_protocol = Proto("SimpleProtocol",  "Example UDP protocol")

-- declare fields
timestamp = ProtoField.uint64("simple.timestamp", "timestamp", base.DEC)
field_a = ProtoField.uint8("simple.field_a", "field_a", base.DEC)
field_b = ProtoField.uint16("simple.field_b", "field_b", base.DEC)
field_c = ProtoField.uint32("simple.field_c", "field_c", base.DEC)
payload_bytes = ProtoField.bytes("simple.payload", "payload_bytes", base.NONE)
payload_str = ProtoField.string("simple.payload_str", "payload_str")

simple_protocol.fields = { timestamp, field_a, field_b, field_c, payload_bytes, payload_str }

function simple_protocol.dissector(buffer, pinfo, tree)
  -- retrieve buffer length
  length = buffer:len()

  -- filter empty packets
  if length == 0 then
    return
  end

  -- Set protocol name
  pinfo.cols.protocol = simple_protocol.name

  -- Add protocol to tree
  local subtree = tree:add(simple_protocol, buffer(), "Simple Protocol")

  -- Add fields to tree
  subtree:add_le(timestamp, buffer(0, 8))
  subtree:add_le(field_a, buffer(8, 1))
  subtree:add_le(field_b, buffer(9, 2))
  subtree:add_le(field_c, buffer(11, 4))
  subtree:add(payload_bytes, buffer(15, length - 15)) -- Remove header
  subtree:add(payload_str, buffer(15, length - 15)) -- Remove header
end

-- Match protocol by UDP port
local udp_port = DissectorTable.get("udp.port")
udp_port:add(65432, simple_protocol)
