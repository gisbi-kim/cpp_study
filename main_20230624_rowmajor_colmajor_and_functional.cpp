/* Results 

############################################
## test env: https://www.onlinegdb.com/online_c++_compiler
  CPU Model: Intel(R) Xeon(R) CPU @ 2.00GHz to 2.80GHz
############################################

############################################
## 1, no compiler optimization 
############################################
  n=500:
    Row-major access            took 0.000843867 seconds, and the reusult is 124975.433
    Row-major (functional impl) took 0.001379423 seconds, and the reusult is 124975.433
    Column-major access         took 0.001298086 seconds, and the reusult is 124975.433
    Column-major access was 1.538258991 times slower than row-major access.

  n=1000:
    Row-major access            took 0.00335054 seconds, and the reusult is 499810.5725
    Row-major (functional impl) took 0.005397353 seconds, and the reusult is 499810.5725
    Column-major access         took 0.005239655 seconds, and the reusult is 499810.5725
    Column-major access was 1.56382404 times slower than row-major access.

  n=5000:
    Row-major access            took 0.085016627 seconds, and the reusult is 12500656.36
    Row-major (functional impl) took 0.137052101 seconds, and the reusult is 12500656.36
    Column-major access         took 0.300620669 seconds, and the reusult is 12500656.36
    Column-major access was 3.536022065 times slower than row-major access.

  n=10000:
    Row-major access            took 0.324418896 seconds, and the reusult is 50000006.61
    Row-major (functional impl) took 0.525901008 seconds, and the reusult is 50000006.61
    Column-major access         took 1.777532428 seconds, and the reusult is 50000006.61
    Column-major access was 5.479127295 times slower than row-major access.

  n=15000:
    Row-major access            took 1.314769019 seconds, and the reusult is 112498804.6
    Row-major (functional impl) took 2.810473077 seconds, and the reusult is 112498804.6
    Column-major access         took 8.229706094 seconds, and the reusult is 112498804.6
    Column-major access was 6.259431105 times slower than row-major access.

############################################
## 2, with compiler optimization flag -O3
############################################
  n=500:
    Row-major access            took 0.000296172 seconds, and the reusult is 125066.0872
    Row-major (functional impl) took 0.000262256 seconds, and the reusult is 125066.0872
    Column-major access         took 0.000321579 seconds, and the reusult is 125066.0872
    Column-major access was 1.085784612 times slower than row-major access.

  n=1000:
    Row-major access            took 0.002056682 seconds, and the reusult is 499334.2621
    Row-major (functional impl) took 0.001160709 seconds, and the reusult is 499334.2621
    Column-major access         took 0.002813145 seconds, and the reusult is 499334.2621
    Column-major access was 1.367807469 times slower than row-major access.

  n=5000:
    Row-major access            took 0.061631129 seconds, and the reusult is 12498378.97
    Row-major (functional impl) took 0.038777388 seconds, and the reusult is 12498378.97
    Column-major access         took 0.489687813 seconds, and the reusult is 12498378.97
    Column-major access was 7.945462317 times slower than row-major access.

  n=10000:
    Row-major access            took 0.199170745 seconds, and the reusult is 50001735.42
    Row-major (functional impl) took 0.125082625 seconds, and the reusult is 50001735.42
    Column-major access         took 1.418928086 seconds, and the reusult is 50001735.42
    Column-major access was 7.124179236 times slower than row-major access.

  n=15000:
    Row-major access            took 0.440319285 seconds, and the reusult is 112498534.6
    Row-major (functional impl) took 0.281632676 seconds, and the reusult is 112498534.6
    Column-major access         took 4.114672291 seconds, and the reusult is 112498534.6
    Column-major access was 9.34474694 times slower than row-major access.

*/

#include <vector>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <fstream>

using MatrixElmType = double;
using Matrix = std::vector<std::vector<MatrixElmType>>;

inline void print_cpu_spec() {
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuInfoFile, line)) {
        if (line.substr(0, 10) == "model name") {
            std::cout << "CPU Model: " << line.substr(13) << std::endl;
            break;
        }
    }
    cpuInfoFile.close();
}

inline auto tic() {
    return std::chrono::high_resolution_clock::now();
}

struct Result {
  MatrixElmType sum;
  double timecost_sec;
};

auto generate_random_machine(){
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return std::make_pair(generator, distribution);
}

