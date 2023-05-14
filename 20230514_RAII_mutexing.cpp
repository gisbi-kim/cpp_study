/* v1: 프로그래머의 unlock 누락 실수 방지  
  std::lock_guard는 생성 시점에 뮤텍스를 잠그고, 객체가 소멸할 때 (즉, 스코프를 벗어날 때) 자동으로 뮤텍스를 해제합니다. 
  따라서 프로그래머는 직접적으로 락을 관리할 필요가 없습니다. 
  이러한 방식은 락을 잊어버리거나, 예외가 발생했을 때 락이 해제되지 않는 등의 문제를 방지할 수 있습니다.

#include <mutex>

class Data {
private:
    std::mutex mtx;
    // 데이터 정의
    int data;

public:
    void update_data(int new_data) {
        std::lock_guard<std::mutex> lock(mtx);
        // lock_guard가 생성되면서 mtx가 자동으로 잠깁니다.
        data = new_data;
        // 함수가 끝나고 lock_guard가 소멸되면서 mtx가 자동으로 해제됩니다.
    }

    int read_data() {
        std::lock_guard<std::mutex> lock(mtx);
        // lock_guard가 생성되면서 mtx가 자동으로 잠깁니다.
        return data;
        // 함수가 끝나고 lock_guard가 소멸되면서 mtx가 자동으로 해제됩니다.
    }
};

*/


/* v2-a: 프로그래머의 deadlock 실수 방지 (lock_guard 이후 lock_guard를 가지는 함수를 재호출 하는 상황)
  하나의 뮤텍스를 여러 함수가 사용하는 경우에는, 
  호출하는 함수와 호출되는 함수 모두에서 동일한 뮤텍스를 잠그려고 하면 데드락이 발생할 수 있습니다. 
  이런 상황을 방지하는 한 가지 방법은 "재귀적 뮤텍스"(std::recursive_mutex)를 사용하는 것입니다.

#include <mutex>

class Data {
private:
    std::recursive_mutex mtx;
    int data;

public:
    void update_data(int new_data) {
        std::lock_guard<std::recursive_mutex> lock(mtx);
        data = new_data;
        read_data();  // 재귀적 뮤텍스를 사용하면 안전하게 호출할 수 있습니다.
    }

    int read_data() {
        std::lock_guard<std::recursive_mutex> lock(mtx);
        return data;
    }
};

*/


/* v2-b: 프로그래머의 deadlock 실수 방지 (lock_guard 이후 lock_guard를 가지는 함수를 재호출 하는 상황)
  또 다른 방법은 락을 필요로 하는 코드를 별도의 private 함수로 분리하고, 이 함수는 락 없이 호출되는 것입니다. 
  이렇게 하면 락을 잠그는 public 함수에서 이 private 함수를 안전하게 호출할 수 있습니다.
  ps. 단, 팀 내 규칙 수립 필요. 예시:
    모든 public 함수의 제일 첫번째에서는 lock_guard 를 실행하고, 
    그 public 함수가 끝나기 전까지 어떠한 명시적인 unlock도 수행해서는 안된다 와 같은 약속
*/
  
#include <mutex>

class Data {
private:
    std::mutex mtx;
    int data;

    // 락 없이 데이터를 업데이트하는 private 함수
    void do_update_data(int new_data) {
        data = new_data;
    }

    // 락 없이 데이터를 읽는 private 함수
    int do_read_data() {
        return data;
    }

public:
    void update_data(int new_data) {
        std::lock_guard<std::mutex> lock(mtx);
        do_update_data(new_data);
    }

    int read_data() {
        std::lock_guard<std::mutex> lock(mtx);
        return do_read_data();
    }

    // 이제 `read_data()`를 안전하게 호출할 수 있는 새로운 함수를 추가할 수 있습니다.
    void update_and_read(int new_data) {
        std::lock_guard<std::mutex> lock(mtx);
        do_update_data(new_data);
        int read = do_read_data();
        // `read`를 사용하는 코드...
    }
};


/* 요약
mutex 를 안전하게 사용하기 위한 프로그래밍 습관을 위해서는 아키텍처적으로 고민해야 한다. 

1. 함수의 단위: 일단 기본적으로 작은함수를 지향해야 햔다 (e.g., five lines)
  함수가 한 가지 일만 하는지 확인하세요. 
  함수가 너무 많은 일을 한다면, 락을 잡고 있는 시간이 길어져서 성능 문제가 발생할 수 있습니다. 
  그런 경우에는 함수를 더 작은 단위로 분리하고, 필요한 곳에서만 락을 사용하도록 하는 것이 좋습니다.

2. 재사용성: 그리고 어떤 데이터/함수가 락을 필요로 하는지 락-프리 인지 먼저 구분/정의 해야 한다. 
  락을 사용하지 않는 private 함수를 만들어서 재사용하면, 코드의 중복을 줄이고 가독성을 향상시킬 수 있습니다. 
  그러나 이런 함수를 만들기 위해서는, 락을 사용하는 코드와 사용하지 않는 코드를 명확하게 구분할 수 있어야 합니다.

3. 예외 안정성: 그 다음에야 (드디어) 문법적으로 명시적인 lock/unlock 호출은 지양하고 RAII기반의 문법을 사용해야 한다. 
  함수가 예외를 던진다면, 락은 자동으로 해제되어야 합니다. 
  std::lock_guard와 같은 RAII 기반의 락 관리 클래스를 사용하면 이를 보장할 수 있습니다.
*/
