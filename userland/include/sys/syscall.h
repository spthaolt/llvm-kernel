/* $NetBSD: syscall.h,v 1.228 2009/07/19 02:54:22 rmind Exp $ */

/*
 * System call numbers.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	NetBSD: syscalls.master,v 1.228 2009/07/19 02:50:44 rmind Exp
 */

#ifndef _SYS_SYSCALL_H_
#define	_SYS_SYSCALL_H_

#define	SYS_MAXSYSARGS	8

/* syscall: "syscall" ret: "int" args: "int" "..." */
#define	SYS_syscall	0

/* syscall: "exit" ret: "void" args: "int" */
#define	SYS_exit	1

/* syscall: "fork" ret: "int" args: */
#define	SYS_fork	2

/* syscall: "read" ret: "ssize_t" args: "int" "void *" "size_t" */
#define	SYS_read	3

/* syscall: "write" ret: "ssize_t" args: "int" "const void *" "size_t" */
#define	SYS_write	4

/* syscall: "open" ret: "int" args: "const char *" "int" "..." */
#define	SYS_open	5

/* syscall: "close" ret: "int" args: "int" */
#define	SYS_close	6

/* syscall: "link" ret: "int" args: "const char *" "const char *" */
#define	SYS_link	9

/* syscall: "unlink" ret: "int" args: "const char *" */
#define	SYS_unlink	10

				/* 11 is obsolete execv */
/* syscall: "chdir" ret: "int" args: "const char *" */
#define	SYS_chdir	12

/* syscall: "fchdir" ret: "int" args: "int" */
#define	SYS_fchdir	13

/* syscall: "chmod" ret: "int" args: "const char *" "mode_t" */
#define	SYS_chmod	15

/* syscall: "chown" ret: "int" args: "const char *" "uid_t" "gid_t" */
#define	SYS_chown	16

/* syscall: "brk" ret: "int" args: "char *" */
#define	SYS_brk	17

/* syscall: "getpid" ret: "pid_t" args: */
#define	SYS_getpid	20

/* syscall: "unmount" ret: "int" args: "const char *" "int" */
#define	SYS_unmount	22

/* syscall: "setuid" ret: "int" args: "uid_t" */
#define	SYS_setuid	23

/* syscall: "getuid" ret: "uid_t" args: */
#define	SYS_getuid	24

/* syscall: "geteuid" ret: "uid_t" args: */
#define	SYS_geteuid	25

/* syscall: "ptrace" ret: "int" args: "int" "pid_t" "void *" "int" */
#define	SYS_ptrace	26

/* syscall: "recvmsg" ret: "ssize_t" args: "int" "struct msghdr *" "int" */
#define	SYS_recvmsg	27

/* syscall: "sendmsg" ret: "ssize_t" args: "int" "const struct msghdr *" "int" */
#define	SYS_sendmsg	28

/* syscall: "recvfrom" ret: "ssize_t" args: "int" "void *" "size_t" "int" "struct sockaddr *" "unsigned int *" */
#define	SYS_recvfrom	29

/* syscall: "accept" ret: "int" args: "int" "struct sockaddr *" "unsigned int *" */
#define	SYS_accept	30

/* syscall: "getpeername" ret: "int" args: "int" "struct sockaddr *" "unsigned int *" */
#define	SYS_getpeername	31

/* syscall: "getsockname" ret: "int" args: "int" "struct sockaddr *" "unsigned int *" */
#define	SYS_getsockname	32

/* syscall: "access" ret: "int" args: "const char *" "int" */
#define	SYS_access	33

/* syscall: "chflags" ret: "int" args: "const char *" "u_long" */
#define	SYS_chflags	34

/* syscall: "fchflags" ret: "int" args: "int" "u_long" */
#define	SYS_fchflags	35

/* syscall: "sync" ret: "void" args: */
#define	SYS_sync	36

/* syscall: "kill" ret: "int" args: "int" "int" */
#define	SYS_kill	37

/* syscall: "getppid" ret: "pid_t" args: */
#define	SYS_getppid	39

/* syscall: "dup" ret: "int" args: "int" */
#define	SYS_dup	41

/* syscall: "pipe" ret: "int" args: */
#define	SYS_pipe	42

/* syscall: "getegid" ret: "gid_t" args: */
#define	SYS_getegid	43

/* syscall: "profil" ret: "int" args: "char *" "size_t" "u_long" "u_int" */
#define	SYS_profil	44

/* syscall: "ktrace" ret: "int" args: "const char *" "int" "int" "int" */
#define	SYS_ktrace	45

/* syscall: "getgid" ret: "gid_t" args: */
#define	SYS_getgid	47

/* syscall: "__getlogin" ret: "int" args: "char *" "size_t" */
#define	SYS___getlogin	49

/* syscall: "__setlogin" ret: "int" args: "const char *" */
#define	SYS___setlogin	50

