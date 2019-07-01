#!/bin/bash

# Generates new c++ files

printf '%s\n' "/*" \
    "Glassy Dynamics Simulation Module: $1" \
    "Created by Joe Raso, $(date)" \
    "Copyright © 2019 Joe Raso, All rights reserved." "*/" \
    "" "#ifndef $1_hpp" "#define $1_hpp" \
    "" "" "#endif /*$1_hpp*/" \
        > ${1}.hpp
        
printf '%s\n' "/*" \
    "Glassy Dynamics Simulation Module: $1" \
    "Created by Joe Raso, $(date)" \
    "Copyright © 2019 Joe Raso, All rights reserved." "*/" \
    "" "#include \"$1.hpp\"" \
        > ${1}.cpp
