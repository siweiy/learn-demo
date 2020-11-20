#include <iostream>
#include <vector>
#include "boost/thread.hpp"

namespace Thread{

    void wait(int seconds) { 
        boost::this_thread::sleep(boost::posix_time::seconds(seconds)); // 中断函数
    } 

    void thread() { 
        for (int i = 0; i < 5; ++i) { 
            wait(1); 
            std::cout << i << std::endl; 
        } 
    }

    void test1() {
        boost::thread t(thread); 
        t.interrupt();// 中断
        t.join(); 
    }

    void test2() {
        std::cout << boost::this_thread::get_id() << std::endl; 
        // 返回基于CPU数目
        std::cout << boost::thread::hardware_concurrency() << std::endl; 
    }
}

namespace sync_thread{

    void wait(int seconds) { 
        boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
    } 

    int sum = 0;
    boost::mutex mutex_1; 
    boost::timed_mutex mutex_2;
    boost::shared_mutex mutex_3; 
    std::vector<int> random_numbers;

    void fill() { 
        std::srand(static_cast<unsigned int>(std::time(0))); 
        for (int i = 0; i < 3; ++i) { 
            boost::unique_lock<boost::shared_mutex> lock(mutex_3); 
            random_numbers.push_back(std::rand()); // 插入
            lock.unlock(); 
            wait(1); 
        } 
    } 

    void print() { 
        for (int i = 0; i < 3; ++i) { 
            wait(1); 
            boost::shared_lock<boost::shared_mutex> lock(mutex_3); 
            std::cout << random_numbers.back() << std::endl; // 访问
        } 
    } 

    void count() { 
        for (int i = 0; i < 3; ++i) { 
            wait(1); 
            // boost::shared_lock 的类提供了非独占锁
            boost::shared_lock<boost::shared_mutex> lock(mutex_3); 
            sum += random_numbers.back(); 
        } 
    } 

    void thread() { 
        for (int i = 0; i < 5; ++i) { 
            wait(1); 

            // 1
            // boost::lock_guard<boost::mutex> lock(mutex_1); 

            // 2
            // mutex_1.lock(); 

            // std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 

            // 2
            // mutex_1.unlock(); 

            // 3
            // boost::unique_lock 这个所谓的独占锁意味着一个互斥量同时只能被一个线程获取
            boost::unique_lock<boost::timed_mutex> lock(mutex_2, boost::try_to_lock); 
            if (!lock.owns_lock()) {// 是否获得互斥体
                lock.timed_lock(boost::get_system_time() + boost::posix_time::seconds(1)); // 等待1秒后再上锁
            }
            std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
            boost::timed_mutex *m = lock.release(); 
            m->unlock(); 
        }
    } 

    void test1() {
        boost::thread t1(thread); 
        boost::thread t2(thread); 
        t1.join(); 
        t2.join(); 
    }

    void test2() {
        boost::thread t1(fill); 
        boost::thread t2(print); 
        boost::thread t3(count); 
        t1.join(); 
        t2.join(); 
        t3.join(); 
        std::cout << "Sum: " << sum << std::endl; 
    }
}

namespace cond_thread{

    boost::mutex mutex; 
    boost::condition_variable_any cond; 
    std::vector<int> random_numbers; 

    void fill() { 
        std::srand(static_cast<unsigned int>(std::time(0))); 
        for (int i = 0; i < 3; ++i) { 
            boost::unique_lock<boost::mutex> lock(mutex); 
            random_numbers.push_back(std::rand()); 
            cond.notify_all(); 
            cond.wait(mutex); 
        } 
    } 

    void print() { 
        std::size_t next_size = 1; 
        for (int i = 0; i < 3; ++i) { 
            boost::unique_lock<boost::mutex> lock(mutex); 
            while (random_numbers.size() != next_size) {
                cond.wait(mutex); 
            }
            std::cout << random_numbers.back() << std::endl; 
            ++next_size; 
            cond.notify_all(); 
        } 
    } 

    void test1() {
        boost::thread t1(fill); 
        boost::thread t2(print); 
        t1.join(); 
        t2.join(); 
    }
}

// 线程本地存储（TLS）
namespace TLS_thread{

    void init_number_generator() { 
#if 1
        static bool done = false; 
        if (!done) { 
            std::cout << "111111" << std::endl; 
            done = true; 
            std::srand(static_cast<unsigned int>(std::time(0))); 
        } 
#else
        static boost::thread_specific_ptr<bool> tls; 
        // 使用 reset() 方法，可以把它的地址保存到 tls 里面。 
        // 在给出的例子中，会动态地分配一个 bool 型的变量，由 new 返回它的地址，并保存到 tls 里。 
        // 为了避免每次调用 init_number_generator() 都设置 tls ，
        // 它会通过 get() 函数检查是否已经保存了一个地址。
        if (!tls.get()) {
            tls.reset(new bool(false)); 
        }
        if (!*tls) { 
            std::cout << "111111" << std::endl; 
            *tls = true; 
            std::srand(static_cast<unsigned int>(std::time(0))); 
        } 
#endif
    } 

    boost::mutex mutex; 

    void random_number_generator() { 
        init_number_generator(); 
        int i = std::rand(); 
        boost::lock_guard<boost::mutex> lock(mutex); 
        std::cout << i << std::endl; 
        // boost::this_thread::sleep(boost::posix_time::seconds(2));
    } 

    void test1() { 
        boost::thread t[3]; 

        for (int i = 0; i < 3; ++i) {
            boost::this_thread::sleep(boost::posix_time::seconds(1));
            t[i] = boost::thread(random_number_generator); 
        }

        for (int i = 0; i < 3; ++i) {
            t[i].join(); 
        }
    } 
}

int main(int argc, char const *argv[])
{
    // Thread::test2();
    // sync_thread::test2();
    // cond_thread::test1();
    TLS_thread::test1();

    return 0;
}