/* syscall: "acct" ret: "int" args: "const char *" */
#define	SYS_acct	51

/* syscall: "ioctl" ret: "int" args: "int" "u_long" "..." */
#define	SYS_ioctl	54

/* syscall: "revoke" ret: "int" args: "const char *" */
#define	SYS_revoke	56

/* syscall: "symlink" ret: "int" args: "const char *" "const char *" */
#define	SYS_symlink	57

/* syscall: "readlink" ret: "ssize_t" args: "const char *" "char *" "size_t" */
#define	SYS_readlink	58

/* syscall: "execve" ret: "int" args: "const char *" "char *const *" "char *const *" */
#define	SYS_execve	59

/* syscall: "umask" ret: "mode_t" args: "mode_t" */
#define	SYS_umask	60

/* syscall: "chroot" ret: "int" args: "const char *" */
#define	SYS_chroot	61

/* syscall: "vfork" ret: "int" args: */
#define	SYS_vfork	66

				/* 67 is obsolete vread */
				/* 68 is obsolete vwrite */
/* syscall: "sbrk" ret: "int" args: "intptr_t" */
#define	SYS_sbrk	69

/* syscall: "sstk" ret: "int" args: "int" */
#define	SYS_sstk	70

/* syscall: "vadvise" ret: "int" args: "int" */
#define	SYS_vadvise	72

/* syscall: "munmap" ret: "int" args: "void *" "size_t" */
#define	SYS_munmap	73

/* syscall: "mprotect" ret: "int" args: "void *" "size_t" "int" */
#define	SYS_mprotect	74

/* syscall: "madvise" ret: "int" args: "void *" "size_t" "int" */
#define	SYS_madvise	75

				/* 76 is obsolete vhangup */
				/* 77 is obsolete vlimit */
/* syscall: "mincore" ret: "int" args: "void *" "size_t" "char *" */
#define	SYS_mincore	78

/* syscall: "getgroups" ret: "int" args: "int" "gid_t *" */
#define	SYS_getgroups	79

/* syscall: "setgroups" ret: "int" args: "int" "const gid_t *" */
#define	SYS_setgroups	80

/* syscall: "getpgrp" ret: "int" args: */
#define	SYS_getpgrp	81

/* syscall: "setpgid" ret: "int" args: "int" "int" */
#define	SYS_setpgid	82

/* syscall: "dup2" ret: "int" args: "int" "int" */
#define	SYS_dup2	90

/* syscall: "fcntl" ret: "int" args: "int" "int" "..." */
#define	SYS_fcntl	92

/* syscall: "fsync" ret: "int" args: "int" */
#define	SYS_fsync	95

/* syscall: "setpriority" ret: "int" args: "int" "id_t" "int" */
#define	SYS_setpriority	96

/* syscall: "connect" ret: "int" args: "int" "const struct sockaddr *" "unsigned int" */
#define	SYS_connect	98

/* syscall: "getpriority" ret: "int" args: "int" "id_t" */
#define	SYS_getpriority	100

/* syscall: "bind" ret: "int" args: "int" "const struct sockaddr *" "unsigned int" */
#define	SYS_bind	104

/* syscall: "setsockopt" ret: "int" args: "int" "int" "int" "const void *" "unsigned int" */
#define	SYS_setsockopt	105

/* syscall: "listen" ret: "int" args: "int" "int" */
#define	SYS_listen	106

				/* 107 is obsolete vtimes */
/* syscall: "getsockopt" ret: "int" args: "int" "int" "int" "void *" "unsigned int *" */
#define	SYS_getsockopt	118

				/* 119 is obsolete resuba */
/* syscall: "readv" ret: "ssize_t" args: "int" "const struct iovec *" "int" */
#define	SYS_readv	120

/* syscall: "writev" ret: "ssize_t" args: "int" "const struct iovec *" "int" */
#define	SYS_writev	121

/* syscall: "fchown" ret: "int" args: "int" "uid_t" "gid_t" */
#define	SYS_fchown	123

/* syscall: "fchmod" ret: "int" args: "int" "mode_t" */
#define	SYS_fchmod	124

/* syscall: "setreuid" ret: "int" args: "uid_t" "uid_t" */
#define	SYS_setreuid	126

/* syscall: "setregid" ret: "int" args: "gid_t" "gid_t" */
#define	SYS_setregid	127

/* syscall: "rename" ret: "int" args: "const char *" "const char *" */
#define	SYS_rename	128

/* syscall: "flock" ret: "int" args: "int" "int" */
#define	SYS_flock	131

/* syscall: "mkfifo" ret: "int" args: "const char *" "mode_t" */
#define	SYS_mkfifo	132

/* syscall: "sendto" ret: "ssize_t" args: "int" "const void *" "size_t" "int" "const struct sockaddr *" "unsigned int" */
#define	SYS_sendto	133

