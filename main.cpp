#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdint>

using namespace std;

unordered_map<string, uint64_t> hash_table;

void write_record(const string& filename, const string& key, const string& value){
    ofstream file(filename, ios::binary | ios::app);
    if(!file){
        cout << "Failed to open the file!" << endl;

        return;

    }

    uint64_t offset = static_cast<uint64_t>(file.tellp());
    uint32_t key_len = static_cast<uint32_t>(key.size());
    uint32_t val_len = static_cast<uint32_t>(value.size());

    file.write(reinterpret_cast<const char*>(&key_len), sizeof(key_len));
    file.write(reinterpret_cast<const char*>(&val_len), sizeof(val_len));

    file.write(key.data(), key_len);
    file.write(value.data(), val_len);

    hash_table[key] = offset;

    cout << "Saved: '" << key  <<"' with value of '" << value << "'at byte offset " << offset << endl;


}

string read_record(const string& filename, const string& key){

    ifstream file(filename, ios::binary);

    if(!file){
        cout << "Failed to open the file!" << endl;

        return "";
    }

}

int main(){

    string file = "db.bin";

    write_record(file, "user-1", "Bssk");

    

    return 0;
}