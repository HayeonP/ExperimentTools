/* PMU events */

/* 0 ~ 3 */
#define ARMV8_SW_INCR                   0x0000
#define ARMV8_L1I_CACHE_REFILL          0x0001
#define ARMV8_L1I_TLB_REFILL            0x0002
#define ARMV8_L1D_CACHE_REFILL          0x0003

/* 4 ~ 7 */
#define ARMV8_L1D_CACHE                 0x0004
#define ARMV8_L1D_TLB_REFILL            0x0005
#define ARMV8_LD_RETIRED                0x0006  // Not working
#define ARMV8_ST_RETIRED                0x0007  // Not working

/* 8 ~ 11 */
#define ARMV8_INST_RETIRED              0x0008
#define ARMV8_EXC_TAKEN                 0x0009
#define ARMV8_EXC_RETURN                0x000A
#define ARMV8_CID_WRITE_RETIRED         0x000B

/* 12 ~ 15 */
#define ARMV8_PC_WRITE_RETIRED          0x000C  // Not working
#define ARMV8_BR_IMMED_RETIRED          0x000D  // Not working
#define ARMV8_BR_RETURN_RETIRED         0x000E  // Not working
#define ARMV8_UNALIGNED_LDST_RETIRED    0x000F  // Not working

/* 16 ~ 19 */
#define ARMV8_BR_MIS_PRED               0x0010
#define ARMV8_CPU_CYCLES                0x0011
#define ARMV8_BR_PRED                   0x0012
#define ARMV8_MEM_ACCESS                0x0013

/* 20 ~ 23 */
#define ARMV8_L1I_CACHE                 0x0014
#define ARMV8_L1D_CACHE_WB              0x0015
#define ARMV8_L2D_CACHE                 0x0016
#define ARMV8_L2D_CACHE_REFILL          0x0017

/* 24 ~ 27 */
#define ARMV8_L2D_CACHE_WB              0x0018
#define ARMV8_BUS_ACCESS                0x0019
#define ARMV8_MEMORY_ERROR              0x001A
#define ARMV8_INST_SPEC                 0x001B

/* 28 ~ 31 */
#define ARMV8_TTBR_WRITE_RETIRED        0x001C  // Not working
#define ARMV8_BUS_CYCLES                0x001D
#define ARMV8_CHAIN                     0x001E
#define ARMV8_L1D_CACHE_ALLOCATE        0x001F

/* 32 ~ 35 */
#define ARMV8_L2D_CACHE_ALLOCATE        0x0020
#define ARMV8_BR_RETIRED                0x0021
#define ARMV8_BR_MIS_PRED_RETIRED       0x0022
#define ARMV8_STALL_FRONTEND            0x0023

/* 36 ~ 39 */
#define ARMV8_STALL_BACKEND             0x0024
#define ARMV8_L1D_TLB                   0x0025
#define ARMV8_L1I_TLB                   0x0026
#define ARMV8_L2I_CACHE                 0x0027  // Not working

/* 40 ~ 43 */
#define ARMV8_L2I_CACHE_REFILL          0x0028  // Not working
#define ARMV8_L3D_CACHE_ALLOCATE        0x0029
#define ARMV8_L3D_CACHE_REFILL          0x002A
#define ARMV8_L3D_CACHE                 0x002B

/* 44 ~ 47 */
#define ARMV8_L3D_CACHE_WB              0x002C
#define ARMV8_L2D_TLB_REFILL            0x002D
#define ARMV8_L2I_TLB_REFILL            0x002E  // Not working
#define ARMV8_L2D_TLB                   0x002F

/* 48 ~ 51 */
#define ARMV8_L2I_TLB                   0x0030  // Not working
#define ARMV8_REMOTE_ACCESS             0x0031  // Not working
#define ARMV8_LL_CACHE                  0x0032  // Not working
#define ARMV8_LL_CACHE_MISS             0x0033  // Not working

/* 52 ~ 55 */
#define ARMV8_DTLB_WALK                 0x0034  // Not working
#define ARMV8_ITLB_WALK                 0x0035  // Not working
#define ARMV8_LL_CACHE_RD               0x0036  // Not working
#define ARMV8_LL_CACHE_MISS_RD          0x0037  // Not working

/* 56 ~ 59 */
#define ARMV8_REMOTE_ACCESS_RD          0x0038  // Not working