/* syscall: "shutdown" ret: "int" args: "int" "int" */
#define	SYS_shutdown	134

/* syscall: "socketpair" ret: "int" args: "int" "int" "int" "int *" */
#define	SYS_socketpair	135

/* syscall: "mkdir" ret: "int" args: "const char *" "mode_t" */
#define	SYS_mkdir	136

/* syscall: "rmdir" ret: "int" args: "const char *" */
#define	SYS_rmdir	137

/* syscall: "setsid" ret: "int" args: */
#define	SYS_setsid	147

/* syscall: "quotactl" ret: "int" args: "const char *" "int" "int" "void *" */
#define	SYS_quotactl	148

/* syscall: "nfssvc" ret: "int" args: "int" "void *" */
#define	SYS_nfssvc	155

/* syscall: "sysarch" ret: "int" args: "int" "void *" */
#define	SYS_sysarch	165

/* syscall: "pread" ret: "ssize_t" args: "int" "void *" "size_t" "int" "off_t" */
#define	SYS_pread	173

/* syscall: "pwrite" ret: "ssize_t" args: "int" "const void *" "size_t" "int" "off_t" */
#define	SYS_pwrite	174

#if defined(NTP) || !defined(_KERNEL_OPT)
/* syscall: "ntp_adjtime" ret: "int" args: "struct timex *" */
#define	SYS_ntp_adjtime	176

#else
				/* 176 is excluded ntp_adjtime */
#endif
/* syscall: "setgid" ret: "int" args: "gid_t" */
#define	SYS_setgid	181

/* syscall: "setegid" ret: "int" args: "gid_t" */
#define	SYS_setegid	182

/* syscall: "seteuid" ret: "int" args: "uid_t" */
#define	SYS_seteuid	183

#if defined(LFS) || !defined(_KERNEL)
/* syscall: "lfs_bmapv" ret: "int" args: "fsid_t *" "struct block_info *" "int" */
#define	SYS_lfs_bmapv	184

/* syscall: "lfs_markv" ret: "int" args: "fsid_t *" "struct block_info *" "int" */
#define	SYS_lfs_markv	185

/* syscall: "lfs_segclean" ret: "int" args: "fsid_t *" "u_long" */
#define	SYS_lfs_segclean	186

/* syscall: "pathconf" ret: "long" args: "const char *" "int" */
#define	SYS_pathconf	191

/* syscall: "fpathconf" ret: "long" args: "int" "int" */
#define	SYS_fpathconf	192

/* syscall: "getrlimit" ret: "int" args: "int" "struct rlimit *" */
#define	SYS_getrlimit	194

/* syscall: "setrlimit" ret: "int" args: "int" "const struct rlimit *" */
#define	SYS_setrlimit	195

/* syscall: "mmap" ret: "void *" args: "void *" "size_t" "int" "int" "int" "long" "off_t" */
#define	SYS_mmap	197

/* syscall: "__syscall" ret: "quad_t" args: "quad_t" "..." */
#define	SYS___syscall	198

/* syscall: "lseek" ret: "off_t" args: "int" "int" "off_t" "int" */
#define	SYS_lseek	199

/* syscall: "truncate" ret: "int" args: "const char *" "int" "off_t" */
#define	SYS_truncate	200

/* syscall: "ftruncate" ret: "int" args: "int" "int" "off_t" */
#define	SYS_ftruncate	201

/* syscall: "__sysctl" ret: "int" args: "const int *" "u_int" "void *" "size_t *" "const void *" "size_t" */
#define	SYS___sysctl	202

/* syscall: "mlock" ret: "int" args: "const void *" "size_t" */
#define	SYS_mlock	203

/* syscall: "munlock" ret: "int" args: "const void *" "size_t" */
#define	SYS_munlock	204

/* syscall: "undelete" ret: "int" args: "const char *" */
#define	SYS_undelete	205

/* syscall: "getpgid" ret: "pid_t" args: "pid_t" */
#define	SYS_getpgid	207

/* syscall: "reboot" ret: "int" args: "int" "char *" */
#define	SYS_reboot	208

/* syscall: "poll" ret: "int" args: "struct pollfd *" "u_int" "int" */
#define	SYS_poll	209

/* syscall: "semget" ret: "int" args: "key_t" "int" "int" */
#define	SYS_semget	221

/* syscall: "semop" ret: "int" args: "int" "struct sembuf *" "size_t" */
#define	SYS_semop	222

/* syscall: "semconfig" ret: "int" args: "int" */
#define	SYS_semconfig	223

#else
				/* 221 is excluded semget */
				/* 222 is excluded semop */
				/* 223 is excluded semconfig */
#endif
#if defined(SYSVMSG) || !defined(_KERNEL_OPT)
/* syscall: "msgget" ret: "int" args: "key_t" "int" */
#define	SYS_msgget	225

