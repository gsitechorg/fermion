#include "common_api.h"

baryon_apuc_rsp_fifo_t apuc_rsp_fifo;
baryon_apuc_t apuc;
baryon_seu_layer_t seu_layer;

void baryon_init() {
  baryon_init_apuc_rsp_fifo(&apuc_rsp_fifo);
  baryon_init_apuc(&apuc, &apuc_rsp_fifo);
  baryon_init_seu_layer(&seu_layer);
}

void baryon_exit() {
  return;
}
