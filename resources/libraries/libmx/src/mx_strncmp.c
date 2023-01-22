int mx_strncmp(const char *s1, const char *s2, int n) {
	for (int i = 0; i < n && (s1[i] != '\0' || s2[i] != '\0'); i++)
		if (s1[i] != s2[i]) return s1[i] - s2[i];
	return 0;
}