/* syscall: "msgsnd" ret: "int" args: "int" "const void *" "size_t" "int" */
#define	SYS_msgsnd	226

/* syscall: "msgrcv" ret: "ssize_t" args: "int" "void *" "size_t" "long" "int" */
#define	SYS_msgrcv	227

#else
				/* 225 is excluded msgget */
				/* 226 is excluded msgsnd */
				/* 227 is excluded msgrcv */
#endif
#if defined(SYSVSHM) || !defined(_KERNEL_OPT)
/* syscall: "shmat" ret: "void *" args: "int" "const void *" "int" */
#define	SYS_shmat	228

/* syscall: "shmdt" ret: "int" args: "const void *" */
#define	SYS_shmdt	230

/* syscall: "shmget" ret: "int" args: "key_t" "size_t" "int" */
#define	SYS_shmget	231

#else
				/* 228 is excluded shmat */
				/* 230 is excluded shmdt */
				/* 231 is excluded shmget */
#endif

/* syscall: "timer_create" ret: "int" args: "clockid_t" "struct sigevent *" "timer_t *" */
#define	SYS_timer_create	235

/* syscall: "timer_delete" ret: "int" args: "timer_t" */
#define	SYS_timer_delete	236

/* syscall: "timer_getoverrun" ret: "int" args: "timer_t" */
#define	SYS_timer_getoverrun	239

/* syscall: "fdatasync" ret: "int" args: "int" */
#define	SYS_fdatasync	241

/* syscall: "mlockall" ret: "int" args: "int" */
#define	SYS_mlockall	242

/* syscall: "munlockall" ret: "int" args: */
#define	SYS_munlockall	243

/* syscall: "modctl" ret: "int" args: "int" "void *" */
#define	SYS_modctl	246

/* syscall: "_ksem_init" ret: "int" args: "unsigned int" "intptr_t *" */
#define	SYS__ksem_init	247

/* syscall: "_ksem_open" ret: "int" args: "const char *" "int" "mode_t" "unsigned int" "intptr_t *" */
#define	SYS__ksem_open	248

/* syscall: "_ksem_unlink" ret: "int" args: "const char *" */
#define	SYS__ksem_unlink	249

/* syscall: "_ksem_close" ret: "int" args: "intptr_t" */
#define	SYS__ksem_close	250

/* syscall: "_ksem_post" ret: "int" args: "intptr_t" */
#define	SYS__ksem_post	251

/* syscall: "_ksem_wait" ret: "int" args: "intptr_t" */
#define	SYS__ksem_wait	252

/* syscall: "_ksem_trywait" ret: "int" args: "intptr_t" */
#define	SYS__ksem_trywait	253

/* syscall: "_ksem_getvalue" ret: "int" args: "intptr_t" "unsigned int *" */
#define	SYS__ksem_getvalue	254

/* syscall: "_ksem_destroy" ret: "int" args: "intptr_t" */
#define	SYS__ksem_destroy	255

/* syscall: "mq_open" ret: "mqd_t" args: "const char *" "int" "mode_t" "struct mq_attr *" */
#define	SYS_mq_open	257

/* syscall: "mq_close" ret: "int" args: "mqd_t" */
#define	SYS_mq_close	258

/* syscall: "mq_unlink" ret: "int" args: "const char *" */
#define	SYS_mq_unlink	259

/* syscall: "mq_getattr" ret: "int" args: "mqd_t" "struct mq_attr *" */
#define	SYS_mq_getattr	260

/* syscall: "mq_setattr" ret: "int" args: "mqd_t" "const struct mq_attr *" "struct mq_attr *" */
#define	SYS_mq_setattr	261

/* syscall: "mq_notify" ret: "int" args: "mqd_t" "const struct sigevent *" */
#define	SYS_mq_notify	262

/* syscall: "mq_send" ret: "int" args: "mqd_t" "const char *" "size_t" "unsigned" */
#define	SYS_mq_send	263

/* syscall: "mq_receive" ret: "ssize_t" args: "mqd_t" "char *" "size_t" "unsigned *" */
#define	SYS_mq_receive	264

/* syscall: "posix_rename" ret: "int" args: "const char *" "const char *" */
#define	SYS_posix_rename	270

/* syscall: "swapctl" ret: "int" args: "int" "void *" "int" */
#define	SYS_swapctl	271

/* syscall: "minherit" ret: "int" args: "void *" "size_t" "int" */
#define	SYS_minherit	273

/* syscall: "lchmod" ret: "int" args: "const char *" "mode_t" */
#define	SYS_lchmod	274

/* syscall: "lchown" ret: "int" args: "const char *" "uid_t" "gid_t" */
#define	SYS_lchown	275

/* syscall: "msync" ret: "int" args: "void *" "size_t" "int" */
#define	SYS_msync	277

/* syscall: "__sigaltstack14" ret: "int" args: "const struct sigaltstack *" "struct sigaltstack *" */
#define	SYS_sigaltstack	281

