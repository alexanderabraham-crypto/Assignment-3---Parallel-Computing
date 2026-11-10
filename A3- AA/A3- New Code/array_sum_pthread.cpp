
#include <iostream>
#include <pthread.h>

void* testThread(void* arg)
{
    std::cout << "Hello from a Pthread!" << std::endl;
    return nullptr;
}

int main()
{
    pthread_t thread;

    pthread_create(&thread, nullptr, testThread, nullptr);

    pthread_join(thread, nullptr);

    std::cout << "Main program finished!" << std::endl;

    return 0;
}

