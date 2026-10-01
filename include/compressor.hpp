#pragma once

#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
namespace rle {

    // Compresses a text string using basic RLE (Run-Length Encoding)
    inline string compress_string(string_view input) {
        if (input.empty()) return "";

        string compressed;
        compressed.reserve(input.size()); // Pre-allocate to maximize memory efficiency

        size_t count = 1;
        for (size_t i = 1; i <= input.size(); ++i) {
            if (i < input.size() && input[i] == input[i - 1]) {
                count++;
            } else {
                compressed += input[i - 1];
                compressed += to_string(count);
                count = 1;
            }
        }
        return compressed;
    }

    // Decompresses an RLE string back to its original form
    inline string decompress_string(string_view input) {
        string decompressed;
        size_t i = 0;

        while (i < input.size()) {
            char ch = input[i++];
            
            // Read the variable-length number following the character
            string count_str;
            while (i < input.size() && isdigit(static_cast<unsigned char>(input[i]))) {
                count_str += input[i++];
            }

            if (!count_str.empty()) {
                size_t count = stoull(count_str);
                decompressed.append(count, ch);
            }
        }
        return decompressed;
    }

    // Stream interface managing file handles and RAII (Resource Acquisition Is Initialization)
    inline bool process_file(string_view input_path, string_view output_path, bool mode_compress) {
        ifstream in_file(input_path.data(), ios::in | ios::binary);
        if (!in_file) {
            cerr << "Failed to open input file: " << input_path << endl;
            return false;
        }

        ofstream out_file(output_path.data(), ios::out | ios::binary);
        if (!out_file) {
            cerr << "Failed to create output file: " << output_path << endl;
            return false;
        }

        // Read file content into memory buffer stream
        stringstream buffer;
        buffer << in_file.rdbuf();
        string content = buffer.str();

        string result = mode_compress ? compress_string(content) : decompress_string(content);

        out_file << result;
        return true;
    }
}
