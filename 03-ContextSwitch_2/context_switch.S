.thumb
.syntax unified

.type svc_handler, %function
.global svc_handler
svc_handler:
	/*	Save user state */
	mrs r0, psp       /* stack pointer of User task  stores in PSP*/    
	stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}  /* push into PSP*/
	
	/* Do Some Stuff*/
	
	/* load kernel state */
	pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}  /* pop out from MSP*/
	msr psr, ip


	bx lr

.global activate
activate:
	/* save kernel state*/
	mrs ip, psr
	push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}  

	/* load user state */
	ldmia r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr }

	msr psp, r0

	mov r0, #0xfffffff0
	cmp lr, r0            /* lr - 0xfffffff0*/

	ittt ls
	movls r0, #3
	msrls control, r0    /* Set thread mode to un-priv and use PSP   */

	isbls     			/* After programming CONTROL register        */
			  			/* the proceccor should execute ISB to flush */
			  			/* pipeline and re-fetch instructions        */
	bx lr

