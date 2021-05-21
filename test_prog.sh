#!/bin/bash
name=$1
[ -f $name ] || (echo 'Syntax: test_prog <filename>' && exit 2)
prefix=$(basename -s .lang $name)
echo "Creating $prefix.prg"
./examplang < $name| petcat -w2 -o $prefix.prg
echo "Launching emulator"
x64 -autostartprgmode 1 ./$prefix.prg
