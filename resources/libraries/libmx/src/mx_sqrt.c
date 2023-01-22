int mx_sqrt(int x) {
    if (x < 0) {
        return 0;
    }

    for (int i = 0; i < x - 1; i++) {
        int squared_i = i * i;
        if (squared_i == x) {
            return i;
        }
        if (squared_i > x || squared_i < i) {
            return 0;
        }
    }

    return 0;
}

