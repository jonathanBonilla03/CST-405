float multiply(int a, int b) {
    float c;
    c = (float)a * (float)b;
    return c;
}
float add(int a, int b) {
    float c;
    c = (float)a + (float)b;
    return c;
}

void main() {
    int x;
    x = 2;
    int y;
    y = 3;
    float resultM;
    resultM = multiply(x, y);
    print(resultM); // Should print 6.0
    float resultA;
    resultA = add(x, y);
    print(resultA); // Should print 5.0
}
