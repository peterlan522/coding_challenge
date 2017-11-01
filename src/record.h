/*
 * This class stores total amount contribution so far
 * and can get out running median, total transaction and
 * total amount contributions.
 */

#ifndef RECORD_H_
#define RECORD_H_

#include "running_median.h"
#include <cmath>

class Record {
 public:
  Record();
  ~Record();

  void AddAmount(const int amount);

  int GetTotalAmount() const;
  unsigned int GetTotalTransaction() const;
  int GetMedian();

 private:
  RunningMedian r_;
  int total_amount_;
  unsigned int total_transactions_;
};

#endif // RECORD_H_

Record::Record() {
  total_amount_ = 0;
  total_transactions_ = 0;
}

Record::~Record() {}

void Record::AddAmount(const int amount) {
  total_amount_ += amount;
  total_transactions_++;
  r_.AddNumber(amount);
}

int Record::GetTotalAmount() const { return total_amount_; }

unsigned int Record::GetTotalTransaction() const { return total_transactions_; }

int Record::GetMedian() { return round(r_.GetRunningMedian()); }
