/*
 * usb_parallel_port.c
 *
 *  Created on: Apr 15, 2020
 *      Author: wruslan

// ========================================================
(1) PROLIFIC USB-to-Serial PL2303 cable, making it a RS-232 serial port device.
(2) PROLIFIC USB-to-Parallel PL2305 cable, making it a IEEE-1284 parallel port device.

Both cables are USB version 1.1 specification compliant.

The PL2303 chip on the Prolific Technology USB-to-Serial cable device,
is a full-duplex transmitter and receiver (TXD and RXD) for read and
write serial communications.

The PL2305 chip on the USB-to-Parallel cable emulates a Bidirectional
printer device so can also be used for read and write parallel communications.

Note: The USB-to-Parallel cable (PROLIFIC) is identical to USB-to-Parallel cable (KATRON)

=========================================
(1) For USB-to-Parallel cable (PROLIFIC)
=========================================
wruslan@HP-EliteBook-8470p-Ub1804:~$ dmesg
....
[10905.859361] usb 1-1.6: new full-speed USB device number 21 using ehci-pci
[10905.969246] usb 1-1.6: New USB device found, idVendor=067b, idProduct=2305
[10905.969251] usb 1-1.6: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[10905.969253] usb 1-1.6: Product: IEEE-1284 Controller
[10905.969255] usb 1-1.6: Manufacturer: Prolific Technology Inc.
[10905.976090] usblp 1-1.6:1.0: usblp0: USB Bidirectional printer dev 21 if 0 alt 1 proto 2 vid 0x067B pid 0x2305
wruslan@HP-EliteBook-8470p-Ub1804:~$

====================================
wruslan@HP-EliteBook-8470p-Ub1804:~$ ls -al /dev/usb
total 0
drwxr-xr-x  2 root root     60 Apr 15 14:10 .
drwxr-xr-x 21 root root   4600 Apr 15 14:10 ..
crw-rw----  1 root lp   180, 0 Apr 15 14:10 lp0
wruslan@HP-EliteBook-8470p-Ub1804:~$

====================================
wruslan@HP-EliteBook-8470p-Ub1804:~$ stat /dev/usb/lp0
  File: /dev/usb/lp0
  Size: 0         	Blocks: 0          IO Block: 4096   character special file
Device: 6h/6d	Inode: 592         Links: 1     Device type: b4,0
Access: (0660/crw-rw----)  Uid: (    0/    root)   Gid: (    7/      lp)
Access: 2020-04-15 14:10:28.496741748 +0800
Modify: 2020-04-15 14:10:28.496741748 +0800
Change: 2020-04-15 14:10:28.496741748 +0800
 Birth: -
wruslan@HP-EliteBook-8470p-Ub1804:~$

=========================================
(2) For USB-to-Parallel cable (KATRON)
=========================================

[31158.633881] usb 1-1.2: New USB device found, idVendor=0fe6, idProduct=811e
[31158.633886] usb 1-1.2: New USB device strings: Mfr=0, Product=2, SerialNumber=0
[31158.633888] usb 1-1.2: Product: IEEE-1284 Controller
[31158.739902] usblp 1-1.2:1.0: usblp0: USB Bidirectional printer dev 62 if 0 alt 0 proto 2 vid 0x0FE6 pid 0x811E
wruslan@HP-EliteBook-8470p-Ub1804:~$

====================================
wruslan@HP-EliteBook-8470p-Ub1804:~$ ls -al /dev | grep usb
drwxr-xr-x   2 root    root          60 Apr 15 19:48 usb
wruslan@HP-EliteBook-8470p-Ub1804:~$ ls -al /dev/usb
total 0
drwxr-xr-x  2 root root     60 Apr 15 19:48 .
drwxr-xr-x 21 root root   4600 Apr 15 19:48 ..
crw-rw----  1 root lp   180, 0 Apr 15 19:48 lp0
wruslan@HP-EliteBook-8470p-Ub1804:~$

===================================
wruslan@HP-EliteBook-8470p-Ub1804:~$ stat /dev/usb/lp0
  File: /dev/usb/lp0
  Size: 0         	Blocks: 0          IO Block: 4096   character special file
Device: 6h/6d	Inode: 592         Links: 1     Device type: b4,0
Access: (0660/crw-rw----)  Uid: (    0/    root)   Gid: (    7/      lp)
Access: 2020-04-15 19:48:01.987343911 +0800
Modify: 2020-04-15 19:48:01.987343911 +0800
Change: 2020-04-15 19:48:01.987343911 +0800
 Birth: -
wruslan@HP-EliteBook-8470p-Ub1804:~$


*/
// ========================================================
// C-PROGRAM HEADER FILES
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <sched.h>
#include <signal.h>    // Signal for User interrupt Ctrl-C to stop
#include <math.h>
#include <errno.h>
#include <string.h>	   // TO HANDLE strlen IN gcode . h
#include <curses.h>	   // TO HANDLE getch () , wgetch ()
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/io.h>
#include <sys/mman.h>

