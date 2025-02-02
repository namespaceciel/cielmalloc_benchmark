#include <ciel/core/config.hpp>
#include <ciel/core/message.hpp>
#include <ciel/vector.hpp>
#include <cielmalloc/interface.hpp>
#include <cstddef>
#include <cstdlib>
#include <ctz/scheduler.hpp>
#include <ctz/ticket.hpp>
#include <memory>
#include <new>

void* operator new(size_t sz) {
    if CIEL_LIKELY (void* ptr = cielmalloc::malloc(sz)) {
        return ptr;
    }

    CIEL_THROW_EXCEPTION(std::bad_alloc{});
}

void* operator new[](size_t sz) {
    if CIEL_LIKELY (void* ptr = cielmalloc::malloc(sz)) {
        return ptr;
    }

    CIEL_THROW_EXCEPTION(std::bad_alloc{});
}

void operator delete(void* ptr) noexcept {
    cielmalloc::free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept {
    cielmalloc::free(ptr);
}

void operator delete[](void* ptr) noexcept {
    cielmalloc::free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    cielmalloc::free(ptr);
}

CIEL_NODISCARD bool isPrime(int i) noexcept {
    const int c = static_cast<int>(std::sqrt(i));

    for (int j = 2; j <= c; j++) {
        if (i % j == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    ctz::Scheduler::start(ctz::SchedulerConfig::allCores());
    CIEL_DEFER({ ctz::Scheduler::stop(); });

    ctz::TicketQueue queue;

    for (int searchBase = 1; searchBase <= 100000; searchBase += 1000) {
        auto ticket = queue.take();

        ctz::Scheduler::schedule([=] {
            ciel::vector<int> primes(ciel::reserve_capacity, 1000);
            for (int i = searchBase; i < searchBase + 1000; ++i) {
                if (isPrime(i)) {
                    primes.unchecked_emplace_back(i);
                }
            }

            ticket->wait();

            // for (auto prime : primes) {
            //     ciel::println("{} is prime", prime);
            // }

            ticket->done();
        });
    }

    queue.take()->wait();
}
