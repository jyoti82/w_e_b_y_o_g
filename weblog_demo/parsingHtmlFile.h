/* 
 * File:   parsingHtmlFile.h
 * Author: root
 *
 * Created on January 26, 2015, 1:18 AM
 */
#include <iostream>
#include <cstring>      // Needed for memset
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>      // std::istringstream
#include <iostream>
#include<vector>
#include <set>
#include <curl/curl.h>
#include <curl/easy.h>
using namespace std;
#ifndef PARSINGHTMLFILE_H
#define	PARSINGHTMLFILE_H

#endif	/* PARSINGHTMLFILE_H */


set<string> fetchUrlFromHtmlFile(string,string,string);
