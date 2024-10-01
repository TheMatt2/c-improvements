// Min / Max function that only evaluates its values once
#define MIN(a, b) ({ \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a <= _b ? _a : _b; \
})

#define MAX(a, b) ({ \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; \
})

// Macro to get number of elements in array
#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

// Macro to put quotes around a macro
#define XSTR(x) #x
#define STR(x) XSTR(x)

/* Define thread_local for thread specific buffer */
#if __STDC_VERSION__ <= 199901L
#define thread_local __thread
#elif __STDC_VERSION__ < 202311L
// C23 changes thread_local to be a keyword
#define thread_local _Thread_local
#endif
