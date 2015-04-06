#!/bin/sh

# DEBIAN
PACKAGEID="strusrpc-0.0"

cd pkg/$PACKAGEID
dpkg-buildpackage

