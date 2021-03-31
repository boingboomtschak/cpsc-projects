using System;
using System.Transactions;

namespace Project3CPSC3200 {
    class P3 {
        static void Main(string[] args) {
            Console.WriteLine("---- CPSC3200 P3 ----");
            Console.WriteLine("--- By Devon McKee --");
            Console.WriteLine("\nClass Testing:\n");
            Console.WriteLine("Testing Heterogeneous Collections...");
            testHeterogeneousCollections();
            Console.WriteLine();
            Console.WriteLine("Testing Variety Instantiation...");
            testVarietyInstantiation();
            Console.WriteLine();
            Console.WriteLine("Testing Mode Changes...");
            testModeChanges();
            Console.WriteLine();
            Console.WriteLine("Driver testing complete!");
            Console.WriteLine("Exiting program... ");
        }

        static void testHeterogeneousCollections() {
            dataFilter[] collect = new dataFilter[4];
            collect[0] = new dataFilter();
            collect[1] = new dataFilter(17);
            collect[2] = new dataMod(23);
            collect[3] = new dataCut(29);
            Random rnd = new Random();
            int[] testArray = new int[6] { 
                rnd.Next(1, 50), 
                rnd.Next(1, 50), 
                rnd.Next(1, 50), 
                rnd.Next(1, 50), 
                rnd.Next(1, 50), 
                rnd.Next(1, 50) 
            };
            Console.Write("Testing Array: ");
            for (int i = 0; i < testArray.Length; i++) {
                Console.Write(testArray[i] + " ");
            }
            Console.Write("\n");
            for (int i = 0; i < collect.Length; i++) {
                collect[i].scramble(testArray);
                int[] dFilter = collect[i].filter();
                Console.Write("Filtered Array: ");
                for (int j = 0; j < dFilter.Length; j++) {
                    Console.Write(dFilter[j] + " ");
                }
                Console.Write("\n");
            }


        }

        static void testVarietyInstantiation() {
            Random rnd = new Random();
            int arrLength = rnd.Next(1, 20);
            Console.WriteLine("Initializing array of dataFilters of length " + arrLength + "...");
            dataFilter[] arr = new dataFilter[arrLength];
            for (int i = 0; i < arr.Length; i++) {
                arr[i] = new dataFilter(rnd.Next(1, 50));
            }
            int[] testArray = new int[rnd.Next(1, 50)];
            Console.WriteLine("Initializing array of random integers of size " + testArray.Length + "...");
            for (int i = 0; i < testArray.Length; i++) {
                testArray[i] = rnd.Next(1, 50);
            }
            Console.WriteLine("Calling scramble() and filter() sequentially on each dataFilter...");
            for (int i = 0; i < arr.Length; i++) {
                arr[i].scramble(testArray);
                arr[i].filter();
            }

        }

        static void testModeChanges() {
            Console.WriteLine("Initializing dataFilter and testing various setPrimes...");
            dataFilter d = new dataFilter(17);
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
    }
}

