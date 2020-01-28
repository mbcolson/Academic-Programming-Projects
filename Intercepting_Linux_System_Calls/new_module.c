#include <linux/init.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/system.h>
#include <linux/slab.h>
#include <linux/socket.h>
#include <linux/in.h>
#include <net/sock.h>
#include <linux/file.h>
#include <linux/net.h>
#include <linux/rtc.h>

MODULE_LICENSE("GPL");

#define FILE_LOG_PATH "/home/mbcolson/Desktop/output/file/"
#define NETWORK_LOG_PATH "/home/mbcolson/Desktop/output/network/"

char USER_TIME[11]="###:##:###";
char log_filename[11]="##_##_####";

unsigned long *syscall_table = (unsigned long *) 0xffffffff81600300;

asmlinkage int (*original_write)(unsigned int, const char __user *, size_t);
asmlinkage size_t (*original_read)(int, char *, size_t);
asmlinkage int (*original_close)(unsigned int);
asmlinkage int (*original_open)(const char __user *, int, int);
asmlinkage int (*original_getsockname)(int,struct sockaddr __user *,int *);
asmlinkage int (*original_getpeername)(int,struct sockaddr __user *,int *);
asmlinkage long (*original_connect)(int, struct sockaddr __user *, int);
asmlinkage long (*original_accept)(int, struct sockaddr __user *, int __user *);
asmlinkage long (*original_sendto)(int, void __user *, size_t, unsigned,
                                   struct sockaddr __user *, int);
asmlinkage long (*original_recvfrom)(int, void __user *, size_t, unsigned,
                                     struct sockaddr __user *, int __user *);

void print_time(char char_time[]);
void write_file(char *,char *);
char *inet_ntoa(struct in_addr inn);
short unsigned int my_ntoh(short unsigned int src_port);

void get_exe_path(char **exe_path) {
    struct mm_struct *mm;
    mm = current->mm;

    if(mm) {
        down_read(&mm->mmap_sem);
        if(mm->exe_file) {
            char *pathname = kmalloc(PATH_MAX, GFP_ATOMIC);
 
            if(pathname) {
                *exe_path = d_path(&mm->exe_file->f_path, pathname, PATH_MAX);
                kfree(pathname);
            } else {
                printk("Error in get_exe_path, kmalloc error on pathname\n");
            }
        }
        up_read(&mm->mmap_sem);
    }
}

asmlinkage size_t new_write(int fd, char __user *buf, size_t count)
{
    char fileinfo_buff[300], path[120], pid_buff[12], cnt_buffer[12], fd_buff[4];
    char *exe_path = "";

    print_time(USER_TIME);
    strcpy(fileinfo_buff, USER_TIME + 1);

    snprintf(pid_buff, 12, "%u", current->pid);
    snprintf(cnt_buffer, 12, "%zu", count);
    snprintf(fd_buff, 4, "%d", fd);
   
    strcat(fileinfo_buff, "write intercepted");
    strcat(fileinfo_buff, "#pid=");
    strcat(fileinfo_buff, pid_buff);
    strcat(fileinfo_buff, "#");
    strcat(fileinfo_buff, cnt_buffer);
    strcat(fileinfo_buff, " bytes written");
    strcat(fileinfo_buff, "#fd=");
    strcat(fileinfo_buff, fd_buff);

    get_exe_path(&exe_path);

    strcat(fileinfo_buff, "#proc=");
    strcat(fileinfo_buff, exe_path);
    strcat(fileinfo_buff, "\n");

    strcpy(path, FILE_LOG_PATH);
    strncat(path, log_filename, 11);

    write_file(fileinfo_buff, path);
    
    return original_write(fd, buf, count);
}

asmlinkage size_t new_read(int fd, char __user *buf, size_t count)
{
    char fileinfo_buff[300], path[120], pid_buff[12], cnt_buffer[12], fd_buff[4];
    char *exe_path = "";

    print_time(USER_TIME);
    strcpy(fileinfo_buff, USER_TIME + 1);

    snprintf(pid_buff, 12, "%u", current->pid);
    snprintf(cnt_buffer, 12, "%zu", count);
    snprintf(fd_buff, 4, "%d", fd);

    strcat(fileinfo_buff, "read intercepted");
    strcat(fileinfo_buff, "#pid=");
    strcat(fileinfo_buff, pid_buff);
    strcat(fileinfo_buff, "#");
    strcat(fileinfo_buff, cnt_buffer);
    strcat(fileinfo_buff, " bytes read");
    strcat(fileinfo_buff, "#fd=");
    strcat(fileinfo_buff, fd_buff);
    
    get_exe_path(&exe_path);

    strcat(fileinfo_buff, "#proc=");
    strcat(fileinfo_buff, exe_path);
    strcat(fileinfo_buff, "\n");

    strcpy(path, FILE_LOG_PATH);
    strncat(path, log_filename, 11);

    write_file(fileinfo_buff, path);

    return original_read(fd, buf, count);
}

