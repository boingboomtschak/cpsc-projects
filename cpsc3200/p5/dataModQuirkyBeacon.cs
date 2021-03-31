using System;
using System.Collections.Generic;
using System.Text;

namespace Project5CPSC3200 {
    public class dataModQuirkyBeacon : ADataBeacon {
        private dataMod df;
        private quirkyBeacon bc;

        // Class Methods

        public dataModQuirkyBeacon() {
            df = new dataMod();
            bc = new quirkyBeacon();
        }

        public dataModQuirkyBeacon(int prime) {
            df = new dataMod(prime);
            bc = new quirkyBeacon();
        }

        // Interface Methods

        public override void setSeq(int[] newSeq) {
            bc.setSeq(newSeq);
        }

        public override int signal() {
            return bc.signal();
        }

        public override void recharge(int newCharge) {
            bc.recharge(newCharge);
        }

        public override int getCharge() {
            return bc.getCharge();
        }

        public override void turnOn() {
            bc.turnOn();
        }

        public override void turnOff() {
            bc.turnOff();
        }

        public override bool isOn() {
            return bc.isOn();
        }

        public override int[] filter() {
            return df.filter();
        }

        public override int[] scramble(int[] newSeq) {
            return df.scramble(newSeq);
        }

        public override bool getMode() {
            return df.getMode();
        }

        public override void setMode(bool newMode) {
            df.setMode(newMode);
        }

        public override void setPrime(int p) {
            df.setPrime(p);
        }
    }
}
