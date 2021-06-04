mov AX, 10000
sub AX, 10005
mov DS, AX
mov BX, 1455
jmp ok
inc AX
push 20
pop AX
mov CX, 3200
mov DX, 10
ok:
mov BP, 20
