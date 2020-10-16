#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Record {
    string country_or_area;
    string year;
    string comm_code;
    string commodity;
    string flow;
    string trade_usd;
    string weight_kg;
    string quantity_name;
    string quantity;
    string category;
};

struct Record2 {
    string zip_code;
    string county_name;
    string state_name; 
    string name; 
    string addrs1; 
    string city; 
    string abbrev; 
    string zip; 
    string web_addr; 
    string textcond; 
    string sp_textcond; 
    string description; 
    string over65; 
    string under65; 
    string na_available; 
    string community; 
    string issue; 
    string attained; 
    string na_rating;
    string last_mod;
};

struct Bucket
{
    int size;
    int local_depth;
    Bucket* next_bucket;
    vector<pair<string, long>> registros;
    /* string name; */
};

template <typename R>
class Hash{
    private:
        unordered_map<string, Bucket> hash;
        fstream archIndex;
        fstream archData;
        string archName;
        string archDataName;
        int max_global_depth;
        int global_depth;
        int block_factor;
        /* string key; */
    public:
        Hash(string archIndexName, string dataName)
        {
            archName = archIndexName;
            archDataName = dataName;
            cout << "Inserte factor de bloque: ";
            cin >> block_factor;
            cout << "Inserte maximo de nivel global: ";
            cin >> max_global_depth;
            global_depth = 1;
            /* hash["0"] = 0;
            hash["1"] = sizeof(Bucket); 
            archIndex.open(archName, ios::binary | ios::out); */
            Bucket zero;
            Bucket one;
            zero.next_bucket = nullptr;
            one.next_bucket = nullptr;
            zero.size = 0;
            one.size = 0;
            zero.local_depth = 1;
            one.local_depth = 1;
            hash["0"] = zero;
            hash["1"] = one;
        }
        void insert(R registro, string key){
            fstream removedData;
            removedData.open("eliminados.dat", ios::binary | ios::ate);
            long address = -1;
            int size = 0;
            if (removedData)
            {
                file.seekg(0, ios::end);
                size = (int)file.tellg();
                file.seekg(0, ios::beg);
            }
            if (size > 0){
                int valid = 0;
                int cont =-1;
                while (valid == 0 & !removedData.eof())
                {
                    removedData.read((char *)address, sizeof(address));
                    removedData.read((char *)valid, sizeof(valid));
                    cont++;
                }
                if (valid != 0){
                    valid = 0;
                    removedData.seekg(cont * (sizeof(long) + sizeof(int)) + sizeof(long));
                    removedData.write((char *)valid, sizeof(valid));
                    archData.open(archDataName, ios::binary | ios::ate);
                    archData.seekg(address);
                }
            }
            if (size == 0 || address == -1) {
                archData.open(archDataName, ios::binary | ios::app);
                address = archData.tellp();
            }
            archData.write((char *)&registro, sizeof(registro));
            archData.close();
            removedData.close();
            string hashCode = hashing(key);
            string newHash;
            Bucket bucket;
            int contDepth = 0;
            bool encontrado = false;
            while (contDepth < global_depth && !encontrado)
            {
                contDepth++;
                newHash = hashCode.substr(hashCode.length() - contDepth);
                if (hash.find(newHash) != hash.end())
                {
                    bucket = hash[newHash];
                    encontrado = true;
                }
            }
            bool overflow = false;
            while (bucket.next_bucket != nullptr)
            {
                bucket = *(bucket.next_bucket);
                overflow = true;
            }
            if (bucket.size < block_factor){
                bucket.size++;
                bucket.registros.push_back(make_pair(hashCode, address));
            } else {
                if (bucket.local_depth < max_global_depth) {
                    Bucket newBucket;
                    newBucket.local_depth = ++bucket.local_depth;
                    newBucket.next_bucket = nullptr;
                    string hashToReallocate;
                    string newHash0 = "0" + newHash;
                    string newHash1 = "1" + newHash;
                    for (int i = 0; i < bucket.size; i++)
                    {
                        hashToReallocate = bucket.registros[i].first;
                        if (hashToReallocate.substr(hashToReallocate.length() - bucket.local_depth) == newHash1){
                            newBucket.registros.push_back(bucket.registros[i]);
                            bucket.registros.erase(bucket.registros.begin() + i);
                            bucket.size--;
                            newBucket.size++;
                        }
                    }
                    hash.erase(newHash);
                    hash[newHash0] = bucket;
                    hash[newHash1] = newBucket;
                    if (global_depth < bucket.local_depth){
                        global_depth++;
                    }
                } else {
                    Bucket newBucket;
                    newBucket.local_depth = bucket.local_depth;
                    newBucket.next_bucket = -1;
                    newBucket.size = 1;
                    newBucket.registros.push_back(make_pair(hashCode, address));
                    bucket.next_bucket = newBucket;
                }
            }
        };

        string hashing(string key){
            //convierte la cadena a 0, 1,01, 001,
            int suma;
            for (int i = 0; i < key.length(); i++){
                suma += (int)key[i];
            }
            string hashCode;
            for (int i = 0; suma > 0; i++)
            {    
                hashCode += to_string(suma%2);    
                suma = suma/2;  
            }
            return hashCode;
        };

        void remove(string key){
            string hashBinary = hashing(key);
            long posInArch = -1;
            string pos ; //ṕosicion de hash[DeBucket]
            int contDepth = 0;
            bool encontrado = false;
            while (contDepth < global_depth && !encontrado)
            {
                contDepth++;
                // 101010 length = 4, substr(length - 3) = '010'
                pos = hashBinary.substr(hashBinary.length() - contDepth);
                if (hash.find(pos) != hash.end())
                {
                    posInArch = hash[pos];
                    encontrado = true;
                }
            }


        }
        
        R search(string key){
            string hashBinary = hashing(key);
            long posInArch = -1;
            string pos ; //ṕosicion de hash[DeBucket]
            int contDepth = 0;
            bool encontrado = false;
            while (contDepth < global_depth && !encontrado)
            {
                contDepth++;
                // 101010 length = 4, substr(length - 3) = '010'
                pos = hashBinary.substr(hashBinary.length() - contDepth);
                if (hash.find(pos) != hash.end())
                {
                    posInArch = hash[pos];
                    encontrado = true;
                }
            }
            if (encontrado) {
                archIndex.open(archName, ios::in | ios::binary);
                archIndex.seekg(posInArch);
                R registro;
                long posinData;
                Bucket bucket;

                archIndex.read((char *)&bucket, sizeof(bucket));                
                archIndex.close();
                for (int i= 0; i< BLOCK_FACTOR ;i++){
                    posinData = bucket.registros[i];
                    archData.open(archDataName, ios::binary | ios::app);
                    archData.seekg(posinData);
                    archData.read((char *)&registro, sizeof(registro));
                    if (registro.id == key){
                        archData.close();
                        return registro;                               
                    }
                }
            } else {
                cerr << "No se encontro la busqueda";
                return NULL;
            }
        }; 
};

int main(){
    Hash<Record> extensibleHash ("example.dat", "arch.csv");
    return 0;
}