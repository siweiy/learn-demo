#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <unistd.h>

class Thread {
public:
    Thread() : m_bThreadExit(false) {}
    ~Thread() { this->stop(); }

    void start() {
        this->m_bThreadExit = false;
        m_runTask = std::thread(&Thread::run, this);// 创建线程并返回句柄
    }

    void stop() {
        if (!this->m_bThreadExit) {
            this->m_bThreadExit = true;
            m_runTask.join();
        }
    }

private:
    void run() {
        while (!m_bThreadExit) {
            std::cout << "2222222222222" << std::endl;
            sleep(1);
        }
    }

    bool m_bThreadExit;
    std::thread m_runTask;
    std::mutex m_Mutex;
};

int main(int argc, char const *argv[])
{
	Thread th;
	th.start();
	sleep(5);
	th.stop();
    
	return 0;
}

