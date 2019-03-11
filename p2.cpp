// Created by Nicholas Webster

/******************
For this assignment, you will implement a simple multi-threaded program
  to generate a log file.
Your main function should create a file called <first initial + last name>.log.
For example, my log file will be named myang.log. Then it will create
  two separate threads, Thread-A and Thread-B.

Both threads will open the log file and write to it.
  Thread-A will write the numbers 1 to 26 ten times;
    each time on a separate line.
  Thread-B will write the letters A to Z ten times;
    each time on a separate line. Use nested for loops.

The main thread will write the following events to the log file:
    program start
    thread A created
    thread B created
    thread A terminated
    thread B terminated
    program end
*******************/

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
