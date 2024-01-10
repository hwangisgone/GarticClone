#ifndef THREAD_QUEUE_HPP
#define THREAD_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

// Thread-safe queue
template <typename T>
class TSQueue
{
private:
	// Underlying queue
	std::queue<T> m_queue;

	// mutex for thread synchronization
	std::mutex m_mutex;

	// Condition variable for signaling
	std::condition_variable m_cond;

public:
	size_t size() const
	{
		return m_queue.size();
	}
	// Pushes an element to the queue
	void push(T &item)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(std::move(item));

		// Notify one thread that
		// is waiting
		m_cond.notify_one();
	}

	T front()
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		T item = m_queue.front();
		return item;
	}

	// Pops an element off the queue
	T pop()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cond.wait(lock, [this]()
					{ return !m_queue.empty(); });

		T item = std::move(m_queue.front());
		m_queue.pop();

		return item;
	}
};

#endif