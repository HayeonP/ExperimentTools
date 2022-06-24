#include <linux/module.h>
#include <linux/types.h>
#include "pmu_events.h"

#define ARMV8_PMUSERENR_EL0_EN (1 << 0)         // Enable accesses of all counters in user-space
#define ARMV8_PMUSERENR_EL0_CR (1 << 2)         // Cycle counter
#define ARMV8_PMUSERENR_EL0_ER (1 << 3)         // Event counter

#define ARMV8_PMCNTENSET_EL0_C (1 << 31)        // Enable cycle counter
#define ARMV8_PMCNTENSET_EL0_N(n) (1 << n)      // Enable event counter

#define ARMV8_PMCR_EL0_E (1 << 0)               // Enable all counters

static u64 event_ary[4] = {0, 0, 0, 0};

void enable_pmu_access(void){
    u64 val=0;

    /* Enable user-mode access to counters. */
    // asm volatile("msr pmuserenr_el0, %0" : : "r"((u64)ARMV8_PMUSERENR_EL0_EN|ARMV8_PMUSERENR_EL0_ER|ARMV8_PMUSERENR_EL0_CR));

    /* Enable cycle counter and event counter 0-3 */ 
    asm volatile("msr pmcntenset_el0, %0" : : "r" (ARMV8_PMCNTENSET_EL0_C|ARMV8_PMCNTENSET_EL0_N(0)|ARMV8_PMCNTENSET_EL0_N(1)|ARMV8_PMCNTENSET_EL0_N(2)|ARMV8_PMCNTENSET_EL0_N(3)));

    /* Enable all counters */
    asm volatile("mrs %0, pmcr_el0" : "=r" (val));
    asm volatile("msr pmcr_el0, %0" : : "r" (val|ARMV8_PMCR_EL0_E));

    /* Select event to event counter 0~3 */
    asm volatile("isb"); // Instruction synchronization

    asm volatile("mrs %0, pmevtyper0_el0" : "=r" (event_ary[0]));
    asm volatile("mrs %0, pmevtyper1_el0" : "=r" (event_ary[1]));
    asm volatile("mrs %0, pmevtyper2_el0" : "=r" (event_ary[2]));
    asm volatile("mrs %0, pmevtyper3_el0" : "=r" (event_ary[3]));

    asm volatile("msr pmevtyper0_el0, %0" : : "r" (event_ary[0]|ARMV8_L2D_CACHE_REFILL));
    asm volatile("msr pmevtyper1_el0, %0" : : "r" (event_ary[1]|ARMV8_L2I_CACHE_REFILL));
    asm volatile("msr pmevtyper2_el0, %0" : : "r" (event_ary[2]|ARMV8_L3D_CACHE_REFILL));
    asm volatile("msr pmevtyper3_el0, %0" : : "r" (event_ary[3]|ARMV8_LL_CACHE_MISS_RD));
}

void disable_pmu_access(void){
    u64 val=0, event=0;

    /* Disable user-mode access to counters. */
    asm volatile("msr pmuserenr_el0, %0" : : "r"(0));

    /* Disable cycle counter and event counter 0 */ 
    // asm volatile("msr pmcntenset_el0, %0" : : "r" (0));

    /* Disable all counters */
    asm volatile("mrs %0, pmcr_el0" : "=r" (val));
    asm volatile("msr pmcr_el0, %0" : : "r" (val & 0x0000));



    /* Disable selection register */
    asm volatile("isb"); // Instruction synchronization

    asm volatile("msr pmselr_el0, %0" : : "r" (0)); 
    asm volatile("mrs %0, pmxevtyper_el0" : "=r" (event));
    asm volatile("msr pmxevtyper_el0, %0" : : "r" (event & !ARMV8_LL_CACHE_MISS));
    
    asm volatile("msr pmevcntr0_el0, %0" : : "r" (0));
    asm volatile("msr pmevcntr1_el0, %0" : : "r" (0));
    asm volatile("msr pmevcntr2_el0, %0" : : "r" (0));
    asm volatile("msr pmevcntr3_el0, %0" : : "r" (0));
    asm volatile("msr pmevtyper0_el0, %0" : : "r" (0));
    asm volatile("msr pmevtyper1_el0, %0" : : "r" (0));
    asm volatile("msr pmevtyper2_el0, %0" : : "r" (0));
    asm volatile("msr pmevtyper3_el0, %0" : : "r" (0));

}

int init_module(void)
{
    int i;

    printk("Enable PMU access.\n");
    for_each_online_cpu(i){
        smp_call_function_single(i, (void *)enable_pmu_access, NULL, 1);
    }

    return 0;
}

void cleanup_module(void)
{
    int i;
    printk("Clean up pmu access.\n");

    for_each_online_cpu(i){
        smp_call_function_single(i, (void *)disable_pmu_access, NULL, 1);
    }
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HayeonP");
MODULE_DESCRIPTION("Enable pmu access on every cores");