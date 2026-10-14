#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <utility>

int main() {
  // сортирую таблицы с числами по сумме элементов, таблицы могут быть разного
  // размера
  // int*** - массив таблиц, каждая таблица это массив указателей на строки.
  // при сортировке меняю местами только указатели на таблицы а сами числа не
  // копирую. без int*** пришлось бы хранить всё в одном массиве и при
  // сортировке копировать сами числа
  // void* - вся память под таблицы выделяется одним куском через malloc. в
  // этом куске лежат вперемешку int** (таблицы), int* (строки) и сами int,
  // поэтому у куска нет одного типа и я иду по нему через void*, приводя к
  // нужному типу. без этого пришлось бы делать new на каждую строку отдельно
  // ввод: количество таблиц, потом размеры всех таблиц, потом сами числа по
  // строкам
  std::size_t tables_count;
  std::cin >> tables_count;
  if (tables_count == 0) {
    return 0;
  }

  std::size_t* rows_counts = new std::size_t[tables_count];
  std::size_t* columns_counts = new std::size_t[tables_count];
  std::size_t total_rows = 0;
  std::size_t total_cells = 0;
  for (std::size_t i = 0; i < tables_count; ++i) {
    std::cin >> rows_counts[i] >> columns_counts[i];
    total_rows += rows_counts[i];
    total_cells += rows_counts[i] * columns_counts[i];
  }

  std::size_t pool_size = (tables_count * sizeof(int**)) +
                          (total_rows * sizeof(int*)) +
                          (total_cells * sizeof(int));
  void* pool = std::malloc(pool_size);
  void* cursor = pool;

  int*** tables = static_cast<int***>(cursor);
  cursor = static_cast<char*>(cursor) + (tables_count * sizeof(int**));
  for (std::size_t i = 0; i < tables_count; ++i) {
    tables[i] = static_cast<int**>(cursor);
    cursor = static_cast<char*>(cursor) + (rows_counts[i] * sizeof(int*));
  }
  for (std::size_t i = 0; i < tables_count; ++i) {
    for (std::size_t j = 0; j < rows_counts[i]; ++j) {
      tables[i][j] = static_cast<int*>(cursor);
      cursor = static_cast<char*>(cursor) + (columns_counts[i] * sizeof(int));
    }
  }

  long long* sums = new long long[tables_count];
  for (std::size_t i = 0; i < tables_count; ++i) {
    sums[i] = 0;
    for (std::size_t j = 0; j < rows_counts[i]; ++j) {
      for (std::size_t k = 0; k < columns_counts[i]; ++k) {
        std::cin >> tables[i][j][k];
        sums[i] += tables[i][j][k];
      }
    }
  }

  for (std::size_t i = 0; i < tables_count; ++i) {
    for (std::size_t j = 0; j + 1 < tables_count - i; ++j) {
      if (sums[j] > sums[j + 1]) {
        std::swap(tables[j], tables[j + 1]);
        std::swap(rows_counts[j], rows_counts[j + 1]);
        std::swap(columns_counts[j], columns_counts[j + 1]);
        std::swap(sums[j], sums[j + 1]);
      }
    }
  }

  for (std::size_t i = 0; i < tables_count; ++i) {
    std::cout << sums[i] << '\n';
    for (std::size_t j = 0; j < rows_counts[i]; ++j) {
      for (std::size_t k = 0; k < columns_counts[i]; ++k) {
        std::cout << tables[i][j][k] << ' ';
      }
      std::cout << '\n';
    }
  }

  std::free(pool);
  delete[] sums;
  delete[] rows_counts;
  delete[] columns_counts;
}
