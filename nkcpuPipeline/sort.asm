.data
value: .word 29,23,35,50,15,34,5,41,53,13,86,20,4,6,15,71,8,52,19,37
.text
main: add $s7,$zero,$zero
p1: la $v2,value
lw $v0,($v2+$s7)
blez $v0,p6
addi $s6,$s7,1
p2: lw $v1,($v2+$s6)
blez $v1,p3
slt $t0,$v0,$v1
blez $t0,p5
sw $v0,($v2+$s6)
sw $v1,($v2+$s7)
p5: addi $s6,$s6,1
j p2
p3: addi $s7,$s7,1
j p1
p6: add $s7,$zero,$zero
p7: li $v0,1
la $v2,value
lw $a0,($v2+$s7)
blez $a0,p8
syscall
addi $s7,$s7,1
j p7
p8: #end with a blank line