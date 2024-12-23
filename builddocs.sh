#!/bin/bash

minilang src/document.mini docs/library src/*/*.c src/*/*.cpp
cd docs && sphinx-build . ../html/ && cd ..
echo `date` > html/reload
