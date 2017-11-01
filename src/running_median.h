/*
 * This class computes running median based on
 * max heap and min heap.
 */

#ifndef RUNNING_MEDIAN_
#define RUNNING_MEDIAN_

#include <queue>

class RunningMedian {
 public:
  RunningMedian();
  ~RunningMedian();

  bool AddNumber(const int num);
  double GetRunningMedian();

 private:
  void Rebalance();
  std::priority_queue<int> lower_; // max_heap
  std::priority_queue<int, std::vector<int>, std::greater<int> >
      higher_; // min_heap
};

#endif // RUNNING_MEDIAN_

RunningMedian::RunningMedian() {}

RunningMedian::~RunningMedian() {}

bool RunningMedian::AddNumber(const int num) {
  if (lower_.size() == 0 || num < lower_.top()) {
    lower_.push(num);
    return true;
  } else {
    higher_.push(num);
    return true;
  }
  return false;
}

void RunningMedian::Rebalance() {
  int lower_size = lower_.size();
  int higher_size = higher_.size();

  if (lower_size - higher_size >= 2) {
    higher_.push(lower_.top());
    lower_.pop();
  } else if (higher_size - lower_size >= 2) {
    lower_.push(higher_.top());
    higher_.pop();
  }
}

double RunningMedian::GetRunningMedian() {
  Rebalance();

  if (lower_.size() == higher_.size()) {
    return (lower_.top() + higher_.top()) / 2.0;
  } else {
    return lower_.size() > higher_.size() ? lower_.top() : higher_.top();
  }
}
