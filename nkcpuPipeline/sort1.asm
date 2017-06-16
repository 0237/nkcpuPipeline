.data
value: .word 29,23,35,50,15,34,5,41,53,13,86,20,4,6,15,71,8,52,19,37
.text
main: add $s7,$zero,$zero
la $a2,value
p1: lw $a0,($a2+$s7)
blez $a0,p6
addi $s6,$s7,1
p2: lw $a0,($a2+$s7)
lw $a1,($a2+$s6)
blez $a1,p3
slt $t0,$a0,$a1
blez $t0,p5
sw $a0,($a2+$s6)
sw $a1,($a2+$s7)
p5: addi $s6,$s6,1
j p2
p3: addi $s7,$s7,1
j p1
p6: #end with a blank line