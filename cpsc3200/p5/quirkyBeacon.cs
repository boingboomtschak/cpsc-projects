using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// Class Invariants:
// - quirkyBeacon emits signals with a largely undiscernible pattern.
// - quirkyBeacon has a finite number of switches between on and off, which disables the functionality
//   of turnOn() and turnOff() when it is exceeded.
// - Max number of switches is set to the absolute value of the maximum in the list upon calls to
//   setSeq(), initializes to 10.

// Interface Invariants:
// - 

namespace Project5CPSC3200 {
    public class quirkyBeacon : beacon {
        private int MAX_SWITCHES;
        private int switches;

        // Class Methods
        public quirkyBeacon() {
            charge = MAX_CHARGE;
            on = true;
            curSig = 0;
            switches = 0;
            MAX_SWITCHES = 10;
        }

        // Public Methods

        // PRE: None
        // POST: Internal seq is set to copy of newSeq
        public override void setSeq(int[] newSeq) {
            seq = new int[newSeq.Length];
            for (int i = 0; i < newSeq.Length; i++) {
                seq[i] = newSeq[i];
            }
            MAX_SWITCHES = Math.Abs(seq.Max());
        }

        // PRE: seq is initialized with setSeq(), beacon is on and has a greater charge than 0, and 
        //      the amount of switches (between on and off) does not exceed MAX_SWITCHES
        // POST: None
        public override int signal() {
            if (seq == null) {
                return 0;
            } else if (on && charge > 0) {
                charge--;
                curSig = quirky(curSig); 
                return seq[curSig];
            } else {
                return 0;
            }
        }

        // PRE: None
        // POST: If switches <= MAX_SWITCHES, switches++ and quirkyBeacon object turned on
        public override void turnOn() {
            if (switches <= MAX_SWITCHES) {
                switches++;
                base.turnOn();
            }
        }

        // PRE: None
        // POST: If switches <= MAX_SWITCHES, switches++ and quirkyBeacon object turned off
        public override void turnOff() {
            if (switches <= MAX_SWITCHES) {
                switches++;
                base.turnOff();
            }
        }

        // Private Methods

        // Helper method to mess with curSig on each signal()
        private int quirky(int signal) {
            if (signal != 0) {
                signal = Convert.ToInt32(Math.Pow(signal, 2) + Math.Log(Math.Pow(signal, 4)));
            }
            if (signal > 0 && signal >= seq.Length) {
                while (signal >= seq.Length) {
                    signal -= seq.Length;
                }
                return signal;
            } else if (signal < 0) {
                while (signal < 0) {
                    signal += seq.Length;
                }
                return signal;
            } else {
                return signal;
            }

        }
    }
}

// Implementation Invariants:
// - quirkyBeacon uses quirky(int) to modify current signal when calling signal()
