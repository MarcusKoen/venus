# /proc VFS

Apparently linux mounts a Virtual File System (VFS) under /proc/ with 
numerical Process Identifiers (PIDs) as directories. Quite based.
Need to have appropriate permissions to access PIDs and consequently
process names, since only child objects of parent can access. The work-
around is running venus with sudo.

1. Iterate through /proc/ and display list of PIDs
2. Select a PID from list
3. Read the PID name under /proc/<pid>/cmdline or /proc/<pid>/comm
	I will stick with comm
4. Map target's virtual address space
	Parse /proc/<pid>/maps
Sample layout

```
➜  ~ cat /proc/342309/maps      
559f9fecf000-559f9fed0000 r--p 00000000 fe:01 28968082                   /home/marcus/Documents/RE/venus/venus/t
559f9fed0000-559f9fed1000 r-xp 00001000 fe:01 28968082                   /home/marcus/Documents/RE/venus/venus/t
559f9fed1000-559f9fed2000 r--p 00002000 fe:01 28968082                   /home/marcus/Documents/RE/venus/venus/t
559f9fed2000-559f9fed3000 r--p 00002000 fe:01 28968082                   /home/marcus/Documents/RE/venus/venus/t
559f9fed3000-559f9fed4000 rw-p 00003000 fe:01 28968082                   /home/marcus/Documents/RE/venus/venus/t
559fdf34f000-559fdf370000 rw-p 00000000 00:00 0                          [heap]
7f9012b1c000-7f9012b2d000 r--p 00000000 fe:01 52177057                   /usr/lib/x86_64-linux-gnu/libm.so.6
7f9012b2d000-7f9012baa000 r-xp 00011000 fe:01 52177057                   /usr/lib/x86_64-linux-gnu/libm.so.6
7f9012baa000-7f9012c0a000 r--p 0008e000 fe:01 52177057                   /usr/lib/x86_64-linux-gnu/libm.so.6
7f9012c0a000-7f9012c0b000 r--p 000ed000 fe:01 52177057                   /usr/lib/x86_64-linux-gnu/libm.so.6
7f9012c0b000-7f9012c0c000 rw-p 000ee000 fe:01 52177057                   /usr/lib/x86_64-linux-gnu/libm.so.6
7f9012c0c000-7f9012c34000 r--p 00000000 fe:01 52177054                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f9012c34000-7f9012d97000 r-xp 00028000 fe:01 52177054                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f9012d97000-7f9012ded000 r--p 0018b000 fe:01 52177054                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f9012ded000-7f9012df1000 r--p 001e0000 fe:01 52177054                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f9012df1000-7f9012df3000 rw-p 001e4000 fe:01 52177054                   /usr/lib/x86_64-linux-gnu/libc.so.6
7f9012df3000-7f9012e00000 rw-p 00000000 00:00 0 
7f9012e00000-7f9012e9d000 r--p 00000000 fe:01 52167024                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
7f9012e9d000-7f9012fc6000 r-xp 0009d000 fe:01 52167024                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
7f9012fc6000-7f9013054000 r--p 001c6000 fe:01 52167024                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
7f9013054000-7f901305f000 r--p 00254000 fe:01 52167024                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
7f901305f000-7f9013062000 rw-p 0025f000 fe:01 52167024                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.33
7f9013062000-7f9013066000 rw-p 00000000 00:00 0 
7f90130d2000-7f90130d7000 rw-p 00000000 00:00 0 
7f90130d7000-7f90130db000 r--p 00000000 fe:01 52166661                   /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7f90130db000-7f90130fe000 r-xp 00004000 fe:01 52166661                   /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7f90130fe000-7f9013102000 r--p 00027000 fe:01 52166661                   /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7f9013102000-7f9013103000 r--p 0002b000 fe:01 52166661                   /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7f9013103000-7f9013104000 rw-p 0002c000 fe:01 52166661                   /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7f901311f000-7f9013121000 rw-p 00000000 00:00 0 
7f9013121000-7f9013125000 r--p 00000000 00:00 0                          [vvar]
7f9013125000-7f9013127000 r-xp 00000000 00:00 0                          [vdso]
7f9013127000-7f9013128000 r--p 00000000 fe:01 52177051                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f9013128000-7f9013150000 r-xp 00001000 fe:01 52177051                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f9013150000-7f901315b000 r--p 00029000 fe:01 52177051                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f901315b000-7f901315d000 r--p 00034000 fe:01 52177051                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f901315d000-7f901315e000 rw-p 00036000 fe:01 52177051                   /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7f901315e000-7f901315f000 rw-p 00000000 00:00 0 
7fff9b577000-7fff9b598000 rw-p 00000000 00:00 0                          [stack]

```
# Detour: Memory 

I just had an idea
	Only look at sections that has rwXX
Another idea
How do I actually inspect the eranges listed by /map?

Ended up reading 
https://man7.org/tlpi/
https://man7.org/linux/man-pages/man2/process_vm_readv.2.html#SEE_ALSO

7fff9b577000-7fff9b598000 rw-p 00000000 00:00 0 
End-Start = whole number = 0x1000 pages = 4096 bytes = 4kB
Rewrite
	Each region is 0x1000 = 4kB = 4096 bytes
Breakind this down
```
7fff9b577000
```
12 hex characters
	12 * 4 = 48 BIT memory
This is also called canonical memory

https://simonis.github.io/Memory/

This might become an issue

TODO :

Address Space Layout Randomization (ASLR) 


This address

```
559f9fed3000-559f9fed4000 rw-p 00003000 fe:01 28968082                   /home/marcus/Documents/RE/venus/venus/t
```
most likely contains the global variable I need to change.
We know this is 4096 bytes = 4kB
Before I ask how to iterate through
WTF does one of these addresses contain
e.g.
```
559f9fed3000
```
https://unix.stackexchange.com/questions/489297/how-to-get-value-of-a-memory-address-using-command

There are other ways of doing this

1. GDB
2. Current proc/map proc/mem
3. Kernal level
ALSO TODO explain base, offset


//dd bs=1 skip="$((0x556d62906000))" count=4 if="/proc/$pid/mem" |od -An -vtu4
    //gdb --batch -ex 'x/u 0x7fffffffeb58' -p "$pid"
I know this displays 32 bit unsigned int but its garbage to me
2152878208

Again to reiterate
there are 1000 pages, each 4096 bytes

But will the current method work for floating point as well?

