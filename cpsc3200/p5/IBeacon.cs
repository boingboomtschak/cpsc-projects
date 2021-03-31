using System;
using System.Collections.Generic;
using System.Text;

namespace Project5CPSC3200 {
    interface IBeacon {
        void setSeq(int[] seq);
        int signal();
        void recharge(int newCharge);
        int getCharge();
        void turnOn();
        void turnOff();
        bool isOn();
    }
}
