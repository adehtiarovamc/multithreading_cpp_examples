#include <iostream>
#include <limits.h>
#include <mutex>

using namespace std::chrono_literals;

// example is almost identical to the one provided in Anthony Williams book (chapter 3)
//
class HierarchicalMutex
{
public:
    explicit HierarchicalMutex(int value)
        : hierarchy_(value)
        , prev_hierarchy_(0)
    {
    }

    bool check_for_hierarchy_violation()
    {
        if (this_thread_hierarchy_ <= hierarchy_)
            return false;

        return true;
    }

    void update_hierarchy_value()
    {
        prev_hierarchy_ = this_thread_hierarchy_;
        this_thread_hierarchy_ = hierarchy_;
        std::cout << "hierarchy_value: " << this_thread_hierarchy_ << '\n';
    }

    void lock()
    {
        if (!check_for_hierarchy_violation())
            throw std::logic_error("bad_hierarchy");

        m_.lock();
        update_hierarchy_value();
    }

    void unlock()
    {
        if (this_thread_hierarchy_ != hierarchy_)
            throw std::logic_error("bad_hierarchy");
        
        this_thread_hierarchy_ = prev_hierarchy_;

        m_.unlock();
    }

    bool try_lock()
    {
        check_for_hierarchy_violation();
        if (!m_.try_lock())
        {
            return false;
        }

        update_hierarchy_value();
        return true;
    }

private:
    std::mutex m_;
    int hierarchy_;
    int prev_hierarchy_;
    static thread_local int this_thread_hierarchy_;
};

thread_local int HierarchicalMutex::this_thread_hierarchy_(INT_MAX);


int main (int argc, char *argv[]) {

    HierarchicalMutex high_lvl(100);
    HierarchicalMutex low_lvl(1);

    std::thread high_lvl_t([&high_lvl, &low_lvl]() {
        std::lock_guard<HierarchicalMutex> high_lvl_lck(high_lvl);
        std::lock_guard<HierarchicalMutex> low_lvl_lck(low_lvl);
        std::this_thread::sleep_for(5s);
    });


    std::thread low_lvl_t([&high_lvl, &low_lvl]() {
        std::lock_guard<HierarchicalMutex> low_lvl_lck(low_lvl);
        std::lock_guard<HierarchicalMutex> high_lvl_lck(high_lvl); // wrong hierarchy, exception thrown and 'terminate' is called
        std::this_thread::sleep_for(5s);
    });

    high_lvl_t.join();
    low_lvl_t.join();
    return 0;
}
