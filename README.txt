OS_ASSIGN02_2017103994_���ֿ� README.txt

1. ���α׷��� ���۵Ǹ� ������ ���� �޼����� ��µ˴ϴ�.

Enter the entire size of memory :

������ ���� ������ ��ü �޸� ����� �Է����ֽø� �˴ϴ�.

Enter the entire size of memory : 256

2. ���μ��� ID�� ���� �޼����� ��µ˴ϴ�.

Enter the process id (-1 to exit) :

�̶� -1�� �Է��� �ֽø� ���α׷��� ����˴ϴ�. ������ 1�� �Է��ϰڽ��ϴ�.

Enter the process id (-1 to exit) : 1

3. ���μ����� ũ�⸦ ���� �޼����� ��µ˴ϴ�. 

Enter the size of process (0 to deallocate) :

�̶� 0�� �Է��� �ֽø� 2.���� �Է��� ���μ��� ID�� �ش��ϴ� ���μ����� �Ҵ� �����˴ϴ�. 64�� �Է��ϰڽ��ϴ�.

Enter the size of process (0 to deallocate) : 64

4.  �Ҵ��� �Ϸ�Ǹ� ������ ����, PID�� Best Fit�϶� ��� �ּҰ��� �Ҵ�Ǵ���, ��������� ũ��� ��������� ����, ��������� ��� ũ��� ���� �޸𸮿� ��������� ���°� ��µ˴ϴ�.

REQUEST 1: 64K
Best Fit: Allocated at address  0K
192K free, 1 block(s), average size = 192K

<MEMORY>
PID : 1 IN 0~63
<HOLES>
64~255

5. 2~4 ������ 3�� �ݺ��غ��ڽ��ϴ�. ��³����� ������ �����ϴ�.

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

6. �̹��� ���μ��� 1�� �Ҵ� �����ϰڽ��ϴ�. ��� ������ ������ �����ϴ�.

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

���� ���μ��� 1�� �ش��ϴ� �޸𸮰����� 0~64�� �Ҵ������Ǿ� holes�� �߰��Ȱ��� Ȯ�� �Ҽ��ֽ��ϴ�.

7. ���μ��� 3�� �����ϰ� ���μ��� 5�� 32K ��ŭ�� ������ �Ҵ��ϰڽ��ϴ�.

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

8. �̹��� ���μ��� 2�� �Ҵ������ϰڽ��ϴ�.

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

Coalescing�� �Ͼ 0K ��ġ�� block�� 64K ��ġ�� block�� ������ 0~127�� �ش��ϴ� block�� ���� ���� Ȯ�� �� �� �ֽ��ϴ�.

9. ���μ��� ID�� -1�� �Է��Ͽ� ���α׷��� �����մϴ�.

Enter the process id (-1 to exit) : -1