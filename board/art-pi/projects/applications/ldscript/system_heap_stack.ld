dtcm_ram_start = ORIGIN(DTCMRAM);
dtcm_ram_size  = LENGTH(DTCMRAM);

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x8000;            /* 32K required amount of heap  */
_Min_Stack_Size = 0x800;            /* 1K required amount of stack */

/* system stack stored in DTCM area */
sys_heap_stack_top = dtcm_ram_start + _Min_Heap_Size + _Min_Stack_Size;    /* from top to bottom */

/* Highest address of the user mode stack */
_estack = dtcm_ram_start + dtcm_ram_size;
