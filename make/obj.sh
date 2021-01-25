#!/bin/bash

list=""
for file in $(find source -name "*.cpp"); do
	folder=$(dirname "$file")
	name=$(basename "$file" .cpp)
	list+=" obj/$folder/$name.o"
done;

echo $list
