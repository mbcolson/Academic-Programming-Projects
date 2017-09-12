int readStudent(struct Student *pRecord);

#include "student.inc"
.text
.global readStudent
readStudent:
oldEbp = 0
retAddr = oldEbp + 4
pRecord = retAddr + 4
counter = oldEbp - 4
retVal = counter - 4
ch = counter - 4
pushl %ebp
movl %esp,%ebp
addl $ch,%esp
movl pRecord(%ebp),%ecx      # %ecx is being used as ptr
movl $0,retVal(%ebp)
movl $0,counter(%ebp)
beginDo.1:
  movl $3,%eax
  movl $0,%ebx
  movl $1,%edx
  int $0x80
  cmpl $0,%eax     # here %eax will contain the number of characters actually read
  jng endif
  cmpb $10,(%ecx)
  jz endif
    addl $1,%ecx               # ++ptr
    addl $1,counter(%ebp)      # ++counter
  endif:
cmpl $0,%eax
jng endDoWhile.1
cmpb $10,(%ecx)
jz endDoWhile.1
cmpl $31,counter(%ebp)
jnl endDoWhile.1
jmp beginDo.1
endDoWhile.1:
cmpl $0,%eax
jng endif.2
  beginWhile:
  cmpb $10,(%ecx)
  jz endWhile
  cmpl $0,%eax
  jng endWhile
    movl $3,%eax
    movl $0,%ebx
    movl $1,%edx
    int $0x80
    jmp beginWhile
  endWhile:
  movb $0,(%ecx)
  movl $0,counter(%ebp)
  beginDo.2:
    #pushl %ecx
    movl $3,%eax
    movl $0,%ebx
    movl %ebp,%ecx
    addl $ch,%ecx
    movl $1,%edx
    int $0x80
    #popl %ecx
  cmpl $0,%eax
  jng endif.1
  cmpb $10,ch(%ebp)
  jz endif.1
    movl counter(%ebp),%ebx
    pushl %ecx
    pushl %eax
    movl $0,%ecx
    movb ch(%ebp),%cl
    subb $'0',%cl
    movl $10,%eax
    mull %ebx
    addl %ecx,%eax
    movl %eax,counter(%ebp)
    popl %eax
    popl %ecx
  endif.1:
  cmpl $0,%eax
  jng endDoWhile.2
  cmpb $10,ch(%ebp)
  jz endDoWhile.2
  jmp beginDo.2
  endDoWhile.2:
  movl pRecord(%ebp),%ebx
  addl $Student_score,%ebx
  movl counter(%ebp),%eax
  movl %eax,(%ebx)
  movl $1,retVal(%ebp)
endif.2:
movl retVal(%ebp),%eax
movl %ebp,%esp
popl %ebp
ret
