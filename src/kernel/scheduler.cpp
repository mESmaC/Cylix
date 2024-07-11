#include <cstdint>

extern "C" void context_switch(void* old_context, void* new_context);

struct Context {
    uint64_t registers[6];  
    uint64_t rsp;
};

void initialize_scheduler() {
}

void schedule() {
}