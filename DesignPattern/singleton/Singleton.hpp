<<<<<<< Updated upstream:DesignPattern/singleton/Singleton.hpp
/*
 * Copyright (CPP) 2019-2020 ----
 */
/******************************************************************************
 * @file     Singleton.hpp
 * @brief    Defines Singleton APIs
 * @version  V1.0
 * @date     24. September 2020
 * @usage    Singleton<class_name>::Instance()->func()
 ******************************************************************************/
#pragma once

=======
#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

/** Singleton template class ×*/
#define SINGLETON_INDEX 0
#define DEBUG_PRINT 1

#ifndef DEBUG_PRINT
#include <iostream>
#endif

#if SINGLETON_INDEX == 0

#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>

// 4、C++ 11版本之后的跨平台实现 -- 线程安全
>>>>>>> Stashed changes:Utils/Singleton.hpp
template<class T>
class Singleton {
private:
    static std::atomic<T*> m_instance;
    static std::mutex m_mutex;
    Singleton() = default;
    Singleton(const Singleton& s) = default;
    Singleton& operator=(const Singleton& s) = default;

    // TODO:模板嵌套模板没成功
    // template<class Ty=T>
    // class GarbageCollector {
    // public:
    //     ~GarbageCollector() { // 防止内存读写reorder不安全
    //         std::cout << "~GarbageCollector\n";
    //         Ty* tmp = m_instance.load(std::memory_order_relaxed);
    //         if (tmp) {
    //             std::cout << "free m_singleton: " << tmp << std::endl;
    //             delete tmp;
    //         }
    //     }
    // };
    // template<class Ty=T>
    // static GarbageCollector<Ty> m_gc;


public:
    void *getSingletonAddress() { 	// 后续使用指针
        return m_instance;
    }
    static T* getInstance() { 		// 第一次获取指针使用
        T* tmp = m_instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);
            tmp = m_instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new T();  // 1、分配内存，2 调用构造，3 赋值操作
                std::atomic_thread_fence(std::memory_order_release);//释放内存fence
                m_instance.store(tmp, std::memory_order_relaxed);
#ifdef DEBUG_PRINT
            	std::cout << "new m_singleton: " << tmp << std::endl;
#endif
            }
        }
        return tmp;
    }
    static void releaseSingletonAddress() {
    	T* tmp = m_instance.load(std::memory_order_relaxed);
        if (tmp) {
#ifdef DEBUG_PRINT
            std::cout << "free m_singleton: " << tmp << std::endl;
#endif
            delete tmp;
        }
    }
};

template<class T>
std::atomic<T*>  Singleton<T>::m_instance;
template<class T>
std::mutex Singleton<T>::m_mutex;
// template<class T>
// Singleton<T>::GarbageCollector<Ty> Singleton<T>::m_gc;


#elif SINGLETON_INDEX == 1

// 懒汉式
template<class T>
class Singleton {
private:
	Singleton() = default;  // 自动生成默认构造函数
    // explicit Singleton() {                           // 构造函数 会影响局部静态变量， 不能用隐式的构造函数
    //     cout << "Singleton construct\n";
    // }
    Singleton(const Singleton& s) = delete;    // 禁用拷贝构造函数
    Singleton& operator=(const Singleton& s) = delete; // 禁用拷贝赋值操作符
public:
    static T* getInstance(){
        static T s_singleton;  // C++11线程安全， C++11之前不是线程安全  __cxa_guard_acquire 和 __cxa_guard_release
        return &s_singleton;
    }
};

#endif

#endif