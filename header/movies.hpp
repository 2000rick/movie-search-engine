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

  void set_selection(Select* new_select);
  bool update(int id);
  void set_column_names(const std::vector<std::string>& names);
  void add_vector(const std::vector<std::vector<std::string>>& row_data);
  int get_column_by_name(const std::string& name) const;
public:
  ~Movies()
  std::vector<std::string>& cell_data(int row, int column);
  bool search(string& query);
  void print_selection(std::ostream& out) const;
  void clear();
  bool update(string sort, int n);
};

#endif
