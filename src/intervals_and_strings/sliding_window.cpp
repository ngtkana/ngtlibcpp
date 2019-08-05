/* init crr, ret */
for (int l = 0, r = 0; l < n; l++) {
  if (r <= l) {
    r = l;
    /* re-init crr */;
  }
  for (; r < n; r++) {
    if (/* cannot push r */) break;
    /* push r */;
  }
  ret += r - l;
  /* pop l */
}