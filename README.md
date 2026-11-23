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

