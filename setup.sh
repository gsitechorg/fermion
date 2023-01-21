#!/usr/bin/env bash

set -x

EXIT_SUCCESS=0
EXIT_INVALID_OPTION=1
EXIT_MKDIR_FAILED=2
EXIT_CMAKE_FAILED=3
EXIT_MAKE_FAILED=4
EXIT_INSTALL_FAILED=5

declare PRINT_HELP
declare INSTALL_PREFIX
declare INSTALL_LEPTON

BUILD_TESTS=false
BUILD_TYPE=Debug
NUM_CORES=1

SCRIPT_NAME="$(basename "$0")"

function print-help {
    cat <<EOF
Software emulator for the GSI APU and libraries like libs-gvml and sys-apu.

Options:
  -h|--help       Print this help text.
  --prefix        Specify the installation prefix (default: /usr/local)
  --install       Install Lepton after building it.
  --enable-tests  Build the testing suite for Lepton.
  --build-type    CMake build type (Debug, Release, etc., default: $BUILD_TYPE)
  --num-cores     Number of CPU cores to build the library on.

Usage:
  $SCRIPT_NAME [--help] \
      [--prefix /path/to/install/dir] \
      [--no-tests]

Examples:
  $SCRIPT_NAME --prefix lepton-inst --no-tests
EOF

    return $EXIT_SUCCESS
}

function parse-opts {
    local OPTION
    local RETURN_CODE=$EXIT_SUCCESS

    while (( $# > 0 )); do
        OPTION="$1"
        case "$OPTION" in
            -h|--help)
                PRINT_HELP=true
                shift
                ;;
            --prefix)
                INSTALL_PREFIX="$2"
                shift 2
                ;;
            --install)
                INSTALL_LEPTON=true
                shift
                ;;
            --enable-tests)
                BUILD_TESTS=true
                shift
                ;;
            --build-type)
                BUILD_TYPE=$2
                shift 2
                ;;
            --num-cores)
                NUM_CORES=$2
                shift 2
                ;;
            -[a-z][a-z]*)
                shift
                # Expand short args in reverse, in case the right-most arg
                # accepts a parameter.
                for (( i = ${#OPTION} - 1; i > 0; i -= 1 )); do
                    set - "-${OPTION:$i:1}" "$@"
                done
                ;;
            *)
                echo "Unsupported option: $OPTION" 1>&2
                PRINT_HELP=true
                RETURN_CODE=$EXIT_INVALID_OPTION
                shift
                ;;
        esac
    done

    if [ -z "$INSTALL_PREFIX" ]; then
        INSTALL_PREFIX="/usr/local"
    fi

    return $RETURN_CODE
}

function build-lepton {
    local RETURN_CODE

    mkdir -p build
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "mkdir failed with status $RETURN_CODE" 1>&2
        return $EXIT_MKDIR_FAILED
    fi

    pushd build

    cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
          -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
          -DBUILD_TESTS="$BUILD_TESTS" \
          ..
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "cmake failed with status $RETURN_CODE" 1>&2
        return $EXIT_CMAKE_FAILED
    fi

    make -j${NUM_CORES}
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "make failed with status $RETURN_CODE" 1>&2
        return $EXIT_MAKE_FAILED
    fi

    popd

    return $EXIT_SUCCESS
}

function install-lepton() {
    local RETURN_CODE

    pushd build

    make install
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "make install failed with status $RETURN_CODE" 1>&2
        return $EXIT_INSTALL_FAILED
    fi

    popd

    return $EXIT_SUCCESS
}

function main {
    local RETURN_CODE

    parse-opts "$@"
    RETURN_CODE=$?

    if [ -n "$PRINT_HELP" ]; then
        print-help
        return $RETURN_CODE
    fi

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        return $RETURN_CODE
    fi

    build-lepton
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        return $RETURN_CODE
    fi

    if [ -n "$INSTALL_LEPTON" ]; then
        install-lepton
        RETURN_CODE=$?

        if (( RETURN_CODE != EXIT_SUCCESS )); then
            return $RETURN_CODE
        fi
    fi

    return $EXIT_SUCCESS
}

main "$@"
exit $?
