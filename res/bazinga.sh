#!/bin/sh

rm w1.dvi
rubber w1.tex
dvipng w1.dvi
convert w11.png -trim +repage w11.png
display w11.png
rubber --clean w1.tex

rm w2.dvi
rubber w2.tex
dvipng w2.dvi
convert w21.png -trim +repage w21.png
display w21.png
rubber --clean w2.tex
