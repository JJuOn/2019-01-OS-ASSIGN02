#include <iostream>
#include <vector>
#include <string>

using namespace std;
// struct process
struct process {
	int pid; // 프로세스 ID
	int address; // 프로세스의 주소값
	int size; // 프로세스의 크기
};

// struct hole
struct hole {
	int address; // hole의 주소값
	int size; // hole의 크기
};

// 해당 프로세스를 할당해주는 함수
void allocate(vector<process>& memory, vector<hole>& holes, process& p);

// 해당 프로세스를 할당해제해주는 함수
void deallocate(vector<process>& memory, vector<hole>& holes, process p);

// 현재 메모리 상태를 출력해주는 함수
void printMemory(vector<process> memory);

// 현재 가용공간의 상태를 출력해주는 함수
void printHoles(vector<hole> holes);

// 가용공간의 크기를 반환해주는 함수
int getFreeSpace(vector<hole>& holes);

int main() {
	vector<process> memory; // memory를 나타내는 vector
	vector<hole> holes; // 가용공간을 나타내는 vector
	int total; // 전체 메모리 사이즈
	int pid, size; // 프로세스 ID, 프로세스의 크기
	// 전체 메모리의 크기 입력
	std::cout << "Enter the entire size of memory : ";
	cin >> total;
	// 가용공간 초기설정
	hole initalHole;
	initalHole.address = 0;
	initalHole.size = total;
	holes.push_back(initalHole);
	// pid가 -1이 아닐 때 반복
	do {
		// pid 입력, -1 입력시 프로그램 종료 
		std::cout << "Enter the process id (-1 to exit) : ";
		cin >> pid;
		if (pid == -1)
			break;
		// 프로세스의 크기 입력, 0 입력시 할당 해제
		std::cout << "Enter the size of process (0 to deallocate) : ";
		cin >> size;
		// 입력된 크기가 가용공간의 크기보다 크다면
		if (size > getFreeSpace(holes)) {
			// 프로세스의 크기가 매우 크다는 메세지를 출력하고 continue
			cout << "Too large process size ! \n";
			continue;
		}
		// 함수 parameter로 전달할 process p 초기화
		process p;
		p.pid = pid;
		p.size = size;
		// size가 0이 아니면
		if (size != 0) {
			// 프로세스 할당
			allocate(memory, holes, p);
		}
		// size가 0이면
		else {
			// 프로세스 할당 해제
			deallocate(memory, holes, p);
		}
		// 메모리의 상태 출력
		printMemory(memory);
		// 가용공간의 상태 출력
		printHoles(holes);
		cout << endl;
	} while (pid != -1);
	return 0;
}

