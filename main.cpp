#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdint>

using namespace std;

unordered_map<string, uint64_t> hash_table;

void write_record(const string& filename, const string& key, const string& value){
    ofstream file(filename, ios::binary || ios::app);
    if(!file.is_open()){
        cout << "Failed to open the file!" << endl;

        return;

    }

    uint32_t key_len = static_cast<uint32_t>(key.size());
    uint32_t val_len = static_cast<uint32_t>(value.size());

    file.write()


}

int main(){

    string file = "db.bin";

    write_record(file, "user-1", "Bssk");

    

    return 0;
}