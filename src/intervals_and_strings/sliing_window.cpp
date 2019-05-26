int l = 0, r = 0;
for (; l < ${1:n}; l++) {
  while (r < n && ${2:/*valid ? [l, r + 1)*/}) {
    r++;
    ${3:/*visit : [l, r + 1)*/};
  }
}
