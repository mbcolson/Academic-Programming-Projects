int findMinIndex(struct Student *pClass, int numStudent);
#include "student.inc"
# pseudocode:
#   local int i,m
#   m = 0
#   i = 1
#   while i < numStudent do
#     if (cmpStudent(&pClass[i], &pClass[m]) < 0)
#       m = i
#     end if
#     i = i + 1
#   end while
#   return m
.text
.global findMinIndex
findMinIndex:
oldEbp = 0
retAddr = oldEbp + 4
pClass = retAddr + 4
numStudent = pClass + 4
m = oldEbp - 4
i = m - 4
pClass_itemsize = 44
pushl %ebp
movl %esp,%ebp
movl $0,m(%ebp)
movl $1,i(%ebp)
cmpl numStudent(%ebp),i(%ebp)
jnl endWhile
movl m(%ebp),%eax
movl $pClass_itemsize,%ebx
mull %ebx
addl $pClass,%eax
pushl %eax
movl i(%ebp),%eax
movl $pClass_itemsize,%ebx
mull %ebx
addl $pClass,%eax
pushl %eax
call cmpStudent
addl $8,%esp
cmpl $0,%eax
jnl endIf
movl i(%ebp),%ebx
movl %ebx,m(%ebp)
endIf:
movl i(%ebp),%ebx
addl $1,%ebx
movl %ebx,i(%ebp)
endWhile:
movl m(%ebp),%eax
movl %ebp,%esp
popl %ebp
ret
