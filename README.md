# CnvMsg
Conveter for JSON and MessagePack

# translating JSON to MessagePack
CnvMsg.exe /mode pack input.dat output.msg

# translating MessagePack to JSON
CnvMsg.exe /mode unpack input.msg output.dat

# translating MessagePack to JSON (set precision)
CnvMsg.exe /mode unpack /precision 9 input.msg output.dat

# translating MessagePack to JSON (use scientific format)
CnvMsg.exe /mode unpack /s /precision 9 input.msg output.dat
