# Baryon Simulator

Native (C) simulators for the Bit-Engine Language of Expressions (Belex) of GSI's APU.

## Initializing the Environment

```shell
mamba env create --force -f environment.yml
conda activate baryon
```

## Building

The basic command for building `libgsi-baryon-gvml.a` and `libgsi-baryon-sys.a` follows:

```
$ ./setup.sh --clean
~/Workspace/fermion/build ~/Workspace/fermion
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
belex-aot: /home/dylon/.pyenv/shims/belex-aot
Configuration results
---------------------
C compiler      : /usr/bin/cc
Build type: Debug
C compiler flags      : -g
Installation prefix: /usr/local
-- Configuring done
-- Generating done
-- Build files have been written to: /home/dylon/Workspace/fermion/build
[  6%] Generating gensrc/gsi/gvml_fragments.c, gensrc/gsi/gvml_fragments.h
[ 12%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/operations.c.o
[ 18%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/fifo.c.o
[ 25%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/apuc.c.o
[ 31%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/seu_layer.c.o
[ 37%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/common_api.c.o
[ 43%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libapl.c.o
[ 50%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgal.c.o
[ 56%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgdl.c.o
[ 62%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libsys.c.o
[ 68%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/gsi_sim_config.c.o
[ 75%] Linking C static library libgsi-baryon-sys.a
[ 75%] Built target gsi-baryon-sys
[ 81%] Building C object CMakeFiles/gsi-baryon-gvml.dir/gensrc/gsi/gvml_fragments.c.o
[ 87%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/libgvml.c.o
[ 93%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/rsp.c.o
[100%] Linking C static library libgsi-baryon-gvml.a
[100%] Built target gsi-baryon-gvml

$ ls -1 build/*.a
build/libgsi-baryon-gvml.a
build/libgsi-baryon-sys.a
```

To build and install the libs to a package root, append `--prefix $PREFIX` and `--install` as follows, where `$PREFIX` is the installation prefix (e.g. the `$CONDA_PREFIX` of some conda env):

```
$ ./setup.sh --clean --prefix ~/Workspace/belex-tests/venv --install
~/Workspace/fermion/build ~/Workspace/fermion
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
belex-aot: /home/dylon/.pyenv/shims/belex-aot
Configuration results
---------------------
C compiler      : /usr/bin/cc
Build type: Debug
C compiler flags      : -g
Installation prefix: /home/dylon/Workspace/belex-tests/venv
-- Configuring done
-- Generating done
-- Build files have been written to: /home/dylon/Workspace/fermion/build
[  6%] Generating gensrc/gsi/gvml_fragments.c, gensrc/gsi/gvml_fragments.h
[ 18%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/operations.c.o
[ 18%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/fifo.c.o
[ 25%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/apuc.c.o
[ 31%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/seu_layer.c.o
[ 37%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/common_api.c.o
[ 43%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libapl.c.o
[ 50%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgal.c.o
[ 56%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgdl.c.o
[ 62%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libsys.c.o
[ 68%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/gsi_sim_config.c.o
[ 75%] Linking C static library libgsi-baryon-sys.a
[ 75%] Built target gsi-baryon-sys
[ 81%] Building C object CMakeFiles/gsi-baryon-gvml.dir/gensrc/gsi/gvml_fragments.c.o
[ 87%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/rsp.c.o
[ 93%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/libgvml.c.o
[100%] Linking C static library libgsi-baryon-gvml.a
[100%] Built target gsi-baryon-gvml
~/Workspace/fermion
~/Workspace/fermion/build ~/Workspace/fermion
[ 68%] Built target gsi-baryon-sys
[100%] Built target gsi-baryon-gvml
Install the project...
-- Install configuration: "Debug"
-- Installing: /home/dylon/Workspace/belex-tests/venv/lib/libgsi-baryon-sys.a
-- Installing: /home/dylon/Workspace/belex-tests/venv/lib/libgsi-baryon-gvml.a
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/__pycache__
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgvml_memory.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgal.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/gsi_sim_config.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgvml_element_wise.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/__pycache__
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/seu_layer.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/operations.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/fifo.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/apuc.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/constants.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgvml.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/gal-fast-funcs.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/rsp.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgdl.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/common_api.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libapl.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/libc.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/assert.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/types.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/log.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/error.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/debug.h
~/Workspace/fermion
You may wish to export the following for CMake dependencies:

    export CMAKE_PREFIX_PATH="/home/dylon/Workspace/belex-tests/venv"

```

