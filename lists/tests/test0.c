#include <assert.h>

#include "basic_testing.h"
#include "../lists.h"

int main() {
    struct list * L[] = { 0, 0, 0 };

    assert(concatenate_all(3, L) == 0);
    assert(merge_sorted(0, 0) == 0);
    return 0;
}
