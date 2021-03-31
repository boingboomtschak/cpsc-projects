using System;
using System.Text;

// Class Invariants:
//
//

// Interface Invariants:
// - filter() returns a filtered array of ints with the same pattern as dataFilter.filter(),
//   but each item is incremented (large mode) or decremented (small mode) after filtering
// - scramble() takes an integer array in the same way as dataFilter.scramble(), but replaces
//   all prime numbers in the array with '2', the first prime number before scrambling

namespace Project5CPSC3200 {
    public class dataMod : dataFilter {

        // Class Methods
        public dataMod() {
            prime = 2; // Defaults to first prime number
            mode = false;
        }

        public dataMod(int p) {
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
            for (int i = 0; i < filtered.Length; i++) {
                if (mode) {
                    // 'Large' mode
                    filtered[i] = filtered[i] + 1;
                } else {
                    // 'Small' mode
                    filtered[i] = filtered[i] - 1;
                }
            }
            return filtered;
        }

        public override int[] scramble(int[] newSeq) {
            for (int i = 0; i < newSeq.Length; i++) {
                if (isPrime(newSeq[i])) {
                    newSeq[i] = 2;
                }
            }
            return base.scramble(newSeq);
        }
    }
}

// Implementation Invariants:
//
//
