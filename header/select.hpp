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


#endif
