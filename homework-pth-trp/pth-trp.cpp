#include <iostream>
#include <limits>

enum class Result{
    PTH,
    NOT_PTH,
    OVER
};

bool is_over_sum(size_t a, size_t b){
    size_t max = std::numeric_limits<size_t>::max();
    if (max - a < b){
        return 1;
    }return 0;
}


bool  is_over_multiply(size_t a, size_t b){
    size_t max = std::numeric_limits<size_t>::max();
    if (max / a < b){
        return 1;
    } return 0;
}


size_t max(size_t a, size_t b){
    if (a > b) return a;
    return b;
}

size_t min(size_t a, size_t b){
    if (a < b) return a;
    return b;
}

Result is_pth_trp(size_t a, size_t b, size_t c){
    size_t biggest =  max(a, max(b,c));
    size_t smallest = min(a, max(b,c));
    size_t medium = a-biggest+b-smallest+c;
    if (is_over_multiply(biggest, biggest)) return Result::OVER;
    if (is_over_sum(medium*medium, smallest*smallest)) return Result::OVER;
    if (medium*medium + smallest*smallest == biggest*biggest) return Result::PTH;
    else return Result::NOT_PTH;
}





int main(){
    size_t count = 0;
    long long a,b,c;
    std::cin >> a >> b >> c;
    if (std::cin.eof()) return 2;
    while (true){
        if (std::cin.eof()){
            std::cout << count << "\n";
            return 0;
        }
        else if (std::cin.fail()) return 1;
        else if (a <= 0 || b <= 0 || c <=0) return 2;
        switch (is_pth_trp(a, b, c)){
            case Result::OVER:
                return 2;
            case Result::PTH:
                count++;
        }
        a = b;
        b = c;
        std::cin >> c;
    }
}

