#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
/// <summary>
/// A class should only have ONE reason to change
/// </summary>

struct Journal {
    string title;
    vector<string> entries;
     
    Journal(const string& title) : title(title) {}

    void add_entry(const string& entry) {
        static int count = 1;
        entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
    }

    // This is bad because the Journal object is now in charge of writing AS WELL AS saving. 
    // Instead we're going to use a persistence manager
    [[deprecated]]
    void save(const string& filename) {
        ofstream ofs(filename);
        for (auto& e : entries) {
            ofs << e << endl;
        }
    }
};

struct PersistenceManager {
    static void save(const Journal& j, const string& filename) {
        ofstream ofs(filename);
        for (auto& e : j.entries)
            ofs << e << endl;
    }
};

void SingleResponsibilityPrinciple() {
    //journal = Journal{"Dear Diary"}
    Journal journal = Journal("Dear Diary");
    journal.add_entry("entry 1");
    journal.add_entry("entry 2");
    PersistenceManager pm;
    pm.save(journal, "Journal.txt");
}