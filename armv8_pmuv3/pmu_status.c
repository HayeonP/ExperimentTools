#include <linux/module.h>

int init_module(void)
{
    printk("========================================\n");
    printk("[PMU Status]\n")

    u64 val=0;
    asm volatile("mrs %0, pmccfilter_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMCCFILTER_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmccntr_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMCCNTR_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmceid0_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMCEID0_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmceid1_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMCEID1_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmcntenclr_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMCNTENCLR_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmcntenset_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMCNTENSET_EL0", val, val);
    val=0;


    asm volatile("mrs %0, pmcr_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMCR_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevcntr0_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVCNTR0_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevcntr1_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVCNTR1_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevcntr2_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVCNTR2_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevcntr3_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVCNTR3_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevtyper0_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVTYPER0_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevtyper1_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVTYPER1_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevtyper2_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVTYPER2_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmevtyper3_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMEVTYPER3_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmintenclr_el1" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMINTENCLR_EL1", val, val);
    val=0;

    asm volatile("mrs %0, pmintenset_el1" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMINTENSET_EL1", val, val);
    val=0;

    asm volatile("mrs %0, pmovsclr_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMOVSCLR_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmovsset_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMOVSSET_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmselr_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMSELR_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmswinc_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMSWINC_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmuserenr_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMUSERENR_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmxevcntr_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMXEVCNTR_EL0", val, val);
    val=0;

    asm volatile("mrs %0, pmxevtyper_el0" : "=r" (val));
    printk("%s \t\t %X | %llu\n", "PMXEVTYPER_EL0", val, val);
    val=0;

    printk("========================================\n");
    

    return 0;
}

void cleanup_module(void)
{
    printk("Clean up pmu_status.\n");
}

MODULE_LICENSE("GPL");
