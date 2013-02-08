[bits 16]
[org 0x7C00]

start:
  jmp short begin
  nop
  times 0x3b db 0

begin:
  cli ; disable interrupts
  jmp $

  times 512-($-$$)-2 db 0
  dw 0AA55h
