/*
 * This is the main program to read file, do the computation,
 * and write out to file.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "one_recipient.h"

// Get tokens based on delim passed in.
std::vector<std::string> Split(std::string str, const char *delim) {
  std::vector<std::string> v;
  std::string tmp;

  for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
    if (*it != *delim && it != str.end()) {
      tmp += *it;
    } else {
      v.push_back(tmp);
      tmp = "";
    }
  }
  return v;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage: " << argv[0] << "<filename>\n";
  } else {
    std::ifstream the_file(argv[1]);

    if (!the_file.is_open()) {
      std::cout << "Could not open file\n";

    } else {

      // read file
      std::string line;
      const std::string delim = "|";
      std::map<std::string, OneRecipient> recipients;

      while (getline(the_file, line)) {
        std::vector<std::string> key_words = Split(line, delim.c_str());

        if (key_words[0] != "" && key_words[14] != "" && key_words[15] == "") {
          const std::string recipient = key_words[0];
          const std::string date = key_words[13];
          const std::string zip_code = key_words[10];
          const int amount = stoi(key_words[14]);

          std::map<std::string, OneRecipient>::iterator it =
            recipients.find(recipient);
          if (it != recipients.end()) {
            (it->second).AddRecord(date, zip_code, amount);
          } else {
            OneRecipient one_recipient(recipient);
            one_recipient.AddRecord(date, zip_code, amount);
            recipients.insert(std::make_pair(recipient, one_recipient));
          }
        }
      }
      the_file.close(); // end of reading file

      // write to file
      const std::string filename_by_date = "../output/medianvals_by_date.txt";

      std::ofstream file_by_date;
      file_by_date.open(filename_by_date);
      for (std::map<std::string, OneRecipient>::iterator it =
             recipients.begin();
           it != recipients.end(); ++it) {
        for (auto n : (it->second).GetAllRecordsByDate()) {

          file_by_date << it->first << delim;
          file_by_date << n.first << delim;                // date
          file_by_date << (n.second).GetMedian() << delim; // running median
          file_by_date << (n.second).GetTotalTransaction()
                       << delim; // total transaction
          file_by_date << (n.second).GetTotalAmount() << std::endl;
        }
      }
      file_by_date.close(); // end of writing

      // write to file
      const std::string filename_by_zip_code =
        "../output/medianvals_by_zip.txt";

      std::ofstream file_by_zip_code;
      file_by_zip_code.open(filename_by_zip_code);
      for (std::map<std::string, OneRecipient>::iterator it =
             recipients.begin();
           it != recipients.end(); ++it) {
        for (auto n : (it->second).GetAllRecordsByZipCode()) {
          file_by_zip_code << it->first << delim;
          file_by_zip_code << n.first << delim;                // zip code
          file_by_zip_code << (n.second).GetMedian() << delim; // running median
          file_by_zip_code << (n.second).GetTotalTransaction()
                           << delim; // total transaction
          file_by_zip_code << (n.second).GetTotalAmount() << std::endl;
        }
      }
      file_by_zip_code.close(); // end of writing
    }
  }
  return 0;
}