// 해당 프로세스를 할당해주는 함수
void allocate(vector<process>& memory, vector<hole>& holes, process& p) {
	std::cout << "\nREQUEST " << p.pid << ": " << p.size << "K" << endl;
	// 메모리가 비어있다면, 처음 할당된 프로세스라면
	if (memory.empty()) {
		// 프로세스의 주소값을 0으로 설정
		p.address = 0;
		// memory에 삽입
		memory.push_back(p);
		// 가용공간의 주소값을 변경
		holes[0].address = p.size;
		// 새로 할당한 프로세스의 크기만큼 가용공간에서 제거
		holes[0].size -= p.size;
		// 할당 결과 출력
		std::cout << "Best Fit: Allocated at address\t" << p.address << "K" << endl;
		int freeSpace = getFreeSpace(holes);
		int blockNum = holes.size();
		int averageSize;
		if (blockNum == 0) {
			averageSize = 0;
		}
		else {
			averageSize = freeSpace / blockNum;
		}
		std::cout << freeSpace << "K free, " << blockNum << " block(s), average size = " << averageSize << "K\n" << endl;
		return;
	}
	// 이미 메모리에 프로세스가 존재하면,
	else {
		// 현재 가용공간의 block 중 할당할 프로세스의 크기보다 큰 block이 있는지 확인하는 flag
		bool found = false;
		// best fit을 찾기 위해 할당할 프로세스의 크기보다 큰 block중에서 size가 가장 작은 block의 index
		int bestIndex=0;
		// holes의 모든 hole에 대해 반복
		for (int i = 0; i < holes.size(); i++) {
			// 프로세스를 바로 할당할 수 있는 block이 있으면
			if (holes[i].size >= p.size) {
				// found에 true 저장
				found = true;
				// 해당 block이 best fit이라면
				if (holes[i].size < holes[bestIndex].size) {
					// bestIndex에 현재 block의 인덱스 저장
					bestIndex = i;
				}
			}
		}
		// 프로세스를 바로 할당할 수 있는 block이 있으면
		if (found) {
			// p의 주소값을 bestIndex에 해당하는 block의 주소값으로 저장
			p.address = holes[bestIndex].address;
			// 할당한 크기만큼 hole의 주소값 변경
			holes[bestIndex].address = p.address + p.size;
			// 할당한 크기만큼 hole의 사이즈 감소
			holes[bestIndex].size -= p.size;
			// memory에 process p 삽입
			memory.push_back(p);
		}
		// 프로세스를 바로 할당할 수 있는 block이 없으면
		else {
			// 가장 크기가 큰 block의 index 저장
			int maxHoleIndex = 0;
			// maxHoleIndex가 0이므로 i=1 부터 holes의 모든 block에 대해 반복
			for (int i = 1; i < holes.size(); i++) {
				// maxHoleIndex 위치의 block 크기보다 i 위치의 block 크기가 더 크다면
				if (holes[i].size > holes[maxHoleIndex].size) {
					// maxHoleIndex에 현재 index 저장
					maxHoleIndex = i;
				}
			}
			// hole의 갯수를 1로 만들 때 까지 반복
			while (holes.size() != 1) {
				// 모든 hole에 대해 반복, holes.erase()를 사용해야하기 때문에 iterator 사용 
				for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
					// 현재 hole과 maxHoleIndex 위치의 hole이 같다면
					if ((*it).address == holes[maxHoleIndex].address)
						// 스킵
						continue;
					// 현재 hole이 maxHoleIndex 위치의 hole보다 주소값기준 앞에 있다면
					else if ((*it).address < holes[maxHoleIndex].address) {
						// 이미 할당된 메모리의 프로세스에 대해
						for (int i = 0; i < memory.size(); i++) {
							// 해당 프로세스의 주소값이 현재 hole의 주소값과 maxHoleIndex 위치 hole의 주소값 사이에 있다면
							if (memory[i].address > (*it).address && memory[i].address < holes[maxHoleIndex].address)
								// 메모리의 주소값에서 현재 hole의 사이즈만큼 뺀다, 이를 통해 메모리 상의 프로세스가 주소값기준 앞으로 이동하게 된다
								memory[i].address -= (*it).size;
						}
						// maxHoleIndex 위치의 hole의 주소값을 현재 hole의 크기만큼 빼주면서 maxHoleIndex의 앞에 현재 hole을 붙인다
						holes[maxHoleIndex].address -= (*it).size;
						// maxHoleIndex의 앞에 현재 hole을 붙였기 때문에 maxHoleIndex의 size도 증가시켜준다
						holes[maxHoleIndex].size += (*it).size;
						// 해당 hole이 maxHoleIndex보다 앞에 위치해 있었으므로, 두 hole을 합친 이후 maxHoleIndex를 -1 해준다
						maxHoleIndex -= 1;
						// 두 hole이 합쳐졌기 때문에, 현재 hole은 삭제해준다
						holes.erase(it);
						break;
					}
					// 현재 hole이 maxHoleIndex 위치의 hole보다 주소값기준 뒤에 있다면
					else {
						// 이미 할당된 메모리의 프로세스에 대해
						for (int i = 0; i < memory.size(); i++) {
							// 해당 프로세스의 주소값이 현재 hole의 주소값과 maxHoleIndex 위치 hole의 주소값 사이에 있다면 
							if (memory[i].address < (*it).address && memory[i].address > holes[maxHoleIndex].address)
								// 메모리의 주소값에서 현재 hole의 사이즈만큼 뺀다, 이를 통해 메모리 상의 프로세스가 주소값기준 뒤로 이동하게 된다
								memory[i].address += (*it).size;
						}
						// maxHoleIndex의 뒤에 현재 hole을 붙였기 때문에 maxHoleIndex의 size만 증가시켜준다
						holes[maxHoleIndex].size += (*it).size;
						// 두 hole이 합쳐졌지만, maxHoleIndex의 뒤에 붙였기 때문에 maxHoleIndex의 값은 변화없고, 현재 hole은 삭제한다
						holes.erase(it);
						break;
					}
				}
			}
			// one single big hole이 생성되었으므로, 재귀함수를 호출하여 할당 실행
			allocate(memory, holes, p);
		}
	}
	// 할당 결과 출력
	std::cout << "Best Fit: Allocated at address\t" << p.address << "K" << endl;
	int freeSpace = getFreeSpace(holes);
	int blockNum = holes.size();
	int averageSize;
	if (blockNum == 0) {
		averageSize = 0;
	}
	else {
		averageSize = freeSpace / blockNum;
	}
	std::cout << freeSpace << "K free, " << blockNum << " block(s), average size = " << averageSize << "K\n" << endl;
	return;
}

