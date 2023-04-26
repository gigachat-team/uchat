#include "id_and_changes_count.h"

t_id_and_changes_count_array create_id_and_changes_count(size_t len) {
    t_id_and_changes_count_array id_and_changes_count_array = {
        .arr = malloc(len * sizeof(t_id_and_changes_count)),
        .len = len
    };
    return id_and_changes_count_array;
}
