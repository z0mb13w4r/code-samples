local eth_info = {
  version = "0.0.0",
  author = "Kyle Wickens",
  descriptor = "Ethernet frame example.",
  repository = ""
}

set_plugin_info(eth_info)

-- add some field(s) to the protocol
local pf = {
  field_typ = ProtoField.string("proto_name.type", "some field description"),
  field_src = ProtoField.new("some other field description", "proto_name.src", ftypes.ETHER),
  field_dst = ProtoField.new("some other field description", "proto_name.dst", ftypes.ETHER)
}

-- create a protocol to attach new fields to
local eth_p = Proto.new("proto_name", "some protocol decription")

eth_p.fields = pf

-- create a field extractor to copy packet field data
local eth_f = Field.new("eth.type") --arp.dst.proto_ipv4")

-- create the postdissector function that will run on each frame/packet
function eth_p.dissector(tvb,pinfo,tree)
  local subtree = nil
  
  -- copy existing field(s) into table for processing
  finfo = { eth_f() }
  
  if (#finfo > 0) then
    if not subtree then
      subtree = tree:add(eth_p)
      --subtree = tree:add(eth_p, tvb(), "Custom Ethernet Analysis")
    end

 -- add fields to the subtree (extracting byte ranges)
    subtree:add(pf.field_dst, tvb(0, 6))
    subtree:add(pf.field_src, tvb(6, 6))

    print("-----")
  -- extract EtherType as a number to do something with the payload
    local etype = tvb(12, 2):uint()
    print(string.format("etype: 0x%04x", etype))

    print("tvb.len: " .. tvb:len())

    for k, v in pairs(finfo) do
      -- process data and add results to the tree
      subtree:add(pf.field_typ, v.display)
      print("v.name: " .. v.name)
      print("v.display: " .. v.display)
      print(string.format("v.value:  %d 0x%04x", v(), v()))
      print("v.offset: " .. v.offset)
      print("v.length: " .. v.len)
    end
  end
end

-- register the new protocol as a postdissector
--#local eth_type = DissectorTable.get("ethertype")
--eth_type:add(0x0800, eth_p)
register_postdissector(eth_p)

