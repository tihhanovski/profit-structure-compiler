#include <string>
#include <fstream>
#include <iostream>
#include <dirent.h>

using namespace std;

int main()
{
    DIR *dir;
    struct dirent *ent;
    unsigned char isFile =0x8;
    unsigned char isFolder =0x4;


    if ((dir = opendir ("../samples/sampleproject/tables")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL)
      {
          cout << ent->d_name << (ent->d_type == isFolder ? "/" : "") << endl;
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      return EXIT_FAILURE;
    }
}
