#include "compressor.hpp"
#include <chrono>
using namespace std;
void print_usage() {
    cout << "=====================================================" << endl
        << "RLE Compression Utility" << endl
        << "=====================================================" << endl
        << "Usage: ./compressor <mode> <input_file> <output_file>" << endl << endl
        << "Modes:" << endl
        << " -c    Compress input text file" << endl
        << " -d    Decompress an encoded file" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        print_usage();
        return 1;
    }

    string_view mode = argv[1];
    string_view input_file = argv[2];
    string_view output_file = argv[3];

    bool compress = false;
    if (mode == "-c") {
        compress = true;
    } else if (mode != "-d") {
        cerr << "Invalid mode flag '" << mode << endl;
        print_usage();
        return 1;
    }

    cout << (compress ? "Compressing file: " : "Decompressing file: ") << input_file << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    bool success = rle::process_file(input_file, output_file, compress);
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    if (success) {
        cout << "Completed successfully in " << elapsed << " microseconds." << endl
            << "Resusts saved to " << output_file << " file";
        return 0;
    }
    else {
       cout << (compress ? "Failed to compress file: " : "Failed to decompress file: ") << input_file << endl;
    }

    return 1;
}
