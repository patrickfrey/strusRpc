#!/bin/sh

scripts/genInterface.pl `find ../strus{,Analyzer}/include/strus -name "*Interface.hpp" | sort`

