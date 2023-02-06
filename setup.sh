#!/usr/bin/env bash

shopt -s nocasematch
if [[ "$DEBUG_MODE" =~ ^(true|yes|on|1)$ ]]; then
    set -x
fi
shopt -u nocasematch

EXIT_SUCCESS=0
EXIT_INVALID_OPTION=1
EXIT_MKDIR_FAILED=2
EXIT_CMAKE_FAILED=3
EXIT_MAKE_FAILED=4
EXIT_INSTALL_FAILED=5
EXIT_TEST_FAILED=6

declare PRINT_HELP
declare INSTALL_PREFIX
declare INSTALL_BARYON
declare ENABLE_TESTS
declare RUN_TESTS
declare GTEST_FILTER

BUILD_TYPE=Debug
NUM_CORES=$(nproc)

BASEDIR="$(dirname "$0")"
BASEDIR="$(cd "$BASEDIR"; pwd)"
BUILD_DIR="${BASEDIR}/build"
SCRIPT_NAME="$(basename "$0")"

function print-help {
    cat <<EOF
Software emulator for the GSI APU and libraries like libs-gvml and sys-apu.

Options:
  -h|--help                   Print this help text.
  --prefix PATH               Specify the installation prefix
                              (default: /usr/local)
  --test                      Run tests after building them.
  --install                   Install Baryon after building it.
  --enable-tests              Build the testing suite for Baryon.
  --build-type Debug|Release  CMake build type (Debug, Release, etc.,
                              default: $BUILD_TYPE)
  --num-cores INT             Number of CPU cores to build the library on
                              (default: ${NUM_CORES}).
  --filter PATTERN            Filters which tests to run.

Usage:
  $SCRIPT_NAME [--help] \\
      [--prefix /path/to/install/dir] \\
      [--test] \\
      [--install] \\
      [--enable-tests] \\
      [--build-type BUILD_TYPE] \\
      [--num-cores NUM_CORES] \\
      [--filter GTEST_FILTER]

Examples:
  $SCRIPT_NAME --prefix build/baryon-inst --enable-tests --install
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
            --build-type)
                BUILD_TYPE=$2
                shift 2
                ;;
            --num-cores)
                NUM_CORES=$2
                shift 2
                ;;
            --enable-tests)
                ENABLE_TESTS=true
                shift
                ;;
            --test)
                ENABLE_TESTS=true
                RUN_TESTS=true
                shift
                ;;
            --filter)
                GTEST_FILTER="$2"
                shift 2
                ;;
            --install)
                INSTALL_BARYON=true
                shift
                ;;
            --*=*)
                shift
                LVALUE="${OPTION/=*}"
                RVALUE="${OPTION:1+${#LVALUE}}"
                set -- "$LVALUE" "$RVALUE" "$@"
                ;;
            -[a-z][a-z]*)
                shift
                # Expand short args in reverse, in case the right-most arg
                # accepts a parameter.
                for (( i = ${#OPTION} - 1; i > 0; i -= 1 )); do
                    set -- "-${OPTION:$i:1}" "$@"
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

    mkdir -p "$INSTALL_PREFIX"
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "mkdir failed with status $RETURN_CODE" 1>&2
        return $EXIT_MKDIR_FAILED
    fi

    INSTALL_PREFIX="$(cd "$INSTALL_PREFIX"; pwd)"

    return $RETURN_CODE
}

function build-baryon {
    local RETURN_CODE

    mkdir -p "$BUILD_DIR"
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "mkdir failed with status $RETURN_CODE" 1>&2
        return $EXIT_MKDIR_FAILED
    fi

    pushd "$BUILD_DIR"

    cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
          -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
          -DBUILD_TESTS="$ENABLE_TESTS" \
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

function test-baryon() {
    local RETURN_CODE

    pushd "$BUILD_DIR"

    gtest-parallel \
        --workers="$NUM_CORES" \
        --print_test_times \
        --gtest_filter "$GTEST_FILTER" \
        ./test/test-baryon
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "test-baryon failed with status $RETURN_CODE" 1>&2
        return $EXIT_TEST_FAILED
    fi

    popd

    return $EXIT_SUCCESS
}

function install-baryon() {
    local RETURN_CODE

    pushd "$BUILD_DIR"

    if [ -n "$ENABLE_TESTS" ]; then
        test-baryon
        RETURN_CODE=$?

        if (( RETURN_CODE != EXIT_SUCCESS )); then
            return $RETURN_CODE
        fi
    fi

    make install
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        echo "make install failed with status $RETURN_CODE" 1>&2
        return $EXIT_INSTALL_FAILED
    fi

    popd

    echo "You may wish to export the following for CMake dependencies:"
    echo
    echo "    export CMAKE_PREFIX_PATH=\"${INSTALL_PREFIX}\""
    echo

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

    build-baryon
    RETURN_CODE=$?

    if (( RETURN_CODE != EXIT_SUCCESS )); then
        return $RETURN_CODE
    fi

    if [ -n "$INSTALL_BARYON" ]; then
        install-baryon
        RETURN_CODE=$?

        if (( RETURN_CODE != EXIT_SUCCESS )); then
            return $RETURN_CODE
        fi
    elif [ -n "$RUN_TESTS" ]; then
        test-baryon
        RETURN_CODE=$?

        if (( RETURN_CODE != EXIT_SUCCESS )); then
            return $RETURN_CODE
        fi
    fi

    return $EXIT_SUCCESS
}

main "$@"
exit $?
