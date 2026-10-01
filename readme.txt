g++ -std=c++20 -Iinclude src/main.cpp -o compressor

Test:
echo "AAAAABBBBBCCCCCDDDDD" > test.

compression command: ./compressor -c test.txt compressed.rle

decompression command: ./compressor -d compressed.rle test2.txt