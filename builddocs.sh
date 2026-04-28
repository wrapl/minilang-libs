#!/bin/bash

minilang src/document.mini docs/library src/*/*.c src/*/*.cpp obj/net/curl_options.c
cd docs && sphinx-build . ../html/ && cd ..
echo `date` > html/reload
