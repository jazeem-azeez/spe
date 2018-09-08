#if !defined ( __CPUID_H_ )
#define __CUPID_H_

/* CPUID structure */

typedef struct cpuid_s{
	char	vendor[13];
	double flags[4];
	double serial[4];
	double speed;
}__attribute__((packed)) cpuid_t;

extern void osdk_get_cpuid(cpuid_t *);

#endif
