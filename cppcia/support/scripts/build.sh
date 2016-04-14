#!/usr/bin/env bash

# initialize configuration vars

SRC_DIR=""
INSTALL_DIR=""


# set configuration vars

if [ -z "$BOOST_ROOT_DIR" ]; then 
  echo "error: Boost root directory was not provided" 

  exit 1
fi


if [ -z "$1" ]; then 
  echo "error: source directory was not provided" 

  exit 1
fi

SRC_DIR=$1


# print configuration vars

echo "info: printing configuation vars"
echo "info: source dir: ${SRC_DIR}"
echo "info: boost dir: ${BOOST_ROOT_DIR}"
echo ""


CC=clang CXX=clang++ \
  cmake \
  -DBOOST_ROOT=${BOOST_ROOT_DIR} \
  -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
  -DCMAKE_EXE_LINKER_FLAGS="-lc++abi" \
  ${SRC_DIR}


exit $?

