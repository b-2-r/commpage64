# commpage64
Dumps the content of a 64-bit comm page (macOS).

### Sample Session
```
$ uname -a
Darwin nop.local 16.6.0 Darwin Kernel Version 16.6.0: Fri Apr 14 16:21:16 PDT 2017; root:xnu-3789.60.24~6/RELEASE_X86_64 x86_64
$ ./commpage64
[*] COMM_PAGE_SIGNATURE: commpage 64-bit
[*] COMM_PAGE_VERSION: 13
[*] COMM_PAGE_NCPUS: 8
[*] COMM_PAGE_CACHE_LINESIZE: 64
[*] COMM_PAGE_SCHED_GEN: 27530712
[*] COMM_PAGE_MEMORY_PRESSURE: 0
[*] COMM_PAGE_SPIN_COUNT: 1
[*] COMM_PAGE_KDEBUG_ENABLE: 0
[*] COMM_PAGE_ATM_DIAGNOSTIC_CONFIG: 1
[*] COMM_PAGE_BOOTTIME_USEC: 1500274845171977
[*] COMM_PAGE_ACTIVE_CPUS: 8
[*] COMM_PAGE_PHYSICAL_CPUS: 4
[*] COMM_PAGE_LOGICAL_CPUS: 8
[*] COMM_PAGE_MEMORY_SIZE: 17179869184
[*] COMM_PAGE_CPUFAMILY: 280134364
[*] COMM_PAGE_CPU_CAPABILITIES64:
	MMX: true
	SSE: true
	SSE2: true
	SSE3: true
	Cache32: false
	Cache64: true
	Cache128: false
	FastThreadLocalStorage: true
	SupplementalSSE3: true
	64Bit: true
	SSE4_1: true
	SSE4_2: true
	AES: true
	InOrderPipeline: false
	Slow: false
	UP: false
	NumCPUs: 8
	AVX1_0: true
	RDRAND: true
	F16C: true
	ENFSTRG: true
	FMA: true
	AVX2_0: true
	BMI1: true
	BMI2: true
	RTM: true
	HLE: true
	ADX: true
	RDSEED: false
	MPX: false
	SGX: false
[*] Done dumping comm page.
```
