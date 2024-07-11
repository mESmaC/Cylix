#include <cstdint>

extern "C" void context_switch(void* new_context);

struct Context {
    uint32_t registers[8];  
    uint32_t lr;
};

void initialize_scheduler() {
}

void schedule() {
}
