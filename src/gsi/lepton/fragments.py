from belex.kernel_libs.memory import (copy_l1_to_l2_byte, copy_l2_to_l1_byte,
                                      l2_end, load_16_t0, store_16_t0)

from belex.literal import VR, Mask, belex_apl
from belex_libs.arithmetic import (_3to2_mul_16_7tmp,
                                   _3to2_mul_16_7tmp_iter_msk_13,
                                   _3to2_mul_16_7tmp_last, add_u16, init_mul_16_7tmp,
                                   mul_u16_u16xu16_7t)
from belex_libs.common import cpy_imm_16
