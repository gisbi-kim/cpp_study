/*
nanotime 을 써야하는 중요성
타이머의 한 틱보다 짧은 단위로 발생한 이벤트가 0단위시간으로 보이기 때문
이를 게이팅 에러 라고 부름 
따라서 타이머로 시간을 측정할 때는 반드시 대상 연산의 실행 시간을 타이머의 최소 틱 단위보다 크게 구성해야 오차를 최소화할 수 있다.
*/

#include <iostream>
#include <chrono>
#include <ctime>

using std::cout;
using std::endl;

namespace chrno = std::chrono;

using Clock = chrno::high_resolution_clock;
using Tpoint = Clock::time_point;

#define tic() Clock::now()
#define toc(time) Clock::now() - time

int main() 
{
  std::cout << "Hello World!\n";

  Tpoint tpoint = Clock::now();
  std::time_t tt = Clock::to_time_t(tpoint);

  auto disp = [](int i){ if(i % 100 == 0) cout << i << endl; };
  auto disp2 = [](int i, int interval = 100) { 
    if(i % interval == 0) 
      cout << i << endl; 
  };
  auto dispTocMilli = [](Tpoint& start) {
    auto diff = toc(start);
    cout 
      << chrno::duration<double, std::milli>(diff).count() 
      // << chrno::duration<double, std::micro>(diff).count() 
      // << chrno::milliseconds(diff).count()
      << " mill sec." 
      << endl;    
  };
  auto dispTocMicro = [](Tpoint& start) {
    auto diff = toc(start);
    cout 
      // << chrno::duration<double, std::milli>(diff).count() 
      << chrno::duration<double, std::micro>(diff).count() 
      // << chrno::milliseconds(diff).count()
      << " micro sec." 
      << endl;    
  };
  auto dispTocNano = [](Tpoint& start) {
    auto diff = toc(start);
    // auto tt_ = chrno::duration<double, std::nano>(diff).count();
    // double tt2_ = tt_ + 3444444.30;
    // cout << tt2_ << endl;
    cout 
      << chrno::duration<double, std::nano>(diff).count() 
      << " nano sec." 
      << endl;    
  };
  // auto dispRelToc = []()

  // 1st run 
  int num_1strun {1000000};
  int disp_duration_1strun {num_1strun/5};
  auto start = tic();
  for(int i=0; i<num_1strun; i++)
  {
    int a = 1;
    int b = 2;
    int c = a + b;
    disp2(i, disp_duration_1strun);
  }
  dispTocNano(start);

  // 2nd run 
  int num_2ndrun = 10 * num_1strun;
  int disp_duration_2ndrun {num_2ndrun/5};
  auto start2 = tic();
  for(int i=0; i<num_2ndrun; i++)
  {
    int a = 1;
    int b = 2;
    int c = a + b;
    disp2(i, disp_duration_2ndrun);
  }
  dispTocNano(start2);

  //
  cout << "end of the program." << endl;
  return 0;
}
