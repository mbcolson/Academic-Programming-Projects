void selSort(struct Student *pClass, int numStudent);

#include "student.inc"
# pseudocode:
#   local int i
#   for (i = 0; i < numStudent-1; ++i)
#     swapStudent(&pClass[i],&pClass[i+findMinIndex(&pClass[i], numStudent-i)])
#                                 XOR (one or the other)
#     swapStudent(&pClass[i],&pClass[i+findMinIndex(pClass+i, numStudent-i)])
#   end for

.text
.global selSort
selSort:
oldEbp = 0
retAddr = oldEbp + 4  
pClass = oldEbp + 4
numStudent = pClass + 4
i = oldEbp - 4
pClass_itemsize = 44
pushl %ebp
movl %esp,%ebp
movl $0,i(%ebp)
movl numStudent(%ebp),%ecx
subl $1,%ecx
beginForLoop:
cmpl %ecx,i(%ebp)
jnl endForLoop
pushl %ecx
movl i(%ebp),%eax
movl $pClass_itemsize,%ebx
mull %ebx
addl $pClass,%eax
pushl %eax
call findMinIndex
addl $8,%esp
mull %ebx
addl $pClass,%eax
pushl %eax
movl i(%ebp),%eax
mull %ebx
addl $pClass,%eax
pushl %eax
call swapStudent
addl $12,%esp
movl i(%ebp),%edx
addl $1,%edx
movl %edx,i(%ebp)
jmp beginForLoop
endForLoop:
movl %ebp,%esp
popl %ebp
ret
