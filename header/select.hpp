#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <string>

class Select {
 public:
   // Return true if row should be selected
   virtual bool select(const Movies* data, int row) const = 0;

   virtual ~Select() = default;
};

class Select_Contains: public Select_Column {
 protected:
   int column;
   std::string keyword;
 public:
   Select_Contains(const Movies* data, const std::string& column, const std::string& s) {
      column = data->get_column_by_name(name);
      keyword = user_string;
   }
   virtual bool select(const Movies* data, int row) const {
      return select(data->cell_data(row, column));
   }
   virtual bool select(const std::vector<std::string>& s) const {
      for (int i = 0; i < s.size(); ++i) {
         if(s.at(i).find(keyword)) {
            return true;
         }
      }
      return false;
   }
};

class Select_And: public Select {
 protected:
   Select* left = nullptr;
   Select* right = nullptr;
 public:
   Select_And(Select* lhs, Select* rhs) {
      left = lhs;
      right = rhs;
   }
   virtual ~Select_And() {
      delete left;
      delete right;
   }
   virtual bool select(const Movies* movie, int row) const {
      if (left->select(movie, row) && right->select(movie, row)) {
         return true;
      }
      else {
         return false;
      }
   }
};

class Select_Not: public Select {
 protected:
   Select* ptr = nullptr;
 public:
   Select_Not(Select* p) {
      ptr = p;
   }
   virtual ~Select_Not() {
      delete ptr;
   }
   virtual bool select(const Movies* movie, int row) const {
      if(!(ptr->select(movie, row))) {
         return true;
      }
      else {
         return false;
      }
   }
};

class Select_Or: public Select {
 protected:
   Select* left = nullptr;
   Select* right = nullptr;
 public:
   Select_Or(Select* lhs, Select* rhs) {
      left = lhs;
      right = rhs;
   }
   virtual ~Select_Or() {
      delete left;
      delete right;
   }
   virtual bool select(const Movies* movie, int row) const {
      if(left->select(movie, row) || right->select(movie, row)) return true;
      return false;
   }
};

#endif
