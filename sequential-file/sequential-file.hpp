/*************************************
 * Sequential File implementation
 *************************************/

#include <vector>
#include <algorithm>
#include <fstream>
#include "animal-record.hpp"
//#include "medical-record.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::to_string;

template <class T>
class SequentialFile {
    string file_name;
    string aux_name;
    int count;
    int first;
    int fl_root;
    //char page;
    int num_records();
    vector<T> sorted_records(fstream& file);

public:
    SequentialFile(const string& file_name);
    int init_first();
    int init_freelist();
    void print_all();
    void print_sorted();
    void insert_all(vector<T>& records);
    T search_by_key(const string& key);
    vector<T> search_by_range(const string& beg, const string& end);
    void add_record(T& record);
    void delete_record(int pos);  // FreeList (LIFO Stack)
};

template <class T>
int SequentialFile<T>::num_records() {
    int num_records;
    if (first == -1) {  // empty file
        num_records = 0;
    } else {
        fstream in_file;
        in_file.open(file_name, ios::in | ios::binary);
        if (in_file.is_open()) {
            in_file.seekg(0, ios::end);
            long bytes = in_file.tellg();
            num_records = (bytes - sizeof(int) * 2) / sizeof(T);
            in_file.close();
        } else {
            cout << "Could not open the file " << file_name << endl;
        }
    }
    
    return num_records;
}

template <class T>
vector<T> SequentialFile<T>::sorted_records(fstream& in_file) {
    vector<T> sorted_records;
    int first_temp;
    int root_temp;
    T record;
    
    in_file.seekg(0, ios::beg);
    in_file.read((char*)&first_temp, sizeof(int));
    in_file.read((char*)&root_temp, sizeof(int));
    if (first_temp != -1) {
        /* Locate cursor at the first sorted record */
        in_file.seekg(first_temp * sizeof(T) + sizeof(first_temp) * 2);
        in_file.read((char*)&record, sizeof(record));
        sorted_records.push_back(record);

        /* Read record by record */
        string nextPtr = to_string(record.next) + record.page;
        while (nextPtr != "-1d") {      
            in_file.seekg(record.next * sizeof(T) + sizeof(int) * 2);
            in_file.read((char*)&record, sizeof(record));
            sorted_records.push_back(record);
            nextPtr = to_string(record.next) + record.page;        
        }
    }
    return sorted_records;
}

/* Public methods */

template <class T>
SequentialFile<T>::SequentialFile(const string& file_name) {
    this->file_name = file_name;
    this->first = init_first();
    this->fl_root = init_freelist();
    this->count = num_records();  
}

template <class T>
int SequentialFile<T>::init_first() {
    int first_temp;  
    /* Check if First has already been created */
    bool ready = false;
    fstream file;
    file.open(file_name, ios::in | ios:: binary | ios::ate);
    
    if (file.is_open()) {  
        long bytes = file.tellg();
        ready = bytes >= (sizeof(T) + sizeof(int) * 2);   
        file.seekg(0, ios::beg);
        file.read((char*)&first_temp, sizeof(int));
        file.close();
    }

    /* Create the file with First ptr to NULL */
    if (!ready) {      
        first_temp = -1; 
        file.open(file_name, ios::in | ios::out | ios::binary);
        if (file.is_open()) {
            if (file.tellp() == 0) {  // empty binary file
                file.write((char*)&first_temp, sizeof(int));
            }
            file.close();
        }
    }

    return first_temp;
}

template <class T>
int SequentialFile<T>::init_freelist() {
    int first_temp;
    int root_temp;
    /* Check if First has already been created */
    bool ready = false;
    fstream file;
    file.open(file_name, ios::in | ios::binary | ios::ate);
    if (file.is_open()) {
        long bytes = file.tellg();
        ready = bytes >= (sizeof(T) + sizeof(int) * 2);
        file.seekg(0, ios::beg);
        file.read((char*)&first_temp, sizeof(int));
        file.read((char*)&root_temp, sizeof(int));
        file.close();
    }

    /* Create the file with First ptr to NULL */
    if (!ready) {      
        root_temp = -1; 
        file.open(file_name, ios::in | ios::out | ios::binary);
        if (file.is_open()) {
            if (file.tellp() == 0) {       // empty binary file
                file.seekg(sizeof(int));   // first
                file.write((char*)&root_temp, sizeof(int));
            }
            file.close();
        }
    }

    return root_temp;
}

