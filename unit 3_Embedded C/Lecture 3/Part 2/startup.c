#include "stdint.h"
#define STACK_Start_SP 0x20001000
extern int main(void);
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;

void Rest_Handler(void)
{
	int i=0;
	unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA ;
	unsigned char* P_src = (unsigned char*)&_E_text;
	unsigned char* P_dst = (unsigned char*)&_S_DATA;
	for(i=0; i<DATA_size; i++)
	{
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src++) ;
	}

	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss ;
	P_dst = (unsigned char*)&_S_bss ;
	for(i=0; i<DATA_size; i++)
	{
		*((unsigned char*)P_dst++) = *(unsigned char*)0 ;
	}
	main();
}

void Default_Handler(void)
{
	Rest_Handler();
}

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));;
void H_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));;
void MM_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));;
void Bus_Fault(void) __attribute__((weak, alias("Default_Handler")));;
void Usage_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));;

uint32_t vectors[] __attribute__((section(".vectors"))) = {
	STACK_Start_SP,
	(uint32_t) &Rest_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault,
	(uint32_t) &Usage_Fault_Handler,
};
