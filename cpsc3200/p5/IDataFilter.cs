using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Project5CPSC3200 {
    interface IDataFilter {
        int[] filter();
        int[] scramble(int[] newSeq);
        bool getMode();
        void setMode(bool newMode);
        void setPrime(int p);
    }
}
