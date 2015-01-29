#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
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
string base_url;
set<string> parsed_set ; // holds downloaded urls;
set<string> functionToDownloadUrl(set<string> );
set <string> functionToParseList(set<string> );
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  int written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int main(void)
{
  CURL *curl_handle;
  static const char *headerfilename = "index.html";
  FILE *headerfile;
  set<string> old_list;
  set<string> new_list;
  string website_url ;
  size_t found_hash;
  std::set<string>::iterator it,temp;
  long respcode;
 // static const char *bodyfilename = "body.html";
 // FILE *bodyfile;
  cout << "Enter site name to download "<<endl;
  cin >> website_url;
  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* set URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, website_url.c_str());

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
  found_hash = website_url.find('/',website_url.length()-1);
   if(found_hash == std::string::npos)
   {
       website_url.append("/");
   }
  found_hash = website_url.find('/');
  cout<<website_url<<endl;
  base_url = website_url.substr(0,found_hash+1);
  cout<<base_url<<endl;
  old_list = fetchUrlFromHtmlFile("index.html",website_url,base_url);
  
  // parsed_set.insert(old_list.begin(),old_list.end()); // parsed_set; // unique list to check whehter the url has been visited earlier;
  
    cout << "printing ***** parsed_set  ******" << endl;
    for (it=old_list.begin(); it!=old_list.end(); ++it)
    {
        cout << *it <<endl;
    }
    do{
        
        new_list = functionToDownloadUrl(old_list);
        /*
        if(old_list.empty())
            break;
         */
        /*
        new_list.insert("files/dtd/dtd_examples.asp");
        new_list.insert("files/index.html");
        new_list.insert("files/html/default.asp");
        new_list.insert("files/html/json/default.asp");
        */
        
        old_list = functionToParseList(new_list);
        
        //break;
    }while(!old_list.empty());
 
 // old_list.insert(new_list.begin(),new_list.end());
 // }while(new_list.size() != 0);
return 0;
}

//function returns files to parse for new links
set<string> functionToDownloadUrl(set<string> old_list){
    string urlToDownload;
    string commandToRun;
    string fileName;
    string w3schools,parent;
    string find_url;
    std::size_t found;
    set<string> file_to_parse_list;
    vector<string> dir_vector;
    CURL *curl_handle;
    FILE *fp;
    std::set<string>::iterator it,temp;
    //pair  iterator to know whether the element is inserted in set or no
    std::pair<std::set<string>::iterator,bool> ret;
  
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    for (it=old_list.begin(); it!=old_list.end(); ++it)
    {
        fileName.clear();
        urlToDownload = *it;
        found = urlToDownload.find('/');
        fileName = urlToDownload;
        ret = parsed_set.insert(urlToDownload);
        if(ret.second == false){
            cout<< "this url already downloaded  "<< urlToDownload<<endl; 
            continue;
        }
        if(found!=std::string::npos)
            fileName = fileName.substr(found+1);
        else
            continue;
     
        //fileName = fileName.substr(website_url.length());
        
        //fp = fopen(fileName.c_str(),"w");
        //if (fp == NULL) {
            commandToRun = "./myfile.sh ";
            commandToRun.append(fileName);
            system(commandToRun.c_str());
        //}
        //fclose(fp);
        cout << fileName << " open fileName" <<endl;
        w3schools = "files/";
        //w3schools = "";
        w3schools.append(fileName);
        fp = fopen(w3schools.c_str(),"w");
        curl_handle = curl_easy_init();
        if (fp == NULL) 
        {
            curl_easy_cleanup(curl_handle);
            //return -1;
            continue;
        }
        else
        {
            cout << w3schools << " opened "<<endl;
        }
        curl_easy_setopt(curl_handle, CURLOPT_URL,urlToDownload.c_str()  );
        curl_easy_setopt(curl_handle,   CURLOPT_WRITEDATA, fp);
        curl_easy_perform(curl_handle);
        // if file size is zero delete it.
        fclose(fp);
        file_to_parse_list.insert(w3schools); // added file to html link parsing list
        curl_easy_cleanup(curl_handle);
        parsed_set.insert(*it);
    }
    cout << "printing ***** file_to_parse_list  ******" << endl;
    for (it=file_to_parse_list.begin(); it!=file_to_parse_list.end(); ++it)
    {
        cout << *it <<endl;
    }
    return file_to_parse_list;
}

//function returns url's to download
set <string> functionToParseList(set<string> new_list){
    set<string> list_to_download,temp_list;
    std::set<string>::iterator it,temp;
    string website_url;
    string filename;
    size_t first_slash,last_slash;
    std::pair<std::set<string>::iterator,bool> ret;
  
    cout << "printing ***** file names to parse  ******" << endl;
    for (it=new_list.begin(); it!=new_list.end(); ++it)
    {
        temp_list.clear();
        cout << *it <<endl;
        filename = *it;
        first_slash = filename.find('/');
        last_slash = filename.find_last_of('/');
        website_url.clear();
        if((first_slash != last_slash) && (first_slash !=std::string::npos) && last_slash!=std::string::npos){
            //cout << last_slash << " last slash";
            //cout << filename.length() << " filename.length()";
            website_url.append(base_url).append(filename.substr(first_slash+1,last_slash-first_slash));
            cout<< website_url <<"   website_url"<<endl;
        }else{
            website_url.append(base_url);
        }
        cout<< filename <<"   filename"<<endl;
        temp_list = fetchUrlFromHtmlFile(filename,website_url,base_url);
        //cout << "printing ***** file names to download  ******" << endl;
        for (temp=temp_list.begin(); temp!=temp_list.end(); ++temp)
        {
            //cout << *temp << "to download";
            ret = parsed_set.insert(*temp);
            if(ret.second == true){
                list_to_download.insert(*temp);
                parsed_set.erase(*temp);
            }
            
        }
        
    }
    
    return list_to_download;
}