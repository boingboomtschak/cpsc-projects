using System;
using System.Collections.Generic;
using System.Text;

namespace Project5CPSC3200 {
    public abstract class ADataBeacon : IDataFilter, IBeacon {
        public abstract int[] filter();
        public abstract int[] scramble(int[] newSeq);
        public abstract bool getMode();
        public abstract void setMode(bool newMode);
        public abstract void setPrime(int p);
        public abstract void setSeq(int[] seq);
        public abstract int signal();
        public abstract void recharge(int newCharge);
        public abstract int getCharge();
        public abstract void turnOn();
        public abstract void turnOff();
        public abstract bool isOn();
    }
}
