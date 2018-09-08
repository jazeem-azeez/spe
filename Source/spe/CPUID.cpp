//Author - Niloy Mondal
//Reference - Intel Instruction Set Reference Volume 2
#include<stdio.h>
#include<conio.h>

int main()
{
	char *strFeatures[32]={	"FPU - x87 FPU on Chip",
							"VME - Virtual 8086 Enhancement",
							"DE - Debugging Extensions",
							"PSE - Page Size Extensions",
							"TSC - Time Stamp Counter",
							"MSR - RDMSR and WRMSR Support",
							"PAE - Physical Address Extensions",
							"MCE - Machine Check Exception",
							"CX8 - CMPXCHG8B instruction",
							"APIC - Advanced Programmable Interrupt Controller on Chip",
							" ",	//Reserved
							"SEP - SYSENTER and SYSEXIT",
							"MTRR - Memory Type Range Register",
							"PGE - PTE Global Bit",
							"MCA - Machine Check Architecture",
							"CMOV - Condtional Move/Compare Instruction",
							"PAT - Page Attribute Table",
							"PSE-32 - Page Size Extension",
							"PSN - Processor Serial Number",
							"CLFSH - CFLUSH Instruction",
							" ",	//Reserved
							"DS - Debug Store",
							"ACPI - Thermal Monitor and Clock Control",
							"MMX - MMX Technology",
							"FXSR - FXSAVE/FXRSTOR",
							"SSE- SSE Extensions",
							"SSE2 - SSE2 Extensions",
							"SS - Self Snoop",
							"HTT - Hyper Threading Tech",
							"TM - Thermal Monitor",
							" ",	//Reserved
							"PBE - Pend. Brk. En"};

	char VendorID[13];
	unsigned char SteppingID;
	unsigned char Model;
	unsigned char Family;
	unsigned char ProcessorType;
	unsigned char Brand;
	unsigned long VersionInfo;
	unsigned long FeatureInfo;

	_asm
	{
		mov eax,0
		cpuid							//CPUID Instruction
		mov dword ptr [VendorID],ebx
		mov dword ptr [VendorID+4],edx
		mov dword ptr [VendorID+8],ecx
		mov byte ptr [VendorID+12],0
	}
//Show the Vendor ID. Should be "GenuineIntel" if the processor is Intel"/////////////
	printf("Your processor is a %s\n",VendorID);
//Store all the required information in memory////////////////////////////////////////
	_asm
	{
		mov eax,1
		cpuid							//CPUID Instruction
		mov VersionInfo,eax				//Store Version Information
		mov FeatureInfo,edx				//Store Feature Information
		mov Brand,bl					//Store Brand Information
	}
//////////////////////////////////////////////////////////////////////////////////////
//Extract the SteppingID, model and family from the bit encoded VersionInfo and display
	SteppingID = VersionInfo & 0x0F;			//Stepping ID
	Model = (VersionInfo & 0xF0)>>4;			//Model
	Family = (VersionInfo & 0x0F00)>>8;			//Family
	ProcessorType = (VersionInfo & 3000)>>12;	//Processor Type
	printf("Stepping ID : %5d\n",SteppingID);
	printf("Model       : %5d\n",Model);
	printf("Family      : %5d\n",Family);
//////////////////////////////////////////////////////////////////////////////////////
//Show the Processor Type/////////////////////////////////////////////////////////////
	switch(ProcessorType)
	{
	case 0:
		printf("Processor Type : Original OEM Processor\n");
		break;
	case 1:
		printf("Processor Type : Intel OverDrive Processor\n");
		break;
	case 2:
		printf("Processor Type : Dual Processor\n");
		break;
	case 3:
		printf("Processor Type : Intel reserved\n");
	}
//////////////////////////////////////////////////////////////////////////////////////
//Show the Computer Brand/////////////////////////////////////////////////////////////
	printf("Your Computer Brand is :- ");
	switch(Brand)
	{
	case 0x00:
		printf("This Processor does not support the brand identification feature");break;
	case 0x01:
		printf("Intel Celeron processor");break;
	case 0x02:
		printf("Intel Pentium III processor");break;
	case 0x03:
		printf("Intel Pentium III Xeon or Intel Celeron processor");break;
	case 0x04:
		printf("Intel Pentium III processor");break;
	case 0x06:
		printf("Mobile Intel Pentium III processor-M");break;
	case 0x07:
		printf("Mobile Intel Celeron processor");break;
	case 0x08:
		printf("Intel Pentium 4 processor");break;
	case 0x09:
		printf("Intel Pentium 4 processor");break;
	case 0x0A:
		printf("Intel Celeron processor");break;
	case 0x0B:
		printf("Intel Xeon processor or Xeon processor MP");break;
	case 0x0C:
		printf("Intel Xeon processor MP");break;
	case 0x0E:
		printf("Mobile Intel Pentium 4  or Intel Xeon processor");break;
	case 0x0F:
		printf("Mobile Intel Celeron processor");break;
	case 0x13:
		printf("Mobile Intel Celeron processor");break;
	case 0x16:
		printf("Intel Pentium M processor");break;
	default:
		printf("Future Processor");
	}
	printf("\n---------------------Press any key to continue more----------------\n");
	_getch();
/////////////////////////////////////////////////////////////////////////////////////
//Show the Processor Features////////////////////////////////////////////////////////
	printf("Your Processor has the following Features:-\n");
	for(long i=0;i<32;i++)
	{
		_asm xor ebx,ebx
		_asm mov ebx,i
		_asm bt FeatureInfo,ebx	//"bt" is opcode to test a particular bit(on/off) in a string
								//The bit number to test is provided as the second operand
								//The result is stored in the carry flag
		_asm jnc Feature_not_installed
		printf("%s\n",strFeatures[i]);
Feature_not_installed:
		;
	}
//////////////////////////////////////////////////////////////////////////////////////
	printf("************************Programmer - Niloy Mondal***********************");
	return 1;
}