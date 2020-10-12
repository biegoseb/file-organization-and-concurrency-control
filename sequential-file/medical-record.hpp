#ifndef MEDICAL_RECORD_HPP
#define MEDICAL_RECORD_HPP
#include <iostream>
#include <string>
#include <cstring>
using std::cout;
using std::endl;

struct MedicalRecord {
    char zip_code[10];
    char county_name[30];
    char state_name[30]; 
    char name[35]; 
    char addrs1[30]; 
    char city[30]; 
    char abbrev[5]; 
    char zip[10]; 
    //string web_addr; 
    //string textcond; 
    //string sp_textcond; 
    //string description; 
    //string over65; 
    //string under65; 
    //string na_available; 
    //string community; 
    //string issue; 
    //string attained; 
    //string na_rating;
    //string last_mod;
};

#endif // MEDICAL_RECORD_HPP