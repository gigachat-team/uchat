#include "../utils.h"

t_package create_package(size_t size) {
    t_package package = {
        .buffer = malloc(sizeof(struct iovec) * size),
        .size = size,
        .filled_size = 0
    };
    return package;
}

void free_package(t_package package) {
    for (size_t i = 0; i < package.filled_size; i++) {
        free(package.buffer[i].iov_base);
    }
    free(package.buffer);
}

void handle_packer_error(t_package package, char *message) {
    if (package.filled_size + 1 > package.size) {
        fprintf(stderr, "%s: The filled size of the package can't be greater than the size", message);
        exit(EXIT_FAILURE);
    }
}

void pack_byte(uint8_t byte, t_package *package) {
    handle_packer_error(*package, "Failed to pack a byte");
    uint8_t *allocated_value = malloc(sizeof(byte));
    *allocated_value = byte;
    package->buffer[package->filled_size].iov_base = allocated_value;
    package->buffer[package->filled_size++].iov_len = sizeof(byte);
}

void pack_uint16(uint16_t number, t_package *package) {
    handle_packer_error(*package, "Failed to pack an uint16");
    uint16_t *converted_value = malloc(sizeof(number));
    *converted_value = htons(number);
    package->buffer[package->filled_size].iov_base = converted_value;
    package->buffer[package->filled_size++].iov_len = sizeof(number);
}

void pack_uint32(uint32_t number, t_package *package) {
    handle_packer_error(*package, "Failed to pack an uint32");
    uint32_t *converted_value = malloc(sizeof(number));
    *converted_value = htonl(number);
    package->buffer[package->filled_size].iov_base = converted_value;
    package->buffer[package->filled_size++].iov_len = sizeof(number);
}

void pack_bytes(char *bytes, t_package *package) {
    handle_packer_error(*package, "Failed to pack bytes");
    uint32_t number_of_bytes = strlen(bytes);
    uint32_t converted_number_of_bytes = htonl(number_of_bytes);

    const size_t number_of_sending_bytes = sizeof(uint32_t) + (number_of_bytes * sizeof(char));
    char *sending_bytes = malloc(number_of_sending_bytes);
    memcpy(sending_bytes, &converted_number_of_bytes, sizeof(uint32_t));
    strncpy(sending_bytes + sizeof(uint32_t), bytes, number_of_bytes);

    package->buffer[package->filled_size].iov_base = sending_bytes;
    package->buffer[package->filled_size++].iov_len = number_of_sending_bytes;
}

void send_package(int socket, t_package package) {
    writev(socket, package.buffer, package.filled_size);
}

void send_and_free_package(int socket, t_package package) {
    send_package(socket, package);
    free_package(package);
}
