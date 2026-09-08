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

    file.close();

    cout << "Saved: '" << key  <<"' with value of '" << value << "'at byte offset " << offset << endl;


}

string read_record(const string& filename, const string& key){
   
    if(hash_table.find(key) == hash_table.end()){
        cout << "Error Key: '" << key << "' was not found" << endl;

        return "";
    }

    uint64_t offset = hash_table[key];

    ifstream file(filename, ios::binary);

    if(!file){
        cout << "Failed to open the file!" << endl;

        return "";
    }


    file.seekg(offset);
    uint32_t key_len = 0;
    uint32_t val_len = 0;

    file.read(reinterpret_cast<char*>(&key_len), sizeof(key_len));
    file.read(reinterpret_cast<char*>(&val_len), sizeof(val_len));

    file.seekg(key_len, ios::cur);

    string value(val_len, '\0');
    file.read(&value[0], val_len);

    file.close();
    return value;


}

int main(){

    string file = "db.bin";

    write_record(file, "user-1", "Bssk");

    

    return 0;
}