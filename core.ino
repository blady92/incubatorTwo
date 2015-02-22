int pow (int a, int b) {
  if (b == 0) return 1;
  int olda = a;
  for (int i = 1; i < b; i++) {
    a *= olda;
  }
  return a;
}
