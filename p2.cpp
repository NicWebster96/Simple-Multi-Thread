// Created by Nicholas Webster

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

void numbers(ostream& myFile) {
    mtx.lock();
    for (int i=0; i<10; i++) {
        for (int j=1; j<27; j++) {
            myFile << j << " ";
        }
        myFile << endl;
    }
    mtx.unlock();
}

void letters(ostream& myFile) {
    mtx.lock();
    for (int i=0; i<10; i++) {
        for (int j=65; j<91; j++) {
            myFile << char(j) << " ";
        }
        myFile << endl;
    }
    mtx.unlock();
}

int main() {

    string fileName = "nwebster.log";
    ofstream myFile(fileName);
    myFile << "Nic's Project 2 started" << endl;

    mtx.lock();

    thread threadA(numbers,ref(myFile));
    thread threadB(letters,ref(myFile));
    myFile << "Thread A (ID " << threadA.get_id() << ") created!" << endl;
    myFile << "Thread B (ID " << threadB.get_id() << ") created!" << endl;

    mtx.unlock();
    threadA.join();
    threadB.join();

    myFile << "Thread A (ID " << threadA.get_id() << ") terminated!" << endl;
    myFile << "Thread B (ID " << threadB.get_id() << ") terminated!" << endl;
    myFile << "Nic's Project 2 ended" << endl;
    return 0;
}
