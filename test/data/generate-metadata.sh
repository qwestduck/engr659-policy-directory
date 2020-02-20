#!/bin/bash

for f in tokenized/*
do
	fileName=$(basename $f)
	docId=$(echo "$fileName" | sed "s/^\([0-9]*\)_.*$/\1/")
	publishDate=$(echo "$fileName" | sed "s/^.*_\([0-9]*\)\.txt$/\1/")

	echo "$fileName $docId"
done