/* syscall: "__vfork14" ret: "int" args: */
#define	SYS_vfork	282

/* syscall: "__posix_chown" ret: "int" args: "const char *" "uid_t" "gid_t" */
#define	SYS___posix_chown	283

/* syscall: "__posix_fchown" ret: "int" args: "int" "uid_t" "gid_t" */
#define	SYS___posix_fchown	284

/* syscall: "__posix_lchown" ret: "int" args: "const char *" "uid_t" "gid_t" */
#define	SYS___posix_lchown	285

/* syscall: "getsid" ret: "pid_t" args: "pid_t" */
#define	SYS_getsid	286

/* syscall: "__clone" ret: "pid_t" args: "int" "void *" */
#define	SYS___clone	287

/* syscall: "fktrace" ret: "int" args: "int" "int" "int" "int" */
#define	SYS_fktrace	288

/* syscall: "preadv" ret: "ssize_t" args: "int" "const struct iovec *" "int" "int" "off_t" */
#define	SYS_preadv	289

/* syscall: "pwritev" ret: "ssize_t" args: "int" "const struct iovec *" "int" "int" "off_t" */
#define	SYS_pwritev	290

/* syscall: "sigpending" ret: "int" args: "sigset_t *" */
#define	SYS_sigpending	292

/* syscall: "sigprocmask" ret: "int" args: "int" "const sigset_t *" "sigset_t *" */
#define	SYS_sigprocmask	293

/* syscall: "sigsuspend" ret: "int" args: "const sigset_t *" */
#define	SYS_sigsuspend	294

/* syscall: "__getcwd" ret: "int" args: "char *" "size_t" */
#define	SYS___getcwd	296

/* syscall: "fchroot" ret: "int" args: "int" */
#define	SYS_fchroot	297

/* syscall: "lchflags" ret: "int" args: "const char *" "u_long" */
#define	SYS_lchflags	304

/* syscall: "issetugid" ret: "int" args: */
#define	SYS_issetugid	305

/* syscall: "utrace" ret: "int" args: "const char *" "void *" "size_t" */
#define	SYS_utrace	306

/* syscall: "getcontext" ret: "int" args: "struct __ucontext *" */
#define	SYS_getcontext	307

/* syscall: "setcontext" ret: "int" args: "const struct __ucontext *" */
#define	SYS_setcontext	308

/* syscall: "_lwp_create" ret: "int" args: "const struct __ucontext *" "u_long" "lwpid_t *" */
#define	SYS__lwp_create	309

/* syscall: "_lwp_exit" ret: "int" args: */
#define	SYS__lwp_exit	310

/* syscall: "_lwp_self" ret: "lwpid_t" args: */
#define	SYS__lwp_self	311

/* syscall: "_lwp_wait" ret: "int" args: "lwpid_t" "lwpid_t *" */
#define	SYS__lwp_wait	312

/* syscall: "_lwp_suspend" ret: "int" args: "lwpid_t" */
#define	SYS__lwp_suspend	313

/* syscall: "_lwp_continue" ret: "int" args: "lwpid_t" */
#define	SYS__lwp_continue	314

/* syscall: "_lwp_wakeup" ret: "int" args: "lwpid_t" */
#define	SYS__lwp_wakeup	315

/* syscall: "_lwp_getprivate" ret: "void *" args: */
#define	SYS__lwp_getprivate	316

/* syscall: "_lwp_setprivate" ret: "void" args: "void *" */
#define	SYS__lwp_setprivate	317

/* syscall: "_lwp_kill" ret: "int" args: "lwpid_t" "int" */
#define	SYS__lwp_kill	318

/* syscall: "_lwp_detach" ret: "int" args: "lwpid_t" */
#define	SYS__lwp_detach	319

/* syscall: "_lwp_unpark" ret: "int" args: "lwpid_t" "const void *" */
#define	SYS__lwp_unpark	321

/* syscall: "_lwp_unpark_all" ret: "ssize_t" args: "const lwpid_t *" "size_t" "const void *" */
#define	SYS__lwp_unpark_all	322

/* syscall: "_lwp_setname" ret: "int" args: "lwpid_t" "const char *" */
#define	SYS__lwp_setname	323

/* syscall: "_lwp_getname" ret: "int" args: "lwpid_t" "char *" "size_t" */
#define	SYS__lwp_getname	324

/* syscall: "_lwp_ctl" ret: "int" args: "int" "struct lwpctl **" */
#define	SYS__lwp_ctl	325

/* syscall: "sa_register" ret: "int" args: "sa_upcall_t" "sa_upcall_t *" "int" "ssize_t" */
#define	SYS_sa_register	330

/* syscall: "sa_stacks" ret: "int" args: "int" "stack_t *" */
#define	SYS_sa_stacks	331

/* syscall: "sa_enable" ret: "int" args: */
#define	SYS_sa_enable	332

