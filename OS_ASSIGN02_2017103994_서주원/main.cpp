#include <iostream>
#include <vector>
#include <string>

using namespace std;
// struct process
struct process {
	int pid; // ���μ��� ID
	int address; // ���μ����� �ּҰ�
	int size; // ���μ����� ũ��
};

// struct hole
struct hole {
	int address; // hole�� �ּҰ�
	int size; // hole�� ũ��
};

// �ش� ���μ����� �Ҵ����ִ� �Լ�
void allocate(vector<process>& memory, vector<hole>& holes, process& p);

// �ش� ���μ����� �Ҵ��������ִ� �Լ�
void deallocate(vector<process>& memory, vector<hole>& holes, process p);

// ���� �޸� ���¸� ������ִ� �Լ�
void printMemory(vector<process> memory);

// ���� ��������� ���¸� ������ִ� �Լ�
void printHoles(vector<hole> holes);

// ��������� ũ�⸦ ��ȯ���ִ� �Լ�
int getFreeSpace(vector<hole>& holes);

int main() {
	vector<process> memory; // memory�� ��Ÿ���� vector
	vector<hole> holes; // ��������� ��Ÿ���� vector
	int total; // ��ü �޸� ������
	int pid, size; // ���μ��� ID, ���μ����� ũ��
	// ��ü �޸��� ũ�� �Է�
	std::cout << "Enter the entire size of memory : ";
	cin >> total;
	// ������� �ʱ⼳��
	hole initalHole;
	initalHole.address = 0;
	initalHole.size = total;
	holes.push_back(initalHole);
	// pid�� -1�� �ƴ� �� �ݺ�
	do {
		// pid �Է�, -1 �Է½� ���α׷� ���� 
		std::cout << "Enter the process id (-1 to exit) : ";
		cin >> pid;
		if (pid == -1)
			break;
		// ���μ����� ũ�� �Է�, 0 �Է½� �Ҵ� ����
		std::cout << "Enter the size of process (0 to deallocate) : ";
		cin >> size;
		// �Էµ� ũ�Ⱑ ��������� ũ�⺸�� ũ�ٸ�
		if (size > getFreeSpace(holes)) {
			// ���μ����� ũ�Ⱑ �ſ� ũ�ٴ� �޼����� ����ϰ� continue
			cout << "Too large process size ! \n";
			continue;
		}
		// �Լ� parameter�� ������ process p �ʱ�ȭ
		process p;
		p.pid = pid;
		p.size = size;
		// size�� 0�� �ƴϸ�
		if (size != 0) {
			// ���μ��� �Ҵ�
			allocate(memory, holes, p);
		}
		// size�� 0�̸�
		else {
			// ���μ��� �Ҵ� ����
			deallocate(memory, holes, p);
		}
		// �޸��� ���� ���
		printMemory(memory);
		// ��������� ���� ���
		printHoles(holes);
		cout << endl;
	} while (pid != -1);
	return 0;
}

