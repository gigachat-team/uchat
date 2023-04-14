#include "../../client.h"


void gui_init_chat_settings_window(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id) {
    uint32_t members_count = 0;
    t_user *members = rq_get_chat_members(*server_address, chat_id, &members_count);
    for (size_t i = 0; i < members_count; i++) {
        printf("Id: %d; Login: %s\n", members[i].id, members[i].login);
    }
    free_users(members, members_count);

    (void)builder;
    (void)user_id;
}
