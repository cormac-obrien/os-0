section .text

global isr0
isr0: ; Division by zero
  pushad
  push isr0_msg
  extern kernel_puts
  call kernel_puts
  popad
  iret

section .data
global isr0_msg
isr0_msg:
db "Divided by zero, fuck you", 0x0a, 0x00