// �ش� ���μ����� �Ҵ����ִ� �Լ�
void allocate(vector<process>& memory, vector<hole>& holes, process& p) {
	std::cout << "\nREQUEST " << p.pid << ": " << p.size << "K" << endl;
	// �޸𸮰� ����ִٸ�, ó�� �Ҵ�� ���μ������
	if (memory.empty()) {
		// ���μ����� �ּҰ��� 0���� ����
		p.address = 0;
		// memory�� ����
		memory.push_back(p);
		// ��������� �ּҰ��� ����
		holes[0].address = p.size;
		// ���� �Ҵ��� ���μ����� ũ�⸸ŭ ����������� ����
		holes[0].size -= p.size;
		// �Ҵ� ��� ���
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
	// �̹� �޸𸮿� ���μ����� �����ϸ�,
	else {
		// ���� ��������� block �� �Ҵ��� ���μ����� ũ�⺸�� ū block�� �ִ��� Ȯ���ϴ� flag
		bool found = false;
		// best fit�� ã�� ���� �Ҵ��� ���μ����� ũ�⺸�� ū block�߿��� size�� ���� ���� block�� index
		int bestIndex=0;
		// holes�� ��� hole�� ���� �ݺ�
		for (int i = 0; i < holes.size(); i++) {
			// ���μ����� �ٷ� �Ҵ��� �� �ִ� block�� ������
			if (holes[i].size >= p.size) {
				// found�� true ����
				found = true;
				// �ش� block�� best fit�̶��
				if (holes[i].size < holes[bestIndex].size) {
					// bestIndex�� ���� block�� �ε��� ����
					bestIndex = i;
				}
			}
		}
		// ���μ����� �ٷ� �Ҵ��� �� �ִ� block�� ������
		if (found) {
			// p�� �ּҰ��� bestIndex�� �ش��ϴ� block�� �ּҰ����� ����
			p.address = holes[bestIndex].address;
			// �Ҵ��� ũ�⸸ŭ hole�� �ּҰ� ����
			holes[bestIndex].address = p.address + p.size;
			// �Ҵ��� ũ�⸸ŭ hole�� ������ ����
			holes[bestIndex].size -= p.size;
			// memory�� process p ����
			memory.push_back(p);
		}
		// ���μ����� �ٷ� �Ҵ��� �� �ִ� block�� ������
		else {
			// ���� ũ�Ⱑ ū block�� index ����
			int maxHoleIndex = 0;
			// maxHoleIndex�� 0�̹Ƿ� i=1 ���� holes�� ��� block�� ���� �ݺ�
			for (int i = 1; i < holes.size(); i++) {
				// maxHoleIndex ��ġ�� block ũ�⺸�� i ��ġ�� block ũ�Ⱑ �� ũ�ٸ�
				if (holes[i].size > holes[maxHoleIndex].size) {
					// maxHoleIndex�� ���� index ����
					maxHoleIndex = i;
				}
			}
			// hole�� ������ 1�� ���� �� ���� �ݺ�
			while (holes.size() != 1) {
				// ��� hole�� ���� �ݺ�, holes.erase()�� ����ؾ��ϱ� ������ iterator ��� 
				for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
					// ���� hole�� maxHoleIndex ��ġ�� hole�� ���ٸ�
					if ((*it).address == holes[maxHoleIndex].address)
						// ��ŵ
						continue;
					// ���� hole�� maxHoleIndex ��ġ�� hole���� �ּҰ����� �տ� �ִٸ�
					else if ((*it).address < holes[maxHoleIndex].address) {
						// �̹� �Ҵ�� �޸��� ���μ����� ����
						for (int i = 0; i < memory.size(); i++) {
							// �ش� ���μ����� �ּҰ��� ���� hole�� �ּҰ��� maxHoleIndex ��ġ hole�� �ּҰ� ���̿� �ִٸ�
							if (memory[i].address > (*it).address && memory[i].address < holes[maxHoleIndex].address)
								// �޸��� �ּҰ����� ���� hole�� �����ŭ ����, �̸� ���� �޸� ���� ���μ����� �ּҰ����� ������ �̵��ϰ� �ȴ�
								memory[i].address -= (*it).size;
						}
						// maxHoleIndex ��ġ�� hole�� �ּҰ��� ���� hole�� ũ�⸸ŭ ���ָ鼭 maxHoleIndex�� �տ� ���� hole�� ���δ�
						holes[maxHoleIndex].address -= (*it).size;
						// maxHoleIndex�� �տ� ���� hole�� �ٿ��� ������ maxHoleIndex�� size�� ���������ش�
						holes[maxHoleIndex].size += (*it).size;
						// �ش� hole�� maxHoleIndex���� �տ� ��ġ�� �־����Ƿ�, �� hole�� ��ģ ���� maxHoleIndex�� -1 ���ش�
						maxHoleIndex -= 1;
						// �� hole�� �������� ������, ���� hole�� �������ش�
						holes.erase(it);
						break;
					}
					// ���� hole�� maxHoleIndex ��ġ�� hole���� �ּҰ����� �ڿ� �ִٸ�
					else {
						// �̹� �Ҵ�� �޸��� ���μ����� ����
						for (int i = 0; i < memory.size(); i++) {
							// �ش� ���μ����� �ּҰ��� ���� hole�� �ּҰ��� maxHoleIndex ��ġ hole�� �ּҰ� ���̿� �ִٸ� 
							if (memory[i].address < (*it).address && memory[i].address > holes[maxHoleIndex].address)
								// �޸��� �ּҰ����� ���� hole�� �����ŭ ����, �̸� ���� �޸� ���� ���μ����� �ּҰ����� �ڷ� �̵��ϰ� �ȴ�
								memory[i].address += (*it).size;
						}
						// maxHoleIndex�� �ڿ� ���� hole�� �ٿ��� ������ maxHoleIndex�� size�� ���������ش�
						holes[maxHoleIndex].size += (*it).size;
						// �� hole�� ����������, maxHoleIndex�� �ڿ� �ٿ��� ������ maxHoleIndex�� ���� ��ȭ����, ���� hole�� �����Ѵ�
						holes.erase(it);
						break;
					}
				}
			}
			// one single big hole�� �����Ǿ����Ƿ�, ����Լ��� ȣ���Ͽ� �Ҵ� ����
			allocate(memory, holes, p);
		}
	}
	// �Ҵ� ��� ���
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

// �ش� ���μ����� �Ҵ��������ִ� �Լ�
void deallocate(vector<process>& memory, vector<hole>& holes, process p) {
	// �޸��� ��� ���μ����� ����
	for (vector<process>::iterator it = memory.begin(); it != memory.end(); it++) {
		// process p�� �ش��ϴ� �޸��� ���μ����� ã����
		if ((*it).pid == p.pid) {
			// �ּҰ���
			p.address = (*it).address;
			// ����� ������ ������
			p.size = (*it).size;
			// �޸𸮿��� �ش� ���μ����� �����Ѵ�
			memory.erase(it);
			break;
		}
	}
	std::cout << "\nFREE REQUEST " << p.pid << "(" << p.size << "K)" << endl;
	std::cout << "Best Fit: Freed at address\t" << p.address << "K" << endl;
	// �յڷ� �ִ� �ι��� coalescing�� �߻� �����ϱ� ������ 2�� �ݺ�
	for (int i = 0; i < 2; i++) {
		// ��� hole�� ����
		for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
			// �Ҵ� ������ p�� ��ġ �տ� hole�� ������ �ִٸ�
			if ((*it).address + (*it).size == p.address) {
				std::cout << "Coalescing blocks at addresses " << (*it).address << "K and " << p.address << "K" << endl;
				// ���� hole�� p���� �տ� ��ġ�� �ֱ� ������ p�� �ּҰ��� ���� hole�� �ּҰ����� �ٲ��ش�
				p.address = (*it).address;
				// p�� ũ�⿡ ���� hole�� ũ�⸦ ���Ѵ�
				p.size += (*it).size;
				// ������ hole�� �����Ѵ�
				holes.erase(it);
				break;
			}
			// �Ҵ� ������ p�� ��ġ �ڿ� hole�� ������ �ִٸ�
			else if (p.address + p.size == (*it).address) {
				std::cout << "Coalescing blocks at addresses " << p.address << "K and " << (*it).address << "K" << endl;
				// �� hole�� ������ ����
				p.size += (*it).size;
				// ������ hole�� �����Ѵ�
				holes.erase(it);
				break;
			}
		}
	}
	// ���ο� hole�� holes�� ����
	hole newHole;
	newHole.address = p.address;
	newHole.size = p.size;
	holes.push_back(newHole);
	// �Ҵ� ���� ��� ���
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

// ���� �޸� ���¸� ������ִ� �Լ�
void printMemory(vector<process> memory) {
	std::cout << "<MEMORY>" << endl;
	// ��� memory�� ���μ����� ����
	for (vector<process>::iterator it = memory.begin(); it != memory.end(); it++) {
		// ���μ��� ID�� �Ҵ�� ������ ���۰� �� �ּҰ� ���
		std::cout << "PID : " << (*it).pid << " IN " << (*it).address << "~" << (*it).address + (*it).size - 1 << endl;
	}
}

// ���� ��������� ���¸� ������ִ� �Լ�
void printHoles(vector<hole> holes) {
	std::cout << "<HOLES>" << endl;
	// ��� hole�� ����
	for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
		// ��������� ���۰� �� �ּҰ� ���
		std::cout << (*it).address << "~" << (*it).address + (*it).size - 1 << endl;
	}
}

// ��������� ũ�⸦ ��ȯ���ִ� �Լ�
int getFreeSpace(vector<hole>& holes) {
	// ��������� ũ�� �ʱⰪ
	int size = 0;
	// ��� hole�� ����
	for (vector<hole>::iterator it = holes.begin(); it != holes.end();) {
		// ũ�Ⱑ 0�� hole�� �ִٸ�
		if ((*it).size == 0) {
			// �ش� hole�� ����
			holes.erase(it);
			// �ݺ��� �����
			it = holes.begin();
			// ��������� ũ�� �ʱ�ȭ
			size = 0;
		}
		// ũ�Ⱑ 0�� hole�� �ƴ϶��
		else {
			// ��ü ��������� ũ�⿡ �ش� hole�� ũ�⸦ ���ϰ�
			size += (*it).size;
			// ���� hole�� ���� ����
			it++;
		}
	}
	return size;
}