#ifndef _PROCESS_POOL_H
#define _PROCESS_POOL_H

#include <thread>
#include <functional>
#include <queue>
#include <list>
#include <mutex>
#include <condition_variable>

template <typename T>
class ProcessPool{
public:
	typedef std::function<bool(T)>	handler_t;
	typedef std::thread				worker_t;
	typedef std::unique_lock<std::mutex> lock_t;

	ProcessPool(){
	}
	ProcessPool(int nWorkers, handler_t handler){
		createWorkers( nWorkers, handler );
	}
	virtual ~ProcessPool(){
		killWorkers();
	}

	void enqueue(T workItem){
		lock_t lock(queueMutex);
			qWork.push( workItem );
		lock.unlock();

		signal.notify_one();
	}

protected:
	void createWorkers(int nWorkers,handler_t handler){
		quit = false;

		for(int i=0;i<nWorkers;i++){
			int tid = i;
			workers.push_back( std::thread( [=](){
				while( !quit ){
					T workItem;
					bool result;

					lock_t lock( queueMutex );
						while( qWork.empty() )
							signal.wait(lock);

						workItem = qWork.front();
						qWork.pop();
					lock.unlock();

					result = handler( workItem );
				}})
			);
		}
	}
	void killWorkers(){
		for( auto &worker : workers ){
			worker.detach();
		}

		workers.clear();
		quit = true;
	}
	void flush(){
	}

protected:
	std::list<worker_t> workers;
	std::queue<T> qWork;

	std::condition_variable signal;
	std::mutex queueMutex;

	bool quit;
};

#endif // _PROCESS_POOL_H