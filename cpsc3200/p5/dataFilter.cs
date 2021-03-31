using System;

// Class Invariants:
// - dataFilter is always either in "small" mode or "large" mode.
// - dataFilter encapsulates an int[] sequence, and a prime number 
// - 'prime' will always be prime, ensured by the class methods to interface with it.

// Interface Invariants:
// - Public method getMode() returns true if the dataFilter is in large mode, false if in small mode.
// - Class iterables are int[], and any sequence parameters should take int[]
// - filter() returns a filtered sequence of integers, where numbers larger than prime are 
//   returned (large mode) or numbers smaller than prime are return (small mode)
// - scramble() updates the internal sequence and returns a reordered sequence of ints where 

namespace Project5CPSC3200 {
    public class dataFilter : IDataFilter {
        protected int prime;
        protected bool mode;
        protected int[] seq;

        // Class Methods

        public dataFilter() {
            prime = 2; // Defaults to first prime number
            mode = false;
        }

        public dataFilter(int p) {
            if (isPrime(p)) {
                prime = p;
            } else {
                prime = 2;
            }
            mode = false;
        }

        // Public Methods

        // POST: Returns filtered array of ints based on class mode, or returns array containing only prime
        //       if seq is null
        public virtual int[] filter() {
            if (seq == null) {
                return new int[] { prime };
            }
            int filteredLength = 0;
            for (int i = 0; i < seq.Length; i++) { // Not ideal but this is a refactor from using List<int>
                if (mode) {
                    if (seq[i] > prime) { filteredLength++; }
                } else {
                    if (seq[i] < prime) { filteredLength++; }
                }
            }
            int[] filtered = new int[filteredLength];
            int filteredCount = 0;
            for (int i = 0; i < seq.Length; i++) {
                if (mode) {
                    if (seq[i] > prime) {
                        filtered[filteredCount] = seq[i];
                        filteredCount++;
                    }
                } else {
                    if (seq[i] < prime) {
                        filtered[filteredCount] = seq[i];
                        filteredCount++;
                    }
                }
            }
            return filtered;
        }

        // PRE: scramble() takes an integer array 
        // POST: The scrambled sequence of integers is returned as an integer array
        public virtual int[] scramble(int[] newSeq) {
            if (seq == null) {
                seq = new int[newSeq.Length];
                for (int i = 0; i < newSeq.Length; i++) {
                    seq[i] = newSeq[i];
                }
            }
            int[] reordered = new int[newSeq.Length];
            for (int i = 0; i < newSeq.Length; i++) {
                if ((i + 1) % 2 == 0) {
                    if (mode) {
                        // 'Large' mode
                        if (newSeq[i] > newSeq[i - 1]) {
                            reordered[i - 1] = newSeq[i];
                            reordered[i] = newSeq[i - 1];
                        } else {
                            reordered[i - 1] = newSeq[i - 1];
                            reordered[i] = newSeq[i];
                        }
                    } else {
                        // 'Small' mode
                        if (newSeq[i] < newSeq[i - 1]) {
                            reordered[i - 1] = newSeq[i];
                            reordered[i] = newSeq[i - 1];
                        } else {
                            reordered[i - 1] = newSeq[i - 1];
                            reordered[i] = newSeq[i];
                        }
                    }
                }
            }
            if (newSeq.Length % 2 != 0) {
                reordered[newSeq.Length - 1] = newSeq[newSeq.Length - 1];
            }
            return reordered;
        }

        public bool getMode() {
            return mode;
        }

        // POST: Mode is set to either true ('large') or small ('false')
        public void setMode(bool newMode) {
            mode = newMode;
        }

        // POST: If p is prime, prime is set to p, otherwise p is unchanged
        public void setPrime(int p) {
            if (isPrime(p)) {
                prime = p;
            }
        }

        // Private/Protected Methods

        // Helper function to check if number prime
        protected bool isPrime(int n) {
            for (int i = 2; i < n; i++) {
                if (n % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }
}

// Implementation Invariants
// - Mode is stored in a boolean, 'mode', which is either false (mode is 'small') or true (mode is 'large')
// - Mode is 'small' by default (mode = false)
// - filter() returns int[] of filtered numbers if encapsulated seq != null, returns int[] containing only
//   prime otherwise (to keep interface consistent)
// - If constructor is passed non-prime number for prime, prime is initialized to first prime (2), and can be
//   set again with a valid prime using setMode9)