#ifndef _THREAD_SAFE_SINGLETON_H
#define _THREAD_SAFE_SINGLETON_H

#include <atomic>
#include <mutex>

template <typename T>
class ThreadSafeSingleton{
public:
	ThreadSafeSingleton(void){
	}
	virtual ~ThreadSafeSingleton(void){
	}

	static T* getInstance(){
		auto ptr = instance.load();

		if( ptr == nullptr ){
			std::lock_guard<std::mutex> guard( lock );

			ptr = instance.load();
			if( ptr == nullptr ){
				ptr = new T();
				instance.store( ptr );
			}
		}
		return ptr;
	}

	static void releaseInstance(){
		delete instance.load();
		instance.store( nullptr );
	}

private:
	static std::mutex lock;
	static std::atomic<T*> instance;

};

template <typename T>
std::atomic<T*> ThreadSafeSingleton<T>::instance;

template <typename T>
std::mutex ThreadSafeSingleton<T>::lock;



#endif //_THREAD_SAFE_SINGLETON_H