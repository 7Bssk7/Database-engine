#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <iomanip>

using namespace std;

unordered_map<string, uint64_t> hash_table;

void write_record(const string& filename, const string& key, const string& value, const int& count){
    ofstream file(filename, ios::binary | ios::app);
    if(!file){
        cout << "Failed to open the file!" << endl;

        return;

    }


    if(count > 1){
        file.seekp(0, ios::end);
    }

    uint64_t offset = static_cast<uint64_t>(file.tellp());

    uint32_t key_len = static_cast<uint32_t>(key.size());
    uint32_t val_len = static_cast<uint32_t>(value.size());

    file.write(reinterpret_cast<const char*>(&key_len), sizeof(key_len));
    file.write(reinterpret_cast<const char*>(&val_len), sizeof(val_len));

    file.write(key.data(), key_len);
    file.write(value.data(), val_len);

    file.close();

    hash_table[key] = offset;

    cout << "Saved: '" << key  <<"' with value of '" << value << "' at byte offset " << offset << endl;


}

string read_record(const string& filename, const string& key){
   
    if(hash_table.find(key) == hash_table.end()){
        cout << " Error Key: '" << key << "' was not found" << endl;

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
    bool check = true;

    
    string userName;
    string userMessage; 
    int counter = 0;
    char ch;

    counter += 1;
    write_record(file, "user-1", "Bssk", counter);

    do{
        cout << "Enter your user name: ";
        getline(cin, userName);
        cout << endl;

        cout << "Enter your message: ";
        getline(cin, userMessage);
        cout << endl;

        counter += 1;

        write_record(file, userName, userMessage, counter);

        
        cout << "Press any key to continue, otherwise press 'n'." << endl;
        cin >> ch;
        cin.ignore();

        if(ch == 'n'){
            check = false;
        }


    }while(check != false);


    cout << endl;
    cout << endl;
    
    check = true;
    cout << "------ Look up data from data base ------" << endl;
    cout << "Example: User-1: " << read_record(file, "user-1") << endl;

    do{
        cout << "Enter your user name: ";
        getline(cin, userName);

        cout << userName << ": " << read_record(file, userName) << endl;

        cout << "Press any key to continue, otherwise press 'n'." << endl;
        cin >> ch;
        cin.ignore();

        if(ch == 'n'){
            check = false;
        }

    }while(check != false);

    cout << "Number of elemnts added in this session: " << counter << endl;



    

    return 0;
}