## Testing

Testing is trivial, just run:

```
$ ./setup.sh --clean --test
~/Workspace/fermion/build ~/Workspace/fermion
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
belex-aot: /home/dylon/mambaforge/envs/baryon/bin/belex-aot
Configuration results
---------------------
C compiler      : /usr/bin/cc
Build type: Debug
C compiler flags      : -g
Installation prefix: /usr/local
-- Configuring done
-- Generating done
-- Build files have been written to: /home/dylon/Workspace/fermion/build
[  1%] Generating gensrc/gsi/gvml_fragments.c, gensrc/gsi/gvml_fragments.h
[  2%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/fifo.c.o
[  3%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/operations.c.o
[  4%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/apuc.c.o
[  5%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/seu_layer.c.o
[  6%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/common_api.c.o
[  7%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libapl.c.o
[  8%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgal.c.o
[ 10%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgdl.c.o
[ 11%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libsys.c.o
[ 12%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/gsi_sim_config.c.o
[ 12%] Built target copy-rapidcheck-config
[ 13%] Linking C static library libgsi-baryon-sys.a
[ 13%] Built target gsi-baryon-sys
[ 14%] Building C object CMakeFiles/gsi-baryon-gvml.dir/gensrc/gsi/gvml_fragments.c.o
[ 15%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/libgvml.c.o
[ 16%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/rsp.c.o
[ 17%] Linking C static library libgsi-baryon-gvml.a
[ 17%] Built target gsi-baryon-gvml
[ 19%] Building CXX object test/CMakeFiles/test-baryon.dir/rapidcheck_parser.cpp.o
[ 20%] Building CXX object test/CMakeFiles/test-baryon.dir/test_matvec.cpp.o
[ 21%] Building CXX object test/CMakeFiles/test-baryon.dir/test_baryon.cpp.o
[ 22%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/fixtures.cpp.o
[ 23%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_init.cpp.o
[ 24%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_add_u16.cpp.o
[ 25%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_cpy_imm_16.cpp.o
[ 26%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_mul_u16.cpp.o
[ 28%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_store_load_16.cpp.o
[ 29%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_libgal.cpp.o
[ 30%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_store_load_vmr_16.cpp.o
[ 32%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/generators.cpp.o
[ 31%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/comparators.cpp.o
[ 33%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/fixtures.cpp.o
[ 35%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/utils.cpp.o
[ 35%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_apuc.cpp.o
[ 37%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_ggl_from_rl.cpp.o
[ 38%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_ggl_from_rl_and_l1.cpp.o
[ 39%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_l1_from_lgl.cpp.o
[ 40%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_l1_from_ggl.cpp.o
[ 41%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_l2_from_lgl.cpp.o
[ 42%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_lgl_from_l1.cpp.o
[ 43%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_gl_from_rl.cpp.o
[ 44%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_ggl_from_l1.cpp.o
[ 46%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_brsp16.cpp.o
[ 47%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_operations.cpp.o
[ 48%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_lgl_from_l2.cpp.o
[ 49%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_inv_sb.cpp.o
[ 50%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_inv_src.cpp.o
[ 51%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_sb_and_inv_src.cpp.o
[ 52%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_sb_and_src.cpp.o
[ 53%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_sb.cpp.o
[ 55%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_sb.cpp.o
[ 56%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_sb_and_inv_src.cpp.o
[ 57%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_src.cpp.o
[ 58%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_sb_and_src.cpp.o
[ 59%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_src.cpp.o
[ 60%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb.cpp.o
[ 61%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_and_inv_src.cpp.o
[ 62%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_and_src.cpp.o
[ 64%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_or_inv_src.cpp.o
[ 65%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_or_src.cpp.o
[ 66%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_xor_inv_src.cpp.o
[ 67%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_src.cpp.o
[ 68%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_xor_src.cpp.o
[ 69%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_inv_src.cpp.o
[ 70%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_sb.cpp.o
[ 71%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_sb_and_inv_src.cpp.o
[ 73%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_sb_and_src.cpp.o
[ 74%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_src.cpp.o
[ 75%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_inv_src.cpp.o
[ 76%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_sb.cpp.o
[ 77%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_sb_and_src.cpp.o
[ 78%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_sb_and_inv_src.cpp.o
[ 79%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_src.cpp.o
[ 80%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp16_from_rl.cpp.o
[ 83%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp256_from_rsp16.cpp.o
[ 83%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp16_from_rsp256.cpp.o
[ 84%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp256_from_rsp2k.cpp.o
[ 85%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp2k_from_rsp256.cpp.o
[ 86%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp2k_from_rsp32k.cpp.o
[ 87%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp32k_from_rsp2k.cpp.o
[ 88%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp_end.cpp.o
[ 89%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp_fifo.cpp.o
[ 92%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_cond_eq_inv_src.cpp.o
[ 92%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rwinh.cpp.o
[ 93%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_cond_eq_src.cpp.o
[ 94%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_from_inv_src.cpp.o
[ 95%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_from_src.cpp.o
[ 96%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_set_rl.cpp.o
[ 97%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_seu_layer.cpp.o
[ 98%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_src.cpp.o
[100%] Linking CXX executable test-baryon
[100%] Built target test-baryon
~/Workspace/fermion
~/Workspace/fermion/build ~/Workspace/fermion
[94/94] matvec.test_matvec (3802 ms)
PASSED TESTS (94/94):
       7 ms: ./test/test-baryon BaryonSEULayerTest_RapidCheck.foreach_re_row
       7 ms: ./test/test-baryon BaryonSEULayerTest_RapidCheck.foreach_ewe_row
      21 ms: ./test/test-baryon operations.left_xor_right
      22 ms: ./test/test-baryon operations.inv_right
      23 ms: ./test/test-baryon operations.left_xor_inv_right
      28 ms: ./test/test-baryon operations.inv_left_and_right
      30 ms: ./test/test-baryon operations.left_or_inv_right
      33 ms: ./test/test-baryon operations.left_or_right
      34 ms: ./test/test-baryon operations.inv_left_and_inv_right
      36 ms: ./test/test-baryon operations.right
      39 ms: ./test/test-baryon operations.left_and_inv_right
      53 ms: ./test/test-baryon operations.left_and_right
     177 ms: ./test/test-baryon BaryonAPUCTest.foreach_masked_section
     182 ms: ./test/test-baryon gvml_init.test_is_gvml_init
     193 ms: ./test/test-baryon BaryonAPUCTest.foreach_bank_plat
     214 ms: ./test/test-baryon BaryonGVMLTest.gvml_cpy_imm_16
     217 ms: ./test/test-baryon BaryonAPUCTest.plats_for_bank
     237 ms: ./test/test-baryon BaryonGVMLTest.gal_mem_to_l2_to_mem
     264 ms: ./test/test-baryon BaryonGVMLTest.gal_get_pm_inst_count
     741 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.l2_from_lgl
     759 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_inv_src
     769 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp16_from_rsp256
     797 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_add_u16
     801 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp256_from_rsp2k
     806 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.lgl_from_l2
     808 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_inv_src
     845 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.apuc_rsp_fifo
     850 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl_from_l1
     859 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_src
     861 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl
     862 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.reset_rl
     878 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.l1_from_lgl
     885 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.lgl_from_l1
     888 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl
     894 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp_end
     920 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl_from_rl
     955 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_rsp16
     959 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp16
     968 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_src
     978 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_gl
     981 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp32k_from_rsp2k
     990 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp256_from_rsp16
    1037 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp16_from_rl
    1043 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.set_rl
    1051 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp2k_from_rsp32k
    1079 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_inv_src
    1084 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp2k_from_rsp256
    1091 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_src
    1104 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_src
    1112 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.l1_from_ggl
    1130 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.gl
    1163 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl_from_rl_and_l1
    1163 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.gl_from_rl
    1230 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_src
    1253 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rwinh_standard_use
    1280 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_from_inv_src
    1293 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_ggl
    1318 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_cond_eq_src
    1355 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_cond_eq_inv_src
    1398 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_from_src
    1741 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_xor_inv_src
    1757 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_sb_and_src
    1780 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_sb
    1797 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb
    1813 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_and_inv_src
    1826 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_inv_sb
    1864 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_and_src
    1878 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_sb_and_inv_src
    1911 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_or_src
    1922 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_sb_and_inv_src
    1929 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_sb_and_src
    1937 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_sb
    1955 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_or_inv_src
    1961 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_sb_and_src
    1972 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_sb_and_inv_src
    1981 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_sb
    1998 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_sb_and_src
    2012 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_sb
    2112 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_sb_and_inv_src
    2227 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_xor_src
    2254 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_rl
    2272 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_store_load_16
    2304 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.nrl
    2328 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.srl
    2341 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.wrl
    2394 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_nrl
    2410 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_erl
    2420 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.brsp16
    2545 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_srl
    2561 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_wrl
    2749 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_store_load_vmr_16
    2775 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.erl
    3692 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_mul_u16
    3802 ms: ./test/test-baryon matvec.test_matvec
```

