using System;
using System.Text;

// Class Invariants:
// - The class encapsulates an integer array which details the last scrambled sequence
// 

// Interface Invariants:
// - filter() works with the same function signature and pattern as dataFilter.filter(), but
//   removes the maximum number from the array (large mode) or removes the minimum number from
//   the array (small mode)
// - scramble() removes any number that occurred in the previous call to scramble(), and then
//   executes scramble() in an identical pattern to dataFilter.scramble()

namespace Project5CPSC3200 {
    public class dataCut : dataFilter {
        private int[] lastScrambled;

        // Class Methods

        public dataCut() {
            prime = 2; // Defaults to first prime number
            mode = false;
        }

        public dataCut(int p) {
            if (isPrime(p)) {
                prime = p;
            } else {
                prime = 2;
            }
            mode = false;
        }

        // Public Methods

        public override int[] filter() {
            int[] filtered = base.filter();
            if (mode) {
                // 'Large' mode
                int max = filtered[0];
                int maxCount = 1;
                for (int i = 1; i < filtered.Length; i++) {
                    if (filtered[i] > max) {
                        max = filtered[i];
                        maxCount = 1;
                    } else if (filtered[i] == max) {
                        maxCount++;
                    }
                }
                int[] removed = new int[filtered.Length - maxCount];
                int removedCount = 0;
                for (int i = 0; i < filtered.Length; i++) {
                    if (filtered[i] != max) {
                        removed[removedCount] = filtered[i];
                        removedCount++;
                    }
                }
                return removed;
            } else {
                // 'Small' mode
                // find min
                int min = filtered[0];
                int minCount = 1;
                for (int i = 1; i < filtered.Length; i++) {
                    if (filtered[i] < min) {
                        min = filtered[i];
                        minCount = 1;
                    } else if (filtered[i] == min) {
                        minCount++;
                    }
                }
                int[] removed = new int[filtered.Length - minCount];
                int removedCount = 0;
                for (int i = 0; i < filtered.Length; i++) {
                    if (filtered[i] != min) {
                        removed[removedCount] = filtered[i];
                        removedCount++;
                    }
                }
                return removed;
            }

        }

        public override int[] scramble(int[] newSeq) {
            if (lastScrambled == null) {
                int[] scrambled = base.scramble(newSeq);
                lastScrambled = new int[newSeq.Length];
                for (int i = 0; i < newSeq.Length; i++) {
                    lastScrambled[i] = newSeq[i];
                }
                return scrambled;
            } else {
                // Not ideal but this is a refactor from using List<int>
                int removedLength = 0;
                for (int i = 0; i < newSeq.Length; i++) {
                    bool remove = false;
                    for (int j = 0; j < lastScrambled.Length; j++) {
                        if (newSeq[i] == lastScrambled[j]) {
                            remove = true;
                        }
                    }
                    if (!remove) {
                        removedLength++;
                    }
                }
                int[] removed = new int[removedLength];
                int removeCount = 0;
                for (int i = 0; i < newSeq.Length; i++) {
                    bool remove = false;
                    for (int j = 0; j < lastScrambled.Length; j++) {
                        if (newSeq[i] == lastScrambled[j]) {
                            remove = true;
                        }
                    }
                    if (!remove) {
                        removed[removeCount] = newSeq[i];
                        removeCount++;
                    }
                }
                int[] scrambled = base.scramble(removed);
                return scrambled;
            }
        }
    }
}

// Implementation Invariants:
// - last scrambled sequence is stored in the class as an int[] private variable
