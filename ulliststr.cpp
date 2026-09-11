#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std:: string& val)
{
  if(empty()) {

    Item* newItem = new Item;

    head_ = newItem;
    tail_ = newItem;

    newItem->val[newItem->last] = val;
    newItem->last++;

    size_++;
    return;
    
  }

  if(tail_->last < ARRSIZE){
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
    return;
  }

  Item* newItem = new Item;
  newItem->prev = tail_;
  tail_->next = newItem;
  tail_ = newItem;

  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;
}

void ULListStr::pop_back(){
if(empty()){
  return;
}

--tail_->last;
size_--;

if(tail_->first == tail_->last){
  Item* prevTail = tail_;
  tail_ = tail_->prev;

  if(tail_ == NULL) {
    head_ = NULL;
  }
  else{
    tail_->next = NULL;
  }
  delete prevTail;
}
}

void ULListStr::push_front(const std:: string& val){
if(empty()) {
  Item* newItem = new Item;

  head_ = newItem;
  tail_ = newItem;

  newItem->first = ARRSIZE - 1;
  newItem->last = ARRSIZE;
  newItem->val[newItem->first] = val;

  size_++;
  return;
}

if(head_->first > 0){
  --head_->first;
  head_->val[head_->first] = val;

  size_++;
  return;
}

Item* newItem = new Item;

newItem->next = head_;
head_->prev = newItem;
head_ = newItem;

newItem->first = ARRSIZE - 1;
newItem->last = ARRSIZE;
newItem->val[newItem->first] = val;

size_++;
}

void ULListStr::pop_front(){
if(empty()){
  return;
}

++head_->first;
size_--;

if(head_->first == head_->last){
  Item* prevHead = head_;
  head_ = head_->next;

  if(head_ == NULL) {
    tail_ = NULL;
  }
  else{
    head_->prev = NULL;
  }
  delete prevHead;
}
}

std::string const& ULListStr::back() const{
return tail_->val[tail_->last - 1];
}

std::string const& ULListStr::front() const{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  
  if(loc >= size_) {
    return NULL;
  }

  Item* current = head_;

  while(current != NULL) {
    size_t numValues = current->last - current->first;

    if(loc < numValues){
      return &(current->val[current->first +loc]);
    }

    loc -= numValues;
    current = current->next;
  }

  return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
