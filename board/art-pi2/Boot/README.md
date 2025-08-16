# rt-thread print
System Clock information
SYSCLK_Frequency = 600000000
HCLK_Frequency   = 300000000
PCLK1_Frequency  = 150000000
PCLK2_Frequency  = 150000000
PLL2S_XSPI1_2_Frequency  = 200000000
PLL2T_Frequency  = 133333333

   ___  ______  _____         ______  _   ______  _____  _____  _____ 
  / _ \ | ___ \|_   _|        | ___ \(_)  | ___ \/  _  \/  _  \|_   _|
 / /_\ \| |_/ /  | |   ______ | |_/ / _   | |_/ /| | | || | | |  | |  
 |  _  ||    /   | |  |______||  __/ | |  | ___ \| | | || | | |  | |  
 | | | || |\ \   | |          | |    | |  | |_/ /\ \_/ /\ \_/ /  | |  
 \_| |_/\_| \_|  \_/          \_|    |_|  \____/  \___/  \___/   \_/  

 Powered by RT-Thread.

[I/XSPI] Read Flash ID success:0xef 0x5b 0x1a
msh >[I/XSPI] Reconfigure Flash clock

[I/XSPI] Flash Re-Enter Octal DTR and Read ID success:ef 1a 00
[I/XSPI] Flash XIP success

Jump to APP...

#################################################################################
## boot print

        SFDP::1 - reset data SFDPObject to zero
        SFDP::2 - initialize the SFDPObject
        SFDP::3 - set memory link and speed to 50Mhz maximum
        SFDP::4 - analyze the SFPD structure to get driver information
                SFDP::SFDP_GetHeader
                SFDP::try a command configuration
                SFDP::SFDP_ReadHeader
                SFDP::SFDP signature::0x50444653
                SFDP::signature of the header: OK
                SFDP::param_number=0x2
                SFDP::AccessProtocol=0xff
        SFDP::5 - reset the memory
                SFDP::SFDP_MemoryReset
                SFDP::sfdp_get_paraminfo
                SFDP::-> type SFPD_PARAMID_FUNCTION_JEDEC
                SFDP::-> info SFPD_PARAMID_BASIC_SPIPROTOCOL
                SFDP::::reset 0x66 0x99
        SFDP::6 - analyze the SFPD structure to get driver information
                SFDP::SFDP_GetHeader
                SFDP::try a command configuration
                SFDP::SFDP_ReadHeader
                SFDP::SFDP signature::0x50444653
                SFDP::signature of the header: OK
                SFDP::param_number=0x2
                SFDP::AccessProtocol=0xff
        SFDP::7 - read the flash ID
        SFDP:: Flash ID(0xef:0x5b:0x1a:0x2)
        SFDP::8 - collect the SFDP data
                SFDP::SFDP_CollectData
                SFDP::sfdp_get_paraminfo
                SFDP::-> type SFPD_PARAMID_FUNCTION_JEDEC
                SFDP::-> info SFPD_PARAMID_BASIC_SPIPROTOCOL
                SFDP::sfdp_get_paraminfo
                SFDP::-> type SFPD_PARAMID_FUNCTION_JEDEC
                SFDP::-> info SFPD_PARAMID_4BYTE_ADDRESS_INSTRUCTION
                SFDP::sfdp_get_paraminfo
                SFDP::-> info SFPD_PARAMID_XSPI_V1_0
        SFDP::9 - build the generic driver information and prepare the physical layer
                SFDP::SFDP_BuildGenericDriver
                SFDP::-> flash size: 2^0x1a
        SFDP::10 - adjust the frequency if required
        SFDP::11 - read again the SFDP header to adjust memory type if necessary
                SFDP::SFDP_ReadHeader
                SFDP::SFDP signature::0x0
                SFDP::signature of the header: KO
        SFDP::ERROR::EXTMEM_DRIVER_NOR_SFDP_MEMTYPE_CHECK
art-pi2 bootloader
booting...
