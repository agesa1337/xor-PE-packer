#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void xor_encrypt_decrypt(vector<char>& data, char key) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] ^= key;
    }
}

bool read_file(const string& filename, vector<char>& data) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return false;
    }

    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);

    data.resize(size);
    file.read(data.data(), size);
    file.close();
    return true;
}

void save_encrypted_file(const string& filename, const vector<char>& data) {
    ofstream file(filename, ios::binary);
    file.write(data.data(), data.size());
    file.close();
}

int main() {
    string input_filename = "Auth.exe";
    string encrypted_filename = "packed.ldr";

    char key = 0x2038642379ACBFD;

    vector<char> input_data;
    if (!read_file(input_filename, input_data)) {
        return -1;
    }

    vector<char> encrypted_data = input_data;
    xor_encrypt_decrypt(encrypted_data, key);

    save_encrypted_file(encrypted_filename, encrypted_data);

    return 0;
}
