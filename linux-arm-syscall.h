#define restart_syscall 0
#define exit 1
#define fork 2
#define read 3
#define write 4
#define open 5
#define close 6
#define creat 8
#define link 9
#define unlink 10
#define execve 11
#define chdir 12
#define time 13
#define mknod 14
#define chmod 15
#define lchown 16
#define lseek 19
#define getpid 20
#define mount 21
#define umount 22
#define setuid 23
#define getuid 24
#define stime 25
#define ptrace 26
#define alarm 27
#define pause 29
#define utime 30
#define access 33
#define nice 34
#define sync 36
#define kill 37
#define rename 38
#define mkdir 39
#define rmdir 40
#define dup 41
#define pipe 42
#define times 43
#define brk 45
#define setgid 46
#define getgid 47
#define geteuid 49
#define getegid 50
#define acct 51
#define umount2 52
#define ioctl 54
#define fcntl 55
#define setpgid 57
#define umask 60
#define chroot 61
#define ustat 62
#define dup2 63
#define getppid 64
#define getpgrp 65
#define setsid 66
#define sigaction 67
#define setreuid 70
#define setregid 71
#define sigsuspend 72
#define sigpending 73
#define sethostname 74
#define setrlimit 75
#define getrlimit 76
#define getrusage 77
#define gettimeofday 78
#define settimeofday 79
#define getgroups 80
#define setgroups 81
#define select 82
#define symlink 83
#define readlink 85
#define uselib 86
#define swapon 87
#define reboot 88
#define readdir 89
#define mmap 90
#define munmap 91
#define truncate 92
#define ftruncate 93
#define fchmod 94
#define fchown 95
#define getpriority 96
#define setpriority 97
#define statfs 99
#define fstatfs 100
#define socketcall 102
#define syslog 103
#define setitimer 104
#define getitimer 105
#define stat 106
#define lstat 107
#define fstat 108
#define vhangup 111
#define syscall 113
#define wait4 114
#define swapoff 115
#define sysinfo 116
#define ipc 117
#define fsync 118
#define sigreturn 119
#define clone 120
#define setdomainname 121
#define uname 122
#define adjtimex 124
#define mprotect 125
#define sigprocmask 126
#define init_module 128
#define delete_module 129
#define quotactl 131
#define getpgid 132
#define fchdir 133
#define bdflush 134
#define sysfs 135
#define personality 136
#define setfsuid 138
#define setfsgid 139
#define llseek 140
#define getdents 141
#define newselect 142
#define flock 143
#define msync 144
#define readv 145
#define writev 146
#define getsid 147
#define fdatasync 148
#define sysctl 149
#define mlock 150
#define munlock 151
#define mlockall 152
#define munlockall 153
#define sched_setparam 154
#define sched_getparam 155
#define sched_setscheduler 156
#define sched_getscheduler 157
#define sched_yield 158
#define sched_get_priority_max 159
#define sched_get_priority_min 160
#define sched_rr_get_interval 161
#define nanosleep 162
#define mremap 163
#define setresuid 164
#define getresuid 165
#define poll 168
#define nfsservctl 169
#define setresgid 170
#define getresgid 171
#define prctl 172
#define rt_sigreturn 173
#define rt_sigaction 174
#define rt_sigprocmask 175
#define rt_sigpending 176
#define rt_sigtimedwait 177
#define rt_sigqueueinfo 178
#define rt_sigsuspend 179
#define pread64 180
#define pwrite64 181
#define chown 182
#define getcwd 183
#define capget 184
#define capset 185
#define sigaltstack 186
#define sendfile 187
#define vfork 190
#define ugetrlimit 191
#define mmap2 192
#define truncate64 193
#define ftruncate64 194
#define stat64 195
#define lstat64 196
#define fstat64 197
#define lchown32 198
#define getuid32 199
#define getgid32 200
#define geteuid32 201
#define getegid32 202
#define setreuid32 203
#define setregid32 204
#define getgroups32 205
#define setgroups32 206
#define fchown32 207
#define setresuid32 208
#define getresuid32 209
#define setresgid32 210
#define getresgid32 211
#define chown32 212
#define setuid32 213
#define setgid32 214
#define setfsuid32 215
#define setfsgid32 216
#define getdents64 217
#define pivot_root 218
#define mincore 219
#define madvise 220
#define fcntl64 221
#define gettid 224
#define readahead 225
#define setxattr 226
#define lsetxattr 227
#define fsetxattr 228
#define getxattr 229
#define lgetxattr 230
#define fgetxattr 231
#define listxattr 232
#define llistxattr 233
#define flistxattr 234
#define removexattr 235
#define lremovexattr 236
#define fremovexattr 237
#define tkill 238
#define sendfile64 239
#define futex 240
#define sched_setaffinity 241
#define sched_getaffinity 242
#define io_setup 243
#define io_destroy 244
#define io_getevents 245
#define io_submit 246
#define io_cancel 247
#define exit_group 248
#define lookup_dcookie 249
#define epoll_create 250
#define epoll_ctl 251
#define epoll_wait 252
#define remap_file_pages 253
#define set_tid_address 256
#define timer_create 257
#define timer_settime 258
#define timer_gettime 259
#define timer_getoverrun 260
#define timer_delete 261
#define clock_settime 262
#define clock_gettime 263
#define clock_getres 264
#define clock_nanosleep 265
#define statfs64 266
#define fstatfs64 267
#define tgkill 268
#define utimes 269
#define arm_fadvise64_64 270
#define pciconfig_iobase 271
#define pciconfig_read 272
#define pciconfig_write 273
#define mq_open 274
#define mq_unlink 275
#define mq_timedsend 276
#define mq_timedreceive 277
#define mq_notify 278
#define mq_getsetattr 279
#define waitid 280
#define socket 281
#define bind 282
#define connect 283
#define listen 284
#define accept 285
#define getsockname 286
#define getpeername 287
#define socketpair 288
#define send 289
#define sendto 290
#define recv 291
#define recvfrom 292
#define shutdown 293
#define setsockopt 294
#define getsockopt 295
#define sendmsg 296
#define recvmsg 297
#define semop 298
#define semget 299
#define semctl 300
#define msgsnd 301
#define msgrcv 302
#define msgget 303
#define msgctl 304
#define shmat 305
#define shmdt 306
#define shmget 307
#define shmctl 308
#define add_key 309
#define request_key 310
#define keyctl 311
#define semtimedop 312
#define vserver 313
#define ioprio_set 314
#define ioprio_get 315
#define inotify_init 316
#define inotify_add_watch 317
#define inotify_rm_watch 318
#define mbind 319
#define get_mempolicy 320
#define set_mempolicy 321
#define openat 322
#define mkdirat 323
#define mknodat 324
#define fchownat 325
#define futimesat 326
#define fstatat64 327
#define unlinkat 328
#define renameat 329
#define linkat 330
#define symlinkat 331
#define readlinkat 332
#define fchmodat 333
#define faccessat 334
#define pselect6 335
#define ppoll 336
#define unshare 337
#define set_robust_list 338
#define get_robust_list 339
#define splice 340
#define arm_sync_file_range 341
#define tee 342
#define vmsplice 343
#define move_pages 344
#define getcpu 345
#define epoll_pwait 346
#define kexec_load 347
#define utimensat 348
#define signalfd 349
#define timerfd_create 350
#define eventfd 351
#define fallocate 352
#define timerfd_settime 353
#define timerfd_gettime 354
#define signalfd4 355
#define eventfd2 356
#define epoll_create1 357
#define dup3 358
#define pipe2 359
#define inotify_init1 360
#define preadv 361
#define pwritev 362
#define rt_tgsigqueueinfo 363
#define perf_event_open 364
#define recvmmsg 365
