#ifndef __SELECTMOCK_HPP__
#define __SELECTMOCK_HPP__

#include <string>
#include <vector>

bool found(std::string keyword, std::string string);

class Select {
 public:
   // Return true if row should be selected
   virtual bool select(const MoviesMock* data, int row) const = 0;

   virtual ~Select() = default;
};

class Select_Contains: public Select {
 protected:
   int column;
   std::string str;
 public:
   Select_Contains(const MoviesMock* data, const std::string& column, const std::string& s) {
      this->column = data->get_column_by_name(column);
      str = s;
   }
   bool select(const MoviesMock* data, int row) const {
     if (column == -1){ return false; }
     else { return select(data->cell_data(row, column)); }
   }
   bool select(const std::vector<std::string>& s) const {
      for (int i = 0; i < s.size(); ++i) {
        if(found(str, s.at(i)) == true) return true;
      }
      return false;
   }
};

bool found(std::string keyword, std::string string) {
      for (char& c : keyword) c = std::tolower(c);
      for (char& c : string) c = std::tolower(c);
      if (string.find(keyword) != std::string::npos) return true;
      return false;
}

class Select_And: public Select {
 protected:
   Select* s0 = nullptr;
   Select* s1 = nullptr;
 public:
   Select_And(Select* i0, Select* i1) {
      s0 = i0;
      s1 = i1;
   }
   ~Select_And() {
      delete s0;
      delete s1;
   }
   bool select(const MoviesMock* data, int row) const {
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
   ~Select_Not() {
      delete s0;
   }
   bool select(const MoviesMock* data, int row) const {
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
   ~Select_Or() {
      delete s0;
      delete s1;
   }
   bool select(const MoviesMock* data, int row) const {
      if(s0->select(data, row) || s1->select(data, row)) return true;
      return false;
   }
};

#endif
