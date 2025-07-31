.RxDescripSection (NOLOAD) : ALIGN(4)
{
    . = ALIGN(4);
    *(.RxDescripSection)
    *(.RxDescripSection.*)
    . = ALIGN(4);
    __RxDescripSection_free__ = .;
} > RAM3_D2

.TxDescripSection (NOLOAD) : ALIGN(4)
{
    . = ALIGN(4);
    *(.TxDescripSection)
    *(.TxDescripSection.*)
    . = ALIGN(4);
    __TxDescripSection_free__ = .;
} > RAM3_D2
