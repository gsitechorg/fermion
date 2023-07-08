#include "common_api.h"

baryon_apuc_rsp_fifo_t apuc_rsp_fifo;
baryon_apuc_t apuc;
baryon_seu_layer_t seu_layer;

// Temporaries for SRC variants
baryon_rl_t src_rl;        // (INV_)?([NEWS]_)?RL
baryon_gl_t src_gl;        // (INV_)?GL
baryon_ggl_t src_ggl;      // (INV_)?GGL
baryon_rsp16_t src_rsp16;  // (INV_)?RSP16

void baryon_init() {
  baryon_init_apuc_rsp_fifo(&apuc_rsp_fifo);
  baryon_init_apuc(&apuc, &apuc_rsp_fifo);
  baryon_init_seu_layer(&seu_layer);
}

void baryon_exit() {
  return;
}
