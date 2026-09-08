#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;

void write_record(const string& filename, const string& key, const string& value){
    ofstream file(filename, ios::binary || ios::app);
    if(!file.is_open()){
        cout << "Failed to open the file!" << endl;

        return;

    }

    uint32_t key_len = static_cast<uint32_t>(key.size());
    uint32_t val_len = static_cast<uint32_t>(value.size());


}

int main(){

    

    return 0;
}