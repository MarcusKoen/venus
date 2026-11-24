Okay. This is what has happened

1. Run test program
	program has been modified to print memory address
	of the variable I want to change
```
990x7ffce4a55fec
```
	Possible bug I dont know why there is 990

2. Use top to find PID

3. cat /proc/<pid>/maps

4. Confirm that the printed address is within the region that is rw
and in userspace?
	
```
55d4baea2000-55d4baea3000 rw-p 00003000 fe:01 28968129                   /home/marcus/Documents/RE/venus/venus/t

```

PID = 364534

They do not coincide

Either something is wrong with 
1. Pointer vs VFS interaction
2. Misunderstanding the regions, 2 columns I dont know 
3. Possible permissions?

It was 2.

I misunderstood global vs local variables.
Local variables, even when used in int main() is stored on stack
Global would be rw?

rechecking

Stack region
```
7ffce4a37000-7ffce4a58000 rw-p 00000000 00:00 0                          [stack]
```
coincides with 

```
0x7ffce4a55fec

```
Reading that address with 
```
dd bs=1 skip="$((0x556d62906000))" count=4 if="/proc/$pid/mem" |od -An -vtu4

dd bs=1 skip="$((0x7ffce4a55fec))" count=4 if="/proc/364534/mem" |od -An -vtu4

```

Holy poes it coincides, it was on the top of the stack
gives 22?


Wait this is a false victory, I still need to iterate through the entire section

Iterate through ALL regions not just stack
add constant variable to test
run current iteration
only output with if statement translation to 32 bit int

I just realized this is pointless dd command if I cant use it with C++ fns


# References for research
1. man pages
```
proc(5)
lseek(2)
open(2)
read(2)
write(2)
process_vm_readv(2)
pread
```
Apparently use seek, open, read, write i.o std::ifstream/std::ofstream

2. Linux Kernel Documentation
Kernel procfs documentation
```
Documentation/filesystems/proc.rst
```
Linux Virtual Memory/mm documentation
```
Documentation/admin-guide/mm/pagemap.rst and Documentation/mm/):
```
3. Sys Prog Books
The Linux Programming Interface by Michael Kerrisk:
Linux System Programming by Robert Love
4. File discriptors

# File Descriptors
Just an integer, unique to proccess.
Also used for non-files like drivers and sockets.
https://www.youtube.com/watch?v=o9iZucYSkQA

```
man 2 open
```
