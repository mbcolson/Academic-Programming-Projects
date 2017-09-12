void swapStudent(struct Student *pA, struct Student *pB);

#include "student.inc"

.text

.global swapStudent

swapStudent:
# pseudocode:

#   local struct Student x

#   x = *pA

#   *pA = *pB

#   *pB = x

ret


.text
.global swapStudent
swapStudent:
oldEbp = 0
retAddr = oldEbp + 4
pA = retAddr + 4
pB = pA + 4
x = oldEbp - 44
pushl %ebp
movl %esp,%ebp

movl pA(%ebp),%eax
movl (%eax),%ebx
movl %ebx,x(%ebp)

movl pB(%ebp),%ecx
movl (%ecx),%ebx
movl %ebx,(%eax)

movl x(%ebp),%edx
movl %edx,(%ecx)

movl %ebp,%esp
popl %ebp
ret 
