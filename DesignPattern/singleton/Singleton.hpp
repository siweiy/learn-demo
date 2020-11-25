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

template<class T>
class Singleton
{
public:
	static T* Instance() {
		if (NULL == _member) {
			_member = new T();
		}
		return _member;
	}

	static void Release() {
		if (_member) {
			delete _member;
			_member = NULL;
		}
	}

private:
	Singleton(){}

	~Singleton() { Release(); }

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	static T* _member;
};

template<class T>
T* Singleton<T>::_member = NULL;