Matrix generate_random_matrix(const int SIZE) {
    auto [generator, distribution] = generate_random_machine();
    Matrix matrix(SIZE, std::vector<MatrixElmType>(SIZE));
    for (auto& row : matrix) {
        for (auto& elem : row) {
            elem = distribution(generator);
        }
    }
    return matrix;
}

template <class F>
Result experiment_factory(const Matrix& matrix, F&& for_loop_main) {
    auto start_time = tic();
    MatrixElmType sum = std::forward<F>(for_loop_main)(matrix);
    auto duration = std::chrono::duration<double>(tic() - start_time);
    return Result {sum, duration.count()};
};


int main() {
    print_cpu_spec();
    
    const int SIZE = 5000;  // Large enough size to exceed cache size
    auto matrix = generate_random_matrix(SIZE);

    auto colmajor_result = experiment_factory(matrix, [](const Matrix& _mat){
        MatrixElmType sum;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                sum += _mat[j][i];
            }
        }
        return sum;
    });
    
    auto rowmajor_result = experiment_factory(matrix, [](const Matrix& _mat){
        MatrixElmType sum;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                sum += _mat[i][j];
            }
        }
        return sum;
    });

    auto rowmajor_functional_result = experiment_factory(matrix, [](const Matrix& _mat){   
        auto sumRow = [](auto acc, auto& row) {
            return acc + std::accumulate(row.begin(), row.end(), 0.0);
        };
        return std::accumulate(_mat.begin(), _mat.end(), 0.0, sumRow);
    });

    std::cout << "experimented SIZE is " << SIZE << std::endl;

    std::cout.precision(10);
    std::cout << "Row-major access            took " << rowmajor_result.timecost_sec << " seconds, and the reusult is " << rowmajor_result.sum << std::endl;
    std::cout << "Row-major (functional impl) took " << rowmajor_functional_result.timecost_sec << " seconds, and the reusult is " << rowmajor_functional_result.sum << std::endl;
    std::cout << "Column-major access         took " << colmajor_result.timecost_sec << " seconds, and the reusult is " << colmajor_result.sum << std::endl;

    double ratio = colmajor_result.timecost_sec / rowmajor_result.timecost_sec;
    std::cout << "Column-major access was " << ratio << " times slower than row-major access." << std::endl;

    return 0;
}

/* to visualize the above result, using this Python code 

import pandas as pd
import matplotlib.pyplot as plt

# 데이터 생성
data = {
    "Size": [500, 1000, 5000, 10000, 15000, 500, 1000, 5000, 10000, 15000, 500, 1000, 5000, 10000, 15000],
    "Type": ['Row', 'Row', 'Row', 'Row', 'Row', 'Column', 'Column', 'Column', 'Column', 'Column', 'RowFunc', 'RowFunc', 'RowFunc', 'RowFunc', 'RowFunc'],
    "Time_No_Optimization": [0.000843867, 0.00335054, 0.085016627, 0.324418896, 1.314769019, 0.001298086, 0.005239655, 0.300620669, 1.777532428, 8.229706094, 0.001379423, 0.005397353, 0.137052101, 0.525901008, 2.810473077],
    "Time_O3_Optimization": [0.000296172, 0.002056682, 0.061631129, 0.199170745, 0.440319285, 0.000321579, 0.002813145, 0.489687813, 1.418928086, 4.114672291, 0.000262256, 0.001160709, 0.038777388, 0.125082625, 0.281632676]
}

# 데이터프레임 생성
df = pd.DataFrame(data)

# 그래프 그리기
fig, ax = plt.subplots()

markers = {'Row': 'o', 'Column': '^', 'RowFunc': '*'}
colors = {'Row': 'b', 'Column': 'r', 'RowFunc': 'g'}

for label, group in df.groupby('Type'):
    group.plot('Size', 'Time_No_Optimization', ax=ax, label=f'{label}_No_Optimization', 
               marker=markers[label], color=colors[label], linestyle='-')
    group.plot('Size', 'Time_O3_Optimization', ax=ax, label=f'{label}_O3_Optimization', 
               marker=markers[label], color=colors[label], linestyle='--')

plt.ylabel('Time (seconds)')
plt.xlabel('Matrix Size')
plt.title('Comparison of Row-major and Column-major access')
plt.grid(True)
plt.show()

*/
