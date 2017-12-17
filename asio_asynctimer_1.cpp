//boost asio 서비스 header 
//io_service 와 steady_timer 
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>

//chrono 시간관련 C++ 표준 모듈
#include <chrono>
#include <iostream>


using namespace boost::asio;

void handler(const boost::system::error_code& ec){
  std::cout << "3 sec\n";
}


int main()
{

  // asio 핵심은 blocking 과 non-blocking

  // [ async_xx 함수(xx=wait,read,write)]
  // 1. 즉시 함수 return 을 반환-> non-blocking
  // 2. 대신 callback 또는 handler를 전달
  // 3. 요청한 작업이 끝나면 callback(handler)를 실행


  // [ xx 함수(xx=wait,read,write)]
  // 1. 함수 return 까지 기다림 -> blocking
  // 2. 다음 라인 작업을 진행


  // operation system 의 동기,비동기 작업 결과를 확인할 수있도록 인터페이싱
  // ioservices 는 os의 wrapper라고 인식 필요
  io_service ioservice;


  // 3초를 기다리는 timer 생성
  steady_timer timer{ioservice, std::chrono::seconds{3}};

  // *** [non-blocking wait 호출] ***
  timer.async_wait(handler);

  ioservice.run();
}

