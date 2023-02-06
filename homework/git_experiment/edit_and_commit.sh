#!/usr/bin/env bash

for commit_count in {2..100}
do
  let linenum="10+$commit_count"
  sed -i "$linenum i This is a sentence on line $linenum" foo.tex
  pdflatex foo.tex > /dev/null 2>&1
  git add -u
  git commit -m "Adds a sentence at line $linenum and compiles"
done
