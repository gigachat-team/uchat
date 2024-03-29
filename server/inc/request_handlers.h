#pragma once

#include <unistd.h>
#include "senders.h"
#include "threads.h"
#include "request.h"
#include "database.h"
#include "receivers.h"
#include "state_code.h"
#include "server_senders.h"
#include "server_receivers.h"

void *handle_client_request_thread(void *allocated_client_socket);

void handle_chat_creation(int client_socket);
void handle_getting_chats(int client_socket);
void handle_adding_new_member_to_chat(int client_socket);
/**
 * @brief Receives text message data from CLIENT_SOCKET, creates entry in database
 * and send response to CLIENT_SOCKET: TEXT_MESSAGE_SEND_SUCCESSFULLY for success.
*/
void handle_text_message_sending(int client_socket);
void handle_messages_in_chat_getting(int client_socket);
void handle_message_sending_and_messages_updates_getting(int client_socket);
void handle_message_deleting_and_messages_updates_getting(int client_socket);
void handle_message_changing_and_message_updates_getting(int client_socket);
void handle_message_replying_and_message_updates_getting(int client_socket);
void handle_message_updates_getting(int client_socket);
void handle_removing_user_from_chat(int client_socket);
void handle_getting_chat_members(int client_socket);
void handle_registration(int client_socket);
void handle_login(int client_socket);
void handle_login_changing(int client_socket);
void handle_account_deleting(int client_socket);