template <class T>
void SequentialFile<T>::print_all() {
    int first_temp;
    int root_temp;
    ifstream in_file;
    T record;
    in_file.open(file_name, ios::in | ios::binary);
    in_file.read((char*)&first_temp, sizeof(int));
    in_file.read((char*)&root_temp, sizeof(int));
    
    cout << RED << "\t\tBINARY FILE: " << RESET << file_name << endl;
    cout << RED << "First: " << this->first << "d" << RESET << endl;
    cout << RED << "FL Root: " << this->fl_root << "d" << RESET << endl;
    record.print_headers();
    int count = 0;
    while (in_file.read((char*)&record, sizeof(record))) {
        // TODO: avoid deleted records
        record.print_info(count++, record.page);
    }
    in_file.close();  
    cout << endl; 
}

template <class T>
void SequentialFile<T>::print_sorted() {
    //if (first != -1) {
    //    // Locate cursor at the first sorted record
    //    in_file.seekg(first * sizeof(Record) + sizeof(first));
    //    in_file.read((char*)&record, sizeof(record));
    //    record.print_info(count++, record.page);
    //
    //    // Read and print record by record
    //    string nextPtr = to_string(record.next) + record.page;
    //    while (nextPtr != "-1d") {      
    //        in_file.seekg(record.next * sizeof(Record) + sizeof(int));
    //        in_file.read((char*)&record, sizeof(record));
    //        record.print_info(count++, record.page);
    //        nextPtr = to_string(record.next) + record.page;        
    //    }
    //}

    fstream in_file;
    in_file.open(file_name, ios::in | ios::binary);
    auto v = sorted_records(in_file);
    cout << "SIZE: " << v.size() << endl;
    cout << "First: " << first << endl;
    cout << "FL Root: " << fl_root << endl;
    cout << "Count: " << count << endl;
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i].name << "-" << v[i].pos << endl;
    }
    in_file.close();
}

template <class T>
void SequentialFile<T>::insert_all(vector<T>& records) {
    for (T& record : records) {
        record.pos = count;
        record.page = 'd';
        add_record(record);   
    }
}

template <class T>
T SequentialFile<T>::search_by_key(const string& key) {
    char name_key[20];
    strcpy(name_key, key.c_str());
    bool found = false; 

    T temp, record;
    fstream in_file;
    in_file.open(file_name, ios::in | ios::binary);

    if (in_file.is_open()) {
        /* Binary search O(logn) */
        vector<T> sorted = sorted_records(in_file);
        int left  = 0;                  // first index record
        int right = sorted.size() - 1;  // last index record
        int mid;

        while (right >= left && !found) {
            mid = (left + right) / 2;
            int pos = sorted[mid].pos;

            /* Locate cursor at the beginnig of the record and read */
            in_file.seekg(pos * sizeof(temp) + sizeof(int));
            in_file.read((char*)&temp, sizeof(temp));

            if (strcmp(name_key, temp.name) == 0) {
                record = temp;
                break;
            } else if (strcmp(name_key, temp.name) < 0) {
                right = mid - 1;  // take the first part of the array file (lower)
            } else if (strcmp(name_key, temp.name) > 0) {
                
                left = mid + 1;   // take the second part of the array file (higher)
            }
        }
        in_file.close();
    }
    return record;
}

