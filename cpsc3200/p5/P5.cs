using System;

namespace Project5CPSC3200 {
    class P5 {
        static void Main(string[] args) {
            Console.WriteLine("---- CPSC3200 P3 ----");
            Console.WriteLine("--- By Devon McKee --");
            Console.WriteLine("\nClass Testing:\n");
            Console.WriteLine("Testing Heterogeneous Collections...");
            testHeterogeneousCollections();
            Console.WriteLine();
            Console.WriteLine("Testing Variety Mode Changes for dataFilter-like objects...");
            testVarietyModeChangesDataFilter();
            Console.WriteLine();
            Console.WriteLine("Testing Variety Mode Changes for beacon-like objects...");
            testVarietyModeChangesBeacon();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("Driver testing complete!");
            Console.WriteLine("Exiting program... ");
        }
        
        static void testHeterogeneousCollections() {
            ADataBeacon[] adb = new ADataBeacon[9];
            int[] testArray = new int[] { 1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
            Console.WriteLine("Testing heterogeneous collection with composite types...");
            adb[0] = new dataFilterBeacon();
            adb[1] = new dataFilterStrobeBeacon();
            adb[2] = new dataFilterQuirkyBeacon();
            adb[3] = new dataModBeacon();
            adb[4] = new dataModStrobeBeacon();
            adb[5] = new dataModQuirkyBeacon();
            adb[6] = new dataCutBeacon();
            adb[7] = new dataCutStrobeBeacon();
            adb[8] = new dataCutQuirkyBeacon();
            for (int i = 0; i < adb.Length; i++) {
                adb[i].scramble(testArray);
                adb[i].setMode(true);
                adb[i].filter();
                adb[i].setSeq(testArray);
                adb[i].getMode();
                adb[i].setPrime(37);
                adb[i].getCharge();
                adb[i].recharge(5);
                for (int j = 0; j < 5; j++) {
                    adb[i].signal();
                }
                adb[i].turnOff();
                adb[i].isOn();
                adb[i].turnOn();
            }
        }

        static void testVarietyModeChangesDataFilter() {
            Console.WriteLine("Initializing dataFilterBeacon and testing various setPrimes...");
            dataFilterBeacon d = new dataFilterBeacon(17);
            Console.Write(d.filter()[0] + " ");
            d.setPrime(18);
            Console.Write(d.filter()[0] + " ");
            d.setPrime(181);
            Console.WriteLine(d.filter()[0]);
            d.setPrime(23);
            Console.WriteLine("Initializing test array and testing filter in small and large mode...");
            Random rnd = new Random();
            int[] testArray = new int[6] {
                rnd.Next(1, 50),
                rnd.Next(1, 50),
                rnd.Next(1, 50),
                rnd.Next(1, 50),
                rnd.Next(1, 50),
                rnd.Next(1, 50)
            };
            Console.WriteLine("Current Prime: 23");
            Console.Write("Test Array: ");
            for (int i = 0; i < testArray.Length; i++) {
                Console.Write(testArray[i] + " ");
            }
            Console.Write("\n");
            d.scramble(testArray);
            int[] filteredSmall = d.filter();
            Console.Write("Filtered Array (Small): ");
            for (int i = 0; i < filteredSmall.Length; i++) {
                Console.Write(filteredSmall[i] + " ");
            }
            Console.Write("\n");
            d.setMode(true);
            int[] filteredLarge = d.filter();
            Console.Write("Filtered Array (Large): ");
            for (int i = 0; i < filteredLarge.Length; i++) {
                Console.Write(filteredLarge[i] + " ");
            }
            Console.Write("\n");
        }

        static void testVarietyModeChangesBeacon() {
            ADataBeacon[] adb = new ADataBeacon[9];
            int[] testArray = new int[] { 9, 24, 39, 10, 54 };
            Console.WriteLine("Initializing collection of composite types");
            adb[0] = new dataFilterBeacon();
            adb[1] = new dataFilterStrobeBeacon();
            adb[2] = new dataFilterQuirkyBeacon();
            adb[3] = new dataModBeacon();
            adb[4] = new dataModStrobeBeacon();
            adb[5] = new dataModQuirkyBeacon();
            adb[6] = new dataCutBeacon();
            adb[7] = new dataCutStrobeBeacon();
            adb[8] = new dataCutQuirkyBeacon();
            Console.Write("Charges: ");
            for (int i = 0; i < adb.Length; i++) {
                adb[i].setSeq(testArray);
                for (int j = 0; j < 5; j++) {
                    if (adb[i].isOn()) {
                        adb[i].turnOff();
                    } else {
                        adb[i].turnOn();
                    }
                    adb[i].signal();
                }
                adb[i].recharge(5);
                Console.Write(adb[i].getCharge() + " ");
            }
            Console.WriteLine();
        }
    }
}
