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
  std::string sort;

  bool valid(std::string& query); //search function helper
  Select* search_helper(std::stringstream& stream); //search function helper
  void set_selection(Select* new_select);
  bool movie_update(int id);
  void set_column_names(const std::vector<std::string>& names);
  void add_vector(const std::vector<std::vector<std::string>>& row_data);
public:
  ~Movies();
  const std::vector<std::string>& cell_data(int row, int column) const;
  bool search(std::string& query);
  void print_selection(std::ostream& out) const;
  void clear();
  bool movie_update(std::string sort, int n);
  int get_column_by_name(const std::string& name) const;
  bool movie_from_file(std::string fileName);
  void init_column_names();
  int return_num_movies();
  std::string return_sort();
  void clear_select();
  bool return_searched();
  int num_searched();
};

#endif
