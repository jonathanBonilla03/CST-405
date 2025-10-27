// Test simple mathematical expressions
float testBasicPrecedence() {
    int a = 2;
    int b = 3;
    int c = 4;
    float result;

    // Check */ over +- precedence and type casting
    result = (float)a + (float)b * (float)c - (float)a / (float)b; // 2 + 3*4 - 2/3 = 2 + 12 - 0.6667 = 13.3333
    return result;
}

float testComplexPrecedence() {
    int a = 5;
    int b = 10;
    int c = 2;

    // Check mixed operations + exponents & parentheses
    // (5 + 10) ** (2 - 0.5) = 15 ** 1.5 = 58.0947
    return ((float)a + (float)b) ** ((float)c - (float)a / (float)b);
}

float testArrayMath() {
    int arr[3] = {2, 3, 4};
    float result;

    // Perform arithmetic on array elements with type casting
    result = (float)arr[0] ** (float)arr[1] + (float)arr[2]; // 2 ** 3 + 4 = 8 + 4 = 12
    return result;
}

float testScopesA(int a, int b) {
    float result;
    result = (float)a + (float)b;
    return result;
}

float testScopesB(int a, int b) {
    float result;
    result = (float)a * (float)b;
    return result;
}

/* Test exponentiation operator */
void main() {
    print(testBasicPrecedence()); // 13.3333
    print(testComplexPrecedence()); // 58.0947
    print(testArrayMath()); // 12.0
    print(testScopesA(3, 4)); // 7.0
    print(testScopesB(3, 4)); // 12.0

    float store;
    store = testScopesA(6, 2) ** testScopesB(2, 3); // (6+2) ** (2*3) = 8 ** 6 = 262144
    print(store); // 262144.0
}