// 해당 프로세스를 할당해제해주는 함수
void deallocate(vector<process>& memory, vector<hole>& holes, process p) {
	// 메모리의 모든 프로세스에 대해
	for (vector<process>::iterator it = memory.begin(); it != memory.end(); it++) {
		// process p에 해당하는 메모리의 프로세스를 찾으면
		if ((*it).pid == p.pid) {
			// 주소값과
			p.address = (*it).address;
			// 사이즈를 가져온 다음에
			p.size = (*it).size;
			// 메모리에서 해당 프로세스를 삭제한다
			memory.erase(it);
			break;
		}
	}
	std::cout << "\nFREE REQUEST " << p.pid << "(" << p.size << "K)" << endl;
	std::cout << "Best Fit: Freed at address\t" << p.address << "K" << endl;
	// 앞뒤로 최대 두번의 coalescing이 발생 가능하기 때문에 2번 반복
	for (int i = 0; i < 2; i++) {
		// 모든 hole에 대해
		for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
			// 할당 해제된 p의 위치 앞에 hole이 인접해 있다면
			if ((*it).address + (*it).size == p.address) {
				std::cout << "Coalescing blocks at addresses " << (*it).address << "K and " << p.address << "K" << endl;
				// 현재 hole이 p보다 앞에 위치해 있기 때문에 p의 주소값을 현재 hole의 주소값으로 바꿔준다
				p.address = (*it).address;
				// p의 크기에 현재 hole의 크기를 더한다
				p.size += (*it).size;
				// 기존의 hole을 삭제한다
				holes.erase(it);
				break;
			}
			// 할당 해제된 p의 위치 뒤에 hole이 인접해 있다면
			else if (p.address + p.size == (*it).address) {
				std::cout << "Coalescing blocks at addresses " << p.address << "K and " << (*it).address << "K" << endl;
				// 두 hole을 합쳐준 다음
				p.size += (*it).size;
				// 기존의 hole을 삭제한다
				holes.erase(it);
				break;
			}
		}
	}
	// 새로운 hole을 holes에 삽입
	hole newHole;
	newHole.address = p.address;
	newHole.size = p.size;
	holes.push_back(newHole);
	// 할당 해제 결과 출력
	int freeSpace = getFreeSpace(holes);
	int blockNum = holes.size();
	int averageSize;
	if (blockNum == 0) {
		averageSize = 0;
	}
	else {
		averageSize = freeSpace / blockNum;
	}
	std::cout << freeSpace << "K free, " << blockNum << " block(s), average size = " << averageSize << "K\n" << endl;
}

// 현재 메모리 상태를 출력해주는 함수
void printMemory(vector<process> memory) {
	std::cout << "<MEMORY>" << endl;
	// 모든 memory의 프로세스에 대해
	for (vector<process>::iterator it = memory.begin(); it != memory.end(); it++) {
		// 프로세스 ID와 할당된 공간의 시작과 끝 주소값 출력
		std::cout << "PID : " << (*it).pid << " IN " << (*it).address << "~" << (*it).address + (*it).size - 1 << endl;
	}
}

// 현재 가용공간의 상태를 출력해주는 함수
void printHoles(vector<hole> holes) {
	std::cout << "<HOLES>" << endl;
	// 모든 hole에 대해
	for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
		// 가용공간의 시작과 끝 주소값 출력
		std::cout << (*it).address << "~" << (*it).address + (*it).size - 1 << endl;
	}
}

// 가용공간의 크기를 반환해주는 함수
int getFreeSpace(vector<hole>& holes) {
	// 가용공간의 크기 초기값
	int size = 0;
	// 모든 hole에 대해
	for (vector<hole>::iterator it = holes.begin(); it != holes.end();) {
		// 크기가 0인 hole이 있다면
		if ((*it).size == 0) {
			// 해당 hole을 삭제
			holes.erase(it);
			// 반복문 재실행
			it = holes.begin();
			// 가용공간의 크기 초기화
			size = 0;
		}
		// 크기가 0인 hole이 아니라면
		else {
			// 전체 가용공간의 크기에 해당 hole의 크기를 더하고
			size += (*it).size;
			// 다음 hole에 대해 실행
			it++;
		}
	}
	return size;
}