/* syscall: "sa_setconcurrency" ret: "int" args: "int" */
#define	SYS_sa_setconcurrency	333

/* syscall: "sa_yield" ret: "int" args: */
#define	SYS_sa_yield	334

/* syscall: "sa_preempt" ret: "int" args: "int" */
#define	SYS_sa_preempt	335

				/* 336 is obsolete sys_sa_unblockyield */
/* syscall: "__sigaction_sigtramp" ret: "int" args: "int" "const struct sigaction *" "struct sigaction *" "const void *" "int" */
#define	SYS___sigaction_sigtramp	340

/* syscall: "pmc_get_info" ret: "int" args: "int" "int" "void *" */
#define	SYS_pmc_get_info	341

/* syscall: "pmc_control" ret: "int" args: "int" "int" "void *" */
#define	SYS_pmc_control	342

/* syscall: "rasctl" ret: "int" args: "void *" "size_t" "int" */
#define	SYS_rasctl	343

/* syscall: "kqueue" ret: "int" args: */
#define	SYS_kqueue	344

/* syscall: "_sched_setparam" ret: "int" args: "pid_t" "lwpid_t" "int" "const struct sched_param *" */
#define	SYS__sched_setparam	346

/* syscall: "_sched_getparam" ret: "int" args: "pid_t" "lwpid_t" "int *" "struct sched_param *" */
#define	SYS__sched_getparam	347

/* syscall: "_sched_setaffinity" ret: "int" args: "pid_t" "lwpid_t" "size_t" "const cpuset_t *" */
#define	SYS__sched_setaffinity	348

/* syscall: "_sched_getaffinity" ret: "int" args: "pid_t" "lwpid_t" "size_t" "cpuset_t *" */
#define	SYS__sched_getaffinity	349

/* syscall: "sched_yield" ret: "int" args: */
#define	SYS_sched_yield	350

/* syscall: "fsync_range" ret: "int" args: "int" "int" "off_t" "off_t" */
#define	SYS_fsync_range	354

/* syscall: "uuidgen" ret: "int" args: "struct uuid *" "int" */
#define	SYS_uuidgen	355

/* syscall: "getvfsstat" ret: "int" args: "struct statvfs *" "size_t" "int" */
#define	SYS_getvfsstat	356

/* syscall: "statvfs1" ret: "int" args: "const char *" "struct statvfs *" "int" */
#define	SYS_statvfs1	357

/* syscall: "fstatvfs1" ret: "int" args: "int" "struct statvfs *" "int" */
#define	SYS_fstatvfs1	358

/* syscall: "extattrctl" ret: "int" args: "const char *" "int" "const char *" "int" "const char *" */
#define	SYS_extattrctl	360

/* syscall: "extattr_set_file" ret: "int" args: "const char *" "int" "const char *" "const void *" "size_t" */
#define	SYS_extattr_set_file	361

/* syscall: "extattr_get_file" ret: "ssize_t" args: "const char *" "int" "const char *" "void *" "size_t" */
#define	SYS_extattr_get_file	362

/* syscall: "extattr_delete_file" ret: "int" args: "const char *" "int" "const char *" */
#define	SYS_extattr_delete_file	363

/* syscall: "extattr_set_fd" ret: "int" args: "int" "int" "const char *" "const void *" "size_t" */
#define	SYS_extattr_set_fd	364

/* syscall: "extattr_get_fd" ret: "ssize_t" args: "int" "int" "const char *" "void *" "size_t" */
#define	SYS_extattr_get_fd	365

/* syscall: "extattr_delete_fd" ret: "int" args: "int" "int" "const char *" */
#define	SYS_extattr_delete_fd	366

/* syscall: "extattr_set_link" ret: "int" args: "const char *" "int" "const char *" "const void *" "size_t" */
#define	SYS_extattr_set_link	367

/* syscall: "extattr_get_link" ret: "ssize_t" args: "const char *" "int" "const char *" "void *" "size_t" */
#define	SYS_extattr_get_link	368

/* syscall: "extattr_delete_link" ret: "int" args: "const char *" "int" "const char *" */
#define	SYS_extattr_delete_link	369

/* syscall: "extattr_list_fd" ret: "ssize_t" args: "int" "int" "void *" "size_t" */
#define	SYS_extattr_list_fd	370

/* syscall: "extattr_list_file" ret: "ssize_t" args: "const char *" "int" "void *" "size_t" */
#define	SYS_extattr_list_file	371

/* syscall: "extattr_list_link" ret: "ssize_t" args: "const char *" "int" "void *" "size_t" */
#define	SYS_extattr_list_link	372

/* syscall: "setxattr" ret: "int" args: "const char *" "const char *" "void *" "size_t" "int" */
#define	SYS_setxattr	375

/* syscall: "lsetxattr" ret: "int" args: "const char *" "const char *" "void *" "size_t" "int" */
#define	SYS_lsetxattr	376

