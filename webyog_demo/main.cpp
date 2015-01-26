#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
//#include <curl/types.h>
#include<vector>
#include <curl/easy.h>
#include "parsingHtmlFile.h"
#include <set>
#include <dirent.h>
using namespace  std;
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  int written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int main(void)
{
  CURL *curl_handle;
  static const char *headerfilename = "w3schools/index.html";
  FILE *headerfile;
  set<string> old_list;
  vector<string> new_list;
  string website = "www.w3schools.com/";
  std::set<string>::iterator it;
  
 // static const char *bodyfilename = "body.html";
 // FILE *bodyfile;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* set URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "www.w3schools.com/");

  /* no progress meter please */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  /* open the files */
  headerfile = fopen(headerfilename,"w");
  if (headerfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }

  /* we want the headers to this file handle */
  curl_easy_setopt(curl_handle,   CURLOPT_WRITEDATA, headerfile);

  /*
   * Notice here that if you want the actual data sent anywhere else but
   * stdout, you should consider using the CURLOPT_WRITEDATA option.  */

  /* get it! */
  curl_easy_perform(curl_handle);

  /* close the header file */
  fclose(headerfile);

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  old_list = fetchUrlFromHtmlFile("w3schools/index.html",website);
  
  set<string> parsed_set(old_list.begin(),old_list.end()); // parsed_set; // unique list to check whehter the url has been visited earlier;
  
  cout << "printing ***** parsed_set  ******" << endl;
  string urlToDownload;
  string commandToRun;
  string fileName;
  string w3schools;
  std::size_t found;
  vector<string> dir_vector;
  for (it=parsed_set.begin(); it!=parsed_set.end(); ++it){
      fileName.clear();
    urlToDownload = *it;
    found = urlToDownload.find('/');
    fileName = urlToDownload;
    //cout << fileName << "fileName" <<endl;
    if(found!=std::string::npos)
        fileName = fileName.substr(found+1);
    else
        continue;
    //cout << fileName << "fileName" <<endl;
    headerfile = fopen(fileName.c_str(),"w");
    if (headerfile == NULL) {
        commandToRun = "./myfile.sh ";
        commandToRun.append(fileName);
       // cout << commandToRun.c_str() << "    commandToRun" <<endl;
        system(commandToRun.c_str());
    }
    //dir_vector = parseUrlToDirectoryVector(urlToDownload);
    //system("./myfile.sh ");
     fclose(headerfile);
 cout << fileName << " open fileName" <<endl;
    w3schools = "w3schools/";
    w3schools.append(fileName);
    headerfile = fopen(w3schools.c_str(),"w");
    
  curl_handle = curl_easy_init();

  if (headerfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
  else
  {
      cout << fileName << " opened ";
  }
     
  curl_easy_setopt(curl_handle, CURLOPT_URL,urlToDownload.c_str()  );

    curl_easy_setopt(curl_handle,   CURLOPT_WRITEDATA, headerfile);
 
  curl_easy_perform(curl_handle);

    fclose(headerfile);

  curl_easy_cleanup(curl_handle);
  

  }
  
  
  
  return 0;
}
