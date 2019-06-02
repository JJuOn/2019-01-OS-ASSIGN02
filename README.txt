OS_ASSIGN02_2017103994_서주원 README.txt

1. 프로그램이 시작되면 다음과 같은 메세지가 출력됩니다.

Enter the entire size of memory :

다음과 같이 정수로 전체 메모리 사이즈를 입력해주시면 됩니다.

Enter the entire size of memory : 256

2. 프로세스 ID를 묻는 메세지가 출력됩니다.

Enter the process id (-1 to exit) :

이때 -1을 입력해 주시면 프로그램이 종료됩니다. 지금은 1을 입력하겠습니다.

Enter the process id (-1 to exit) : 1

3. 프로세스의 크기를 묻는 메세지가 출력됩니다. 

Enter the size of process (0 to deallocate) :

이때 0을 입력해 주시면 2.에서 입력한 프로세스 ID에 해당하는 프로세스가 할당 해제됩니다. 64를 입력하겠습니다.

Enter the size of process (0 to deallocate) : 64

4.  할당이 완료되면 다음과 같이, PID와 Best Fit일때 어느 주소값에 할당되는지, 가용공간의 크기와 가용공간의 개수, 가용공간의 평균 크기와 현재 메모리와 가용공간의 상태가 출력됩니다.

REQUEST 1: 64K
Best Fit: Allocated at address  0K
192K free, 1 block(s), average size = 192K

<MEMORY>
PID : 1 IN 0~63
<HOLES>
64~255

5. 2~4 과정을 3번 반복해보겠습니다. 출력내용은 다음과 같습니다.

Enter the process id (-1 to exit) : 2
Enter the size of process (0 to deallocate) : 64

REQUEST 2: 64K
Best Fit: Allocated at address  64K
128K free, 1 block(s), average size = 128K

<MEMORY>
PID : 1 IN 0~63
PID : 2 IN 64~127
<HOLES>
128~255

Enter the process id (-1 to exit) : 3
Enter the size of process (0 to deallocate) : 32

REQUEST 3: 32K
Best Fit: Allocated at address  128K
96K free, 1 block(s), average size = 96K

<MEMORY>
PID : 1 IN 0~63
PID : 2 IN 64~127
PID : 3 IN 128~159
<HOLES>
160~255

Enter the process id (-1 to exit) : 4
Enter the size of process (0 to deallocate) : 16

REQUEST 4: 16K
Best Fit: Allocated at address  160K
80K free, 1 block(s), average size = 80K

<MEMORY>
PID : 1 IN 0~63
PID : 2 IN 64~127
PID : 3 IN 128~159
PID : 4 IN 160~175
<HOLES>
176~255

6. 이번엔 프로세스 1을 할당 해제하겠습니다. 출력 내용은 다음과 같습니다.

Enter the process id (-1 to exit) : 1
Enter the size of process (0 to deallocate) : 0

FREE REQUEST 1(64K)
Best Fit: Freed at address      0K
144K free, 2 block(s), average size = 72K

<MEMORY>
PID : 2 IN 64~127
PID : 3 IN 128~159
PID : 4 IN 160~175
<HOLES>
176~255
0~63

기존 프로세스 1에 해당하는 메모리공간인 0~64가 할당해제되어 holes에 추가된것을 확인 할수있습니다.

7. 프로세스 3을 해제하고 프로세스 5에 32K 만큼의 공간을 할당하겠습니다.

Enter the process id (-1 to exit) : 3
Enter the size of process (0 to deallocate) : 0

FREE REQUEST 3(32K)
Best Fit: Freed at address      128K
176K free, 3 block(s), average size = 58K

<MEMORY>
PID : 2 IN 64~127
PID : 4 IN 160~175
<HOLES>
176~255
0~63
128~159

Enter the process id (-1 to exit) : 5
Enter the size of process (0 to deallocate) : 32

REQUEST 5: 32K
Best Fit: Allocated at address  128K
144K free, 2 block(s), average size = 72K

<MEMORY>
PID : 2 IN 64~127
PID : 4 IN 160~175
PID : 5 IN 128~159
<HOLES>
176~255
0~63

8. 이번엔 프로세스 2를 할당해제하겠습니다.

Enter the process id (-1 to exit) : 2
Enter the size of process (0 to deallocate) : 0

FREE REQUEST 2(64K)
Best Fit: Freed at address      64K
Coalescing blocks at addresses 0K and 64K
208K free, 2 block(s), average size = 104K

<MEMORY>
PID : 4 IN 160~175
PID : 5 IN 128~159
<HOLES>
176~255
0~127

Coalescing이 일어나 0K 위치의 block과 64K 위치의 block이 합쳐져 0~127에 해당하는 block이 생긴 것을 확인 할 수 있습니다.

9. 프로세스 ID에 -1을 입력하여 프로그램을 종료합니다.

Enter the process id (-1 to exit) : -1