// WRY Date-Time stamp nanosecond display
#include "common/c_dtstamp.h"

// ========================================================
// GLOBAL DEFINITIONS

	// DEVICE: For-Cable-USB-to-Parallel-PL2305.
	#define DEVICE_USB_TO_PAR	"/dev/usb/lp0"

	// BINARY REPRESENTATION FOR PRINTING (DISPLAY) TO SCREEN
	char bin8_output[33] = {0};	// LAST CHAR IS NULL "\0"

// ========================================================
void convert_integer_to_binary8(int input_int, char *output_bin8) {
// ========================================================
    unsigned int mask8;
    mask8  = 0b10000000;

    int bitposition = 0;
    while (mask8)  {         		// Loop until MASK is empty
		bitposition++;

		if (input_int & mask8) {     	// Bitwise AND => test the masked bit
				*output_bin8 = '1';     // if true, binary value 1 is appended to output array
		} else {
				*output_bin8 = '0';     // if false, binary value 0 is appended to output array
		}

		output_bin8++;              // next character
        mask8 >>= 1;                // shift the mask variable 1 bit to the right
    } // End while..

    *output_bin8 = 0;               // add the trailing null
}

// ========================================================
void test_writeusb_to_parport(void) {
// ========================================================
DTStamp(); printf("STARTED  test_writeusb_to_parport(void).\n");

// Open usb_parport for both read and write
int fd_usb_parport = open(DEVICE_USB_TO_PAR, O_WRONLY | O_RDONLY | O_NOCTTY | O_NDELAY);
if (fd_usb_parport < 0) {
	DTStamp(); printf("ERROR:   open DEVICE_USB_TO_PAR = /dev/usb/lp0/ return fd_usb_parport = %d \n", fd_usb_parport);
	DTStamp(); printf("ERROR:   Must run as root with $ sudo ./XXX \n");
	perror("fd_usb_parport");
	exit(1);
} else {
	DTStamp(); printf("SUCCESS: open DEVICE_USB_TO_PAR = /dev/usb/lp0/ return fd_usb_parport = %d \n", fd_usb_parport);
}

	// TEST EXECUTE DEVICE write() ELECTRICAL PULSES TO PARALLEL PORT (char, short and long) data types
	unsigned char data_uchar;
	data_uchar = 'R';
	if (fd_usb_parport != -1) {
		write(fd_usb_parport, (const void *)(long)data_uchar, 1);
		DTStamp(); printf("SUCCESS: write(fd_usb_parport, (const void *)data_uchar, 1) = %c\n", data_uchar);
	} else {
		DTStamp(); printf("FAILED:  write(fd_usb_parport, (const void *)data_uchar, 1) = %c\n", data_uchar);
	}

	short data_short;
	data_short= 165;
	if (fd_usb_parport != -1) {
		write(fd_usb_parport, (const void *)(long)data_short, 1);
		DTStamp(); printf("SUCCESS: write(fd_usb_parport, (const void *)data_short, 1) = %d\n", data_short);
	} else {
		DTStamp(); printf("FAILED:  write(fd_usb_parport, (const void *)data_short, 1) = %d\n", data_short);
	}

	long data_long;
	data_long = 66577789;
	if (fd_usb_parport != -1) {
		write(fd_usb_parport, (const void *)data_long, 1);
		DTStamp(); printf("SUCCESS: write(fd_usb_parport, (const void *)data_long,  1) = %ld\n", data_long);
	} else {
		DTStamp(); printf("FAILED:  write(fd_usb_parport, (const void *)data_long,  1) = %ld\n", data_long);
	}

	// Test write loop with buffered data
	// PERFORM WRITE LOOP FOR ELECTRICAL PULSE OUTPUTS
	int i;
	int intToWrite = 0;
	char TheChar[] = "Bismillah WRY and Alhamdulillah WRY!";
	int str_length = strlen(TheChar);

	for (i = 0; i < str_length; i++) {

		// GRAB INTEGER TO WRITE (8-BITS) TO DEVICE
		intToWrite = TheChar[i];
		if (fd_usb_parport != -1) {
			convert_integer_to_binary8(intToWrite, bin8_output);
			write(fd_usb_parport, (const void *)(long)TheChar[i], 1);
			DTStamp();
			printf("SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = %d \tchar= %c bin= %s hex= 0x%x int= %d \n", i, intToWrite, bin8_output, intToWrite, intToWrite);
		} else {
			DTStamp();
			printf("FAILED:  write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = %d \tchar= %c bin= %s hex= 0x%x int= %d \n", i, intToWrite, bin8_output, intToWrite, intToWrite);
		}
	} // End for..loop


// Close usb_parport
if (fd_usb_parport >= 0) {
	close(fd_usb_parport);
}

DTStamp(); printf("FINISHED test_writeusb_to_parport(void).\n");
}
// ========================================================
/*
wruslan@HP-EliteBook-8470p-Ub1804:~/apps/cpp-eclipse-wks/usb-to-parallel-port/Debug$ sudo ./usb-to-parallel-port
2020-04-15 17:20:35.553079232 	Starting in main(), Bismillah 3 times WRY.
2020-04-15 17:20:35.553113644 	Program started.

=============================================================
2020-04-15 17:20:35.553134018 	Timer 1 start.
2020-04-15 17:20:35.553151144 	CHECK 1: Check environment, date, time and clock.
2020-04-15 17:20:35.553204631 	Current date and time: Wed Apr 15, 2020 17:20:35
2020-04-15 17:20:35.553223357 	Current directory: /home/wruslan/apps/cpp-eclipse-wks/usb-to-parallel-port/Debug
2020-04-15 17:20:35.553237035 	Current runfile  : ./usb-to-parallel-port
2020-04-15 17:20:35.553264870 	Clock time resolution 	= 1 nanoseconds
2020-04-15 17:20:35.553270084 	Timer 1 stop. Duration (timer start-to-stop) = 0.000140646 seconds.

=============================================================
2020-04-15 17:20:35.553282722 	Timer 2 start.
2020-04-15 17:20:35.553290825 	EXECUTE: Write via usb to parallel port using PL2305 chip on cable
2020-04-15 17:20:35.553299061 	STARTED  test_writeusb_to_parport(void).
2020-04-15 17:20:35.553331400 	SUCCESS: open DEVICE_USB_TO_PAR = /dev/usb/lp0/ return fd_usb_parport = 3
2020-04-15 17:20:35.553373061 	SUCCESS: write(fd_usb_parport, (const void *)data_uchar, 1) = R
2020-04-15 17:20:35.553408759 	SUCCESS: write(fd_usb_parport, (const void *)data_short, 1) = 165
2020-04-15 17:20:35.553418382 	SUCCESS: write(fd_usb_parport, (const void *)data_long,  1) = 66577789
2020-04-15 17:20:35.553427937 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 0 	char= B bin= 01000010 hex= 0x42 int= 66
2020-04-15 17:20:35.553438343 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 1 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-15 17:20:35.553446091 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 2 	char= s bin= 01110011 hex= 0x73 int= 115
2020-04-15 17:20:35.553453454 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 3 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-15 17:20:35.553460819 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 4 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-15 17:20:35.553468392 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 5 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-15 17:20:35.553475953 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 6 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-15 17:20:35.553483394 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 7 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-15 17:20:35.553490855 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 8 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-15 17:20:35.553499829 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 9 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-15 17:20:35.553507702 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 10 	char= W bin= 01010111 hex= 0x57 int= 87
2020-04-15 17:20:35.553515137 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 11 	char= R bin= 01010010 hex= 0x52 int= 82
2020-04-15 17:20:35.553522606 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 12 	char= Y bin= 01011001 hex= 0x59 int= 89
2020-04-15 17:20:35.553529984 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 13 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-15 17:20:35.553537395 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 14 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-15 17:20:35.553544838 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 15 	char= n bin= 01101110 hex= 0x6e int= 110
2020-04-15 17:20:35.553552261 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 16 	char= d bin= 01100100 hex= 0x64 int= 100
2020-04-15 17:20:35.553559632 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 17 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-15 17:20:35.553567088 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 18 	char= A bin= 01000001 hex= 0x41 int= 65
2020-04-15 17:20:35.553574457 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 19 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-15 17:20:35.553581873 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 20 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-15 17:20:35.553589309 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 21 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-15 17:20:35.553596710 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 22 	char= m bin= 01101101 hex= 0x6d int= 109
2020-04-15 17:20:35.553604075 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 23 	char= d bin= 01100100 hex= 0x64 int= 100
2020-04-15 17:20:35.553611538 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 24 	char= u bin= 01110101 hex= 0x75 int= 117
2020-04-15 17:20:35.553618902 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 25 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-15 17:20:35.553626266 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 26 	char= i bin= 01101001 hex= 0x69 int= 105
2020-04-15 17:20:35.553633725 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 27 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-15 17:20:35.553641086 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 28 	char= l bin= 01101100 hex= 0x6c int= 108
2020-04-15 17:20:35.553648455 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 29 	char= a bin= 01100001 hex= 0x61 int= 97
2020-04-15 17:20:35.553655887 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 30 	char= h bin= 01101000 hex= 0x68 int= 104
2020-04-15 17:20:35.553663297 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 31 	char=   bin= 00100000 hex= 0x20 int= 32
2020-04-15 17:20:35.553670748 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 32 	char= W bin= 01010111 hex= 0x57 int= 87
2020-04-15 17:20:35.553678232 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 33 	char= R bin= 01010010 hex= 0x52 int= 82
2020-04-15 17:20:35.553685603 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 34 	char= Y bin= 01011001 hex= 0x59 int= 89
2020-04-15 17:20:35.553693041 	SUCCESS: write(fd_usb_parport, (const void *)(long)TheChar[i],  1) i = 35 	char= ! bin= 00100001 hex= 0x21 int= 33
2020-04-15 17:20:35.556972969 	FINISHED test_writeusb_to_parport(void).
2020-04-15 17:20:35.556982628 	Timer 2 stop. Duration (timer start-to-stop) = 0.003700299 seconds.

2020-04-15 17:20:35.556995158 	Total program run duration   = 0.004025134 seconds.

2020-04-15 17:20:35.557006488 	Program ended.
2020-04-15 17:20:35.557014540 	Ending in main(), Alhamdulillah 3 times WRY.
wruslan@HP-EliteBook-8470p-Ub1804:~/apps/cpp-eclipse-wks/usb-to-parallel-port/Debug$

*/
// ========================================================
/*
[ 9764.184593] usb 1-1.2: new full-speed USB device number 17 using ehci-pci
[ 9764.222686] usb 1-1.2: New USB device found, idVendor=067b, idProduct=2305
[ 9764.222691] usb 1-1.2: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[ 9764.222693] usb 1-1.2: Product: IEEE-1284 Controller
[ 9764.222696] usb 1-1.2: Manufacturer: Prolific Technology Inc.
[ 9764.224047] usblp 1-1.2:1.0: usblp0: USB Bidirectional printer dev 17 if 0 alt 1 proto 2 vid 0x067B pid 0x2305
[10002.864782] traps: parallel-port-0[9298] general protection ip:400a09 sp:7ffc064aaf80 error:0 in parallel-port-01[400000+3000]
wruslan@HP-EliteBook-8470p-Ub1804:~$

wruslan@HP-EliteBook-8470p-Ub1804:~$ ls -al /dev/usb
total 0
drwxr-xr-x  2 root root     60 Apr 15 14:03 .
drwxr-xr-x 21 root root   4600 Apr 15 14:03 ..
crw-rw----  1 root lp   180, 0 Apr 15 14:03 lp0
wruslan@HP-EliteBook-8470p-Ub1804:~$

// ========================================================
Bus 001 Device 017: ID 067b:2305 Prolific Technology, Inc. PL2305 Parallel Port
Device Descriptor:
  bLength                18
  bDescriptorType         1
  bcdUSB               1.00
  bDeviceClass            0 (Defined at Interface level)
  bDeviceSubClass         0
  bDeviceProtocol         0
  bMaxPacketSize0         8
  idVendor           0x067b Prolific Technology, Inc.
  idProduct          0x2305 PL2305 Parallel
  bcdDevice            2.02
  iManufacturer           1 (error)
  iProduct                2 (error)
  iSerial                 0
  bNumConfigurations      1
  Configuration Descriptor:
    bLength                 9
    bDescriptorType         2
    wTotalLength           78
    bNumInterfaces          1
    bConfigurationValue     1
    iConfiguration          0
    bmAttributes         0x80
      (Bus Powered)
    MaxPower              100mA
    Interface Descriptor:
      bLength                 9
      bDescriptorType         4
      bInterfaceNumber        0
      bAlternateSetting       0
      bNumEndpoints           1
      bInterfaceClass         7 Printer
      bInterfaceSubClass      1 Printer
      bInterfaceProtocol      1 Unidirectional
      iInterface              0
      Endpoint Descriptor:
        bLength                 7
        bDescriptorType         5
        bEndpointAddress     0x01  EP 1 OUT
        bmAttributes            2
          Transfer Type            Bulk
          Synch Type               None
          Usage Type               Data
        wMaxPacketSize     0x0040  1x 64 bytes
        bInterval               0
    Interface Descriptor:
      bLength                 9
      bDescriptorType         4
      bInterfaceNumber        0
      bAlternateSetting       1
      bNumEndpoints           2
      bInterfaceClass         7 Printer
      bInterfaceSubClass      1 Printer
      bInterfaceProtocol      2 Bidirectional
      iInterface              0
      Endpoint Descriptor:
        bLength                 7
        bDescriptorType         5
        bEndpointAddress     0x01  EP 1 OUT
        bmAttributes            2
          Transfer Type            Bulk
          Synch Type               None
          Usage Type               Data
        wMaxPacketSize     0x0040  1x 64 bytes
        bInterval               0
      Endpoint Descriptor:
        bLength                 7
        bDescriptorType         5
        bEndpointAddress     0x82  EP 2 IN
        bmAttributes            2
          Transfer Type            Bulk
          Synch Type               None
          Usage Type               Data
        wMaxPacketSize     0x0040  1x 64 bytes
        bInterval               0
    Interface Descriptor:
      bLength                 9
      bDescriptorType         4
      bInterfaceNumber        0
      bAlternateSetting       2
      bNumEndpoints           3
      bInterfaceClass       255 Vendor Specific Class
      bInterfaceSubClass      0
      bInterfaceProtocol    255
      iInterface              0
      Endpoint Descriptor:
        bLength                 7
        bDescriptorType         5
        bEndpointAddress     0x01  EP 1 OUT
        bmAttributes            2
          Transfer Type            Bulk
          Synch Type               None
          Usage Type               Data
        wMaxPacketSize     0x0040  1x 64 bytes
        bInterval               0
      Endpoint Descriptor:
        bLength                 7
        bDescriptorType         5
        bEndpointAddress     0x82  EP 2 IN
        bmAttributes            2
          Transfer Type            Bulk
          Synch Type               None
          Usage Type               Data
        wMaxPacketSize     0x0040  1x 64 bytes
        bInterval               0
      Endpoint Descriptor:
        bLength                 7
        bDescriptorType         5
        bEndpointAddress     0x83  EP 3 IN
        bmAttributes            3
          Transfer Type            Interrupt
          Synch Type               None
          Usage Type               Data
        wMaxPacketSize     0x0004  1x 4 bytes
        bInterval               1
Device Status:     0xd5f0
  (Bus Powered)
  Debug Mode

*/
// ========================================================
