#!/bin/bash
# Use the first command to find duplicate files in a folder
# It is a combination of various commands piped together.
# 'find -not -empty -type f -printf "%s\n" ' Finds all files which are not empty and are of regular type and returns their size  
# 'sort -rn' sorts files and feeds the output to 'uniq -d' which returns duplicate lines
# ' xargs -I{} -n1 find -type f -size {}c -print0 | xargs -0 md5sum ' is used to checks the md5 sum which acts as a digital fingerprint of the system
# Thus files having same size but differnt data are eliminated by 'md5sum'

find -not -empty -type f -printf "%s\n" | sort -rn | uniq -d | xargs -I{} -n1 find -type f -size {}c -print0 | xargs -0 md5sum | sort | uniq -w32 --all-repeated=separate