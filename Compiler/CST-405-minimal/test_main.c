int add(int x, int y) {
    return x + y;
}

print(1); // Should not run

void main() {
    int a;
    int b;
    int c;
    int d;

    a = 10;
    b = 20;
    c = add(a, b); // c should be 30
    print(c); // Expect 30

    d = add(c, 5); // d should be 35
    print(d); // Expect 35
}

// Tests Optional Main