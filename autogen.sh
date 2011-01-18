#!/bin/sh

libtoolize --copy --force --install
aclocal
autoconf
automake -a -c -f --foreign
