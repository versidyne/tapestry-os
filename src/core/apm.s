;
; apm.s -- advanced power management code
;

[GLOBAL check_apm]    ; Allows the C code to call init_apm()

check_apm:
    
    ;preform an installation check
    mov ah,53h            ;this is an APM command
    mov al,00h            ;installation check command
    xor bx,bx             ;device id (0 = APM BIOS)
    int 15h               ;call the BIOS function through interrupt 15h

[GLOBAL init_apm]    ; Allows the C code to call init_apm()

init_apm:
    
    ;Enable power management for all devices
    
    mov ah,53h              ;this is an APM command
    mov al,08h              ;Change the state of power management...
    mov bx,0001h            ;...on all devices to...
    mov cx,0001h            ;...power management on.
    int 15h                 ;call the BIOS function through interrupt 15h

[GLOBAL standby]    ; Allows the C code to call standby()

standby:
    
    ;Set the power state for all devices
    mov ah,53h              ;this is an APM command
    mov al,07h              ;Set the power state...
    mov bx,0001h            ;...on all devices to...
    mov cx,01h              ;initiate standby
    int 15h                 ;call the BIOS function through interrupt 15h
    call 0x30:0x0 
    jc apm_end

[GLOBAL suspend]    ; Allows the C code to call suspend()

suspend:
    
    ;Set the power state for all devices
    mov ah,53h              ;this is an APM command
    mov al,07h              ;Set the power state...
    mov bx,0001h            ;...on all devices to...
    mov cx,02h              ;initiate suspend
    int 15h                 ;call the BIOS function through interrupt 15h
    call 0x30:0x0 
    jc apm_end

[GLOBAL shutdown]    ; Allows the C code to call shutdown()

shutdown:
    
    push ebp
    mov ebp, esp
    
    pushf
    push ebx
    push ecx
    push edx
    
    ;Set the power state for all devices
    mov ah,53h              ;this is an APM command
    mov al,07h              ;Set the power state...
    mov bx,0001h            ;...on all devices to...
    mov cx,03h              ;initiate shutdown
    int 15h                 ;call the BIOS function through interrupt 15h
    call 0x30:0x0 
    jc apm_end
    
apm_end:
    
    pop edx   
    pop ecx   
    pop ebx   
    popf
    
    mov esp, ebp
    pop ebp
    ret 0               ; Exit for good measure and in case of failure
