
extern task_t* current_task;

void panic(registers_t* r)
{
     beep();
     kprintf("\n\n\t\tPANIC\n\n");
     kprintf("Task PID: %d\n",current_task->id);
     kprintf("EIP: 0x%x ESP: 0x%x EBP: 0x%x uESP: 0x%x\n",r->eip,r->esp,r->ebp,r->useresp);
     kprintf("EDI: 0x%x ESI: 0x%x\n",r->edi,r->esi,r->ebp);
     kprintf("EAX: 0x%x EBX: 0x%x ECX: 0x%x EDX: 0x%x\n",r->eax,r->ebx,r->ecx,r->edx);
     kprintf("CS: 0x%x DS: 0x%x SS: 0x%x\n",r->cs,r->ds,r->ss);
     kprintf("INT: 0x%x ERROR: 0x%x\n",r->int_no,r->err_code);
     cli();
     halt();
}

void panic_assert(const char *file, u32int line, const char *desc)
{
    kprintf("Assertion failed (%d) at %s:%d\n",desc,file,line);
}
