# hufmann

Hufmann compression algorithm implementation in C. I created this CLI for one of my university assignments at Budapest University of Technology and Economics (from which I later dropped out).

Works better with larger texts (>300 chars) and unfortunately, decompression not working to this day (it crashes with segmentation errors caused by recursion).

## What you can find in this repo:

* Specification (in hungarian only)
* Documentation (in hungarian only)
* Header files and C source files
* Sample txt file

## User manual

1. Compression
    1. `huffman -if <input file path> [ -o <output file path>]`: compresses the content of a text file into a .hcf file, at the path of the specified output file. If this is empty, the default will be the file named tomoritett.hcf created in the runtime directory. 
    2. `huffman -is <string> [ -o <output file path>]`: compresses a typed text content into a .hcf file, at the path of the specified output file. If this is empty, the default will be the file named tomoritett.hcf created in the runtime directory

2. Decompression ( ! not working ! )
    1. `huffman -rf <compressed file path> [ -o <output file path>]`: restores the compressed file to the original, uncompressed file and writes the result to the output file
    2. `huffman -rs <compressed file path> [ -o <output file path>]`: restores the compressed file and prints the result to the screen

3. Help: `huffman -h`
