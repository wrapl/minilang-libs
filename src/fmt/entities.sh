#!/bin/sh
gperf -LANSI-C -C -c -t -n -KName -Zentity -Hentity_hash -Nentity_lookup -r -m 50 --null-strings entities.lst > entities.c
