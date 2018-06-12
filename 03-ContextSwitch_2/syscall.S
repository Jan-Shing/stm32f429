.thumb
.syntax unified

.global syscall
syscall:
	svc 0   /* calling kernel function 0*/
	nop 	/* No Operation*/
	bx lr
