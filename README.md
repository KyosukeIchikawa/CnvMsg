# CnvMsg
Conveter for JSON and MessagePack

## EXSAMPLE: translating JSON to MessagePack
CnvMsg.exe /mode pack input.dat output.msg

## EXSAMPLE: translating MessagePack to JSON
CnvMsg.exe /mode unpack input.msg output.dat

## EXSAMPLE: set precision
CnvMsg.exe /mode unpack /precision 9 input.msg output.dat

## EXSAMPLE: use scientific format
CnvMsg.exe /mode unpack /s /precision 9 input.msg output.dat