/* syscall: "fsetxattr" ret: "int" args: "int" "const char *" "void *" "size_t" "int" */
#define	SYS_fsetxattr	377

/* syscall: "getxattr" ret: "int" args: "const char *" "const char *" "void *" "size_t" */
#define	SYS_getxattr	378

/* syscall: "lgetxattr" ret: "int" args: "const char *" "const char *" "void *" "size_t" */
#define	SYS_lgetxattr	379

/* syscall: "fgetxattr" ret: "int" args: "int" "const char *" "void *" "size_t" */
#define	SYS_fgetxattr	380

/* syscall: "listxattr" ret: "int" args: "const char *" "char *" "size_t" */
#define	SYS_listxattr	381

/* syscall: "llistxattr" ret: "int" args: "const char *" "char *" "size_t" */
#define	SYS_llistxattr	382

/* syscall: "flistxattr" ret: "int" args: "int" "char *" "size_t" */
#define	SYS_flistxattr	383

/* syscall: "removexattr" ret: "int" args: "const char *" "const char *" */
#define	SYS_removexattr	384

/* syscall: "lremovexattr" ret: "int" args: "const char *" "const char *" */
#define	SYS_lremovexattr	385

/* syscall: "fremovexattr" ret: "int" args: "int" "const char *" */
#define	SYS_fremovexattr	386

/* syscall: "getdents" ret: "int" args: "int" "char *" "size_t" */
#define	SYS_getdents	390

				/* 391 is ignored old posix_fadvise */
/* syscall: "socket" ret: "int" args: "int" "int" "int" */
#define	SYS_socket	394

/* syscall: "getfh" ret: "int" args: "const char *" "void *" "size_t *" */
#define	SYS_getfh	395

/* syscall: "fhopen" ret: "int" args: "const void *" "size_t" "int" */
#define	SYS_fhopen	396

/* syscall: "fhstatvfs1" ret: "int" args: "const void *" "size_t" "struct statvfs *" "int" */
#define	SYS_fhstatvfs1	397

/* syscall: "aio_cancel" ret: "int" args: "int" "struct aiocb *" */
#define	SYS_aio_cancel	399

/* syscall: "aio_error" ret: "int" args: "const struct aiocb *" */
#define	SYS_aio_error	400

/* syscall: "aio_fsync" ret: "int" args: "int" "struct aiocb *" */
#define	SYS_aio_fsync	401

/* syscall: "aio_read" ret: "int" args: "struct aiocb *" */
#define	SYS_aio_read	402

/* syscall: "aio_return" ret: "int" args: "struct aiocb *" */
#define	SYS_aio_return	403

/* syscall: "aio_write" ret: "int" args: "struct aiocb *" */
#define	SYS_aio_write	405

/* syscall: "lio_listio" ret: "int" args: "int" "struct aiocb *const *" "int" "struct sigevent *" */
#define	SYS_lio_listio	406

/* syscall: "mount" ret: "int" args: "const char *" "const char *" "int" "void *" "size_t" */
#define	SYS_mount	410

/* syscall: "mremap" ret: "void *" args: "void *" "size_t" "void *" "size_t" "int" */
#define	SYS_mremap	411

/* syscall: "pset_create" ret: "int" args: "psetid_t *" */
#define	SYS_pset_create	412

/* syscall: "pset_destroy" ret: "int" args: "psetid_t" */
#define	SYS_pset_destroy	413

/* syscall: "pset_assign" ret: "int" args: "psetid_t" "cpuid_t" "psetid_t *" */
#define	SYS_pset_assign	414

/* syscall: "_pset_bind" ret: "int" args: "idtype_t" "id_t" "id_t" "psetid_t" "psetid_t *" */
#define	SYS__pset_bind	415

/* syscall: "posix_fadvise" ret: "int" args: "int" "int" "off_t" "off_t" "int" */
#define	SYS_posix_fadvise	416

/* syscall: "select" ret: "int" args: "int" "fd_set *" "fd_set *" "fd_set *" "struct timeval *" */
#define	SYS_select	417

/* syscall: "gettimeofday" ret: "int" args: "struct timeval *" "void *" */
#define	SYS_gettimeofday	418

/* syscall: "settimeofday" ret: "int" args: "const struct timeval *" "const void *" */
#define	SYS_settimeofday	419

/* syscall: "utimes" ret: "int" args: "const char *" "const struct timeval *" */
#define	SYS_utimes	420

/* syscall: "__adjtime" ret: "int" args: "const struct timeval *" "struct timeval *" */
#define	SYS___adjtime	421

#if defined(LFS) || !defined(_KERNEL)
/* syscall: "lfs_segwait" ret: "int" args: "fsid_t *" "struct timeval *" */
#define	SYS_lfs_segwait	422

#else
				/* 422 is excluded lfs_segwait */
