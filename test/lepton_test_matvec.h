#ifndef __LEPTON_TEST_MATVEC_H__
#define __LEPTON_TEST_MATVEC_H__

#include <stddef.h>
#include <stdint.h>

#include <gsi/libsys.h>

struct common_dev_host {
  char buffer[64];
  uint16_t k;
  uint16_t n;
  uint64_t in_mem_hndl1;
  uint64_t in_mem_hndl2;
  uint64_t out_mem_hndl1;
  uint64_t counter;
} __attribute__((packed));

uint16_t r_analytic(size_t i);
void *increment_p_i16(void *p, uint32_t n32s);
uint16_t indirect_p_i16(void *p, uint32_t index32);
uint16_t *alloc_i16s(unsigned int count);
uint16_t *alloc_random_i16s(unsigned int count);
void initialize_A(uint32_t k, uint16_t *a);
void initialize_B(uint32_t k, uint32_t n, uint16_t *B);

gsi_prod_status_t lepton_test_matvec_device(void *in_buf, void *out_buf);
void lepton_test_matvec_host(void);
void lepton_test_matvec(void);

#endif // __LEPTON_TEST_MATVEC_H__
