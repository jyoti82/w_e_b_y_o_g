
#include "parsingHtmlFile.h"
using namespace std;

set<string> fetchUrlFromHtmlFile(string fileNameToParse,string parent_url)
{   string url;
    string complete_url;
    set<string> list;
           int i=0;     
    //vector<string> list;
	 std::ifstream file(fileNameToParse);
	 std::string line;
         std::size_t found;
         std::size_t found_http ;
         
	 while(std::getline(file, line))
	{
            //std::istringstream iss(line);
            
             found = line.find("href");
            
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
                 i=found;
                 if(line[found] == '/') {
                        i++;
                    }
                while(line[found] != '\"' && line[found] != '\'')
                {   /*
                    cout << "string   " << line[found] << endl;
                    url[i++] = line[found++];
                    cout << "url string   " << url[i] << endl;
                    */
                    
                    found++;
                }
                url = line.substr(i,found-i);
                //cout <<"url " << url << endl;
                
               
                // skipping the url's which contain http:// because they may redirect to some other site or server too.
                found_http = url.find("http");
                //list.push_back(url);
                complete_url.clear();
                 if(found_http == std::string::npos && url.compare("#") != 0 ){
                    //http not present in url
                     complete_url.append(parent_url).append(url);
                     list.insert(complete_url);
                     
                 }
                found = line.find("href",found+1);
                 if(found > line.length()){
                   break;
                }
            }
            
	}
         
	return list;

}
