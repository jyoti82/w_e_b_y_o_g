#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    
	 std::ifstream file("input_test.txt");
	 std::string line;
	 while(std::getline(file, line))
	{
            //std::istringstream iss(line);
            
            std::string token;
            std::size_t found = line.find("href");
            
            //if(found!=std::string::npos)
              //  cout<<"line ----->" << line <<endl;
                        
            while(found!=std::string::npos){
                //cout << line[found] << endl;
                found += 4;
                //cout <<line[found] << endl;
                while(line[found] == ' ' || line[found] == '=')
                    found++;
                
                found++; // to get character after '\"' or '\''
                //cout << line[found] << endl;
                std:string url;
                int i=found;
                while(line[found] != '\"' && line[found] != '\'')
                {   /*
                    cout << "string   " << line[found] << endl;
                    url[i++] = line[found++];
                    cout << "url string   " << url[i] << endl;
                    */
                    found++;
                }
                url = line.substr(i,found-i);
                cout <<"url " << url << endl;
                found = line.find("href",found+1);
                if(found > line.length()){
                   // cout << "found " << found<< endl ;
                    break;
                
                }
            }
	}
	return 0;

}
