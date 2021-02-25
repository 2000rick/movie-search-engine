#ifndef __MOVIES_HPP__
#define __MOVIES_HPP__

#include <string>
#include <initializer_list>
#include <vector>
#include <iosfwd>

class Select;

class Movies {
private:
  std::vector<std::string> column_names;
  std::vector<std::vector<std::vector<std::string>>> data;
  Select* select = nullptr;
  std::string api_key = "8b6eb71dd22c58cfb6125ac835f94e2a";

  bool valid(std::string& query); //search function helper
  void set_selection(Select* new_select);
  bool movie_update(int id);
  void set_column_names(const std::vector<std::string>& names);
  void add_vector(const std::vector<std::vector<std::string>>& row_data);
  int get_column_by_name(const std::string& name) const;
public:
  ~Movies()
  std::vector<std::string>& cell_data(int row, int column);
  bool search(std::string& query);
  void print_selection(std::ostream& out) const;
  void clear();
  bool movie_update(string sort, int n);
};

#endif
