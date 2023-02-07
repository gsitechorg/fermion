#include "common_api.h"

baryon_rsp32k_fifo_t rsp32k_fifo;
baryon_rsp2k_fifo_t rsp2k_fifo;
baryon_apuc_t apuc;
baryon_seu_layer_t seu_layer;

void baryon_init() {
  baryon_init_rsp32k_fifo(&rsp32k_fifo);
  baryon_init_rsp2k_fifo(&rsp2k_fifo);
  baryon_init_apuc(&apuc, &rsp32k_fifo, &rsp2k_fifo);
  baryon_init_seu_layer(&seu_layer);
}

void baryon_exit() {
  return;
}
