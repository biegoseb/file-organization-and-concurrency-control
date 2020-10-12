#include "sequential-file.hpp"
#include "../parser/parser.hpp"

int main() {

    Parser parser("../parser/sample_data.csv");
    auto animal_records = parser.get_animal_records();

    SequentialFile<AnimalRecord> sqf("data.dat");
    AnimalRecord rec1 ((char*)"Afghanistan",(char*)"2016",10410,(char*)"Sheep live",(char*)"Export",6088,2339,(char*)"Number of items",51,(char*)"01_live_animals");
    AnimalRecord rec2 ((char*)"Argentina",(char*)"2016",10410,(char*)"Sheep live",(char*)"Export",6088,2339,(char*)"Number of items",51,(char*)"01_live_animals");
    //sqf.add_record(rec1);
    //sqf.add_record(rec2);
    sqf.insert_all(*animal_records);
    sqf.print_all();
    //sqf.print_sorted();

    return 0;
}