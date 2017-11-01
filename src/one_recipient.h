/*
 * This class stores all information about one recipient,
 * including all records on one date and all records in
 * one zip code.
 */

#ifndef ONE_RECIPIENT_H_
#define ONE_RECIPIENT_H_

#include <map>
#include <ostream>
#include <string>
#include <utility>

#include "record.h"
#include "validate_date.h"

class OneRecipient {
 public:
  OneRecipient(const std::string &recipient);
  ~OneRecipient();

  std::string GetRecipient() const;

  void AddRecord(const std::string date, const std::string zip_code,
                 const int amount);
  std::map<std::string, Record> GetAllRecordsByDate() const;
  std::map<std::string, Record> GetAllRecordsByZipCode() const;

  bool operator<(const OneRecipient &r1) const;

 private:
  ValidateDate valid_date_;
  bool isValidZipCode(const std::string zip_code);
  const int kValidZipCodeLength = 5;
  std::string recipient_;
  std::map<std::string, Record> date_records_;
  std::map<std::string, Record> zip_code_records_;
};

#endif // ONE_RECIPIENT_H_

OneRecipient::OneRecipient(const std::string &recipient) {
  recipient_ = recipient;
}

OneRecipient::~OneRecipient() {}

std::string OneRecipient::GetRecipient() const { return recipient_; }

bool OneRecipient::isValidZipCode(const std::string zip_code) {
  return (zip_code != "") && (zip_code.size() >= kValidZipCodeLength);
}

void OneRecipient::AddRecord(const std::string date, const std::string zip_code,
                             const int amount) {

  // add date records
  if (valid_date_.isValid(date)) {
    std::map<std::string, Record>::iterator it = date_records_.find(date);
    if (it != date_records_.end()) {
      (it->second).AddAmount(amount);
    } else {
      Record r;
      r.AddAmount(amount);
      std::pair<const std::string, Record> one_date_record(date, r);
      date_records_.insert(one_date_record);
    }
  }
  
  // add zip code records
  if (isValidZipCode(zip_code)) {
    const std::string short_zip_code = zip_code.substr(0, 5);
    std::map<std::string, Record>::iterator jt =
      zip_code_records_.find(short_zip_code);
    if (jt != zip_code_records_.end()) {
      (jt->second).AddAmount(amount);
    } else {
      Record r;
      r.AddAmount(amount);
      std::pair<const std::string, Record> one_zip_code_record(short_zip_code,
          r);
      zip_code_records_.insert(one_zip_code_record);
    }
  }
}

std::map<std::string, Record> OneRecipient::GetAllRecordsByDate() const {
  return date_records_;
}

std::map<std::string, Record> OneRecipient::GetAllRecordsByZipCode() const {
  return zip_code_records_;
}

bool OneRecipient::operator<(const OneRecipient &r1) const {
  return (recipient_ < r1.GetRecipient());
}
