<!--
 Copyright (c) 2021 Ketan Goyal
 
 This software is released under the MIT License.
 https://opensource.org/licenses/MIT
-->

# TODO List

1. Create an event queue to store a chronologically ordered sequence of operation event records
    - Implement a no-lock queue data structure
    - Create `EventQueue` class which uses the above to store chronologically ordered sequence of operation event records

2. Create an `Operation` macro to run one or more statements as a single unit. The class should push the start and end event records in the event queue.

3. Create a `Runner` class to execute one or more Lambda functions in multiple threads.

4. Create an `AssertionMap` class to map a sequence of events to a `Assertion` function object. The function object is used to assert expected behavior for the mapped event sequence.
