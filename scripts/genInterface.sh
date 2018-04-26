#!/bin/sh

scripts/genInterface.pl `find ../strus{,Analyzer,Base}/include/strus -name "*Interface.hpp"  | grep -v ebugTraceInterface | grep -v rrorBufferInterface | sort`

