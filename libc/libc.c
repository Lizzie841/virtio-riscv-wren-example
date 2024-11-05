#include "stdio.h"
#include "wren.h"
#include "wren_vm.h"

volatile unsigned char * uart = (volatile unsigned char *)0x10000000; 
void write_fn(WrenVM* vm, const char* str) {
	while(*str != '\0') {
		*uart = *str++;
	}
}
void error_fn(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message) {
	while(*message != '\0') {
		*uart = *message++;
	}
}
void kmain(void) {
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.writeFn = &write_fn;
    config.errorFn = &error_fn;
    WrenVM* vm = wrenNewVM(&config);
    const char* module = "main";
    const char* script = "System.print(\"I am running in a VM!\")";
    wrenInterpret(vm, module, script);
	while(1) {
		// Read input from the UART
		*uart;
	}
#if 0
    wrenFreeVM(vm);
#endif
	return;
}

#define assert(x) { if(!(x)) { write_fn(NULL, __FILE__ ": " #x); while(1); } }

int errno = 0;

double strtod(const char *s, char **end) {
    //assert(0);
    return 0;
}
long long strtoll(const char *nptr, char **endptr, int base) {
    //assert(0);
    return 0;
}

int isspace(int c) {
    return c == ' ' || c == '\t';
}

/* each node is 512 bytes */
#define MM_BLOCK_SIZE (256)
#define MM_BLOCK_COUNT (8192)
static uint8_t heap[MM_BLOCK_COUNT * MM_BLOCK_COUNT] = { 0 };
static void* heap_tag[MM_BLOCK_COUNT] = { 0 };
static WrenVM g_wrenVm = { 0 };

void *realloc(void *p, size_t n) {
    if(p == NULL && n == sizeof(WrenVM)) {
        return &g_wrenVm;
    }

    //assert(n < 4096);

    if(p != NULL) {
        for(size_t i = 0; i < MM_BLOCK_COUNT; i++) {
            if(heap_tag[i] == p) {
                heap_tag[i] = NULL;
            }
        }
    }
    for(size_t i = 0; i < MM_BLOCK_COUNT; i++) {
        if(heap_tag[i] == NULL) {
            int do_alloc = 1;
            for(size_t j = 0; j < (n / MM_BLOCK_SIZE) + 1; j++) {
                if(heap_tag[i + j] != NULL) {
                    do_alloc = 0;
                    break;
                }
            }
            if(do_alloc) {
                void *old_p = p;
                p = &heap[i * MM_BLOCK_SIZE];
                if(old_p != NULL) {
                    memmove(p, old_p, n);
                }
                for(size_t j = 0; j < (n / MM_BLOCK_SIZE) + 1; j++) {
                    assert(i + j < MM_BLOCK_COUNT);
                    heap_tag[i + j] = p;
                }
                assert(heap_tag[i] == p);
                return p;
            }
        }
    }
    assert(0);
    return NULL;
}
void free(void *p) {
    for(size_t i = 0; i < MM_BLOCK_COUNT; i++) {
        if(heap_tag[i] == p) {
            heap_tag[i] = NULL;
        }
    }
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *dp = (uint8_t *)dest;
    const uint8_t *sp = (const uint8_t *)src;
    if(sp < dp && sp + n > dp){
        sp += n;
        dp += n;
        while(n-- > 0){
            *--dp = *--sp;
        }
    } else {
        while(n-- > 0){
            *dp++ = *sp++;
        }
    }
    return dest;
}
void *memset(void *s, int c, size_t n) {
    uint8_t *dp = (uint8_t *)s;
    while(n-- > 0) {
        *dp++ = c;
    }
    return s;
}
void *memcpy(void *s1, const void *s2, unsigned long n) {
    uint8_t *dp = (uint8_t *)s1;
    const uint8_t *sp = (const uint8_t *)s2;
    while(n-- > 0) {
        *dp++ = *sp++;
    }
    return s1;
}
int memcmp(const void *s1, const void *s2, size_t n) {
    uint8_t *dp = (uint8_t *)s1;
    const uint8_t *sp = (const uint8_t *)s2;
    while(n-- > 0) {
        if(*dp++ != *sp++) {
            return 1;
        }
    }
    return 0;
}

int printf(const char *fmt, ...) {
    write_fn(NULL, fmt);
    return 0;
}
int sprintf(char *s, const char *fmt, ...) {
    write_fn(NULL, fmt);
    return 0;
}
int vsprintf(char *s, const char *fmt, va_list *arg) {
    write_fn(NULL, fmt);
    return 0;
}

int strcmp(const char *s1, const char *s2) {
    while(*s1 && *s2) {
        if(*s1 != *s2)
            return 1;
    }
    return 0;
}
int strncmp(const char *s1, const char *s2, size_t n) {
    while(n-- > 0 && *s1 && *s2) {
        if(*s1 != *s2)
            return 1;
    }
    return 0;
}
size_t strlen(const char *s) {
    size_t i = 0;
    for(; *s++; ++i)
        ;
    return i;
}

int clock() {
    return 0;
}

double fmax(double x, double y) {
    return x > y ? x : y;
}
double fmin(double x, double y) {
    return x < y ? x : y;
}
float trunc(float x) {
    return (float)((int)x);
}
int isnan(double x) {
    return 0;
}
int isinf(double x) {
    return 0;
}
double modf(double x, double *iptr) {
    return 0;
}
double atan2(double x, double y) {
    return 0;
}
double pow(double x, double y) {
    return 0;
}
double fmod(double x, double y) {
    return 0;
}
double exp(double x) {
    return 0;
}
double log(double x) {
    return 0;
}
double log2(double x) {
    return 0;
}
double asin(double x) {
    return 0;
}
double acos(double x) {
    return 0;
}
double atan(double x) {
    return 0;
}
double sin(double x) {
    return 0;
}
double cos(double x) {
    return 0;
}
double tan(double x) {
    return 0;
}
double sqrt(double x) {
    return 0;
}
double ceil(double x) {
    return (double)((int)x);
}
double floor(double x) {
    return (double)((int)x);
}
double abs(double x) {
    return x > 0 ? x : -x;
}
double fabs(double x) {
    return x > 0 ? x : -x;
}
double round(double x) {
    return (double)((int)x);
}
double cbrt(double x) {
    return 0;
}
