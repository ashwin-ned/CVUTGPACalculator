#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class CCalc {
private:
    std::ifstream inFile;
    std::vector< std::pair<int, double> > weight;
    int credits;
    double weightTotal;
public:
    /**
     * Constructor
     */
    CCalc ( const char *srcFileName );
    /**
     * Destructor
     */
    ~CCalc ();
    /**
     * Method loads data from a file
     */
    bool readFile ();
    /**
     * Method calculates credit count
     */
    void totalCredits ();
    /**
     * Method calculates total weight count
     */
    void totalWeight ();
    /**
     * Method returns credits value
     */
    int getCredits () const;
    /**
     * Method returns weightTotal value
     */
    double getWeightTotal () const;
    /**
     * Method returns GPA
     */
    double gpa () const;
};

CCalc::CCalc ( const char *srcFileName ) {
    inFile.open(srcFileName, std::ios::binary | std::ios::in);
}
CCalc::~CCalc () {
    inFile.close();
}
bool CCalc::readFile () {
    if( !inFile.is_open() ) {
      std::cout << "Sorry, could not open the file, where is it located?" << std::endl;
      return false;
    }

    while (1) {
        std::string subjectName;
        int credit;
        char grade;
        double flgrade;
        /**
         * First we read a line containing subject name
         */
        getline(inFile, subjectName);

        if( !inFile ) {
          std::cout << "Sorry, smth wrong happened, while read the file" << std::endl;
          break;
        }

        cout << subjectName << endl;

        /**
         * We read credit on the next line
         */
        inFile >> credit;

        if( !inFile ) {
          std::cout << "Sorry, smth wrong happened, while read the file" << std::endl;
          break;
        }

        cout << credit << " ";
        /**
         * We read grade on the same line
         */
        inFile >> grade;

        cout << (char)grade << endl;

        switch( grade )
        {
            case 'A':
                flgrade = 1.0;
                break;
            case 'B':
                flgrade = 1.5;
                break;
            case 'C':
                flgrade = 2.0;
                break;
            case 'D':
                flgrade = 2.5;
                break;
            case 'E':
                flgrade = 3.0;
                break;
            default:
            case 'X':
                flgrade = 0.0;
                break;
        }

        /**
         * Add grade and credit to dynamic array
         */
        weight.emplace_back(credit, flgrade);



        string temp;
        getline(inFile, temp);

        if(inFile.eof()) {
          std::cout << "EOF, exiting while loop" << std::endl;
          break;
        }

        if( !inFile ) {
          std::cout << "Sorry, smth wrong happened, while read the file" << std::endl;
          break;
        }
    }
    return true;
}
void CCalc::totalCredits () {
    credits = 0;
    for( auto subject : weight )
    {
        credits += subject.first;
        std::cout << "Credits = " << credits << " += " << subject.first << std::endl;
    }
}
void CCalc::totalWeight () {
    weightTotal = 0.0;
    for( auto subject : weight )
    {
        std::cout << "WeightTotal = " << subject.first * subject.second + weightTotal << " = "  << weightTotal << " + " << subject.first << " * " << subject.second << std::endl;
        weightTotal += (subject.first * subject.second);
    }
}
int CCalc::getCredits () const {
    return CCalc::credits;
}
double CCalc::getWeightTotal () const {
    return CCalc::weightTotal;
}
double CCalc::gpa () const {
  cout << "WeightTotal = " << CCalc::weightTotal << endl;
  cout << "Credits = " << CCalc::credits << endl;
    return CCalc::weightTotal/CCalc::credits;
}
int main(int argc, const char * argv[]) {

    CCalc calculate("grad.txt");
    calculate.readFile();
    calculate.totalCredits();
    calculate.totalWeight();

    double gpa =  calculate.gpa();

    std::cout << "GPA: ";
    std::cout << std::setprecision (4) << gpa << std::endl;
    return 0;
}
