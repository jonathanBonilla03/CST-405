float divide(int a, int b) {
    float d[2];
    d[0] = (float)a;
    d[1] = (float)b;
    return d[0] / d[1];
}

void main() {
    float x;
    float y;
    x = divide(2, 3);
    y = divide(5, 10);
    if (x > 0 && x < 1) {
        print(x); // Should print 0.666667
        if (y > 0 && y < 1) {
            print(y); // Should print 0.5
        } else {
            print(1);
        }
        if (x + y > 1) {
            print(2); // Should print 2
        }
    } else {
        print(0);
    }
}
