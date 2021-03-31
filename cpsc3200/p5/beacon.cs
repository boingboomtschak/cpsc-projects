using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Text;

// Class Invariants:
// - Maximum charge amount is set to 10, any extra charge will not allow the class to exceed that.
// - beacon objects are initialized as "on" and fully charged.
// 

// Interface Invariants:
// - beacon objects return "0" from signal() until the integer sequence is initialized and beacon is on
//   and charged.
// 

namespace Project5CPSC3200 {
    public class beacon : IBeacon {
        protected const int MAX_CHARGE = 10;
        protected int charge;
        protected bool on;
        protected int[] seq;
        protected int curSig;

        // Class Methods
        
        public beacon() {
            charge = MAX_CHARGE;
            on = true;
            curSig = 0;
        }

        // Public Methods

        // PRE: None
        // POST: Internal seq is set to copy of newSeq
        public virtual void setSeq(int[] newSeq) {
            seq = new int[newSeq.Length];
            for (int i = 0; i < newSeq.Length; i++) {
                seq[i] = newSeq[i];
            }
        }
        
        // PRE: seq is initialized with setSeq(), beacon is on and has a greater charge than 0
        // POST: None
        public virtual int signal() {
            if (seq == null) {
                return 0;
            } else if (on && charge > 0) {
                charge--;
                if (curSig + 1 > seq.Length) {
                    curSig = 0;
                }
                return seq[curSig++];
            } else {
                return 0;
            }
        }

        // PRE: None
        // POST: charge has newCharge added to it (if newCharge is a nonzero positive number), and
        //       charge will be at most MAX_CHARGE, any extra charge is wasted.
        public virtual void recharge(int newCharge) {
            if (newCharge > 0) {
                if (charge + newCharge <= MAX_CHARGE) {
                    charge += newCharge; 
                } else {
                    charge = MAX_CHARGE;
                }
            }
        }

        // PRE: None
        // POST: None
        public int getCharge() {
            return charge;
        }

        // PRE: None
        // POST: beacon object is turned on
        public virtual void turnOn() {
            on = true;
        }

        // PRE: None
        // POST: beacon object is turned off
        public virtual void turnOff() {
            on = false;
        }

        // PRE: None
        // POST: None
        public bool isOn() {
            return on;
        }

    }
}

// Implementation Invariants:
// - Max charge amount set as protected class constant "MAX_CHARGE".
// - On/off status is stored as a boolean "on", where beacon is on when it is true, and off when it is
//   false.
// - Internal sequence, when set using setSeq(), makes a copy of the sequence being passed in rather
//   than consuming it.
// 

