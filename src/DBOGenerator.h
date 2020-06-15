#include <string>

using namespace std;

class DBOGenerator
{
public:
    string inputDir = ".";  //input directory, default current dir
    string outputDir = "."; //output directory, default current dir

    /**
     * Generate source code
     */
    void generate();
};
