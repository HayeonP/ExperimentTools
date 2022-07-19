#include <linux/module.h>
#include <linux/types.h>

#define BYTE_TO_32_BINARY_PATTERN "%c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c   %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c\n"
#define BYTE_TO_64_BINARY_PATTERN "%c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c   %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c   %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c   %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c\n"

#define BYTE_TO_32_BINARY(byte) \
  (byte & 0x80000000 ? '1' : '0'), \
  (byte & 0x40000000 ? '1' : '0'), \
  (byte & 0x20000000 ? '1' : '0'), \
  (byte & 0x10000000 ? '1' : '0'), \
  (byte & 0x08000000 ? '1' : '0'), \
  (byte & 0x04000000 ? '1' : '0'), \
  (byte & 0x02000000 ? '1' : '0'), \
  (byte & 0x01000000 ? '1' : '0'), \
  (byte & 0x00800000 ? '1' : '0'), \
  (byte & 0x00400000 ? '1' : '0'), \
  (byte & 0x00200000 ? '1' : '0'), \
  (byte & 0x00100000 ? '1' : '0'), \
  (byte & 0x00080000 ? '1' : '0'), \
  (byte & 0x00040000 ? '1' : '0'), \
  (byte & 0x00020000 ? '1' : '0'), \
  (byte & 0x00010000 ? '1' : '0'), \
  (byte & 0x00008000 ? '1' : '0'), \
  (byte & 0x00004000 ? '1' : '0'), \
  (byte & 0x00002000 ? '1' : '0'), \
  (byte & 0x00001000 ? '1' : '0'), \
  (byte & 0x00000800 ? '1' : '0'), \
  (byte & 0x00000400 ? '1' : '0'), \
  (byte & 0x00000200 ? '1' : '0'), \
  (byte & 0x00000100 ? '1' : '0'), \
  (byte & 0x00000080 ? '1' : '0'), \
  (byte & 0x00000040 ? '1' : '0'), \
  (byte & 0x00000020 ? '1' : '0'), \
  (byte & 0x00000010 ? '1' : '0'), \
  (byte & 0x00000008 ? '1' : '0'), \
  (byte & 0x00000004 ? '1' : '0'), \
  (byte & 0x00000002 ? '1' : '0'), \
  (byte & 0x00000001 ? '1' : '0') 

