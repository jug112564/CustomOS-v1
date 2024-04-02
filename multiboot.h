#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

typedef struct Module Module;
struct Module
{
	unsigned int ModuleStart;
	unsigned int ModuleEnd;
	char* Name;
	unsigned int Reserved;
}__attribute__((packed));

struct AOUTSymbolTable
{
	unsigned int tabsize;
	unsigned int strsize;
	unsigned int addr;
	unsigned int reserved;
}__attribute__((packed));

struct ELFHeaderTable
{
	unsigned int num;
	unsigned int size;
	unsigned int addr;
	unsigned int shndx;
}__attribute__((packed));

#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2

struct multiboot_mmap_entry
{
	unsigned int size;
	unsigned int baseAddressLower;
	unsigned int baseAddressHigher;
	unsigned int lengthLower;
	unsigned int lengthHigher;
	unsigned int type;
}__attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;
typedef struct multiboot_mmap_entry multiboot_mmap_entry;

struct drive_info
{
	/* The size of this structure.  */
	unsigned long size;

	/* The BIOS drive number.  */
	unsigned char drive_number;

	/* The access mode (see below).  */
	unsigned char drive_mode;

	/* The BIOS geometry.  */
	unsigned short drive_cylinders;
	unsigned char drive_heads;
	unsigned char drive_sectors;

	/* The array of I/O ports used for the drive.  */
	unsigned short drive_ports;
}__attribute__((packed));

struct ROMConfigurationTable
{
	unsigned short Length;
	unsigned char Model;
	unsigned char Submodel;
	unsigned char BiosRevision;
	int DualBus : 1;
	int MicroChannelBus : 1;
	int EBDAExists : 1;
	int WaitForExternalEventSupported : 1;
	int Reserved0 : 1;
	int HasRTC : 1;
	int MultipleInterruptControllers : 1;
	int BiosUsesDMA3 : 1;
	int Reserved1 : 1;
	int DataStreamingSupported : 1;
	int NonStandardKeyboard : 1;
	int BiosControlCpu : 1;
	int BiosGetMemoryMap : 1;
	int BiosGetPosData : 1;
	int BiosKeyboard : 1;
	int DMA32Supported : 1;
	int ImlSCSISupported : 1;
	int ImlLoad : 1;
	int InformationPanelInstalled : 1;
	int SCSISupported : 1;
	int RomToRamSupported : 1;
	int Reserved2 : 3;
	int ExtendedPOST : 1;
	int MemorySplit16MB : 1;
	unsigned char Reserved3 : 1;
	unsigned char AdvancedBIOSPresence : 3;
	int EEPROMPresent : 1;
	int Reserved4 : 1;
	int FlashEPROMPresent : 1;
	int EnhancedMouseMode : 1;
	unsigned char Reserved5 : 6;
}__attribute__((packed));

struct APMTable
{
	unsigned short Version;
	unsigned short CS;
	unsigned int Offset;
	unsigned short CS16Bit;	//This is the 16-bit protected mode code segment
	unsigned short DS;
	unsigned short Flags;
	unsigned short CSLength;
	unsigned short CS16BitLength;
	unsigned short DSLength;
}__attribute__((packed));

struct VbeInfoBlock
{
	char Signature[4];
	unsigned short Version;
	short OEMString[2];
	unsigned char Capabilities[4];
	short VideoModes[2];
	short TotalMemory;
}__attribute__((packed));

struct VbeModeInfo
{
	unsigned short ModeAttributes;
	char WinAAttributes;
	char WinBAttributes;
	unsigned short WinGranularity;
	unsigned short WinSize;
	unsigned short WinASegment;
	unsigned short WinBSegment;
	unsigned int WinFuncPtr;
	short BytesPerScanLine;
	short XRes;
	short YRes;
	char XCharSize;
	char YCharSize;
	char NumberOfPlanes;
	char BitsPerPixel;
	char NumberOfBanks;
	char MemoryModel;
	char BankSize;
	char NumberOfImagePages;
	char res1;
	char RedMaskSize;
	char RedFieldPosition;
	char GreenMaskSize;
	char GreenFieldPosition;
	char BlueMaskSize;
	char BlueFieldPosition;
	char RsvedMaskSize;
	char RsvedFieldPosition;
	char DirectColorModeInfo; //MISSED IN THIS TUTORIAL!! SEE ABOVE
	//VBE 2.0
	unsigned int PhysBasePtr;
	unsigned int OffScreenMemOffset;
	short OffScreenMemSize;
	//VBE 2.1
	short LinbytesPerScanLine;
	char BankNumberOfImagePages;
	char LinNumberOfImagePages;
	char LinRedMaskSize;
	char LinRedFieldPosition;
	char LingreenMaskSize;
	char LinGreenFieldPosition;
	char LinBlueMaskSize;
	char LinBlueFieldPosition;
	char LinRsvdMaskSize;
	char LinRsvdFieldPosition;
	char res2[194];
}__attribute__((packed));

struct multiboot_info
{
	/* Multiboot info version number */
	unsigned int flags;

	/* Available memory from BIOS */
	unsigned int mem_lower;
	unsigned int mem_upper;

	/* "root" partition */
	unsigned int boot_device;

	/* Kernel command line */
	char* cmdline;

	/* Boot-Module list */
	unsigned int mods_count;
	struct Module* Modules;

	union
	{
		struct AOUTSymbolTable AOUTTable;
		struct ELFHeaderTable ELFTable;
	} SymbolTables;

	/* Memory Mapping buffer */
	unsigned int mmap_length;
	unsigned int mmap_addr;

	/* Drive Info buffer */
	unsigned int drives_length;
	struct drive_info* drives_addr;

	/* ROM configuration table */
	struct ROMConfigurationTable* ConfigTable;

	/* Boot Loader Name */
	char* boot_loader_name;

	/* APM table */
	struct APMTable* APMTable;

	/* Video */
	struct VbeInfoBlock* vbe_control_info;
	struct VbeModeInfo* vbe_mode_info;
	unsigned short vbe_mode;
	unsigned short vbe_interface_seg;
	unsigned short vbe_interface_off;
	unsigned short vbe_interface_len;

	//GRUB2
	unsigned long long framebuffer_addr;	
	unsigned int framebuffer_pitch;
	unsigned int framebuffer_width;
	unsigned int framebuffer_height;
	unsigned char framebuffer_bpp;
#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED 0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB     1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
	unsigned char framebuffer_type;
	union
	{
		struct
		{
			unsigned int framebuffer_palette_addr;
			unsigned short framebuffer_palette_num_colors;
		}framebuffer_palette;
		struct
		{
			unsigned char framebuffer_red_field_position;
			unsigned char framebuffer_red_mask_size;
			unsigned char framebuffer_green_field_position;
			unsigned char framebuffer_green_mask_size;
			unsigned char framebuffer_blue_field_position;
			unsigned char framebuffer_blue_mask_size;
		}framebuffer_MASK;
	};

}__attribute__((packed));
typedef struct multiboot_info multiboot_info_t;
typedef struct multiboot_info multiboot_info;
#endif