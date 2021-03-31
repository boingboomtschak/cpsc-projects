using System;
using System.Collections.Generic;
using System.Text;

// Class Invariants:
// - Cannot be recharged
// - Signal returned is oscillated between positive and negative values

// Interface Invariants:
// - recharge() is inherited from the base class but is set to a NOOP

namespace Project5CPSC3200 {
    public class strobeBeacon : beacon {
        private bool strobe;
        
        // Class Methods
        public strobeBeacon() {
            charge = MAX_CHARGE;
            on = true;
            curSig = 0;
            strobe = true;
        }

        // Public Methods

        // PRE: seq is initialized with setSeq(), beacon is on and has a greater charge than 0
        // POST: None
        public override int signal() {
            if (seq == null) {
                return 0;
            } else if (on && charge > 0) {
                charge--;
                if (curSig + 1 > seq.Length) {
                    curSig = 0;
                }
                if (strobe) {
                    strobe = false;
                    return seq[curSig++];
                } else {
                    strobe = true;
                    return (-1 * seq[curSig++]);
                }
            } else {
                return 0;
            }
        }

        // PRE: None
        // POST: None
        public override void recharge(int newCharge) {
            ; // NOOP to leave recharge signature in place
        }
    }
}

// Implementation Invariants:
// - Tracking of positive and negative signals returned is done using the bool "strobe", where true
//   means the next signal() will return a positive value (assuming the next value in the sequence is
//   also positive) and false means the next signal() will return a negative value