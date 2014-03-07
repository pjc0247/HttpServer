#ifndef _SPINLOCK_H
#define _SPINLOCK_H

#include <atomic>
#include <thread>

class SpinLock{
public:
	SpinLock() : atom(0){
	}

	void lock(){
		while( atom.exchange(1, std::memory_order_acquire) == 1 ){
		}
	}
	void unlock(){
		atom.store(0, std::memory_order_release);
	}
	void force_lock(){
		atom.store(1, std::memory_order_release);
	}

protected:
	std::atomic<int> atom;
};

#endif //_SPINLOCK_H