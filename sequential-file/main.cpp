#include "sequential-file.hpp"
#include "../parser/parser.hpp"
#include "time.h"

int main() {

    std::ios_base::sync_with_stdio(false); 
    clock_t start, end; 
    //Parser parser("../parser/sales-records.csv");
    Parser parser ("../parser/sales-sample.csv");
    auto sale_records = parser.get_sale_records();

    SequentialFile<SaleRecord> sqf("data-temp.dat");
    //SaleRecord rec1 ((char*)"Ciego", (char*)"ciego", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    //SaleRecord rec2 ((char*)"Biego", (char*)"biego", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    //SaleRecord rec3 ((char*)"Aiego", (char*)"aiego", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    //SaleRecord rec4 ((char*)"Diego", (char*)"diego", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    //sqf.add_record(rec1);
    //sqf.add_record(rec2);
    //sqf.add_record(rec3);
    //sqf.add_record(rec4);
    start = clock(); 
    sqf.insert_all(*sale_records);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << std::fixed  
         << time_taken / 1000 << std::setprecision(5) << " ms " << endl;
    //sqf.delete_record(13);
    //sqf.delete_record(11);
    //sqf.delete_record(17);
    //sqf.print_all();
    //sqf.print_sorted();

    return 0;
}