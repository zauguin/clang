#!/bin/bash
tmp=$(mktemp)

function cleanup()
{
	rm -f ${tmp}
}

trap cleanup EXIT

for src in $(dirname ${0})/*.cpp
do
	echo "${src}:"
	$(dirname ${0})/../../../../_build/bin/clang++ \
		-std=c++14 -I$(dirname ${0})/.. -o ${tmp} ${src} &&\
	${tmp}
done
