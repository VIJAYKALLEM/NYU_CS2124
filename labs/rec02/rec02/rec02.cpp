/* 
 Simran Soin
 Recitation 2
 Store and Sort Molecular Formulas From File
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct MolecularFormula;
void openStream(ifstream& file);
bool addNameIfInFormulas(vector<MolecularFormula>& formulas, int carbon_atoms, int hydrogen_atoms, const string& name);
void fillVector(vector<MolecularFormula>& formulas, ifstream& file);
bool smallerHCarbon(const MolecularFormula& hcarbon1, const MolecularFormula& hcarbon2);
void sortVector(vector<MolecularFormula>& formulas);
void displayVector(const vector<MolecularFormula>& formulas);
MolecularFormula createHydrocarbon (const string& name, int carbon_atoms, int hydrogen_atoms);

int main() {
    vector<MolecularFormula> formulas;
    ifstream file;
    openStream(file);
    fillVector(formulas, file);
    sortVector(formulas);
    displayVector(formulas);
}

struct MolecularFormula {
    vector<string> formula_name;
    int carbon_atoms;
    int hydrogen_atoms;
};

void openStream(ifstream& file){
    while (!file.is_open()){
        string file_name;
        cout << "Enter file name: ";
        cin >> file_name;
        file.open(file_name);
    }
}

MolecularFormula createHydrocarbon(const string& name, int carbon_atoms, int hydrogen_atoms){
    MolecularFormula hydrocarbon;
    hydrocarbon.formula_name.push_back(name);
    hydrocarbon.carbon_atoms = carbon_atoms;
    hydrocarbon.hydrogen_atoms = hydrogen_atoms;
    return hydrocarbon;
}

bool smallerHCarbon(const MolecularFormula& hcarbon1, const MolecularFormula& hcarbon2){
    bool smaller = false;
    if (hcarbon1.carbon_atoms < hcarbon2.carbon_atoms){
        smaller = true;
    }
    else if ((hcarbon1.carbon_atoms == hcarbon2.carbon_atoms) && (hcarbon1.hydrogen_atoms < hcarbon2.hydrogen_atoms)){
        smaller = true;
    }
    return smaller;
}

bool addNameIfInFormulas(vector<MolecularFormula>& formulas,
    int carbon_atoms, int hydrogen_atoms, const string& name){
    
    bool formula_already_added = false;
    for (MolecularFormula& formula : formulas) {
        if (formula.carbon_atoms == carbon_atoms && formula.hydrogen_atoms == hydrogen_atoms) {
            formula.formula_name.push_back(name);
            formula_already_added = true;
            break;
        }
    }
    return formula_already_added;
}


void fillVector(vector<MolecularFormula>& formulas, ifstream& file){
    string name;
    char element;
    int carbon_atoms;
    int hydrogen_atoms;
    while (file >> name >> element >> carbon_atoms >> element >> hydrogen_atoms) {
        bool formula_already_added = addNameIfInFormulas(formulas, carbon_atoms, hydrogen_atoms, name);
        // if formula_already_added is false, then create a new hydrocarbon with the data
        if (!formula_already_added) {
            MolecularFormula hcarbon = createHydrocarbon(name, carbon_atoms, hydrogen_atoms);
            // add hydrocarbon to formulas vector
            formulas.push_back(hcarbon);
        }
    }
}

void sortVector(vector<MolecularFormula>& formulas) {
    size_t smallest_index;
    // selection sort
    for (size_t i=0; i<formulas.size(); ++i){
        smallest_index = i;
        for (size_t j=i+1; j<formulas.size(); ++j){
            if (smallerHCarbon(formulas[j], formulas[smallest_index])){
                smallest_index = j;
            }
        }
        MolecularFormula temp_storage;
        temp_storage = formulas[i];
        formulas[i] = formulas[smallest_index];
        formulas[smallest_index] = temp_storage;
    }
}

void displayVector(const vector<MolecularFormula>& formulas){
    for (const MolecularFormula formula: formulas){
        cout << "C" << formula.carbon_atoms << "H" << formula.hydrogen_atoms;
        for (const string& name : formula.formula_name) {
            cout << " " << name;
        }
        cout << endl;
    }
}
