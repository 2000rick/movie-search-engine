#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select {
 public:
   // Return true if row should be selected
   virtual bool select(const Movies* movie, int row) const = 0;

   virtual ~Select() = default;
};

class Select_Column: public Select {
 protected:
   int column;
 public:
   Select_Column(const Movies* movie, const std::string& name) {
      column = movie->get_column_by_name(name);
   }
   virtual bool select(const Movies* movie, int row) const {
      return select(movie->cell_data(row, column));
   }
   // For derived classes
   virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column {
 protected:
   std::string keyword;
 public:
   Select_Contains(const Movies* movie, const category_name, const std::string& user_string): Select_Category(movie, category_name) {
      keyword = user_string;
   }
   virtual bool select(const std::string& s) const {
      if(s.find(keyword) != std::string::npos) return true;
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

#endif
