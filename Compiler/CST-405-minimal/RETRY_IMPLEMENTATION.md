# Our Unique C-Minus Feature: Retry Loop

## Summary

The **retry loop construct** provides clean, maintainable error handling patterns with built-in timing and failure recovery.

---

## 🎯 Retry Loop Syntax

### Grammar
```ebnf
retry-stmt ::= 'retry' '(' <int> [',' 'backoff' '=' <int>] ')' <block> ['onfail' <block>]
break-stmt ::= 'break' ';'
```

### Syntax Examples
```c
// Basic retry with early exit on success
retry(3) {
    if (network_call() == SUCCESS) {
        break;  // Exit retry loop immediately
    }
}

// Retry with 5-second backoff delay
retry(5, backoff = 5000) {
    connection = connect_to_server();
    if (connection_status == CONNECTED) {
        print("Connected successfully!");
        break;  // Skip remaining attempts
    }
    print("Connection failed, retrying in 5 seconds...");
}

// Complete retry with failure handling
retry(3, backoff = 5000) {
    status = attempt_operation();
    if (status == SUCCESS) {
        break;  // Success - skip onfail block
    }
} onfail {
    print("All attempts failed");
    use_fallback_method();
}
```

---

## 🔧 Technical Implementation

### TAC Code Generation
The retry loop generates Three-Address Code with:
- Loop counter initialization and management
- Conditional branching for retry limits
- Label generation for loop entry/exit points
- Break statement handling for early termination
- OnFail block conditional execution

### Key Components
- **Retry Counter**: Tracks current attempt number
- **Backoff Timer**: Built-in delay mechanism between attempts
- **Break Support**: Early exit capability from retry loop
- **OnFail Block**: Executes only when all attempts are exhausted
- **Nested Break**: Break statements work within retry loops

---

## 🎯 Language Feature Goals

### Why Retry Loops?
- **Clean Syntax**: Eliminates verbose manual retry logic
- **Built-in Timing**: No need for separate delay functions
- **Failure Handling**: Structured approach to handling complete failures
- **Early Exit**: Break statements allow optimization when success is achieved
- **Readable Code**: Self-documenting retry behavior

### Real-world Applications

- Network connection establishment
- Service API calls with retry policies  
- File system operations with transient failures
- Database connection retries
- Resource acquisition with backoff strategies

---


## 🎮 Demo Program: simple_retry.cm

The demonstration program showcases both success and failure scenarios with visible 5-second delays:

### Key Demonstrations
1. **Early Success with Break**: Demo 1 shows retry loop exiting early when connection succeeds
2. **Complete Failure Handling**: Demo 2 shows all attempts failing and onfail block execution
3. **Automatic Backoff**: Built-in 5-second delays between retry attempts
4. **Realistic Scenarios**: Network connections and API service calls

---

## 🧪 Demo Testing

### Running the Demo
```bash
./minicompiler simple_retry.cm output.s
```

### Expected QtSPIM Output
```
=== C-Minus Retry Loop Demonstration ===
Note: Each attempt includes a 5-second backoff delay

=== Demo 1: Retry with Success Detection ===
Simulating network connection attempts...

>>> Attempting connection - Try #
1
    Connecting to server...
    FAILED: Connection refused
    Waiting 5 seconds before retry...
[5-second delay]

>>> Attempting connection - Try #
2  
    Connecting to server...
    FAILED: Connection refused
    Waiting 5 seconds before retry...
[5-second delay]

>>> Attempting connection - Try #
3
    Connecting to server...
    SUCCESS: Connection established!
    Breaking out of retry loop...

--- Demo 1 Results ---
Final connection status: 1
Total attempts made: 3
========================

=== Demo 2: Retry with Guaranteed Failure ===
[Similar pattern with all 3 attempts failing]
ERROR: Service permanently unavailable
RECOVERY: Switching to backup service
========================
```
---