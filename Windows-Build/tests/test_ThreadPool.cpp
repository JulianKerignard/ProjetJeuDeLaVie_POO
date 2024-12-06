#include "gtest/gtest.h"
#include "ThreadPool.h"
#include <chrono>
#include <thread>

TEST(ThreadPoolTest, TaskExecution) {
    ThreadPool pool(4);

    auto task1 = pool.enqueue([] { return 1 + 1; });
    auto task2 = pool.enqueue([](int a, int b) { return a + b; }, 2, 3);

    EXPECT_EQ(task1.get(), 2);
    EXPECT_EQ(task2.get(), 5);
}

TEST(ThreadPoolTest, MultipleTasks) {
    ThreadPool pool(4);
    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(pool.enqueue([i] { return i * i; }));
    }

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(results[i].get(), i * i);
    }
}

TEST(ThreadPoolTest, DelayedTaskExecution) {
    ThreadPool pool(4);

    auto start = std::chrono::high_resolution_clock::now();
    auto task = pool.enqueue([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 42;
    });

    EXPECT_EQ(task.get(), 42);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    EXPECT_GE(duration, 100);
}

/*
TEST(ThreadPoolTest, Shutdown) {
    ThreadPool pool(4);

    auto task = pool.enqueue([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 42;
    });

    pool.shutdown();
    EXPECT_EQ(task.get(), 42);
}

TEST(ThreadPoolTest, EnqueueAfterShutdown) {
    ThreadPool pool(4);
    pool.shutdown();

    EXPECT_THROW(pool.enqueue([] { return 1; }), std::runtime_error);
}
*/
