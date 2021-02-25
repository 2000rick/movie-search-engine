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
   std::string str;
 public:
   Select_Contains(const Movies* data, const std::string& column, const std::string& s) {
      this->column = data->get_column_by_name(column);
      str = user_string;
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
   Select* s0 = nullptr;
   Select* s1 = nullptr;
 public:
   Select_And(Select* i0, Select* i1) {
      s0 = i0;
      s1 = i1;
   }
   virtual ~Select_And() {
      delete s0;
      delete s1;
   }
   virtual bool select(const Movies* data, int row) const {
      if (s0->select(data, row) && s1->select(data, row)) {
         return true;
      }
      else {
         return false;
      }
   }
};

class Select_Not: public Select {
 protected:
   Select* s0 = nullptr;
 public:
   Select_Not(Select* i0) {
      s0 = i0;
   }
   virtual ~Select_Not() {
      delete s0;
   }
   virtual bool select(const Movies* data, int row) const {
      if(!(s0->select(data, row))) {
         return true;
      }
      else {
         return false;
      }
   }
};

class Select_Or: public Select {
 protected:
   Select* s0 = nullptr;
   Select* s1 = nullptr;
 public:
   Select_Or(Select* i0, Select* i1) {
      s0 = i0;
      s1 = i1;
   }
   virtual ~Select_Or() {
      delete s0;
      delete s1;
   }
   virtual bool select(const Movies* data, int row) const {
      if(s0->select(data, row) || s1->select(data, row)) return true;
      return false;
   }
};

#endif