template <class T>
void SequentialFile<T>::add_record(T& record) {
    // TODO: when file already has records and need to insert more records
    T temp;
    fstream file;

    file.open(file_name, ios::in | ios::out | ios::binary);
    if (file.is_open()) {
        record.pos = count;
        record.page = 'd';     
        if (first == -1) {  // no records
            /* Write at the end of file */
            file.seekg(0, ios::end);
            record.next = -1;
            record.page = 'd';
            file.write((char*)&record, sizeof(record));

            /* Overwrite updated first index in file */
            first = 0;
            file.seekg(0, ios::beg);     
            file.write((char*)&first, sizeof(int));
        } else {
            /* Binary search O(logn) */
            vector<T> sorted = sorted_records(file);
            int left  = 0;                  // first index record
            int right = sorted.size() - 1;  // last index record
            int mid;

            while (right >= left) {
                mid = (left + right) / 2;
                int pos = sorted[mid].pos;

                /* Locate cursor at the beginnig of the record and read */
                file.seekg(pos * sizeof(temp) + sizeof(int) * 2);
                file.read((char*)&temp, sizeof(temp));

                if (strcmp(record.country, temp.country) < 0) {            
                    right = mid - 1;  // take the first part of the array file (lower)
                } else {       
                    left = mid + 1;   // take the second part of the array file (higher)
                }
            }

            /* Locate cursor at prev record and read */
            int prev;
            if (right < 0) {
                prev = sorted[0].pos;
            } else {
                prev = sorted[right].pos;
            }
            file.seekg(prev * sizeof(T) + sizeof(int) * 2);
            file.read((char*)&temp, sizeof(T));

            /* Update next pointers */
            if (first == temp.pos && right != 0) {
                T ex_first;
                record.next = temp.pos; // make new record point to first
                record.prev = -1;

                /* Update prev of ex-first */
                temp.prev = record.pos;
                file.seekg(temp.pos * sizeof(T) + sizeof(int) * 2);
                file.write((char*)&temp, sizeof(T));

                /* Update and ow first index if prev is the first sorted record */
                first = num_records();
                file.seekg(0, ios::beg);     
                file.write((char*)&first, sizeof(int));
            } else {
                record.next = temp.next;    // make new record point to next of temp
                temp.next = record.pos;     // make prev record point to new record
                record.prev = temp.pos;    // make new record point to temp

                /* Relocate cursor at prev record and write */
                file.seekg(temp.pos * sizeof(T) + sizeof(int) * 2);
                file.write((char*)&temp, sizeof(T));
                
                if (record.next != -1) {
                    file.seekg(record.next * sizeof(T) + sizeof(int) * 2);
                    file.read((char*)&temp, sizeof(T));
                    temp.prev = record.pos;
                    file.seekg(record.next * sizeof(T) + sizeof(int) * 2);
                    file.write((char*)&temp, sizeof(T));
                }
            }

            /* Write new record at the end of file */
            file.seekg(0, ios::end);
            file.write((char*)&record, sizeof(T));
        }
        ++count;
        file.close();
    }
}

template <class T>
void SequentialFile<T>::delete_record(int pos) {
    fstream file;
    T rec, prev_rec, next_rec;
    file.open(file_name, ios::in | ios::out | ios::binary);
    if (file.is_open()) {
        /* read FreeList header and First */
        int firstPtr;
        int rootPtr;
        file.read((char*)&firstPtr, sizeof(int));
        file.read((char*)&rootPtr, sizeof(int));

        /* locate the cursor and read the record */
        file.seekg(pos * sizeof(T) + sizeof(int) * 2);
        file.read((char*)&rec, sizeof(T));


        // TODO: first and last
        /* update prev and next sorted record */
        file.seekg(rec.prev * sizeof(T) + sizeof(int) * 2);
        file.read((char*)&prev_rec, sizeof(T));
        prev_rec.next = rec.next;
        file.seekg(rec.next * sizeof(T) + sizeof(int) * 2);
        file.read((char*)&next_rec, sizeof(T));
        next_rec.prev = rec.prev; 


        /* update its nextdel */
        rec.next_del = rootPtr;

        /* write and update the records */  
        file.seekg(rec.prev * sizeof(T) + sizeof(int) * 2);
        file.write((char*)&prev_rec, sizeof(T));
        file.seekg(rec.next * sizeof(T) + sizeof(int) * 2);
        file.write((char*)&next_rec, sizeof(T));
        file.seekg(pos * sizeof(T) + sizeof(int) * 2);
        file.write((char*)&rec, sizeof(T));

        /* write delete ptr */
        fl_root = pos;
        file.seekg(0, ios::beg);
        file.read((char*)&firstPtr, sizeof(int));
        file.write((char*)&fl_root, sizeof(int));

        file.close();
    } else {
        cout << "Could not open the file " << file_name << endl;
    }
}