# BGMs
 
2017.12.17

BOOST ASIO 개념 설명

Blocking :
- 함수가 끝날때 까지 기다리는 동작

Non-Blocking :
- 함수가 끝날때 까지 기다리지 않고 handler를 넘겨주고
- 다른 일을 하다가 함수가 끝났을 때 handler를 실행

To do

1. 개발 서버에 접속해서 git config 설정

<아래 명령어 참조>
-$ git config --global user.name "John Doe"
-$ git config --global user.email johndoe@example.com


2. GIT에 올려놓은 프로젝트 clone

-$ git clone http://github.com/elentail/BGMs

3. blocking 과 non-blocking 소스 컴파일

< 컴파일 방법 g++ 을이용>

- g++ 통해 xx.cpp 를 컴파일하여 실행가능한 output test 파일을 만듬
- 해당 과정에서  library boost_system 을 link 시키는데
- 해당 코드가 c++11 스타일로 되어있음

-$ g++ -o test1 asio_synctimer_1.cpp -lboost_system -std=c++11
-$ g++ -o test2 asio_asynctimer_1.cpp -lboost_system -std=c++11


4. 과제 timer 추가

- 현재 3초 타이머 외에 5초 타이머를 추가
- 제한조건 non-blocking 작업을 통해 가장 긴 타이머 시간에 모든 작업 종료
(3초, 5초 2개 타이머가 동시에 시작해서 5초 후 종료 되도록 코드 수정)


* 시간이 되면 ReadAsyncWithTCP.cpp 어떤 프로그램인지 파악
