/**
 * commpage64
 * Copyright (C) 2017 NOP 0xe1a00000
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define COMM_PAGE64_BASE_ADDRESS        ( 0x00007fffffe00000ULL )
#define COMM_PAGE_CPU_CAPABILITIES64    ( COMM_PAGE64_BASE_ADDRESS + 0x010 )

const char *cpu_cap_strings[] = {
    "MMX",      // Bit 0
    "SSE",
    "SSE2",
    "SSE3",
    "Cache32",
    "Cache64",
    "Cache128",
    "FastThreadLocalStorage",
    "SupplementalSSE3",
    "64Bit",
    "SSE4_1",
    "SSE4_2",
    "AES",
    "InOrderPipeline",
    "Slow",
    "UP",       // Bit 15
    "NumCPUs",  // >> kNumCPUsShift
    "AVX1_0",   // Bit 24
    "RDRAND",
    "F16C",
    "ENFSTRG",
    "FMA",
    "AVX2_0",
    "BMI1",
    "BMI2",
    "RTM",      // Bit 32
    "HLE",
    "ADX",
    "RDSEED",
    "MPX",
    "SGX",      // Bit 37
};

char *
signature()
{
    char *signature = malloc(0x10);
    strlcpy(signature, (void *)COMM_PAGE64_BASE_ADDRESS, 0x10);
    
    return signature;
}

uint8_t
read_uint8(uint64_t address) {
    uint8_t value = ((uint8_t *)address)[0];
    return value;
}

uint16_t
read_uint16(uint64_t address) {
    uint16_t value = ((uint16_t *)address)[0];
    return value;
}

uint32_t
read_uint32(uint64_t address) {
    uint32_t value = ((uint32_t *)address)[0];
    return value;
}

uint64_t
read_uint64(uint64_t address) {
    uint64_t value = ((uint64_t *)address)[0];
    return value;
}

void dump_comm_page() {
    printf("[*] COMM_PAGE_SIGNATURE: %s\n", signature());
    printf("[*] COMM_PAGE_VERSION: %d\n", read_uint16(COMM_PAGE64_BASE_ADDRESS + 0x01E));
    printf("[*] COMM_PAGE_NCPUS: %d\n", read_uint8(COMM_PAGE64_BASE_ADDRESS + 0x022));
    printf("[*] COMM_PAGE_CACHE_LINESIZE: %d\n", read_uint16(COMM_PAGE64_BASE_ADDRESS + 0x026));
    printf("[*] COMM_PAGE_SCHED_GEN: %d\n", read_uint32(COMM_PAGE64_BASE_ADDRESS + 0x028));
    printf("[*] COMM_PAGE_MEMORY_PRESSURE: %d\n", read_uint32(COMM_PAGE64_BASE_ADDRESS + 0x02c));
    printf("[*] COMM_PAGE_SPIN_COUNT: %d\n", read_uint32(COMM_PAGE64_BASE_ADDRESS + 0x030));
    printf("[*] COMM_PAGE_KDEBUG_ENABLE: %d\n", read_uint32(COMM_PAGE64_BASE_ADDRESS + 0x044));
    printf("[*] COMM_PAGE_ATM_DIAGNOSTIC_CONFIG: %d\n", read_uint32(COMM_PAGE64_BASE_ADDRESS + 0x048));
    printf("[*] COMM_PAGE_BOOTTIME_USEC: %lld\n", read_uint64(COMM_PAGE64_BASE_ADDRESS + 0x0C8));
    printf("[*] COMM_PAGE_ACTIVE_CPUS: %d\n", read_uint8(COMM_PAGE64_BASE_ADDRESS + 0x034));
    printf("[*] COMM_PAGE_PHYSICAL_CPUS: %d\n", read_uint8(COMM_PAGE64_BASE_ADDRESS + 0x035));
    printf("[*] COMM_PAGE_LOGICAL_CPUS: %d\n", read_uint8(COMM_PAGE64_BASE_ADDRESS + 0x036));
    printf("[*] COMM_PAGE_MEMORY_SIZE: %lld\n", read_uint64(COMM_PAGE64_BASE_ADDRESS + 0x038));
    printf("[*] COMM_PAGE_CPUFAMILY: %d\n", read_uint32(COMM_PAGE64_BASE_ADDRESS + 0x040));
    printf("[*] COMM_PAGE_CPU_CAPABILITIES64:\n");
    
    uint64_t cpu_caps = read_uint64(COMM_PAGE_CPU_CAPABILITIES64);
    for (int i = 0, shift = 0; i < sizeof(cpu_cap_strings) / sizeof(void *); i++) {
        printf("\t%s: ", cpu_cap_strings[i]);
        if (shift == 16) {
            // Number of CPUs…
            printf("%d\n", (int)(cpu_caps & 0x00FF0000) >> 16);
            // Jump to next relevant bits…
            shift = 24;
            continue;
        }
        if (cpu_caps & (1ULL << shift)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
        shift++;
    }
}

int main(int argc, const char * argv[]) {
    dump_comm_page();

    return 0;
}
