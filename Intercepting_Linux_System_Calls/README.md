# Intercepting Linux System Calls

### Goal
The goal of this project is to learn about how system calls can be intercepted and logged using loadable <br />
kernel modules.

### Background
The Linux kernel's system call table is an array of function pointers to system calls. The system calls can <br />
be overwritten with our own versions of them. This allows us to log the system calls generated by the system <br />
for monitoring and security purposes.

### Setup

**Note**: This program will only work on 64-bit Linux and has only been tested on 64-bit Ubuntu 10.10 <br />
Linux kernel version 2.6.35-22.

1. Run this shell command to get the address of the `'sys_call_table'`:
```shell
# grep sys_call_table /boot/System.map-2.6.35-22-generic
```

2. Change the address assigned to the 'syscall_table' pointer to the address obtained 
in step 1
```C
unsigned long *syscall_table = (unsigned long *) 0xffffffff81600300;
```

3. Create a folder named `'output'` with two subdirectories named `'file'` and `'network'`:

4. Update the `'FILE_LOG_PATH'` and `'NETWORK_LOG_PATH'` macros in new_module.c to your directory paths <br />
created in step 3

5. Build the loadable kernel object and insert it into the kernel
```shell
# make
# sudo insmod new_module.ko
```

6. Files named with the current day's date should be created in the `'file'` and `'network'` folders created <br />
in step 3. These files are where the file and network system calls are logged.

7. Remove the loadable kernel object from the kernel
```shell
# sudo rmmod new_module
```

### Log File Output Format

| System Call |                                    Log File Format                                                        |
|-------------|-----------------------------------------------------------------------------------------------------------|
|**open**     | time stamp # RD (read) or WR (write) # file path # pid # process file path                                |
|**read**     | time stamp # read intercepted # pid # number of bytes read # file descriptor # process file path          |
|**write**    | time stamp # write intercepted # pid # number of bytes written # file descriptor # process file path      |
|**connect**  | time stamp # CONNECT # src IP addr # src port # dest IP addr # dest port # process file path              |
|**accept**   | time stamp # ACCEPT # src IP addr # src port # dest IP addr # dest port # process file path               |
|**sento**    | time stamp # SEND # src IP addr # src port # dest IP addr # dest port # process file path                 |
|**recvfrom** | time stamp # RECEIVE # src IP addr # src port # dest IP addr # dest port # process file path              |
