
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <boost/math/special_functions/binomial.hpp>
using namespace std;

vector<int> generateRandomNumbers(int count, int min, int max) {
    vector<int> numbers;
    while (numbers.size() < count) {
        int num = rand() % (max - min + 1) + min;
        if (find(numbers.begin(), numbers.end(), num) == numbers.end()) {
            numbers.push_back(num);
        }
    }
    return numbers;
}

// 生成组合的辅助函数
void generate_combinations(const std::vector<int>& pool, int count, std::vector<std::vector<int>>& combinations) {
    std::vector<bool> v(pool.size());
    std::fill(v.end() - count, v.end(), true);
    do {
        std::vector<int> c;
        for (int i = 0; i < pool.size(); ++i) {
            if (v[i]) {
                c.push_back(pool[i]);
            }
        }
        combinations.push_back(c);
    } while (std::next_permutation(v.begin(), v.end()));
}

int main() {

    srand(time(NULL));  // Seed random number generator
    // Generate winning numbers
    vector<int> winning_reds= generateRandomNumbers(6, 1, 33);
    vector<int> winning_blue = generateRandomNumbers(1, 1, 16);
     long total_prize = 0;
     long  total_cost = 0;
     long  total_feedback=0;
     long  buy_number=10000000;
     int red_number=9;
     int blue_number=3;
     long count_each_number=boost::math::binomial_coefficient<double>(red_number, 6)*boost::math::binomial_coefficient<double>(blue_number, 1);
     std::cout << "C(" << red_number<< ", " << blue_number << ") = " << count_each_number << std::endl;
     int each_cost=count_each_number*2;
     total_cost=buy_number*count_each_number*2;
    for(int i=0;i<buy_number;i++){
    // User input
    vector<int> player_reds = generateRandomNumbers(red_number,1, 33);
    vector<int> player_blues = generateRandomNumbers(blue_number, 1, 16);
   // 存储所有红球和蓝球的组合
    std::vector<std::vector<int>> red_combinations;
    std::vector<std::vector<int>> blue_combinations;

    // 生成组合
    generate_combinations(player_reds, 6, red_combinations);
    generate_combinations(player_blues, 1, blue_combinations);

    // 遍历所有组合以计算奖金
    bool flag_hit=false;
    for (auto& red_comb : red_combinations) {
        for (auto& blue_comb : blue_combinations) {
            int red_match_count = std::count_if(red_comb.begin(), red_comb.end(), [&](int n) {
                return std::find(winning_reds.begin(), winning_reds.end(), n) != winning_reds.end();
            });
            bool blue_match = std::find(blue_comb.begin(), blue_comb.end(), winning_blue[0]) != blue_comb.end();

            // 根据匹配数量判断奖项
            if (red_match_count == 6 && blue_match) {
                total_prize += 8000000;  // 假设的一等奖金额
                //std::cout << "一等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 6) {
                total_prize += 300000;  // 假设的二等奖金额
                //std::cout << "二等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 5 &&  blue_match) {
                total_prize += 3000;  // 假设的三等奖金额
                //std::cout << "三等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 5) {
                total_prize += 200;  // 假设的四等奖金额
                //std::cout << "四等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 4 &&  blue_match) {
                total_prize += 200;  // 假设的四等奖金额
                //std::cout << "四等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 4) {
                total_prize += 10;  // 假设的五等奖金额
                //std::cout << "五等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 3 && blue_match) {
                total_prize += 10;  // 假设的五等奖金额
                //std::cout << "五等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 2 && blue_match) {
                total_prize += 5;  // 假设的六等奖金额
                //std::cout << "六等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 1 && blue_match) {
                total_prize += 5;  // 假设的六等奖金额
                //std::cout << "六等奖！" << std::endl;
                flag_hit=true;
            } else if (red_match_count == 0 && blue_match) {
                total_prize += 5;  // 假设的六等奖金额
                //std::cout << "六等奖！" << std::endl;
                flag_hit=true;
            } 
        }
    }
    if(flag_hit==true){
        total_prize += each_cost;
        total_feedback+= each_cost;
    }

    // Output results
    //cout << "Winning Reds: ";
    //for (int red : winning_reds) cout << red << " ";
    //cout << "\nWinning Blue: " << winning_blue[0] << endl;
    //cout << "Your Reds: ";
    //for (int red : player_reds) cout << red << " ";
    //cout << "\nYour Blues: ";
    //for (int blue : player_blues) cout << blue << " ";
    //cout << endl;
    std::cout << "总奖金: " << total_prize << "元" << std::endl;
    std::cout << "总返回: " << total_feedback<< "元" << std::endl;
    std::cout << "总支出: " << total_cost << "元" << std::endl;
    std::cout << "单注组合: " << count_each_number << "种" << std::endl;
    }
    std::cout << "比例: " << (double)total_prize/total_cost*100 << "%" << std::endl;
    return 0;
}