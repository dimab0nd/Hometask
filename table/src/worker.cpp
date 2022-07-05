#include "worker.h"


Worker::Worker(int n)
{
    this->number = n;
    answers.clear();
}

void Worker::doHeavyCaclulations()
{
    for(int i = 1; i < number; ++i)
    {
        if(isPrime(i)) answers.push_back(i);
        emit(progress(i));
    }
}

bool Worker::isPrime(int n)
{
    if(n > 0 && n < 4) return true;
     else
    {
        for(int i = 4; i < n; ++i)
        {
            if(n % i == 0) return false;
        }
        return true;
    }
}