#define BYTE_TO_64_BINARY(byte) \
  (byte & 0x8000000000000000 ? '1' : '0'), \
  (byte & 0x4000000000000000 ? '1' : '0'), \
  (byte & 0x2000000000000000 ? '1' : '0'), \
  (byte & 0x1000000000000000 ? '1' : '0'), \
  (byte & 0x0800000000000000 ? '1' : '0'), \
  (byte & 0x0400000000000000 ? '1' : '0'), \
  (byte & 0x0200000000000000 ? '1' : '0'), \
  (byte & 0x0100000000000000 ? '1' : '0'), \
  (byte & 0x0080000000000000 ? '1' : '0'), \
  (byte & 0x0040000000000000 ? '1' : '0'), \
  (byte & 0x0020000000000000 ? '1' : '0'), \
  (byte & 0x0010000000000000 ? '1' : '0'), \
  (byte & 0x0008000000000000 ? '1' : '0'), \
  (byte & 0x0004000000000000 ? '1' : '0'), \
  (byte & 0x0002000000000000 ? '1' : '0'), \
  (byte & 0x0001000000000000 ? '1' : '0'), \
  (byte & 0x0000800000000000 ? '1' : '0'), \
  (byte & 0x0000400000000000 ? '1' : '0'), \
  (byte & 0x0000200000000000 ? '1' : '0'), \
  (byte & 0x0000100000000000 ? '1' : '0'), \
  (byte & 0x0000080000000000 ? '1' : '0'), \
  (byte & 0x0000040000000000 ? '1' : '0'), \
  (byte & 0x0000020000000000 ? '1' : '0'), \
  (byte & 0x0000010000000000 ? '1' : '0'), \
  (byte & 0x0000008000000000 ? '1' : '0'), \
  (byte & 0x0000004000000000 ? '1' : '0'), \
  (byte & 0x0000002000000000 ? '1' : '0'), \
  (byte & 0x0000001000000000 ? '1' : '0'), \
  (byte & 0x0000000800000000 ? '1' : '0'), \
  (byte & 0x0000000400000000 ? '1' : '0'), \
  (byte & 0x0000000200000000 ? '1' : '0'), \
  (byte & 0x0000000100000000 ? '1' : '0'), \
  (byte & 0x0000000080000000 ? '1' : '0'), \
  (byte & 0x0000000040000000 ? '1' : '0'), \
  (byte & 0x0000000020000000 ? '1' : '0'), \
  (byte & 0x0000000010000000 ? '1' : '0'), \
  (byte & 0x0000000008000000 ? '1' : '0'), \
  (byte & 0x0000000004000000 ? '1' : '0'), \
  (byte & 0x0000000002000000 ? '1' : '0'), \
  (byte & 0x0000000001000000 ? '1' : '0'), \
  (byte & 0x0000000000800000 ? '1' : '0'), \
  (byte & 0x0000000000400000 ? '1' : '0'), \
  (byte & 0x0000000000200000 ? '1' : '0'), \
  (byte & 0x0000000000100000 ? '1' : '0'), \
  (byte & 0x0000000000080000 ? '1' : '0'), \
  (byte & 0x0000000000040000 ? '1' : '0'), \
  (byte & 0x0000000000020000 ? '1' : '0'), \
  (byte & 0x0000000000010000 ? '1' : '0'), \
  (byte & 0x0000000000008000 ? '1' : '0'), \
  (byte & 0x0000000000004000 ? '1' : '0'), \
  (byte & 0x0000000000002000 ? '1' : '0'), \
  (byte & 0x0000000000001000 ? '1' : '0'), \
  (byte & 0x0000000000000800 ? '1' : '0'), \
  (byte & 0x0000000000000400 ? '1' : '0'), \
  (byte & 0x0000000000000200 ? '1' : '0'), \
  (byte & 0x0000000000000100 ? '1' : '0'), \
  (byte & 0x0000000000000080 ? '1' : '0'), \
  (byte & 0x0000000000000040 ? '1' : '0'), \
  (byte & 0x0000000000000020 ? '1' : '0'), \
  (byte & 0x0000000000000010 ? '1' : '0'), \
  (byte & 0x0000000000000008 ? '1' : '0'), \
  (byte & 0x0000000000000004 ? '1' : '0'), \
  (byte & 0x0000000000000002 ? '1' : '0'), \
  (byte & 0x0000000000000001 ? '1' : '0')

static int    param_cpu_id;
module_param(param_cpu_id    , int, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(param_cpu_id, "CPU ID that operations run on");

void print_status(void){
  u64 val=0;

  printk("[PMU Status - CPU %d]\n", get_cpu());

  // asm volatile("mrs %0, PMCCFILTER_EL0" : "=r" (val));
  // printk("%s \t\t 0x%llX | "BYTE_TO_32_BINARY_PATTERN, "PMCCFILTER_EL0", val, BYTE_TO_32_BINARY(val));
  // val=0;

  asm volatile("mrs %0, ctr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_32_BINARY_PATTERN, "CTR_EL0", val, BYTE_TO_32_BINARY(val));
  val=0;

  asm volatile("mrs %0, clidr_el1" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_64_BINARY_PATTERN, "CLIDR_EL1", val, BYTE_TO_64_BINARY(val));
  val=0;

  asm volatile("mrs %0, sctlr_el1" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_32_BINARY_PATTERN, "SCTLR_EL1", val, BYTE_TO_32_BINARY(val));
  val=0;

  // asm volatile("mrs %0, hcr_el2" : "=r" (val));
  // printk("%s \t\t 0x%llX | "BYTE_TO_32_BINARY_PATTERN, "HCR_EL2", val, BYTE_TO_32_BINARY(val));
  // val=0;
}

int init_module(void)
{
  int i;

  printk("========================================\n");
  
  for_each_online_cpu(i){
    smp_call_function_single(i, (void *)print_status, NULL, 1);
  }

  printk("========================================\n");

  return 0;
}

void cleanup_module(void)
{
    printk("Clean up pmu_status.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HayeonP");
MODULE_DESCRIPTION("Print pmu status log of every cores");