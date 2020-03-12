# cse_221_os
operating system

- CPU
  measurement overhead:\n
    cpu_read.c
    cpu_iter.c
  procedure call overhead:
    cpu_proc.c
  system call overhead:
    cpu_syncall.c
    cpu_sycall_measure.c
  process, thread creation:
    cpu_task.c
  
  process context switch:
    cpu_task_cs.c
  thread context switch:
    cpu_thread_cs.c
    
- Memory 
  memory access:
    mem_access.c
  memory bandwidth:
    mem_bandwidth.c
  page fault:
    page_fault.c

- Network
  RTT:
    RTT.py
  bandwidth, setup, teardown:
    bandwidth.py
    
    usage
      server side: python bandwidth.py -s 
      client side: python bandwidth.py -c [host_addr]
      setup: python bandwidth.py -setup [host_addr]
      teardown: python bandwidth.py -teardown [host_addr]
      
- File System
  File read:
    file_read.c
  File cache:
    file_cache.c
  Remote access:
    remote_fileclient.c
    remote_fileserver.c
  Contention:
    file_extra_proc.c
    file_contention.c
    
