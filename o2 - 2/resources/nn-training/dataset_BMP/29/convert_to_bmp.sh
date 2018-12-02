#!/bin/bash
echo "Hello, World!" 
convert "*.png" -type truecolor "*.bmp"
rename 's/\*-//' *
rm *.png