#endif
/* syscall: "futimes" ret: "int" args: "int" "const struct timeval *" */
#define	SYS_futimes	423

/* syscall: "lutimes" ret: "int" args: "const char *" "const struct timeval *" */
#define	SYS_lutimes	424

/* syscall: "setitimer" ret: "int" args: "int" "const struct itimerval *" "struct itimerval *" */
#define	SYS_setitimer	425

/* syscall: "getitimer" ret: "int" args: "int" "struct itimerval *" */
#define	SYS_getitimer	426

/* syscall: "clock_gettime" ret: "int" args: "clockid_t" "struct timespec *" */
#define	SYS_clock_gettime	427

/* syscall: "clock_settime" ret: "int" args: "clockid_t" "const struct timespec *" */
#define	SYS_clock_settime	428

/* syscall: "clock_getres" ret: "int" args: "clockid_t" "struct timespec *" */
#define	SYS_clock_getres	429

/* syscall: "nanosleep" ret: "int" args: "const struct timespec *" "struct timespec *" */
#define	SYS_nanosleep	430

/* syscall: "__sigtimedwait" ret: "int" args: "const sigset_t *" "siginfo_t *" "struct timespec *" */
#define	SYS___sigtimedwait	431

/* syscall: "mq_timedsend" ret: "int" args: "mqd_t" "const char *" "size_t" "unsigned" "const struct timespec *" */
#define	SYS_mq_timedsend	432

/* syscall: "mq_timedreceive" ret: "ssize_t" args: "mqd_t" "char *" "size_t" "unsigned *" "const struct timespec *" */
#define	SYS_mq_timedreceive	433

/* syscall: "_lwp_park" ret: "int" args: "const struct timespec *" "lwpid_t" "const void *" "const void *" */
#define	SYS__lwp_park	434

/* syscall: "kevent" ret: "int" args: "int" "const struct kevent *" "size_t" "struct kevent *" "size_t" "const struct timespec *" */
#define	SYS_kevent	435

/* syscall: "pselect" ret: "int" args: "int" "fd_set *" "fd_set *" "fd_set *" "const struct timespec *" "const sigset_t *" */
#define	SYS_pselect	436

/* syscall: "pollts" ret: "int" args: "struct pollfd *" "u_int" "const struct timespec *" "const sigset_t *" */
#define	SYS_pollts	437

/* syscall: "aio_suspend" ret: "int" args: "const struct aiocb *const *" "int" "const struct timespec *" */
#define	SYS_aio_suspend	438

/* syscall: "stat" ret: "int" args: "const char *" "struct stat *" */
#define	SYS_stat	439

/* syscall: "fstat" ret: "int" args: "int" "struct stat *" */
#define	SYS_fstat	440

/* syscall: "lstat" ret: "int" args: "const char *" "struct stat *" */
#define	SYS_lstat	441

#if defined(SYSVSEM) || !defined(_KERNEL_OPT)
/* syscall: "semctl" ret: "int" args: "int" "int" "int" "..." */
#define	SYS_semctl	442

#else
				/* 442 is excluded semctl */
#endif
#if defined(SYSVSHM) || !defined(_KERNEL_OPT)
/* syscall: "shmctl" ret: "int" args: "int" "int" "struct shmid_ds *" */
#define	SYS_shmctl	443

#else
				/* 443 is excluded shmctl */
#endif
#if defined(SYSVMSG) || !defined(_KERNEL_OPT)
/* syscall: "msgctl" ret: "int" args: "int" "int" "struct msqid_ds *" */
#define	SYS_msgctl	444

#else
				/* 444 is excluded msgctl */
#endif
/* syscall: "getrusage" ret: "int" args: "int" "struct rusage *" */
#define	SYS_getrusage	445

/* syscall: "timer_settime" ret: "int" args: "timer_t" "int" "const struct itimerspec *" "struct itimerspec *" */
#define	SYS_timer_settime	446

/* syscall: "timer_gettime" ret: "int" args: "timer_t" "struct itimerspec *" */
#define	SYS_timer_gettime	447

#if defined(NTP) || !defined(_KERNEL_OPT)
/* syscall: "ntp_gettime" ret: "int" args: "struct ntptimeval *" */
#define	SYS_ntp_gettime	448

#else
				/* 448 is excluded _ntp_gettime */
#endif
/* syscall: "wait4" ret: "int" args: "int" "int *" "int" "struct rusage *" */
#define	SYS_wait4	449

/* syscall: "mknod" ret: "int" args: "const char *" "mode_t" "dev_t" */
#define	SYS_mknod	450

/* syscall: "fhstat" ret: "int" args: "const void *" "size_t" "struct stat *" */
#define	SYS_fhstat	451

#define	SYS_MAXSYSCALL	452
#define	SYS_NSYSENT	512
#endif /* _SYS_SYSCALL_H_ */
