
#include <stddef.h>
#include <iostream>
#include <string.h>
#include "string.h"

using namespace std;

/**
    * @brief Initiates an empty string
    */
String::String() {
    length = 0;
    data = NULL;
}

/**
   * @brief Initiates string from other string
   */
String::String(const String &str) {
    if (str.length == 0) {
        data = NULL;
    } else {
//    length = str.length;
        data = new char[str.length + 1];
        strcpy(data, str.data);
    }
}


/**
     * @brief Initiates a string from char array
     */
String::String(const char* str) {
	if(str != NULL){
		length = strlen(str);
		int tmp=strlen(str)+1;
		data = new char[tmp];
		strcpy(data,str);
	}
	else{
		data=NULL;
		length=0;
	}

}






String::~String() {
if(data != nullptr){
    delete[] data;
    data = nullptr;
    length = 0; //34567890-
    }
}

/**
     * @brief Changes this from String
     */
String &String::operator=(const String &rhs) {
    if (rhs.length != 0) {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
            length = 0; //wertyuiop
        }
        data = new char[rhs.length + 1];
        strcpy(data, rhs.data);
    }
    if (rhs.length == 0) {
        delete[] data;
        length = 0;
    }
    return *this;
}

/**
     * @brief Changes this from char array
     */
String &String::operator=(const char *str) {
    if (data != NULL) {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
            length = 0; //wertyuiop
        }
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    if (strlen(str) == 0) {
        delete[] data;
        length = 0;
    }
    return *this;
}

/**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
bool String::equals(const String &rhs) const {
    if (rhs.length == length) {
        if (strcmp(data, rhs.data) == 0)
            return true;
        else return false;
    }
    return false;
}

/**
     * @brief Returns true iff the contents of this equals to rhs
     */
bool String::equals(const char *rhs) const {
    if (strlen(rhs) == length) {
        if (strcmp(data, rhs) == 0)
            return true;
        else return false;
    }
    return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const {

    int nums=0;
    int counter=1;
    int sub=0;
    char* token;
    char copy[length+1]={0};

    for (size_t i = 0; i < length + 1; ++i) {
        copy[i]=0;
    }
    if(delimiters == nullptr){
        nums=0;
//        if(data == NULL){
//            if(size == NULL){
//                return;
//            }
//            *size=0;
//            return;
//        }
    }else{
        for (size_t i = 0; i < length + 1; ++i) {
            copy[i]=0;
        }
        int ssize=strlen(delimiters);
        nums =ssize;
    }
    if(data == NULL){
        if(size == NULL){
            return;
        }
        *size=0;
        return;
    }
    if(size == NULL){
        if(size == NULL){
            return;
        }
        *size=0;
        return;
    }
    strncpy(copy,data,length);
    for (size_t i = 0; i < length; ++i) {
        copy[i] = data[i];
    }
    copy[length] = '\0';


    for (size_t i = 1; i < length+1; i++)
        for (int j = 1; j < nums+1; j++) {
            {
                if (copy[i-1] == delimiters[j-1]) {
                    counter++;
                }
            }
        }
    *size = counter;
    if (output == NULL) {
        return;
    }else{
        *output = new String[counter];
        token = strtok(copy, delimiters);
        while (token != NULL) {
            (*output)[sub] = String(token);
            sub++;
            token = strtok(NULL, delimiters);
        }
        return;
    }
}


int String::to_integer() const {
    if (data == nullptr) return 0;
    if (length == 0) {
        return 0;
    }
    auto tmp = std::atoi(data);
    return tmp;
}

String String::trim() const {
    if (length == 0) {
        return String();
    }
    int count_spaces = 0;
    int count_leading_spaces = 0;
    for (size_t i = 0; i < length; i++) {
        if ((data[i] == ' ')) {
            count_spaces++;
        } else {
            break;
        }
    }
    for (size_t j = 0; j < length; j++) {
        if ((data[length - j - 1] == ' ')) {
            count_spaces++;
            count_leading_spaces++;
        } else {
            break;
        }
    }
    char str[length - count_spaces + 1];
    for (size_t k = count_leading_spaces; k <= length - count_spaces + count_leading_spaces - 1; k++) {
        str[k - count_leading_spaces] = data[k];
    }
    str[length - count_spaces] = '\0';
    return String(str);
}
