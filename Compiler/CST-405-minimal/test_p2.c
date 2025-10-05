// Arithmetic and logical test
int a;
int b;
int c;
int d;
bool flag;

a = 5;
b = 2;
c = a * b + 10 / 2;     // c = 5*2 + 5 = 15
flag = (a > b) && (c == 15);

if (flag) {
    print(c);           // Expect 15
} else {
    print(a);
}

// Nested if and negation
d = 3;
if (!(d > 5) || (a == 5)) {
    print(d);           // Expect 3
} else {
    print(b);
}

// Test relational operators and else branch
if (a < b) {
    print(100);         // Should not print
} else {
    print(999);         // Expect 999
}