asmlinkage long new_connect(int fd, struct sockaddr __user *buff1, int flag)
{ 
    int ret1, ret2, socklen;
    struct sockaddr_in getsock, getpeer;
    char netinfo_buff[300], path[120], buff[100], *exe_path = "";
    mm_segment_t old_fs;

    socklen = sizeof(getsock);
 
    old_fs=get_fs();
    set_fs(KERNEL_DS);

    ret1 = original_getsockname(fd, (struct sockaddr *)&getsock, &socklen);

    ret2 = original_getpeername(fd, (struct sockaddr *)&getpeer, &socklen);

    set_fs(old_fs);

    printk("\nret1 is %d, ret2 is %d\n", ret1, ret2);

    if(getsock.sin_family == AF_INET)
    {
        print_time(USER_TIME);
        strcpy(netinfo_buff, USER_TIME + 1);

	snprintf(buff, 9, "%s", "CONNECT");
        strcat(netinfo_buff, buff);
        snprintf(buff, 18, "#%s", inet_ntoa(getsock.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff, 10, "#%u", my_ntoh(getsock.sin_port));
        strcat(netinfo_buff, buff);
	snprintf(buff, 18, "#%s", inet_ntoa(getpeer.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff, 10, "#%u", my_ntoh(getpeer.sin_port));
        strcat(netinfo_buff, buff);

        get_exe_path(&exe_path);

        strcat(netinfo_buff, "#proc=");
        strcat(netinfo_buff, exe_path);
        strcat(netinfo_buff, "\n"); 
 
	strcpy(path, NETWORK_LOG_PATH);
        strncat(path,log_filename, 11);

	write_file(netinfo_buff, path);
    }

    return original_connect(fd, buff1, flag);
}

asmlinkage long new_accept(int fd, struct sockaddr __user *buff1, int __user *buff2)
{
    int ret1, ret2, socklen;
    struct sockaddr_in getsock, getpeer;
    char netinfo_buff[300], path[120], buff[100], *exe_path = "";
    mm_segment_t old_fs;

    socklen = sizeof(getsock);

    old_fs=get_fs();
    set_fs(KERNEL_DS);

    ret1 = original_getsockname(fd, (struct sockaddr *)&getsock, &socklen);

    ret2 = original_getpeername(fd, (struct sockaddr *)&getpeer, &socklen);

    set_fs(old_fs);

    printk("\nret1 is %d, ret2 is %d\n", ret1, ret2);

    if(getsock.sin_family == AF_INET)
    {
        print_time(USER_TIME);
        strcpy(netinfo_buff, USER_TIME + 1);

        snprintf(buff, 8, "%s", "ACCEPT");
        strcat(netinfo_buff, buff);
        snprintf(buff, 18, "#%s", inet_ntoa(getsock.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff, 10, "#%u", my_ntoh(getsock.sin_port));
        strcat(netinfo_buff, buff);
        snprintf(buff, 18, "#%s", inet_ntoa(getpeer.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff, 10, "#%u", my_ntoh(getpeer.sin_port));
        strcat(netinfo_buff, buff);
 
        get_exe_path(&exe_path);
 
        strcat(netinfo_buff, "#proc=");
        strcat(netinfo_buff, exe_path);
        strcat(netinfo_buff, "\n"); 
 
	strcpy(path, NETWORK_LOG_PATH);
        strncat(path,log_filename, 11);

	write_file(netinfo_buff, path);
    }
 
    return original_accept(fd, buff1, buff2);
}

asmlinkage long new_sendto(int fd, void __user *buff1, size_t len, unsigned flags,
                           struct sockaddr __user *addr, int addr_len)
{
    int ret1, ret2, socklen;
    struct sockaddr_in getsock, getpeer;
    char netinfo_buff[300], path[120], buff[100], *exe_path = "";
    mm_segment_t old_fs;

    socklen = sizeof(getsock);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    ret1 = original_getsockname(fd, (struct sockaddr *)&getsock, &socklen);

    ret2 = original_getpeername(fd, (struct sockaddr *)&getpeer, &socklen);

    set_fs(old_fs);
    printk("\nret1 is %d, ret2 is %d\n", ret1, ret2);

    if(getsock.sin_family == AF_INET)
    {
        print_time(USER_TIME);
        strcpy(netinfo_buff, USER_TIME + 1);

        snprintf(buff, 8, "%s", "SEND");
        strcat(netinfo_buff, buff);
        snprintf(buff, 18, "#%s", inet_ntoa(getsock.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff,10, "#%u", my_ntoh(getsock.sin_port));
        strcat(netinfo_buff, buff);
	snprintf(buff, 18, "#%s", inet_ntoa(getpeer.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff, 10, "#%u", my_ntoh(getpeer.sin_port));
        strcat(netinfo_buff, buff);
 
        get_exe_path(&exe_path);

        strcat(netinfo_buff, "#proc=");
        strcat(netinfo_buff, exe_path);
        strcat(netinfo_buff, "\n");
 
    	strcpy(path, NETWORK_LOG_PATH);
	strncat(path, log_filename, 11);

	write_file(netinfo_buff, path);
    }
 
    return original_sendto(fd, buff1, len, flags, addr, addr_len);
}

asmlinkage long new_recvfrom(int fd, void __user *buff1, size_t len, unsigned flags,
                             struct sockaddr __user *ar, int __user *buff2)
{
    int ret1, ret2, socklen;
    struct sockaddr_in getsock, getpeer;
    char netinfo_buff[300], path[120], buff[100], *exe_path = "";
    mm_segment_t old_fs;

    socklen = sizeof(getsock);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    ret1 = original_getsockname(fd, (struct sockaddr *)&getsock, &socklen);

    ret2 = original_getpeername(fd, (struct sockaddr *)&getpeer, &socklen);

    set_fs(old_fs);

    printk("\nret1 is %d, ret2 is %d\n", ret1, ret2);

    if(getsock.sin_family == AF_INET)
    {
        print_time(USER_TIME);
        strcpy(netinfo_buff, USER_TIME + 1);

        snprintf(buff, 9, "%s", "RECEIVE");
        strcat(netinfo_buff, buff);
        snprintf(buff, 18, "#%s", inet_ntoa(getsock.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff, 10, "#%u", my_ntoh(getsock.sin_port));
        strcat(netinfo_buff, buff);
	snprintf(buff, 18, "#%s", inet_ntoa(getpeer.sin_addr));
        strcat(netinfo_buff, buff);
        snprintf(buff, 10, "#%u", my_ntoh(getpeer.sin_port));
        strcat(netinfo_buff, buff);
 
        get_exe_path(&exe_path);
 
        strcat(netinfo_buff, "#proc=");
        strcat(netinfo_buff, exe_path);
        strcat(netinfo_buff, "\n");
 
	strcpy(path, NETWORK_LOG_PATH);
        strncat(path, log_filename, 11);

	write_file(netinfo_buff, path);
    }
 
    return (*original_recvfrom)(fd, buff1, len, flags, ar, buff2);
}

asmlinkage int new_open(const char __user *filename, int flags, int mode)
{
    char fileinfo_buff[300], path[120], pid_buf[12], *exe_path = "";

    print_time(USER_TIME);
    strcpy(fileinfo_buff, USER_TIME + 1);

    if(flags & (O_WRONLY|O_APPEND)) {
        strcat(fileinfo_buff,"WR#");
    } else {
        strcat(fileinfo_buff,"RD#");
    }
                       
    strcat(fileinfo_buff, filename);
    snprintf(pid_buf, 12, "%u", current->pid);
    strcat(fileinfo_buff, "#pid=");
    strcat(fileinfo_buff, pid_buf);
    strcat(fileinfo_buff, "#proc=");
 
    get_exe_path(&exe_path);

    strcat(fileinfo_buff, exe_path);
    strcat(fileinfo_buff, "\n");
    strcpy(path, FILE_LOG_PATH);
    strncat(path, log_filename, 11);
 
    write_file(fileinfo_buff, path);
 
    return (*original_open)(filename, flags, mode);
}

void write_file(char *buffer, char *path)
{
    mm_segment_t old_fs;
    int fd, i, j, len = strlen(path);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    for(i = len - 1, j = 0; j < 10; i--, j++) {
        if((path[i] < '0' || path[i] > '9') && path[i] != '_') {
            set_fs(old_fs);
            return; 
        } 
    }

    fd = original_open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);

    //printk("\nfd = %d, buffer = %s\n", fd, buffer);

    if(fd >= 0) {
        original_write(fd, buffer, strlen(buffer));
        original_close(fd);
    } else {
        printk(KERN_ALERT "\nError in write_file() while opening a file\n");
    }

    set_fs(old_fs);

    return;
}

static int __init new_module_init(void) 
{
    printk("\n*************************Module starting...***************************\n");

    write_cr0(read_cr0() & (~ 0x10000));

    original_write = (void *)syscall_table[__NR_write];
    original_read = (void *)syscall_table[__NR_read];
    original_close = (void *)syscall_table[__NR_close];
    original_open = (void *)syscall_table[__NR_open];
 
    original_getsockname = (void *)syscall_table[__NR_getsockname];
    original_getpeername = (void *)syscall_table[__NR_getpeername];
    original_connect = (void *)syscall_table[__NR_connect];
    original_accept = (void *)syscall_table[__NR_accept];
    original_sendto = (void *)syscall_table[__NR_sendto];
    original_recvfrom = (void *)syscall_table[__NR_recvfrom];

    syscall_table[__NR_open] = (unsigned long)new_open;
    syscall_table[__NR_write] = (unsigned long)new_write;
    syscall_table[__NR_read] = (unsigned long)new_read;
    syscall_table[__NR_sendto] = (unsigned long)new_sendto;
    syscall_table[__NR_recvfrom] = (unsigned long)new_recvfrom;
    syscall_table[__NR_connect] = (unsigned long)new_connect;
    syscall_table[__NR_accept] = (unsigned long)new_accept;

    write_cr0(read_cr0() | 0x10000);

    return 0;
}

static void __exit new_module_exit(void)
{
    write_cr0(read_cr0() & (~ 0x10000));

    syscall_table[__NR_open] = (unsigned long)original_open;
    syscall_table[__NR_write] = (unsigned long)original_write;
    syscall_table[__NR_read] = (unsigned long)original_read;
    syscall_table[__NR_sendto] = (unsigned long)original_sendto;
    syscall_table[__NR_recvfrom] = (unsigned long)original_recvfrom;
    syscall_table[__NR_connect] = (unsigned long)original_connect;
    syscall_table[__NR_accept] = (unsigned long)original_accept;

    write_cr0(read_cr0() | 0x10000);

    printk("**********************Module exiting****************************\n");

    return;
}

short unsigned int my_ntoh(short unsigned int src_port)
{
    short unsigned int t, t1, t2;

    t = (src_port >> 8);
    t1 = (src_port << 8);
    t2 = t | t1;

    return(t2);
}

char *inet_ntoa(struct in_addr inn)
{
    static char m[18];
    register char *m1;

    m1 = (char *)&inn;

    #define UCC(m)	(((int)m)&0xff)

    (void)snprintf(m, sizeof(m), "%u.%u.%u.%u", UCC(m1[0]), UCC(m1[1]), 
                   UCC(m1[2]), UCC(m1[3]));

    return(m);
}

void print_time(char char_time[])
{
    struct timeval my_tv;
    struct rtc_time tm;
    unsigned long local_time;
    int month, day, year;

    do_gettimeofday(&my_tv);
    local_time = (u32)(my_tv.tv_sec - (sys_tz.tz_minuteswest * 60));
    rtc_time_to_tm(local_time, &tm);

    char_time[1] = (tm.tm_hour / 10) + 48;
    char_time[2] = (tm.tm_hour % 10) + 48;
    char_time[4] = (tm.tm_min / 10) + 48;
    char_time[5] = (tm.tm_min % 10) + 48;
    char_time[7] = (tm.tm_sec / 10) + 48;
    char_time[8] = (tm.tm_sec % 10) + 48;
    char_time[10] = '\0';

    month = tm.tm_mon + 1;
    day = tm.tm_mday;
    year = tm.tm_year + 1900;

    log_filename[0] = (month / 10) + 48;
    log_filename[1] = (month % 10) + 48;
    log_filename[3] = (day / 10) + 48;
    log_filename[4] = (day % 10) + 48;
    log_filename[6] = (year / 1000) + 48;
    log_filename[7] = ((year / 100) % 10) + 48;
    log_filename[8] = ((year / 10) % 10) + 48;
    log_filename[9] = (year % 10) + 48;
    log_filename[10] = '\0';
}

module_init(new_module_init);
module_exit(new_module_exit);