You may also run `--test` in conjunction with `--install`, which will prevent installation if the tests fail:

```
$ ./setup.sh --clean --prefix ~/Workspace/belex-tests/venv --test --install
~/Workspace/fermion/build ~/Workspace/fermion
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
belex-aot: /home/dylon/mambaforge/envs/baryon/bin/belex-aot
Configuration results
---------------------
C compiler      : /usr/bin/cc
Build type: Debug
C compiler flags      : -g
Installation prefix: /home/dylon/Workspace/belex-tests/venv
-- Configuring done
-- Generating done
-- Build files have been written to: /home/dylon/Workspace/fermion/build
[  1%] Generating gensrc/gsi/gvml_fragments.c, gensrc/gsi/gvml_fragments.h
[  2%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/fifo.c.o
[  3%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/apuc.c.o
[  4%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/seu_layer.c.o
[  5%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/common_api.c.o
[  6%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libapl.c.o
[  7%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgal.c.o
[  8%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libgdl.c.o
[ 10%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/gsi_sim_config.c.o
[ 11%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/baryon/operations.c.o
[ 12%] Building C object CMakeFiles/gsi-baryon-sys.dir/src/gsi/libsys.c.o
[ 12%] Built target copy-rapidcheck-config
[ 13%] Linking C static library libgsi-baryon-sys.a
[ 13%] Built target gsi-baryon-sys
[ 14%] Building C object CMakeFiles/gsi-baryon-gvml.dir/gensrc/gsi/gvml_fragments.c.o
[ 15%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/libgvml.c.o
[ 16%] Building C object CMakeFiles/gsi-baryon-gvml.dir/src/gsi/rsp.c.o
[ 17%] Linking C static library libgsi-baryon-gvml.a
[ 17%] Built target gsi-baryon-gvml
[ 19%] Building CXX object test/CMakeFiles/test-baryon.dir/test_baryon.cpp.o
[ 20%] Building CXX object test/CMakeFiles/test-baryon.dir/rapidcheck_parser.cpp.o
[ 21%] Building CXX object test/CMakeFiles/test-baryon.dir/test_matvec.cpp.o
[ 22%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/fixtures.cpp.o
[ 23%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_init.cpp.o
[ 24%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_add_u16.cpp.o
[ 25%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_cpy_imm_16.cpp.o
[ 26%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_mul_u16.cpp.o
[ 28%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_store_load_16.cpp.o
[ 29%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_gvml_store_load_vmr_16.cpp.o
[ 30%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/test_libgal.cpp.o
[ 31%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/comparators.cpp.o
[ 32%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/fixtures.cpp.o
[ 33%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_apuc.cpp.o
[ 34%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/utils.cpp.o
[ 35%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/generators.cpp.o
[ 37%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_ggl_from_l1.cpp.o
[ 38%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_ggl_from_rl.cpp.o
[ 39%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_brsp16.cpp.o
[ 40%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_ggl_from_rl_and_l1.cpp.o
[ 41%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_gl_from_rl.cpp.o
[ 42%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_l1_from_lgl.cpp.o
[ 43%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_l1_from_ggl.cpp.o
[ 44%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_lgl_from_l1.cpp.o
[ 46%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_lgl_from_l2.cpp.o
[ 47%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_operations.cpp.o
[ 48%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_inv_sb.cpp.o
[ 49%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_sb_and_inv_src.cpp.o
[ 50%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_sb_and_src.cpp.o
[ 51%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_l2_from_lgl.cpp.o
[ 52%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_inv_src.cpp.o
[ 53%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_sb.cpp.o
[ 55%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_and_eq_src.cpp.o
[ 56%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_sb.cpp.o
[ 57%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_sb_and_src.cpp.o
[ 58%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_sb_and_inv_src.cpp.o
[ 59%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_inv_src.cpp.o
[ 60%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb.cpp.o
[ 61%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_and_inv_src.cpp.o
[ 62%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_and_src.cpp.o
[ 64%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_or_inv_src.cpp.o
[ 65%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_or_src.cpp.o
[ 66%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_xor_inv_src.cpp.o
[ 67%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_sb_xor_src.cpp.o
[ 68%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_from_src.cpp.o
[ 69%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_inv_src.cpp.o
[ 70%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_sb.cpp.o
[ 71%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_sb_and_inv_src.cpp.o
[ 73%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_sb_and_src.cpp.o
[ 74%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_or_eq_src.cpp.o
[ 75%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_inv_src.cpp.o
[ 76%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_sb.cpp.o
[ 77%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_sb_and_inv_src.cpp.o
[ 78%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_sb_and_src.cpp.o
[ 79%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rl_xor_eq_src.cpp.o
[ 80%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp16_from_rl.cpp.o
[ 82%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp16_from_rsp256.cpp.o
[ 83%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp256_from_rsp16.cpp.o
[ 84%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp256_from_rsp2k.cpp.o
[ 85%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp2k_from_rsp256.cpp.o
[ 86%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp2k_from_rsp32k.cpp.o
[ 87%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp_end.cpp.o
[ 88%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp32k_from_rsp2k.cpp.o
[ 89%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rsp_fifo.cpp.o
[ 91%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_rwinh.cpp.o
[ 92%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_cond_eq_inv_src.cpp.o
[ 93%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_cond_eq_src.cpp.o
[ 94%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_from_inv_src.cpp.o
[ 95%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_sb_from_src.cpp.o
[ 96%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_set_rl.cpp.o
[ 97%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_seu_layer.cpp.o
[ 98%] Building CXX object test/CMakeFiles/test-baryon.dir/gsi/baryon/test_src.cpp.o
[100%] Linking CXX executable test-baryon
[100%] Built target test-baryon
~/Workspace/fermion
~/Workspace/fermion/build ~/Workspace/fermion
~/Workspace/fermion/build ~/Workspace/fermion/build ~/Workspace/fermion
[94/94] matvec.test_matvec (6760 ms)
PASSED TESTS (94/94):
      13 ms: ./test/test-baryon BaryonSEULayerTest_RapidCheck.foreach_ewe_row
      32 ms: ./test/test-baryon BaryonSEULayerTest_RapidCheck.foreach_re_row
      60 ms: ./test/test-baryon operations.left_xor_right
      64 ms: ./test/test-baryon operations.left_and_inv_right
      67 ms: ./test/test-baryon operations.left_or_inv_right
      75 ms: ./test/test-baryon operations.inv_right
      79 ms: ./test/test-baryon operations.left_xor_inv_right
      89 ms: ./test/test-baryon operations.inv_left_and_inv_right
      99 ms: ./test/test-baryon operations.inv_left_and_right
     133 ms: ./test/test-baryon operations.left_or_right
     159 ms: ./test/test-baryon operations.left_and_right
     173 ms: ./test/test-baryon BaryonGVMLTest.gvml_cpy_imm_16
     187 ms: ./test/test-baryon operations.right
     188 ms: ./test/test-baryon BaryonAPUCTest.plats_for_bank
     228 ms: ./test/test-baryon BaryonGVMLTest.gal_get_pm_inst_count
     273 ms: ./test/test-baryon gvml_init.test_is_gvml_init
     275 ms: ./test/test-baryon BaryonAPUCTest.foreach_bank_plat
     276 ms: ./test/test-baryon BaryonAPUCTest.foreach_masked_section
     304 ms: ./test/test-baryon BaryonGVMLTest.gal_mem_to_l2_to_mem
     795 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl
     820 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp32k_from_rsp2k
     901 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl
     965 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp256_from_rsp2k
    1015 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp16_from_rsp256
    1051 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.l1_from_lgl
    1057 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp2k_from_rsp256
    1065 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.l2_from_lgl
    1126 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl_from_rl_and_l1
    1184 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp256_from_rsp16
    1186 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.lgl_from_l2
    1222 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_src
    1245 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.apuc_rsp_fifo
    1249 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl_from_l1
    1265 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_add_u16
    1280 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_inv_src
    1294 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp16_from_rl
    1296 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp16
    1374 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_from_src
    1405 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_from_inv_src
    1407 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_rsp16
    1420 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rwinh_standard_use
    1436 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.gl
    1449 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_inv_src
    1496 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.lgl_from_l1
    1519 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_src
    1523 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_cond_eq_src
    1525 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp2k_from_rsp32k
    1529 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.ggl_from_rl
    1624 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.reset_rl
    1625 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rsp_end
    1657 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_src
    1678 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_gl
    1704 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_inv_src
    1761 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.l1_from_ggl
    1774 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.gl_from_rl
    1923 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_src
    1962 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.sb_cond_eq_inv_src
    1992 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.set_rl
    2204 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_src
    2343 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_and_inv_src
    2384 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_sb
    2500 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb
    2530 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_sb_and_inv_src
    2633 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_sb_and_inv_src
    2723 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_erl
    2838 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_nrl
    2947 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_ggl
    2954 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_store_load_vmr_16
    3408 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.erl
    3427 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_sb
    3478 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_xor_src
    3555 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_sb_and_src
    3605 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_sb
    3693 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_sb
    3704 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_sb_and_inv_src
    3749 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.brsp16
    3828 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_wrl
    3897 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_xor_inv_src
    3950 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.srl
    4131 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_xor_eq_sb_and_src
    4164 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_sb_and_inv_src
    4204 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.wrl
    4232 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_srl
    4584 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_or_src
    4732 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.inv_rl
    4892 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_and_eq_inv_sb
    4902 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_or_eq_sb_and_src
    4991 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.nrl
    5203 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_and_src
    5220 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_sb_or_inv_src
    5249 ms: ./test/test-baryon BaryonAPUCTest_RapidCheck.rl_from_inv_sb_and_src
    5353 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_mul_u16
    5464 ms: ./test/test-baryon BaryonGVMLTest_RapidCheck.gvml_store_load_16
    6760 ms: ./test/test-baryon matvec.test_matvec
~/Workspace/fermion/build ~/Workspace/fermion
[ 12%] Built target gsi-baryon-sys
[ 17%] Built target gsi-baryon-gvml
[ 17%] Built target copy-rapidcheck-config
[100%] Built target test-baryon
Install the project...
-- Install configuration: "Debug"
-- Installing: /home/dylon/Workspace/belex-tests/venv/lib/libgsi-baryon-sys.a
-- Installing: /home/dylon/Workspace/belex-tests/venv/lib/libgsi-baryon-gvml.a
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/__pycache__
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgvml_memory.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgal.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/gsi_sim_config.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgvml_element_wise.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/__pycache__
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/seu_layer.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/operations.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/fifo.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/apuc.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/baryon/constants.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgvml.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/gal-fast-funcs.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/rsp.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libgdl.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/common_api.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libapl.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/libc.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/assert.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/types.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/log.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/error.h
-- Up-to-date: /home/dylon/Workspace/belex-tests/venv/include/gsi/libsys/debug.h
~/Workspace/fermion
You may wish to export the following for CMake dependencies:

    export CMAKE_PREFIX_PATH="/home/dylon/Workspace/belex-tests/venv"

```

## Additional Help

To get more help, just run `./setup.sh --help`:

```
$ ./setup.sh --help
Software emulator for the GSI APU and libraries like libs-gvml and sys-apu.

Options:
  -h|--help                   Print this help text.
  --prefix PATH               Specify the installation prefix
                              (default: /usr/local)
  --test                      Run tests after building them.
  --install                   Install Baryon after building it.
  --enable-tests              Build the testing suite for Baryon.
  --build-type Debug|Release  CMake build type (Debug, Release, etc.,
                              default: Debug)
  --num-cores INT             Number of CPU cores to build the library on
                              (default: 36).
  --filter PATTERN            Filters which tests to run.
  --clean                     Delete /home/dylon/Workspace/fermion/build and rebuild everything.

Usage:
  setup.sh [--help] \
      [--prefix /path/to/install/dir] \
      [--test] \
      [--install] \
      [--enable-tests] \
      [--build-type BUILD_TYPE] \
      [--num-cores NUM_CORES] \
      [--filter GTEST_FILTER] \
      [--clean]

Examples:
  ./setup.sh --prefix build/baryon-inst --enable-tests --install

  ./setup.sh --clean --prefix ~/mambaforge/envs/ch_emulation --install
```
