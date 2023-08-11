/* By Dylon Edwards
 *
 * Copyright 2019 - 2023 GSI Technology, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __GSI__BARYON__SIM_CONFIG_H__
#define __GSI__BARYON__SIM_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

struct gsi_sim_contexts {
    unsigned long long mem_size;
    unsigned int apu_count;
    unsigned int apucs_per_apu;
};

int gsi_sim_create_simulator(unsigned int num_ctxs,
                             struct gsi_sim_contexts *ctxs);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__SIM_CONFIG_H__
