#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct process {
	int pid;
	int address;
	int size;
};
struct hole {
	int address;
	int size;
};

void allocate(vector<process>& memory, vector<hole>& holes, process& p);
void deallocate(vector<process>& memory, vector<hole>& holes, process p);
void printMemory(vector<process> memory);
void printHoles(vector<hole> holes);
int getFreeSpace(vector<hole>& holes);

int main() {
	vector<process> memory;
	vector<hole> holes;
	int total;
	int pid, size;
	std::cout << "Enter the entire size of memory : ";
	cin >> total;
	hole initalHole;
	initalHole.address = 0;
	initalHole.size = total;
	holes.push_back(initalHole);
	do {
		std::cout << "Enter the process id (-1 to exit) : ";
		cin >> pid;
		if (pid == -1)
			break;
		std::cout << "Enter the size of process (0 to deallocate) : ";
		cin >> size;
		if (size > getFreeSpace(holes)) {
			cout << "Too large process size ! \n";
			continue;
		}
		process p;
		p.pid = pid;
		p.size = size;
		if (size != 0) {
			allocate(memory, holes, p);
		}
		else {
			deallocate(memory, holes, p);
		}
		printMemory(memory);
		printHoles(holes);
		cout << endl;
	} while (pid != -1);
	return 0;
}

void allocate(vector<process>& memory, vector<hole>& holes, process& p) {
	std::cout << "\nREQUEST " << p.pid << ": " << p.size << "K" << endl;
	if (memory.empty()) {
		p.address = 0;
		memory.push_back(p);
		holes[0].address = p.size;
		holes[0].size -= p.size;
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
	else {
		bool found = false;
		int bestIndex=0;
		for (int i = 0; i < holes.size(); i++) {
			if (holes[i].size >= p.size) {
				found = true;
				if (holes[i].size < holes[bestIndex].size) {
					bestIndex = i;
				}
			}
		}
		if (found) {
			p.address = holes[bestIndex].address;
			holes[bestIndex].address = p.address + p.size;
			holes[bestIndex].size -= p.size;
			memory.push_back(p);
		}
		else {
			int maxHoleIndex = 0;
			for (int i = 1; i < holes.size(); i++) {
				if (holes[i].size > holes[maxHoleIndex].size) {
					maxHoleIndex = i;
				}
			}
			while (holes.size() != 1) {
				for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
					if ((*it).address == holes[maxHoleIndex].address)
						continue;
					else if ((*it).address < holes[maxHoleIndex].address) {
						for (int i = 0; i < memory.size(); i++) {
							if (memory[i].address > (*it).address && memory[i].address < holes[maxHoleIndex].address)
								memory[i].address -= (*it).size;
						}
						holes[maxHoleIndex].address -= (*it).size;
						holes[maxHoleIndex].size += (*it).size;
						maxHoleIndex -= 1;
						holes.erase(it);
						break;
					}
					else {
						for (int i = 0; i < memory.size(); i++) {
							if (memory[i].address < (*it).address && memory[i].address > holes[maxHoleIndex].address)
								memory[i].address += (*it).size;
						}
						holes[maxHoleIndex].size += (*it).size;
						holes.erase(it);
						break;
					}
				}
			}
			allocate(memory, holes, p);
		}
	}
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

void deallocate(vector<process>& memory, vector<hole>& holes, process p) {
	for (vector<process>::iterator it = memory.begin(); it != memory.end(); it++) {
		if ((*it).pid == p.pid) {
			p.address = (*it).address;
			p.size = (*it).size;
			memory.erase(it);
			break;
		}
	}
	std::cout << "\nFREE REQUEST " << p.pid << "(" << p.size << "K)" << endl;
	std::cout << "Best Fit: Freed at address\t" << p.address << "K" << endl;
	for (int i = 0; i < 2; i++) {
		for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
			if ((*it).address + (*it).size == p.address) {
				std::cout << "Coalescing blocks at addresses" << (*it).address << "K and " << p.address << "K" << endl;
				p.address = (*it).address;
				p.size += (*it).size;
				holes.erase(it);
				break;
			}
			else if (p.address + p.size == (*it).address) {
				std::cout << "Coalescing blocks at addresses" << p.address << "K and " << (*it).address << "K" << endl;
				p.size += (*it).size;
				holes.erase(it);
				break;
			}
		}
	}
	hole newHole;
	newHole.address = p.address;
	newHole.size = p.size;
	holes.push_back(newHole);
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

void printMemory(vector<process> memory) {
	std::cout << "<MEMORY>" << endl;
	for (vector<process>::iterator it = memory.begin(); it != memory.end(); it++) {
		std::cout << "PID : " << (*it).pid << " IN " << (*it).address << "~" << (*it).address + (*it).size - 1 << endl;
	}
}

void printHoles(vector<hole> holes) {
	std::cout << "<HOLES>" << endl;
	for (vector<hole>::iterator it = holes.begin(); it != holes.end(); it++) {
		std::cout << (*it).address << "~" << (*it).address + (*it).size - 1 << endl;
	}
}

int getFreeSpace(vector<hole>& holes) {
	int size = 0;
	for (vector<hole>::iterator it = holes.begin(); it != holes.end();) {
		if ((*it).size == 0) {
			holes.erase(it);
			it = holes.begin();
			size = 0;
		}
		else {
			size += (*it).size;
			it++;
		}
	}
	return size;
}