#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;
#define BLOCK_FACTOR 4

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

/* void read_Bucket(string arch, Bucket &bucket)
{
    fstream archB;
    archB.open(arch, ios::binary | ios::in);
    if (archB.is_open()){
        string line;
        getline(archB, line);
        bucket.size = stoi(line);
        getline(archB, bucket.next_bucket);
        string delim = ",";
        for (int i = 0; i < bucket.size; i++)
        {
            Record registro;
            size_t last = 0;
            size_t next = 0;
            int cont = 0;
            getline(archB, line);
            while((next = line.find(delim, last)) != string::npos) {
                switch (cont)
                {
                case 0:
                    registro.country_or_area = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 1:
                    registro.year = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 2:
                    registro.comm_code = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 3:
                    registro.commodity = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 4:
                    registro.flow = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 5:
                    registro.trade_usd = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 6:
                    registro.weight_kg = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 7:
                    registro.quantity_name = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 8:
                    registro.quantity = line.substr(last, next - last);
                    last = next + 1;
                    cont++;
                    break;
                case 9:
                    registro.category = line.substr(last);
                    break;
                }
            }
            bucket.registros.push_back(registro);
        }
    }
}
*/

struct Bucket
{
    int size;
    long next_bucket;
    long registros[BLOCK_FACTOR];
    int local_depth;
    /* string name; */
};

template <typename R>
class Hash{
    private:
        unordered_map<string, long> hash;
        fstream archIndex;
        fstream archData;
        string archName;
        string archDataName;
        int max_global_depth;
        int global_depth;
        /* int block_factor; */
        /* string key; */
    public:
        Hash(string archIndexName, string dataName)
        {
            archName = archIndexName;
            archDataName = dataName;
            /* cout << "Inserte factor de bloque: ";
            cin >> block_factor; */
            /* cout << "Inserte la key para el hash: ";
            cin >> key; */
            cout << "Inserte maximo de nivel global: ";
            cin >> max_global_depth;
            global_depth = 1;
            hash["0"] = 0;
            hash["1"] = sizeof(Bucket);
            archIndex.open(archName, ios::binary | ios::out);
            Bucket zero;
            Bucket one;
            zero.next_bucket = -1;
            one.next_bucket = -1;
            zero.size = 0;
            one.size = 0;
            zero.local_depth = 1;
            one.local_depth = 1;
            /* zero.registros[0] = 0;
            zero.registros[1] = 1;
            zero.registros[2] = 2;
            zero.registros[3] = 3;
            one.registros[3] = 5;
            archIndex.seekg(hash["0"]);
            archIndex.write((char *)& zero, sizeof(Bucket));
            archIndex.seekg(hash["1"]);
            archIndex.write((char *)& one, sizeof(Bucket));
            archIndex.close();

            //prueba
            archIndex.open(archName, ios::in | ios::binary);
            Bucket test1;
            Bucket test2;
            archIndex.seekg(hash["0"]);
            archIndex.read((char *)&test1, sizeof(Bucket));
            archIndex.seekg(hash["1"]);
            archIndex.read((char *)&test2, sizeof(Bucket));
            archIndex.close();
            cout << test1.next_bucket << endl;
            cout << test1.size << endl;
            cout << test1.registros[0] << endl;
            cout << test1.registros[1] << endl;
            cout << test1.registros[2] << endl;
            cout << test1.registros[3] << endl;
            cout << test2.next_bucket << endl;
            cout << test2.size << endl;
            cout << test2.registros[0] << endl;
            cout << test2.registros[1] << endl;
            cout << test2.registros[2] << endl;
            cout << test2.registros[3] << endl;
            */
        }
        void insert(R registro, string key){
            archData.open(archDataName, ios::binary | ios::app);
            long address = archData.tellp();
            archData.write((char *)&registro, sizeof(registro));

            string hashCode = hashing(key);
            long posInArch;
            int contDepth = 0;
            bool encontrado = false;
            while (contDepth < global_depth && !encontrado)
            {
                contDepth++;
                if (hash.find(hashCode.substr(hashCode.length() - contDepth)) != hash.end()){
                    posInArch = hash[hashCode.substr(hashCode.length() - contDepth)];
                    encontrado = true;
                }
            }
            Bucket bucket;
            archIndex.open(archName, ios::binary | ios::ate);
            archIndex.seekg(posInArch);
            archIndex.read((char *)&bucket, sizeof(bucket));
            long lastBucket = -1;
            while (bucket.next_bucket != -1)
            {
                lastBucket = bucket.next_bucket;
                archIndex.seekg(bucket.next_bucket);
                archIndex.read((char *)&bucket, sizeof(Bucket));
            }
            if (bucket.size < BLOCK_FACTOR)
            {
                bucket.size = bucket.size + 1;
                bucket.registros[bucket.size - 1] = address;
                (lastBucket == -1) ? archIndex.seekg(posInArch) : archIndex.seekg(lastBucket);
                archIndex.write((char *)&bucket, sizeof(Bucket));
                /* archIndex.seekg(lastBucket + sizeof(int) + sizeof(long) + sizeof(long) * bucket.size);
                archIndex.write((char *)&address, sizeof(long)); */
            } else if (bucket.local_depth < max_global_depth) {
                bool inserted = false;
                while (!inserted){
                    Bucket newBucket;
                    newBucket.next_bucket = -1;
                    string hashNew;
                    for (int i = 0; i < bucket.size; i++)
                    {
                        hashNew = hashing(bucket.registros[i]);

                    }
                }
            } else {
                Bucket newBucket;
                newBucket.next_bucket = -1;
                newBucket.size = 1;
                newBucket.registros[0] = address;
                archIndex.seekg(0, ios::end);
                bucket.next_bucket = (long)archIndex.tellg();
                (lastBucket == -1) ? archIndex.seekg(posInArch) : archIndex.seekg(lastBucket);
                archIndex.write((char *)&bucket, sizeof(Bucket));
                archIndex.seekg(bucket.next_bucket);
                archIndex.write((char *)&newBucket, sizeof(Bucket));
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