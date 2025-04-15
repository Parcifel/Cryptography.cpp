#!/bin/bash

NC='\033[0m' # No Color
RED='\033[0;31m'
GREEN='\033[0;32m'
LGREEN='\033[1;32m'
DYELLOW='\033[0;33m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
LBLUE='\033[1;34m'
DGRAY='\033[1;30m'
LGRAY='\033[0;37m'
WHITE='\033[1;37m'

echo -e "${LGRAY}"
make clean
echo -e "${NC}"

echo -n "Mode (D=DEBUG, V=VERBOSE, _=DEFAULT): "
read mode

echo -e "${YELLOW}"
case $mode in
  D)
    echo "DEBUG"
    make debug
    ;;

  V)
    echo "VERBOSE"
    make verbose
    ;;

  *)
    echo "DEFAULT"
    make
    ;;
esac
echo -e "${NC}"
echo ""

./crypto