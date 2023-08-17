/* By Dylon Edwards
 */

#include "rsp.h"

static int num_rsp_outstanding;

void rsp_outstanding_pushn(uint32_t count) {
  num_rsp_outstanding += count;
}

void rsp_outstanding_push() {
  rsp_outstanding_pushn(1);
}

void rsp_outstanding_pop(void) {
  num_rsp_outstanding--;
}
