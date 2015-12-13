#!/bin/bash

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:.
echo "Exporting ${LD_LIBRARY_PATH}"
./$1
