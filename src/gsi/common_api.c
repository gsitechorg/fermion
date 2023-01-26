#include "common_api.h"

baryon_apuc_t apuc;
baryon_seu_layer_t seu_layer;

void baryon_init() {
  baryon_init_apuc(&apuc);
  baryon_init_seu_layer(&seu_layer);
}

void baryon_exit() {
  return;
}
