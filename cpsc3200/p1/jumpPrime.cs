using System;
using System.Collections.Generic;
using System.Text;

// Class Invariants:
// Encapsulated number 'num' >= MIN_VALUE
// jumpPrime must be initialized with an integer

// Interface Invariants: 
// jumpPrime.up() or jumpPrime.down() returns 0 if inactive if jumpPrime is inactive
// jumpPrime.up() or jumpPrime.down() returns another number n where n > 0 if jumpPrime is active


namespace Project1CPSC3200 
{
    class jumpPrime {
        private const int DEFAULT_JUMP_BOUND = 10;
        private const int MIN_VALUE = 1000;

        private int num;
        private int startingNum; 
        private int prevPrime;
        private int nextPrime;
        private int queries; 
        private int jumps;
        private int jumpBound = DEFAULT_JUMP_BOUND;

        // Post: num == n
        public jumpPrime(int n) {
            queries = jumps = 0;
            if (n < MIN_VALUE) {
                jumpBound = -1;
            }
            startingNum = num = n;
            prevPrime = findPrevPrime();
            nextPrime = findNextPrime();
        }

        // Post: queries++
        public int up() {
            queries++;
            // Jump if number of queries exceeds difference between closest primes
            if (queries >= (nextPrime - prevPrime) && jumps < jumpBound) {
                jump();
                jumps++;
                queries = 0;
            }

            if (jumps < jumpBound) {
                return nextPrime;
            } else {
                return 0;
            }
        }

        // Post: queries++
        public int down() {
            queries++;
            // Jump if number of queries exceeds difference between closest primes
            if (queries >= (nextPrime - prevPrime) && jumps < jumpBound) {
                jump();
                jumps++;    
                queries = 0;
            }

            if (jumps < jumpBound) {
                return prevPrime;
            } else {
                return 0;
            }
        }

        // Post: num set to startingNum
        public void reset() {
            num = startingNum;
            queries = jumps = 0;
            prevPrime = findPrevPrime();
            nextPrime = findNextPrime();
            
        }

        // Post: jumps = 0 if jumps >= JUMP_BOUND, JUMP_BOUND = -1 if jumps < JUMP_BOUND
        public void revive() {
            if (jumps < jumpBound) {
                jumpBound = -1;
            } else {
                jumps = 0;
                queries = 0;
            }
        }

        public bool isActive() {
            if (jumps < jumpBound) {
                return true;
            } else {
                return false;
            }
        }

        // Pre: num > MIN_VALUE
        private int findPrevPrime() {
            int ctr;
            for(int i = num; i >= 1; i--) {
                ctr = 0;
                for (int j = 2; j < i; j++) {
                    if (i % j == 0) {
                        ctr++;
                    }
                }
                if (ctr == 0) {
                    return i;
                } 
            }
            return 0;
        }

        // Pre: num > MIN_VALUE
        private int findNextPrime() {
            int ctr;
            for (int i = num + 1; i <= int.MaxValue; i++) {
                ctr = 0;
                for (int j = 2; j < i; j++) {
                    if (i % j == 0) {
                        ctr++;
                    }
                }
                if (ctr == 0) {
                    return i;
                }
            }
            return 0;
        }

        // Post: num is reassigned to new number based on jump decision
        private void jump() {
            int lower_jump = prevPrime - (Math.Abs(prevPrime - num));
            int upper_jump = nextPrime + (Math.Abs(nextPrime - num));
            if (Math.Abs(num - lower_jump) < Math.Abs(num - upper_jump) && lower_jump >= MIN_VALUE) {
                num = lower_jump;
            } else {
                num = upper_jump;
            }
            prevPrime = findPrevPrime();
            nextPrime = findNextPrime();
        }
    }
}

// Implementation Invariants:
// Number of jumps before jumpPrime is invalid is set to 10.
// When jumping, jumpPrime jumps to a number equidistant from the number to the nearest prime number in both directions, whichever is smaller
// Previous prime number (down()) is inclusive of the encapsulated number, and will return the number if it is prime - next prime number (up()) will return the next highest prime number