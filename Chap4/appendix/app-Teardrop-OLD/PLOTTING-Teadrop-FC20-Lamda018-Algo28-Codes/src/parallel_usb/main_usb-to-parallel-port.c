//============================================================================
// Name        : main_usb-to-parallel-port.c
// Author      : wruslan
// Version     :
// Copyright   : Busmillah Hirrahma Nirrahim
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
REFERENCE: https://www.howtoforge.com/tutorial/accessing-parallel-ports-on-linux/

Accessing Physical Ports on Linux

Because the port hardware on a PC is controlled directly by the Linux kernel,
we must access certain headers related to the parallel port bus. The GCC compiler
can access these headers, always bearing in mind that the user must have root
privileges to avoid access errors. These headers are:

(1) stdio.h: The "standard input-output header" (standard header I/O) is the
header file that contains the macro definitions, constants, function declarations
in the standard library of the C programming language to perform operations,
standard input and output, as well as the definition of types necessary for such
operations. For compatibility reasons, the programming language C ++ (C derivative)
also has its own implementation of these functions, which are declared with
<cstdio> file header. The function I have to use is fprintf which allows to print
on a terminal window if there is any error.

(2) stdlib.h: Is the header file for the standard library of the general-purpose
programming language C. It contains the C function prototypes for dynamic memory
management, process control and other. It supports C ++ where it is known as
<cstdlib>. The function I will use is exit when we get an error.

(3) unistd.h:  Header file that provides access to the POSIX operating system API.
On Unix-like systems, the interface defined by unistd.h is typically made up largely
of system call wrapper functions such as fork, pipe and I/O primitives (read, write,
close, etc.).

(4) sys/io.h: This family of functions is used to do low-level port input and output.
The out* functions do port output, the in* functions do port input; the b-suffix functions
are byte-width and the w-suffix functions word-width; the _p-suffix functions pause
until the I/O completes. Of this family function I will use outb.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

// WRY Date-Time stamp nanosecond display
#include "common/c_dtstamp.h"

// WRY parallel port codes
#include "parallel_usb/usb_parallel_port.h"

// ========================================================
int main(int argc, char* argv[]){
// ========================================================
WRY_starting_salutation();

	printf("=============================================================\n");
	start_timer(1);
	DTStamp();
	printf("CHECK 1: Check environment, date, time and clock.\n");
	display_date_only();
	current_working_directory();
	DTStamp(); printf("Current runfile  : %s \n", argv[0]);
	display_resolution_date_time();
	stop_timer(1);

	printf("=============================================================\n");
	start_timer(2);
	DTStamp();
	printf("EXECUTE: Write via usb to parallel port using PL2305 chip on cable\n");
	test_writeusb_to_parport();
	stop_timer(2);

total_program_duration();
WRY_ending_salutation();
return (0);
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
