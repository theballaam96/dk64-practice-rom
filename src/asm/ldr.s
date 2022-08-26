.section    .text, "ax", @progbits
.set        nomips16
.set        nomicromips

.global     _start
.ent        _start
.type       _start, @function

_start:
LUI a0, hi(0x2000000) //start of ROM copy
LUI a1, hi(0x2000000 + customCodeSize)
ADDIU a1, a1, lo(0x2000000 + customCodeSize)
ADDIU a0, a0, lo(0x2000000)
LUI a2, customCodeUpper
JAL dmaFileTransfer
ORI a2, a2, customCodeLower //RAM location to copy to
J displacedBootCode
NOP

.end _start
.size _start, . - _start