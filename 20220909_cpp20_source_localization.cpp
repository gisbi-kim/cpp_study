// $ g++ prog.cc -Wall -Wextra -std=gnu++2a

#include <iostream>
#include <functional>
#include <source_location>

std::source_location getLocation(void) {
    return std::source_location::current();
}
    
int main()
{
    auto get_location = [](void) -> auto {
        std::source_location location = std::source_location::current();
        return location;
    };

    auto print_location = [](const auto& location) {
        using std::cout;
        using std::endl;

        cout << "\n=== print location ===" << endl;
        cout << location.line() << endl;           // 行番号
        cout << location.column() << endl;         // 列番号
        cout << location.file_name() << endl;      // ファイル名
        cout << location.function_name() << endl;  // 関数名        
    };
    
    // std::source_location location = std::source_location::current();
    print_location(get_location());
    print_location(getLocation());

    return 0;
}
