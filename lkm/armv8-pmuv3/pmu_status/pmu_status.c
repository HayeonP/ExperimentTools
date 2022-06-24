#include <linux/module.h>
#include <linux/types.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c   %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c\n"

#define BYTE_TO_BINARY(byte) \
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

static int    param_cpu_id;
module_param(param_cpu_id    , int, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(param_cpu_id, "CPU ID that operations run on");

void print_status(void){
  u64 val=0;

  printk("[PMU Status - CPU %d]\n", get_cpu());

  // asm volatile("mrs %0, PMCCFILTER_EL0" : "=r" (val));
  // printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMCCFILTER_EL0", val, BYTE_TO_BINARY(val));
  // val=0;

  asm volatile("mrs %0, pmccntr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMCCNTR_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmceid0_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMCEID0_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmceid1_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMCEID1_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmcntenclr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMCNTENCLR_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmcntenset_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMCNTENSET_EL0", val, BYTE_TO_BINARY(val));
  val=0;


  asm volatile("mrs %0, pmcr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMCR_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevcntr0_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVCNTR0_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevcntr1_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVCNTR1_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevcntr2_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVCNTR2_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevcntr3_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVCNTR3_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevtyper0_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVTYPER0_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevtyper1_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVTYPER1_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevtyper2_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVTYPER2_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmevtyper3_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMEVTYPER3_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmintenclr_el1" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMINTENCLR_EL1", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmintenset_el1" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMINTENSET_EL1", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmovsclr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMOVSCLR_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmovsset_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMOVSSET_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmselr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMSELR_EL0", val, BYTE_TO_BINARY(val));
  val=0;
    
  asm volatile("mrs %0, pmuserenr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMUSERENR_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmxevcntr_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMXEVCNTR_EL0", val, BYTE_TO_BINARY(val));
  val=0;

  asm volatile("mrs %0, pmxevtyper_el0" : "=r" (val));
  printk("%s \t\t 0x%llX | "BYTE_TO_BINARY_PATTERN, "PMXEVTYPER_EL0", val, BYTE_TO_BINARY(val));
  val=0;
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